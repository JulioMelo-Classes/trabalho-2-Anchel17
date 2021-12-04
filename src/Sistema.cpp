#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

#include "../include/Sistema.h"
#include "../include/Usuario.h"
#include "../include/Servidor.h"

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

//só para verificar algumas coisas, depois apago
void Sistema::teste(){
/*
	for(int i = 0; i < m_usuarios.size(); i++){
		cout<<"Id: "<<m_usuarios[i] -> getId()<<endl;
		cout<<"Nome: "<<m_usuarios[i] -> getNome()<<endl;
		cout<<"Email: "<<m_usuarios[i] -> getEmail()<<endl;
		cout<<"Senha: "<<m_usuarios[i] -> getSenha()<<endl;
	}*/
	if(m_usuariosLogados.empty()){
		cout<<"Não existem usuários logados"<<endl;
	}
	else{
		for(auto it = m_usuariosLogados.begin(); it != m_usuariosLogados.end(); it++){
			cout<<"ID: "<<it -> first<<" Servidor|canal: "<< it -> second.first<<"|"<< it -> second.second<<endl;
		}
	}//*/
}

//create_user OK
string Sistema::create_user (const string email, const string senha, const string nome){
	Usuario *user = new Usuario(email, senha, nome, m_usuarios.size()+1);

	if(email == ""){
		return "Por favor, digite um email";
	}

	if(senha == ""){
		return "Por favor, insira uma senha";
	}

	if(nome == ""){
		return "Por favor, digite o nome de usuário";
	}

	if(m_usuarios.empty()){

		m_usuarios.push_back(user);
		return "Usuário criado";
	}
	else{
		for(int i = 0; i < m_usuarios.size(); i++){
			if(email == m_usuarios[i] -> getEmail()){
				return "Usuário já cadastrado";
			}
		}

		m_usuarios.push_back(user);
		return "usuário criado";
	}
	
}

//delete_user OK
std::string Sistema::delete_user (const std::string email, const std::string senha){
	unsigned int l_id;

	if(m_usuarios.empty()){
		return "Não existem usuários cadastrados";
	}
	else{
		for(int i = 0; i < m_usuarios.size(); i++){
			if(m_usuarios[i] -> getEmail() == email){
				l_id = m_usuarios[i] -> getId();
			}

			auto it = m_usuariosLogados.find(l_id);
			
			if(it != m_usuariosLogados.end()){
				return "Por favor, desconecte o usuário para deletá-lo";
			}
		}

		for(int i = 0; i < m_usuarios.size(); i++){
			if(email == m_usuarios[i] -> getEmail()){
				m_usuarios.erase(m_usuarios.begin() + i);
				
				//isso aqui vai re-setar os Id de usuários após o usuário deletado
				for(int j = 0; j < m_usuarios.size(); j++){
					m_usuarios[j] -> re_setId(j+1);

					//update no ID de usuários logados
					m_usuariosLogados[j].first = m_usuarios[j] -> getId();
				}

				return "Usuário deletado";
			}

			teste();
		}

		return "Usuário não cadastrado";
	}
}

//login OK
string Sistema::login(const string email, const string senha){

	for(int i = 0; i < m_usuarios.size(); i++){
		if(email == m_usuarios[i] -> getEmail() && senha == m_usuarios[i] -> getSenha()){
			//verifica se usuário já está logado
			auto l_user = m_usuariosLogados.find(m_usuarios[i] -> getId());
			if(l_user != m_usuariosLogados.end()){
				return "Usuário já logado";
			}

			m_usuariosLogados.insert({m_usuarios[i] -> getId(), {0, 0}});
			teste();
			return "Logado como " + m_usuarios[i] -> getEmail();
		}
	}

	return "Usuário ou senha incorreto";
}

//disconnect OK
string Sistema::disconnect(int id){

	if(!m_usuariosLogados.empty() && id != 0){
		auto it = m_usuariosLogados.find(id);
		m_usuariosLogados.erase(it);
		teste();
		return "Usuário desconectado";
	}

	return "Usuário não logado!";
}

