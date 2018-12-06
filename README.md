# toaster
-------------
toaster_v3.0:
-------------
This version of the code uses threads for different modules (timer, reader, controller, writer) and uses queues in order to communicate between the threads

---------------------------------------------------------------
NOTE: This code has been written and tested on Ubuntu 18.04 LTS
---------------------------------------------------------------

-----------
How to Run?
-----------
1. Open first terminal and run python app_toaster.py
2. Open second terminal
3. Run:
       python trigger.py l - signals lever down
       python trigger.py c - signals cancel button pressed
       python trigger.py s - stops the toster
