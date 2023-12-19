#ifndef RESULT_COLUMN_HPP
#define RESULT_COLUMN_HPP

#include <string>
using namespace std;
class ResultColumn
{
private:
	static const int NO_RESULT = 10;
private:
	string playerName;
	int* results;
	int nrOfCourses;
public:
	ResultColumn(string playerName, int nrOfCourses);
	ResultColumn(const ResultColumn& origin);
	ResultColumn& operator=(const ResultColumn& origin);
	~ResultColumn();
	bool addResult(int courseNr, int result);
	string getPlayerName() const;
	string toString() const;
	int totalResult() const;
};
#endif
