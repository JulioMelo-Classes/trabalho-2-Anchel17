#include <string>
#include <ctime>
#include <iostream>

#include "../include/Mensagem.h"
#include "../include/Usuario.h"

using namespace std;

Mensagem::Mensagem(unsigned int id, Usuario* enviadaPor, string msg){
    int mes;
    int ano;

    time_t t;
    struct tm *h;

    time(&t);
    h = localtime(&t);
    mes = (h -> tm_mon) + 1;
    ano = (h -> tm_year) + 1900;

    this -> msg_DataHora = to_string(h -> tm_mday) + "/" + to_string(mes) + "/" + to_string(ano) + " - " + to_string(h -> tm_hour) + ":" + to_string(h -> tm_min);
    this -> msg_id = id;
    this -> msg_enviadaPor = enviadaPor;
    this -> msg_conteudo = msg;
}

unsigned int Mensagem::getMsg_id(){
    return this -> msg_id;
}

string Mensagem::getMsg_DataHora(){
    return this -> msg_DataHora;
}

string Mensagem::getMsg_Conteudo(){
    return this -> msg_conteudo;
}

Usuario* Mensagem::getMsg_EnviadaPor(){
    return this -> msg_enviadaPor;
}

void Mensagem::setMsg_donoAnonimo(){
    this -> msg_enviadaPor -> setUserAnonimo();
}
