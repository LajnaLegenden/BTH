#include "BST.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>


template<typename T>
bool checkIfSorted(T arr[], int n)
{
	bool isSorted = true;
	int i;
	for (i = 0; (i < n - 1) && (arr[i] <= arr[i + 1]); i++);
	if (i < n - 1)
		isSorted = false;
	return isSorted;
}

void generateRandomNumbers(int*& arrPtr, int n, int lowerBound, int upperBound, unsigned int seed)
{
	srand(seed);
	arrPtr = new int[n];
	for (int i = 0; i < n; i++)
	{
		arrPtr[i] = rand() % (upperBound - lowerBound + 1) + lowerBound;
	}
}

bool contains(int arr[], int n, int  value) 
{
	bool unique = true;
	for (int i = 0; i < n && unique; i++)
		if (arr[i] == value)
			unique = false;
	return !unique;
}

void generateUniqueNumbers(int*& arrPtr, int n, unsigned int seed)
{
	srand(seed);
	arrPtr = new int[n];
	arrPtr[0] = rand() % n;
	for (int i = 1; i < n; i++)
	{
		arrPtr[i] = rand() % n;
		if (contains(arrPtr, i, arrPtr[i]))
			i--;
	}
}

void readFromFile(int*& arrPtr, int n)
{
	std::string filename = "unique" + std::to_string(n) + ".txt";

	std::ifstream in(filename);
	if (!in.is_open())
	{
		std::cout<<"Could not open file"<<filename<<std::endl;
	}
	else
	{
		arrPtr = new int[n];
		for (int i = 0; i < n; i++)
		{
			in >> arrPtr[i];
		}
		in.close();
	}
}

template<typename T>
void reverseTheOrder(T arr[], int n)
{
	for (int i = 0; i < n / 2; i++)
	{
		std::swap(arr[i], arr[n - 1 - i]);
	}
}

bool basicTesting()
{
	std::string e;
	
	const int CAP = 11;
	BST<int> bst;
	int arr[CAP]{ 45, 20, 36, 88, 10, 100, 50, 90, 96, 120 , 25 };

	for (auto elem : arr)
	{
		bst.insert(elem);
	}

	if (bst.nrOfNodes() != CAP)
	{
		e += "Not correct number of nodes\n";
	}
	if (bst.height() != 4)
	{
		e += "Not correct height\n";
	}
	if (bst.minimum() != 10)
	{
		e += "Not correct min value\n";
	}
	if (bst.maximum() != 120)
	{
		e += "Not correct max value ";
	}

	int preArr[]{ 45, 20, 10, 36, 25, 88, 50, 100, 90, 96, 120 };
	int postArr[]{ 10, 25, 36, 20, 50, 96, 90, 120, 100, 88, 45 };

	std::vector<int> nrs;
	int capacity = 11;

	bst.preorder(nrs);
	bool ok = true;
	for (int i = 0; i < capacity && ok; i++)
	{
		if (nrs[i] != preArr[i])
		{
			e += "Preorder did not result in correct order\n";
			ok = false;
		}
	}

	nrs.clear();
	bst.postorder(nrs);
	ok = true;
	for (int i = 0; i < capacity && ok; i++)
	{
		if (nrs[i] != postArr[i])
		{
			e+= "Postorder did not result in correct order\n";
			ok = false;
		}
	}

	if (e != "")
		throw e;

	return true;
}

bool firstRemoveTest()
{
	std::string e;
	const int CAP = 13;
	BST<int> bst;
	int arr[CAP]{ 45, 20, 36, 88, 10, 100, 50, 90, 96, 120 , 25, 5, 60 };

	for (auto elem : arr)
	{
		bst.insert(elem);
	}

	int nrOfNodes = CAP;
	bst.remove(5);
	nrOfNodes--;

	if (bst.nrOfNodes() != nrOfNodes)
		e+= "Not correct nr of nodes after removing a leaf node\n";

	bst.remove(36);
	nrOfNodes--;
	if (bst.nrOfNodes() != nrOfNodes)
		e += "Not correct nr of nodes after removing a node with only left child\n";

	bst.remove(50);
	nrOfNodes--;
	if (bst.nrOfNodes() != nrOfNodes)
		e += "Not correct nr of nodes after removing a node with only right child\n";

	bst.remove(88);
	nrOfNodes--;
	if (bst.nrOfNodes() != nrOfNodes)
		e += "Not correct nr of nodes after removing a node with two children\n";

	if (e != "")
		throw  e;

	return true;
}

bool secondRemoveTest()
{
	std::string e;
	
	const int CAP = 11;
	BST<int> bst;
	int arr[CAP]{ 45, 20, 36, 88, 10, 100, 50, 90, 96, 120 , 25 };

	for (auto elem : arr)
	{
		bst.insert(elem);
	}


	for (auto elem : arr)
	{
		bst.remove(elem);
	}

	if (bst.nrOfNodes() != 0)
		e+= "Tree not empty (nr of nodes = 0) after removing all elements\n";

	for (auto elem : arr)
	{
		bst.insert(elem);
	}

	bst.remove(96);
	if (bst.height() != 3)
		e += "Not correct height after removing a leaf that effects the height\n";

	bst.remove(50);
	bst.remove(45);
	bst.remove(88);
	bst.remove(20);

	if (bst.height() != 2)
		e += "Not correct height after removing some nodes\n";
	if (e != "")
		throw e;

	return true;
}

