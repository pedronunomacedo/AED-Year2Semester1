/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

// a alterar
double Bank::getWithdraw(string cod1) const{
    double totalBalance = 0;
    for (auto &c : accounts) {
        if (c->getCodH() == cod1) {
            totalBalance += c->getWithdraw();
        }
    }
	return totalBalance;
}


// a alterar
vector<Account *> Bank::removeBankOfficer(string name){
	vector<Account *> myAccounts;
    vector<BankOfficer>::const_iterator it;
    for (it = bankOfficers.begin(); it != bankOfficers.end(); it++) {
        if (it->getName() == name) {
            myAccounts = (*it).getAccounts();
            bankOfficers.erase(it);
            break;
        }
    }
	return myAccounts;
}


// a alterar
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    vector<BankOfficer>::iterator it;
    for (it = bankOfficers.begin(); it != bankOfficers.end(); it++) {
        if ((*it).getName() == name) {
            (*it).addAccount(ac);
            return (*it);
        }
    }
    throw NoBankOfficerException(name);
}

bool compareAccounts(Account *a1, Account *a2) {
    if (a1->getBalance() < a2->getBalance()) return true;
    else if (a2->getBalance() < a1->getBalance()) return false;
    return (a1->getCodIBAN() < a2->getCodIBAN());
}

// a alterar
void Bank::sortAccounts() {
    sort(accounts.begin(), accounts.end(), compareAccounts);
}

