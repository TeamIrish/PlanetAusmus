#ifndef HEART_H_
	#define HEART_H_

#include "MapEditor.h"
#include "Entity.h"

// represents heart entity dropped randomly by slain enemies
class Heart : public Entity
{
 public:
  Heart(int,int); // constructor
  void OnLoop(); // implement game logic
  void onHit(); // handle collision with player
  void OnSave(ofstream &); // save to file
 private:
  int counter;
};

#endif
