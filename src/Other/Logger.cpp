#include "Logger.h"

Logger::Logger(){
    time(&timestamp);
}

void Logger::PushLog(std::string log){
    logs.push_back(log);
    std::ofstream backupFile(".logs_"+std::to_string(timestamp)+".txt", std::fstream::app);

    backupFile<<log<<"\n";

    backupFile.close();
}

void Logger::Save(){
    std::ofstream file("logs_"+std::to_string(timestamp)+".txt");

    std::string backupName = ".logs_"+std::to_string(timestamp)+".txt";

    std::remove(backupName.c_str());

    for(int i=0; i<logs.size(); i++){
        file<<logs[i]<<"\n";
    }
    file.close();
}