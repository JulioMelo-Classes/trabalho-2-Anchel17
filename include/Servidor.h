#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <vector>
#include "../include/Usuario.h"

class Servidor{

    private:

    unsigned int s_id;      //<!ID do servidor

    Usuario* dono;          //<!Referência para o usuário que criou o servidor

    std::string nome;       //<!Nome do servidor

    std::string descricao   //<!Descrição do servidor

    std::string codigoConvide //<!Código de convite para o servidor

    //std::vector<CanalTexto> CanaisTexto; //<!vector contendo os canais de texto do servidor

    std::vector<Usuario*> participantes; //<!vetor contendo referència aos usuários participantes dele

    public:
};

#endif