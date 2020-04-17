#pragma once
#include <vector>
#include "Subject.h"
#include "Resources.h"
#include "Player.h"



class  GameState : public Subject {
public:

	int* numOfPlayers = new int;
	int* remainingTiles = new int;
	int* currentTurn = new int;
	Player* players[4];
	GBMap* gameBoard;
	HarvestDeck* harvest_deck;
	BuildingDeck* building_deck;


	//GameState();


};