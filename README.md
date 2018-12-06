# toaster
------------------------------------------------------------------------------------------------
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

----- README -----

app_toaster_cpp_v2.0

-----------------------------------------------------------------------
Note: This application has been created and tested on Ubuntu 18.04 LTS
-----------------------------------------------------------------------
-------------------------
Compilation Instructions:
--------------------------
- gcc app_toaster.cpp -o app_toaster -lstdc++ -pthread
- gcc trigger.cpp -o trigger -lstdc++ -pthread

---------------------
Running Instructions:
---------------------
- ./app_toaster
- ./trigger
- Running trigger, press 'l' for lever down, 'c' for cancel, 's' to stop
