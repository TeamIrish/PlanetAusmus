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
  double getX();
  double getY();
  void changePos(int,int);
  void OnCleanup();
 private:
  int X;
  int Y;
  int width;
  int height;
  int enemyStateX;
  int enemyStateY;
  SDL_Surface* EnemySprite;
};

#endif
