import os
import sys
import signal

# READING THE PID (GIVEN BY app_toaster.py)
f = open('pid', 'r')
pid = int(f.read())
f.close()

print pid

# READ COMMAND LINE ARGUEMENT
input = sys.argv[1]

# USE THE COOMAND LINE ARGUEMENT TO TRIGGER A SPECIFIC FUNCTION
if input == 'l':
    # LEVER DOWN / START TRIGGER
    os.kill(pid, signal.SIGUSR1)
if input == 'c':
    # CANCEL BUTTON TRIGGER
    os.kill(pid, signal.SIGUSR2)
if input == 's':
    # STOP SIGNALTRIGGER
    os.kill(pid, signal.SIGKILL)
