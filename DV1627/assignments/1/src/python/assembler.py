import sys

# Number of registers this implementation support
REGISTER_SIZE = 8

##################################
#### 'PRIVATE' HELP FUNCTIONS ####
##################################

def GetRegIndex(reg : str):
	# Examples of reg strings
	# "R0" : return 0
	# "R1" : return 1
	# Return the second character as an integer
	# Registers only has a single digit
	return int(reg[1])

def GetConstant(const : str):
	# Examples of reg strings
	# "#5" : return 5
	# "#17" : return 17
	# "#-1" : return -1
	# Remove the '#' character,
	# convert rest of string to an integer
	return int(const[1:])

def IsReg(term : str):
	return term[0] == 'R'

def ExtractValue(source : str, registers : list):
	# Check if register or constant
	# If register, return value in that register
	# If constant, return the constant value
	if IsReg(source):
		return registers[GetRegIndex(source)]
	return GetConstant(source)



##################################
###### EXPOSED ASSEMBLER API #####
##################################

# General command construction and reading

def BuildCommandList(commands : list, filepath : str):

	# Clear previous values (if any)
	commands.clear()

	# Check if possible to open file
	try:
		file = open(filepath, 'r')
	except FileNotFoundError:
		return False

	# Read each line from file.
	# For each line:
	# 1. Remove new-line character (if any)
	# 2. Convert into command format
	# 3. Append to command list
	for line in file:
		line = line.replace('\n','')

		# Read only non-empty lines
		if len(line) != 0:		
			line = line.split()				
			commands.append(line)
	file.close()

	# If this is reached,
	# the build is completed
	return True

def PeekNextCommandIndex(registers : list):
	return registers[REGISTER_SIZE-1]

def GetAndStepCommandIndex(registers : list):
	index = registers[REGISTER_SIZE-1]
	registers[REGISTER_SIZE-1] += 1
	return index

# Assignment intructions

def MOV(command : list, registers : list):
	destIndex = GetRegIndex(command[1])
	value = ExtractValue(command[2], registers)
	registers[destIndex] = value

# Arithmetic instructions

def ADD(command : list, registers : list):
	destIndex = GetRegIndex(command[1])
	term1 = ExtractValue(command[2], registers)
	term2 = ExtractValue(command[3], registers)
	registers[destIndex] = term1 + term2

def SUB(command : list, registers : list):
	destIndex = GetRegIndex(command[1])
	term1 = ExtractValue(command[2], registers)
	term2 = ExtractValue(command[3], registers)
	registers[destIndex] = term1 - term2

# Jump instructions

def JEQ(command : list, registers : list):
	value1 = ExtractValue(command[1], registers)
	value2 = ExtractValue(command[2], registers)
	if value1 == value2:
		# -1 is needed to counter the step command
		step = ExtractValue(command[3], registers) - 1
		registers[REGISTER_SIZE-1] += step

def JGT(command : list, registers : list):
	value1 = ExtractValue(command[1], registers)
	value2 = ExtractValue(command[2], registers)
	if value1 > value2:
		# -1 is needed to counter the step command
		step = ExtractValue(command[3], registers) - 1
		registers[REGISTER_SIZE-1] += step

def JLT(command : list, registers : list):
	value1 = ExtractValue(command[1], registers)
	value2 = ExtractValue(command[2], registers)
	if value1 < value2:
		# -1 is needed to counter the step command
		step = ExtractValue(command[3], registers) - 1
		registers[REGISTER_SIZE-1] += step