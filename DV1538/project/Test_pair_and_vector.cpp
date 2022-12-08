#include <utility>
#include <vector>
#include <string>
#include <iostream>

int main()
{
	std::pair<int, std::string> aPair;
	aPair.first = 1;
	aPair.second = "one";

	std::cout << aPair.first << " , " << aPair.second << std::endl;

	std::vector<std::pair<int, std::string>> testVect;
	testVect.push_back(aPair);
	aPair.first = 2;
	aPair.second = "two";
	testVect.push_back(aPair);
	aPair.first = 3;
	aPair.second = "three";
	testVect.push_back(aPair);
	std::cout << std::endl << std::endl;
	for (auto pair : testVect)
	{
		std::cout << pair.first << " , " << pair.second << std::endl;
	}

	testVect[1].second = "TWO";

	return 0;
}