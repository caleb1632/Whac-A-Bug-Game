#ifndef _PLAYER4_
#define _PLAYER4_

#include <cmath>
#include <string>
#include <ostream>
#include <string>
#include <cstring>
#include <typeinfo>
#include "gamespace.h"
#include "dice.h"

using namespace std;

class PlayerClass{
private:
  static const int WILLPOWER_RATING = 13;
  static const int POWER_RATING = 13;
  static const int DIE_ROLL = 13;
  
  DirEnum dir;
	
  PlayerClass();

  const int * const STATS;

  static const int IMPACT_TABLE[DIE_ROLL][POWER_RATING];
  static const int WOUND_TABLE[DIE_ROLL][WILLPOWER_RATING];

  int stats[8];

  bool IsHuman(void)const;

  void SetStats(void);
	
  const string NAME;
  
  string NameToUpper(string s)const;

  virtual PlayerClass* Clone()const =0;

protected:
  PlayerClass(string NAME, const int INIT_STATS[], const int INIT_stats[]);
  bool MoveUnits(int x);

public:
  static const int HEAL_VALUE = 10;
  static const int CONST_STATS = 5;
  static const int CRITICAL_HIT_DMG = 10;
  static const int VAR_STATS = 8;
  
  friend class Player;
  
  enum StatsType{
    SPEED, HEALTH, WILLPOWER, POWER, MOMENTUM, ACTIVE, COL, ROW
  };
  enum ConstType{
    MAXSPEED, MAXHEALTH, DAV, NUMDIE, FACES
  };
  
  //Constructors
  PlayerClass(string player_name, char kind);

  //Destructors
  virtual ~PlayerClass();
  //*************************************************************************************************************
  //Methods

  //Narative: Makes the player active if they are not dead
  //Pre-Conditions: Void
  //Post-Conditions: makes isActive true
  bool Active(void);

  //Narative: Makes the player inactive
  //Called if player is dying this turn or quits.
  //Pre-Conditions: Void
  //Post-Conditions: makes isActive false
  bool InActive(void);

  //Narative: Kills the player
  //Pre-Conditions: Void
  //Post-Conditions: health = 0, WillPower = 0, and isActive = 0
  bool Dead(void);

  //Narative: Gives health to player if they are not at max hp
  //Pre-Conditions: Void
  //Post-Conditions: Returns successful resets Momentum
  bool Heal(void);

  //Narative: Sets the player cell to newRow, newColumn
  //Pre-Conditions: int newRow, int newCol
  //Post-Conditions: Returns successful
  bool SetCell(int newRow, int newCol);

  //Narative: Returns true if player is alive, else return false
  //Pre-Conditions: Void
  //Post-Conditions: Returns successful
  bool IsAlive(void)const;

  //Narative: Checks if player meets "dead" conditions
  //Pre-Conditions: Void
  //Post-Conditions: Returns a true or false
  bool IsDead(void)const;

  //Narative: Returns true if player is active, else return false
  //Pre-Conditions: Void
  //Post-Conditions: Returns successful
  bool IsActive(void)const;
	
  //Narative: Moves player to cell to the north
  //Pre-Conditions: CanRun() is true
  //Post-Conditions: Moves player to the cell to the north
  bool Run(void);
	
  //Narative: Returns true if player can move to the cell to the north
  //Pre-Conditions: Momentum() > 0 and IsActive()
  //Post-Conditions: Return if CanRun
  bool CanRun(void)const;
	
  //Narative: Sets the direction of player
  //Pre-Conditions: N/A
  //Post-Conditions: Player is facing new direction d
  bool SetDir(DirEnum d);
	
  //Narative: Moves the player
  //Pre-Conditions: Momentum() >= Cost to move into the cell 
  //Post-Conditions: Moves player into cell
  virtual bool Move(void) =0;
  
  //Narative: Checks if player is an enemy
  //Pre-Conditions: N/A
  //Post-Conditions: Returns true if enemies false if not enemies
  virtual bool IsMyEnemy(const PlayerClass* p)const =0;
	
