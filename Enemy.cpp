// Benjamin Laws, Matt Rundle, Matt Mahan, Paul Kennedy
// CSE 20212 Final Project

#include "Enemy.h"
#include "MapEditor.h"

Enemy::Enemy(string file,int w,int h,int x,int y){
  string fullfilename = "graphics/"+file;
  EnemySprite = Surface::OnLoad(fullfilename.c_str());
  width = w;
  height = h;
  X = x;
  Y = y;
}

bool Enemy::OnRender(SDL_Surface* Display){
  if(Surface::OnDraw(Display,EnemySprite,X+Camera::CameraControl.GetX()-width/2,Y+Camera::CameraControl.GetY()-height/2,enemyStateX*width,enemyStateY*height,width,height) == false) return false;

  return true;
}

