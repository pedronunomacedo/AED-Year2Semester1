#ifndef MY_RESOLUTION_DOCTOR_H
#define MY_RESOLUTION_DOCTOR_H

#include <iostream>
#include <string>
#include <queue>
#include "Patient.h"
using namespace std;

class Doctor {
    unsigned codeM;
    string medicalSpecialty;
    queue<Patient> patients;
public:
    Doctor(unsigned codM, string mS);
    Doctor(unsigned codM, string mS, queue<Patient> patients1);
    unsigned getCode() const;
    string getMedicalSpecialty() const;
    queue<Patient> getPatients() const;
    void addPatient(const Patient &p1);
    //Patient removeNextPatient();

    void moveToFront(unsigned codP1);

    class PatientInexistent {};

};


#endif //MY_RESOLUTION_DOCTOR_H
