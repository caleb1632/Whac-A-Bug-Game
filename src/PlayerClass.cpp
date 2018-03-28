#include "PlayerClass.h"
#include <iostream>
#include <string>

using namespace std;

void GetStats(CharacterType typeT, PlayerStatsType &stats);
WeaponT GetWeaponStats(Weapons weapon);
void NameToLower(string &s);

//Constructors
PlayerClass::PlayerClass(){
	 

	PlayerStatsType stats;
	characterType = SPIDER;
	GetStats(characterType, stats);
	
	
	cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
	type=Type();
	cout<<type<<endl;
	cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
	
	weapon = stats.weapon;
	
	isActive = false;
	maxHealth = stats.maxHealth;
	health = stats.maxHealth;
	willpower = stats.willpower;
	maxSpeed = stats.maxSpeed;
	currentSpeed = stats.maxSpeed;
	power = stats.power;
	defArmor = stats.defArmor;
	weaponSkill = stats.weaponSkill;
	row = stats.row;
	col = stats.col;
	momentum = stats.maxSpeed;
	physicalDamage = stats.physicalDamage;
	name = DEFAULT_NAME;

}
PlayerClass::PlayerClass(CharacterType typeT, string str){
	

	PlayerStatsType stats;
	GetStats(typeT, stats);
	
	this->characterType = typeT;
	
	weapon = stats.weapon;
	type = Type();
	isActive = false;
	maxHealth = stats.maxHealth;
	health = stats.maxHealth;
	willpower = stats.willpower;
	maxSpeed = stats.maxSpeed;
	currentSpeed = stats.maxSpeed;
	power = stats.power;
	defArmor = stats.defArmor;
	weaponSkill = stats.weaponSkill;
	row = stats.row;
	col = stats.col;
	momentum = stats.maxSpeed;
	physicalDamage = stats.physicalDamage;
	name = str;
}

PlayerClass::PlayerClass(const PlayerClass &otherPlayer, string &otherStr){
	cout<<" * * * * *   COPY CONST   * * * * * "<<endl;
	int i = 0;

	this->characterType = otherPlayer.characterType;
	this->maxHealth = otherPlayer.maxHealth;
	this->health = otherPlayer.health;
	this->willpower = otherPlayer.willpower;
	this->maxSpeed = otherPlayer.maxSpeed;
	this->currentSpeed = otherPlayer.maxSpeed;
	this->power = otherPlayer.power;
	this->defArmor = otherPlayer.defArmor;
	this->weaponSkill = otherPlayer.weaponSkill;
	this->row = otherPlayer.row;						//?
	this->col = otherPlayer.col;						//?
	this->momentum = otherPlayer.momentum;
	this->physicalDamage = otherPlayer.physicalDamage;

	for(i=0;i<otherStr.length();i++){
		this->name += otherStr[i];
		cout<<"copy const   "<<this->name<<endl;
	}

	cout<<" * * * * *   COPY CONST   * * * * * "<<endl;
}

PlayerClass::PlayerClass(CharacterType type, int health1, int maxHealth1, int willpower1, int maxSpeed1, int currentSpeed1, int power1, int defArmor1, int weaponSkill1, int momentum1, int physicalDamage1, int row1, int col1, string name1){
  
	this->characterType = type;
	//weapon = stats.weapon;
  
	health = health1;
	maxHealth = maxHealth1;
	willpower = willpower1;
	maxSpeed = maxSpeed1;
	currentSpeed = currentSpeed1;
	power = power1;
	defArmor = defArmor1;
	weaponSkill = weaponSkill1;
	row = row1;
	col = col1;
	momentum = momentum1;
	physicalDamage = physicalDamage1;
	name = name1;
}
//Methods


// Narative: Makes the player active if they are not dead
// Pre-Conditions: Void
// Post-Conditions: makes isActive true
// 
bool PlayerClass::Active(void){
    bool isSuccessful = false;
    
    if(IsDead() == false){
	isActive = true;
	isSuccessful = true;
    }
    
    return isSuccessful;
}






 //Narative: Makes the player inactive
//Called if player is dying this turn or quits.
 //Pre-Conditions: Void
 //Post-Conditions: makes isActive false
 
 bool PlayerClass::InActive(void){
     bool isSuccessful = false;
     
	isActive = false;
	isSuccessful = true;

     return isSuccessful;
 }



//Narative: Checks if player meets "dead" conditions
//Pre-Conditions: Void
//Post-Conditions: Returns a true or false

bool PlayerClass::IsDead(void){
	bool isSuccessful = false;

	if(health <= DEAD_VALUE){
		isSuccessful = true;
    }
	
	return isSuccessful;
}

