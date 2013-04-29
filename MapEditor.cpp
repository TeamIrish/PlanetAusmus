/*
Team: Matt Rundle, Benjamin Laws, Matt Mahan, Paul Kennedy
File: MapEditor.cpp

This is the implementation file for the MapEditor class, which is the 'overarching' class of the program.
*/

#include "MapEditor.h"
#include "Camera.h"
#include <iostream>
using namespace std;

//==============================================================================
// initialize static variables
bool MapEditor::Running;
string MapEditor::filenameSave[4];
string MapEditor::filenameLoad[4];
int MapEditor::playerHealth;
int MapEditor::numPlayerBullets;
bool MapEditor::gotGem[5];
Map MapEditor::gameMap[4];
vector<Entity*> MapEditor::EntityList;
bool MapEditor::runLoadMaps;
bool MapEditor::runAddChests[4];
bool MapEditor::debug;
int MapEditor::moveSize;
int MapEditor::numEnemies;
Mix_Chunk* MapEditor::sfx1;
// tile order: deepwater,water,sand,grass,grass,evergreen,tree,grass,grass,dirt,rock,snow,mountains,snow,rock,lava
int MapEditor::tileX[] = {0,6,3,0,0,6,0,0,0,0,3,3,6,3,3,6};
int MapEditor::tileY[] = {2,1,1,1,1,6,6,1,1,3,0,9,9,9,0,8};
int MapEditor::tileTypes[] = {2,2,1,1,1,3,3,1,1,1,1,1,3,1,1,2}; // 1 = traversable, 2 = shootable, 3 = non-traversable


//==============================================================================
//
MapEditor::MapEditor(string inputarg1,string inputarg2) {

	// Initialize the surfaces to NULL to avoid errors
	Surf_Display = NULL;
	Tileset = NULL;
	Objective=NULL;
	ObjBackground=NULL;
	Menu = NULL;
		dispMenu = false;
	HeartBar = NULL;
	BulletIndicator = NULL;
	Gems = NULL;
	for(int i=0;i<5;i++) gotGem[i] = false;
	TitleScreen = NULL;
		dispTitle = true;
		displayInitialMenu = true;
	TitleScreen_StartDepressed = NULL;
		displayStartDepressedMenu = false;
	TitleScreen_AboutDepressed = NULL;
		displayAboutDepressedMenu = NULL;
	TitleMenu = NULL;
		dispPlainTitleMenu = false;
	TitleMenu_BackDepressed = NULL;
		displayBackDepressedTitleMenu = false;


	Player_Character = NULL;
	Grave = NULL;
	GameOverText = NULL;
	YouWinText = NULL;

	mus = NULL;
	sfx1 = NULL;
	sfx2 = NULL;
	healSound = NULL;
	
	// Initialize Font objects to NULL
	XObjectiveFont = NULL;
		dispObjective = true;

	// Other variables
	currentTileXID=0;
	currentTileYID=1;

	playerHealth = INIT_PLAYER_HEALTH;
	numPlayerBullets = INIT_PLAYER_BULLETS;
	numEnemies = 0;
	EntityList.clear();

	runLoadMaps = false;
	for(int i=0;i<4;i++) runAddChests[i] = false;

	Running = true;
	Quit = false;
	Replay = false;

	if(inputarg1=="debug" || inputarg2=="debug"){
	  debug=true;
	  cout<<"DEBUG MODE"<<endl;
	}
	else debug=false;

	moveSize = 6;
}


