//main.cpp
//ECE 5367 MIPS Unpiplined Processor Simulator

#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;
//Check list of things to finish code:
//	The timing of the instruction sequence should show cycle numbers in rows, while columns should be labeled with instruction numbers aspect 
//	output file formating

int strToInt(string number){
	int stringSize = number.size();
	int returnVal = 0;
	for(int i = 0; i < stringSize; i++)
	{
		returnVal += (number[i] - 48) * pow(10, (stringSize - i - 1)); 
	}
	return returnVal;
}
int binaryStrToInt(string number)
{
	int stringSize = number.size();
	int returnVal = 0;
	for(int i = 0; i < stringSize; i++)
	{
		returnVal += (number[i] - 48) * pow(2, (stringSize - i - 1));
	}
	return returnVal;
}

struct registerNode
{
	int registerNumber, registerContent;
	registerNode *next;
};
struct memoryNode
{
	int memoryLocation, memoryContents;
	memoryNode *next;
};
struct codeNode
{
	string binaryCode;
	codeNode *next;
};

class MIPS
{
private:
	registerNode *registerHead = NULL;
	memoryNode *memoryHead = NULL;
	codeNode *codeHead = NULL;
public:
	void appendRegisterNode(int registerNum, int registerCon)
	{
		registerNode *cu, *temp;
    	temp = new registerNode;
    	temp -> registerNumber = registerNum;
    	temp -> registerContent = registerCon;
    	temp -> next = NULL;
    	if(registerHead == NULL)
    	{
        	registerHead = temp;
    	}
   		else
   		{
        	cu = registerHead;
        	while(cu -> next != NULL)
        	{
            	cu = cu -> next;
        	}
        	cu -> next = temp;
    	}
	};
	void appendMemoryNode(int memLoc, int memCon)
	{
		memoryNode *cu, *temp;
    	temp = new memoryNode;
    	temp -> memoryLocation = memLoc;
    	temp -> memoryContents = memCon;
    	temp -> next = NULL;
    	if(memoryHead == NULL)
    	{
        	memoryHead = temp;
    	}
   		else
   		{
        	cu = memoryHead;
        	while(cu -> next != NULL)
        	{
            	cu = cu -> next;
        	}
        	cu -> next = temp;
    	}
	};
	void appendCodeNode(string codeLine)
	{
		codeNode *cu, *temp;
    	temp = new codeNode;
    	temp -> binaryCode = codeLine;
    	temp -> next = NULL;
    	if(codeHead == NULL)
    	{
        	codeHead = temp;
    	}
   		else
   		{
        	cu = codeHead;
        	while(cu -> next != NULL)
        	{
            	cu = cu -> next;
        	}
        	cu -> next = temp;
    	}
	};
	void printRegisterList()
	{
		registerNode *cu;
		cu = registerHead;
		while(cu != NULL)
		{
			cout << cu -> registerNumber << " " << cu -> registerContent << endl;
			cu = cu -> next;
		}
	};
	void printMemoryList()
	{
		memoryNode *cu;
		cu = memoryHead;
		while(cu != NULL)
		{
			cout << cu -> memoryLocation << " " << cu -> memoryContents << endl;
			cu = cu -> next;
		}
	};
	void printCodeList()
	{
		codeNode *cu;
		cu = codeHead;
		while(cu != NULL)
		{
			cout << cu -> binaryCode << endl;
			cu = cu -> next;
		}
	};
	void executeCode(string outputFile)
	{
		ofstream ols;
		ols.open(outputFile);

		codeNode *cuCode;
		registerNode *cuReg;
		memoryNode *cuMem;
		cuCode = codeHead;
		int linesExecuted = 1;
		int instructionSubCount = 1;
		while(cuCode != NULL)
		{
			string opcode, sourceRegister, targetRegister, destinationRegister, shiftAmount, function, offset, codeLine;
			int opcodeNum, sourceRegisterNum, targetRegisterNum, destinationRegisterNum, shiftAmountNum, functionNum, offsetNum;
			codeLine = cuCode -> binaryCode;
			for(int i = 0; i < 6; i++)
			{
				opcode += codeLine[i];
			}
			opcodeNum = binaryStrToInt(opcode);
			//will need to write code part to output file in if statements need to figure out how IF,ID, EX, MEM, and WB work first
			if(opcodeNum == 0)
			{
				//I know the instruction is of R type
				for(int i = 6; i < 11; i++)
				{
					//this tells me the source register
					sourceRegister += codeLine[i];

				}
				sourceRegisterNum = binaryStrToInt(sourceRegister);
				for(int i = 11; i < 16; i++)
				{
					//this tells me the target register
					targetRegister += codeLine[i];
				}
				targetRegisterNum = binaryStrToInt(targetRegister);
				for(int i = 16; i < 21; i++)
				{
					destinationRegister += codeLine[i];
				}
				destinationRegisterNum = binaryStrToInt(destinationRegister);
				for(int i = 21; i < 26; i++)
				{
					//this tells me the shift amount (usually and hopefully always zero)
					shiftAmount += codeLine[i];
				}
				shiftAmountNum = binaryStrToInt(shiftAmount);
				for(int i = 26; i < 32; i++)
				{
					//this tells the function to carry out
					function += codeLine[i];
				}
				functionNum = binaryStrToInt(function);
				//if to go to the appropriate function
				if(functionNum == 32)
				{
					//function to be carried out is addition
					add(sourceRegisterNum, targetRegisterNum, destinationRegisterNum);
					//Write to output file here
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-IF" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-ID" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-EX" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-WB" << endl;
					instructionSubCount++;
				}
				else if(functionNum == 34)
				{
					//function to be carried out is subtraction
					sub(sourceRegisterNum, targetRegisterNum, destinationRegisterNum);
					//write to output file here
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-IF" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-ID" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-EX" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-WB" << endl;
					instructionSubCount++; 
				}
				else if(functionNum == 42)
				{
					//function to be carried out is set less than
					slt(sourceRegisterNum, targetRegisterNum, destinationRegisterNum);
					//write to output file here
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-IF" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-ID" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-EX" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-WB" << endl;
					instructionSubCount++;
				}
				else
				{
					//Function is not one of 8 executable by this program, should not be an issue but may want to output an error or a simple message
				}
			}
			else
			{
				//I know the instruction is of I type
				for(int i = 6; i < 11; i++)
				{
					sourceRegister += codeLine[i];
				}
				sourceRegisterNum = binaryStrToInt(sourceRegister);
				for(int i = 11; i < 16; i++)
				{
					destinationRegister += codeLine[i];
				}
				destinationRegisterNum = binaryStrToInt(destinationRegister);
				for(int i = 16; i < 32; i++)
				{
					offset += codeLine[i];
				}
				offsetNum = binaryStrToInt(offset);
				if(opcodeNum == 35)
				{
					//call loadWord function
					loadWord(sourceRegisterNum, destinationRegisterNum, offsetNum);
					//write to output file here
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-IF" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-ID" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-EX" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-MEM" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-WB" << endl;
					instructionSubCount++;
				}
				else if(opcodeNum == 43)
				{
					//call storeWord function
					storeWord(sourceRegisterNum, destinationRegisterNum, offsetNum);
					//write to output file here
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-IF" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-ID" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-EX" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-MEM" << endl;
					instructionSubCount++;
				}
				else if(opcodeNum == 8)
				{
					//call addI function
					addI(sourceRegisterNum, destinationRegisterNum, offsetNum);
					//write to output file here FIX THIS 
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-IF" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-ID" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-EX" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-WB" << endl;
					instructionSubCount++;
				}
				else if(opcodeNum == 4)
				{
					//call beq function
					if(sourceRegisterNum == destinationRegisterNum)
					{
						for(int i = 0; i < offsetNum; i++)
						{
							cuCode = cuCode -> next;
						}
					}
					//write to output file here
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-IF" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-ID" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-EX" << endl;
					instructionSubCount++;
				}
				else if(opcodeNum == 5)
				{
					//call bne function
					if(sourceRegisterNum != destinationRegisterNum)
					{
						for(int i = 0; i < offsetNum; i++)
						{
							cuCode = cuCode -> next;
						}
					}
					//write to output file here 
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-IF" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-ID" << endl;
					instructionSubCount++;
					ols << "C#" << instructionSubCount << " I" << linesExecuted << "-EX" << endl;
					instructionSubCount++;
				}
			}
			cuCode = cuCode -> next;
			linesExecuted++;
		}
		cuReg = registerHead;
		sortRegisters(cuReg);
		ols << "REGISTERS" << endl;
		while(cuReg != NULL)
		{
			ols << "R" << cuReg -> registerNumber << " " << cuReg -> registerContent << endl;
			cuReg = cuReg -> next;
		}
		cuMem = memoryHead;
		sortMemory(cuMem);
		ols << "MEMORY" << endl;
		while(cuMem != NULL)
		{
			ols << cuMem -> memoryLocation << " " << cuMem -> memoryContents << endl;
			cuMem = cuMem -> next;
		}
		ols.close();
	};
	//I type instruction functions
	void loadWord(int sourceRegister, int destinationRegister, int offset)
	{
		//need to access memory list here
		int memLocation, sourceContent, destinationContent;
		bool destinationExists = false; 
		registerNode *cuRegister = registerHead;
		memoryNode *cuMemory = memoryHead;
		while(cuRegister != NULL)
		{
			if(cuRegister -> registerNumber == sourceRegister)
			{
				sourceContent = cuRegister -> registerContent;
			}
			if(cuRegister -> registerNumber == destinationRegister)
			{
				destinationExists = true;
			}
			cuRegister = cuRegister -> next;
		}
		memLocation = sourceContent + offset;
		while(cuMemory != NULL)
		{
			if(cuMemory -> memoryLocation == memLocation)
			{
				destinationContent = cuMemory -> memoryContents;
				break;
			}
			cuMemory = cuMemory -> next;
		}
		//place memory contents in destination register
		if(destinationExists == true)
		{
			cuRegister = registerHead;
			while(cuRegister != NULL)
			{
				if(cuRegister -> registerNumber == destinationRegister)
				{
					cuRegister -> registerContent = destinationContent;
					break;
				}
				cuRegister = cuRegister -> next;
			}
		}
		else
		{
			//destination does not exist, create and place accordingly
			appendRegisterNode(destinationRegister, destinationContent);
		}
	};
	void storeWord(int sourceRegister, int destinationRegister, int offset)
	{
		//need to access memory list here
		int memLocation, sourceContent, destinationContent;
		bool memoryExists = false; 
		registerNode *cuRegister = registerHead;
		memoryNode *cuMemory = memoryHead;
		while(cuRegister != NULL)
		{
			if(cuRegister -> registerNumber == sourceRegister)
			{
				sourceContent = cuRegister -> registerContent;
			}
			if(cuRegister -> registerNumber == destinationRegister)
			{
				destinationContent = cuRegister -> registerContent;
			}
			cuRegister = cuRegister -> next;
		}
		memLocation = offset + sourceContent;
		while(cuMemory != NULL)
		{
			if(cuMemory -> memoryLocation == memLocation)
			{
				memoryExists = true;
				cuMemory -> memoryContents = destinationContent; 
				break;
			}
			cuMemory = cuMemory -> next;
		}
		if(memoryExists == false)
		{
			appendMemoryNode(memLocation, destinationContent);
		}
	};
	void addI(int sourceRegister, int destinationRegister, int immediate)
	{
		int sourceContent, destinationContent;
		bool destinationExists = false;
		registerNode *cu = registerHead;
		while(cu != NULL)
		{
			if(cu -> registerNumber == sourceRegister)
			{
				sourceContent = cu -> registerContent;
			}
			if(cu -> registerNumber == destinationRegister)
			{
				destinationExists = true;
			}
			cu = cu -> next;
		}
		destinationContent = sourceContent + immediate;
		if(destinationExists == true)
		{
			cu = registerHead;
			while(cu != NULL)
			{
				if(cu -> registerNumber == destinationRegister)
				{
					cu -> registerContent = destinationContent;
					break;
				}
				cu = cu -> next;
			}
		}
		else
		{
			appendRegisterNode(destinationRegister, destinationContent);
		}
	};
	//R type instruction functions
	void add(int sourceRegister, int targetRegister, int destinationRegister)
	{
		int sourceContent, targetContent, destinationContent;
		bool destinationExists = false;
		//need to check list if destination register exists if not new node must be created
		registerNode *cu = registerHead;
		while(cu != NULL)
		{
			if(cu -> registerNumber == sourceRegister)
			{
				sourceContent = cu -> registerContent;
			}
			if(cu -> registerNumber == targetRegister)
			{
				targetContent = cu -> registerContent;
			}
			if(cu -> registerNumber == destinationRegister)
			{
				destinationExists = true;
			}
			cu = cu -> next;
		}
		destinationContent = sourceContent + targetContent;
		if(destinationExists == true)
		{
			//overwrite addition calculation in existing register
			registerNode *cuR;
			cuR = registerHead;
			while(cuR != NULL)
			{
				if(cuR -> registerNumber == destinationRegister)
				{
					cuR -> registerContent = destinationContent;
					break;
				}
				cuR = cuR -> next;
			}
		}
		else
		{
			//destination does not exist, create and place accordingly
			appendRegisterNode(destinationRegister, destinationContent);
		}
	};
	void sub(int sourceRegister, int targetRegister, int destinationRegister)
	{
		int sourceContent, targetContent, destinationContent;
		bool destinationExists = false;
		//need to check list if destination register exists if not new node must be created
		registerNode *cu = registerHead;
		while(cu != NULL)
		{
			if(cu -> registerNumber == sourceRegister)
			{
				sourceContent = cu -> registerContent;
			}
			if(cu -> registerNumber == targetRegister)
			{
				targetContent = cu -> registerContent;
			}
			if(cu -> registerNumber == destinationRegister)
			{
				destinationExists = true;
			}
			cu = cu -> next;
		}
		//destinationContent = sourceContent - targetContent;
		if(destinationExists == true)
		{
			//overwrite addition calculation in existing register
			registerNode *cuR;
			cuR = registerHead;
			while(cuR != NULL)
			{
				if(cuR -> registerNumber == destinationRegister)
				{
					cuR -> registerContent = destinationContent;
					break;
				}
				cuR = cuR -> next;
			}
		}
		else
		{
			//destination does not exist, create and place accordingly
			appendRegisterNode(destinationRegister, destinationContent);
		}
	};
	void slt(int sourceRegister, int targetRegister, int destinationRegister)
	{
		//going to do this function last need to know how it works first
		int sourceContent, targetContent, destinationContent;
		bool destinationExists = false;
		//need to check list if destination register exists if not new node must be created
		registerNode *cu = registerHead;
		while(cu != NULL)
		{
			if(cu -> registerNumber == sourceRegister)
			{
				sourceContent = cu -> registerContent;
			}
			if(cu -> registerNumber == targetRegister)
			{
				targetContent = cu -> registerContent;
			}
			if(cu -> registerNumber == destinationRegister)
			{
				destinationExists = true;
			}
			cu = cu -> next;
		}
		//compare source and target values here
		//if source is less than target: destination = 0 else destination = 1
		if(sourceContent < targetContent)
		{
			destinationContent = 0;
		}
		else
		{
			destinationContent = 1;
		}
		if(destinationExists == true)
		{
			//overwrite addition calculation in existing register
			registerNode *cuR;
			cuR = registerHead;
			while(cuR != NULL)
			{
				if(cuR -> registerNumber == destinationRegister)
				{
					cuR -> registerContent = destinationContent;
					break;
				}
				cuR = cuR -> next;
			}
		}
		else
		{
			//destination does not exist, create and place accordingly
			appendRegisterNode(destinationRegister, destinationContent);
		}
	};
	//Sorting functions
	void sortRegisters(registerNode *start)
	{
		//need to fix this
		int swapped, i; 
    	struct registerNode *ptr1; 
    	struct registerNode *lptr = NULL; 
  
    	/* Checking for empty list */
    	if (start == NULL) 
        	return; 
  
    	do
    	{ 
        	swapped = 0; 
        	ptr1 = start; 
  
        	while (ptr1->next != lptr) 
        	{ 
            	if (ptr1 -> registerNumber > ptr1 -> next -> registerNumber) 
            	{  
                	swapRegister(ptr1, ptr1 -> next); 
                	swapped = 1; 
            	} 
            	ptr1 = ptr1 -> next; 
        	} 
        	lptr = ptr1; 
    	} 
    	while (swapped);
	};
	void sortMemory(memoryNode *start)
	{
		int swapped, i; 
    	struct memoryNode *ptr1; 
    	struct memoryNode *lptr = NULL; 
  
    	/* Checking for empty list */
    	if (start == NULL) 
        	return; 
  
    	do
    	{ 
        	swapped = 0; 
        	ptr1 = start; 
  
        	while (ptr1->next != lptr) 
        	{ 
            	if (ptr1 -> memoryLocation > ptr1 -> next -> memoryLocation) 
            	{  
                	swapMemory(ptr1, ptr1 -> next); 
                	swapped = 1; 
            	} 
            	ptr1 = ptr1 -> next; 
        	} 
        	lptr = ptr1; 
    	} 
    	while (swapped);
	};
	void swapRegister(registerNode *a, registerNode *b)
	{
		int temp = a -> registerNumber;
		int temp2 = a -> registerContent; 
    	a -> registerNumber = b -> registerNumber; 
    	a -> registerContent = b -> registerContent;
    	b -> registerNumber = temp;
    	b -> registerContent = temp2;
	};
	void swapMemory(memoryNode *a, memoryNode *b)
	{
		int temp = a -> memoryLocation;
		int temp2 = a -> memoryContents; 
    	a -> memoryLocation = b -> memoryLocation; 
    	a -> memoryContents = b -> memoryContents;
    	b -> memoryLocation = temp;
    	b -> memoryContents = temp2;
	};
};

