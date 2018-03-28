#include "player6.h"
#include "board.h"

using namespace std;
using namespace GameSpace;

//Constructors
PlayerClass::PlayerClass(void):NAME(EditName(NAME)), STATS(NULL){

}

PlayerClass::PlayerClass(string player_name, char kind):NAME(EditName(NAME)),STATS(NULL){

}

PlayerClass::PlayerClass(string NAME, const int INIT_STATS[], const int INIT_stats[]):dir(EAST),STATS(INIT_STATS),NAME(EditName(NAME)){
  for(int i = 0; i<VAR_STATS;i++){
    stats[i] = INIT_stats[i];
  }
}

//Destructors
PlayerClass::~PlayerClass(void){

}

PlayerClass& PlayerClass::operator=(const PlayerClass& p){
  
  if(this != &p){
    *const_cast<string *>(&NAME) = p.NAME;
    *const_cast<const int **>(&STATS)=p.STATS;
    dir = p.dir;
    for(int i = 0; i<VAR_STATS; i++){
      stats[i] = p.stats[i];
    }
  }
  return * this;
}

//Methods
bool PlayerClass::Active(void){
  if (!IsDead())
    stats[ACTIVE] = true;
  return stats[ACTIVE];
}

bool PlayerClass::InActive(void){
  stats[ACTIVE] = false;
  return true;
}

bool PlayerClass::IsDead(void)const{
  return stats[HEALTH]<=0? true: false;
}

bool PlayerClass::Dead(void){
  stats[HEALTH] = 0;
  stats[WILLPOWER] = 0;
  stats[MOMENTUM] = 0;
  stats[ACTIVE] = false;
  return IsDead();
}

bool PlayerClass::Heal(void){
  if(IsActive()){
    stats[SPEED] = STATS[MAXSPEED];
    stats[HEALTH] += HEAL_VALUE;
    if(stats[HEALTH] >=STATS[MAXHEALTH])
      stats[HEALTH] = STATS[MAXHEALTH];
    }
  return IsActive();
}

bool PlayerClass::SetCell(int newRow, int newCol){
  bool isSuccessful = false;

  if((newRow >= -1) & (newCol >= -1)){ //if valid position...
    stats[ROW] = newRow;
    stats[COL] = newCol;
    isSuccessful = true;
  }

  return isSuccessful;
}

bool PlayerClass::IsAlive(void)const{
  return !IsDead();
}

bool PlayerClass::IsActive(void)const{
  return stats[ACTIVE];
}

bool PlayerClass::CriticalWound(void){
  int colIndex = 0;
  int rowIndex = 0;
  int critical = 0;
  if(IsActive()){
    colIndex = stats[WILLPOWER];
    stats[SPEED] = stats[SPEED]/2;
    stats[WILLPOWER] -= 1;
    stats[HEALTH] -= CRITICAL_HIT_DMG;
    if(stats[MOMENTUM] > stats[SPEED]){ 
      stats[MOMENTUM] = stats[SPEED];
    }
    if((stats[WILLPOWER] <= 0)||(stats[HEALTH] <= 0)){
      Dead();
    }else{
      rowIndex = Dice::Roll(NAME, GameSpace::WOUND, 2, 6);
      critical = WOUND_TABLE[rowIndex][colIndex];
    }
    if(critical == 1){
      Dead();
    }else{
      if(critical == 0){
        cout<<"WOUND_TABLE out of bounds"<<endl;
      }
    }
  }
  return IsAlive();
}

int PlayerClass::ResetMomentum(void){
  if(IsActive()){
    stats[MOMENTUM] = stats[SPEED];
  }
  return stats[MOMENTUM];
}

int PlayerClass::UseMomentum(int amount){
  if(amount>0){
    stats[MOMENTUM] -= amount;
    if(stats[MOMENTUM]<0){
      stats[MOMENTUM] = 0;
    }
  } 
  return stats[MOMENTUM];
}

int PlayerClass::Row(void)const{
  return stats[ROW];
}

int PlayerClass::Column(void)const{
  return stats[COL];
}

int PlayerClass::Health(void)const{
  return stats[HEALTH];
}

