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
	}
	if(m_usuariosLogados.empty()){
		cout<<"Não existem usuários logados"<<endl;
	}
	else{
		for(auto it = m_usuariosLogados.begin(); it != m_usuariosLogados.end(); it++){
			cout<<"ID: "<<it -> first<<" Servidor|canal: "<< it -> second.first<<"|"<< it -> second.second<<endl;
		}
	}*/
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

		//precisa dar uma polida, só não deleta se o USUÁRIO RECÉM LOGADO TENTAR DELETAR A SI MESMO
		for(int i = 0; i < m_usuarios.size(); i++){
			if(m_usuarios[i] -> getEmail() == email){
				l_id = m_usuarios[i] -> getId();
			}

			auto it = m_usuariosLogados.find(l_id);
			
			if(it == m_usuariosLogados.end()){
				return "Por favor, desconecte o usuário para deletá-lo";
			}
		}

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

		return "Usuário não cadastrado";
	}
}

//login OK
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

//disconnect OK
string Sistema::disconnect(int id) {
	//parece que tá funcionando
	if(!m_usuariosLogados.empty() && id != 0){
		auto it = m_usuariosLogados.find(id);
		m_usuariosLogados.erase(it);
		teste();
		return "Usuário desconectado";
	}

	return "Usuário não logado!";
}

//create_server OK
string Sistema::create_server(int id, const string nome) {
	//verificar se o id corresponde a um usuário logado
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
	
	Servidor server(id, nome);

	m_servidores.push_back(server);

	for(int i = 0; i < m_servidores.size(); i++){
		cout<<"ID dono: "<<m_servidores[i].getServ_Id()<<endl;
		cout<<"Nome do server: "<<m_servidores[i].getServ_Nome()<<endl;
		cout<<"------------------------------------"<<endl;
	}

	return "Servidor criado";
}

//set_server_desc OK
string Sistema::set_server_desc(int id, const string nome, const string descricao) {

	for(int i = 0; i < m_servidores.size(); i++){
		if(m_servidores[i].getServ_Id() != id && m_servidores[i].getServ_Nome() == nome){
			return "Você não pode mudar a descrição de um servidor que não foi criado por você!";
		}

		if(m_servidores[i].getServ_Id() == id && m_servidores[i].getServ_Nome() == nome){
			m_servidores[i].setServ_descricao(descricao);

			return "Descrição do servidor \'" + m_servidores[i].getServ_Nome() + "\' Alterada";
		}
	}

	return "Servidor não encontrado";
}

//set_server_invite_code OK
string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
	
	for(int i = 0; i < m_servidores.size(); i++){
		if(m_servidores[i].getServ_Id() != id && m_servidores[i].getServ_Nome() == nome){
			return "Você não possui autorização para mudar o código de convite de um servidor que não foi criado por você!";
		}

		if(m_servidores[i].getServ_Id() == id && m_servidores[i].getServ_Nome() == nome){
			m_servidores[i].setServ_codigoConvite(codigo);

			if(codigo == ""){
				return "Código de convite do servidor \'" + m_servidores[i].getServ_Nome() + "\' removido";
			}
			
			return "Código de convite do servidor \'" + m_servidores[i].getServ_Nome() + "\' alterado para: " + codigo;
		}
	}
	
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

