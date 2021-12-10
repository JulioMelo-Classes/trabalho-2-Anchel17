#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

#include "../include/Sistema.h"
#include "../include/Usuario.h"
#include "../include/Servidor.h"
#include "../include/CanalTexto.h"
#include "../include/Mensagem.h"

/* COMANDOS */
string Sistema::quit(){
  return "Saindo...";
}

//só para verificar algumas coisas, depois apago
void Sistema::teste(){

	for(int i = 0; i < m_usuarios.size(); i++){
		cout<<"Id: "<<m_usuarios[i] -> getId()<<endl;
		cout<<"Nome: "<<m_usuarios[i] -> getNome()<<endl;
		//cout<<"Email: "<<m_usuarios[i] -> getEmail()<<endl;
		//cout<<"Senha: "<<m_usuarios[i] -> getSenha()<<endl;
	}
}

unsigned int Sistema::id_user(){
	if(m_idUsuarioExcluido.empty()){
		m_idUser++;
		return this -> m_idUser;
	}
	
	for(auto itId = m_idUsuarioExcluido.begin(); itId != m_idUsuarioExcluido.end(); itId++){
		int l_id = *itId;
		m_idUsuarioExcluido.erase(itId);
		return l_id;
	}
}

unsigned int Sistema::id_server(){
	m_idServer++;
	return this -> m_idServer;
}

string Sistema::create_user (const string email, const string senha, const string nome){
	if(email == ""){
		return "Por favor, digite um email";
	}

	if(senha == ""){
		return "Por favor, insira uma senha";
	}

	if(nome == ""){
		return "Por favor, digite o nome de usuário";
	}

	for(int i = 0; i < m_usuarios.size(); i++){
		if(email == m_usuarios[i] -> getEmail()){
			return "Usuário já cadastrado";
		}
	}

	Usuario *user = new Usuario(email, senha, nome, id_user());

	m_usuarios.push_back(user);
	teste();
	return "usuário criado";
	
	
}

//delete_user sendo re-trabalhada
std::string Sistema::delete_user (const std::string email, const std::string senha){
	unsigned int l_id;

	for(int i = 0; i < m_usuarios.size(); i++){
		if(m_usuarios[i] -> getEmail() == email){
			l_id = m_usuarios[i] -> getId();
		}

		auto it = m_usuariosLogados.find(l_id);
		
		if(it != m_usuariosLogados.end()){
			return "Por favor, desconecte o usuário para deletá-lo";
		}

		for(auto itServ = m_servidores.begin(); itServ != m_servidores.end(); itServ++){
			//verifica se o usuário a ser deletado é participante de algum servidor
			if(itServ -> verServ_participantes(m_usuarios[i] -> getId())){
				itServ -> eraseServ_participante(m_usuarios[i] -> getId());
				break;
			}
		}
	}

	for(int i = 0; i < m_usuarios.size(); i++){
		if(m_usuarios[i] -> getId() == l_id){
			m_usuarios.erase(m_usuarios.begin() + i);
			teste();
			m_idUsuarioExcluido.push_back(l_id);
			return "Usuário "+ email +" excluído";
		}
	}

	return "Usuário não cadastrado";
}

string Sistema::login(const string email, const string senha){

	for(int i = 0; i < m_usuarios.size(); i++){
		if(email == m_usuarios[i] -> getEmail() && senha == m_usuarios[i] -> getSenha()){
			//verifica se usuário já está logado
			auto l_user = m_usuariosLogados.find(m_usuarios[i] -> getId());
			if(l_user != m_usuariosLogados.end()){
				return "Usuário já logado";
			}

			m_usuariosLogados.insert({m_usuarios[i] -> getId(), {0, 0}});
			//teste();
			return "Logado como " + m_usuarios[i] -> getEmail();
		}
	}

	return "Usuário ou senha incorreto";
}

string Sistema::disconnect(int id){

	auto logado = m_usuariosLogados.find(id);

	if(logado == m_usuariosLogados.end()){
		return "Usuário já não está logado";
	}

	if(!m_usuariosLogados.empty() && id != 0){
		auto it = m_usuariosLogados.find(id);
		m_usuariosLogados.erase(it);
		//teste();
		return "Usuário desconectado";
	}

	return "Usuário não logado!";
}

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
			Servidor server(m_usuarios[i], id_server(), nome);
			m_servidores.push_back(server);
			break;
		}
	}

	return "Servidor criado";
}

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

