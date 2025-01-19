#include "PlayerPerson.h"

PlayerPerson::PlayerPerson(GameLoop* _loop){
	loop = _loop;
}

void PlayerPerson::SetLoop(GameLoop *_loop){
	loop = _loop;
}

void PlayerPerson::OnTurn(){
	std::cout<<"Player on turn event"<<std::endl;

	if(skipTurn){
		std::cout<<"Turn skipped"<<std::endl;
		turnsSkipped-=1;
		if(turnsSkipped<=0){
			skipTurn = false;
		}
		loop->NextTurn();
	}

	std::cout<<"Last used"<<std::endl;
	deck->PrintUsed(deck->UsedSize()-1);

	std::cout<<"Current hand"<<std::endl;
	PrintHand();
	AwaitCommand();
}
bool PlayerPerson::SendCommand(std::string command){
	std::vector<std::string> formatedCommand = SO::Split(command, " ");

	if(formatedCommand.size()<=0){
		return false;
	}
	if(formatedCommand[0] == "play"){
		if(formatedCommand.size()<=1 || formatedCommand[1] != std::to_string(std::stoi(formatedCommand[1]))){
			std::cout<<"wrong command"<<std::endl;
			return false;
		}
		Card* card = GetCard(std::stoi(formatedCommand[1])-1);
		std::string flags = "";

		if(formatedCommand.size()>2){
			flags = formatedCommand[2];
		}

		if(card==nullptr){
			std::cout<<"card out of range"<<std::endl;
			return false;
		}
		if(!loop->ValidateMove(card, flags)){
			std::cout<<"wrong move"<<std::endl;
			return false;
		}

		PlayCard(std::stoi(formatedCommand[1])-1);
		return true;
		
	}
	else if(formatedCommand[0] == "draw"){
		DrawCard();
		return true;
	}
	return false;
}
void PlayerPerson::AwaitCommand(){
	std::cout<<"Command: ";
	std::string command;
	getline(std::cin, command);
	bool correctCommand = SendCommand(command);
	while(!correctCommand){
		std::cout<<"Provided incorrect command, try again"<<std::endl;
		std::cout<<"Command: ";
		std::string command;
		getline(std::cin, command);
		correctCommand = SendCommand(command);
	}
	loop->NextTurn();
}
