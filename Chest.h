#ifndef CHEST_H_
	#define CHEST_H_

#include "MapEditor.h"
#include "Entity.h"

// represents a treasure chest; inherits from entity
class Chest : public Entity {
 public:
  Chest(int,int); // constructor

  void OnLoop(); // carry out game logic on the chest
  void onHit(); // handle a collision
  void OnSave(ofstream &); // save the map's chests to the file
  void OpenChest(); // decide what a chest contains and set it up to open
 private:
  int counter;  // used for opening animation
};

#endif
