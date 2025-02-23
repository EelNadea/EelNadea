#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_SIZE 32 // Hash table size
#define BUFFER 65 // Buffer space for username and password

// Self-referential-structure to use linked lists when handling collisions from the hash, a.k.a. "chaining"
typedef struct account {
    bool Authenticated;
    char Username[BUFFER];
    char Password[BUFFER];
    double Balance;
    struct account *next;
} account;

typedef struct hashTable {
    account *table[TABLE_SIZE];
} hashTable;

account *AccountCreator(char *username, char *password, double balance) {
    // Allocate memory for the new account
    account *newAccount = (account *)malloc(sizeof(account));

    if (newAccount == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Initialize the variables
    newAccount->Authenticated = false;
    strcpy(newAccount->Username, username);
    strcpy(newAccount->Password, password);
    newAccount->Balance = balance;
    newAccount->next = NULL;

    return newAccount;
}

/* This hashCode function generates a hash value for a given string (key)
by shifting the current hash value 5 bits to the left and adding the ASCII value of each character,
then returns the hash value modulo the table size (TABLE_SIZE) to ensure it fits within the array bounds. */
unsigned int hashCode(char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }

    return hash % TABLE_SIZE;
}

/* The InsertAccount function calculates the hash index for the given account's username,
then adds the account to the front of the linked list at that index in the hash table by updating the account's next pointer
and the table entry. */
void InsertAccount(hashTable *ht, account *acc) {
    unsigned int index = hashCode(acc->Username);

    acc->next = ht->table[index];
    ht->table[index] = acc;
}

/* The findAccount function calculates the hash index for the given username,
then traverses the linked list at that index in the hash table
to find and return the account with the matching username;
if no match is found, it returns NULL and prints a message. */
account *findAccount(hashTable *ht, char *username) {
    unsigned int index = hashCode(username);

    account *current = ht->table[index];
    while (current != NULL) {

        if (strcmp(current->Username, username) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

// If login successful, print balance
bool ShowBal(bool CheckUserPass, double *Balance) {
    if (CheckUserPass == true) {
        printf("\nBalance: $%lf\n", *Balance);
        return true;
    }
    else {
        return false;
    }
}

// Withdraw or deposit
void WithOrDep(bool *ShowBalReceive, double *Balance) {
    if (*ShowBalReceive == true) {
        char answer[5];
        printf("\nDeposit(dep) or Withdraw(with): "); scanf("%4s", answer);

        double Deposit = 0;
        double Withdraw = 0;

        if (strcmp("dep", answer) == 0) {
            printf("Enter money to deposit: "); scanf("%lf", &Deposit);
            *Balance += Deposit;
            printf("\nNew balance: $%lf", *Balance);
        } 
        else if (strcmp("with", answer) == 0) {
            printf("Enter money to withdraw: "); scanf("%lf", &Withdraw);

            if (Withdraw > *Balance) {
                printf("Invalid amount");
            } 
            else {
                *Balance -= Withdraw;
                printf("\nNew balance: $%lf", *Balance);
            }
        }
    }
}

// Frees the memory of an individual account and any accounts chained to it
void freeAccount(account *acc) {
    account *current = acc;
    account *nextAccount;
    while (current != NULL) {
        nextAccount = current->next;
        free(current);
        current = nextAccount;
    }
}

// Frees all of the accounts in the hash table
void freeHashTable(hashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->table[i] != NULL) {
            freeAccount(ht->table[i]);
        }
    }
}

// Handles all of the commands; such as newacc, login, logout, and exit 
void CommandHandler(hashTable *ht, char *command, account **currentUser) {
    char username[BUFFER];
    char password[BUFFER];
    double balance;
    
    // NEWACC
    if (strcmp(command, "newacc") == 0) {
        printf("Enter username: "); fgets(username, sizeof(username), stdin);
        printf("Enter password: "); fgets(password, sizeof(password), stdin);
        printf("Enter balance: "); scanf("%lf", &balance);

        // Newline character remover
        size_t usernameLen = strlen(username);
        size_t passwordLen = strlen(password);
        if (usernameLen > 0 && username[usernameLen - 1] == '\n') {
            username[usernameLen - 1] = '\0';
        }
        else if (passwordLen > 0 && password[passwordLen - 1] == '\n') {
            password[passwordLen - 1] = '\0';
        }

        account *newAccount = AccountCreator(username, password, balance);
        InsertAccount(ht, newAccount);

        printf("Account created successfully.\n");
        return;
    }

    // LOGIN
    else if (strcmp(command, "login") == 0) {
        
        if ( (*currentUser != NULL) && ((*currentUser)->Authenticated == true) ) {
            printf("You must first log-out.\n");
            return; // Exit out of the entire function
        }

        printf("Enter username: "); fgets(username, sizeof(username), stdin);
        printf("Enter password: "); fgets(password, sizeof(password), stdin);

        // Newline character remover
        size_t usernameLen = strlen(username);
        size_t passwordLen = strlen(password);
        if (usernameLen > 0 && username[usernameLen - 1] == '\n') {
            username[usernameLen - 1] = '\0';
        }
        else if (passwordLen > 0 && password[passwordLen - 1] == '\n') {
            password[passwordLen - 1] = '\0';
        }

        account *acc = findAccount(ht, username);
        if (acc && strcmp(acc->Password, password) == 0) {
            printf("Login successful.\n");

            acc->Authenticated = true;
            *currentUser = acc;
            ShowBal(true, &(acc->Balance));
            WithOrDep( &(acc->Authenticated), &(acc->Balance) );
        }
        else if (acc == NULL) {
            printf("No account found with username '%s'\n", username);
        }
        else {
            printf("Incorrect username or password.\n");
        }
    }

    // LOGOUT
    else if (strcmp(command, "logout") == 0) {
        if (*currentUser != NULL) {
            (*currentUser)->Authenticated = false;
            *currentUser = NULL;
            printf("Logged out successfully.\n");
        } 
        else {
            printf("You are not logged in currently.\n");
        }
    }

    /* If user inputs "exit", free all of the memory dynamically allocated on the heap
    then exit the program */
    else if (strcmp(command, "exit") == 0) {
        freeHashTable(ht);
        exit(0);
    }

    else {
        printf("Invalid command.\n");
    }
}

int main() {
    hashTable ht = {0};
    account *currentUser = NULL;

    printf("Welcome to Aedan's bank!\n");
    printf("Commands: newacc, login, logout, exit\n");

    char command[7];
    do {
        printf("\n> "); scanf("%6s", command);
        CommandHandler(&ht, command, &currentUser);
    } while (true);

    return 0;
}
