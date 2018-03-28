#include "human.h"
#include "bug.h"
  
class Player{
private:
  PlayerClass* p;
  void CopyIntoMe(const Player& player);
public:
  enum PlayerType{
    EXPLORER, WARRIOR, HORNET, KILLERANT, SPIDER
  };
  
  Player();
  ~Player();
  Player(const string name, PlayerType type=EXPLORER);
  Player(const Player& player);
  Player(PlayerClass* ptr);
  
  Player& operator=(const Player& player);
  
  
/*************************************************************************************************************/
/*Observers*/
  
  //Narative: Returns true if player is alive, else return false
  //Pre-Conditions: N/A
  //Post-Conditions: Returns successful
  bool IsAlive(void)const;
  
  //Narative: Checks if player meets "dead" conditions
  //Pre-Conditions: N/A
  //Post-Conditions: Returns a true or false 
  bool IsDead(void)const;
  
  //Narative: Returns true if player is active, else return false
  //Pre-Conditions: N/A
  //Post-Conditions: Returns successful
  bool IsActive(void)const;
  
  //Narative: Returns true if player can move to the cell to the north
  //Pre-Conditions: Momentum() > 0 and IsActive()
  //Post-Conditions: Return if CanRun
  bool CanRun(void)const;
  
  //Narative: Checks if player is an enemy
  //Pre-Conditions: N/A
  //Post-Conditions: Returns true if enemies false if not enemies
  bool IsMyEnemy(const Player &ptr)const;
  
  //Narrative: If the weapon name is a valid weapon name return true
  //Pre-Conditions: weapon name
  //Post-Conditions: True if player has a weapon
  bool HasWeapon(void)const;
  
  //Narative: Returns direction currently facing
  //Pre-Conditions: N/A
  //Post-Conditions: Returns direction
  DirEnum Direction(void)const;
  
  //Narative: Returns the Row Value
  //Pre-Conditions: N/A
  //Post-Conditions: Returns row
  int Row(void)const;
  
  //Narative: Returns column value
  //Pre-Conditions: N/A
  //Post-Conditions: Returns column
  int Column(void)const;
  
  //Narative: Returns health points
  //Pre-Conditions: N/A
  //Post-Conditions: Returns health
  int Health(void)const;
  
  //Narative: Returns willPower points
  //Pre-Conditions: N/A
  //Post-Conditions: Returns willPower
  int WillPower(void)const;
  
  //Narative: Returns Max Speed points
  //Pre-Conditions: N/A
  //Post-Conditions: Returns maxSpeed
  int MaxSpeed(void)const;
  
  //Narative: Returns Current Speed points
  //Pre-Conditions: N/A
  //Post-Conditions: Returns currentSpeed
  int CurrentSpeed(void)const;
  
  //Narative: Returns Power points
  //Pre-Conditions: N/A
  //Post-Conditions: Returns pwer
  int Power(void)const;
  
  //Narative: Returns Armor points
  //Pre-Conditions: N/A
  //Post-Conditions: Returns armor
  int Armor(void)const;
  
  //Narative: Returns Momentum points
  //Pre-Conditions: N/A
  //Post-Conditions: Returns momentum
  int Momentum(void)const;
  
  //Narrative: Uses power/weapon power and dice roll to determine damage dealt
  //Pre-Conditions: Dice roll, power, weapon power
  //Post-Conditions: Returns damage
  int Damage(void)const;
  
  //Narrative: Returns value from IMPACT_TABLE based on dice roll and power/weapon power rating
  //Pre-Conditions: Dice roll weapon power, power
  //Post-Conditions: IMPACT_TABLE indexed value;
  int Impact(void)const;
  
  //Narative: Returns weaponSkill
  //Pre-Condition: N/A
  //Post-Conditions: returns weaponSkill
  int WeaponSkill(void)const;
  
  //Narative: Returns name
  //Pre-Condition: N/A
  //Post-Conditions: returns name
  string Name(void)const; 
  
  //Narative: Returns weaponName
  //Pre-Condition: N/A
  //Post-Conditions: returns weaponName
  string WeaponName(void)const;
  
  //Narrative: Prints player information
  //Pre-Condition: N/A
  //Post-Condition: Prints player information to the ostream
  void Display(ostream& out)const;
  
/*************************************************************************************************************/ 
/*Transformers*/
  
  //Narative: Makes the player active if they are not dead
  //Pre-Conditions: N/A
  //Post-Conditions: makes isActive true
  bool Active(void);
  
  //Narative: Makes the player inactive
  //Called if player is dying this turn or quits.
  //Pre-Conditions: N/A
  //Post-Conditions: makes isActive false
  bool InActive(void);
  
  //Narative: Kills the player
  //Pre-Conditions: N/A
  //Post-Conditions: health = 0, WillPower = 0, and isActive = 0 returns true
  bool Dead(void);
  
  //Narative: Gives health to player if they are not at max hp
  //Pre-Conditions: N/A
  //Post-Conditions: Returns successful resets Momentum
  bool Heal(void);
  
  //Narative: Sets the player cell to newRow, newColumn
  //Pre-Conditions: int newRow, int newCol
  //Post-Conditions: Returns successful
  bool SetCell(int newRow, int newCol);
  
  //Narative: Moves player to cell to the north
  //Pre-Conditions: CanRun() is true
  //Post-Conditions: Moves player to the cell to the north
  bool Run(void);	
  
  //Narative: Sets the direction of player
  //Pre-Conditions: N/A
  //Post-Conditions: Player is facing new direction d
  bool SetDir(DirEnum d);	
  
  //Narative: Moves the player
  //Pre-Conditions: Momentum() >= Cost to move into the cell 
  //Post-Conditions: Moves player into cell
  bool Move(void);
  
  //Narrative: Applies the results of the critical wound to the player and returns wheather the player is alive or not
  //Pre-Conditions: Current speed, Willpower, and health
  //Post-Conditions: Returns 1 if the player is still alive else returns 0
  bool CriticalWound(void);
  
  //Narrative: Drops the players current weapon 
  //Pre-Conditions: Player is human
  //Post-Conditions: Returns 1 if the player has a weapon other wise 0
  bool DropWeapon(void);
  
  //Narrative: Sets the weapon name and skill to the new weapon name and skill
  //Pre-Conditions: Weapon name, weapon, skill
  //Post-Conditions: Set wepaon name to string weapon and skill to int skill
  bool GrabWeapon(string weapon, int skill);
  
  //Narative: Resets the player's momentum (start of turn)
  //Pre-Conditions: N/A
  //Post-Conditions: momentum = maxSpeed
  int ResetMomentum(void);
  
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
  
/*************************************************************************************************************/
/*Overloaded Operators*/
  
  bool operator==(const Player& player)const;
  bool operator!=(const Player& player)const;
  bool operator<=(const Player& player)const;
  bool operator>=(const Player& player)const;
  bool operator<(const Player& player)const;
  bool operator>(const Player& player)const;
};