//Narative: Kills the player
//    Sets hp and willpower to 0
//    Sets isActive to false
//    Returns true if successfully killed
//Pre-Conditions: Void
//Post-Conditions: health = 0, Willpower = 0, and isActive = 0

 bool PlayerClass::Dead(void){
    
	health = 0;
    willpower = 0;
	//isActive = false;
	//currentSpeed = 0;
	//momentum = 0;
	//defArmor = 0;
	//power = 0;
	//physicalDamage = 0;

	return IsDead();
 }

// Narative: Gives health to player if they are not at max hp
// 	  Resets Momentum
// Pre-Conditions: Void
// Post-Conditions: Returns successful

bool PlayerClass::Heal(void){
	bool isSuccessful = false;
	
	if(currentSpeed == maxSpeed && isActive == true && health < maxHealth){
              
		if((health + HEAL_VALUE) > (maxHealth)){ 
			health = maxHealth;
			isSuccessful = true;
		}
		
		else{
			health += HEAL_VALUE;
			isSuccessful = true;
		
        }
		momentum = 0;
		currentSpeed = maxSpeed;
	}

	return isSuccessful;
}

//Narative: Sets the player cell to newRow, newColumn
// Pre-Conditions: int newRow, int newCol
// Post-Conditions: Returns successful

bool PlayerClass::SetCell(int newRow, int newCol){
	bool isSuccessful = false;
	
	if((newRow >= 0) && (newCol >= 0)){ //if valid position...
	  if(newRow >= MAX_BOARD_ROW){
	    while(newRow >= MAX_BOARD_ROW){
		newRow -= MAX_BOARD_ROW;
	    }
	    row = newRow;
	  }
	  else{
	    row = newRow;
	  }  
	  if(newCol >= MAX_BOARD_COLUMN){
	    while(newCol >= MAX_BOARD_COLUMN){
	      newCol -= MAX_BOARD_COLUMN;
	    }
	    col = newCol;
	  }
	  else{
	    col = newCol;
	  }
	  isSuccessful = true;
	}

	return isSuccessful;
}

// Narative: Returns if the paramater class is an enemy or not
// Pre-Conditions: Player, a pointer to an instance of PlayerClass
// Post-Conditions: Returns if they are an enemy (true) or not (false)

bool PlayerClass::IsMyEnemy(PlayerClass *Player){
	bool isMyEnemy = true;
	
	if(this->characterType == Player->characterType){
		isMyEnemy = false;
	}else{
		if((this->characterType == WARRIOR ||this->characterType == EXPLORER) && (Player->characterType == WARRIOR ||Player->characterType == EXPLORER)){
			isMyEnemy = false;
		}else{
			isMyEnemy = true;
		}
	}


	return isMyEnemy;
}

// Narative: Returns true if player is alive, else return false
// Pre-Conditions: Void
// Post-Conditions: Returns successful

bool PlayerClass::IsAlive(void){
	bool isSuccessful = false;
	
	if(IsDead() == false){
		isSuccessful = true;
    }
	
	return isSuccessful;
}

// Narative: Returns true if player is active, else return false
// Pre-Conditions: Void
// Post-Conditions: Returns successful

bool PlayerClass::IsActive(void){
	return isActive;
}

 //Narative: Resets the player's momentum (start of turn)
 //Pre-Conditions: Void
 //Post-Conditions: momentum = maxSpeed

 int PlayerClass::ResetMomentum(void){
     int returnMomentum = 0;
     
	 momentum = currentSpeed;
	 returnMomentum = momentum;

     return returnMomentum;
 }
    

// Narative: Subtracts amount from the player's momentum
// 	     If amount is more than the momentum left, it will only use
// 		what it can to keep momentum larger or equal to zero
// 	     Returns how much momentum is used
// Pre-Conditions: amount > 0
// Post-Conditions: currentSpeed >= 0
// 		    Return amountUsed

int PlayerClass::UseMomentum(int amount){
	int amountUsed = 0;
	int absValue = 0;

	if(amount > momentum){		// using more than they have
	  amountUsed = momentum;
	  currentSpeed = 0;
	  momentum = 0;
	}  
	else{				// using less than they have
	   amountUsed = amount;
	   momentum -= amount;
	   currentSpeed -=amount;
	}
	
	
	
    return amountUsed;
}

// Narative: Returns the Row Value
// Pre-Conditions: Void
// Post-Conditions: Returns row

int PlayerClass::Row(void){
	return row;
}

// Narative: Returns column value
// Pre-Conditions: Void
// Post-Conditions: Returns col

