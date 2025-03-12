#include "ClientBase.h"

ClientBase::ClientBase(Deck* _deck, Validator* _validator, SpecialRules* _rules) {
    deck = _deck;
    validator = _validator;
    rules = _rules;
}

void ClientBase::SetDeck(Deck* _deck) {
    deck = _deck;
}

void ClientBase::SetValidator(Validator* _validator) {
    validator = _validator;
}

void ClientBase::SetRules(SpecialRules* _rules) {
    rules = _rules;
}

void ClientBase::SetLogger(Logger* _logger) {
    logger = _logger;
}

void ClientBase::SetId(int _id) {
    playerId = _id;
}

void ClientBase::SetLastPlayer(ClientBase* player) {
    lastPlayer = player;
}

void ClientBase::SetNextPlayer(ClientBase* player) {
    nextPlayer = player;
}

Card* ClientBase::GetCard(int id) {
    if (id < 0 || id >= onHand.size()) {
        return nullptr;
    }
    return onHand[id];
}

bool ClientBase::DrawCard() {
    Card* card = deck->TakeCard();
    onHand.push_back(card);

    std::string cardCode = translate::name::Code(card->GetName()) + translate::suit::Codename(card->GetSuit());
    std::string lastCode;
    if (deck->DeckSize() + deck->UsedSize() - 1 <= 0) {
        logger->PushLog("T_NC");
        std::cout << "Terminating, not enough cards to play" << std::endl;
        return false;
    }
    if (deck->GetLastUsed() == nullptr) {
        lastCode = "NULL";
    } else {
        lastCode = translate::name::Code(deck->GetLastUsed()->GetName()) + translate::suit::Codename(deck->GetLastUsed()->GetSuit());
    }

    logger->PushLog(std::to_string(playerId) + ";D_" + cardCode + " -- " + lastCode);
    return true;
}

void ClientBase::PlayCard(int id) {
    Card* card = GetCard(id);
    if (card == nullptr) {
        return;
    }
    std::string cardCode = translate::name::Code(card->GetName()) + translate::suit::Codename(card->GetSuit());
    std::string lastCode;
    if (deck->GetLastUsed() == nullptr) {
        lastCode = "NULL";
    } else {
        lastCode = translate::name::Code(deck->GetLastUsed()->GetName()) + translate::suit::Codename(deck->GetLastUsed()->GetSuit());
    }

    logger->PushLog(std::to_string(playerId) + ";P_" + cardCode + " -> " + lastCode);

    deck->UseCard(card);

    std::vector<bool> actions = rules->UpdateOnCard(card, playerId);

    ChangeCard(actions);

    onHand[id] = nullptr;

    for (int i = id; i < onHand.size() - 1; i++) {
        onHand[i] = onHand[i + 1];
    }
    onHand.resize(onHand.size() - 1);
}

int ClientBase::HandSize() {
    return onHand.size();
}

std::vector<Card*> ClientBase::GetHand() {
    return onHand; // Return the player's hand
}