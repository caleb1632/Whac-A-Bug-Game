#include "handle.h"

Player::Player():p(NULL){
  
}

Player::Player(const string name, PlayerType type):p(NULL){
  switch(type){
    case WARRIOR:
      p = new Warrior(name);
      break;
    case HORNET:
      p = new Hornet(name);
      break;
    case KILLERANT:
      p = new KillerAnt(name);
      break;
    case SPIDER:
      p = new Spider(name);
      break;
    default:
      p = new Explorer(name);
  }
}

Player::Player(const Player& player):p(NULL){
  CopyIntoMe(player);
}

Player::Player(PlayerClass* ptr):p(ptr){
   
}

Player::~Player(){
  delete p;
  p = NULL;
}

void Player::Display(ostream& out)const{
  if(p){
    p->Display(out);
  }
  return;
}

void Player::CopyIntoMe(const Player& player){
  delete p;
  p = NULL;
  if(player.p != NULL){
    p = player.p->Clone();
  }
  return;
}

Player& Player::operator=(const Player& player){
  if(this != &player){
    CopyIntoMe(player);
  }
  return * this;
}

bool Player::IsAlive(void)const{
  if(p)
    return p->IsAlive();
  else
    return false;
}

bool Player::IsDead(void)const{
  if(p)
    return p->IsDead();
  else
    return false;
}

bool Player::IsActive(void)const{
  if(p)
    return p->IsActive();
  else
    return false;
}

bool Player::CanRun(void)const{
  if(p)
    return p->CanRun();
  else
    return false;
}
  
bool Player::HasWeapon(void)const{
  Human * h;
  h = dynamic_cast<Human *>(p);
  if(h)
    return h->HasWeapon();
  else
    return false;
}
  
DirEnum Player::Direction(void)const{
  if(p)
    return p->Direction();
  else
    return EAST;
}  

int Player::Row(void)const{
  if(p)
    return p->Row();
  else
    return 0;
}

int Player::Column(void)const{
  if(p)
    return p->Column();
  else
    return 0;
}

int Player::Health(void)const{
  if(p)
    return p->Health();
  else
    return 0;
}

int Player::WillPower(void)const{
  if(p)
    return p->WillPower();
  else
    return 0;
}

int Player::MaxSpeed(void)const{
  if(p)
    return p->MaxSpeed();
  else
    return 0;
}

int Player::CurrentSpeed(void)const{
  if(p)
    return p->CurrentSpeed();
  else
    return 0;
}

int Player::Power(void)const{
  if(p)
    return p->Power();
  else
    return 0;
}

int Player::Armor(void)const{
  if(p)
    return p->Armor();
  else
    return 0;
}

int Player::Momentum(void)const{
  if(p)
    return p->Momentum();
  else
    return 0;
}

int Player::Damage(void)const{
  if(p)
    return p->Damage();
  else
    return 0;
}

int Player::Impact(void)const{
  if(p)
    return p->Impact();
  else
    return 0;
}
  
int Player::WeaponSkill(void)const{
  Human * h;
  h = dynamic_cast<Human *>(p);
  if(h)
    return h->WeaponSkill();
  else
    return 0;
}
  
string Player::Name(void)const{
  if(p)
    return p->Name();
  else
    return "";
}
  
string Player::WeaponName(void)const{
  Human * h;
  h = dynamic_cast<Human *>(p);
  if(h)
    return h->WeaponName();
  else
    return "";
}

bool Player::Active(void){
  if(p)
    return p->Active();
  else
    return false;
}

bool Player::InActive(void){
  if(p)
    return p->InActive();
  else
    return false;
}

bool Player::Dead(void){
  if(p)
    return p->Dead();
  else
    return false;
}

bool Player::Heal(void){
  if(p)
    return p->Heal();
  else
    return false;
}

bool Player::SetCell(int newRow, int newCol){
  if(p)
    return p->SetCell(newRow, newCol);
  else
    return false;
}

bool Player::Run(void){
  if(p)
    return p->Run();
  else
    return false;
}

bool Player::SetDir(DirEnum d){
  if(p)
    return p->SetDir(d);
  else
    return false;
}

bool Player::Move(void){
  if(p)
    return p->Move();
  else
    return false;
}

bool Player::CriticalWound(void){
  if(p)
    return p->CriticalWound();
  else
    return false;
}
  
bool Player::DropWeapon(void){
  Human * h;
  h = dynamic_cast<Human *>(p);
  if(h)
    return h->DropWeapon();
  else
    return false;
}

bool Player::GrabWeapon(string weapon, int skill){
  Human * h;
  h = dynamic_cast<Human *>(p);
  if(h)
    return h->GrabWeapon(weapon, skill);
  else
    return false;
}

bool Player::IsMyEnemy(const Player &ptr)const{
  if((p)&&(ptr.p)){
   return p->IsMyEnemy(ptr.p);    
  }else{
    return false;
  }
}

int Player::ResetMomentum(void){
  if(p)
    return p->ResetMomentum();
  else
    return 0;
}

int Player::UseMomentum(int amount){
  if(p)
    return p->UseMomentum(amount);
  else
    return 0;
}

int Player::SlowDown(int hazard){
  if(p)
    return p->SlowDown(hazard);
  else
    return 0;
}

int Player::ResetCurrentSpeed(void){
  if(p)
    return p->ResetCurrentSpeed();
  else
    return 0;
}

int Player::Wounded(int damage){
  if(p)
    return p->Wounded(damage);
  else
    return 0;
}

bool Player::operator==(const Player& player)const{
  if((p)&&(player.p))
    return (*p == *(player.p));
  else
    return false;
}

bool Player::operator!=(const Player& player)const{
  if((p)&&(player.p))
    return !Player::operator==(player);
  else
    return false;
}

bool Player::operator<=(const Player& player)const{
  if((p)&&(player.p))
    return (*p <= *(player.p));
  else
    return false;
}

bool Player::operator>=(const Player& player)const{
  if((p)&&(player.p))
    return (*p >= *(player.p));
  else
    return false;
}

bool Player::operator<(const Player& player)const{
  if((p)&&(player.p))
    return (*p < *(player.p));
  else
    return false;  
}

bool Player::operator>(const Player& player)const{
  if((p)&&(player.p))
    return (*p > *(player.p));
  else
    return false;  
  
}
