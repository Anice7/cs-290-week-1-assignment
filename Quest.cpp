/**************************************************************
** Program Name: Final Project
** Author: Anthony Nice
** Date: 12/01/18
** Description: Contains the Menu and supporting functions for 
** the game. Allows user to select there path to the tower and
** make other decisions along the way.
***************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include "Battle.hpp"
#include "Barter.hpp"
#include "Riddle.hpp"
#include "Unpassable.hpp"
#include "Quest.hpp"
#include "integerValidation.hpp"


Quest::Quest(){

	currentSpace = NULL;

	rows = 13;
	columns = 71;

	// dynamic allocation of memory space for the map.
	map = new char *[rows];
	for(int i = 0; i < rows; i++){
	map[i] = new char[columns];
	}

	// Create the map for the quest.
	for(int i = 0; i < rows; i++){

		for(int j = 0; j < columns; j++){
			if(i == 0){
				map[i][j] = '-';
			}
			else if(i == rows - 1){
				map[i][j] = '-';
			}
			else if(i == 6 && j >= 10 && j <= 60){
				map[i][j] = '-';
			}
			else if(j == 0){
				map[i][j] = '|';
			}
			else if(j == 10 || j == 20 || j == 30 || j == 40 || j == 50 || j == 60){
				map[i][j] = '|';
			}
			else if(j == columns - 1){
				map[i][j] = '|';
			}
			else if(i == 6 && j == 5){
				map[i][j] = '1';
			}
			else if(i == 3 && j == 15){
				map[i][j] = '2';
			}
			else if(i == 9 && j == 15){
				map[i][j] = '3';
			}
			else if(i == 3 && j == 25){
				map[i][j] = '4';
			}
			else if(i == 9 && j == 25){
				map[i][j] = '5';
			}
			else if(i == 3 && j == 35){
				map[i][j] = '6';
			}
			else if(i == 9 && j == 35){
				map[i][j] = '7';
			}
			else if(i == 3 && j == 45){
				map[i][j] = '8';
			}
			else if(i == 9 && j == 45){
				map[i][j] = '9';
			}
			else if(i == 3 && j == 55){
				map[i][j] = '1';
			}
			else if(i == 3 && j == 56){
				map[i][j] = '0';
			}
			else if(i == 9 && j == 55){
				map[i][j] = '1';
			}
			else if(i == 9 && j == 56){
				map[i][j] = '1';
			}
			else if(i == 6 && j == 65){
				map[i][j] = '1';
			}
			else if(i == 6 && j == 66){
				map[i][j] = '2';
			}
			else{
				map[i][j] = ' ';
			}
		}
	}

}

int Quest::Menu(){

	// Create all the spaces.
	Space* lake = new Barter;
	Space* eastBeast = new Battle;
	Space* meadowSpirit = new Riddle;
	Space* canyonThieves = new Barter;
	Space* cliffUnpassable = new Unpassable;
	Space* caveMonster = new Battle;
	Space* riverLady = new Riddle;
	Space* hollowGiant = new Barter;
	Space* bridgeUnpassable = new Unpassable;
	Space* blackwoodHounds = new Battle;
	Space* bridgeTroll = new Riddle;
	Space* lostKnight = new Battle;

	// link the spaces together to create the path.

	// Tier 1
	// Start at the lake.
	currentSpace = lake;

	// Tier 2
	lake->right = eastBeast;
	lake->left = meadowSpirit;

	// Tier 3
	eastBeast->right = cliffUnpassable;
	eastBeast->left = canyonThieves;

	meadowSpirit->right = cliffUnpassable;
	meadowSpirit->left = canyonThieves;

	cliffUnpassable->left = canyonThieves;

	// Tier 4
	canyonThieves->right = caveMonster;
	canyonThieves->left = riverLady;

	// Tier 5 
	caveMonster->right = hollowGiant;
	caveMonster->left = bridgeUnpassable;

	riverLady->right = hollowGiant;
	riverLady->left = bridgeUnpassable;

	bridgeUnpassable->right = hollowGiant;

	// Tier 6
	hollowGiant->right = blackwoodHounds;
	hollowGiant->left = bridgeTroll;

	// Tier 7	
	blackwoodHounds->top = lostKnight;
	bridgeTroll->top = lostKnight;

/****************************************************************
** Create the bag that the user will be taking on the quest.
****************************************************************/

	std::cout << "**********Introduction To Quest**********" << std::endl;
	std::cout << " " << std::endl;
	
	// Introduction to the game.
	introduction();

	// Input validation variables.
	std::string intInput;
	int numInput;

	// Create the bag container
	bag = new int [11];
	for(int i = 0; i < 11; i++){
		bag[i] = 0;
	}

	// Ask which weapons the user would like to take.
	std::cout << "Which weapon would you like to take on your quest?" << std::endl;
	std::cout << "1. Sword" << std::endl;
	std::cout << "2. Bow and Arrow" << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}	

	// Add weapon to the bag.
	if(numInput == 1){
		bag[0] = 1;
	}
	else{
		bag[1] = 1;
	}

	// Add default Items to the bag.
	std::cout << " " << std::endl;
	std::cout << "You are also taking 25 coins a ring and a map ";
	std::cout << "to the tower on your quest." << std::endl;

	// coins
	bag[4] = 25;

	bag[5] = 1;

	// map
	bag[10] = 1;

	// Choose another item to take and add it to the bag.
	std::cout << " " << std::endl;
	std::cout << "You can choose one of the following items to take too." << std::endl;
	std::cout << "These items will help with battle or previde some value to you. " << std::endl;
	std::cout << "1. Shield" << std::endl;
	std::cout << "2. Medallion" << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter a 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}

	// Add item to the bag.
	if(numInput == 1){
		bag[2] = 1;
	}
	else{
		bag[6] = 1;
	}

	// Select which journal to take.
	std::cout << " " << std::endl;
	std::cout << "You also must choose between Sir John's and Sir Peter's journal. ";
	std::cout << "Both of which did research on the path to the tower." << std::endl;
	std::cout << "1. Sir John's journal" << std::endl;
	std::cout << "2. Sir Peter's journal" << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}

	// Add journal to the bag.
	if(numInput == 1){
		bag[8] = 1;
	}
	else{
		bag[9] = 1;
	}

	// Print out contents of the bag.
	printBag();

