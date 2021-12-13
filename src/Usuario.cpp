#include <iostream>

#include "../include/Usuario.h"

using namespace std;

Usuario::Usuario(std::string email, std::string senha, std::string nome, unsigned int id){
    this -> m_email = email;
    this -> m_senha = senha;
    this -> m_nome = nome;
    this -> m_id = id;
}

string Usuario::getNome(){
    return m_nome;
}

string Usuario::getEmail(){
    return m_email;
}

string Usuario::getSenha(){
    return m_senha;
}

unsigned int Usuario::getId(){
    return m_id;
}

void Usuario::setUserAnonimo(){
    this -> m_nome = "<usuário anônimo>";
    this -> m_id = 0;
}
