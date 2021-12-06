#include <iostream>
#include <map>

#include "../include/Servidor.h"
#include "../include/Usuario.h"
#include "../include/Sistema.h"

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

void Servidor::eraseServ_participante(unsigned int id){
    for(auto it = serv_participantes.begin(); it != serv_participantes.end(); it++){
        if(*it == id){
            serv_participantes.erase(it);
            break;
        }
    } 
}

bool Servidor::verServ_participantes(unsigned int id){
    for(auto itPart = serv_participantes.begin(); itPart != serv_participantes.end(); itPart++){
        if(id == *itPart){
            return true;
        }
    }

    return false;
}

string Servidor::getServ_participantes(vector<Usuario*> &user){
    string retorno = "";

    for(unsigned int i : serv_participantes){
        for(Usuario* u : user){
            if(u -> getId() == i){
                retorno += u -> getNome() + "\n";
            }
        }
    }

    return retorno;
}

void Servidor::setServ_participantes(unsigned int id){
    this -> serv_participantes.push_back(id);
}

int Servidor::getServ_canaisTextoSize(){
    return this -> CanaisTexto.size();
}

string Servidor::getServ_canaisTexto(){
    string retorno = "#Canais de texto\n";

    cout<<CanaisTexto.size()<<endl;
    
    for(CanalTexto canal : CanaisTexto){
        retorno += canal.getCh_Nome() + "\n";
    }

    return retorno;
}

void Servidor::setServ_canaisTexto(CanalTexto canaisTexto){
    this -> CanaisTexto.push_back(canaisTexto);
    cout<<CanaisTexto.size()<<endl;
}