int PlayerClass::WillPower(void)const{
  return stats[WILLPOWER];
}

int PlayerClass::MaxSpeed(void)const{
  return STATS[MAXSPEED];
}

int PlayerClass::CurrentSpeed(void)const{
  return stats[SPEED];
}

int PlayerClass::Power(void)const{
  return stats[POWER];
}

int PlayerClass::Armor(void)const{
  return STATS[DAV];
}

int PlayerClass::Momentum(void)const{
  return stats[MOMENTUM];
}

int PlayerClass::SlowDown(int hazard){
  if(IsActive()){
    if(hazard>0){
      if(stats[SPEED] - hazard >= 0){
        stats[SPEED] -= hazard;
        if(stats[SPEED] <= stats[MOMENTUM]){
          stats[MOMENTUM] = stats[SPEED];
        }
      }else{
        stats[SPEED] = 0;
        stats[MOMENTUM] = 0;
      }
    }
  }
  return stats[SPEED];
}

int PlayerClass::ResetCurrentSpeed(void){
  stats[SPEED] = STATS[MAXSPEED];
  return stats[SPEED];
}

int PlayerClass::Wounded(int damage){
  if(damage > 0){
    if(stats[HEALTH] - damage > 0){
      stats[HEALTH] -= damage;
      if(stats[WILLPOWER] <= 0){
        Dead();
      }
    }else{Dead();}
  }
  return stats[HEALTH];
}

int PlayerClass::Damage(void)const{
  int diceRoll = 0;
  int damage = 0;

  if(IsActive()){
    diceRoll = Dice::Roll(NAME, GameSpace::DAMAGE, STATS[NUMDIE], STATS[FACES]);
    if(diceRoll > 1){
      damage = diceRoll + stats[POWER];
    }else{damage = 0;}
  }else{damage = 0;}

  return damage;
}

int PlayerClass::Impact(void)const{
  int impact = 0;
  int colIndex = 0;
  int rowIndex = 0;
  
  if((stats[POWER] >= 2)&&(IsActive())){
    rowIndex = Dice::Roll(NAME, GameSpace::IMPACT, 2, 6);
    if((rowIndex < 13)&&(rowIndex > 1)){
      colIndex = stats[POWER];
    }else{impact = 0;}
  }else{impact = 0;}
  
  return IMPACT_TABLE[rowIndex][colIndex];
}

bool PlayerClass::SetDir(DirEnum d){
  dir=d;
  return true;
}

DirEnum PlayerClass::Direction(void)const{
  return dir;
}

bool PlayerClass::MoveUnits(int x){
  bool move = false;
  if(IsActive()){
    Board * ptr;
    ptr = Board::GetBd();
    move = ptr->MoveForward(this,x);
  }
  return move;
}

bool PlayerClass::CanRun(void)const{
  bool run = false;
  if(IsActive()){
    Board * ptr;
    ptr = Board::GetBd();
    run = stats[MOMENTUM]>=ptr->RunCost(this)?true:false;
  }
  return run;
}

bool PlayerClass::Run(void){
  bool move = false;
  if((CanRun())&&(IsActive())){
    dir=NORTH;
    move = MoveUnits(1);
  }
  return move;
}

string PlayerClass::EditName(string playerName){
  string testStr;
  testStr = playerName;
  string newStr;
  string tmpStr;

  if(!(playerName.length()>20)){
    for(int j = 0; j < testStr.length(); j++){
      if(testStr[j] != ' '){
        testStr.erase(testStr.begin(),testStr.begin()+j);
	j = testStr.length();
      }
    }
    for(int j = testStr.length()-1; j > 0; j--){
      if(testStr[j] != ' '){
        testStr.erase(j+1);
	j = 0;
      }
    }
    for(int i = 0; i < testStr.length(); i++){
      if(isalnum(testStr[i]) || testStr[i] == ' '){
        tmpStr = testStr[i];
	newStr.append(tmpStr);
      }
    }
    if(newStr.length() > 20){
      newStr = "DEFAULT";
    }else{
      playerName = newStr;
    }  
  }else{playerName = "DEFAULT";}
  
  return playerName;
}

