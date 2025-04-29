#include "Logger.h"
#include <chrono>

Logger::Logger(){

    time(&timestamp);
    randId = rand();
}

void Logger::PushLog(std::string log){
    logs.push_back(log);
    std::ofstream backupFile("./logs/.log_"+std::to_string(timestamp)+std::to_string(randId)+".txt", std::fstream::app);

    backupFile<<log<<"\n";

    backupFile.close();
}

void Logger::Save(){
    std::ofstream file("./logs/log_"+std::to_string(timestamp)+std::to_string(randId)+".txt");

    std::string backupName = "./logs/.log_"+std::to_string(timestamp)+std::to_string(randId)+".txt";

    std::remove(backupName.c_str());

    for(int i=0; i<logs.size(); i++){
        file<<logs[i]<<"\n";
    }
    file.close();
}
