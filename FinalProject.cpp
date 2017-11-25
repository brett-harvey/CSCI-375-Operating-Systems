/******************************************************************************

Title: CSCI 375 - Final Project

Author: Brett Harvey

Date: November 24th, 2017

*******************************************************************************/

#include <iostream>
using namespace std;

/**** SuperClass: Scheduling Algorithms ****/
class SchedulingAlgorithms {
  uint jobID;
  int arrivalTime, completionTime, processingTime, waitingTime,
      findTurnAroundTime;

  /**** Class: First Come First Serve *****/
  class FirstComeFirstServe : SchedulingAlgorithms {
    int main() {
      // process id's
      int processes[] = {1, 2, 3};
      uint size = sizeof processes / sizeof processes[0];

      // Burst time of all processes
      int burst_time[] = {10, 5, 8};

      findavgTime(processes, n, burst_time);
      return 0;
    }

    /**************
      Function: FirstComeFirstServe()
      Params: int _processes[], int size, int bt[], int wt[]
      Purpose: To get the waiting time for a set of given processes.
    **************/
    void GetWaitingTime(int _processes[], int __size, int bt[], int wt[]) {
      // waiting time for first process is 0
      wt[0] = 0;

      // calculating waiting time
      for (int i = 1; i < size; i++) wt[i] = bt[i - 1] + wt[i - 1];
    }

    /**************
      Function: GetTurnaroundTime()
      Params: int _processes[], int size, int bt[], int wt[], int tat[]
      Purpose: To get the turnaround time for a set of processes.
    **************/
    void GetTurnaroundTime(int __processes[], int__size, int bt[], int wt[],
                           int tat[]) {
      // calculating turnaround time by adding
      // bt[i] + wt[i]
      for (int i = 0; i < n; i++) tat[i] = bt[i] + wt[i];
    }

    /**************
      Function: FindTheAverageTime()
      Params: int _processes[], int size, int bt[], int wt[]
      Purpose: To get the turnaround time for a set of processes.
    **************/
    void findavgTime(int __processes[], int __size, int bt[]) {
      int wt[n], tat[n], total_wt = 0, total_tat = 0;

      // Function to find waiting time of all processes
      findWaitingTime(processes, n, bt, wt);

      // Function to find turn around time for all processes
      findTurnAroundTime(processes, n, bt, wt, tat);

      // Display processes along with all details
      cout << " Job ID  " 
           << " State    "
           << " Counter   "
           << " Number of Bursts "
           << " CPU Bursts "
           << " Current CPU Burst "
           << " Time of completion of the current I/O operation \n"; 

      // Calculate total waiting time and total turn
      // around time
      for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << "   " << i + 1 << "\t\t" << bt[i] << "\t    " << wt[i]
             << "\t\t  " << tat[i] << endl;
      }

      cout << "Average waiting time = " << (float)total_wt / (float)n;
      cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
    }
  }

  /**** Class: Shorest-Job-First  *****/
  class ShorestJobFirst : SchedulingAlgorithms {
    int main() { 
        return 0; 
        
    }
    
    
  }
  
  
  /**** Class: Round Robin  *****/
  class RoundRobin : SchedulingAlgorithms {
    int main() { 
        return 0; 
        
    }
  }
}
