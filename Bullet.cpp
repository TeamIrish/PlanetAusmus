#include "Bullet.h"

// constructor
Bullet::Bullet() : Entity("bullets.png", 12, 12, WWIDTH/2 - Camera::CameraControl.GetX(), WHEIGHT/2 - Camera::CameraControl.GetY(), 9)
{
	// change the direction of the bullet's initial velocity based on the direction the player is currently facing
  switch(Camera::CameraControl.playerStateX){
   case 0:
     movingV = 1;
     movingH = 0;
     break;
   case 1:
     movingV = -1;
     movingH = 0;
     break;
   case 2:
     movingV = 0;
     movingH = -1;
     break;
   case 3:
     movingV = 0;
     movingH = 1;
     break;
  }
}

// carry out game logic for the bullet
void Bullet::OnLoop()
{
	// modify X and Y coordinates by the bullet's horizontal and vertical velocity
  X += speed * movingH;
  Y += speed * movingV;

	// if the bullet has struck something (speed set to 0) change its animation frame and set desetroy to true
  if(speed == 0) {
    height = 18;
    width = 18;
    entityStateY = 3;
    destroy = true;
  }
	// if the bullet collides with something, call its onHit() method
  else if(BulletCheckCollisions()==TILE_TYPE_NON_TRAVERSABLE){
    onHit();
  }
	// otherwise, advance its animation frame
  else entityStateY = !entityStateY;
}

// return the bullet's collision status
int Bullet::BulletCheckCollisions()
{
  return MapEditor::CheckTileCollision(X,Y,width,height);
}

// simulate a "hit" by changing speed to 0, switching to an "exploding" animation frame, and and playing a sound
void Bullet::onHit()
{
  if(speed!=0) { // ensures that both frames of bullet hit animation are played
    speed = 0;
    height = 16;
    width = 16;
    entityStateY = 2;
    Mix_PlayChannel(-1, MapEditor::sfx1, 0); // Play a little noise for bullet destruction
  }
}

void Bullet::OnSave(ofstream &){}
