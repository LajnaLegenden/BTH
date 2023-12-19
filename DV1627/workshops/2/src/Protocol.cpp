#include "../includes/Protocol.hpp"
#include <iostream>
using namespace std;

Protocol::Protocol(string names[], int nrOfPlayers, int nrOfCourses) : nrOfPlayers(nrOfPlayers)
{
    this->resultColumn = new ResultColumn *[nrOfPlayers];
    for (int i = 0; i < nrOfPlayers; i++)
    {
        this->resultColumn[i] = new ResultColumn(names[i], nrOfCourses);
    }
}

Protocol::Protocol(const Protocol &original)
{
    this->nrOfPlayers = original.nrOfPlayers;
    this->resultColumn = new ResultColumn *[this->nrOfPlayers];
    for (int i = 0; i < this->nrOfPlayers; i++)
    {
        this->resultColumn[i] = new ResultColumn(*original.resultColumn[i]);
    }
}

Protocol::~Protocol()
{
    for (int i = 0; i < this->nrOfPlayers; i++)
    {
        delete this->resultColumn[i];
    }
    delete[] this->resultColumn;
}

Protocol &Protocol::operator=(const Protocol &original)
{
    for (int i = 0; i < this->nrOfPlayers; i++)
    {
        delete this->resultColumn[i];
    }
    delete[] this->resultColumn;
    this->nrOfPlayers = original.nrOfPlayers;
    this->resultColumn = new ResultColumn *[this->nrOfPlayers];
    for (int i = 0; i < this->nrOfPlayers; i++)
    {
        this->resultColumn[i] = new ResultColumn(*original.resultColumn[i]);
    }
}

bool Protocol::addResult(string name, int courseNr, int result)
{
    int index = this->search(name);
    this->resultColumn[index]->addResult(courseNr, result);
}
void Protocol::presentResultForAGivenPlayer(string name) const {}
void Protocol::presentResultForAllPlayers() const {}
void Protocol::presentWinner() const
{
    int winnerIndex = this->findWinner();
    std::cout << "Winner is " << this->resultColumn[winnerIndex]->getPlayerName() << std::endl;
}

int Protocol::search(string name) const
{
    for (int i = 0; i < nrOfPlayers; i++)
    {
        if (this->resultColumn[i]->getPlayerName() == name)
        {
            return i;
        }
    }
}
int Protocol::findWinner() const
{
    int currentTopResult = 0;
    for (int i = 0; i < nrOfPlayers; i++)
    {
        if (this->resultColumn[i]->totalResult() > this->resultColumn[currentTopResult]->totalResult())
        {
            currentTopResult = i;
        }
    }
    return this->resultColumn[currentTopResult]->totalResult();
}
