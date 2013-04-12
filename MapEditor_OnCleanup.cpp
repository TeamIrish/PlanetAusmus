#include "MapEditor.h"

void MapEditor::OnCleanup() {

	// Free the surfaces
	SDL_FreeSurface(Surf_Display);
	SDL_FreeSurface(Tileset);
	SDL_FreeSurface(Player_Character);
	SDL_FreeSurface(Objective);
	SDL_FreeSurface(Menu);
	SDL_FreeSurface(HeartBar);
	SDL_FreeSurface(TitleScreen);
	SDL_FreeSurface(TitleMenu);
	SDL_FreeSurface(Grave);
	SDL_FreeSurface(ObjBackground);

	
	for(int i=0;i<4;i++) SDL_FreeSurface(gameMap[i].Surf_Tileset);
	for(int i=0;i<MapEditor::EntityList.size();i++){
	  EntityList[i]->OnCleanup();
	  delete EntityList[i];
	}

	// Quit out of SDL
	SDL_Quit();
}
