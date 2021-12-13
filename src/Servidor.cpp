#include <iostream>
#include <map>

#include "../include/Servidor.h"
#include "../include/Usuario.h"
#include "../include/Sistema.h"
#include "../include/Mensagem.h"

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

string Servidor::imprimeServ_participantes(vector<Usuario*> &user){
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

int Servidor::getServ_canaisTextoId(string nome){
    for(CanalTexto canal : CanaisTexto){
        if(canal.getCh_Nome() == nome){
            return canal.getCh_Id();
        }
    }
    return 0;
}

string Servidor::getServ_canaisTextoNome(unsigned int id){
    for(CanalTexto canal : CanaisTexto){
        if(canal.getCh_Id() == id){
            return canal.getCh_Nome();
        }
    }
    return "";
}

int Servidor::getServ_canaisTextoSize(){
    return this -> CanaisTexto.size();
}

bool Servidor::verServ_canalTexto(string nome){
    for(CanalTexto canal : CanaisTexto){
        if(canal.getCh_Nome() == nome){
            return true;
        }
    }
    return false;
}

string Servidor::imprimeServ_canaisTexto(){
    string retorno = "#Canais de texto\n";
    
    for(CanalTexto canal : CanaisTexto){
        retorno += canal.getCh_Nome() + "\n";
    }

    return retorno;
}

void Servidor::setServ_canaisTexto(CanalTexto canaisTexto){
    this -> CanaisTexto.push_back(canaisTexto);
}

unsigned int Servidor::getServ_canaisTextoDono(string nome){
    for(CanalTexto canal : CanaisTexto){
        if(canal.getCh_Nome() == nome){
            return canal.getCh_Dono() -> getId();
        }
    }
    return 0;
}

void Servidor::eraseServ_Canal(int id){
    for(auto itCh = CanaisTexto.begin(); itCh != CanaisTexto.end(); itCh++){
        if(itCh -> getCh_Id() == id){
            CanaisTexto.erase(itCh);
            break;
        }
    }
}

void Servidor::add_msg(unsigned int userId, unsigned int chId, string mensagem, vector<Usuario*> &user){
    for(int i = 0; i < user.size(); i++){
        if(user[i] -> getId() == userId){
            for(auto itCh = CanaisTexto.begin(); itCh != CanaisTexto.end(); itCh++){
                if(itCh -> getCh_Id() == chId){
                    Mensagem msg(chId, user[i], mensagem);

                    itCh -> setCh_msg(msg);
                }
            }
        }
    }
}

std::string Servidor::imprime_msg(unsigned int chId, vector<Usuario*> &user){
    for(CanalTexto canal : CanaisTexto){
        if(canal.getCh_Id() == chId){
            return canal.getCh_msg(user);
        }
    }

    return "";
}

void Servidor::verServ_chMsgs(Usuario* &user){
    bool l_achou = false;

    for(CanalTexto canal : CanaisTexto){
        l_achou = canal.verCh_msgDono(user);
        
        if(l_achou){
            break;
        }
    }
}

void Servidor::verServ_chDono(Usuario* &user){    
    for(CanalTexto canal : CanaisTexto){
        if(canal.getCh_Dono() == user){
            canal.setCH_donoAnonimo();

            //talvez não precisa desse break?
            break;
        }
    }
}

void Servidor::setServ_donoAnonimo(vector<Usuario*> usuarios, Usuario* &user){
    for(Usuario* usr : usuarios){
        if(usr == user){
            this -> serv_dono -> setUserAnonimo();
            break;
        }
    }
}
