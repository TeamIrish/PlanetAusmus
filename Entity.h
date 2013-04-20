#ifndef ENTITY_H_
	#define ENTITY_H_

#include "MapEditor.h"
/*
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "Define.h"
#include <string>
using namespace std;
*/
enum {
	ENTITY_TYPE_NONE = 0,

	ENTITY_TYPE_ENEMY,
	ENTITY_TYPE_BULLET,
	ENTITY_TYPE_ITEM,
	ENTITY_TYPE_HEART,
	ENTITY_TYPE_CHEST
};

class Entity {

	public:

  Entity( string="", int=32, int=32, int=MAP_WIDTH, int=MAP_HEIGHT, int=2);
		bool OnRender(SDL_Surface*);
		int getX();
	  int getY();
	  int getW();
	  int getH();
	  void changePos(int,int);
	  void OnCleanup();
	  virtual void OnLoop() = 0;
		void setType(int);
		int getType();
		bool isDestroyable();
		virtual void onHit() = 0;

	protected:

	  int X;
	  int Y;
		int width;
		int height;
		int entityStateX;
		int entityStateY;
		SDL_Surface* EntitySprite;
		int type;
		int speed;
		bool destroy; // set to true when entity should be removed


};
#endif
