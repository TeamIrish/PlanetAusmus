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
	ENTITY_TYPE_ITEM
};

class Entity {

	public:

		Entity(string,int,int,int=MAP_WIDTH,int=MAP_HEIGHT);
		bool OnRender(SDL_Surface*);
		int getX();
	  int getY();
	  int getW();
	  int getH();
	  void changePos(int,int);
	  void OnCleanup();
		void setType(int);
		int getType();

	private:

	  int X;
	  int Y;
		int width;
		int height;
		int entityStateX;
		int entityStateY;
		SDL_Surface* EntitySprite;
		int type;


};
#endif
