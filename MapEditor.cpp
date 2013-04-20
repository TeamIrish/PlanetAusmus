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

	Running = true;
	Quit = false;

	if(inputarg1=="debug" || inputarg2=="debug"){
	  debug=true;
	  cout<<"DEBUG MODE"<<endl;
	}
	else debug=false;

	if(inputarg1=="ssh" || inputarg2=="ssh"){
	  moveSize = 5;
	  Camera::CameraControl.setAnimTimer(2);
	  cout<<"SSH MODE"<<endl;
	}
	else moveSize = 1;
}


//==============================================================================
//
int MapEditor::OnExecute() {

  srand(time(NULL));

  Camera::CameraControl.ChangeMapView();

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
	    LoadMaps(); // HAVING ERRORS
	    runLoadMaps=false;
	  }

		// Render the output
		OnRender();
		
		// delay for frame rate if needed
		fps.delay_if_needed();
	}

	OnSave(); // doesn't actually do anything anymore... might later, though, if we actually save stuff

	GameOver();

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
