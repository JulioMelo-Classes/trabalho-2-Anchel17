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
         * Método Getter do nome do usuário
         * @return nome do usuário
         */
        std::string getNome(){
            return m_nome;
        }

        /**
         * Método Setter do nome do usuário
         * @param nome string recebida para ser o nome do usuário
         */
        void setNome(std::string nome){
            this -> m_nome = nome;
        }

        /**
         * Método Getter do email do usuário
         * @return email do usuário
         */
        std::string getEmail(){
            return m_email;
        }

        /**
         * Método Setter do email do usuário
         * @param email String recebida para ser o nome do email do usuário
         */
        void setEmail(std::string email){
            this -> m_email = email;
        }

        /**
         * Método Getter da senha do usuário
         * @return senha do usuário
         */
        std::string getSenha(){
            return m_senha;
        }

        /**
         * Método Getter da senha do usuário
         * @param senha String recebida para ser a senha do usuário
         */
        void setSenha(std::string senha){
            this -> m_senha = senha;
        }
};

#endif