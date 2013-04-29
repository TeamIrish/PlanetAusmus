#include "MapEditor.h"

void MapEditor::OnCleanup() {

	// Free the surfaces
	SDL_FreeSurface(Surf_Display);
	SDL_FreeSurface(Tileset);
	SDL_FreeSurface(Player_Character);
	SDL_FreeSurface(Objective);
	SDL_FreeSurface(Menu);
	SDL_FreeSurface(HeartBar);
	SDL_FreeSurface(Gems);
	SDL_FreeSurface(BulletIndicator);
	SDL_FreeSurface(Grave);
	SDL_FreeSurface(GameOverText);
	SDL_FreeSurface(YouWinText);
	SDL_FreeSurface(TitleScreen);
	SDL_FreeSurface(TitleMenu);
	SDL_FreeSurface(Grave);
	SDL_FreeSurface(ObjBackground);
	SDL_FreeSurface(Surface_NumPlayerBullets);
	SDL_FreeSurface(TitleScreen_StartDepressed);
	SDL_FreeSurface(TitleScreen_AboutDepressed);
	SDL_FreeSurface(TitleMenu_BackDepressed);

	
	for(int i = 0; i < 4; ++i) SDL_FreeSurface(gameMap[i].Surf_Tileset);
	for(unsigned int i = 0; i < MapEditor::EntityList.size(); ++i) {
	  EntityList[i]->OnCleanup();
	  delete EntityList[i];
	}

	// Clean up the music/sounds
	Mix_FreeMusic(mus);
	Mix_FreeChunk(sfx1);
	Mix_FreeChunk(sfx2);

	Mix_CloseAudio();

	// Quit out of SDL
	SDL_Quit();
}
