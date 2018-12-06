#include <iostream>
#include <fstream>
#include <signal.h>

using namespace std;

int main()
{
  int pid_var;
  char signal;

  // READ PID AND USE IT TO TRIGGER SIGNALS FOR THE PROCESS
  ifstream infile;
  
  infile.open("pid");
  infile >> pid_var;

  cout << pid_var << endl;
  cout << "Please enter l, c, or s for Lever Down, Cancel and Stop respectively" << endl;

  while(1)
  {
    cout << ">> ";
    cin >> signal;
    
    switch(signal)
    {
      case 'l': // LEVER DOWN
        kill(pid_var, SIGUSR1);
        break;
      case 'c': // CANCEL
        kill(pid_var, SIGUSR2);
        break;
      case 's': //STOP
        kill(pid_var, SIGKILL);
        break;
      default: // WRONG INPUT
        cout << "Wrong input given";
        break;
    }

  }
 
  return 0;
}
