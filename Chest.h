#ifndef CHEST_H_
	#define CHEST_H_

#include "MapEditor.h"
#include "Entity.h"

class Chest : public Entity {
 public:
  Chest(int,int);
  void OnLoop();
  void onHit();
 private:
  bool opened;
};

#endif
