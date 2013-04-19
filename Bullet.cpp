#include "Bullet.h"

Bullet::Bullet() : Entity("bullets.png",12,12,WWIDTH/2-Camera::CameraControl.GetX(),WHEIGHT/2-Camera::CameraControl.GetY(),3){

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
  X += speed * movingH;
  Y += speed * movingV;

  if(speed==0){
    height = 18;
    width = 18;
    entityStateY = 3;
    destroy = true;
  }
  else if(BulletCheckCollisions()){
    onHit();
  }
  else entityStateY = !entityStateY;
}

bool Bullet::BulletCheckCollisions(){
  return MapEditor::CheckTileCollision(X,Y,width,height);
}

void Bullet::onHit(){
    speed = 0;
    height = 16;
    width = 16;
    entityStateY = 2;
}
