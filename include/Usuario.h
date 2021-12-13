#ifndef USUARIO_H
#define USUARIO_H

/**
 *  Implementação da classe usuário para o Concordo 
 */
class Usuario{

    private:

        unsigned int m_id;      //<!id do usuário
    
        std::string m_nome;     //<!nome do usuário
    
        std::string m_email;    //<!email do usuário

        std::string m_senha;    //<!senha do usuário

    public:

        /**
         * Construtor da classe Usuario
         * @param email String contendo o email do usuário
         * @param senha String contendo a senha do usuário
         * @param nome String contendo o nome do usuário
         * @param id Inteiro sem sinal contendo o Id do usuário 
         */
        Usuario(std::string email, std::string senha, std::string nome, unsigned int id);

        /**
         * Método Getter do nome do usuário
         * @return nome do usuário
         */
        std::string getNome();

        /**
         * Método Getter do email do usuário
         * @return email do usuário
         */
        std::string getEmail();

        /**
         * Método Getter da senha do usuário
         * @return senha do usuário
         */
        std::string getSenha();

        /**
         * Método Getter do ID do usuário
         * @return id do usuário
         */
        unsigned int getId();

        /**
         * Método para tornar o usuário anônimo
         */
        void setUserAnonimo();
};

#endif
