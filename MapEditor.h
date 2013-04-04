#ifndef _MAPEDITOR_H_
    #define _MAPEDITOR_H_
 
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <cmath>

#include <vector>

#include "Define.h"
#include "Event.h"
#include "Surface.h"
#include "Map.h"
#include "Camera.h"
#include "Enemy.h"

using namespace std;
 
class MapEditor : public Event {
    private:
	bool Running;

	// SDL surfaces
	SDL_Surface* Surf_Display;
	SDL_Surface* Control_Display;
	SDL_Surface* Tileset;
	SDL_Surface* Selector;

	SDL_Surface* Main_Character;

	SDL_Surface* Player_Character;


	public:
	// game map
	Map gameMap[4];

	// filenames
	static string filenameSave[4];
	static string filenameLoad[4];

	public: // need to make get/set functions for these

	// current tile choice
	int currentTileXID;
	int currentTileYID;

	static vector<Enemy*> EnemyList;

    public:
        MapEditor();

        int OnExecute();

	bool LoadMaps(); // called after every change of map view
	static bool runLoadMaps;

	static void RandomMapGenerate(string="randomMap.map", int[4]=NULL);
	static void RMG_Recursion(int[],int[][40]);
	// tile order: lava,rock,snow,mountains,snow,rock,dirt,grass,grass,tree,evergreen,grass,grass,sand,water,deepwater
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

	void OnExit();
 
        void OnLoop();
	bool CheckCollision();
	void SpawnEnemy();
 
        void OnRender();

	void OnSave();

        void OnCleanup();

};
 
#endif
