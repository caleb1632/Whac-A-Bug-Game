#ifndef _BUG_
#define _BUG_
#include "player6.h"

using namespace std;

class Bug:public PlayerClass{
protected:
  Bug(string name, const int INIT_STATS[], const int INIT_stats[]);
  
  virtual Bug* Clone()const =0;
  
  void TurnClockWise(void);
public:
  virtual bool Move(void) =0;
  virtual bool IsMyEnemy(const PlayerClass* p)const =0;
  virtual void Display(ostream& out)const; 
};

class Hornet:public Bug{
private:
  static const int INIT_STATS[CONST_STATS];
  static const int INIT_stats[VAR_STATS];
  
public:
  Hornet(string name);
  
  Hornet* Clone()const;
  
  virtual bool Move(void);
  virtual bool IsMyEnemy(const PlayerClass* p)const;
  virtual void Display(ostream& out)const;
};

class KillerAnt:public Bug{
private:
  static const int INIT_STATS[CONST_STATS];
  static const int INIT_stats[VAR_STATS];
  
public:
  KillerAnt(string name);
  
  KillerAnt* Clone()const;
  
  virtual bool Move(void);
  virtual bool IsMyEnemy(const PlayerClass* p)const;
  virtual void Display(ostream& out)const;
};

class Spider:public Bug{
private:
  static const int INIT_STATS[CONST_STATS];
  static const int INIT_stats[VAR_STATS];
  
public:
  Spider(string name);
  
  Spider* Clone()const;
  
  virtual bool Move(void);
  virtual bool IsMyEnemy(const PlayerClass* p)const;
  virtual void Display(ostream& out)const;
};

#endif
