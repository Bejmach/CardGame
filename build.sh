#!/bin/bash
#Auto-generated build script

#Compile all cpp files
g++ -I ./src  -o out.out \
./src/Cards/CardTranslator.cpp \
./src/Cards/Card.cpp \
./src/Cards/CardHolder.cpp \
./src/Cards/Deck.cpp \
./src/Cards/CardTypes.cpp \
./src/Other/Logger.cpp \
./src/Other/StringOperations.cpp \
./src/Clients/ClientBase.cpp \
./src/Clients/ClientPlayer.cpp \
./src/Clients/ClientBot.cpp \
./src/Rules/MakaoValidator.cpp \
./src/Rules/MakaoRules.cpp \
./src/Rules/Validator.cpp \
./src/Rules/SpecialRules.cpp \
./src/Rules/GameMaster.cpp \
./src/main.cpp \

echo "Project succesfully compiled."
echo "Running project"

#run script
if [[ $1 == "-D" ]]
then
	valgrind --leak-check=full -s ./out.out
else
	./out.out
fi
