#ifndef CANALTEXTO_H
#define CANALTEXTO_H

#include <vector>

#include "../include/Usuario.h"

class CanalTexto{

    private:

        unsigned int ch_id;     //<!Id do canal

        std::string ch_nome;    //<!Nome do canal

        Usuario* ch_dono;       //<!Referência ao dono do canal

        //vector<Mensagem> ch_mensagens;  //<!Vector de mensagens enviadas no canal

    public:

    /**
     * Construtor da classe CanalTexto
     * @param unsigned int id do canal
     * @param string nome do canal
     * @param Usuario* referência ao dono do canal
     */
    CanalTexto(unsigned int id, std::string nome, Usuario* dono);

    /**
     * Método Get para id do canal
     * @return id do canal
     */
    unsigned int getCh_Id();

    /**
     * Método Get para o nome do canal
     * @return Nome do canal
     */
    std::string getCh_Nome();

    /**
     * Método Get para o dono do canal
     * @return referência ao dono do canal
     */
    Usuario* getCh_Dono();
};

#endif
