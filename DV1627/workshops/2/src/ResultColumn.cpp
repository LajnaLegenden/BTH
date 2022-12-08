#include "../includes/ResultColumn.hpp"
#include <iostream>
using namespace std;
ResultColumn::ResultColumn(string playerName, int nrOfCourses)
{
    this->playerName = playerName;
    this->nrOfCourses = nrOfCourses;
    this->results = new int[nrOfCourses];
    for (int i = 0; i < nrOfCourses; i++)
    {
        this->results[i] = NO_RESULT;
    }
}

ResultColumn::ResultColumn(const ResultColumn &origin)
{
    this->playerName = origin.playerName;
    this->nrOfCourses = origin.nrOfCourses;
    this->results = new int[nrOfCourses]{NO_RESULT};
    for (int i = 0; i < origin.nrOfCourses; i++)
    {
        this->results[i] = origin.results[i];
    }
}

ResultColumn::~ResultColumn()
{
    delete[] results;
}

ResultColumn &ResultColumn::operator=(const ResultColumn &origin)
{
    this->playerName = origin.playerName;
    this->nrOfCourses = origin.nrOfCourses;
    delete[] this->results;
    this->results = new int[nrOfCourses]{NO_RESULT};
    for (int i = 0; i < origin.nrOfCourses; i++)
    {
        this->results[i] = origin.results[i];
    }
    return *this;
}

string ResultColumn::getPlayerName() const
{
    return this->playerName;
}

string ResultColumn::toString() const
{
    string out = "";
    out += this->playerName + ":";
    for (int i = 0; i < this->nrOfCourses; i++)
    {
        out += " " + to_string(this->results[i]);
    }
    return out;
}

int ResultColumn::totalResult() const
{
    int count = 0;
    for (int i = 0; i < nrOfCourses; i++)
    {
        count += this->results[i];
    }
    return count;
}

bool ResultColumn::addResult(int courseNr, int result)
{
    if (courseNr - 1 > this->nrOfCourses)
    {
        return false;
    }
    else if (this->results[courseNr - 1] != 10)
    {
        return false;
    }
    this->results[courseNr - 1] = result;
    return true;
}
