#pragma once



/*
Abenezer Tadesse
CSCI 2312 PA-2 GAME OF LIFE

The program was developed on VS 2015 and tested on gnu g++ 4.4.2.
Compiles and runs successfuly on gcc ouray.cudenver.edu.
Meets All Requirements 10/17/2016

*/



// FILE GameOfLife2_csci2312.h
// CLASSES: GamOfLife, Cell and FileIOException, all in the namespace csci2312.
//
// DESCRIPTION: 
// The universe of the Game of Life is an infinite two - dimensional orthogonal grid of square cells, 
// each of which is in one of two possible states, alive or dead, or "populated" or "unpopulated"
// Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent.
// At each step in time, the following transitions occur depending on which rule we apply.
//
//
//=================GoL RULE (Conway's Game Of Life)
//https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
//
// Any live cell with fewer than two live neighbours dies, as if caused by under-population.
// Any live cell with two or three live neighbours lives on to the next generation.
// Any live cell with more than three live neighbours dies, as if by over-population.
// Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
// 
//
//=================HighLife RULE
//http://www.conwaylife.com/w/index.php?title=HighLife
// Similar to GoL with a slight variation.
//
// Any live cell with fewer than two live neighbours dies, as if caused by under-population.
// Any live cell with two or three live neighbours lives on to the next generation.
// Any live cell with more than three live neighbours dies, as if by over-population. 
// Any dead cell with exactly three or six live neighbours becomes a live cell, as if by reproduction.
//
//
// The initial pattern constitutes the seed of the system. 
// The first generation is created by applying either one of the above rules simultaneously to every cell in the seed: 
// - births and deaths occur simultaneously, and the discrete moment at which this happes is sometimes called a tick. 
// In other words, each generation is a pure function of the preceding one. The rules continue to be applied 
// repeatedly to create further generations. 
//    
//   


// *********************************************************************************
//							 		CLASS Cell
// *********************************************************************************
//
// =================== PUBLIC CLASS API - Cell
// CONSTRUCTORS:
//     Cell();
//     POSTCONDITION: Creates a dead(-) Cell
// 
// MODIFIERS/MUTATORS:
//     void setState(bool newState);
//     POSTCONDITION: Cell's state is set to the new state
//					  Cell's face is set to a face maching the new state
//
// ACCESSORS:
//     bool getState() const;  
//     POSTCONDITION: A const method - returns cell's state.  True if alive(o), and false if dead(-)

// =================== PRIVATE CLASS MEMBERS - Cell
//   
//     bool state; 
//	   char face;
//
//
//========================================== END OF Cell CLASS============================================