bool moreTesting()
{
	std::string e;

	int smallArr[]{ 3, 2, 1, 2, 3, 4, 5 };
	BST<int> bstSmall;

	for (auto elem : smallArr)
		bstSmall.insert(elem);

	for (auto elem : smallArr)
		bstSmall.remove(elem);

	if (bstSmall.nrOfNodes() != 0)
		e += "After removing all elements including duplicates the tree should be empty";

	bstSmall.insert(77);
	if (bstSmall.nrOfNodes() != 1)
		e += "After removing all elements and then adding one element the nrOfNodes should be 1";
	
	int arr[]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	BST<int> bst;

	for (auto elem : arr)
	{
		bst.insert(elem);
	}

	if (bst.height() != 9)
		e += "Not correct height when inserting the same value more than once\n";

	bool ok = true;
	int height = bst.height();
	while (bst.nrOfNodes() > 0 && ok)
	{
		bst.remove(1);
		height--;
		if (bst.height() != height)
		{
			e += "Trouble removing elements that occurs more than once\n";
			ok = false;
		}
	}

	if (e != "")
		throw e;
	return true;
}

bool pathTesting()
{
	std::string e;
	BST<int> bst;
	std::vector<int> nrs{ 71, 15, 56, 26, 29, 5, 89, 198, 68, 90, 153, 200, 195, 95, 18, 136, 107, 60, 199, 48, 39, 147, 124, 165, 44 };

	for (int i = 0; i < 25; i++)
	{
		bst.insert(nrs[i]);
	}
	bst.insert(66);
	std::vector<int> pathVector{ 71, 15, 56, 68, 60, 66};
	std::vector<int> vector;
	vector = bst.path(66);
	


	if (pathVector != vector)
	{
		e += "Path from root to 66 is not correct\n";
	}
	pathVector.clear();
	pathVector = { 71, 15, 56, 26, 29, 48, 39};
	vector = bst.path(39);
	if (pathVector != vector)
	{
		e += "Path from root to 39 is not correct\n";
	}
	if (e != "")
		throw e;
	return true;
}

bool finalInsertAndHeightTesting(int n)
{
	std::string e;
	int* nrs = nullptr;

	readFromFile(nrs, n);
	BST<int> bst;
	for (int i = 0; i < n; i++)
	{
		bst.insert(nrs[i]);
	}
	if ((n == 127 && (bst.height() != 14)) ||
		(n == 147 && (bst.height() != 16)) ||
		(n == 167 && (bst.height() != 14)) ||
		(n == 187 && (bst.height() != 14)) ||
		(n == 207 && (bst.height() != 13)))
	{
		e += "Not correct height for " + std::to_string(n) + " elements\n";
	}
	for (int i = 0; i < n; i++)
	{
		bst.remove(nrs[i]);
	}
	delete[] nrs;

	if (e != "")
		throw e;
	return true;
}

int main()
{
	int okCount = 0;
	bool ok = true;
	try 
	{
		basicTesting();
		okCount++;
		std::cout << "Basic test ok\n" << std::endl;
	}
	catch (std::string e)
	{
		std::cout<<"Exception " + e;
		ok = false;
	}
	if (ok)
	{
		try
		{
			firstRemoveTest();
			okCount++;
			std::cout << "First remove test ok\n" << std::endl;
		}
		catch (std::string e)
		{
			std::cout << "Exception " + e;
			ok = false;
		}
	}
	if (ok)
	{
		try
		{
			secondRemoveTest();
			okCount++;
			std::cout << "Second remove test ok\n" << std::endl;
		}
		catch (std::string e)
		{
			std::cout << "Exception " + e;
			ok = false;
		}
	}
	if (ok)
	{
		try
		{
			moreTesting();
			okCount++;
			std::cout << "More testing ok\n" << std::endl;
		}
		catch (std::string e)
		{
			std::cout << "Exception " + e;
			ok = false;
		}
	}
	if (ok)
	{
		try
		{
			pathTesting();
			okCount++;
			std::cout << "Pathtesting ok\n" << std::endl;
		}
		catch (std::string e)
		{
			std::cout << "Exception " + e;
			ok = false;
		}
	}
	if (ok)
	{
		try
		{
			int test = 0;
			for (int i = 0; i < 5; i++)
			{
				finalInsertAndHeightTesting(127 + i * 20);
				okCount++;
				test++;
			}
			if (test == 5)
				std::cout << "Final testing ok\n" << std::endl;
		}
		catch (std::string e)
		{
			std::cout << e;
			ok = false;
		}
	}
	if (okCount != 10)
	{
		std::cout << "Some tests did not pass\n";
		std::cout << "The first " << okCount << " of 10 tests did pass\n";
		std::cout << "It remains " << 10 - okCount << " tests\n";
	}
	else
		std::cout << "All tests did pass\n";

	
	return 10-okCount;
}