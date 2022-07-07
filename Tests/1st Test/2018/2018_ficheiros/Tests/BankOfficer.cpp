/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"

unsigned int BankOfficer::idAux = 1;

BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------

// a alterar
BankOfficer::BankOfficer(string name) {
    setName(name);
    id = idAux;
    idAux++;
}

bool BankOfficer::operator>(const BankOfficer &b1) {
    if (myAccounts.size() > b1.getAccounts().size()) return true;
    else if (myAccounts.size() < b1.getAccounts().size()) return false;
    return (name > b1.getName());
}

void BankOfficer::AddAccount(vector<Account *> accounts) {

}