string Sistema::remove_server(int id, const string nome){
	bool l_ehDono = false;

	auto logado = m_usuariosLogados.find(id);

	if(logado == m_usuariosLogados.end()){
		return "Usuário não está logado";
	}

	for(auto itServ = m_servidores.begin(); itServ != m_servidores.end(); itServ++){
		if(itServ -> getServ_Nome() == nome){
			//verifica se o usuário é dono do servidor
			for(Usuario* user : m_usuarios){
				if(itServ -> getServ_dono() == user){
					l_ehDono = true;
				}
			}

			if(l_ehDono){
				//verifica se existem usuários visualizando o servidor a ser deletado
				for(auto itLog = m_usuariosLogados.begin(); itLog != m_usuariosLogados.end(); itLog++){
					if(itLog -> second.first == itServ -> getServ_Id()){
						itLog -> second.first = 0;
						itLog -> second.second = 0;
					}
				}

				m_servidores.erase(itServ);
				return "Servidor removido com sucesso";
			}
			else{
				return "Você não possui autorização para remover o servidor!";
			}
		}
	}

	return "Servidor não encontrado";
}

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
						//verifica se o usuário já não faz parte do servidor
						if(!it -> verServ_participantes(m_usuarios[i] -> getId())){
							it -> setServ_participantes(m_usuarios[i] -> getId());
						}

						logado -> second.first = it -> getServ_Id();
						//usuário entra visualizando nenhum canal
						logado -> second.second = 0;
						//teste();
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
								//verifica se o usuário já não faz parte do servidor
								if(!it -> verServ_participantes(m_usuarios[i] -> getId())){
									it -> setServ_participantes(m_usuarios[i] -> getId());
								}

								logado -> second.first = it -> getServ_Id();
								//usuário entra visualizando nenhum canal
								logado -> second.second = 0;
								
								//teste();
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
					//teste();
					return "Usuário já está no servidor";
				}

				for(int i = 0; i < m_usuarios.size(); i++){
					//não é a melhor forma, mas ta funcionando
					if(m_usuarios[i] -> getId() == logado -> first){
						//verifica se o usuário já não faz parte do servidor
						if(!it -> verServ_participantes(m_usuarios[i] -> getId())){
							it -> setServ_participantes(m_usuarios[i] -> getId());
						}

						logado -> second.first = it -> getServ_Id();
						//usuário entra visualizando nenhum canal
						logado -> second.second = 0;
			
						//teste();
						return "Entrou no servidor \'" + it -> getServ_Nome() + "\' com sucesso";
					}
				}
			}
		}
	}
	
	return "Servidor não encontrado";
}

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
				logado -> second.first = 0;
				logado -> second.second = 0;
				it -> eraseServ_participante(logado -> first);

				//teste();
				return "Saiu do servidor \'" + it -> getServ_Nome() + "\'";
			}
			else{
				return "Usuário não está no servidor \'" + it -> getServ_Nome() + "\'";
			}
		}
	}

	return "Servidor não encontrado";
}

string Sistema::list_participants(int id){
	string retorno = "";

	auto logado = m_usuariosLogados.find(id);

	if(logado == m_usuariosLogados.end()){
		return "Usuário não está logado";
	}

	for(auto it = m_servidores.begin(); it != m_servidores.end(); it++){
		if(it -> getServ_Id() == logado -> second.first){
			return it -> imprimeServ_participantes(m_usuarios);
		}
	}
	
	return "O usuário não está visualizando nenhum servidor";
}

//list_channels
/*
	Aqui tá com um bug que só aparece quando um usuário está em mais de um servidor e cria
	canais em ambos os servidores
	------CORRIGIDO DEPOIS QUE CORRIGIU A create_channel()-------
*/
string Sistema::list_channels(int id){

	auto logado = m_usuariosLogados.find(id);

	if(logado == m_usuariosLogados.end()){
		return "Usuário não logado";
	}
	
	for(auto itServ = m_servidores.begin(); itServ != m_servidores.end(); itServ++){
		if(itServ -> getServ_Id() == logado -> second.first){
			return itServ -> imprimeServ_canaisTexto();
		}
	}
	
	return "Usuário não está visualizando nenhum servidor";
}

//create_channel 
/*
	Bug que se um usuário possui 2 servidores, ele só cria canais para o primeiro
	servidor dele. -------------CORRIGIDO----------------
*/
string Sistema::create_channel(int id, const string nome){

	auto logado = m_usuariosLogados.find(id);

	if(logado == m_usuariosLogados.end()){
		return "Usuário não logado";
	}


	for(auto verServ = m_servidores.begin(); verServ != m_servidores.end(); verServ++){
		if(verServ -> verServ_canalTexto(nome) && logado -> second.first == verServ -> getServ_Id()){
			return "Já existe uma canal de texto com nome \'"+ nome +"\'";
		}
	}

	for(auto itServ = m_servidores.begin(); itServ != m_servidores.end(); itServ++){
		if(itServ -> getServ_Id() == logado -> second.first){	
			for(int i = 0; i < m_usuarios.size(); i++){
				if(m_usuarios[i] -> getId() == logado -> first){
					CanalTexto canal(itServ -> getServ_canaisTextoSize()+1, nome, m_usuarios[i]);
					itServ -> setServ_canaisTexto(canal);

					return "Canal \'"+ canal.getCh_Nome() + "\' criado";
				}
			}
		}
	}

	return "Usuário não está visualizando nenhum servidor";
}

