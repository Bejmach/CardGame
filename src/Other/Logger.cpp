#include "Logger.h"

void Logger::PushLog(std::string log){
    logs.push_back(log);
}

void Logger::Save(){
    time_t timestamp;
    time(&timestamp);

    std::ofstream file("logs_"+std::to_string(timestamp)+".txt");

    for(int i=0; i<logs.size(); i++){
        file<<logs[i]<<"\n";
    }
    file.close();
}