string PlayerClass::Name(void)const{
  return NAME;
}

string PlayerClass::NameToUpper(string s)const{
  string str = "";
  int len = s.length();
  
  for(int i=0;i<len;i++){
    str += toupper(s[i]);
  }

  return str;
}

//Overloaded opperators
bool PlayerClass::operator==(const PlayerClass& p)const{
  return NameToUpper(this->NAME) == NameToUpper(p.NAME);
}

bool PlayerClass::operator!=(const PlayerClass& p)const{
  return NameToUpper(this->NAME) != NameToUpper(p.NAME);
}

bool PlayerClass::operator<(const PlayerClass& p)const{
  return NameToUpper(this->NAME) < NameToUpper(p.NAME);
}

bool PlayerClass::operator>(const PlayerClass& p)const{
  return NameToUpper(this->NAME) > NameToUpper(p.NAME);
}

bool PlayerClass::operator<=(const PlayerClass& p)const{
  return NameToUpper(this->NAME) <= NameToUpper(p.NAME);
}

bool PlayerClass::operator>=(const PlayerClass& p)const{
  return NameToUpper(this->NAME) >= NameToUpper(p.NAME);
}

void PlayerClass::Display(ostream& out)const{
  out<<"("<<Row()<<","<<Column()<<")#"<<Health()<<"#"<<WillPower()<<"#"<<CurrentSpeed()<<"#"<<Momentum()<<"#";
  return;
}

const int PlayerClass::IMPACT_TABLE[DIE_ROLL][POWER_RATING]={
/*Power:      0  1  2  3  4  5  6  7  8  9  10 11 12 */
/*Roll: 0*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*Roll: 1*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*Roll: 2*/ { 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10},
/*Roll: 3*/ { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,-1},
/*Roll: 4*/ { 0, 0, 2, 3, 4, 5, 6, 7, 8, 9,10,-1,-1},
/*Roll: 5*/ { 0, 0, 3, 4, 5, 6, 7, 8, 9,10,-1,-1,-1},
/*Roll: 6*/ { 0, 0, 4, 5, 6, 7, 8, 9,10,-1,-1,-1,-1},
/*Roll: 7*/ { 0, 0, 5, 6, 7, 8, 9,10,-1,-1,-1,-1,-1},
/*Roll: 8*/ { 0, 0, 6, 7, 8, 9,10,-1,-1,-1,-1,-1,-1},
/*Roll: 9*/ { 0, 0, 7, 8, 9,10,-1,-1,-1,-1,-1,-1,-1},
/*Roll:10*/ { 0, 0, 8, 9,10,-1,-1,-1,-1,-1,-1,-1,-1},
/*Roll:11*/ { 0, 0, 9,10,-1,-1,-1,-1,-1,-1,-1,-1,-1},
/*Roll:12*/ { 0, 0,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
}; //(note:  -1 = wound)

const int PlayerClass::WOUND_TABLE[DIE_ROLL][WILLPOWER_RATING]={
/*WP Rating:  0  1  2  3  4  5  6  7  8  9  10 11 12
/*Roll: 0*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*Roll: 1*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*Roll: 2*/ { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1},
/*Roll: 3*/ { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1,-1},
/*Roll: 4*/ { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,-1,-1,-1},
/*Roll: 5*/ { 0, 0, 1, 1, 1, 1, 1, 1, 1,-1,-1,-1,-1},
/*Roll: 6*/ { 0, 0, 1, 1, 1, 1, 1, 1,-1,-1,-1,-1,-1},
/*Roll: 7*/ { 0, 0, 1, 1, 1, 1, 1,-1,-1,-1,-1,-1,-1},
/*Roll: 8*/ { 0, 0, 1, 1, 1, 1,-1,-1,-1,-1,-1,-1,-1},
/*Roll: 9*/ { 0, 0, 1, 1, 1,-1,-1,-1,-1,-1,-1,-1,-1},
/*Roll:10*/ { 0, 0, 1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
/*Roll:11*/ { 0, 0, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
/*Roll:12*/ { 0, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
}; //(note: 1 = kill)

