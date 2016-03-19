# GoFish_MPC
A simple command line game of Go Fish using Secure MultiParty Computation

https://github.com/trevormeiss/GoFish_MPC

## Functionalities

1. __Shared unknown set with private removal__: Players share a stockpile to draw cards from. When a player draws a card, other players should not know what card was drawn but should also not be able to draw that card in the future.
2. A player may only ask for ranks they already have at least one of in their hand. E.g. a player cannot ask for sixes if they don’t have at least one six in their hand.
3. __Private set contains__: Players must forfeit the requested cards if they have them. E.g. if I ask you for sixes and you have two sixes in your hand, you must give me those two sixes. Other players should be able to determine if each card is a requested card, but should not learn anything else. _We currently do not have a protocol for this functionality because we assume the players are semi-honest._
4. Players must validate that the cards sent are what the requesting player wanted.

## Protocol Overview

1. Create Deck
	- Trusted Initializer
		- Shuffles Deck (array of integers 1-52)
		- Generates n-out-of-n share of every card for all n players
		- Each player receives array of their shares of the deck

2. Draw Hands
	- Round Robin of Players
		- For 0 to # starting cards
			- player sends index of card drawn (0-51) to all other players
				- players mark this index as no longer in deck
				- other players return their share of this deck index

	Now each player knows their own hand and the indices of cards that can no longer be drawn

3. Play
	- Round Robin of Players (initializer chooses random starting player)
		- Player (Sender S) sends request(R,X,i) to all players
			- R is the player number S wants to receive cards from
			- X is the card rank S is looking for (1-13)
			- i is the index of a card of rank X from S's hand
				- In order for S to request cards of rank X, they must have at least one of these cards in their hand
				- R asks for all shares of card at index i to validate it is of rank X

		- If R has card(s) of rank X
			- R tells all players how many cards of rank X it has
			- R sends indices of these cards to S
			- S asks all players for shares of these indices to verify them
			- S can now make another request to any player

		- Else
			- R tells S to go fish
			- S sends index of card drawn to all players
			- all players send share of this index to S

4. Check for Book
	- Every time player receives card(s) (from a player or from deck)
		- If player has four of a rank (aka a book)
			- Player sends indices of these four cards to all players
			- All players exchange shares of these cards to verify them
			- If total books of all players = 13, game is over
				
## Build
1. Download, Build, and Install [Apache Thrift](https://thrift.apache.org/)
  * On OSX, it's easiest to use `$ brew install thrift`
2. Navigate to `\gen-cpp`
3. `$ make`

## Run
1. Start two or more players on one or multiple machines
  * `$ ./GoFish_Player PORT`
2. Start an initializer on any machine to connect and initialize the players
  * `$ ./GoFish_Initializer`
3. With the initializer, connect to all the players
  * `c IP PORT`
4. For sanity check, list all connected players
  * `ls`
5. Optionally set the prime number to be used by all players (should be higher than 52)
  * `p PRIME`
6. Start Go Fish!
  * `s`
  * the initializer chooses a random player to start
7. With the starting player, select another player to request card from
  * i.e. `1`
8. Select a card rank to request
  * i.e. `A`
9. Continue playing until all the cards are used!
