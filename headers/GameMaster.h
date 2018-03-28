//GameMaster.h

/********************************************
Caleb Jackman
Program 5, gamemaster
********************************************/

#ifndef _GM_
#define _GM_

#include <fstream>
#include "phc.h"
#include "board.h"
#include <algorithm>

using namespace std;

class GameMaster{
private:
  MapSquadType squadMap;
  VecPlayerType playerVec;
  QueueType playerQue;
  ArmamentType armamentVec;
  ArsenalType arsenalMap;
  SetType liveSet;
  VecSetType liveSetVec;
  Player * currentPlayer;
  MenuRec MenuType;
  
  bool SquadIsAlive(void);
  bool PlayerInSquad(void);
  bool GameCleanUp(void);
  
  //Board creating methods
  bool LoadPlayers(void);
  bool LoadQueue(void);
  bool LoadArmament(void); 
  
  int SquadNumber(void);
  
  string SquadString(void);
  
  void GetWeapon();
  
  //Gameplay methods
  void BugTurn(void);
  void HumanTurn(void);
  void PostTurn(void);
  void PreTurn(void);
  bool EndGame(void);
  
  Weapon::WeaponType TypeFromChar(char c);
  
public:
  GameMaster();
  ~GameMaster();

  //Board creating methods
  bool GameSetup(void);
  bool BoardSetUp(void);

  
  //Gameplay methods
  void PlayGame(void);
  void GameOver(void);
  
};


#endif
