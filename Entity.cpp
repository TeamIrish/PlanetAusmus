// Benjamin Laws, Matt Rundle, Matt Mahan, Paul Kennedy
// CSE 20212 Final Project

//#include "Entity.h"
#include "MapEditor.h"

Entity::Entity(string file,int w,int h,int x,int y){
  string fullfilename = "graphics/"+file;
  EntitySprite = Surface::OnLoad(fullfilename.c_str());
  width = w;
  height = h;
  X = x;
  Y = y;
  entityStateX = entityStateY = 0;
}

bool Entity::OnRender(SDL_Surface* Display){
  if(Surface::OnDraw(Display,EntitySprite,X+Camera::CameraControl.GetX()-width/2,Y+Camera::CameraControl.GetY()-height/2,entityStateX*width,entityStateY*height,width,height) == false) return false;

  return true;
}

int Entity::getX(){
  return X;
}

int Entity::getY(){
  return Y;
}

int Entity::getW(){
  return width;
}

int Entity::getH(){
  return height;
}

void Entity::changePos(int a,int b){
  X += a;
  Y += b;
}

void Entity::OnCleanup(){
  SDL_FreeSurface(EntitySprite);
}
