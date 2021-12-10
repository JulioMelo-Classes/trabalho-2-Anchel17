#include <iostream>
#include <vector>
#include <string>

#include "../include/CanalTexto.h"

using namespace std;

CanalTexto::CanalTexto(int id, std::string nome, Usuario* dono){
    this -> ch_id = id;
    this -> ch_nome = nome;
    this -> ch_dono = dono;
}

unsigned int CanalTexto::getCh_Id(){
    return this -> ch_id;
}

string CanalTexto::getCh_Nome(){
    return this -> ch_nome;
}

Usuario* CanalTexto::getCh_Dono(){
    return this -> ch_dono;
}

void CanalTexto::setCh_msg(Mensagem msg){
    this -> ch_mensagens.push_back(msg);
}

string CanalTexto::getCh_msg(vector<Usuario*> &user){
    string retorno = "";

    for(auto itMsg = ch_mensagens.begin(); itMsg != ch_mensagens.end(); itMsg++){
        for(Usuario* u : user){
            if(u -> getNome() == itMsg -> getMsg_EnviadaPor() -> getNome()){
                retorno += u -> getNome() + "<" + itMsg -> getMsg_DataHora() + ">: "+   itMsg -> getMsg_Conteudo() + "\n";
            }
        }
    }

    return retorno;
}
