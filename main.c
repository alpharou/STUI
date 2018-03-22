#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

//GUI VARS
int slider1[] = {20, 1}; //Length and position of the slider.

int exc(int ctrl);
int gui();
int inp();
void cls();
void slider(char direction);

int main(int argc, char **argv)
{
	int status;
	
	printf("Simple Terminal User Interface v0.1: Press left/right to use, ESC to EXIT...\n");
	do 
	{
		status = gui(exc(inp())); //input >> exc >> gui
		
		if (status == 0) {printf("Something went wrong.\n"); return 0; break;} //Check for incoherent return values and crash.
		
	} while (status != 16); //Check for the actual EXIT value;
	
	return 16; //Expected EXIT value.
}

//TODO: Draw changes onto the screen depending on the mode.
int gui(int ctrl)
{
	//HIDE CURSOR
	printf("\033[?25l");
	switch (ctrl)
	{
		case 15: {return 15; break;} //SKIP DRAW
		case 16: {return 16; break;} //EXIT
		case 1: 
		{
			cls();
			//This DRAW code should be wrapped into functions.
			for (int i = 1; i <= slider1[0]; i++)
			{
				if (i == slider1[1]) {printf("%c", 219);}
				else {printf("%c", 205);}
			}
			
			printf(" %i/%i\n", slider1[1], slider1[0]);
			//This is the end of the DRAW code chunk.
			return 1; 
			break;
		} //DRAW DEFAULT
		
		case 0: {return 0; break;} //ERROR Propagate
	}
	
	printf("ERROR: gui() returned 0.\n"); return 0; //ERROR. This should never happen.
}

//TODO: Execute the user input and return the drawing mode for the GUI.
int exc(int ctrl)
{
	switch (ctrl)
	{
		case 12: {slider('l'); return 1; break;}	//SLIDER LEFT, DRAW
		case 13: {slider('r'); return 1; break;} 	//SLIDER RIGHT, DRAW
		case 15: {return 15; break;}             	//NOTHING TO REDRAW
		case 16: {return 16; break;}             	//EXIT
		case 0: {return 0; break;}               	//ERROR Propagate.
		default:                                 	//CTRL CODE NOT FOUND, DONT DRAW
		{
			printf("exc(): CTRL CODE %i NOT FOUND.\n", ctrl); 
			return 15; break;
		}                                        
	}
	
	printf("ERROR: exc() returned 0.\n"); return 0; //ERROR. This should never happen.
}

//Get the user input and return suitable control codes for execution.
int inp()
{
	int buff1 = _getch(), buff2;
	//Intercept and map key strokes to desired control codes.
	switch (buff1)
	{
		//Acknowledge special inputs that come with a 0 header.
		case 0:
		{
			buff2 = _getch();
			switch (buff2)
			{
				default: printf("inp(): KEY 0>>%i NOT MAPPED.\n", buff2); return 15; break;
			}
		}
		//Acknowledge special inputs that come with a 0xE0 header.
		case 0xE0:
		{
			buff2 = _getch();
			switch (buff2)
			{
				case 72: {return 11; break;} //UP
				case 75: {return 12; break;} //LEFT
				case 77: {return 13; break;} //RIGHT
				case 80: {return 14; break;} //DOWN
				default: 
				{
					printf("inp(): KEY 0xE0>>%i NOT MAPPED.\n", buff2);
					return 15; break;
				} //DO NOTHING
			}
		}
		case 49: {return 1; break;}  // 1
		case 50: {return 2; break;}  // 2
		case 51: {return 3; break;}  // 3
		case 52: {return 4; break;}  // 4
		case 53: {return 5; break;}  // 5
		case 54: {return 6; break;}  // 6
		case 55: {return 7; break;}  // 7
		case 56: {return 8; break;}  // 8
		case 57: {return 9; break;}  // 9
		case 48: {return 10; break;} // ERASE
		case 8: {return 10; break;}  // ERASE
		case 27: {return 16; break;} //[ESC] EXIT
		default: 
		{
			printf("inp(): KEY %i NOT MAPPED.\n", buff1);
			return 15; break;
		} //DO NOTHING
	}
	
	printf("ERROR: inp() returned 0.\n"); return 0; //ERROR This should never happen.
}

//DUDE THAT THING IS UGLY CLEAR IT UP! (Just for windows)
void cls()
{
	system("cls");
}

void slider(char direction)
{
	switch (direction)
	{
		case 'l': 
		{
			if (slider1[1] > 1) {slider1[1]--;}
			break;
		}
		case 'r': 
		{
			if (slider1[1] < slider1[0]) {slider1[1]++;}
			break;
		}
		default: {break;}
	}
}