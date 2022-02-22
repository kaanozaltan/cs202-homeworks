/*
 * Title: Heaps
 * Author: Cemhan Kaan Özaltan
 * ID: 21902695
 * Section: 3
 * Assignment: 3
 * Description: PrintRequest class interface
 */

#ifndef PRINTREQUEST_H
#define PRINTREQUEST_H
using namespace std;

class PrintRequest {
    public:
        PrintRequest();
        PrintRequest(int id, int priority, int requestTime, int processTime, int arrivalOrder);
        
        int getId();
        int getPriority();
        int getRequestTime();
        int getProcessTime();
        int getArrivalOrder();
    
    private:
        int id; // request id
        int priority; // priority value
        int requestTime; // time at which request is sent
        int processTime; // time it takes to process request
        int arrivalOrder; // order of request in input file
};

#endif