//==============================================================================
//
int MapEditor::OnExecute() {

  srand(time(NULL));

  // Initialize the game; if it fails, return error code and close program
  if(OnInit() == false){
    return -1;
  }

  SDL_Event Event;
  ObjPtr = new Objectives; 

  // Enter into the title screen view
  while(dispTitle == true){

    while(SDL_PollEvent(&Event)){
      OnEvent(&Event);
    }

		// if no button is depressed on the main menu
    if(displayInitialMenu == true) Surface::OnDraw(Surf_Display,TitleScreen,0,0);
		
		// if the start button is depressed on the main menu
		if(displayStartDepressedMenu == true) Surface::OnDraw(Surf_Display, TitleScreen_StartDepressed, 0, 0);
		
		// if the about button is depressed on the main menu
		if(displayAboutDepressedMenu == true) Surface::OnDraw(Surf_Display, TitleScreen_AboutDepressed, 0, 0);

		// if meant to display about menu without button depressed
    if(dispPlainTitleMenu) Surface::OnDraw(Surf_Display, TitleMenu, (WWIDTH - MENU_W) / 2, (WHEIGHT-MENU_H) / 2);

		// if meant to display about menu with button depressed
		if(displayBackDepressedTitleMenu) Surface::OnDraw(Surf_Display, TitleMenu_BackDepressed, (WWIDTH - MENU_W) / 2, (WHEIGHT-MENU_H) / 2);

    SDL_Flip(Surf_Display);
  }

  // Main game loop
  while(Running){
    // start the timer to regulate the frame rate
    fps.start();

    // check for events (user input), pass one at a time to OnEvent(
    while( SDL_PollEvent(&Event) ){
      OnEvent(&Event);
      if(Event.type == SDL_QUIT) Quit = true;
    }
		
    // Manipulate data
    OnLoop();

    // switch map view if necessary
    if(runLoadMaps==true) {
      LoadMaps();

      // add chests only if player has not come to this map before
      for(int i=0;i<4;i++) {
				if(runAddChests[i]){
					AddChests(i);
					runAddChests[i] = false;
				}
			}
		}

    // Render the output
    OnRender();
		
    // delay for frame rate if needed
    fps.delay_if_needed();
  }

  if(CheckEndConditions()) {
		cout << "Found win conditions." << endl;
		Win();
	}
  else if(playerHealth > 0) {
		OnSave();
	}
  else {
		cout << "GAme over." << endl;
		GameOver();
	}

  // Clean up trash
  OnCleanup();

  if(Replay) return 2;
  else return 0;
}


//==============================================================================
//
bool MapEditor::LoadMaps()
{
  for(int i=0;i<4;i++) {
		if( gameMap[i].OnLoad("", filenameLoad[i], currentTileXID, currentTileYID) == false ) {
			cout << "  Error loading " << filenameLoad[i] << endl;
      return false;
		}
	}
	return true;
}

void MapEditor::AddChests(int mapID)
{
	// Add chests
	while(rand()%10 < 2) {
		int chestX,chestY,attempts=0;
		
		while(attempts<100) {
		  chestX = (mapID%2)*MAP_WIDTH*TILE_SIZE + rand()%MAP_WIDTH*TILE_SIZE;
		  chestY = (mapID/2)*MAP_HEIGHT*TILE_SIZE + rand()%MAP_HEIGHT*TILE_SIZE;

		  if(!CheckTileCollision(chestX,chestY,16,16)) break;

		  attempts++;
		}
		
		if(attempts < 100) {
			Entity* tmp = new Chest(chestX, chestY);
			tmp->setType(ENTITY_TYPE_CHEST);
			EntityList.push_back(tmp);
			if(debug) cout << "Entity (chest) spawned: " << chestX/TILE_SIZE << "," << chestY/TILE_SIZE << endl;
		}
	}
}

//==============================================================================
//
bool MapEditor::CheckEndConditions(){
  for(int i=0;i<5;i++){
    if(gotGem[i]==false) return false;
  }
  Running = false;
  return true;
}

void MapEditor::GameOver(){
  SDL_Event Event;

  while(!Quit) {
    while(SDL_PollEvent(&Event)) OnEvent(&Event);
  }

  // remove map files, so next game is new
  system("rm maps/*");
}

void MapEditor::Win(){
  SDL_Event Event;

  // display of "you win" graphic
  Surface::OnDraw(Surf_Display,YouWinText,WWIDTH/2-225,WHEIGHT/2-130);
  SDL_Flip(Surf_Display);

  while(!Quit) {
    while(SDL_PollEvent(&Event)) OnEvent(&Event);
  }

  // remove map files, so next game is new
  system("rm maps/*");
}

//==============================================================================
//
// main function; calls OnExecute to run game loop
int main(int argc, char* argv[]) {
  string arg2="",arg1="";
  int out;
  if(argc>2) arg2 = argv[2];
  if(argc>1) arg1 = argv[1];

  do{
    MapEditor* theApp = new MapEditor(arg1, arg2);
    out = theApp->OnExecute();
    delete theApp;
  }while(out == 2);
}
