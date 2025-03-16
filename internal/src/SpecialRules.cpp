#include "SpecialRules.h"

SpecialRules::SpecialRules(GameModes _mode){
    mode = _mode;
}

SpecialRules::~SpecialRules(){};

void SpecialRules::SetLogger(Logger* _logger){
    logger = _logger;
}