//create_server OK
string Sistema::create_server(int id, const string nome){

	if(m_usuariosLogados.empty()){
		return "Nenhum usuário logado, por favor logue em uma conta.";
	}
	else{
		auto l_user = m_usuariosLogados.find(id);

		if(l_user == m_usuariosLogados.end()){
			return "Usuário não logado!";
		}

		for(auto it = m_servidores.begin(); it != m_servidores.end(); it++){
			if(it -> getServ_Nome() == nome){
				return "Já existe um servidor com esse nome";
			}
		}
	}
	
	
	//para achar o id do usuário que criou o servidor
	for(int i = 0; i < m_usuarios.size(); i++){
		if(m_usuarios[i] -> getId() == id){
			Servidor server(m_usuarios[i], m_servidores.size()+1, nome);
			m_servidores.push_back(server);
			break;
		}
	}

	return "Servidor criado";
}

//set_server_desc sendo re-trabalhado...
string Sistema::set_server_desc(int id, const string nome, const string descricao){

	auto it = m_usuariosLogados.find(id);

	if(it == m_usuariosLogados.end()){
		return "Usuário não está logado";
	}

	for(auto itServer = m_servidores.begin(); itServer != m_servidores.end(); itServer++){
		if(itServer -> getServ_Nome() == nome){
			if(itServer -> getServ_dono() -> getId() == id){
				itServer -> setServ_descricao(descricao);
				return "Descrição do servidor \'" + nome + "\' alterada";
			}
			else{
				return "Você não possui autorização para alterar a descrição desta servidor!";
			}
		}
	}

	return "Servidor não encontrado";
}

//set_server_invite_code OK
string Sistema::set_server_invite_code(int id, const string nome, const string codigo){

	auto l_user = m_usuariosLogados.find(id);
	
	//verifica se o usuário está logado
	if(l_user == m_usuariosLogados.end()){
		return "Usuário não logado!";
	}
	
	for(auto it = m_servidores.begin(); it != m_servidores.end(); it++){
		if(it -> getServ_Nome() == nome){
			if(it -> getServ_dono() -> getId() == id){
				it -> setServ_codigoConvite(codigo);
				if(codigo != ""){
					return "Código de convite do servidor \'"+ it -> getServ_Nome() +"\'modificado com sucesso";
				}
				else{
					return "Código de convite do servidor \'"+ it -> getServ_Nome() +"\' removido";
				}
			}
			else{
				return "Você não tem autorização para modificar o código de convite deste servidor!";
			}
		}
	}
	
	return "Servidor não encontrado";
}

//lista servers OK
string Sistema::list_servers(int id){
	string l_retorno = "";

	auto l_user = m_usuariosLogados.find(id);
	//só para verificar se o usuário está logado
	if(l_user == m_usuariosLogados.end()){
		return "Usuário não está logado";
	}

	for(auto it = m_servidores.begin(); it != m_servidores.end(); it++){
		l_retorno += it -> getServ_Nome() + "\n";
	}

	return l_retorno;
}

//remove-server OK
string Sistema::remove_server(int id, const string nome){

	auto l_user = m_usuariosLogados.find(id);
	//só para verificar se o usuário está logado
	if(l_user == m_usuariosLogados.end()){
		return "Usuário não está logado";
	}

	for(auto it = m_servidores.begin(); it != m_servidores.end(); it++){
		if(it -> getServ_Nome() == nome){
			if(it -> getServ_dono() -> getId() == id){
				auto itLog = m_usuariosLogados.find(id);
				if(itLog != m_usuariosLogados.end()){
					itLog -> second.first = 0;
					itLog -> second.second = 0;
				}

				m_servidores.erase(it);
				teste();
				return "Servidor removido com sucesso";
			}
			else{
				return "Você não tem autorização para remover o servidor!";
			}
		}
	}
	
	return "Servidor não encontrado";
}