void mipsProcessor(string inputFileName, string outputFileName)
{
	ifstream ils(inputFileName);
	int indicator = 0, regCount, memoryCount, codeCount;
	string line;
	MIPS processor;
	while(getline(ils, line))
	{
		if(line == "REGISTERS")
		{
			indicator = 1;
			regCount = 0;
		}
		else if(line == "MEMORY")
		{
			indicator = 2;
			memoryCount = 0;
		}
		else if(line == "CODE")
		{
			indicator = 3;
			codeCount = 0;
		}
		if(indicator == 1)
		{
			string regNum, regCon;
			int lineSize = line.size();
			int changeStringFlag = 0;
			for(int i = 0; i < lineSize; i++)
			{
				if(regCount == 0)
				{
					//do nothing
				}
				else
				{
					if(line[i] == ' ')
					{
						changeStringFlag = 1;
					}
					if(changeStringFlag == 0)
					{
						if(line[i] == 'R')
						{
							//do nothing
						}
						else
						{
							regNum += line[i];
						}
					}
					else
					{
						if(line[i] == ' ')
						{
							//do nothing, don't want to append blank space to string
						}
						else
						{
							regCon += line[i];
						}
					}
				}
			}
			if(regCount != 0)
			{
				int regNumber = strToInt(regNum); 
				int regContent = strToInt(regCon);
				processor.appendRegisterNode(regNumber, regContent);
			}
			regCount++;
		}
		else if(indicator == 2)
		{
			string memNum, memCon;
			int lineSize = line.size();
			int changeStringFlag = 0;
			for(int i = 0; i < lineSize; i++)
			{
				if(line[i] == ' ')
				{
					changeStringFlag = 1;
				}
				if(changeStringFlag == 0)
				{
						memNum += line[i];
				}
				else
				{
					if(line[i] == ' ')
					{
						//do nothing, don't want to append blank space to string
					}
					else
					{
						memCon += line[i];
					}
				}
			}
			if(memoryCount != 0)
			{
				int memNumber = strToInt(memNum); 
				int memContent = strToInt(memCon);
				processor.appendMemoryNode(memNumber, memContent);
			}
			memoryCount++;
		}
		else if(indicator == 3)
		{
			if(codeCount != 0)
			{
				processor.appendCodeNode(line);
			}
			codeCount++;
		}
	}
	// processor.printRegisterList();
	// processor.printMemoryList();
	// processor.printCodeList();
	// cout << endl;
	// //call code execution
	// processor.executeCode(outputFileName);
	// cout << endl << "REGISTERS" << endl;
	// processor.printRegisterList();
	// cout << "MEMORY" << endl;
	// processor.printMemoryList();

	ils.close();
}

int main(int argc, char* argv[])
{
	int repeat = 1;
	while(repeat == 1)
	{
		//This part of the code takes input and output file names
		string input, output;
		cout << "Please enter the name of the input file: ";
		cin >> input;
		cout << "Please enter the name of the output file: ";
		cin >> output;

		//going to read file and write output in function file
		mipsProcessor(input, output);

		//This part of the code checks if the user would like to run the program again
		char runAgain;
		int notValid = 1;
		cout << "Would you like to run the MIPS Unpiplined Processor Simulator again? (Y/N): ";
		cin >> runAgain;
		cout << endl;
		while(notValid == 1)
		{
			if(runAgain == 'Y')
			{
				repeat = 1;
				notValid = 0;
			}
			else if(runAgain == 'N')
			{
				repeat = 0;
				notValid = 0;
			}
			else
			{
				cout << "Invalid Input, please try agian. (Y/N): ";
				cin >> runAgain;
			}
		}
	}
}