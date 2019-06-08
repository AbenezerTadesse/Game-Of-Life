



/*
Abenezer Tadesse
CSCI 2312 PA-2 GAME OF LIFE

The program was developed on VS 2015 and tested on gnu g++ 4.4.2.
Compiles and runs successfuly on gcc ouray.cudenver.edu.
Meets All Requirements 10/17/2016

*/

//FILE: main.cpp
//CLASSES: GameOfLife and Cell 
//DESRIPTION: Contains the driver function for Game Of Life Program
//				Interacts with user for input to set size of printable board,
//				whether to seed from file or randomly, and also number of generations to be printed
//				User has a choice of leaving board size to default value of 30 (30x30) 
//	PRECONDITION: Assumes all inputs are valid.
//	POSTCONDITION: Game Of Life program keeps running until user chooses to EXIT program






#include"GameOfLife2_csci2312.h"
using namespace csci2312;
using std::cout;
using std::cin;
using std::endl;

int main()
{
	GameOfLife* Game1;
	int mainMenu;	//user input from main menu option
	size_t boardSize; //holds user's input for board size

	enum menu_options {
		RANDOM_SEED = 1, SEED_FILE = 2, PRINT_BOARD = 3, RUN_GoL = 4,
		RUN_HIGHLIFE = 5,  EXIT = 0
	};

	
	cout << "\n\n********Welcome to GAME OF LIFE program*********" << endl;
	cout << "Please enter the board size to be dispalyed or enter 0 for a default size of 30\n";
	cin >> boardSize;// read in boardSize

	if (boardSize > 0) // if user entered value set board size to user's specification
	{
		Game1 = new GameOfLife (boardSize);
	}
	else
	{
		Game1 = new GameOfLife();
	}



	mainMenu = 1;
	while (mainMenu > 0)
	{
		cout << "\n\tEnter numbers 0 - 5 to choose from menu below" << endl
			<< "\t1:Seed board with alive cells at random locations\n"
			<< "\t2:Seed board from file\n"
			<< "\t3:Print board\n"
			<< "\t4:Run Game Of Life(GoL) simulation\n"
			<< "\t5:Run High Life simulation\n"
			<< "\t0:Exit Program\n";

		cin >> mainMenu;

		if (mainMenu == RANDOM_SEED)
		{
			cout << "\nPlease enter how many random location you would like to seed\n";
			size_t seed;
			cin >> seed;
			Game1->seedBoard(seed);
		}

		else if (mainMenu == SEED_FILE)
		{
			cout << "\nSeeding from seed.txt file...\n";
			Game1->seedBoard("seed.txt");
		}

		else if (mainMenu == PRINT_BOARD)
		{
			cout << *Game1;
		}

		else if (mainMenu == RUN_GoL)
		{
			int runType;
			cout << "\nEnter number the desired number of generations or 1 to run one at a time\n";
			cin >> runType;
			if (runType > 1)
			{
				Game1->run(runType);
			}
			else
			{
				Game1->run();
			}
		}

		else if (mainMenu == RUN_HIGHLIFE)
		{
			int runType;
			cout << "\nEnter number the desired number of generations or 1 to run one at a time\n";
			cin >> runType;
			if (runType > 1)//if user wants more than one generation
			{
				Game1->runRuleXXX(runType);
			}
			else //user wants to print one generation at a time
			{
				Game1->runRuleXXX();
			}
		}
	}//end while loop

	if (mainMenu == 0) //print program exit message
	{
		cout << "\n\n\tThank you for Playing Game Of Life\n\tGood Bye!!!\n\n\n\n" << endl;
	}

	
	cin.ignore();// pauses screen
	cin.ignore();
	return 0;
}