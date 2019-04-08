/**************************************************************
** Program Name: Final Project
** Author: Anthony Nice
** Date: 12/01/18
** Description: Header file for Quest class.
***************************************************************/

#ifndef QUEST_HPP
#define QUEST_HPP
#include "Space.hpp"

class Quest
{

private:
	char **map;
	int rows;
	int columns;

protected:


public:
	int *bag;
	Space* currentSpace;
	Quest();
	int Menu();
	void printBag();
	void printMap();
	void introduction();
	void endOfGame();
	int sirJohnJournal(int, int);
	int sirPeterJournal(int, int);
	~Quest();

};

#endif	

