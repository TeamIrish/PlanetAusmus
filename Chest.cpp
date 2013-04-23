#include "Chest.h"

Chest::Chest(int X,int Y) : Entity("chest.png",16,16,X,Y,0){
}

void Chest::OnLoop(){}
void Chest::onHit(){}

void Chest::OnSave(ofstream & savefile){
  savefile<<spritefilename<<endl;
  savefile<<width<<endl;
  savefile<<height<<endl;
  savefile<<X<<endl<<Y<<endl;
  savefile<<speed<<endl;
  savefile<<type<<endl;
}
