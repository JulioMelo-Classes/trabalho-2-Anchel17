#include <string>

#include "../include/Mensagem.h"

using namespace std;

Mensagem::Mensagem(unsigned int id, Usuario* enviadaPor);

unsigned int Mensagem::getMsg_id(){
    return this -> msg_id;
}

std::string Mensagem::getMsg_DataHora(){
    return this -> msg_DataHora;
}

    /*
        AQUI VAI OS MÉTODOS SETTERS DE DATAHORA E CONTEÚDO
    */
std::string Mensagem::getMsg_Conteudo(){
    return this -> msg_conteúdo;
}

Usuario* Mensagem::getMsg_EnviadaPor(){
    return this -> msg_enviadaPor;
}
