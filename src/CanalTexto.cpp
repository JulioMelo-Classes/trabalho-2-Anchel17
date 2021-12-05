#include <iostream>
#include <vector>
#include <string>

#include "../include/CanalTexto.h"

using namespace std;

CanalTexto::CanalTexto(unsigned int id, std::string nome, Usuario* dono){
    this -> ch_id = id;
    this -> ch_nome = nome;
    this -> ch_dono = dono;
}

unsigned int CanalTexto::getCh_Id(){
    return this -> ch_id;
}

std::string CanalTexto::getCh_Nome(){
    return this -> ch_nome;
}

Usuario* CanalTexto::getCh_Dono(){
    return this -> ch_dono;
}
