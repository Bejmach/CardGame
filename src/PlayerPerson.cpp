#include "PlayerPerson.h"

PlayerPerson::PlayerPerson(PlayerClient* _client){
	client = _client;
}
void PlayerPerson::SetClient(PlayerClient *_client){
	client = _client;
}

void PlayerPerson::PrintCard(int id){
	if(id>=client->GetCards().size() || id<0){
		return;
	}
	Card* card = client->GetCards()[id];
	std::string suit = translate::suit::EN(card->GetSuit());
	std::string name = translate::name::EN(card->GetName());

	std::cout<<name<<" of "<<suit<<std::endl;
}
void PlayerPerson::PrintHand(){
	for(int i=0; i<client->GetCards().size(); i++){
		PrintCard(i);
	}
}

void PlayerPerson::DrawCard(){
	client->DrawCard();
}
void PlayerPerson::PlayCard(int id){
	client->PlayCard(id);
}

void PlayerPerson::SendCommand(std::string command){
	std::vector<std::string> formatedCommand = SO::Split(command, " ");

	if(formatedCommand.size()<=0){
		return;
	}
	if(formatedCommand[0] == "play"){
		if(formatedCommand.size()<=1 || formatedCommand[1] != std::to_string(std::stoi(formatedCommand[1])) || std::stoi(formatedCommand[1])<0 || std::stoi(formatedCommand[1])>=client->GetCards().size()){
			return;
		}
		PlayCard(std::stoi(formatedCommand[1]));
	}
	else if(formatedCommand[0] == "draw"){
		DrawCard();
	}
	// || id!=std::stoi(std::to_string(id))
}
void PlayerPerson::AwaitCommand(){
	std::string command;
	getline(std::cin, command);
	SendCommand(command);
}
