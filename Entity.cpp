// Benjamin Laws, Matt Rundle, Matt Mahan, Paul Kennedy
// CSE 20212 Final Project

#include "MapEditor.h"

// constructor
Entity::Entity(string file, int w, int h, int x, int y, int s)
{
	// set up the entity's surface
  spritefilename = file; // necessary to store w/o "graphics/" for saving/loading
  string fullfilename = "graphics/"+file; // append graphics/ to give the directory
  EntitySprite = Surface::OnLoad( fullfilename.c_str() ); // create the surface

	// debug message
  if(!EntitySprite) cout << "EntitySprite (" << fullfilename.c_str() << ") load failure." <<endl;

	// color key the surface
  Surface::Transparent(EntitySprite, 255, 0, 255); 

	// basic entity info
  width = w;
  height = h;
  X = x;
  Y = y;
  speed = s;

  entityStateX = entityStateY = 0;
  destroy = false;
}

// blit the entity at the appropriate place on (or off) the screen
bool Entity::OnRender(SDL_Surface* Display)
{
  if( Surface::OnDraw( Display, EntitySprite, X + Camera::CameraControl.GetX() - width/2, Y + Camera::CameraControl.GetY() - height/2, entityStateX * width, entityStateY * height, width, height) == false ) {
		return false; // return false to indicate failure
	}

  return true;
}

// accessors
int Entity::getX()
{
  return X;
}

int Entity::getY()
{
  return Y;
}

int Entity::getW()
{
  return width;
}

int Entity::getH()
{
  return height;
}

int Entity::getType()
{
	return type;
}

bool Entity::isDestroyable()
{
  return destroy;
}

// mutators
void Entity::changePos(int a,int b)
{
  X += a;
  Y += b;
}

void Entity::changeState(int a,int b)
{
  entityStateX = a;
  entityStateY = b;
}

void Entity::setType(int entityType)
{
	type = entityType;
}

void Entity::makeDestroyable()
{
  destroy = true;
}

// free the entity's surface and clean up any other dynamic memory
void Entity::OnCleanup()
{
  SDL_FreeSurface(EntitySprite);
}
