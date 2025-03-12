#ifndef REQUESTTRANSLATORTEST_H
#define REQUESTTRANSLATORTEST_H

#include <vector>
#include "../Cards/Card.h"
#include "./RequestTranslator.h"

void TestGetCurrentTurnRequest();
void TestGetGameStateRequest();
void TestGetTurnResultRequest();
void TestPlayCardsRequest();
void TestCreateNewGameRequest();
void TestJoinGameRequest();

#endif // REQUESTTRANSLATORTEST_H