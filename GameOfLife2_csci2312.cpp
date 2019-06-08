


/*
Abenezer Tadesse
CSCI 2312 PA-2 GAME OF LIFE

The program was developed on VS 2015 and tested on gnu g++ 4.4.2.
Compiles and runs successfuly on gcc ouray.cudenver.edu.
Meets All Requirements 10/17/2016

*/

//FILE: GameOfLife.cpp
//CLASSES: GameOfLife, Cell, FileIOException

//DESRIPTION: Class implementation file. FileIOException is a File IO Error custom exception  class
//				with no members. Its just a class type to handle exception

#include"GameOfLife2_csci2312.h"


namespace csci2312
{
	using std::cout;
	using std::cin;
	using std::endl;
//===========================================  CELL ================================================
	Cell::Cell() //constructs a dead cell
	{
		state = false;
		face = dead;
	}

	Cell::Cell(bool cellState) //constructs a cell with cellState state and corresponding face
	{
		state = cellState;

		if (cellState)
		{
			face = alive;
		}

		else
		{
			face = dead;
		}
	}


	Cell::~Cell()
	{
		//destructor. Nothing to destruct
	}


	bool Cell::getState() const
	{
		return state;
	}


	char Cell::getFace() const
	{
		return face;
	}


	void Cell::setState(bool newState)
	{
		state = newState;

		if (newState) //set the state and face of the cell to newState
		{
			face = alive;
		}

		else
		{
			face = dead;
		}
	}



//====================================  GAME OF LIFE  ===========================================


	GameOfLife::GameOfLife(size_t iBoardSize ) throw (bad_alloc)
	{
		boardSize = iBoardSize + 2; //set boardSize accounting for corner cells
		try 
		{ //try allocating enough memory to accomodate requested boardSize
			currentLife = new CellPtr[boardSize];
			nextLife = new CellPtr[boardSize];

			for (size_t row = 0; row < boardSize; row++)
			{
				currentLife[row] = new Cell[boardSize];
				nextLife[row] = new Cell[boardSize];
			}
		}
		
		catch (bad_alloc) //if not enough memory handle exception
		{
			cout << "\n\tRan out of memory!\n";
		}
	

		displayBoard = currentLife; //update displayBoard
	}


	GameOfLife::GameOfLife(const GameOfLife& game)
	{//deep copy
		boardSize = game.boardSize;// copy size and dynamically create two boards based on boardSize
		currentLife = new CellPtr[boardSize];
		nextLife = new CellPtr[boardSize];

		for (size_t row = 0; row < boardSize; row++)
		{
			currentLife[row] = new Cell[boardSize];
			nextLife[row] = new Cell[boardSize];
		}

		for (size_t row = 1; row < boardSize - 1; row++) //copy cell configuration in both current and next life
		{
			for (size_t col = 1; col < boardSize - 1; col++)
			{
				currentLife[row][col] = game.currentLife[row][col];
				nextLife[row][col] = game.nextLife[row][col];
			}//end inner for loop
		}//end outer for loop


		displayBoard = currentLife; //update displayBoard
	}



	GameOfLife::~GameOfLife()
	{//destruct board
		for (size_t row = 0; row < boardSize; row++) //destruct array of pointers to Cell
		{
			delete [] currentLife[row];
			delete [] nextLife[row];
		}

		delete currentLife; //destruct Cell pointers
		delete nextLife;
	}


	size_t GameOfLife::getBoardSize() const
	{
		return boardSize;
	}


	void GameOfLife::setBoardSize(size_t iBoardSize)
	{
		boardSize = iBoardSize + 2;
	}