/*******************************************************************
** Start the Quest - Tier 1
*******************************************************************/

	int tier = 1;
	int curseDamage = 0;

	std::cout << "**********Begin Your Quest**********" << std::endl;
	std::cout << " " << std::endl;

	// Ask user if they would like to print the map.
	std::cout << "Would you like to print out the map?" << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2. No" << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}

	if(numInput == 1){
		printMap();
	}

	// start across the lake.
	curseDamage = currentSpace->barterChallenge(tier, curseDamage, bag);

	// Print out curse damage and bag contents
	std::cout << "Curse Damage: " << curseDamage << std::endl;
	std::cout << " " << std::endl;
	printBag();

	// Check to see if over curse limit
	if(curseDamage > 20){
		std::cout << "The Curse claimed you." << std::endl;
		std::cout << " " << std::endl;
		return 0;
	}

/*****************************************************************
** Tier 2
*****************************************************************/

	// move to the next tier.
	tier = tier + 1;

	// Ask the user if they would like to reference a journal.
	std::cout << "Would you like to reference a journal?" << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2. No" << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}
	// If yes get a hint from one of the journals.
	if(numInput == 1){
		if(bag[8] == 1){
			curseDamage = sirJohnJournal(tier, curseDamage);
			std::cout << "Curse Damage: " << curseDamage << std::endl;
			std::cout << " " << std::endl;
		}
		else{
			curseDamage = sirPeterJournal(tier, curseDamage);
			std::cout << "Curse Damage: " << curseDamage << std::endl;
			std::cout << " " << std::endl;
		}
	}

	// Ask user if they would like to print the map.
	std::cout << "Would you like to print out the map?" << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2. No" << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}

	// Print map
	if(numInput == 1){
		printMap();
	}

	// Ask the user where they would like to go next.
	std::cout << "Which path would you like to go next?" << std::endl;
	std::cout << "1. East through the Forbidden Wood." << std::endl;
	std::cout << "2. Through the Haunted Meadow." << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}

	// move to the space selected by the user.
	if(numInput == 1){
		currentSpace = eastBeast;
		curseDamage = currentSpace->battleChallenge(tier, curseDamage, bag);
	}
	else{
		currentSpace = meadowSpirit;
		curseDamage = currentSpace->riddleChallenge(tier, curseDamage, bag);
		printBag();
	}

	// print out curse damage
	std::cout << "Curse Damage: " << curseDamage << std::endl;
	std::cout << " " << std::endl;

	// check to see if over the curse damage limit.
	if(curseDamage > 20){
		std::cout << "The Curse claimed you." << std::endl;
		std::cout << " " << std::endl;
		return 0;
	}

