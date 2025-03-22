#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdio>

class Logger{
    private:
        std::vector<std::string> logs;
        time_t timestamp;
        int randId;

    public:
        Logger();
        void PushLog(std::string log);
        void Save();
};

#endif