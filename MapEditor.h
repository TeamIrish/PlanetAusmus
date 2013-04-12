/*
Team: Matt Rundle, Benjamin Laws, Matt Mahan, Paul Kennedy
File: MapEditor.h

This is the header file for the MapEditor class, which is the 'overarching' class of the program.
*/

#ifndef _MAPEDITOR_H_
    #define _MAPEDITOR_H_
 
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "Define.h"
#include "Event.h"
#include "Surface.h"
#include "Map.h"
#include "Camera.h"
#include "Entity.h"
#include "Enemy.h"
#include "Objectives.h"

using namespace std;
 
class MapEditor : public Event {
  friend class Camera;

    private:

			bool Running;
			bool Quit;

			// SDL surfaces
			SDL_Surface* Surf_Display;
			SDL_Surface* Tileset;
			SDL_Surface* Menu;
				bool dispMenu;
			SDL_Surface* HeartBar;
			SDL_Surface* TitleScreen;
				bool dispTitle;
			SDL_Surface* TitleMenu;
				bool dispTitleMenu;

			SDL_Surface* Player_Character;
			SDL_Surface* Grave;
			SDL_Surface* Objective;
				bool dispObjective;

        protected:
			static bool debug;  // set to true with command line argument


	public:
	
			// player health
			int playerHealth;

			// game map
			Map gameMap[4];

			// filenames
			static string filenameSave[4];
			static string filenameLoad[4];
	
			// Fonts
			TTF_Font *XObjectiveFont;
			SDL_Color XObjectiveTextColor;	
	
			Objectives *ObjPtr;

	public: // need to make get/set functions for these

			// current tile choice
			int currentTileXID;
			int currentTileYID;

			static vector<Entity*> EntityList;

   public:
        MapEditor(string);

        int OnExecute();
				void GameOver();

				bool LoadMaps(); // called after every change of map view
				static bool runLoadMaps;

				static void RandomMapGenerate(string="randomMap.map", int[4]=NULL);
				static void RMG_Recursion(int[],int[][40]);
				// tile order: 
				//lava,rock,snow,mountains,snow,rock,dirt,grass,grass,tree,evergreen,grass,grass,sand,water,deepwater
				static int tileX[NUM_TILES];
				static int tileY[NUM_TILES];
				static int tileTypes[NUM_TILES];

    public:

				bool OnInit();
 
        void OnEvent(SDL_Event* Event);

				// When left mouse button clicks, gets position 
				void OnLButtonDown(int mX, int mY);

				void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

				void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

				void OnStop();

				void OnExit();
			 
				void OnLoop();
				
				bool CheckCollision();
				void SpawnEnemy();
				bool CheckEnemyCollisions();
				void DeSpawnEnemies();
			 
			  void OnRender();

				void OnSave();

			  void OnCleanup();

};
 
#endif