/*****************************************************************
** Tier 3
*****************************************************************/

	// move to the next tier.
	tier = tier + 1;

	// Ask the user if they would like to reference a journal.
	std::cout << "Would you like to reference a journal?" << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2. No" << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}
	// If yes get a hint from one of the journals.
	if(numInput == 1){
		if(bag[8] == 1){
			curseDamage = sirJohnJournal(tier, curseDamage);
			std::cout << "Curse Damage: " << curseDamage << std::endl;
			std::cout << " " << std::endl;
		}
		else{
			curseDamage = sirPeterJournal(tier, curseDamage);
			std::cout << "Curse Damage: " << curseDamage << std::endl;
			std::cout << " " << std::endl;
		}
	}

	// Ask user if they would like to print the map.
	std::cout << "Would you like to print out the map?" << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2. No" << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}

	if(numInput == 1){
		printMap();
	}

	// Ask the user where they would like to go next.
	std::cout << "Which path would you like to take next?" << std::endl;
	std::cout << "1. Through the Canyon of Darkness." << std::endl;
	std::cout << "2. Over the Cliffs of Doom." << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}	

	// move to the space selected by the user.
	// If unpassable space go to the other space.
	if(numInput == 1){
		currentSpace = canyonThieves;
		curseDamage = currentSpace->barterChallenge(tier, curseDamage, bag);
		printBag();
	}
	else{
		currentSpace = cliffUnpassable;
		curseDamage = currentSpace->goBack(tier, curseDamage);

		std::cout << " " << std::endl;
		std::cout << "Curse Damage: " << curseDamage << std::endl;
		std::cout << " " << std::endl;

		currentSpace = canyonThieves;
		curseDamage = currentSpace->barterChallenge(tier, curseDamage, bag);
		printBag();
	}

	// print out curse damage
	std::cout << "Curse Damage: " << curseDamage << std::endl;
	std::cout << " " << std::endl;

	// check to see if curse damage is over the limit.
	if(curseDamage > 20){
		std::cout << "The Curse claimed you." << std::endl;
		std::cout << " " << std::endl;
		return 0;
	}

