#include "bug.h"

using namespace std;

Bug::Bug(string name, const int INIT_STATS[], const int INIT_stats[]):PlayerClass(name, INIT_STATS, INIT_stats){

}

void Bug::TurnClockWise(void){
  int dir = Direction();
  dir++;
  if(dir>3)
    dir = 0;
  SetDir(GameSpace::DirEnum(dir));
  return;	
}

void Bug::Display(ostream &out)const{
  PlayerClass::Display(out);
  out<<endl;
  return;
}

const int Hornet::INIT_STATS[CONST_STATS]={8,60,8,3,6};
const int Hornet::INIT_stats[VAR_STATS]={8,60,9,10,8,0,-1,-1};
Hornet::Hornet(string name):Bug(name, INIT_STATS, INIT_stats){
  
}

bool Hornet::Move(void){
  SetDir(GameSpace::DirEnum(EAST));
  int turnCounter = 0;
  bool canMove = false;
  bool moved = false;

  if(IsActive()){
	while((Momentum()>0)&&(turnCounter<4)){
	  canMove = PlayerClass::MoveUnits(2);
	  if(canMove){
		moved = true;
		turnCounter = 0;
	  }else{
		turnCounter++;
		TurnClockWise();
	  }
	}
  }
  SetDir(GameSpace::DirEnum(EAST));
  return moved;
}

bool Hornet::IsMyEnemy(const PlayerClass* p)const{
  const Hornet * h;
  h = dynamic_cast<const Hornet *>(p);
  if(h==NULL)
    return true;
  else
    return false;
}

void Hornet::Display(ostream& out)const{
  out<<"H"<<"#"<<IsActive()<<"#"<<Name()<<"#";
  Bug::Display(out);
  return;
}

Hornet * Hornet::Clone()const{
  return new Hornet(*this);
}

const int KillerAnt::INIT_STATS[CONST_STATS]={2,20,10,2,6};
const int KillerAnt::INIT_stats[VAR_STATS]={2,20,7,5,2,0,-1,-1};

KillerAnt::KillerAnt(string name):Bug(name, INIT_STATS, INIT_stats){
  
}

bool KillerAnt::Move(void){
  SetDir(GameSpace::DirEnum(EAST));
  bool m = true;
  bool moved = true;
  int i = 0;
  while(m){
    m = PlayerClass::MoveUnits(1);
    while((!m)&&(i<3)){
      TurnClockWise();
      m = PlayerClass::MoveUnits(1);
      i++;
    }
    if(m)
      moved = true;
  }
  SetDir(GameSpace::DirEnum(EAST));
  return moved;
}

bool KillerAnt::IsMyEnemy(const PlayerClass* p)const{
  const KillerAnt * k;
  k = dynamic_cast<const KillerAnt *>(p);
  if(k==NULL)
    return true;
  else
    return false;
}

void KillerAnt::Display(ostream& out)const{
  out<<"K"<<"#"<<IsActive()<<"#"<<Name()<<"#";
  Bug::Display(out);
  return;
}

KillerAnt * KillerAnt::Clone()const{
  return new KillerAnt(*this);
}

const int Spider::INIT_STATS[CONST_STATS]={15,50,7,2,6};
const int Spider::INIT_stats[VAR_STATS]={15,50,8,11,15,0,-1,-1};

Spider::Spider(string name):Bug(name, INIT_STATS, INIT_stats){

}

bool Spider::Move(void){
  SetDir(GameSpace::DirEnum(EAST));
  int move = 0;
  int j = 0;
  int i = 0;
  bool m = true;
  bool moved = false;
  bool canmove = true;

  while((canmove)&&(Momentum()>0)){
    if(move<2){
      m = PlayerClass::MoveUnits(1);
      while((!m)&&(i<3)){
        TurnClockWise();
        m = PlayerClass::MoveUnits(1);
        i++;
      }
      moved = m;
      i=0;
      move++;
    }else{
      while((j<move/2+1)&&(m)){
        if(Momentum()>0){
          m = PlayerClass::MoveUnits(1);
          while((!m)&&(i<3)){
            TurnClockWise();
            m = PlayerClass::MoveUnits(1);
            i++;
          }
          i = 0;
          j++;
        }else{
          m = false;
        }
      }
      j=0;
      move++;
    }
    canmove = m;
    TurnClockWise();
  }

  SetDir(GameSpace::DirEnum(EAST));
  return moved;
}

bool Spider::IsMyEnemy(const PlayerClass* p)const{
  const Spider * s;
  s = dynamic_cast<const Spider *>(p);
  if(s==NULL)
    return true;
  else
    return false;
}

void Spider::Display(ostream& out)const{
  out<<"S"<<"#"<<IsActive()<<"#"<<Name()<<"#";
  Bug::Display(out);
  return;
}

Spider * Spider::Clone()const{
  return new Spider(*this);
}
