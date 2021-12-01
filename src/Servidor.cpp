#include <iostream>

#include "../include/Servidor.h"
#include "../include/Usuario.h"

using namespace std;

Servidor::Servidor(int id, std::string nome){
    this -> serv_id = id;
    this -> serv_nome = nome;
}

string Servidor::getServ_Nome(){
    return serv_nome;
}

int Servidor::getServ_Id(){
    return serv_id;
}

string Servidor::getServ_descricao(){
    return serv_descricao;
}

void Servidor::setServ_descricao(string desc){
    this -> serv_descricao = desc;
}

string Servidor::getServ_codigoConvite(){
    return this -> serv_codigoConvite;
}

void Servidor::setServ_codigoConvite(string codigo){
    this -> serv_codigoConvite = codigo;
}

vector<Usuario*> Servidor::getServ_participantes(){
    return this -> serv_participantes;
}

void Servidor::setServ_participantes(Usuario *user){
    this -> serv_participantes.push_back(user);
}