#ifndef BULLET_H_
	#define BULLET_H_

#include "MapEditor.h"
#include "Entity.h"

// Bullet class inheriting from Entity
class Bullet : public Entity
{
public:
	Bullet();													// default constructor

	void OnLoop(); 										// carry out the bullet's game logic
	int BulletCheckCollisions();			// return the bullet's collision status
	void onHit();											// respond to a collision
	void OnSave(ofstream &);					// save the bullets in the save file

private:
	int movingV; 											// vertical motion status; 1=down, -1=up
	int movingH; 											// horizontal motion status; 1=right, -1=left
};

#endif
