#ifndef MENSAGEM_H
#define MENSAGEM_H

#include "Usuario.h"

class Mensagem{

    private:

    unsigned int msg_id;    //<!Id da mensagem

    std::string msg_DataHora;   //<!String que vai conter a data e hora de uma mensagem enviada

    std::string msg_conteúdo;   //<!Mensagem escrita

    Usuario* msg_enviadaPor;    //<!Referência ao usuário que enviou a mensagem

    public:

    /**
     * Construtor da classe mensagem
     * @param unsigned int id da mensagem
     * @param Usuario* referência ao usuário que enviou a mensagem
     */
    Mensagem(unsigned int id, Usuario* enviadaPor);

    /**
     * Método para pegar o Id da mensagem
     * @return id da mensagem
     */
    unsigned int getMsg_id();

    /**
     * Método para pegar a data e hora de envio da mensagem
     * @return string contendo a data e hora de envio da mensagem
     */
    std::string getMsg_DataHora();

    /*
        AQUI VAI OS MÉTODOS SETTERS DE DATAHORA E CONTEÚDO
    */

    /**
     * Método para pegar a mensagem
     * @return string contendo a mensagem
     */
    std::string getMsg_Conteudo();

    /**
     * Método para retornar quem enviou a mensagem
     * @return Usuario que enviou a mensagem
     */
    Usuario* getMsg_EnviadaPor();
};

#endif
