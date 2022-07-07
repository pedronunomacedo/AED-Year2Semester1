/*
 * BankOfficer.h
 */

#ifndef SRC_BANKOFFICER_H_
#define SRC_BANKOFFICER_H_

#include "Account.h"
#include <string>
#include <vector>

class BankOfficer {
    static unsigned int idAux;
	unsigned int id;
	string name;
	vector<Account *> myAccounts;
public:
	BankOfficer();
	void setName(string nm);
	void addAccount(Account *a);
    void AddAccount(vector<Account *> accounts);
    string getName() const;
	vector<Account *> getAccounts() const;
	unsigned int getID() const;

    BankOfficer(string name);
    vector<Account *> removeBankOfficer(string name);
    bool operator> (const BankOfficer &b1);
};

#endif /* SRC_BANKOFFICER_H_ */
