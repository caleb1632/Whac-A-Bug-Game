#ifndef _PLAYERCLASS
#define _PLAYERCLASS

#include <cmath>
#include <string>
#include <ostream>
#include <cstring>

using namespace std;

	const int DAMAGE = 100;
	const int HEAL_VALUE = 10;
	const int DEAD_VALUE = 0;
	const int MAX_NAME_LENGTH = 20;
	const string DEFAULT_NAME = "DEFAULT";
	const int MAX_BOARD_ROW = 3;
	const int MAX_BOARD_COLUMN = 4;

	enum CharacterType{
		WARRIOR, EXPLORER, KILLERANT, SPIDER, HORNET, CHARACTER
	};
	enum Weapons{
		PISTOL, ASSAULT_RIFLE, GERNADE, HEAVY_WEAPON, MELEE
	};
	
	struct WeaponT{
		Weapons weapon;

		string name;

		int range;
		int damage;
		int power;
	};
	struct PlayerStatsType{
		char type;
		
		int health;
		int maxHealth;
		int willpower;
		int maxSpeed;
		int currentSpeed;
		int power;
		int defArmor;
		int weaponSkill;
		int momentum;
		int physicalDamage;
		int row;
		int col;

		WeaponT weapon;
	};


class PlayerClass{

//private:
public:
	WeaponT weapons;
	CharacterType characterType;
	

	WeaponT weapon;

	bool isActive;

	char type;

	int health;
	int maxHealth;
	int willpower;
	int maxSpeed;
	int currentSpeed;
	int power;
	int defArmor;
	int weaponSkill;
	int row;
	int col;
	int momentum;
	int physicalDamage;

	string name;

	//DiceT physicalDamage;

//public:


	//Constructors
	PlayerClass();
	PlayerClass(CharacterType typeT, string str);
	PlayerClass(const PlayerClass &other, string &otherStr);
	PlayerClass(CharacterType typeT, int health, int maxHealth, int willpower, int maxSpeed, int currentSpeed, int power, int defArmor, int weaponSkill, int momentum, int physicalDamage, int row, int col, string name);

	//Methods
	bool Active(void);
	bool InActive(void);
	bool Dead(void);
	bool Heal(void);
	bool SetCell(int newRow, int newCol);
	bool IsMyEnemy(PlayerClass *Player);
	bool IsAlive(void);
	bool IsDead(void);
	bool IsActive(void);
	
	int ResetMomentum(void);
	int UseMomentum(int amount);
	int Row(void);
	int Col(void);
	int Health(void);
	int Willpower(void);
	int MaxSpeed(void);
	int CurrentSpeed(void);
	int Power(void);
	int Armor(void);
	int Momentum(void);
	int WeaponSkill(void);

	string WeaponName(void);
	string Name(void);

	char Type(void);

	//Overloaded operators
	bool operator==(const PlayerClass& p) const;
	bool operator!=(const PlayerClass& p) const;
	bool operator<(const PlayerClass& p) const;
	bool operator>(const PlayerClass& p) const;
	bool operator<=(const PlayerClass& p) const;
	bool operator>=(const PlayerClass& p) const;

	friend ostream & operator<<(ostream & out, const PlayerClass &p);

};


#endif