//enter_server OK
string Sistema::enter_server(int id, const string nome, const string codigo){	
	auto logado = m_usuariosLogados.find(id);

	if(logado == m_usuariosLogados.end()){
		return "Usuário não está logado";
	}

	for(auto it = m_servidores.begin(); it != m_servidores.end(); it++){
		if(it -> getServ_Nome() == nome){
			if(it -> getServ_dono() -> getId() == id){
				if(logado -> second.first == it -> getServ_Id()){
					return "Usuário já está no servidor";
				}
				for(int i = 0; i < m_usuarios.size(); i++){
					//não é a melhor forma, mas ta funcionando
					if(m_usuarios[i] -> getId() == id){
						//Usuario *user = new Usuario(m_usuarios[i] -> getEmail(), m_usuarios[i] -> getSenha(), m_usuarios[i] -> getNome(), m_usuarios[i] -> getId());

						it -> setServ_participantes(m_usuarios[i] -> getId());
						logado -> second.first = it -> getServ_Id();
						teste();
						return "Entrou no servidor \'" + it -> getServ_Nome() + "\' com sucesso";
					}
				}
			}
			
			if(it -> getServ_codigoConvite() != ""){
				if(codigo != ""){
					if(codigo == it -> getServ_codigoConvite()){
						if(logado -> second.first == it -> getServ_Id()){
							return "Usuário já está no servidor";
						}

						for(int i = 0; i < m_usuarios.size(); i++){
							//não é a melhor forma, mas ta funcionando
							if(m_usuarios[i] -> getId() == logado -> first){
								//Usuario *user = new Usuario(m_usuarios[i] -> getEmail(), m_usuarios[i] -> getSenha(), m_usuarios[i] -> getNome(), m_usuarios[i] -> getId());

								it -> setServ_participantes(m_usuarios[i] -> getId());

								logado -> second.first = it -> getServ_Id();
								teste();
								return "Entrou no servidor \'" + it -> getServ_Nome() + "\' com sucesso";
							}
						}
					}
					else{
						return "Código de convite inválido";
					}
				}
				else{
					return "É necessário um código de convite para entrar no servidor";
				}
			}
			//se o servidor não precisa de código de convite
			else{
				if(logado -> second.first == it -> getServ_Id()){
					teste();
					return "Usuário já está no servidor";
				}

				for(int i = 0; i < m_usuarios.size(); i++){
					//não é a melhor forma, mas ta funcionando
					if(m_usuarios[i] -> getId() == logado -> first){
						//Usuario *user = new Usuario(m_usuarios[i] -> getEmail(), m_usuarios[i] -> getSenha(), m_usuarios[i] -> getNome(), m_usuarios[i] -> getId());

						it -> setServ_participantes(m_usuarios[i] -> getId());

						logado -> second.first = it -> getServ_Id();
						teste();
						return "Entrou no servidor \'" + it -> getServ_Nome() + "\' com sucesso";
					}
				}
			}
		}
	}
	
	return "Servidor não encontrado";
}

//leave_server OK
string Sistema::leave_server(int id, const string nome){

	auto logado = m_usuariosLogados.find(id);

	if(logado == m_usuariosLogados.end()){
		return "Usuário não está logado";
	}

	for(auto it = m_servidores.begin(); it != m_servidores.end(); it++){
		if(logado -> second.first == 0){
			return "Você não está em servidor algum";
		}

		if(it -> getServ_Nome() == nome){
			if(it -> getServ_Id() == logado -> second.first){
				//apaga o id de usuário participante do servidor 
				it -> eraseServ_participante(logado -> first);

				logado -> second.first = 0;
				logado -> second.second = 0;
				teste();
				return "Saiu do servidor \'" + it -> getServ_Nome() + "\'";
			}
			else{
				return "Usuário não está no servidor \'" + it -> getServ_Nome() + "\'";
			}
		}
	}

	return "Servidor não encontrado";
}

//list_participants OK
string Sistema::list_participants(int id){
	string retorno = "";

	auto logado = m_usuariosLogados.find(id);

	if(logado == m_usuariosLogados.end()){
		return "Usuário não está logado";
	}

	for(auto it = m_servidores.begin(); it != m_servidores.end(); it++){
		if(it -> getServ_Id() == logado -> second.first){
			return it -> getServ_participantes(m_usuarios);
		}
	}

	return "O usuário não está visualizando nenhum servidor";
}

string Sistema::list_channels(int id) {
	return "list_channels NÃO IMPLEMENTADO";
}

string Sistema::create_channel(int id, const string nome) {
	return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::remove_channel(int id, const string nome) {
	return "remove_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(int id, const string nome) {
	return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel(int id) {
	return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(int id, const string mensagem) {
	return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
	return "list_messages NÃO IMPLEMENTADO";
}

