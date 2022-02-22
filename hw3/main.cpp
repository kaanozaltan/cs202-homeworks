/*
 * Title: Heaps
 * Author: Cemhan Kaan Özaltan
 * ID: 21902695
 * Section: 3
 * Assignment: 3
 * Description: Driver file for the simulation
 */

#include <string>
#include <sstream>
#include "simulator.h"
using namespace std;

int main(int argc, const char** argv) { // pass execution arguments to main
    string filename = argv[1]; // assign filename to first argument
    string avgTime = argv[2]; // assign avgTime to second argument

    // convert avgTime to double
    double avgwaitingtime;
    istringstream(avgTime) >> avgwaitingtime;

    simulate(filename, avgwaitingtime); // simulate given inputs

    return 0;
}