// *********************************************************************************
// 							 		GameOfLife 
// *********************************************************************************
//
//
// =================== PUBLIC CLASS API - GameOfLife
// MEMBER CONSTANTS:
//   const static size_t MAX_BOARD
//   The max size of the visible gameboard.  The actual size will be passed into the game's constructor. 
//
// CONSTRUCTORS:
//     GameOfLife();
//       POSTCONDITION: Creates a 32X32 size matrix of dark cells
//
//     GameOfLife(size_t iBoardSize);
//       PRECONDITION: The system must have enough memory to allocate for the input board size
//					    or bad_alloc exception is thrown  
//       POSTCONDITION: Creates a (iBoardSize + 2) size matrix of dark cells.
//							Sets boardSize private member to iBoardSize + 2
//
//     GameOfLife(GameOfLife &game);
//       PRECONDITION: The source object for this copy-constructor exists  
//       POSTCONDITION: Creates a full copy of the referenced object
//
// MODIFIERS/MUTATORS:
//
//	void setBoardSize(size_t iBoardSize); 
//       POSTCONDITION: boardSize is set to iBoardSize + 2
//						
//
//   void seedBoard(string fileName) throw (FileIOexception);
//     FUNCIONALITY: Initializes the board; reads the configuration of lit cells from a text file. 
//                        May throw FileIOException 
//     POSTCONDITION: Board is successfully seeded with a known predictable pattern,
//
//   void seedBoard(size_t seeds);
//     FUNCTIONALITY:  Initializes the board with seeds-number of lit cells at randomly generated locations. 
//     PRECONDITION: If number of seeds requested is greater than maximum matrix capacity, all cells might be alive
//     POSTCONDITION: Board is successfully seeded
//  
//	bool executeRule110(unsigned int countAlive, bool currentState);
//      FUNCTIONALITY: PA2: Executes GoL(Conway's Game Of Life) rules on a cell based on 
//							the number of alive neighbours (countAlive) and the cell's state (currentState)
//      POSTCONDITION: Returns false for dead, and true for alive
//
//   bool executeRuleXXX(unsigned int countAlive, bool currentState);
//      FUNCTIONALITY: Executes HighLife rules on a cell based on the number of alive neighbours (countAlive)
//						and the cell's state (currentState)                  
//      POSTCONDITION: Returns false for dead, and true for alive cell based on HighLife rules
//   
//   void run( );
//     FUNCTIONALITY: Starts the simulation.  Asks a user if to generate another iteration, or if to end
//						Iterations are based on GoL rules
//     POSTCONDITION: Simulation has run until a user requested it to stop
//
//
//   void runRuleXXX( );
//     FUNCTIONALITY: Starts the simulation.  Asks a user if to generate another iteration, or if to end
//						Iterations are based on HighLife rules
//     POSTCONDITION: Simulation has run until a user requested it to stop
//
//
//   void run(unsigned int numberOfIterations);
//     FUNCTIONALITY: Starts the simulation applying GoL Rules to each generation
//     POSTCONDITION: Simulation has run erquested number of times
//
////   void runRuleXXX(unsigned int numberOfIterations);
//     FUNCTIONALITY: Starts the simulation applying HighLife Rules to each generation
//     POSTCONDITION: Simulation has run erquested number of times
//
// =================== PRIVATE CLASS MEMBERS - GameOfLife
//   
//  
//	int numOfNeighbors(CellPtr* current, int row, int col);
//      FUNCTIONALITY: Given the row and col (x,y coordinate) location of a cell and a pointer to current matrix of cells 
//						it counts how many of 8 neighboring cells are alive 
//     PRECONDITION: The cell is Not a corner cell i.e. it is surrounded by at least 1 cell in each direction 
//						within the bounds of the board  
//     POSTCONDITION: number of alive neighbor cells of the cell at position (row,col) is returned. 
//
//
//   void calculateNextGen(CellPtr* current,CellPtr* next);
//     FUNCTIONALITY:  Calculates the next state of the population of Cells based on GoL rules
//						Current is a pointer to the current matrix of cells and the funtions updates 
//						the matrix of cells the pointer next points to
//					  The Functions also updates displayBoard pointer so that it points to the new generation/matrix
//     POSTCONDITION: Next state has been calculated, displayBoard has been updated
//					  New generation is ready to display
//
//   void calculateNextGenXXX(CellPtr* current,CellPtr* next);
//     FUNCTIONALITY:  Calculates the next state of the population of Cells based on HighLife rules
//						Current is a pointer to the current matrix of cells and the funtions updates 
//						the matrix of cells the pointer next points to
//					  The Functions also updates displayBoard pointer so that it points to the new generation/matrix
//     POSTCONDITION: Next state has been calculated, displayBoard has been updated
//					  New generation is ready to display
//
//
//    CellPtr* currentLife
//    CellPtr* nextLife
//    CellPtr* displayBoard
//    size_t boardSize
//
//====================    PROGRAM DESIGN   ===============
//					currentLife and nextLife are used to make two boards. We will use one baord and calculate
//					the next generation onto the second one. The second board is then used to calculate
//					the following generation onto the first board. So the two boards(matrix of cells) will be
//				    constantly rotating the role of current generation and new generation.
//					
//					Everytime we calculate a new generation on to a board,, diplayBoard gets updated to point to it
//					Therfore dispalyBoard toggles between the two boards depending on which one has the most current
//					generation.
//
//					boardSize is the actual size of the board which is 2 + the displayed boardSize. This is because
//					we will be using halo approach so corner cells are neither displayed nor will have rules of the 
//					game applied to them. Since corner cells do not have 8 neighbours by not taking them into account
//					we apply game rules only to those that have 8 neighbours. So when user sets board size to 50
//					the actual board is 52x52
//
// ===================  NON-MEMBER FUNCTIONS  
//
//   friend ostream& operator << (ostream& out, const GameOfLife& board)
//     POSTCONDITION: The game board has been displayed (printed to ostream out, which,
//     in turn, has been returned to the calling function)
//
//   friend istream& operator >> (istream& in, const GameOfLife& board);
//	   PRECONDITION: text file must exist. File contains '-' and 'o' characters. File operations must be successful 
//     POSTCONDITION: The game board has been populated from the input stream (file or keyboard)


#ifndef GAMEOFLIFE2_CSCI2312_H
#define GAMEOFLIFE2_CSCI2312_H

#include <iostream>
#include<string>
#include<ctime>
#include<fstream>
#include<new>

