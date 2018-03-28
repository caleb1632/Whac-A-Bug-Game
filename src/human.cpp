#include "human.h"

using namespace std;

Human::Human(string name, const string WPN_NAME, const int WPN_SKILL, const int INIT_STATS[], const int INIT_stats[]):PlayerClass(name, INIT_STATS, INIT_stats),wpn(NULL), wpnSkill(WPN_SKILL){
  wpn = new Weapon(WPN_NAME);
}

Human::~Human(){
  delete wpn;
  wpn = NULL;
}

Human::Human(const Human& h):PlayerClass(h),wpn(NULL),wpnSkill(h.wpnSkill){
  if(this != &h){
    if(h.HasWeapon()){
      wpn = new Weapon(h.wpn->WeaponName());
    }else{
      wpn = NULL;
    }
    SetDir(h.Direction());
  }
}

string Human::WeaponName(void)const{
  return wpn!=NULL?wpn->WeaponName():"";
}

int Human::WeaponSkill(void)const{
  return wpnSkill;
}

bool Human::DropWeapon(void){
  bool dropped = false;
  if(IsActive()){  
    if(HasWeapon()){
      delete [] wpn;
      wpn = NULL;
      wpnSkill = 0;
      dropped = true;
    }else{dropped = true;}
  }
  return dropped;
}

bool Human::HasWeapon(void)const{
  return wpn!=NULL ? true : false;
}

bool Human::GrabWeapon(string weapon, int skill){
  if(IsActive()){
    if(HasWeapon()){
      DropWeapon();
    }
    if(Weapon::ValidWeapon(weapon)){
      wpn = new Weapon(weapon);
      wpnSkill = skill;
    }else{
      wpnSkill = 0;
    }
  }
  return HasWeapon();
}

int Human::Damage(void)const{
  int dmg = 0;
  
  if(PlayerClass::IsActive()){
    int power = 0;
    if(HasWeapon()){
      power = wpn->WeaponDamage();
      dmg = power+wpnSkill;
    }else{
      dmg = PlayerClass::Damage();
    }
  }
  return dmg;
}

int Human::Impact(void)const{
  return PlayerClass::Impact();
}

bool Human::Move(void){
  return PlayerClass::MoveUnits(1);
}

void Human::Display(ostream& out)const{
  PlayerClass::Display(out);
  if(wpn)
    out<<WeaponName()<<"#"<<WeaponSkill()<<"#";
  out<<endl;
  return;
}

Human& Human::operator=(const Human& h){
  if(this != &h){
    PlayerClass::operator=(h);
    delete wpn;
    wpn = NULL;
    if(h.HasWeapon()){
      wpn = new Weapon(h.wpn->WeaponName());
    }
    wpnSkill = h.wpnSkill;
    SetDir(h.Direction());
  }
  return * this;
}


bool Human::IsMyEnemy(const PlayerClass* p)const{
  const Human * h;
  h = dynamic_cast<const Human *>(p);
  if(h==NULL)
    return true;
  else
    return false;
}


const int Warrior::INIT_STATS[CONST_STATS]={5, 81, 8, 3, 6};
const int Warrior::INIT_stats[VAR_STATS]={5,81,9,9,5,0,-1,-1};
const int Warrior::WPN_SKILL=5;

const string Warrior::WPN_NAME = "ASSAULT RIFLE";

Warrior::Warrior(string name):Human(name, WPN_NAME, WPN_SKILL, INIT_STATS, INIT_stats){

}

Warrior * Warrior::Clone()const{
  return new Warrior(*this);
}

bool Warrior::Move(void){
  return PlayerClass::MoveUnits(1);
}

void Warrior::Display(ostream& out)const{
  out<<"W"<<"#"<<IsActive()<<"#"<<Name()<<"#";
  Human::Display(out);
  return;
}

const int Explorer::INIT_STATS[CONST_STATS]={8, 42, 0, 1, 6};
const int Explorer::INIT_stats[VAR_STATS]={8,42,7,6,8,0,-1,-1};
const int Explorer::WPN_SKILL=10;

const string Explorer::WPN_NAME = "PISTOL";

Explorer::Explorer(string name):Human(name, WPN_NAME, WPN_SKILL, INIT_STATS, INIT_stats){

}

Explorer * Explorer::Clone()const{
  return new Explorer(*this);
}

bool Explorer::Move(void){
  return PlayerClass::MoveUnits(1);
}

void Explorer::Display(ostream& out)const{
  out<<"E"<<"#"<<IsActive()<<"#"<<Name()<<"#";
  Human::Display(out);
  return;
}
