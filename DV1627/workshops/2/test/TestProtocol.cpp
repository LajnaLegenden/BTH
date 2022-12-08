#include "../includes/Protocol.hpp"
#include <iostream>
using namespace std;
int main()
{
	//Basic test
	{
		string playerName[]{"Nisse", "Lisa"};
		Protocol prot(playerName, 2, 3);
		prot.addResult("Nisse", 1, 5);
		prot.addResult("Lisa", 1, 4);
		prot.addResult("Nisse", 2, 4);
		prot.addResult("Lisa", 2, 3);
		prot.addResult("Nisse", 3, 6);
		prot.addResult("Lisa", 3, 5);

		cout << "Result for Lisa" << endl;
		prot.presentResultForAGivenPlayer("Lisa");
		cout << endl
			 << endl;
		(void)getchar();
		cout << "Result for all" << endl;
		prot.presentResultForAllPlayers();
		cout << endl
			 << endl;
		(void)getchar();
		cout << "Winner" << endl;
		prot.presentWinner();
		cout << endl
			 << endl;
		(void)getchar();
	}

	//Test of copy constructor and assignment operator

	string playerName[]{"Nisse", "Lisa"};
	Protocol prot(playerName, 2, 4);
	prot.addResult("Nisse", 1, 5);
	prot.addResult("Lisa", 1, 4);
	prot.addResult("Nisse", 2, 4);
	prot.addResult("Lisa", 2, 3);
	prot.addResult("Nisse", 3, 6);
	prot.addResult("Lisa", 3, 5);

	//Copy constructor
	Protocol protTwo = prot;
	protTwo.addResult("Nisse", 4, 7);
	cout << "Test of copy constructor" << endl;
	cout << "Result for all" << endl;
	cout << "prot: " << endl;
	prot.presentResultForAllPlayers();
	cout << "protTwo: " << endl;
	protTwo.presentResultForAllPlayers();
	cout << endl
		 << endl;
	(void)getchar();

	//Assignment operator, protThree has fewer players
	string playerNameTwo[]{"Bo", "Eva"};
	Protocol protThree(playerNameTwo, 2, 7);
	protThree = prot;
	protThree.addResult("Nisse", 4, 7);
	cout << "Test of assignment operator 1" << endl;
	cout << "Result for all" << endl;
	cout << "prot: " << endl;
	prot.presentResultForAllPlayers();
	cout << "protThree: " << endl;
	protThree.presentResultForAllPlayers();
	cout << endl
		 << endl;
	(void)getchar();

	//Assignment operator, protFour has more players
	string playerNameThree[]{"Pelle", "Kajsa", "Kalle", "Stina", "Lasse"};
	Protocol protFour(playerNameThree, 5, 1);
	protFour.addResult("Pelle", 1, 8);
	protFour.addResult("Kajsa", 1, 6);
	protFour.addResult("Kalle", 1, 7);
	protFour.addResult("Stina", 1, 5);
	protFour.addResult("Lasse", 1, 6);
	protFour.presentResultForAllPlayers();
	protFour = prot;
	protFour.addResult("Nisse", 4, 5);
	cout << "Test of assignment operator 2" << endl;
	cout << "Result for all" << endl;
	cout << "prot: " << endl;
	prot.presentResultForAllPlayers();
	cout << "protFour: " << endl;
	protFour.presentResultForAllPlayers();
	cout << endl
		 << endl;
	(void)getchar();

	//Assignment operator, self assignment
	prot = prot;
	cout << "Test of assignment operator 3" << endl;
	cout << "Result for all" << endl;
	prot.addResult("Nisse", 4, 8);
	prot.presentResultForAllPlayers();
	cout << endl
		 << endl;
	(void)getchar();

	return 0;
}