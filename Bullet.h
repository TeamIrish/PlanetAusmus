#ifndef BULLET_H_
	#define BULLET_H_

#include "MapEditor.h"
#include "Entity.h"

class Bullet : public Entity {
 public:
  Bullet();
  void OnLoop();
  int BulletCheckCollisions();
  void onHit();
  void OnSave(ofstream &);
 private:
  int movingV; // 1=down, -1=up
  int movingH; // 1=right, -1=left
};

#endif
