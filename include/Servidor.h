#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <vector>
#include <map>

#include "../include/Usuario.h"
#include "../include/CanalTexto.h"

class Servidor{

    private:

    int serv_id;                //<!ID do servidor dono do servidor

    Usuario* serv_dono;         //<!Referência para o usuário que criou o servidor

    std::string serv_nome;       //<!Nome do servidor

    std::string serv_descricao;   //<!Descrição do servidor

    std::string serv_codigoConvite; //<!Código de convite para o servidor

    std::vector<CanalTexto> CanaisTexto; //<!vector contendo os canais de texto do servidor

    std::vector<unsigned int> serv_participantes; //<!vetor contendo Id dos usuários participantes do servidor

    public:

    /**
     * Construtor da classe Servidor
     * @param Usuario* referência ao usuário que criou o servidor
     * @param int id do servidor
     * @param string nome do servidor
     */
    Servidor(Usuario* user, int id, std::string nome);

    /**
     * Método Get para o dono do servidor
     * @return Referência ao dono do servidor
     */
    Usuario* getServ_dono();

    /**
     * método Getter do nome do servidor
     * @return nome do servidor
     */
    std::string getServ_Nome();

    /**
     * Método Getter do Id do dono do servidor
     * @return Id do dono do servidor
     */
    int getServ_Id();

    /**
     * Método Getter da descrição do servidor
     * @return A descrição do servidor
     */
    std::string getServ_descricao();

    /**
     * Método Setter da descrição do servidor
     * @param string desc, descrição digitada para ser colocada como descrição do servidor
     */
    void setServ_descricao(std::string desc);

    /**
     * Método Getter do código de convite do servidor
     * @return código de convite do servidor
     */
    std::string getServ_codigoConvite();

    /**
     * Método Setter do código de convite do servidor
     * @param string codigo, string contendo o código de convite
     */
    void setServ_codigoConvite(std::string codigo);

    /**
     * Método para remover o usuário do vector de participantes de um servidor
     * @param unsigned int id do usuário que sai do servidor
     */
    void eraseServ_participante(unsigned int id);

    /**
     * Método para verificar se um usuário já não faz parte do servidor
     * @param unsigned int id do usuário a ser verificado
     */
    bool verServ_participantes(unsigned int id);

    /**
     * Método Get para pegar os usuários participantes de um servidor
     * @param vector vector contendo referências ao usuários cadastrados no sistema
     * @return string contendo o Id de participantes do servidor
     */
    std::string getServ_participantes(std::vector<Usuario*> &user);
    
    /**
     * Método Seter de participantes
     * @param int id dos usuários para ser guardada no vector
     */
    void setServ_participantes(unsigned int id);
};

#endif
