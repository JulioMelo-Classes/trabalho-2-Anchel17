#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

#include "../include/Sistema.h"
#include "../include/Usuario.h"

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

//só para verificar algumas coisas, depois apago
void Sistema::teste(){

	for(int i = 0; i < m_usuarios.size(); i++){
		cout<<"Id: "<<m_usuarios[i] -> getId()<<endl;
		cout<<"Nome: "<<m_usuarios[i] -> getNome()<<endl;
		cout<<"Email: "<<m_usuarios[i] -> getEmail()<<endl;
		cout<<"Senha: "<<m_usuarios[i] -> getSenha()<<endl;
	}
	for(auto it = m_usuariosLogados.begin(); it != m_usuariosLogados.end(); it++){
		cout<<"ID: "<<it -> first<<" Servidor|canal: "<< it -> second.first<<"|"<< it -> second.second<<endl;
	}
}

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

std::string Sistema::delete_user (const std::string email, const std::string senha){
	if(m_usuarios.empty()){
		return "Não existem usuários cadastrados";
	}
	else{
		for(int i = 0; i < m_usuarios.size(); i++){
			if(email == m_usuarios[i] -> getEmail()){
				m_usuarios.erase(m_usuarios.begin() + i);
				
				//isso aqui vai re-setar os Id de usuários após o usuário deletado
				for(int j = 0; j < m_usuarios.size(); j++){
					m_usuarios[j] -> re_setId(j+1);
				}
			}

			teste();
			return "Usuário deletado";
		}

	}

	return "Usuário não cadastrado";
}

string Sistema::login(const string email, const string senha){

	for(int i = 0; i < m_usuarios.size(); i++){
		if(email == m_usuarios[i] -> getEmail() && senha == m_usuarios[i] -> getSenha()){
			m_usuariosLogados.insert({m_usuarios[i] -> getId(), {0, 0}});
			teste();
			return "Logado como " + m_usuarios[i] -> getEmail();
		}
	}

	return "Usuário ou senha incorreto";
}

string Sistema::disconnect(int id) {
	return "disconnect NÃO IMPLEMENTADO";
}

string Sistema::create_server(int id, const string nome) {
	return "create_server NÃO IMPLEMENTADO";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
	return "set_server_desc NÃO IMPLEMENTADO";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
	return "set_server_invite_code NÃO IMPLEMENTADO";
}

string Sistema::list_servers(int id) {
	return "list_servers NÃO IMPLEMENTADO";
}

string Sistema::remove_server(int id, const string nome) {
	return "remove_server NÃO IMPLEMENTADO";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
	return "enter_server NÃO IMPLEMENTADO";
}

string Sistema::leave_server(int id, const string nome) {
	return "leave_server NÃO IMPLEMENTADO";
}

string Sistema::list_participants(int id) {
	return "list_participants NÃO IMPLEMENTADO";
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