/*
	ACONTECEU 1 CASO DE SEGMENTATION FAULT, NÃO LEMBRO
	QUAL O CASO QUE ISSO ACONTECEU, FIZ NOVOS TESTES
	E DEU CERTO
*/
string Sistema::remove_channel(int id, const string nome){

	auto logado = m_usuariosLogados.find(id);

	if(logado == m_usuariosLogados.end()){
		return "Usuário não logado";
	}

	for(auto itServ = m_servidores.begin(); itServ != m_servidores.end(); itServ++){
		if(itServ -> getServ_canaisTextoNome(itServ -> getServ_canaisTextoId(nome)) == nome){
			if(itServ -> getServ_dono() -> getId() == id || itServ -> getServ_canaisTextoDono(nome) == id){
				//coloca os usuários logados que estavam vendo o canal no servidor para 0
				for(auto verLogado = m_usuariosLogados.begin(); verLogado != m_usuariosLogados.end(); verLogado++){
					if(verLogado -> second.second == itServ -> getServ_canaisTextoId(nome)){
						verLogado -> second.second = 0;
					}
				}

				itServ -> eraseServ_Canal(itServ -> getServ_canaisTextoId(nome));
				return "Canal \'"+ nome +"\' excluído com sucesso";
			}
			else{
				return "Você não é dono do servidor nem do canal, você não pode excluir este canal!";
			}
		}
	}

	return "remove_channel NÃO IMPLEMENTADO";
}

//enter_channel OK
/*
	COM A CORREÇÃO DA CREATE_CHANNEL, CONSERTOU O BUG DAQUI
*/
string Sistema::enter_channel(int id, const string nome){

	auto logado = m_usuariosLogados.find(id);

	if(logado == m_usuariosLogados.end()){
		return "Usuário não logado";
	}

	for(auto itServ = m_servidores.begin(); itServ != m_servidores.end(); itServ++){
		if(itServ -> verServ_canalTexto(nome)){
			if(logado -> second.first == itServ -> getServ_Id()){
				if(logado -> second.second != itServ -> getServ_canaisTextoId(nome)){
					logado -> second.second = itServ -> getServ_canaisTextoId(nome);
					//teste();
					return "Entrou no canal \'"+ nome + "\'";
				}
				else{
					return "Usuário já está no canal \'"+ nome +"\'"; 
				}
			}
		}
	}

	return "canal \'"+ nome +"\' não existe";
}

string Sistema::leave_channel(int id){

	auto logado = m_usuariosLogados.find(id);

	if(logado == m_usuariosLogados.end()){
		return "Usuário não logado";
	}

	if(logado -> second.first == 0){
		return "Usuário não está em servidor nenhum";
	}

	unsigned int l_idCh;
	if(logado -> second.second != 0){
		for(Usuario* user : m_usuarios){
			if(user -> getId() == id){
				for(Servidor serv : m_servidores){
					if(serv.getServ_Id() == logado -> second.first){
						l_idCh = logado -> second.second;
						logado -> second.second = 0;
						//teste();
						return "Usuário "+ user -> getNome() +" saiu do canal \'" + serv.getServ_canaisTextoNome(l_idCh) + "\'";
					}
				}
			}
		}	
	}

	return "Usuário não está visualizando nenhum canal";
}

string Sistema::send_message(int id, const string mensagem){

	auto logado = m_usuariosLogados.find(id);

	if(logado == m_usuariosLogados.end()){
		return "Usuário não logado";
	}

	if(logado -> second.second == 0){
		return "Usuário não está visualizando nenhum canal";
	}

	for(auto itServ = m_servidores.begin(); itServ != m_servidores.end(); itServ++){
		if(logado -> second.first == itServ -> getServ_Id()){
			itServ -> add_msg(logado -> first, logado -> second.second, mensagem, m_usuarios);

			return "Mensagem enviada ao canal";
		}
	}


	return "Usuário não está visualizando nenhum servidor";
}

string Sistema::list_messages(int id){

	auto logado = m_usuariosLogados.find(id);

	if(logado == m_usuariosLogados.end()){
		return "Usuário não logado";
	}

	if(logado -> second.second == 0){
		return "Usuário não está visualizando nenhum canal";
	}

	for(auto itServ = m_servidores.begin(); itServ != m_servidores.end(); itServ++){
		if(itServ -> getServ_Id() == logado -> second.first){
			if(itServ -> imprime_msg(logado -> second.second, m_usuarios) == ""){
				return "Nenhuma mensagem para visualizar";
			}
			else{
				return itServ -> imprime_msg(logado -> second.second, m_usuarios);
			}
		}
	}

	return "Usuário não está visualizando servidor algum";
}

