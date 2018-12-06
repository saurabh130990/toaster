// PREPROCESSOR DIRECTIVES
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <queue>
#include <string>
#include <csignal>
#include <fstream>

using namespace std;

//SIGNAL HANDLER QUEUE
// GLOBAL QUEUE DECLARED BECOZ OF A LIMITATION OF SIG HANDLER
queue <int> sig_hand_q;


// TIMER MODULE
void timer(queue<int>& timer_q)
{
  time_t start_time = time(0);
  while(1)
  {
    sleep(1);
    time_t stop_time = time(0);
    timer_q.push(int(stop_time - start_time));
  }
}


// SIGNAL HANDLER MODULE
void sig_hand(int signum)
{
  int lever_status;
  if (signum == 10) // SIGUSR1 SIGNAL / LEVER DOWN
  {
    lever_status = 1;
  }
  if (signum == 12) // SIGUSR2 SIGNAL / CANCEL
  {
    lever_status = 2;
  }
  sig_hand_q.push(lever_status);
}


// READER MODULE
void reader(queue<int>& sig_hand_q, queue<int>& reader_q)
{
  int mesh_status = 2; // MESH OFF by DEFAULT
  while(1)
  {
    while(!sig_hand_q.empty())
    {
      mesh_status = sig_hand_q.front(); // READ SIGNAL STATUS
      sig_hand_q.pop();
      reader_q.push(mesh_status);
    }
  }
}


// CONTROLLER MODULE
void controller(queue<int>& reader_q, queue<int>& timer_q, queue<string>& controller_m_q, queue<int>& controller_t_q)
{ 
  int i = 0;
  string mesh = "OFF";
  int c_status = 2;

  while(1)
  { // UPDATE c_status if any signal has occured
    while(!reader_q.empty())
    { 
      c_status = reader_q.front();
      reader_q.pop();
    }
    // READ TIMER QUEUE AND UPDATE CONTROLLER QUEUE
    while(!timer_q.empty())
    {
      if(c_status == 1)
      {
        mesh = "ON";
        i = i + 1;
        if(i == 11)
        {
          mesh = "OFF";
          i = 0;
          c_status = 2;
        }
      }
      if(c_status == 2)
      {
        mesh = "OFF";
        i = 0;
      }
      controller_m_q.push(mesh);
      controller_t_q.push(timer_q.front());
      timer_q.pop();    
    }
  }
}


// WRITER MODULE
void writer(queue<string>& controller_m_q, queue<int>& controller_t_q)
{ 
  int timer_status;
  while(1)
  { // LOGIC FOR READING QUEUES AND WRITING OUTPUT ON CLI
    while(!controller_t_q.empty() && !controller_m_q.empty())
    {
      string writer_status = controller_m_q.front();
      controller_m_q.pop();
      timer_status = controller_t_q.front();
      controller_t_q.pop();
      cout << timer_status << " " << writer_status << endl;
    }
  }
}


// MAIN FUNCTION
int main()
{
  // WRITE THE PID TO A FILE, USED BY TRIGGER
  int pid_var = getpid();
  ofstream pid_f;
  pid_f.open("pid");
  pid_f << pid_var << endl;
  pid_f.close();
   
  // SIGNALS
  signal(SIGUSR1, sig_hand); // LEVER SIGNAL
  signal(SIGUSR2, sig_hand); // CANCEL SIGNAL

  //QUEUES
  queue <int> timer_q;
  queue <int> reader_q;
  queue <int> controller_t_q;
  queue <string> controller_m_q;

  // THREADS
  thread timer_t(timer, ref(timer_q));
  thread reader_t(reader, ref(sig_hand_q), ref(reader_q));
  thread controller_t(controller, ref(reader_q), ref(timer_q), ref(controller_m_q), ref(controller_t_q));
  thread writer_t(writer, ref(controller_m_q), ref(controller_t_q));
  
  while(1)
  {
    //KEEP THE PROGRAM RUNNING CONTINUOUSLY
  }
  
return 0;
 
}
