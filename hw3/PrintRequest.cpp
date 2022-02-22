/*
 * Title: Heaps
 * Author: Cemhan Kaan Özaltan
 * ID: 21902695
 * Section: 3
 * Assignment: 3
 * Description: PrintRequest class implementation
 */

#include "PrintRequest.h"
using namespace std;

/*
 * default constructor for PrintRequest
 */
PrintRequest::PrintRequest() {
    id = priority = requestTime = processTime = arrivalOrder = -1; // all properties have initial invalid values
}

/*
 * constructor for PrintRequest
 * @param id request id
 * @param priority request priority
 * @param requestTime request sending time
 * @param processTime request process time
 * @param arrivalOrder request arrival order
 */
PrintRequest::PrintRequest(int id, int priority, int requestTime, int processTime, int arrivalOrder) {
    this->id = id;
    this->priority = priority;
    this->requestTime = requestTime;
    this->processTime = processTime;
    this->arrivalOrder = arrivalOrder;
}

/*
 * gets id
 * @return id
 */
int PrintRequest::getId() {
    return id;
}

/*
 * gets priority
 * @return priority
 */
int PrintRequest::getPriority() {
    return priority;
}

/*
 * gets request time
 * @return request time
 */
int PrintRequest::getRequestTime() {
    return requestTime;
}

/*
 * gets process time
 * @return process time
 */
int PrintRequest::getProcessTime() {
    return processTime;
}

/*
 * gets arrival order
 * @return arrival order
 */
int PrintRequest::getArrivalOrder() {
    return arrivalOrder;
}