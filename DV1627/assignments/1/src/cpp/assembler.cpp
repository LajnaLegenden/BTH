#include "assembler.hpp"
#include <fstream>
#include <iostream>
using namespace std;
// ------------------------------------- //

		/* ---------------------- *\
			Add your code here


		Create needed fuction definitions
		for the functions declared in the
		header file 'assembler.hpp'.

		You may implement help functions.
		These may not be defined in the
		header file.
		\* ---------------------- */

		// ------------------------------------- //


int getContant(string reg) {
	return stoi(reg.substr(1, reg.length() - 1));
}

int getRegIndex(string reg) {
	// using + "" to make sure it is a string
	auto chars = reg[1];
	return stoi(string(1, chars));
}

bool isReg(string instuction) {
	return instuction[0] == 'R';
}

int extractValue(string source, int registers[]) {
	if (isReg(source)) {
		return registers[getRegIndex(source)];
	}
	else {
		return getContant(source);
	}
}


bool BuildCommandList(vector<vector<string>>& commandList, string filepath)
{
	commandList.clear();
	try {
		ifstream asmFile(filepath);
		if (asmFile.good()) {
			vector<string> instruction;
			int pos = 0;
			for (string line; getline(asmFile, line); )
			{
				if (line.empty()) continue;
				instruction.clear();
				// 32 is space char code
				while (line.find((char)32) != string::npos) {
					pos = line.find((char)32);
					// Pushback the pare before space
					instruction.push_back(line.substr(0, pos));
					//Remove everything including next space
					line.erase(0, pos + 1);
				}
				//Add last one too
				instruction.push_back(line);

				commandList.push_back(instruction);
			}
			asmFile.close();
			return true;
		}
		else {
			cout << "Somethignwent wront"<< endl;
			return false;
		}
	}
	catch (exception e) {
		return false;
	}
}

int PeekNextCommandIndex(int registers[])
{
	return registers[REGISTER_SIZE - 1];
}

int GetAndStepCommandIndex(int registers[])
{
	int index = registers[REGISTER_SIZE - 1];
	registers[REGISTER_SIZE - 1] += 1;
	return index;
}

void MOV(std::vector<std::string>& command, int registers[])
{
	int destIndex = getRegIndex(command[1]);
	int value = extractValue(command[2], registers);
	registers[destIndex] = value;
}

void ADD(std::vector<std::string>& command, int registers[])
{
	int destIndex = getRegIndex(command[1]);
	int term1 = extractValue(command[2], registers);
	int term2 = extractValue(command[3], registers);
	registers[destIndex] = term1 + term2;
}

void SUB(std::vector<std::string>& command, int registers[])
{
	int destIndex = getRegIndex(command[1]);
	int term1 = extractValue(command[2], registers);
	int term2 = extractValue(command[3], registers);
	registers[destIndex] = term1 - term2;
}

void JEQ(std::vector<std::string>& command, int registers[])
{
	int value1 = extractValue(command[1], registers);
	int value2 = extractValue(command[2], registers);
	if (value1 == value2) {
		int step = extractValue(command[3], registers) - 1;
		registers[REGISTER_SIZE - 1] += step;
	}
}

void JGT(std::vector<std::string>& command, int registers[])
{
	int value1 = extractValue(command[1], registers);
	int value2 = extractValue(command[2], registers);
	if (value1 > value2) {
		int step = extractValue(command[3], registers) - 1;
		registers[REGISTER_SIZE - 1] += step;
	}
}

void JLT(std::vector<std::string>& command, int registers[])
{
	int value1 = extractValue(command[1], registers);
	int value2 = extractValue(command[2], registers);
	if (value1 < value2) {
		int step = extractValue(command[3], registers) - 1;
		registers[REGISTER_SIZE - 1] += step;
	}
}
