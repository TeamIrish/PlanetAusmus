#include "Bullet.h"

Bullet::Bullet(){
  EntitySprite = Surface::OnLoad("graphics/bullets.png");
  width = 12;
  height = 12;
  X = WWIDTH/2 - Camera::CameraControl.GetX();
  Y = WHEIGHT/2 - Camera::CameraControl.GetY();
  entityStateX = entityStateY = 0;

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

void Bullet::OnLoop(){
  
}
