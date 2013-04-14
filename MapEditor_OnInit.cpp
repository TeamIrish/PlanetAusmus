/*
Team: Matt Rundle, Benjamin Laws, Matt Mahan, Paul Kennedy
File: MapEditor_OnInit.cpp

This is the implementation file for the OnInit() function of the MapEditor class. It handles the initialization
of all SDL components, as well as the loading in of graphics and sounds.
*/

#include "MapEditor.h"

bool MapEditor::OnInit() {

//=====================================================================================
// Initialize all SDL components

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		return false;
	}
	
	// Initialize font 
	if(TTF_Init()==-1) return false;
	

//======================================================================================
// Load the graphics

	// Create window and surface
	if((Surf_Display = SDL_SetVideoMode(WWIDTH,WHEIGHT,32,SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL){
		return false;
	}

	// Load the tileset
	if((Tileset = Surface::OnLoad("./tilesets/grounds32.gif")) == NULL){
		return false;
	}

	// Load player character
	if((Player_Character = Surface::OnLoad("./graphics/character.png")) == NULL){
		return false;
	}	

	// Load Objective Font
 	XObjectiveFont = TTF_OpenFont(OBJ_FONT_TYPE,OBJ_FONT_SIZE); // assign the font and size, which are assigned Define.h
	if(XObjectiveFont==NULL) cout << "Error loading font." << endl;
	SDL_Color XObjectiveTextColor={1,1,1}; // assign color
	
	// Load the Objective Background
	if((ObjBackground = Surface::OnLoad("./graphics/objbackground.png")) == NULL){
		return false;
	}

	

	// Load the menu
	if((Menu = Surface::OnLoad("./graphics/menu.png")) == NULL){
		return false;
	}

	// Load the title screen
	if((TitleScreen = Surface::OnLoad("./graphics/title.png")) == NULL){
		return false;
	}

	// Load the title menu
	if((TitleMenu = Surface::OnLoad("./graphics/titleMenu.png")) == NULL){
		return false;
	}

	// Load the heart bar
	if((HeartBar = Surface::OnLoad("./graphics/hearts.png")) == NULL){
		return false;
	}

	// Load the grave
	if((Grave = Surface::OnLoad("./graphics/grave.png")) == NULL){
		return false;
	}

	// Name the window
	SDL_WM_SetCaption("MapEditor",NULL);

	// Make pink background of following surfaces transparent
	Surface::Transparent(Player_Character,255,0,255);
	Surface::Transparent(Menu,255,0,255);
	Surface::Transparent(TitleMenu,255,0,255);
	Surface::Transparent(HeartBar,255,0,255);
	Surface::Transparent(Grave,255,0,255);

//==========================================================================
// Load map tileset

	for(int i=0;i<4;i++){
  	if((gameMap[i].Surf_Tileset = Surface::OnLoad("./tilesets/grounds32.gif")) == NULL){
  	  return false;
  	}
	}
	
//===============================================================================
// if everything loaded without errors

return true;

}
