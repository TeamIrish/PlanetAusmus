// Benjamin Laws, Matt Rundle, Matt Mahan, Paul Kennedy
// CSE 20212 Final Project

#ifndef ENEMY_H
#define ENEMY_H

#include "MapEditor.h"
//#include "Entity.h"

/*
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "Define.h"
#include <string>
*/
using namespace std;

class Enemy : public Entity {
 public:
  Enemy(string="",int=32,int=32,int=MAP_WIDTH,int=MAP_HEIGHT,int=1,int=3);
  void OnLoop();
  void onHit();
 private:
  int health;
};

#endif