namespace csci2312
{
	using std::string;
	using std::ostream;
	using std::istream;
	using std::ifstream;
	using std::bad_alloc;



	class Cell
	{
	private:
		bool state = false;
		char face;
	public:
		static const char alive = 'o';  // alive image
		static const char dead = '-';  // dead image


		Cell();
		Cell(bool cellState);
		~Cell();

		// Accessors have no intention to modify the object, so it is a good practice to make them 'const' functions
		bool getState() const;
		char getFace() const;

		// Mutators
		void setState(bool newState);
		
	};




	// PA2: File IO Error custom exception  class
	class FileIOException
	{
		//  Nothing inside, just a class type to handle exception
	};




	class GameOfLife
	{

	public:
		// PA2: default display board size
		static const unsigned int MAX_BOARD = 20;

		// PA2: New type (pointer to Cell type) handy with dynamic arrays
		typedef Cell* CellPtr;

		// PA2: Constructs the board of the requested size, can throw exception.
		// If parameter is omitted, it becomes the default constructor, and the board will have MAX_BOARD size
		GameOfLife(size_t iBoardSize = MAX_BOARD) throw (bad_alloc);

		// PA2:  Copy-constructor creates a new instance as a deep copy of the referenced object
		GameOfLife(const GameOfLife& game);

		// PA2:  destructor must release memory taken by dynamic arrays
		~GameOfLife();

		//  Returns board size
		size_t getBoardSize() const;
		void setBoardSize(size_t iBoardSize);

		// PA1: seeds the board from a file
		// int seedBoard(string fileName);

		// PA2: seeds the board from a file and throws an exception if there was trouble with file
		void seedBoard(string fileName) throw (FileIOException);

		// PA1 and PA2: seeds the  board with a given number of seeds at randomized locations
		void seedBoard(size_t seeds);

		// PA1 and PA2: 
		void run();
		void run(unsigned int numberOfIterations);


		// PA2:  Executes Conway set of rules (same rules as PA1). Returns next state
		// Needed for TASK #5 to develop a test harness (the files test harness will be provided separately)
		bool executeRule110(unsigned int countAlive, bool currentState);

		// PA2:  Executes additional set of rules. Returns next state
		bool executeRuleXXX(unsigned int countAlive, bool currentState);
		
		void runRuleXXX();
		void runRuleXXX(unsigned int numberOfIterations);
		// Just an example of an possible accessor which reaches to a private array.  Not needed to satisfy PAs
		// A const(!) accessor method that returns a handle to the private currentLife array. 
		// The return type must also be 'const' because we return a pointer to a static array, and these are fixed
		// It is just an example.  It is not needed if we have a friend operator.		
		// PA1: const Cell(*getCurrentLife() const )[MAX_BOARD+2]  { return currentLife; };
		// PA2: const CellPtr* getCurrentLIfe() const { return currentLife; };

		// PA1 and PA2:  overloaded output operator to displsy the board 
		// friend operator can access private members of GameOfLife
		friend ostream& operator << (ostream& out, const GameOfLife& board);

		// PA2:  overloaded input operator to input the board (from file of keyboard)
		friend istream& operator >> (istream& in, const GameOfLife& board);

	private:

		int numOfNeighbors(CellPtr* current, int row, int col);
		


		// PA2:  Encapsulate next generation calculation in a methos.  Needed only for OPTIONAL Task #6
		void calculateNextGen(CellPtr* current, CellPtr* next);
		void calculateNextGenXXX(CellPtr* current, CellPtr* next);
		// PA1:  static arrays of Cells.  With "Halo" approach we need a bigger board
		// Cell currentLife[MAX_BOARD + 2][MAX_BOARD + 2];
		// Cell nextLife[MAX_BOARD + 2][MAX_BOARD + 2];

		// PA2:  dynamic arrays of Cells. New type CellPtr defined (typedef Cell* CellPtr)
		// currentLife and and nextLife are handles to the dynamic arrays
		CellPtr *currentLife;
		CellPtr *nextLife;

		// Just an example how to declare variable cl as a handle to our array of Cells.  Not needed to satisfy PAs
		// The accessor method getCurrentLife() above uses the same syntax for the return type
		// PA1 with static arrays:  const Cell(*cl)[MAX_BOARD + 2] = currentLife; 
		// PA2 with dynamic arrays: const CellPtr* cl = currentLife; 

		// PA1 and PA2, keeps track of the actual board size, set in the constructor
		size_t boardSize;

		// PA2: A handle to the array that needs to be displyed next.  Only needed for OPTIONAL TASK #6 
		CellPtr *displayBoard;
	};


}


#endif // 