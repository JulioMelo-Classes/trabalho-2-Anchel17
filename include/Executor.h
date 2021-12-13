#ifndef CANALTEXTO_H
#define CANALTEXTO_H

#include <vector>

#include "../include/Usuario.h"
#include "../include/Mensagem.h"

class CanalTexto{

    private:

        unsigned int ch_id;     //<!Id do canal

        std::string ch_nome;    //<!Nome do canal

        Usuario* ch_dono;       //<!Referência ao dono do canal

        std::vector<Mensagem> ch_mensagens;  //<!Vector de mensagens enviadas no canal

    public:

    /**
     * Construtor da classe CanalTexto
     * @param int id do canal
     * @param string nome do canal
     * @param Usuario* referência ao dono do canal
     */
    CanalTexto(int id, std::string nome, Usuario* dono);

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

    /**
     * Método para guardar uma mensagem
     * @param Mensagem contendo as informações da mensagem
     */
    void setCh_msg(Mensagem msg);

    /**
     * Método para retornar as mensagens de um canal
     * @param Usuario* Referência só para procurar o dono da mensagem
     * @return string contendo mensagens enviadas de um canal
     */
    std::string getCh_msg(std::vector<Usuario*> &user);
    
    /**
     * Método para verificar se um usuário é dono de alguma mensagem em canais
     * @param Usuario* referência a um usuário
     * @return true caso o usuário seja dono de alguma mensagem, false caso contrário
     */
    bool verCh_msgDono(Usuario* &user);

    /**
     * Método para tornar o usuário dono do canal a ser deletado anônimo
     */
    void setCH_donoAnonimo();
};

#endif
