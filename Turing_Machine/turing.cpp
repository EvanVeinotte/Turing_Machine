/*

	A turing machine simulator built by Evan Veinotte. (2020-05-19)
	
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
using namespace std;

//maximum amount of individual values to be decoded from a string of code
const int TOKEN_LENGTH_MAX = 11;
//length of the turing tape
const int TAPE_LENGTH = 64;

//Current state of the machine
int Cur_State = 0;
//Position of the turing machine head relative to the tape
int Head_Pos = 0;

//state struct
//s=state to switch to next tick, w=what to write to the tape directly under the head, d=direction to move next tick, left(-1) or right(1)
//when the tape is read, there are 3 different options; the head reads a 1, 0 or blank. Each possibility needs its own state, write and direction instruction. 
struct State{
	int s0;
	int s1;
	int sb;
	string w0;
	string w1;
	string wb;
	int d0;
	int d1;
	int db;
};

//array of states
State statearray[1000];
//the string written in the code file that represents the code to be placed onto the tape
string TapeCode;
//this number represents where to position to insert the turing code
int codeStart;

//This function takes a single line of code, decodes it, and then acts on the instructions. It essentially compiles a single string passed through as its parametre.
void compileLine(string inputstr)
{
	//the c string that will contain the line of code.
	char str1[inputstr.length()];
	
	//transform input string into a character array (str1)
	for (int i = 0; i < inputstr.length(); i++)
	{
		str1[i] = inputstr[i];
	}
	
	//tokenlist will contain all the tokens.
	char *tokenlist[TOKEN_LENGTH_MAX];
	//token is a temp variable to store the token returned from strtok
	char *token;
	//strtok here will return the first token.
	token = strtok(str1, "[]:(), ");
	for (int i = 0; i < TOKEN_LENGTH_MAX; i++)
	{	
		//storing the token pointer into the token list
		tokenlist[i] = token;
		//input a NULL pointer to cycle to next token
		token = strtok(NULL, "[]:(), ");
	}
	
	//operation is the first keyword that tells us what type of line of code it is.
	string operation = tokenlist[0];
	//tempstring is a temporary string to store the tokens, aka char pointers, into a format that can be transformed into an integer.
	string tempstring;
	
	if (operation == "state")
	{
		//transform the tokens into a state object
		//before converting into an integer, the pointer reference needs to be stored as a string.
		//It is then converted into an integer using std::stoi
		tempstring = tokenlist[1];
		int stateid = stoi(tempstring);
		
		tempstring = tokenlist[2];
		statearray[stateid].s0 = stoi(tempstring);
		tempstring = tokenlist[3];
		statearray[stateid].w0 = tempstring;
		tempstring = tokenlist[4];
		statearray[stateid].d0 = stoi(tempstring);
		
		tempstring = tokenlist[5];
		statearray[stateid].s1 = stoi(tempstring);
		tempstring = tokenlist[6];
		statearray[stateid].w1 = tempstring;
		tempstring = tokenlist[7];
		statearray[stateid].d1 = stoi(tempstring);
		
		tempstring = tokenlist[8];
		statearray[stateid].sb = stoi(tempstring);
		tempstring = tokenlist[9];
		statearray[stateid].wb = tempstring;
		tempstring = tokenlist[10];
		statearray[stateid].db = stoi(tempstring);
	}
	else if(operation == "code")
	{
		//this means the second token will just be a line of turing code which can be saved directly into TapeCode
		tempstring = tokenlist[1];
		TapeCode = tempstring;
	}
	else if(operation == "headStart")
	{
		//this means the second token will be the starting position of the head
		tempstring = tokenlist[1];
		Head_Pos = stoi(tempstring);
	}
	else if(operation == "codeStart")
	{
		//where to insert the line of code into the tape.
		tempstring = tokenlist[1];
		codeStart = stoi(tempstring);
	}
	else if(operation == "stateStart")
	{
		//the state the machine will start in.
		tempstring = tokenlist[1];
		Cur_State = stoi(tempstring);
	}
	else if(operation == "//")
	{
		//ignore this line
	}
	else
	{
		cout << operation;
		throw "Compile Error: Unknown operation name.";
	}
}

//this function just calls compileLine for ever line of code in the code file
void compile(string filename)
{
	//turn myfile into a stream
	ifstream myFile(filename);
	
	//check if myFile is open
	if (myFile.is_open())
	{
		//will be used to hold each individual line of code
		string line;
		
		//the statement gets called every line
		while(getline(myFile, line))
		{
			compileLine(line);
		}
		//close the file when done
		myFile.close();
	}
	else
	{
		throw "Sorry your file could not be opened.";
	}
}

//this function draws calculates head pos into the string, and then draws that string onto the console
void drawHeadString()
{
	//clear headstring
	string headstr = "";
	//fill headstring up with empty spaces
	for (int i = 0; i < TAPE_LENGTH; i++)
	{
		headstr += " ";
	}
	//insert the V symbol at headpos
	headstr.replace(Head_Pos, 1, "V");
	//print it onto console
	cout << headstr << "\n";
}

//this function simply draws the tapestring recieved through its parametres
void drawTapeString(string tapestr)
{
	cout << tapestr;
}

//this function calculates the next tapestring based on current state and head position, and then returns it
string act(string tapestr)
{
	//reads the character directly under the head
	char read_value = tapestr[Head_Pos];
	//if the character is a 0
	if (read_value == '0')
	{
		//write what is saved in the current states w0 variable
		tapestr.replace(Head_Pos, 1, statearray[Cur_State].w0);
		//move the head to the left or to the right (-1 or 1)
		Head_Pos += statearray[Cur_State].d0;
		//change the current state to whatever is saved in the s0 variable
		Cur_State = statearray[Cur_State].s0;	
	}
	else if (read_value == '1')
	{
		tapestr.replace(Head_Pos, 1, statearray[Cur_State].w1);
		Head_Pos += statearray[Cur_State].d1;
		Cur_State = statearray[Cur_State].s1;
	}
	else if (read_value == '=')
	{
		tapestr.replace(Head_Pos, 1, statearray[Cur_State].wb);
		Head_Pos += statearray[Cur_State].db;
		Cur_State = statearray[Cur_State].sb;
	}
	else
	{
		throw "Runtime Error: Read a non =,0 or 1 character on the tape.";
	}
	
	return tapestr;
}

int main()
{
	try{
		
		//read the code file and convert it into state objects inside of statearray
		compile("code.vno");
		//builds the tape string. Fills it with blanks
		string tapeString = "";
		for (int i = 0; i < TAPE_LENGTH; i++)
		{
			tapeString += "=";
		}
		//inserts the code at the codeStart position
		tapeString.replace(codeStart, TapeCode.length(), TapeCode);
		
		//the quit variable
		bool quit = false;
		//the input string. Enter q to quit the program
		string input;
		
		while(quit == false)
		{
			//display the machine
			drawHeadString();
			drawTapeString(tapeString);
			//displays the current state of the machine
			cout << "State: " << Cur_State << "\n";
			//act. Calculates the string for next tick
			tapeString = act(tapeString);
			
			//waits for input. if q is input, quit.
			getline(cin, input);
			if (input == "q")
			{
				quit = true;
			}
			//clear the screen
			system("CLS");
		}
		
	}catch (const char* msg){
		cerr << "\n" << msg << endl;
		system("PAUSE");
	}
}