int PlayerClass::Col(void){
	return col;
}

// Narative: Returns health points
// Pre-Conditions: Void
// Post-Conditions: Returns health

int PlayerClass::Health(void){
	return health;
}

// Narative: Returns willpower points
// Pre-Conditions: Void
// Post-Conditions: Returns willpower

int PlayerClass::Willpower(void){
	return willpower;
}

// Narative: Returns Max Speed points
// Pre-Conditions: Void
// Post-Conditions: Returns maxSpeed

int PlayerClass::MaxSpeed(void){
	return maxSpeed;
}

// Narative: Returns Current Speed points
// Pre-Conditions: Void
// Post-Conditions: Returns currentSpeed

int PlayerClass::CurrentSpeed(void){
	return currentSpeed;
}

// Narative: Returns Power points
// Pre-Conditions: Void
// Post-Conditions: Returns pwer

int PlayerClass::Power(void){
	return power;
}

// Narative: Returns Armor points
// Pre-Conditions: Void
// Post-Conditions: Returns defArmor

int PlayerClass::Armor(void){
	return defArmor;
}

// Narative: Returns Momentum points
// Pre-Conditions: Void
// Post-Conditions: Returns momentum

int PlayerClass::Momentum(void){
	return momentum;
}

int PlayerClass::WeaponSkill(void){
	return weaponSkill;
}

// Narative: Returns Player's name
// Pre-Conditions: Void
// Post-Conditions: Returns name

string PlayerClass::Name(void){
     string testStr;
     testStr = name;
     string newStr;
     string tmpStr;
     
     
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
      
	if(isalnum(testStr[i]) || testStr[i] == ' '){		// its valid if its an alpha or numeric or a space
	  tmpStr = testStr[i];					// make the char from testStr into a string
	  newStr.append(tmpStr);				// append that string onto the new string
	}  
      }
    if(newStr.length() > MAX_NAME_LENGTH){
      newStr = DEFAULT_NAME;
    }  
    else{
      name = newStr;
    }
    return newStr;
}

string PlayerClass::WeaponName(void){
	return this->weapon.name;
}

char PlayerClass::Type(void){
	char returnValue = 'Z';
	switch(characterType){
	case WARRIOR:
		returnValue = 'W';
		break;
	case EXPLORER:
		returnValue = 'E';
		break;
	case HORNET:
		returnValue = 'H';
		break;
	case KILLERANT:
		returnValue = 'K';
		break;
	case SPIDER:
		returnValue = 'S';
		break;
	default: 
		cout << "not a valid class Type()" << endl;
	}

	return returnValue;

}


void NameToLower(string &s){
	string original = s;
	int i = 0;
	s="";

	for(i=0;i<original.length();i++){
		s += tolower(original[i]);
	}

	return;
}

//Overloaded opperators

bool PlayerClass::operator==(const PlayerClass& p) const{
	bool isEqual = false;
	string thisLower = this->name;
	string pLower = p.name;

	NameToLower(thisLower);
	NameToLower(pLower);

	if(strcmp(thisLower.c_str(), pLower.c_str())==0){
		isEqual = true;
	}else{
		isEqual = false;
	}
	cout<<" isEqual "<<isEqual<<endl;
	return isEqual;
}

bool PlayerClass::operator!=(const PlayerClass& p) const{
	bool notEqual = false;

	if(this->operator==(p)==false){
		notEqual = true;
	}
	cout<<" notEqual "<<notEqual<<endl;
	return notEqual;
}

bool PlayerClass::operator<(const PlayerClass& p) const{
	bool thisLess = false;

	string thisLower = this->name;
	string pLower = p.name;

	NameToLower(thisLower);
	NameToLower(pLower);

	if(strcmp(thisLower.c_str(), pLower.c_str()) < (0)){
		thisLess = true;
	}
	
	cout<<" thisLess "<<thisLess<<endl;
	return thisLess;
}

bool PlayerClass::operator>(const PlayerClass& p) const{
	bool thisGreater = false;

	if((this -> operator < (p) == false) && (this -> operator == (p) == false)){
		thisGreater = true;
	}

	cout << " thisGreater " << thisGreater << endl;
	return thisGreater;
}

bool PlayerClass::operator<=(const PlayerClass& p) const{
	bool thisLessOrEqual = false;

	if((this->operator<(p)==true)||(this->operator==(p)==true)){
		thisLessOrEqual = true;
	}

	cout<<" thisLessOrEqual "<<thisLessOrEqual<<endl;
	return thisLessOrEqual;
}

