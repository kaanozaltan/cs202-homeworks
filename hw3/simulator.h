/*
 * Title: Heaps
 * Author: Cemhan Kaan Özaltan
 * ID: 21902695
 * Section: 3
 * Assignment: 3
 * Description: Prototypes of the simulator functions
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <string>
using namespace std;

void simulate(string filename, double avgwaitingtime);
double simulateCase(string filename, const int printerCount, const int requestCount, string& result);

#endif