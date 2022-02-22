/*
 * Title: Heaps
 * Author: Cemhan Kaan Özaltan
 * ID: 21902695
 * Section: 3
 * Assignment: 3
 * Description: Printer class interface
 */

#ifndef PRINTER_H
#define PRINTER_H

class Printer {
    public:
        Printer();
        bool isAvailable();
        void setAvailable(bool availability);
        int getRequestEndTime();
        void setRequestEndTime(int endTime);
    
    private:
        bool available; // whether printer is available
        int requestEndTime; // time when current request ends
};

#endif