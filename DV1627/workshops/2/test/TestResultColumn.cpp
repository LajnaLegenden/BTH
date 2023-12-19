#include "../includes/ResultColumn.hpp"
#include <iostream>
#include <ctime>
using namespace std;

int main()
{
	srand((unsigned)time(0));
	bool ok = true;
	// Basic testing of ResultColumn
	{
		ResultColumn resCol("Kalle", 4);

		resCol.addResult(1, 4);
		resCol.addResult(1, 5);
		resCol.addResult(2, 6);
		// course 3 should get 10 as result
		resCol.addResult(4, 1);

		if (resCol.totalResult() != 21 || resCol.getPlayerName() != "Kalle")
			ok = false;
		cout<<"Testing toString(): "<< resCol.toString() << endl;

		ResultColumn resColOne("Sven", 4);
		if (resColOne.totalResult() != 40 || resColOne.getPlayerName() != "Sven")
			ok = false;
	}
	if (!ok)
		cout << "Failed basic testing" << endl;
	else
	{
		cout << "Basic testing ok" << endl << endl << endl;

		// Testing copyconstructor
		{
			ResultColumn resColOne("Pelle", 7);
			for (int i = 1; i <= 6; i++)
			{
				resColOne.addResult(i, rand() % 9 + 1);
			}

			// creating an object from an object containing results
			ResultColumn resColTwo(resColOne);
			// changing one of the two identical objects
			resColOne.addResult(7, 5);

			if (resColOne.totalResult() == resColTwo.totalResult() || resColOne.getPlayerName() != resColTwo.getPlayerName())
				ok = false;

			ResultColumn resCol("Lasse", 5);

			// creating an object from an object containing no results 
			ResultColumn resColThree(resCol);			
			// changing one of the two idenitcal objects
			resColThree.addResult(1, 1);
			if (resCol.totalResult() == resColThree.totalResult())
				ok = false;
		}
	}
	if (!ok)
		cout << "Failed testing copy constructor" << endl;
	else
	{
		cout << "Testing of copy constructor ok" << endl << endl << endl;

		// Testing assignmentoperator
		{
			ResultColumn resCol("Lasse", 5);

			ResultColumn resColOne("Pelle", 7);
			for (int i = 1; i <= 6; i++)
			{
				resColOne.addResult(i, rand() % 9 + 1);
			}
			
			// assigning/changing an objects containing no results, according to an object containing some results
			resCol = resColOne;
			// changing one of the two idenitcal objects 
			resColOne.addResult(7, 5);
			if (resColOne.totalResult() == resCol.totalResult() || resColOne.getPlayerName() != resCol.getPlayerName())
				ok = false;

			ResultColumn resColTwo("Stina", 3);
			// assigning/changing an objects containing some results, according to an object containing no results
			resColOne = resColTwo;
			// changing one of the two idenitcal objects
			resColOne.addResult(1, 5);
			if (resColOne.totalResult() == resColTwo.totalResult() || resColOne.getPlayerName() != resColTwo.getPlayerName())
				ok = false;

			ResultColumn resColThree("Marita", 8);
			for (int i = 2; i <= 8; i++)
			{
				resColOne.addResult(i, rand() % 9 + 1);
			}

			resColTwo.addResult(1, 2);
			resColTwo.addResult(2, 4);
			// assigning/changing an objects containing some results, according to an object also containing some results
			resColThree = resColTwo;
			// changing one of the two idenitcal objects
			resColTwo.addResult(3, 7);

			if (resColThree.totalResult() == resColTwo.totalResult() || resColThree.getPlayerName() != resColTwo.getPlayerName())
				ok = false;
		}
	}
	if (!ok)
		cout << "Failed testing assignment operator" << endl;
	else
	{
		cout << "Testing of assignment operator ok" << endl << endl << endl;
	}
	return 0;
}