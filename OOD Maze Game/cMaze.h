#pragma once
#include <istream>
#include <string>
#include <vector>
#include <random>
#include "cVector2.h"

#include "GameObject.h"

const int NO_SEED = -1;
const int MINIMUM_SIZE = 8;
const int MAXIMUM_WIDTH = 55;
const int MAXIMUM_HEIGHT = 55;
const int DEFAULT_MAZE_WIDTH = 19;
const int DEFAULT_MAZE_HEIGHT = 19;

struct Cell
{
	bool visited;
	bool top_wall;
	bool bot_wall;
	bool left_wall;
	bool right_wall;
	char display;

	GameObject* objectInCell = nullptr;
};

class cMaze
{
protected:
	// call reset() to wipe any existing maze data, ready to create a new one
	virtual void    reset();

	// repeated looks for random cells that contain floor cells
	virtual bool    getRandomEmptyPosition(int& col, int& row, int nAttempts = 0);

	// getPositionValue() returns the character at a particular row/y, col/x location
	virtual char    getPositionValue(int col, int row);

	// setPositionValue() set the character at a particular row/y, col/x location
	virtual char    setPositionValue(int col, int row, char value);

	cVector2    m_start{ 0,0 };         // maze starting point
	cVector2    m_exit{ 0,0 };          // designated end/finish point
	cVector2    m_dimensions{ 0,0 };    // size of the maze: x=width/columns, y=height/rows
	cVector2    m_RequestedDimensions{ 0,0 };    // parameters passed to create. different from m_dimensions if the passed values were invalid.
	int         m_seed{ 0 };            // seed used to generate the maze
	std::mt19937 m_mtRand;				// mersenne-twister object used for random generation
	char** p_chars{ nullptr };     // pointer to an array of characters - printable maze
	char        m_floorChar{ ' ' };      // empty space character
	char        m_wallChar{ (char) 219 }; // this is a block in the extended ascii table
	char        m_startChar{ 'S' };     // starting space character
	char        m_exitChar{ (char) 174 };      // exit space character
	char        m_errorChar{ 0 };       // used when querying the maze to report an error
	bool        m_printDuringGeneration{ false };  // if true, prints progress while map is generated
	bool		m_labelAllEndpoints{ false }; // if true, all corridor ends are labeled with letters, starting with 'a'
	std::vector<std::string>  m_strings; // vector of strings instead that comprise the map
	std::vector<cVector2>	m_endpoints; // vector of endpoints: potential start and exit
	double		m_msLimit{ 0 };

private:
	void        initialize();
	void        generateMaze();
	void        printCells();
	double		calcTimeLimit_ms();

	// The Cell struct is used internally by the maze generation algorithm. 
	//  It is only used during maze creation and not part of the public interface.
	//  Only the resulting character array is stored and usable.


	Cell** p_Cells;


public: 	
	// use create() to make a new maze, giving it appropriate dimensions and optional random seed
	virtual bool   create(int seed = NO_SEED, int width = DEFAULT_MAZE_WIDTH, int height = DEFAULT_MAZE_HEIGHT);
	//  cMaze public interface methods
		 // use createRandomSize() to make a new maze, with random (safe) dimensions and optional random seed
	virtual bool   createRandomSize(int seed = NO_SEED);

	// getStrings() returns a vector of strings; one string for each horizontal row of the maze
	const std::vector<std::string>&	getStrings();

	// getEndpoints returns a vector of potential start and endpoints
	const std::vector<cVector2>& getEndpoints();

	// getWidth() and getHeight() returns the dimensions of the current maze, if any 
	int     getWidth() { return m_dimensions.x; }
	int     getHeight() { return m_dimensions.y; }

	// getSeed() returns the random seed used to create the maze
	int     getSeed() { return m_seed; }

	// getStart() gets the rol and column of the player start position
	bool    getStart(int& col, int& row);
	bool    getStart(cVector2& start);

	// getExit() gets the rol and column of the player end/exit position
	bool    getExit(int& col, int& row);
	bool    getExit(cVector2& exit);

	// print() tells the maze to draw itself to the console, once it has been created.
	// specify the upper-left position using the paramters if you want. Default is 0,0.
	void    print(int startCol = 0, int startRow = 0);

	// turn on/off printing the maze with each change and at the end 
	bool    printOn(bool on) { m_printDuringGeneration = on; return on; }

	// turn on/off displaying alphabetic labels for all maze endpoints
	bool	labelEndpoints(bool on) { m_labelAllEndpoints = on; return on; }

	// get the character used by the maze to indicate a wall space
	char    getWallChar() { return m_wallChar; }

	// get the character used by the maze to indicate a floor space
	char    getFloorChar() { return m_floorChar; }

	// get the character used by the maze to indicate the player starting location
	char    getStartChar() { return m_startChar; }

	// get the character used by the maze to indicate the player exit location
	char    getExitChar() { return m_exitChar; }

	// get the maze traversal target in milliseconds
	double	getTimeLimit_ms() { return m_msLimit; }

	//Print in a position
	void PrintInPosition(GameObject* gameobject);

	//Remove from a position
	void RemoveFromPosition(cVector2 pos);

	//Get Start Position
	cVector2 GetStartPosition();

	//Get Exit Position
	cVector2 GetExitPosition();

	//Get Random Empty Position
	cVector2 GetRandomEmptyPosition();

	//Get Random Empty Position
	cVector2 GetRandomEndPointPosition();

	Cell& GetCell(cVector2 pos);

	Cell& GetUpCell(cVector2 pos);
	Cell& GetDownCell(cVector2 pos);
	Cell& GetRightCell(cVector2 pos);
	Cell& GetLeftCell(cVector2 pos);

	int GetNumberOfEndPoints();

	//Hide Cursor
	void HideCursor();

	// default constructor
	cMaze();
	virtual ~cMaze();
};

