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
- state &#91 :(state_0,write_0,direction_0)(state_1,write_1,direction_1)(state_b,write_b,direction_b): 
