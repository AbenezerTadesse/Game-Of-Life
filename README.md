# Game-Of-Life
### [Conway's Game of Life.](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)
The universe of the Game of Life is a two dimensional orthogonal grid of square cells, each of which is in one of two possible states, alive or dead, or "populated" or "unpopulated".
Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent.
At each step in time, the following transitions occur:
  * Any live cell with fewer than two live neighbours dies, as if caused by under-population.
  * Any live cell with two or three live neighbours lives on to the next generation.
  * Any live cell with more than three live neighbours dies, as if by over-population.
  * Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.


### [HighLife.](http://www.conwaylife.com/w/index.php?title=HighLife)
This simulation has similar rules to Game of Life with a slight variation:
  * Any live cell with fewer than two live neighbours dies, as if caused by under-population.
  * Any live cell with two or three live neighbours lives on to the next generation.
  * Any live cell with more than three live neighbours dies, as if by over-population.
  * Any dead cell with exactly three or six live neighbours becomes a live cell, as if by reproduction.
  
The initial pattern constitutes the seed of the system.
The first generation is created by applying the above rules simultaneously to every cell in the seed. 
Births and deaths occur simultaneously, and the discrete moment at which this happes is sometimes called a tick.
In other words, each generation is a pure function of the preceding one. The rules continue to be applied repeatedly to create further generations. 

The program allows the user to set the canvas size or pick the default size of 30X30.
User has the choice to either seed the canvas randomly or seed from a text file that has rows of *-*(dead) and *o*(alive). The number of rows and column in the text file must match the canvas grid size. The user can then run the HighLife or Game of Life simulation for the desired number of generations.
All the necessary .h and .cpp files along with an example seeding text file are included. This program was developed on VS-2015 for University of Colorado Object Oriented Programing course as a final assignment in Fall 2016.

