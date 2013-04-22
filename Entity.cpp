// Benjamin Laws, Matt Rundle, Matt Mahan, Paul Kennedy
// CSE 20212 Final Project

//#include "Entity.h"
#include "MapEditor.h"

Entity::Entity(string file, int w, int h, int x, int y, int s){
  string fullfilename = "graphics/" + file;
  EntitySprite = Surface::OnLoad( fullfilename.c_str() );
  Surface::Transparent(EntitySprite, 255, 0, 255);

  width = w;
  height = h;
  X = x;
  Y = y;

  if(MapEditor::moveSize==6) speed = 4 * s; // speed up entities in ssh mode
  else speed = s;

  entityStateX = entityStateY = 0;
  destroy = false;
}

bool Entity::OnRender(SDL_Surface* Display){
  if( Surface::OnDraw( Display, EntitySprite, X + Camera::CameraControl.GetX() - width/2, Y + Camera::CameraControl.GetY() - height/2, entityStateX * width, entityStateY * height, width, height) == false ) {
		return false;
	}

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

void Entity::setType(int entityType){
	type = entityType;
}

int Entity::getType(){
	return type;
}

bool Entity::isDestroyable(){
  return destroy;
}
