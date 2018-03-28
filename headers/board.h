// board.h
// include board.h in your playerclass cpp file (NOT header file!!)

#ifndef _BOARD
#define _BOARD

#include <vector>
#include <iostream>
#include <sstream>
#include "gamespace.h"
#include "cell.h"
//#include "phc.h"  // this was should have the header for your handleclass

class Player;
class PlayerClass;

using namespace std;
using namespace GameSpace;

class Board
{
  public:
    static Board* GetBd( );
    // Returns a pointer to the board
    // pre:  board should already be created
    // post: returns a pointer to the board, NULL if no board created

    static vector<Player *> CreateBoard( );
    // Creates the board using a default size
    // pre:  none
    // post: the board is created, unless it already existed
    
    static vector<Player *> CreateBoard(int r, int c);
    // Creates the board using a default size
    // pre:  none
    // post: the board is created, unless it already existed
    
    static void DeleteBoard( );
    // Deallocates the board
    // pre: board is allocated
    // post: instance is deallocated
        
    ~Board( );
    // destructor for the board
    
    vector<Player *> Occupants(const Player * player) const;
    // Returns the vector of occupants for a cell inhabited by player
    // pre:  none
    // post: returns a vector of occupants, empty of player not on board
    
    vector<Player *> Enemies(const Player * player) const;
    // Returns the vector of enemies for a cell inhabited by player
    // pre:  none
    // post: returns a vector of enemies, empty of player not on board
    
    vector<Player *> Friends(const Player * player) const;
    // Returns the vector of friends for a cell inhabited by player
    // pre:  none
    // post: returns a vector of friends, empty of player not on board
    

    bool PlacePlayer(Player *p, int row, int col);
    // Moves a player into a cell, used for initial location
    // pre:  player not on board (will remove from cell if the player is)
    // post: player moved into a cell on the board
    
    bool MoveForward(Player * p, int units);
    // Moves a player a specific units forward
    // pre:  player must be on the board, units must be >=0
    // post: If terrain permits and player has momentum, 
    //       then player is moved forward a specific number of units
    
    int MoveCost(const Player * p, int units) const;
    // Checks the move cost for a player to move units in a forward directions
    // pre:  player must be on the board, units must be >=0
    // post: returns the cost of moving forward, 
    //       >=200 is return if player cannot move forward
    
    bool MoveForward(PlayerClass * p, int units);
    // Moves a player a specific units forward
    // pre:  player must be on the board, units must be >=0
    // post: If terrain permits and player has momentum, 
    //       then player is moved forward a specific number of units
    
    int MoveCost(const PlayerClass * p, int units) const;
    // Checks the move cost for a player to move units in a forward directions
    // pre:  player must be on the board, units must be >=0
    // post: returns the cost of moving forward, 
    //       >=200 is return if player cannot move forward

    int RunCost(const PlayerClass *p) const;
    // Checks the Run cost for a player to move 1 cel NORTH
    // pre:  player must be on the board
    // post: returns the cost of moving NORTH, 
    //       >=200 is return if player cannot RUN

    int RunCost(const Player *p) const;
    // Checks the move cost for a player to move 1 cell North
    // pre:  player must be on the board
    // post: returns the cost of moving NORTH 
    //       >=200 is return if player cannot RUN
    
    void Display(ostream& out, int type = 0) const;
    // Displays the board using the cell Display format
    // pre:  out should be open, type set to 1 for Testing cells
    // post: board is written to the output file
    
    void PrintBoard(ostream& out, const Player* player, int type=0) const;
    // Displays the board for a player using players coordinates
    // pre:  out should be open, type set to 1 for Testing cells
    // post: Board is wrriten to output file for player
        
  private:
    typedef CellClass* CellPtr;
    // used to access the board grid
    
    static Board * bd;
    // instance of the board
    
    const int ROWSIZE;
    // constant set when board is created
    
    const int COLSIZE;
    // constant set when board is created
    
    CellPtr *grid;
    // grid that contains the board information
    
    // Disallowed methods
    Board( );
    Board(int r, int c);
    Board(const Board&);
    Board& operator=(const Board&);
    
    vector<Player *> LoadBoard( );
    // Loads the board from the file
    // pre:  BOARD_FILE must be ready for input with a data line
    //       for each cell 
    //       first char terrain: C or M or R or S
    //       second char trap: N or B or L or S
    //       if trap then trap data follows:
    //          bug hole data: number of bugs followed by type (H, K, S)
    //          Landmine and sinkhole data: number indicating damage & hazard
    // post: cells are created in row major order
    
    vector<Player *> CreateBugs(int num, char type, vector<Player *>& allBugs);
    // Create the bugs given the number, and type
    // pre:  number and type needs proper values
    // post: bugs are created and appended to the allBugs vector,
    //       new bugs returned from the function.
    
    void PrintLine(ostream& out, int num, string s) const;
    // Prints a line to the output stream
    
    int Offset(int r, int c, int colSize) const;
    // Calculates the offset for the grid given the row & col value
    
    void UpdateRowCol(DirEnum dir, int& r, int & c) const;
    // Returns the updated row and column given the direction and current coor.

    Player * FindPlayer(const PlayerClass *p) const;
    // Finds the Player in the cell when given the PlayerClass object
    // Search is done by the player name.  Name must be unique in the cell!!
    
    int FindNewCell(const Player *p, int units, DirEnum dir) const;
    // Determines the new cell the player is accessing
        
};

#endif


