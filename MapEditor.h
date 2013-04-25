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
#include <cstdio>

#include "Define.h"
#include "Event.h"
#include "Surface.h"
#include "Map.h"
#include "Camera.h"
#include "Entity.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Heart.h"
#include "Chest.h"
#include "Objectives.h"
#include "Timer.h"

using namespace std;
 
class MapEditor : public Event {
  friend class Camera;
  friend class Objectives;

    private:

			bool Running;
			bool Quit;

			// SDL surfaces
			SDL_Surface* Surf_Display;
			SDL_Surface* Tileset;
			SDL_Surface* Menu;
				bool dispMenu;
			SDL_Surface* HeartBar;
			SDL_Surface* Gems;
			SDL_Surface* BulletIndicator;
			SDL_Surface* TitleScreen;
				bool dispTitle;
			SDL_Surface* TitleMenu;
				bool dispTitleMenu;

			SDL_Surface* Player_Character;
			SDL_Surface* Grave;
			SDL_Surface* Objective;
			SDL_Surface* ObjBackground;
			SDL_Surface* Surface_NumPlayerBullets;
				bool dispObjective;

			// SDL Music / Sounds
			Mix_Music* mus;
			Mix_Chunk* sfx2;
			Mix_Chunk* healSound;

			// timer for regulating frame rate
			Timer fps;

        protected:
			static bool debug;  // set to true with command line argument


	public:
			static Mix_Chunk* sfx1; // static so that Bullet can access and play whenever destroyed
	
			// player health
			static int playerHealth;

			// number of player's bullets
			static int numPlayerBullets;

			// game map
			static Map gameMap[4];

			// filenames
			static string filenameSave[4];
			static string filenameLoad[4];
	
			// Fonts
			TTF_Font *XObjectiveFont;
			TTF_Font *BulletDisplayFont;
			SDL_Color XObjectiveTextColor;	
	
			Objectives *ObjPtr;

	public: // need to make get/set functions for these

			// current tile choice; don't think we need anymore
			int currentTileXID;
			int currentTileYID;

			static vector<Entity*> EntityList;
			static int numEnemies;
			static int moveSize;

   public:
			MapEditor(string,string);

        int OnExecute();
				void GameOver();

				bool LoadMaps(); // called after every change of map view
				void AddChests(int); // called the first time any map is loaded

				static bool runLoadMaps;
				static bool runAddChests[4];
			        static bool gotGem[5];

				static void RandomMapGenerate(string="randomMap.map", int[4]=NULL);
				static void RMG_Recursion(int[],int[][40]);
				// tile order: 
				//lava,rock,snow,mountains,snow,rock,dirt,grass,grass,tree,evergreen,grass,grass,sand,water,deepwater
				static int tileX[NUM_TILES];
				static int tileY[NUM_TILES];
				static int tileTypes[NUM_TILES];

    public:

				// initialization method
				bool OnInit();
 
 				// event handling and related methods
        void OnEvent(SDL_Event* Event);
				void OnLButtonDown(int mX, int mY); // When left mouse button clicks, gets position 
				void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
				void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
				void OnStop();
				void OnExit();
			 
				// game data logic and related methods
				void OnLoop();
				static int CheckTileCollision(int=-Camera::CameraControl.GetX()+WWIDTH/2,int=-Camera::CameraControl.GetY()+WHEIGHT/2,int=CHARACTER_W,int=CHARACTER_H);
				void SpawnEnemy();
				void AddBullet();
				bool CheckEntityCollisions();
				void DeSpawnEntities();
				void CheckBulletCollision();
			 
			 	// rendering method
			  void OnRender();

				// saving method
				void OnSave();

				// cleanup method
			  void OnCleanup();

};
 
#endif
