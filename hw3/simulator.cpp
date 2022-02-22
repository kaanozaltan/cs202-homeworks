/*
 * Title: Heaps
 * Author: Cemhan Kaan Özaltan
 * ID: 21902695
 * Section: 3
 * Assignment: 3
 * Description: Implementations of the simulator functions
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include "simulator.h"
#include "MaxHeap.h"
#include "Printer.h"
using namespace std;

/*
 * simulates the printer system with increasing printer numbers to determine the mininum amount 
 * of printers required to obtain the desired average wait time
 * @param filename name of input file
 * @param avgwaitingtime desired average waiting time
 */
void simulate(string filename, double avgwaitingtime) {
    string result; // result string to return with pass by reference 
    double avgTime = avgwaitingtime + 1; // start avgTime higher than avgwaitingtime to get in the loop
    int printerCount = 1; // start with 1 printer
    
    // get request count from the file and convert it to int
    ifstream file(filename.c_str());
    string line;
    getline(file, line);
    int requestCount;
    istringstream(line) >> requestCount;

    while (true) {
        avgTime = simulateCase(filename, printerCount, requestCount, result); // simulate case

        // exit loop if simulation case gives low enough avg waiting time, increment printer count if else
        if (avgTime <= avgwaitingtime)
            break;
        else
            printerCount++;
    }

    // display the output of the result case
    cout << "Minimum number of printers required: " << printerCount << endl << endl;
    cout << "Simulation with " << printerCount << " printers:\n\n";
    cout << result << endl;
    cout << "Average waiting time: " << avgTime << " minutes\n";
}

/*
 * simulates a case with a specific number of printers
 * @param filename name of input file
 * @param printerCount printer count to simulate with
 * @param requestCount number of requests
 * @param result simulation output string returned with pass by reference
 * @return average waiting time in this case
 */
double simulateCase(string filename, const int printerCount, const int requestCount, string& result) {
    result = ""; // reset return string
    MaxHeap priorityQueue; // priority queue to keep track of current requests
    ifstream file(filename.c_str()); // file to read requests from
    int time = 0; // initial time is 0 minutes
    double totalWait = 0; // sum of all waiting times

    // traverse the first line of file since it is the request count
    string line;
    getline(file, line);

    PrintRequest requests[requestCount]; // array to keep requests
    int requestInfo[4]; // array for request instantiataion which holds its properties

    // for every request, extract its info from input file, instantiate it and add it to requests
    for (int i = 0; i < requestCount; i++) {
        getline(file, line);
        istringstream iss(line);

        for(int j = 0; j < 4; j++) {
            iss >> requestInfo[j];
        }

        // instantiate request with given info, arrival order is equal to iteration variable
        PrintRequest request(requestInfo[0], requestInfo[1], requestInfo[2], requestInfo[3], i);

        requests[i] = request; // add request to requests
    }

    Printer printers[printerCount]; // array of printers, printer id is the index
    int currentRequest = 0; // start with first request in requests

    // repeat the following process while all requests in requests are not taken and
    // priorityQueue not empty
    while ((currentRequest < requestCount) || (!priorityQueue.heapIsEmpty())) {
        // for every printer in printers, if it is not available and the end time of
        // the request processed by it is reached, free the printer
        for (int i = 0; i < printerCount; i++) {
            if (!printers[i].isAvailable() && printers[i].getRequestEndTime() <= time) {
                printers[i].setAvailable(true);
                printers[i].setRequestEndTime(-1);
            }
        }

        int increment = 0;

        // for every request in requests, add it to priorityQueue if
        // time has reached its request time and update currentRequest after
        for (int i = currentRequest; i < requestCount; i++) {
            if (requests[i].getRequestTime() <= time) {
                priorityQueue.heapInsert(requests[i]);
                increment++;
            }
        }
        
        currentRequest += increment;

        // for every printer, if the printer is available and there is a request in priorityQueue, delete
        // a request from priorityQueue and set the printer's availability and process time accordingly
        // since iteration starts from 0, printer with lowest id will be used in the case of multiple free
        // printers
        for (int i = 0; i < printerCount; i++) {
            if (printers[i].isAvailable() && !priorityQueue.heapIsEmpty()) {
                PrintRequest p;
                priorityQueue.heapDelete(p);
                printers[i].setAvailable(false);
                printers[i].setRequestEndTime(time + p.getProcessTime());

                // convert printer id to string
                stringstream ss1;
                ss1 << i;
                string printerId = ss1.str();

                // convert request id to string
                stringstream ss2;
                ss2 << p.getId();
                string requestId = ss2.str();

                // convert current time to string
                stringstream ss3;
                ss3 << time;
                string timeS = ss3.str();

                // convert waiting time to string
                stringstream ss4;
                ss4 << time - p.getRequestTime();
                string wait = ss4.str();

                result += "Printer " + printerId + " prints print request " + requestId + " at minute " + timeS + " (wait: " + wait + " mins)\n"; // update result string

                totalWait += (time - p.getRequestTime()); // add the waiting time of this request to total waiting time
            }
        }

        time++; // move on to the next minute
    }

    return (totalWait / requestCount); // return avg waiting time
}