	void GameOfLife::seedBoard(string fileName) throw (FileIOException)
	{
		
		try
		{
			ifstream inFile;
			inFile.open(fileName);
			char input;

			if (!(inFile)) //if File IO fails
			{
				throw FileIOException();
			}

			for (size_t row = 1; row < boardSize - 1; row++) //since we are not dispalying corner cells
			{									//we read-in file and update each cell except the corner ones
				for (size_t col = 1; col < boardSize - 1; col++)
				{
					if (inFile >> input)
					{
						if (input == 'o')
						{
							currentLife[row][col].setState(true);
						}

						else
						{
							currentLife[row][col].setState(false);
						}
					}

					else
						return;

				}//end inner for loop
			}//end outer for loop

			displayBoard = currentLife;
		}

		catch (FileIOException) //If file opetation has failed handle exception
		{
			cout << "\n\tFile open error!\n\n";
			cin.ignore();
			exit(0);
		}
	}




	void GameOfLife::seedBoard(size_t seeds)
	{
		srand(time(0)); //seed with run time
		size_t count = 0;
		while (count < seeds)// loop until we have seeded the board seed number of times
		{		//generate random number row and col  from 1 to (boardSize - 1). 
			  //this insures that the random location is always within the dispayed potion of the board
			int row = rand() % (boardSize - 2)+1;
			int col = rand() % (boardSize - 2)+1;
			currentLife[row][col].setState(true);// set cell to alive
			count++;// keep track of number random locations we are seeding. 
		}

		displayBoard = currentLife;
	}



	int GameOfLife::numOfNeighbors(CellPtr* current, int row, int col)
	{
		unsigned int count = 0;		//number of alive cells

		for (int i = -1; i < 2; i++)	//look above and below cell
		{
			for (int j = -1; j < 2; j++) //look to left and right of cell
			{	//combination of (above/below) and (left/right) gives diagonals

				if (!(i == 0 && j == 0))	//when both i and j are zero we are looking at cell itself
				{							//and not its neighbor
					if (current[row + i][col + j].getState())
					{//is this neighbor alive? update count if true
						count++;
					}
				}//end outter if
			}//end inner loop
		}//end outer loop

		return count;

	}


	void GameOfLife::calculateNextGen(CellPtr* current, CellPtr* next)
	{
		for (size_t row = 1; row < boardSize - 1; row++)
		{
			for (size_t col = 1; col < boardSize - 1; col++)
			{
				int pop = 0;	//number of alive neighbors in current generation
				pop = numOfNeighbors(current, row, col);
				bool currentState = current[row][col].getState();
				//Apply GoL rules and update next generation

				next[row][col].setState(executeRule110(pop, currentState));
				
			}//end inner for loop
		}//end outer  for loop

		displayBoard = next;  //update displayBoard to point to the new generation
	}




	void GameOfLife::run()
	{
		cout << "\n\n\tPrinting next generation...\n\n";
		bool flip = true; //switch the keeps track of which board has the most current generation
		int input = 1;//user input to keep iterating

		while (input)//while the user enters 1 keep iterating next generations
		{
			if (flip)//currentLife is the most current board and next generation will be calculated 
			{							//and updated onto nextLife 
				calculateNextGen(currentLife, nextLife);
				cout << *this; //print the calling GameOfLife object. Thus printing most current board
				flip = false; //update flip. When flip is false, NextLife is the most current board
			}

			else //flip is flase which means nextLife is the most current board and we will calculate 
			{					//next generation onto currentLife
				calculateNextGen(nextLife, currentLife);
				cout << *this;// print board
				flip = true;// update flip. When flip is true currentLife is the most current board
			}
			cout << "\n\n\n\tWould you like to print next generation. Enter 1 for yes or 0 to exit\n";
			cin >> input;// read-in user input
		}
	}



	void GameOfLife::run(unsigned int numberOfIterations)
	{
		cout << "\n\n\tPrinting the next "<<numberOfIterations<<" generations...\n\n";
		bool flip = true;
		unsigned int count = 0; //keeps track of number of iterations performed

		while (count < numberOfIterations)// iterate until numberOfIterations is reached
		{
			if (flip)//keeps track of which board is the most current
			{
				calculateNextGen(currentLife, nextLife);
				cout << *this;
				flip = false;
			}

			else
			{
				calculateNextGen(nextLife, currentLife);
				cout << *this;
				flip = true;
			}
			
			count++;//update iteration count
		}
	}




