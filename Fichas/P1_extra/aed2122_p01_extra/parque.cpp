#include "parque.h"
#include <vector>
using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) :lotacao(lot), numMaximoClientes(nMaxCli), vagas(lot) {

}

bool ParqueEstacionamento::adicionaCliente(const string &nome) {

    if (posicaoCliente(nome) == -1 && clientes.size() < numMaximoClientes) {
        InfoCartao person;
        person.nome = nome; person.presente = false;
        clientes.push_back(person);
        vagas++;

        return true;
    }
    return false;
}



bool ParqueEstacionamento::retiraCliente(const string &nome) {
    return false;
}



bool ParqueEstacionamento::entrar(const string &nome) {
    if (posicaoCliente(nome) == -1 || clientes[posicaoCliente(nome)].presente == true || clientes.size() == numMaximoClientes) {

    }
}



bool ParqueEstacionamento::sair(const string &nome) {
    return false;
}



int ParqueEstacionamento::posicaoCliente(const string &nome) const {
    for (unsigned int pos = 0; pos < clientes.size(); pos++) {
        if (clientes[pos].nome == nome) {
            return pos;
        }
    }
    return -1;
}



unsigned ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}



unsigned ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}



unsigned ParqueEstacionamento::getNumLugaresOcupados() const {
    return 0;
}



unsigned ParqueEstacionamento::getNumClientesAtuais() const {
    return 0;
}
