#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

class Logger{
    private:
        std::vector<std::string> logs;

    public:
        void PushLog(std::string log);

        void Save();
};

#endif