/*****************************************************************
** Tier 4
*****************************************************************/

	// move to the next tier.
	tier = tier + 1;	

	// Ask the user if they would like to reference a journal.
	std::cout << "Would you like to reference a journal?" << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2. No" << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}
	// If yes get a hint from one of the journals.
	if(numInput == 1){
		if(bag[8] == 1){
			curseDamage = sirJohnJournal(tier, curseDamage);
			std::cout << "Curse Damage: " << curseDamage << std::endl;
			std::cout << " " << std::endl;
		}
		else{
			curseDamage = sirPeterJournal(tier, curseDamage);
			std::cout << "Curse Damage: " << curseDamage << std::endl;
			std::cout << " " << std::endl;
		}
	}

	// Ask user if they would like to print the map.
	std::cout << "Would you like to print out the map?" << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2. No" << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}

	if(numInput == 1){
		printMap();
	}

	// Ask the user where they would like to go next.
	std::cout << "Which path would you like to take next?" << std::endl;
	std::cout << "1. Through the Abandoned Mining Caves." << std::endl;
	std::cout << "2. Along the banks of the Narrows River." << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}	

	// move to the space selected by the user.
	if(numInput == 1){
		currentSpace = caveMonster;
		curseDamage = currentSpace->battleChallenge(tier, curseDamage, bag);
		printBag();
	}
	else{
		currentSpace = riverLady;
		curseDamage = currentSpace->riddleChallenge(tier, curseDamage, bag);
	}

	// print out curse damage.
	std::cout << "Curse Damage: " << curseDamage << std::endl;
	std::cout << " " << std::endl;

	// check to see if the curse damage is over the limit.
	if(curseDamage > 20){
		std::cout << "The Curse claimed you." << std::endl;
		std::cout << " " << std::endl;
		return 0;
	}

/*****************************************************************
** Tier 5
*****************************************************************/

	// move to the next tier.
	tier = tier + 1;	

	// Ask the user if they would like to reference a journal.
	std::cout << "Would you like to reference a journal?" << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2. No" << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}
	// If yes get a hint from one of the journals.
	if(numInput == 1){
		if(bag[8] == 1){
			curseDamage = sirJohnJournal(tier, curseDamage);
			std::cout << "Curse Damage: " << curseDamage << std::endl;
			std::cout << " " << std::endl;
		}
		else{
			curseDamage = sirPeterJournal(tier, curseDamage);
			std::cout << "Curse Damage: " << curseDamage << std::endl;
			std::cout << " " << std::endl;
		}
	}

	// Ask user if they would like to print the map.
	std::cout << "Would you like to print out the map?" << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2. No" << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}

	if(numInput == 1){
		printMap();
	}

	// Ask the user where they would like to go next.
	std::cout << "Which path would you like to take next?" << std::endl;
	std::cout << "1. Through the Hollow of Whispers." << std::endl;
	std::cout << "2. Over King James's Bridge." << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}	

	// move to the space selected by the user.
	if(numInput == 1){
		currentSpace = hollowGiant;
		curseDamage = currentSpace->barterChallenge(tier, curseDamage, bag);
		printBag();
	}
	else{
		currentSpace = bridgeUnpassable;
		curseDamage = currentSpace->goBack(tier, curseDamage);

		std::cout << " " << std::endl;
		std::cout << "Curse Damage: " << curseDamage << std::endl;
		std::cout << " " << std::endl;

		currentSpace = hollowGiant;
		curseDamage = currentSpace->barterChallenge(tier, curseDamage, bag);
		printBag();
	}

	// print out curse damage.
	std::cout << "Curse Damage: " << curseDamage << std::endl;
	std::cout << " " << std::endl;

	// check to see if the curse damage is over the limit.
	if(curseDamage > 20){
		std::cout << "The Curse claimed you." << std::endl;
		std::cout << " " << std::endl;
		return 0;
	}

