#include "Doctor.h"

Doctor::Doctor(unsigned int codM, string mS) {

}

Doctor::Doctor(unsigned int codM, string mS, queue<Patient> patients1) {

}

unsigned Doctor::getCode() const {
    return 0;
}

string Doctor::getMedicalSpecialty() const {
    return std::string();
}

queue<Patient> Doctor::getPatients() const {
    return queue<Patient>();
}

void Doctor::addPatient(const Patient &p1) {

}

/*
Patient Doctor::removeNextPatient() {
    return Patient(0, __cxx11::basic_string());
}
 */

void Doctor::moveToFront(unsigned int codP1) {

}
