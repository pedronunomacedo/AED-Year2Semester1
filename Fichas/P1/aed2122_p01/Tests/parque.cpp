#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) :lotacao(lot), numMaximoClientes(nMaxCli), vagas(lot) {
}



int ParqueEstacionamento::posicaoCliente(const string & nome) const {
    for (unsigned int pos = 0; pos < clientes.size(); pos++) {
        if (clientes[pos].nome == nome) {
            return pos;
        }
    }
    return -1;
}


bool ParqueEstacionamento::adicionaCliente(const string & nome) {
    if (posicaoCliente(nome) == -1 && clientes.size() < numMaximoClientes) {
        InfoCartao person;
        person.nome = nome; person.presente = false;
        clientes.push_back(person);
        return true;
    }
    return false;
}
 

bool ParqueEstacionamento::retiraCliente(const string & nome) {
    for (unsigned int i = 0; i < clientes.size(); i++) {
        if (clientes[i].nome == nome && clientes[i].presente == false) {
            clientes.erase(clientes.begin() + i);
            return true;
        }
    }
    return false;
}
  

unsigned ParqueEstacionamento::getNumLugares() const {
	return lotacao;
}


unsigned ParqueEstacionamento::getNumLugaresOcupados() const {
	return lotacao-vagas;
}

unsigned ParqueEstacionamento::getNumMaximoClientes() const {
	return numMaximoClientes;
}

unsigned ParqueEstacionamento::getNumClientesAtuais() const {
	return clientes.size();
}

bool ParqueEstacionamento::entrar(const string & nome) {
    bool registed = false, present = false;
    int index;

    for (unsigned int i = 0; i < clientes.size(); i++) {
        if (clientes[i].nome == nome && clientes[i].presente == true) {
            present = true;
            registed  = true;
        }
        else if (clientes[i].nome == nome) {
            index = i;
            registed = true;
            present = false;
        }
    }

    if (registed == false || present == true || vagas  == 0) {
        return false;
    }
    vagas--;
    clientes[index].presente = true;
    return true;
}


bool ParqueEstacionamento::sair(const string & nome) {
    bool registed = false, present = false;
    int index;

    for (unsigned int i = 0; i < clientes.size(); i++) {
        if (clientes[i].nome == nome && clientes[i].presente == true) {
            present = true;
            registed  = true;
            index = i;
        }
        else if (clientes[i].nome == nome) {
            registed = true;
            present = false;
        }
    }

    if (!registed || !present) {
        return false;
    }
    vagas++;
    clientes[index].presente = false;
    return true;
}
		


