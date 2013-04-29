#ifndef ENTITY_H_
	#define ENTITY_H_

#include "MapEditor.h"

// enumeration of entity types
enum {
	ENTITY_TYPE_NONE = 0,

	ENTITY_TYPE_ENEMY,
	ENTITY_TYPE_BULLET,
	ENTITY_TYPE_ITEM,
	ENTITY_TYPE_HEART,
	ENTITY_TYPE_CHEST
};

// abstract class describing non-player, non-map elements in the game
class Entity
{
public:
  Entity( string="", int=32, int=32, int=MAP_WIDTH, int=MAP_HEIGHT, int=2); // constructor

	bool OnRender(SDL_Surface*); // blit the entity to the screen

	int getX();
	int getY();
	int getW(); // width
	int getH(); // height
	
	void changePos(int,int);
	void changeState(int,int);
	
	virtual void OnLoop() = 0; // carry out game logic on the entity
	void OnCleanup(); // cleanup the entity's surface and any other dynamic memory
	virtual void onHit() = 0; // handle collisions with player or other entities
	virtual void OnSave(ofstream &) = 0; // save list of entities to file

	// getter and setter for type of entity, e.g. chest, enemy etc.
	void setType(int); 
	int getType();

	void makeDestroyable();
	bool isDestroyable(); 

protected:
	int X; // x coordinate of upper left corner
	int Y; // y coordinate of upper left corner

	int width; // in pixels
	int height; // in pixels

	int entityStateX; // x multiple on the sprite sheet
	int entityStateY; // y multiple on the sprite sheet
	
	SDL_Surface* EntitySprite; // the surface that stores the image of the entity

	string spritefilename; // gives the location of the entity sprite sheet
	
	int type;			// type of the entity, e.g. chest, enemy etc.
	int speed;		// multiplies the entity motion
	
	bool destroy; // set to true when entity should be removed
};
#endif
