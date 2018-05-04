//GameMaster.h

/********************************************
Caleb Jackman
Program 5, gamemaster
********************************************/

#include "GameMaster.h"
bool Compare(Player* p1, Player* p2);

GameMaster::GameMaster():currentPlayer(NULL){
  
}


GameMaster::~GameMaster(){
}


//Board Creation
bool GameMaster::GameSetup(){
  BoardSetUp();
  LoadPlayers();
  LoadQueue();
  LoadArmament();
  return 0;
}

  bool GameMaster::BoardSetUp(){
	playerVec = Board::CreateBoard(NUMROWS, NUMCOLS);
	return !playerVec.empty();
  }

bool GameMaster::LoadPlayers(){
  ifstream indata;
  char ptype;
  char dir;
  string pname;
  int squad = 0;
  int row;
  int col;
  Player * playerPtr;
  Board * boardPtr = Board::GetBd();  
  
  indata.open(GameSpace::PLAYERS_FILE.c_str());
  while(indata){
	indata>>ptype;
	if(ptype!='q'){
	  indata>>pname>>row>>col>>dir;
	  switch(ptype){
		case 'w':
		  playerVec.push_back(new Player(new Warrior(pname)));
		  break;
		  
		case 'e':
		  playerVec.push_back(new Player(new Explorer(pname)));
		  break;
		  
		case 'k':
		  playerVec.push_back(new Player(new KillerAnt(pname)));
		  break;
		  
		case 'h':
		  playerVec.push_back(new Player(new Hornet(pname)));
		  break;
		  
		case 's':
		  playerVec.push_back(new Player(new Spider(pname)));
		  break;
	  }
	  playerPtr = playerVec[playerVec.size()-1];
	  playerPtr->Active();
	  playerPtr->DropWeapon();
	  playerPtr->SetDir(DirEnum(dir));			//dir is a char...? should be a not char
	  boardPtr->PlacePlayer(playerPtr,row,col);
	  squadMap[pname] = SquadType(squad);
	  liveSet.insert(pname);
	}else{
	  squad++;
	  liveSetVec.push_back(liveSet);
	  liveSet.clear();
	}
  }
  indata.close();
  return !squadMap.empty();
}

bool GameMaster::LoadQueue(void){
  VecPlayerType pvec = playerVec;
  sort(pvec.begin(), pvec.end(), Compare);
  vector<Player *>::iterator i;
  for(i = pvec.begin();i!=pvec.end();i++){
	playerQue.push(*i);
  }
  return !playerQue.empty();
}

bool GameMaster::LoadArmament(void){
  ifstream indata;
  char wtype;
  int amt = 0;
  map<Weapon::WeaponType,int>::iterator iter;
  indata.open(GameSpace::WEAPONS_FILE.c_str());
  
  indata>>wtype>>amt;
  while(indata){
	arsenalMap[TypeFromChar(wtype)] = amt;
	if(wtype=='r'){
	  armamentVec.push_back(arsenalMap);
	  arsenalMap.clear();
	}
	indata>>wtype>>amt;
  }
  indata.close();
  return !armamentVec.empty();
}

bool GameMaster::GameCleanUp(void){
  for(int i=0;i<playerVec.size();i++){
	delete playerVec[i];
  }
  return 0;
}




//Game Play
void GameMaster::PlayGame(void){
  GameSpace::BeginGame(playerQue, liveSetVec, squadMap, armamentVec);
  while(!EndGame()){
	currentPlayer = playerQue.front();
	PreTurn();
	if(IsHuman(currentPlayer)){
          HumanTurn();
	}else{
	  BugTurn();
	}
	PostTurn();
  }
  
  return;
}

void GameMaster::PreTurn(void){
  playerQue.pop();
  currentPlayer->ResetMomentum();
  if(PlayerInSquad()){
	MenuType = GameSpace::BeforeTurn(currentPlayer, SquadString(), armamentVec[SquadNumber()]);
  }else{
	MenuType = GameSpace::BeforeTurn(currentPlayer);
  }
  return;
}