bool PlayerClass::operator>=(const PlayerClass& p) const{
	bool thisGreaterOrEqual = false;

	if((this->operator>(p)==true)||(this->operator==(p)==true)){
		thisGreaterOrEqual = true;
	}

	cout<<" thisGreaterOrEqual "<<thisGreaterOrEqual<<endl;
	return thisGreaterOrEqual;
}

ostream & operator<<(ostream & out ,const PlayerClass &p){
	
	PlayerClass player = p;
	
	out<<"active#"<<player.IsActive()<<"#"<<player.Name()<<"#"<<player.Type()<<"#("<<player.Row()<<", "<<player.Col()<<")#"<<player.Health()
 	   <<"#"<<player.Willpower()<<"#"<<player.CurrentSpeed()<<"#";
	   if(p.weaponSkill > 0){
	     cout<<player.WeaponSkill()<<"#"<<player.WeaponName();
	  }
	   cout<<'\n';

	return out;
}

WeaponT GetWeaponStats(Weapons weapon){

	WeaponT weaponTemp;

	 switch(weapon){
		case PISTOL:
			weaponTemp.name ="Pistol";
			weaponTemp.range = 1;
			weaponTemp.damage = 0;
			weaponTemp.power = 5;
		break;

		case ASSAULT_RIFLE:
			weaponTemp.name = "Assault Rifle";
			weaponTemp.range = 3;
			weaponTemp.damage = 0;
			weaponTemp.power = 11;
		break;

		case GERNADE:
			weaponTemp.name = "Gernade";
			weaponTemp.range = 2;
			weaponTemp.damage = 0;
			weaponTemp.power = 11;

		break;

		case HEAVY_WEAPON:
			weaponTemp.name = "Heavy Weapon";
			weaponTemp.range = 4;
			weaponTemp.damage = 0;
			weaponTemp.power = 9;

		break;
		
		case MELEE:
			weaponTemp.name = "Melee";
			weaponTemp.range = 0;
			weaponTemp.damage = 0;
			weaponTemp.power = 0;
		break;
		
		default:
			cout<<" Not a valid weapon "<<endl;
	 }
	return weaponTemp;
}

void GetStats(CharacterType typeT, PlayerStatsType &stats){

	switch (typeT){
	case WARRIOR:
		stats.type = 'W';
		stats.maxHealth = 81;
		stats.willpower = 9;
		stats.maxSpeed = 5;
		stats.currentSpeed = 5;
		stats.power = 9;
		stats.physicalDamage = DAMAGE;
		stats.defArmor = 8;
		stats.weaponSkill = 5;	
		stats.row = 0;
		stats.col = 0;
		stats.weapon = GetWeaponStats(ASSAULT_RIFLE);
		
		break;

	case EXPLORER:
		stats.type = 'E';
		stats.maxHealth = 42;
		stats.willpower = 7;
		stats.maxSpeed = 8;
		stats.currentSpeed = 8;
		stats.power = 6;
		stats.physicalDamage = DAMAGE;
		stats.defArmor = 0;
		stats.weaponSkill = 10;
		stats.row = 0;
		stats.col = 0;
		stats.weapon = GetWeaponStats(PISTOL);
		
		break;

	case KILLERANT:
		stats.type = 'K';
		stats.maxHealth = 20;
		stats.willpower = 7;
		stats.maxSpeed = 2;
		stats.currentSpeed = 2;
		stats.power = 5;
		stats.physicalDamage = DAMAGE;
		stats.defArmor = 10;
		stats.weaponSkill = 0;
		stats.row = 0;
		stats.col = 0;
		stats.weapon = GetWeaponStats(MELEE);

		break;


	case SPIDER:
		stats.type = 'S';
		stats.maxHealth = 50;
		stats.willpower = 8;
		stats.maxSpeed = 15;
		stats.currentSpeed = 15;
		stats.power = 11;
		stats.physicalDamage = DAMAGE;
		stats.defArmor = 7;
		stats.weaponSkill = 0;
		stats.row = 0;
		stats.col = 0;
		stats.weapon = GetWeaponStats(MELEE);

		break;

	case HORNET:
		stats.type = 'H';
		stats.maxHealth = 60;
		stats.willpower = 9;
		stats.maxSpeed = 8;
		stats.currentSpeed = 8;
		stats.power = 10;
		stats.physicalDamage = DAMAGE;
		stats.defArmor = 8;
		stats.weaponSkill = 0;
		stats.row = 0;
		stats.col = 0;
		stats.weapon = GetWeaponStats(MELEE);

		break;

	default: 
		cout << "not a valid class GetStats()" << endl;

	}


	return;
}