/*****************************************************************
** Tier 6
*****************************************************************/

	// move to the next tier.
	tier = tier + 1;

	// Ask the user if they would like to reference a journal.
	std::cout << "Would you like to reference a journal?" << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2. No" << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}
	// If yes get a hint from one of the journals.
	if(numInput == 1){
		if(bag[8] == 1){
			curseDamage = sirJohnJournal(tier, curseDamage);
			std::cout << "Curse Damage: " << curseDamage << std::endl;
			std::cout << " " << std::endl;
		}
		else{
			curseDamage = sirPeterJournal(tier, curseDamage);
			std::cout << "Curse Damage: " << curseDamage << std::endl;
			std::cout << " " << std::endl;
		}
	}	

	// Ask user if they would like to print the map.
	std::cout << "Would you like to print out the map?" << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2. No" << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}

	if(numInput == 1){
		printMap();
	}

	// Ask the user where they would like to go next.
	std::cout << "Which path would you like to take next?" << std::endl;
	std::cout << "1. Through the Blackwood's." << std::endl;
	std::cout << "2. Over the Stonecastle Bridge." << std::endl;
	std::cin >> intInput;

	numInput = intValidation(intInput);
	while(numInput < 1 || numInput > 2){
		std::cout << "Please enter 1 or 2." << std::endl;
		std::cin >> intInput;
		numInput = intValidation(intInput);
	}	

	// move to the space selected by the user.
	if(numInput == 1){
		currentSpace = blackwoodHounds;
		curseDamage = currentSpace->battleChallenge(tier, curseDamage, bag);
	}
	else{
		currentSpace = bridgeTroll;
		curseDamage = currentSpace->riddleChallenge(tier, curseDamage, bag);
	}

	// print out curse damage.
	std::cout << "Curse Damage: " << curseDamage << std::endl;
	std::cout << " " << std::endl;

	// check to see if the curse is over the limit.
	if(curseDamage > 20){
		std::cout << "The Curse claimed you." << std::endl;
		std::cout << " " << std::endl;
		return 0;
	}

/*****************************************************************
** Tier 7
*****************************************************************/

	// move to the next tier.
	tier = tier + 1;	

	// move to the final space.
	currentSpace = lostKnight;
	curseDamage = currentSpace->battleChallenge(tier, curseDamage, bag);

	// print out curse damage.
	std::cout << "Curse Damage: " << curseDamage << std::endl;
	std::cout << " " << std::endl;

	// check to see if the curse damage is over the limit.
	// if not add key to bag.
	if(curseDamage > 20){
		std::cout << "The Curse claimed you before you could retrieve the Staff." << std::endl;
		std::cout << " " << std::endl;
		return 0;
	}
	else{
		bag[3] = 1;
		printBag();
	}

	// End of game.
	endOfGame();

	// deallocate memory for spaces.
	delete lake;
	delete eastBeast;
	delete meadowSpirit;
	delete cliffUnpassable;
	delete canyonThieves;
	delete caveMonster;
	delete riverLady;
	delete hollowGiant;
	delete bridgeUnpassable;
	delete blackwoodHounds;
	delete bridgeTroll;
	delete lostKnight;	
	currentSpace = NULL;

	// deallocate memory for bag.
	delete[] bag;

	return 0;

}


void Quest::printBag(){

	// print out the contents of the bag.
	std::cout << "*******Content's Of Your Bag*******" << std::endl;
	for(int i = 0; i < 11; i++){
		if(bag[i] != 0){
			if(i == 0){
				std::cout << "Sword" << std::endl;
			}
			if(i == 1){
				std::cout << "Bow and Arrow" << std::endl;
			}
			if(i == 2){
				std::cout << "Shield" << std::endl;
			}
			if(i == 3){
				std::cout << "KEY!!!!" << std::endl;
			}
			if(i == 4){
				int temp;
				temp = bag[i];
				std::cout << "Coins: " << temp << std::endl;
			}
			if(i == 5){
				std::cout << "Ring" << std::endl;
			}
			if(i == 6){
				std::cout << "Medallion" << std::endl;
			}
			if(i == 7){
				std::cout << "Jeweled Dagger" << std::endl;
			}
			if(i == 8){
				std::cout << "Sir John's Journal" << std::endl;
			}
			if(i == 9){
				std::cout << "Sir Peter's Journal" << std::endl;
			}
			if(i == 10){
				std::cout << "Map" << std::endl;
			}
		}
	}
	std::cout << " " << std::endl;
}

