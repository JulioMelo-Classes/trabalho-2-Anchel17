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

//corrigir o bug pro caso do usuário possuir mais de 1 servidor
string Servidor::getServ_participantes(map<int, std::pair<unsigned int, unsigned int>> usuariosLogados,int id){
    string retorno = "";

    for(auto itLog = usuariosLogados.begin(); itLog != usuariosLogados.end(); itLog++){
        if(itLog -> second.first == id){
            for(int i = 0; i < serv_participantes.size(); i++){
                if(serv_participantes[i] -> getId() == itLog -> first){
                    retorno += serv_participantes[i] -> getNome() + "\n";
                }
            }
        }
    }

    return retorno;
}

void Servidor::setServ_participantes(Usuario *user){
    this -> serv_participantes.push_back(user);
}