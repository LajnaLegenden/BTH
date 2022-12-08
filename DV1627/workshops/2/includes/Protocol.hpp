#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP
#include"ResultColumn.hpp"
#include<string>
using namespace std;
class Protocol
{
private:
	ResultColumn* *resultColumn;
	int nrOfPlayers;
	int search(string name)const;
	int findWinner()const;
public:
	Protocol(string names[], int nrOfPlayers, int nrOfCourses);
	~Protocol();
	Protocol(const Protocol &original);
	Protocol& operator=(const Protocol& original);
	bool addResult(string name, int courseNr, int result);
	void presentResultForAGivenPlayer(string name)const;
	void presentResultForAllPlayers()const;
	void presentWinner()const;
};
#endif