void Quest::printMap(){

	std::cout << " " << std::endl;
	std::cout << "**********Path to the Tower Map**********" << std::endl;
	std::cout << " " << std::endl;

	// print out the map.
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			std::cout << map[i][j];
		}
		std::cout << " " << std::endl;
	}

	std::cout << "1. Glass Lake" << std::endl;
	std::cout << "2. Haunted Meadow" << std::endl;
	std::cout << "3. Forbidden Wood" << std::endl;
	std::cout << "4. Canyon of Darkness" << std::endl;
	std::cout << "5. Cliffs fo Doom" << std::endl;
	std::cout << "6. Narros River" << std::endl;
	std::cout << "7. Abandoned Mining Caves" << std::endl;
	std::cout << "8. King James Bridge" << std::endl;
	std::cout << "9. Hollow of Whispers" << std::endl;
	std::cout << "10. Stonecastle Bridge" << std::endl;
	std::cout << "11. The Blackwood's" << std::endl;
	std::cout << "12. The Tower" << std::endl;
	std::cout << " " << std::endl;
	
}

void Quest::introduction(){

	// Introduction to the game.
	std::cout << "Welcome to the Quest for the Staff of Light. You are the noblest Knight in the realm" << std::endl;
	std::cout << "and the King has come to you for help.  He tells you that there is an Army converging on" << std::endl;
	std::cout << "the Kingdom from the North. We are severly out numbered and our walls are sure to fall if" << std::endl;
	std::cout << "we don't something drastic. That is why he is here.  He has come to ask you to make a quest" << std::endl; 
	std::cout << "to retrieve the Staff of Light.  The Staff of Light is located in the Tower across Glass Lake" << std::endl;
	std::cout << "and deep into cursed land.  Long ago a Sorcerer put a curse on the land around the Tower to" << std::endl;
	std::cout << "protect the Staff. The second you step foot on the soil on the other side of Glass Lake you" << std::endl;
	std::cout << "are cursed and can only take Curse Damage up to 20 before the curse claims your life. The only" << std::endl;
	std::cout << "way to cure the curse is to get to the Tower and claim the Staff. The Tower is said to be guarded" << std::endl;
	std::cout << "by the Lost Knight. He is the holder of the key that unlocks the Staff.  Along the way you will" << std::endl;
	std::cout << "face many challenges. You will be able to choose which path you want to take along the way. Each" << std::endl;
	std::cout << "challenge will add time to your quest.  How long will depend on how well you do on the challenge." << std::endl;
	std::cout << "You will be able to take items on the quest that will help you with the challenges. Some of" << std::endl;
	std::cout << "the items are weapons and some are valuables. You will also be able to take a Journal of a" << std::endl;
	std::cout << "Knight that has done research on the path to the Tower. These journals might have hints that" << std::endl;
	std::cout << "help and they might not. If you choose to look for a hint on which way to go that will take" << std::endl;
	std::cout << "some extra time. Now go get ready for your quest and pack your bag you will be leaving soon." << std::endl;
	std::cout << "Good Luck. The Kingdom depends on you." << std::endl;
	std::cout << " " << std::endl; 
}

void Quest::endOfGame(){

	// end of game message.
	std::cout << "**********Congratulations**********" << std::endl;
	std::cout << " " << std::endl;
	std::cout << "You retrieve the key from the Lost Knight and head up the Tower to the room where the Staff" << std::endl;
	std::cout << "of Light it stored. You open the door and there it is, sitting on its throne. You walk over" << std::endl;
	std::cout << "and pick it up and instantly feel better. Now that your have the Staff you will be able to  " << std::endl; 
	std::cout << "defeat the Army from the North and save your Kingdom." << std::endl;
	std::cout << " " << std::endl;
	
}

