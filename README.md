# CardGameBackend

## Send data construction
### Client
* 0-3 localId (user id in room); 2 bytes
* 0-1023 roomId; 10 bytes /*temporary*/
* 0-3 move (0-draw, 1-play...); 2 bytes /*temporary*/
* 0-51 card; 6 bytes
20 bytes
use int32
### Server
#### Send before move
* 0-13 - current card name; 4 bytes
* 0-4 - current card suit; 3 bytes(undefined exists)
7 bytes
use int8
#### Send after move
##### Approach 1
/*Safe?*/
* 0-1 valid move; 1 byte;
* 0-51 number of cards on hand; 6 bytes
* struct{0-51 card type; 6 bytes} * number of card; 6-312 bytes
319 bytes
use something, that can store so many bytes
##### Approach 2
/*Probably safe?*/
* 0-1 valid move; 1 byte;
* 0-52 card to dispose (one additional for situations where move is not valid) 6 bytes
7 bytes
use int8;
#### Send after other players
* 0-3 localId; 2 bytes
* 0-3 move; 2 bytes/*temporary*/
* 0-13 card name; 4 bytes
* 0-4 card suit; 3 bytes

## Work rules
### Before starting work
* Create new branch
### While working
* Do whatever you like
### Before Commiting
* Update gitignore to remove all unnecesary data, like executables/hidden editor folders/editor data
* Check if you only commit source code and needed data(if something like that went to git add, update gitignore to skip those files in future)
* Please, don't just use some buttons to instantly push, I'm begging you, use also git status to check what files you'r commiting, before commiting
### After commiting
* push new branch to github, and open pull request for merging with update branch

## Meetings
* No strict rules. You need something, you ask something
