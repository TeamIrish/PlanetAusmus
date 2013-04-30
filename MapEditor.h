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
#include <cstdlib>

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
 
class MapEditor : public Event
{
	friend class Camera;
	friend class Objectives;

private:

	/*========================
	 * In-Game SDL Surfaces
	 * =======================*/

	SDL_Surface* Surf_Display; // the display surface (the screen)

	SDL_Surface* Tileset; // tileset from which the map is generated

	// HUD surfaces
	SDL_Surface* Menu; // in-game menu
		bool dispMenu; // indicates the menu should be up
	SDL_Surface* HeartBar; // gives the player's health
	SDL_Surface* Gems; // displays the gems the player has collected
	SDL_Surface* Surface_NumPlayerBullets; // displays number of player's bullets
	SDL_Surface* BulletIndicator; // bullet graphic that goes next to bullet count display
	SDL_Surface* Objective; // objective text
	SDL_Surface* ObjBackground; // background for objective text
		bool dispObjective; // indicates whether objective should display
	SDL_Surface* GameOverText; // text for game over
	SDL_Surface* YouWinText; // text for winning state
			
	// player surfaces
	SDL_Surface* Player_Character; // player sprite
	SDL_Surface* Grave; // displays when player dies

	/*==========================
	 * Title Screen SDL Surfaces
	 * =========================*/

	SDL_Surface* TitleScreen; // title screen surface
	SDL_Surface* TitleScreen_StartDepressed; // title screen surface with depressed start button
	SDL_Surface* TitleScreen_AboutDepressed; // title screen surface with depressed about button

	bool dispTitle; // display one of the title screens
	bool displayInitialMenu; // display the initial menu
	bool displayStartDepressedMenu; // start button depressed
	bool displayAboutDepressedMenu; // about button depressed

	SDL_Surface* TitleMenu; // about page surface
	SDL_Surface* TitleMenu_BackDepressed; // about page surface with depressed back button
	
	bool dispPlainTitleMenu; // display the about screen
	bool displayBackDepressedTitleMenu; // back button depressed

	/*===========================
	 * Other Private Data Members
	 * ==========================*/

	// indicators for the game state
	static bool Running; // indicates the main game loop is running
	bool Quit; // set when the game is meant to quit
	bool Replay; // set when the game is meant to replay

	// SDL Music / Sounds
	Mix_Music* mus;
	Mix_Chunk* sfx2;
	Mix_Chunk* healSound;

	Timer fps; // timer for regulating frame rate

protected:
	static bool debug;  // set to true with command line argument

public:

	/*====================
	 * Public Data Members
	 *====================*/

	static Mix_Chunk* sfx1; // static so that Bullet can access and play whenever destroyed
	
	// player state
	static int playerHealth; // player health number
	static int numPlayerBullets;// number of player's bullets

	// indicators for directional motion keys being down
	int a_keyIsDown; // a key for moving left
	int s_keyIsDown; // s key for moving down
	int d_keyIsDown; // d key for moving right
	int w_keyIsDown; // w key for moving up

	// game map; full map composed of two smaller maps
	static Map gameMap[4];

	// filenames
	static string filenameSave[4];
	static string filenameLoad[4];
	
	// Fonts
	TTF_Font *XObjectiveFont;
	TTF_Font *BulletDisplayFont;
	SDL_Color XObjectiveTextColor;	
	
	// objective pointer for current objective
	Objectives *ObjPtr;

	// entity variables
	static vector<Entity*> EntityList;
	static int numEnemies;
	static int moveSize;

	/*===============
	 * Public Methods
	 * ==============*/

	MapEditor(string,string); // constructor

	int OnExecute(); // executes the full application
	
	static bool CheckEndConditions(); // see if end conditions are met
	void GameOver(); // if end conditions indicate game over, take action
	void Win(); // if end conditions indicate win, take action

	bool LoadMaps(); // called after every change of map view
	void AddChests(int); // called the first time any map is loaded

	static bool runLoadMaps;
	static bool runAddChests[4];
		static bool gotGem[5];

	static void RandomMapGenerate(string="randomMap.map", int[4]=NULL);
	static void RMG_Recursion(int[],int[][40]);
	
	// tile order: 
	// lava,rock,snow,mountains,snow,rock,dirt,grass,grass,tree,evergreen,grass,grass,sand,water,deepwater
	static int tileX[NUM_TILES];
	static int tileY[NUM_TILES];
	static int tileTypes[NUM_TILES];

	// initialization methods
	bool OnInit(); // load surfaces and so on
	bool LoadSave(); // read info from save file if it exists
 
 	// event handling and related methods
	void OnEvent(SDL_Event* Event);
	void OnLButtonDown(int mX, int mY); // When left mouse button clicks, gets position 
	void OnLButtonUp(int mX, int mY); // when the left mouse button comes up, gets position
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	void OnStop();
	void OnExit();
			 
	// game data logic and related methods
	void OnLoop();
	void MoveCamera();
	void SpawnEnemy();
	void DeSpawnEntities();
	void AddBullet();
	
	// collision checking
	static int CheckTileCollision(int=-Camera::CameraControl.GetX()+WWIDTH/2,int=-Camera::CameraControl.GetY()+WHEIGHT/2,int=CHARACTER_W,int=CHARACTER_H);
	bool CheckEntityCollisions();
	void CheckBulletCollision();
			 
	// rendering method
	void OnRender();

	// saving method
	void OnSave();

	// cleanup method
	void OnCleanup();
};
 
#endif
