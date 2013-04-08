#include "MapEditor.h"

void MapEditor::OnCleanup() {

	// Free the surfaces
	SDL_FreeSurface(Surf_Display);
	SDL_FreeSurface(Control_Display);
	SDL_FreeSurface(Tileset);
	SDL_FreeSurface(Selector);
	SDL_FreeSurface(Player_Character);
	SDL_FreeSurface(Menu);
	for(int i=0;i<4;i++) SDL_FreeSurface(gameMap[i].Surf_Tileset);
	for(int i=0;i<MapEditor::EnemyList.size();i++){
	  EnemyList[i]->OnCleanup();
	  delete EnemyList[i];
	}

	// Quit out of SDL
	SDL_Quit();
}
