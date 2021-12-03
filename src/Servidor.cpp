#include <iostream>
#include <map>

#include "../include/Servidor.h"
#include "../include/Usuario.h"

using namespace std;

Servidor::Servidor(Usuario* user, int id, std::string nome){
    this -> serv_dono = user;
    this -> serv_id = id;
    this -> serv_nome = nome;
}

Usuario* Servidor::getServ_dono(){
    return this -> serv_dono;
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

string Servidor::getServ_participantes(vector<Usuario*> user){
    string retorno = "";
    for(auto itPart = serv_participantes.begin(); itPart != serv_participantes.end(); itPart++){
        for(auto itUser = user.begin(); itUser != user.end(); itUser++){
            if(*itPart == *itUser){
                retorno;
            }
        }
    }

    return retorno;
}

void Servidor::setServ_participantes(Usuario *user){
    this -> serv_participantes.push_back(user);
}