int Quest::sirJohnJournal(int tier, int curseDamage){

	// print out hints if they are asked for.
	if(tier == 2){
		std::cout << " " << std::endl;
		std::cout << "HINT:" << std::endl;
		std::cout << "There is rummored to be a Beast in the Forbidden Wood. Probably best to battle" << std::endl;
		std::cout << "a Beast of that nature with a Bow and Arrow." << std::endl;
		std::cout << " " << std::endl;

		curseDamage = curseDamage + 1;
	}
	else if(tier == 3){
		std::cout << " " << std::endl;
		std::cout << "HINT:" << std::endl;
		std::cout << "The Canyon is said to have a price for passage. Things other than coins might" << std::endl;
		std::cout << "be more valuable." << std::endl;
		std::cout << " " << std::endl;

		curseDamage = curseDamage + 1;
	}
	else if(tier == 4){
		std::cout << " " << std::endl;
		std::cout << "HINT:" << std::endl;
		std::cout << "In the caves there is rumored to be a Monster. A sword would probably be the " << std::endl;
		std::cout << "most effective in the close quarters." << std::endl;
		std::cout << " " << std::endl;

		curseDamage = curseDamage + 1;
	}
	else if(tier == 5){
		std::cout << " " << std::endl;
		std::cout << "HINT:" << std::endl;
		std::cout << "King James Bridge is over a deep canyon and is very old. Might not be the " << std::endl;
		std::cout << "safest path." << std::endl;
		std::cout << " " << std::endl;

		curseDamage = curseDamage + 1;
	}
	else{
		std::cout << " " << std::endl;
		std::cout << "HINT:" << std::endl;
		std::cout << "In the Blackwood there is said to be Hounds. A shield would be very helpful" << std::endl;
		std::cout << "in defending and defeat them." << std::endl;
		std::cout << " " << std::endl;

		curseDamage = curseDamage + 1;
	}

	return curseDamage;
}

int Quest::sirPeterJournal(int tier, int curseDamage){

	// print out hints if asked for.
	if(tier == 2){
		std::cout << " " << std::endl;
		std::cout << "HINT:" << std::endl;
		std::cout << "Those who have passed through the meadow in the past have said to encounter" << std::endl;
		std::cout << "a mysterious force that took whit to pass." << std::endl;
		std::cout << " " << std::endl;

		curseDamage = curseDamage + 1;
	}
	else if(tier == 3){
		std::cout << " " << std::endl;
		std::cout << "HINT:" << std::endl;
		std::cout << "The Cliffs of Doom are said to be very steep and dangerous. Only experienced " << std::endl;
		std::cout << "climbers should take this path." << std::endl;
		std::cout << " " << std::endl;

		curseDamage = curseDamage + 1;
	}
	else if(tier == 4){
		std::cout << " " << std::endl;
		std::cout << "HINT:" << std::endl;
		std::cout << "The Narrows River has narrow banks and is rummored to be ruled by a magical" << std::endl;
		std::cout << "being that likes to battle with whit not force." << std::endl;
		std::cout << " " << std::endl;

		curseDamage = curseDamage + 1;
	}
	else if(tier == 5){
		std::cout << " " << std::endl;
		std::cout << "HINT:" << std::endl;
		std::cout << "Those who have tried to pass through the Hollow have mentioned encountering a" << std::endl;
		std::cout << "large creature that will take shinny things as payment for passage." << std::endl;
		std::cout << " " << std::endl;

		curseDamage = curseDamage + 1;
	}
	else{
		std::cout << " " << std::endl;
		std::cout << "HINT:" << std::endl;
		std::cout << "Stonecastle Bridge is the final bridge before the tower and requires whit to" << std::endl;
		std::cout << "cross." << std::endl;
		std::cout << " " << std::endl;

		curseDamage = curseDamage + 1;
	}

	return curseDamage;
}

Quest::~Quest(){

	//deallocate memory for map.
	for(int i = 0; i < rows; i++){
		delete[] map[i];
	}
	delete[] map;
}