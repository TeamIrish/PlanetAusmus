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
string MapEditor::filenameSave[4];
string MapEditor::filenameLoad[4];
Map MapEditor::gameMap[4];
vector<Entity*> MapEditor::EntityList;
bool MapEditor::runLoadMaps=false;
bool MapEditor::runAddChests[4];
bool MapEditor::debug;
int MapEditor::moveSize;
int MapEditor::numEnemies;
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
	TitleScreen = NULL;
		dispTitle = true;
	TitleMenu = NULL;
		dispTitleMenu = false;

	Player_Character = NULL;
	Grave = NULL;

	mus = NULL;
	sfx1 = NULL;
	sfx2 = NULL;
	
	// Initialize Font objects to NULL
	TTF_Font *XObjectiveFont = NULL;
		dispObjective = true;

	// Other variables
	currentTileXID=0;
	currentTileYID=1;

	playerHealth = 10;
	numEnemies = 0;

	for(int i=0;i<4;i++) runAddChests[i] = false;

	Running = true;
	Quit = false;

	if(inputarg1=="debug" || inputarg2=="debug"){
	  debug=true;
	  cout<<"DEBUG MODE"<<endl;
	}
	else debug=false;

	if(inputarg1=="ssh" || inputarg2=="ssh"){
	  moveSize = 6;
	  Camera::CameraControl.setAnimTimer(2);
	  cout<<"SSH MODE"<<endl;
	}
	else moveSize = 2;
}


//==============================================================================
//
int MapEditor::OnExecute() {

  srand(time(NULL));

	// Initialize the game; if it fails, return error code and close program
	if(OnInit() == false){
		return -1;
	}

	Camera::CameraControl.ChangeMapView();

	SDL_Event Event;
	ObjPtr = new Objectives; 

	// Enter into the title screen view
	while(dispTitle == true){
		while(SDL_PollEvent(&Event)){
			OnEvent(&Event);
		}
		Surface::OnDraw(Surf_Display,TitleScreen,0,0);
		if(dispTitleMenu) Surface::OnDraw(Surf_Display, TitleMenu, (WWIDTH - MENU_W)/2, (WHEIGHT-MENU_H) / 2);
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
	  if(runLoadMaps==true){
	    LoadMaps();
	    for(int i=0;i<4;i++){ // add chests only if player has not come to this map before
	      if(runAddChests[i]){
		AddChests();
		runAddChests[i] = false;
	      }
	    }
	  }

		// Render the output
		OnRender();
		
		// delay for frame rate if needed
		fps.delay_if_needed();
	}

	if(playerHealth > 0) OnSave(); // doesn't actually do anything anymore... might later, though, if we actually save stuff
	else GameOver();

	// Clean up trash
	OnCleanup();

	return 0;
}


//==============================================================================
//
bool MapEditor::LoadMaps(){
  for(int i=0;i<4;i++){
    if( gameMap[i].OnLoad( "", filenameLoad[i], currentTileXID, currentTileYID ) == false ) {
      cout<<"  Error loading "<<filenameLoad[i]<<endl;
      return false;
    }
  }
  return true;
}

void MapEditor::AddChests(){
      // Add chests
      while(rand()%10 < 2){
	int chestX,chestY,attempts=0;
	while(attempts<100){
	  chestX = rand()%MAP_WIDTH*TILE_SIZE;
	  chestY = rand()%MAP_HEIGHT*TILE_SIZE;
	  if(!CheckTileCollision(chestX,chestY,16,16)) break;
	  attempts++;
	}
	if(attempts<100){
	  Entity * tmp = new Chest(chestX,chestY);
	  tmp->setType(ENTITY_TYPE_CHEST);
	  EntityList.push_back(tmp);
	  if(debug) cout<<"Entity (chest) spawned: "<<chestX/TILE_SIZE<<","<<chestY/TILE_SIZE<<endl;
	}
      }
}

//==============================================================================
//
void MapEditor::GameOver(){
  SDL_Event Event;
  while(!Quit){
    while(SDL_PollEvent(&Event)) OnEvent(&Event);
  }
}


//==============================================================================
//
int main(int argc, char* argv[]) {
  string arg2="",arg1="";
  if(argc>2) arg2 = argv[2];
  if(argc>1) arg1 = argv[1];

  MapEditor theApp(arg1, arg2);
  return theApp.OnExecute();
}
