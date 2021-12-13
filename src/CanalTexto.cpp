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
        retorno += itMsg -> getMsg_EnviadaPor() -> getNome() + "<" + itMsg -> getMsg_DataHora() + ">: "+   itMsg -> getMsg_Conteudo() + "\n";
    }

    return retorno;
}

bool CanalTexto::verCh_msgDono(Usuario* &user){
    int l_contAchou = 0;

    for(Mensagem msg : ch_mensagens){
        if(msg.getMsg_EnviadaPor() == user){
            l_contAchou++;

            msg.setMsg_donoAnonimo();
            return true;
        }
    }
    
    if(l_contAchou > 0){
        return true;
    }

    return false;
}

void CanalTexto::setCH_donoAnonimo(){
    this -> ch_dono -> setUserAnonimo();
}
