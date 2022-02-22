/*
 * Title: Heaps
 * Author: Cemhan Kaan Özaltan
 * ID: 21902695
 * Section: 3
 * Assignment: 3
 * Description: Printer class implementation
 */

#include "Printer.h"
using namespace std;

/*
 * default constructor for Printer
 */
Printer::Printer() {
    // printer initially available and has invalid request end time
    available = true;
    requestEndTime = -1;
}

/*
 * tells whether printer is available
 * @return whether printer is available
 */
bool Printer::isAvailable() {
    return available;
}

/*
 * sets printer availability
 * @param availability availability to set
 */
void Printer::setAvailable(bool availability) {
    available = availability;
}

/*
 * gets request end time
 * @return request end time
 */
int Printer::getRequestEndTime() {
    return requestEndTime;
}

/*
 * sets request end time
 * @param endTime request end time to set
 */
void Printer::setRequestEndTime(int endTime) {
    requestEndTime = endTime;
}