#include "PlayerPerson.h"

PlayerPerson::PlayerPerson(GameLoop* _loop){
	loop = _loop;
}

void PlayerPerson::SetLoop(GameLoop *_loop){
	loop = _loop;
}

void PlayerPerson::OnTurn(){
	std::cout<<"Player on turn event"<<std::endl;
	std::cout<<"Current hand"<<std::endl;
	PrintHand();
	AwaitCommand();
}

void PlayerPerson::PrintCard(int id){
	if(id>=onHand.size() || id<0){
		return;
	}
	Card* card = onHand[id];
	std::string suit = translate::suit::EN(card->GetSuit());
	std::string name = translate::name::EN(card->GetName());

	std::cout<<name<<" of "<<suit<<std::endl;
}
void PlayerPerson::PrintHand(){
	for(int i=0; i<onHand.size(); i++){
		PrintCard(i);
	}
}

void PlayerPerson::SendCommand(std::string command){
	std::vector<std::string> formatedCommand = SO::Split(command, " ");

	if(formatedCommand.size()<=0){
		return;
	}
	if(formatedCommand[0] == "play"){
		if(formatedCommand.size()<=1 || formatedCommand[1] != std::to_string(std::stoi(formatedCommand[1])) || std::stoi(formatedCommand[1])<0 || std::stoi(formatedCommand[1])>=onHand.size()){
			return;
		}
		PlayCard(std::stoi(formatedCommand[1]));
		loop->NextTurn();
		
	}
	else if(formatedCommand[0] == "draw"){
		DrawCard();
		loop->NextTurn();
	}
}
void PlayerPerson::AwaitCommand(){
	std::cout<<"Command: ";
	std::string command;
	getline(std::cin, command);
	SendCommand(command);
}