  //Narrative: Applies the results of the critical wound to the player and returns wheather the player is alive or not
  //Pre-Conditions: Current speed, Willpower, and health
  //Post-Conditions: Returns 1 if the player is still alive else returns 0
  bool CriticalWound(void);

  //Narative: Resets the player's momentum (start of turn)
  //Pre-Conditions: Void
  //Post-Conditions: momentum = maxSpeed
  int ResetMomentum(void);

  // Narative: Returns the Row Value
  // Pre-Conditions: Void
  // Post-Conditions: Returns row
  int Row(void)const;

  //Narative: Returns column value
  //Pre-Conditions: Void
  //Post-Conditions: Returns column
  int Column(void)const;

  //Narative: Returns health points
  //Pre-Conditions: Void
  //Post-Conditions: Returns health
  int Health(void)const;

  //Narative: Returns willPower points
  //Pre-Conditions: Void
  //Post-Conditions: Returns willPower
  int WillPower(void)const;

  //Narative: Returns Max Speed points
  //Pre-Conditions: Void
  //Post-Conditions: Returns maxSpeed
  int MaxSpeed(void)const;

  //Narative: Returns Current Speed points
  //Pre-Conditions: Void
  //Post-Conditions: Returns currentSpeed
  int CurrentSpeed(void)const;

  //Narative: Returns Power points
  //Pre-Conditions: Void
  //Post-Conditions: Returns pwer
  int Power(void)const;

  //Narative: Returns Armor points
  //Pre-Conditions: Void
  //Post-Conditions: Returns armor
  int Armor(void)const;

  //Narative: Returns Momentum points
  //Pre-Conditions: Void
  //Post-Conditions: Returns momentum
  int Momentum(void)const;

  //Narative: Reduces players momentum by amount
  //Pre-Conditions: amount > 0
  //Post-Conditions: if currentSpeed > momentum currentSpeed = Momentum return momentum
  int UseMomentum(int amount);

  //Narrative: Returns players speed and or momentum subtracted by hazard
  //Pre-Conditions: Hazard, current speed, momentum
  //Post-Conditions: Current speed, momentum
  int SlowDown(int hazard);

  //Narrative: Sets the current speed to the max speed
  //Pre-Conditions: Current speen and max speed
  //Post-Conditions: Return current speed
  int ResetCurrentSpeed(void);

  //Narrative: Reduces players health by paramater amount damage
  //Pre-Conditions: Damage, health, and willpower
  //Post-Conditions: Updates and returns player health
  int Wounded(int damage);

  //Narrative: Uses power/weapon power and dice roll to determine damage dealt
  //Pre-Conditions: Dice roll, power, weapon power
  //Post-Conditions: Returns damage
  virtual int Damage(void)const;

  //Narrative: Returns value from IMPACT_TABLE based on dice roll and power/weapon power rating
  //Pre-Conditions: Dice roll weapon power, power
  //Post-Conditions: IMPACT_TABLE indexed value;
  virtual int Impact(void)const;

  //Narrative: Removes white space and unwanted characters from a string
  //Pre-Conditions: String
  //Post-Conditions: String with no characters, leading, or trailing whitespace
  string EditName(string playerName);

  //Narative: Returns name
  //Pre-Condition: Void
  //Post-Conditions: returns name
  string Name(void)const;
 
  //Narative: Returns direction currently facing
  //Pre-Conditions: N/A
  //Post-Conditions: Returns direction
  DirEnum Direction(void)const;

  //Overloaded operators
  PlayerClass& operator=(const PlayerClass& p);
  bool operator==(const PlayerClass& p)const;
  bool operator!=(const PlayerClass& p)const;
  bool operator<(const PlayerClass& p)const;
  bool operator>(const PlayerClass& p)const;
  bool operator<=(const PlayerClass& p)const;
  bool operator>=(const PlayerClass& p)const;
  virtual void Display(ostream& out)const;
};

#endif
