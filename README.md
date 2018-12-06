# toaster
----------------------------------------------------------
Toasters in general are equipped with

- lever (on when pushed down, off when it pops back up)

- cancel button

- assuming power always on, constant heating duration (10 seconds, say) and heating strength

 
Threads (feel free to add more to suit your needs):

- reader (collecting inputs - lever position, cancel button state),

- writer (generating outputs - mesh on/off),

- controller (state machine),

- timer (generating internal time ticks)

 
Signals:

Use existing signals or define your own: Start, Stop, Cancel.

 
Inputs:

- lever position (down: heating on, up: heating off)

- cancel button (heating cancelled when pressed)


Output:

- mesh (on, off)


Print messages showing the mesh state (on/off) for each tick:

1         Mesh: off

2         Mesh: off

3         Mesh: off

4         Mesh: on

5         Mesh: on

6         …

7         Mesh: on

8         Mesh: off

9         Mesh: off

10       …

State transition example:

        Lever: down

 

        Mesh: off                               Mesh: On

                        HeatingOn()

                        Delay(10 seconds)

             -------------------------------------->

                                                ^

                                                |

                                                |  10 seconds

                                                v

            <--------------------------------------

        Lever: up
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
- python trigger.py l - signals lever down
- python trigger.py c - signals cancel button pressed
- python trigger.py s - stops the toster