void GameMaster::BugTurn(void){
  if(currentPlayer->IsActive())
	currentPlayer->Move();
  return;
}

void GameMaster::HumanTurn(void){
  if(currentPlayer->IsActive()){
	switch(MenuType.mm){
	  case 'h':
		currentPlayer->Heal();
		break;
	  case 'm':
		currentPlayer->SetDir(CharToDir(MenuType.data1));
		for(int i=0; i<MenuType.data2;i++){
		  currentPlayer->Move();
		}
		break;
	  case 'w':
		GetWeapon();
		break;
	}
  }
  return;
}

void GameMaster::PostTurn(void){
  
  if(PlayerInSquad()){
	GameSpace::AfterTurn(currentPlayer, SquadString(), armamentVec[SquadNumber()], MenuType);
	for(int i = 0; i < playerVec.size(); i++){
	  if(playerVec[i]->IsDead()){
		SquadType tmpSquad = squadMap[playerVec[i]->Name()];
		liveSetVec[tmpSquad].erase(playerVec[i]->Name());
	  }
	}
  }else{
	GameSpace::AfterTurn(currentPlayer);
  }
  playerQue.push(currentPlayer);

  return;
}

void GameMaster::GetWeapon(){
  int squadNum = 0;
  Weapon::WeaponType curWep;
  ArsenalType tempMap;
  string newWep = Weapon::WpnTypeToStr(TypeFromChar(MenuType.data1));
  
  squadNum = squadMap[currentPlayer->Name()];
  tempMap = armamentVec[squadNum];
  if(tempMap[TypeFromChar(MenuType.data1)] > 0){
	if(currentPlayer->HasWeapon()){
	  curWep = Weapon::StrToWpnType(currentPlayer->WeaponName());
	  if(curWep){
		tempMap[curWep]++;
		armamentVec[squadNum] = tempMap;
	  }else{
	    currentPlayer->DropWeapon();
	  }
	}
	currentPlayer->GrabWeapon(newWep,MenuType.data2);
	tempMap[TypeFromChar(MenuType.data1)]--;
	armamentVec[squadNum] = tempMap;
  }
  return;
}


void GameMaster::GameOver(void){
//  if(currentPlayer)
//	delete [] currentPlayer;
  GameSpace::GameOver(playerQue, liveSetVec, squadMap, armamentVec);
  GameCleanUp();
  return;
}


//Helper Methods

bool Compare(Player* p1, Player* p2){
  return p1->operator<(*p2);
}

bool GameMaster::SquadIsAlive(void){
  VecSetType::iterator i = liveSetVec.begin();
  int liveSquads = 0;
  bool squads = false;
  
  while((!squads)&&(i!=liveSetVec.end())){
	if(!(*i).empty()){
	  liveSquads++;
	}
	if(liveSquads>1){
	  squads=true;
	}
	i++;
  }
  return squads;
}

bool GameMaster::PlayerInSquad(void){
  if(squadMap.find(currentPlayer->Name())!=squadMap.end()){
	return true;
  }else{
	return false;
  }
}

bool GameMaster::EndGame(void){
  bool endGame = false;
  
  if(currentPlayer){
	if(SquadIsAlive()){
	  endGame = false;
	}else{
      endGame = true;
	}
  }else{
	endGame = false;
  }	
  return endGame;
}

int GameMaster::SquadNumber(void){ 
  return squadMap[currentPlayer->Name()];
}

string GameMaster::SquadString(void){
  return SquadToStr(squadMap[currentPlayer->Name()]);
}

Weapon::WeaponType GameMaster::TypeFromChar(char c){
  int pos = 0;
  switch(c){
	case 'g':
	  pos = 0;
	  break;
	  
	case 'h':
	  pos = 1;
	  break;
	  
	case 'p':
	  pos = 2;
	  break;
	  
	case 'r':
	  pos = 3;
	  break;
  }
  return Weapon::WeaponType(pos);
}


int main(){
  Dice::ReadRollsFromFile();
  GameMaster gm;
  gm.GameSetup();
  gm.PlayGame();
  gm.GameOver();
  
  cout<<endl<<endl;
  return 0;
}
