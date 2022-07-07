#include "postOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}


//--------

// TODO
vector<Mail *> PostOffice::removePostman(string name) {
	vector<Mail *> res;
    for (unsigned int i = 0; i < res.size(); i++) {
        if (res[i] )
    }

	return res;
}

// TODO
vector<Mail *> PostOffice::endOfDay(unsigned int &balance) {
	vector<Mail *> res;
	return res;
}


Postman PostOffice::addMailToPostman(Mail *m, string name) {
	Postman p1;
    return p1;
}

