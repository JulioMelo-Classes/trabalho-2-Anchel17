#include <iostream>

#include "../include/Servidor.h"

using namespace std;

Servidor::Servidor(int id, std::string nome){
    this -> serv_id = id;
    this -> serv_nome = nome;

    cout<<serv_id<<" "<<serv_nome<<endl;
}

string Servidor::getServ_Nome(){
    return serv_nome;
}

int Servidor::getServ_Id(){
    return serv_id;
}