	bool GameOfLife::executeRule110(unsigned int countAlive, bool currentState)
	{//GoL Rules
		if (currentState)//any alive cell
		{
			if (countAlive < 2 || countAlive > 3)// with less  than 2 or higher than 3 neighbors
			{
				return false;//dies
			}

			else if (countAlive == 2 || countAlive == 3)//with exaclty 2 or 3 neighbors 
			{
				return currentState;//lives on to the next generation
			}
		}

		else
		{//any dead cell
			if (countAlive == 3)// with exaclty 3 alive neighbors 
			{
				return true;//comes to live
			}

			else
			{//otherwise it stays dead
				return currentState;
			}
		}

	}




	bool GameOfLife::executeRuleXXX(unsigned int countAlive, bool currentState)
	{//HighLife Rule
		if (currentState)//any alive cell
		{
			if (countAlive < 2 || countAlive > 3)//with less than 2 or higher than 3 neighbors
			{
				return false;//dies
			}

			else if (countAlive == 2 || countAlive == 3) //with exaclty 2 or 3 neighbours lives on
			{
				return currentState;
			}
		}

		else
		{//any dead cell
			if (countAlive == 3 || countAlive == 6)//with 3 or 6 neighbours comes to life
			{
				return true;
			}

			else
			{//otherwise stays dead
				return currentState;
			}
		}

	}





	void GameOfLife::calculateNextGenXXX(CellPtr* current, CellPtr* next)
	{
		for (size_t row = 1; row < boardSize - 1; row++)//avoiding corner cells we apply HighLife rule 
		{
			for (size_t col = 1; col < boardSize - 1; col++)
			{
				int pop = 0;	//number of alive neighbors
				pop = numOfNeighbors(current, row, col);
				bool currentState = current[row][col].getState();

				next[row][col].setState(executeRuleXXX(pop, currentState));
			}
		}
		displayBoard = next; //update displayBoard
	}




	void GameOfLife::runRuleXXX()
	{
		cout << "\n\n\tPrinting next generation...\n\n";
		bool flip = true;
		int input = 1;

		while (input)
		{
			if (flip)
			{
				calculateNextGenXXX(currentLife, nextLife);
				cout << *this;
				flip = false;
			}

			else
			{
				calculateNextGenXXX(nextLife, currentLife);
				cout << *this;
				flip = true;
			}
			cout << "\n\n\n\tWould you like to print next HighLife generation. Enter 1 for yes or 0 to exit\n";
			cin >> input;
		}
	}


	void GameOfLife::runRuleXXX(unsigned int numberOfIterations)
	{
		cout << "\n\n\tPrinting the next " << numberOfIterations << " HighLife generations...\n\n";
		bool flip = true;
		unsigned int count = 0;

		while (count < numberOfIterations)
		{
			if (flip)
			{
				calculateNextGenXXX(currentLife, nextLife);
				cout << *this;
				flip = false;
			}

			else
			{
				calculateNextGenXXX(nextLife, currentLife);
				cout << *this;
				flip = true;
			}

			count++;
		}
	}

	ostream& operator << (ostream& out, const GameOfLife& board)

	{
		for (size_t row = 1; row < board.boardSize-1; row++)
		{
			for (size_t col = 1; col < board.boardSize-1; col++)
			{
				out << board.displayBoard[row][col].getFace() << " ";
			}

			out << endl;
		}
		out << endl << endl;
		return out;
	}



	istream& operator >> (istream& in, const GameOfLife& board)
	{
		char input;
		for (size_t row = 1; row < board.boardSize-1; row++)
		{
			for (size_t col = 1; col < board.boardSize-1; col++)
			{
				if (in >> input && input == 'o')
				{
					board.currentLife[row][col].setState(true);
				}

				else
				{
					board.currentLife[row][col].setState(false);
				}
			}
	
		}//end outer for loop



		return in;
	}

}//end namespace