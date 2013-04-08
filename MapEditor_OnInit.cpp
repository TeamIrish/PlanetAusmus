#include "MapEditor.h"

bool MapEditor::OnInit() {

//=====================================================================================
// Initialize all SDL components

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		return false;
	}

//======================================================================================
// Load the graphics

	// Create window and surface
	if((Surf_Display = SDL_SetVideoMode(WWIDTH,WHEIGHT,32,SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL){
		return false;
	}

	if((Tileset = Surface::OnLoad("./tilesets/grounds32.gif")) == NULL){
		return false;
	}

	// Load player character
	if((Player_Character = Surface::OnLoad("./graphics/character.png")) == NULL){
		return false;
	}	

	// Load the menu
	if((Menu = Surface::OnLoad("./graphics/menu.png")) == NULL){
		return false;
	}

	// Name the window
	SDL_WM_SetCaption("MapEditor",NULL);

	// Make the pink background transparent
	Surface::Transparent(Player_Character,255,0,255);
	Surface::Transparent(Menu,255,0,255);

	//==========================================================================
	// Load map tileset

	for(int i=0;i<4;i++){
	  if((gameMap[i].Surf_Tileset = Surface::OnLoad("./tilesets/grounds32.gif")) == NULL){
	    return false;
	  }
	}

//==============================================================================
// Set keyboard repeat count

// Disabled key repeat because it was messing up selection of tiles
// SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

//===============================================================================
// if everything loaded without errors

return true;

}
