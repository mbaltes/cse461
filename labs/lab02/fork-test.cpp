#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main()
{
 // Creating variables: 
 // pid is a datatype for representing a process ID.
 // status is an integer pointer.
 pid_t pid;
 int* status;

 // We now fork the pid process, creating a copy of itself.
 pid = fork();

  // If pid > 0 we are in the parent process.
  if (pid > 0)
   {
      // We print that we are waiting, create a new pid_t variable set to the
      // child processes pid, wait() suspends execution of this parent process
      // until the child process terminates, then we print the child process ID.
      cout << "Parent :child executing" <<endl;
      pid_t cpid=wait(status);
      cout << " Parent : child process" << cpid << " finished" << endl;
    }
   // If pid == 0 we are in the child process that was just created.
   if (pid == 0)
    {
       for (int i=0; i<10000; i++) // We loop for a while to pass some time.
       {
         
       }
       // After the time wasting loop we print and exit.
       cout << "Child :child exiting" << endl; 
       exit(0);

     }
   // We get here in the fork() failed, and we print that it failed.
   if (pid <= 0)
     {
        cout << "fork failed" << endl;
      }
 return 0; //return success
}

