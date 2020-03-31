#include "Player.h"
#include <string>
#include <iostream>

class GBMap;


Player::Player(std::string given_name, int given_id,  HarvestDeck given_hdeck, BuildingDeck given_bdeck) {
	this->name = new string(given_name);
	this->id = new int(given_id);

	building_hand = new vector<BuildingTile*>();
	harvest_hand = new vector<HarvestTile*>();

	player_board = new VGMap();

	cout << *this->name << " is going to draw their starting tiles!" << endl;

	this->DrawHarvestTile(2, given_hdeck);



	cout << *this->name << " has drawn their harvest tiles and will now draw their building tiles.." << endl;

	this->DrawBuilding(6, given_bdeck);



	cout << *this->name << " drew their starting tiles" << endl;
}

Player::~Player()
{
	delete id;
	delete name;
	delete player_board;
	id = nullptr;
	name = nullptr;
	player_board = nullptr;

	building_hand->clear();
	harvest_hand->clear();
}

void Player::exchange(GBMap* given_board, int given_x, int given_y)
{
	this->CalculateResources(given_board, given_x, given_y);
	cout << "GameBoard resources updated!" << endl;
	given_board->PrintResources();
}

bool Player::PlaceHarvestTile(GBMap* given_board, HarvestTile* given_tile, int tl_x, int tl_y, int handIndex)
{
	if ((*given_board).PlaceTile(given_tile, tl_x, tl_y)) { //If the tile has been placed successfully.
		(*harvest_hand).erase((*harvest_hand).begin() + handIndex);
		this->CalculateResources(given_board, tl_x, tl_y); //Calculate the resources we just got.
		return true;
	}
	else return false;
}

void Player::DrawBuilding(int number_of_cards, BuildingDeck given_deck)
{
	for (int i = 0; i < number_of_cards; i++) {
		cout << *this->name << " is drawing a building tile!" << endl;
		this->building_hand->push_back(given_deck.DrawBuildingTile()); //Draw a building tile from the "deck" and add it to the hand vector. Do this for as many cards are requested.
		
	}
}

void Player::DrawHarvestTile(int number_of_cards, HarvestDeck given_deck)
{

	for (int i = 0; i < number_of_cards; i++) {
		cout << *this->name << " is drawing a harvest tile!" << endl;
		this->harvest_hand->push_back(given_deck.DrawHarvestTile()); //Draw a building tile from the "deck" and add it to the hand vector. Do this for as many cards are requested.
		
	}
	
}

void Player::ResourceTracker()
{

}

bool Player::BuildVillage(int given_x, int given_y, bool flipped, BuildingTile given_tile)
{
	return player_board->placeTile(given_x, given_y, flipped, given_tile);
}

void Player::CalculateResources(GBMap* given_board, int tl_x, int tl_y)
{
	(*given_board).CalculateResources(tl_x, tl_y);
}
 
void Player::PrintHarvestHand()
{
	cout << "These are the harvest tiles I have: " << endl;
	int counter = 1;
	for (HarvestTile* harvest_tile : *harvest_hand) {
		cout << "   " << counter++ << "   ";
	}
	cout << endl;
	for (HarvestTile* harvest_tile : *harvest_hand){
		cout << *(harvest_tile->upper_left_str_ptr) << *(harvest_tile->upper_right_str_ptr) << "  ";
		//harvest_tile->PrintHarvestTile();
	}
	cout << endl;
	for (HarvestTile* harvest_tile : *harvest_hand) {
		cout << *(harvest_tile->bottom_left_str_ptr) << *(harvest_tile->bottom_right_str_ptr) << "  ";
		//harvest_tile->PrintHarvestTile();
	}
	cout << endl;


}

void Player::PrintBuildingHand()
{
	cout << "These are the building tiles I have: " << endl;
	for (int i = 0; i < building_hand->size(); i++) {
		cout << (i + 1) << ":";
		building_hand->at(i)->PrintBuildingTile();
		cout << "  ";
	}
	cout << endl;
}
