// Benjamin Laws, Matt Rundle, Matt Mahan, Paul Kennedy
// CSE 20212 Final Project

#ifndef ENEMY_H
#define ENEMY_H

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "Define.h"
#include <string>
using namespace std;

class Enemy{
 public:
  Enemy(string,int,int,int=MAP_WIDTH,int=MAP_HEIGHT);
  bool OnRender(SDL_Surface*);
 private:
  SDL_Surface* EnemySprite;
  int width;
  int height;
  int enemyStateX;
  int enemyStateY;
 public:
  double X;
  double Y;
};

#endif
