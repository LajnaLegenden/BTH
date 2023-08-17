#include <iostream>

#include "assembler.hpp"
#include <vector>
using namespace std;

vector<string> getInput()
{
	string input;
	printf("> ");
	getline(cin, input);
	int pos = 0;
	cout <<input<<endl;
	vector<string> parsedLine;
	if (input.find((char)32) != string::npos)
	{
		while (input.find((char)32) != string::npos)
		{
			pos = input.find((char)32);
			// Pushback the pare before space
			parsedLine.push_back(input.substr(0, pos));
			//Remove everything including next space
			input.erase(0, pos + 1);
		}
		parsedLine.push_back(input);
	}
	else
	{
		parsedLine.push_back(input);
	}
cout << input[1]<< endl;
	return parsedLine;
}

int main()
{
	int registers[REGISTER_SIZE] = {0};

	bool running = true;
	while (running)
	{
		vector<string> input = getInput();
		if (input[0] == "run")
		{
			vector<vector<string>> commandList;
			BuildCommandList(commandList, input[1]);
			cout << "Commandlist leght: " << commandList.size()<<endl;
			while (PeekNextCommandIndex(registers) < commandList.size())
			{
				vector<string> command = commandList[GetAndStepCommandIndex(registers)];

				if (command[0] == "MOV")
				{
					MOV(command, registers);
				}
				else if (command[0] == "ADD")
				{
					ADD(command, registers);
				}
				else if (command[0] == "SUB")
				{
					SUB(command, registers);
				}
				else if (command[0] == "JEQ")
				{
					JEQ(command, registers);
				}
				else if (command[0] == "JLT")
				{
					JLT(command, registers);
				}
				else if (command[0] == "JGT")
				{
					JGT(command, registers);
				}
				cout << ".";
			}

			for(int i  = 0; i < REGISTER_SIZE; i++){
				cout << registers[i] << " ";
			}
			cout << endl;
		}
		else if (input[0] == "exit")
		{
			cout << "Goodbye!" << endl;
			running = false;
		}
		else
		{
			cout << "Invalid command, use either exit, or run [filename] [registry]?" << endl;
		}
	}
	return 0;
}