#ifndef _HUMAN_
#define _HUMAN_

#include "wpn.h"
#include "player6.h"

using namespace std;

class Human:public PlayerClass{
private:
  Human();
  Weapon * wpn;

  int wpnSkill;
   
protected:
  Human(string name, const string WPN_NAME, const int WPN_SKILL, const int INIT_STATS[], const int INIT_stats[]);
 virtual Human * Clone()const =0;
   
public:
  
  friend class Player;
  
  Human(const Human& h);
  virtual ~Human(void);

  //Narative: Returns weaponName
  //Pre-Condition: Void
  //Post-Conditions: returns weaponName
  string WeaponName(void)const;

  //Narative: Returns weaponSkill
  //Pre-Condition: Void
  //Post-Conditions: returns weaponSkill
  int WeaponSkill(void)const;
  
  virtual int Damage(void)const;

  virtual int Impact(void)const;

  //Narrative: If the weapon name is a valid weapon name return true
  //Pre-Conditions: weapon name
  //Post-Conditions: True if player has a weapon
  bool HasWeapon(void)const;

  //Narrative: Drops the players current weapon 
  //Pre-Conditions: Player is human
  //Post-Conditions: Returns 1 if the player has a weapon other wise 0
  bool DropWeapon(void);

  //Narrative: Sets the weapon name and skill to the new weapon name and skill
  //Pre-Conditions: Weapon name, weapon, skill
  //Post-Conditions: Set wepaon name to string weapon and skill to int skill 
  bool GrabWeapon(string weapon, int skill);

  virtual bool Move(void);
  
  virtual bool IsMyEnemy(const PlayerClass* p)const;

  Human& operator=(const Human& h);
  
  virtual void Display(ostream& out)const;

};

class Warrior:public Human{
private:
  static const int INIT_STATS[CONST_STATS];
  static const int INIT_stats[VAR_STATS];
  static const int WPN_SKILL;
  
  static const string WPN_NAME;
  
public:
  Warrior(string name);
  
  Warrior * Clone()const;
  
  virtual bool Move(void);
  virtual void Display(ostream& out)const;
};

class Explorer:public Human{
private:
  static const int INIT_STATS[CONST_STATS];
  static const int INIT_stats[VAR_STATS];
  static const int WPN_SKILL;
  
  static const string WPN_NAME;
  
public:
  Explorer(string name);
  
  Explorer * Clone()const;
  
  virtual bool Move(void);
  virtual void Display(ostream& out)const;
};

#endif
