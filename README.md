# CardGameBackend

> Data for 29.04.2025, 2:55PM

# Work done

## division of labor
- [Bejmach (Maciej Bejmowicz)](https://github.com/Bejmach/): Backend
- [Loter (Hubert Pszybysz)](https://github.com/HPrzybysz): Frontend
- [Kajmaks (Maksymilian Janicki)](https://github.com/kajmaks): AI to play against

## commits
- 49 total commits
- ~15 work on unused things like server or client
- ~5 readme updates

## Personal commit record
- [Bejmach (Maciej Bejmowicz)](https://github.com/Bejmach/): 47 (5 readme / 13 unused / 29 used)
- [Loter (Hubert Pszybysz)](https://github.com/HPrzybysz): 2 (2 unused)
- [Kajmaks (Maksymilian Janicki)](https://github.com/kajmaks): 0
> Bejmach: do I even need to comment that

## Whats done
- Backend with few bugs (Bejmach)
- Debugging tools to monitor games (Bejmach)

## What was dropped
- Server to send data to clients using sockets (Bejmach)
- Client to send data to server using sockets (debugging version) (bejmach)
- Req/Res translator to translate data to and from chars to readable format (base - Loter, Whole redesign, because nothing worked - Bejmach)
- Env reader worked on that for like 15 min, so not so big loss (bejmach)

> Bejmach: Req/Res translator in its first version was using something like 0<<7... im rly don't know what to say. Also comments everywhere. looked a lot like gpt or other AI wrote that.

## Component explanation

- GameMaster: Order of the game, holds pointers to logger, players, deck, validator, and special rules (Bejmach)
- ClientBase: All basic functions to work with deck (Bejmach)
- Deck: Stores all used and unused cards (Bejmach)
- logger: Creates a log files in folder logs, if folder exists (Bejmach)
- validator: Validates, if move can be performed based on game state (Bejmach)
- special rules: works with special cards like 4, to stop another player, or 2, to give card 

## Game Order
- Game master starts creates logger, new deck, validator and special rules
- Players join to game master
- Game master prepares every player to game (gives them pointers to deck, validator, etc.)
- Game master starts turn in player 1
- Player 1 does its turn
- Player 1 tells player 2, that it is its turn
- Repeat last 2, until someone won.
