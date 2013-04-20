#include "Chest.h"

Chest::Chest(int X,int Y) : Entity("chest.png",16,16,X,Y,0){
  opened = false;
}

void Chest::OnLoop(){}
void Chest::onHit(){}
