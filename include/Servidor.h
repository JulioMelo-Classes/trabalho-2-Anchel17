#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <vector>
#include "../include/Usuario.h"

class Servidor{

    private:

    int serv_id;                //<!ID do servidor dono do servidor

    Usuario* serv_dono;         //<!Referência para o usuário que criou o servidor

    std::string serv_nome;       //<!Nome do servidor

    std::string serv_descricao;   //<!Descrição do servidor

    std::string serv_codigoConvite; //<!Código de convite para o servidor

    //std::vector<CanalTexto> CanaisTexto; //<!vector contendo os canais de texto do servidor

    std::vector<Usuario*> serv_participantes; //<!vetor contendo referència aos usuários participantes dele

    public:

    Servidor(int id, std::string nome);

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
};

#endif