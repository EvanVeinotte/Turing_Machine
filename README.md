# Turing_Machine
A turing machine simulator run in the console. 
## What is a turing machine?
A turing machine is a type of computer, theorised by Alan Turing in 1936. Although simple, it is capable of computing anything a modern computer could compute today. Using only 3 symbols, 0s, 1s and blanks, and a table of states and instructions, the turing machine is technically capable of running GTA5 (Albeit extremely slowly). 
- Here is a video explaining them in greater detail: https://www.youtube.com/watch?v=dNRDvLACg5Q&t=145s
## How to use
The turing machine will run whatever code is in the code.vno file. If you run the turing executable, a console window will pop up with a simulation of the machine. To advance onto the next step, press the enter key. You can hold the enter key to advance through the steps quickly. You can also enter a 'q' into the input field, which will terminate the program.
## How to write your own code
### Code Structure:
operation_keyword:parameters:
For example:
codeStart:16:
### List of operation keywords:
- **code:string:** Takes a string of 1s, 0s and =s as a parameter (no quotation marks). Whatever is passed through as a parameter will be inserted onto the tape and will act as the "program" for your turing machine. Example: *code:100101=010=110:*
- **codeStart:integer:** The integer value passed through as a parameter will specify at what position on the tape to insert the code. Example: *codeStart:37:*
- **headStart:integer:** The integer value passed through as a parameter will specify at what position the head of the turing machine will start. Example: *headStart:3:*
- stateStart:integer: The integer value passed through as a parameter will specify what state the machine will start in. Example: *stateStart:401:*
- **state\[state_name\]:(state_0,write_0,direction_0)(state_1,write_1,direction_1)(state_b,write_b,direction_b):** The state keyword is used to create a state, and then define the actions the head will take for each possible character that the head might read (1, 0 or =). Example: *state[502]:(503,1,-1)(502,1,-1)(502,=,-1):* In this example, the machine will change nothing and move to the left if it reads a 1 or a =(blank). If it reads a 0, it will change that 0 to a 1, switch to state 503 and move to the left.
  - state_name (integer): The state's id. Other states can will switch over to this state by using this number.
  - state_0 (integer): This is the state that the machine will switch to next step if the head reads a 0 on the tape.
  - write_0 (char 0,1 or =): This is the value that will be written onto the tape this step if the head reads a 0 on the tape.
  - direction_0 (1 or -1): This value determines which direction the head will move next step when the head reads a 0 on the tape. (1 is right and -1 is left).
  - state_1 (integer): This is the state that the machine will switch to next step if the head reads a 1 on the tape.
  - write_1 (char 0,1 or =): This is the value that will be written onto the tape this step if the head reads a 1 on the tape.
  - direction_1 (1 or -1): This value determines which direction the head will move next step when the head reads a 0 on the tape.(1 is right and -1 is left).
  - state_b (integer): This is the state that the machine will switch to next step if the head reads a =(blank) on the tape.
  - write_b (char 0,1 or =): This is the value that will be written onto the tape this step if the head reads a =(blank) on the tape.
  - direction_1 (1 or -1): This value determines which direction the head will move next step when the head reads a =(blank) on the tape.(1 is right and -1 is left).
## Machine Limitations:
The machine is set to only create states between 0 and 999. However, this could easily be changed by changing the MAX_STATES variable in the source code.
