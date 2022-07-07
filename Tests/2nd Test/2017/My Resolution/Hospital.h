#ifndef MY_RESOLUTION_HOSPITAL_H
#define MY_RESOLUTION_HOSPITAL_H

#include <iostream>
#include <list>
#include <stack>
#include "Doctor.h"
using namespace std;

class Hospital {
    list<Doctor> doctors;
    list< stack<Patient> > letterTray;
    unsigned trayCapacity;
public:
    Hospital(unsigned trayC = 20);

};


#endif //MY_RESOLUTION_HOSPITAL_H
