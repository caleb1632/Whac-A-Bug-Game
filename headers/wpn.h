// wpn.h

#ifndef _WPN
#define _WPN

#include <string>
#include <fstream>
#include <iostream>
//#include "dice.h"
//#include "gamespace.h"

using namespace std;
//using namespace GameSpace;

class Weapon
{
  public:
    
    enum WeaponType {GRENADE, HVYWPN, PISTOL, RIFLE };
    // type of weapon available
    
    static string WpnTypeToStr(WeaponType wpn);
    // converts the WpnType to string
    // pre:  none
    // post: string name is returned
    
    static WeaponType StrToWpnType(string wpn);
    // converts the string to WpnType
    // pre:  none
    // post: wpnType is returned
        
    Weapon(WeaponType wpn);
    // constructor must have type of weapon
    // pre:  wpn must have a type
    // post: wpn is created
    
    Weapon(const string wpn);
    // constructor must have type of weapon spelled correctly
    // pre:  wpn must have a type
    // post: wpn is created, if not a match then pistol is set
    
    string WeaponName( ) const;
    // Returns the name of the weapon
    // pre:  none
    // post: name is returned
    
    int WeaponRange( ) const;
    // Returns the range of the weapon
    // pre:  none
    // post: range of wpn is returned
    
    int WeaponDamage( ) const;
    // Returns the damage rolled
    // pre:  none
    // post: damage is rolled and returned
    
    int WeaponPower( ) const;
    // Returns the power of the wpn
    // pre:  none
    // post: power of wpn is returned

   static bool ValidWeapon(const string weaponName) ;
   // Returns true if the weaponName is valid
   // pre:  none
   // post: returns true if weaponName is valid, false otherwise
      
    void Display(ostream& out) const;
    // wpn name is printed to the stream
    // pre:  none
    // post: name is written to the stream
    
  private:
    Weapon( );
    // default constructor cannot be used
    
    enum WeaponEnum {RNG,NUMDIE,FACES,POW};
    // enum for accessing the wpnTable of data
    
    static const int wpnTable[4][4];
    // table of wpn data
    
    WeaponType wpn;
    // type of wpn
};
    
#endif

