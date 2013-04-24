#include "Chest.h"

Chest::Chest(int X,int Y) : Entity("chest.png",16,16,X,Y,0){
  counter=0;
}

void Chest::OnLoop(){
  if(entityStateY!=0 && entityStateY!=8) counter++;
  if(counter>=20) entityStateY=8;
}

void Chest::onHit(){}

void Chest::OnSave(ofstream & savefile){
  savefile<<spritefilename<<endl;
  savefile<<width<<endl;
  savefile<<height<<endl;
  savefile<<X<<endl<<Y<<endl;
  savefile<<speed<<endl;
  savefile<<type<<endl;
  savefile<<entityStateX<<endl<<entityStateY<<endl;
}

void Chest::OpenChest(){
  if(entityStateY==0){ // closed
    int choose = rand()%11;
    if(choose<3) entityStateY=1; // heart
    else if(choose<6) entityStateY=2; // bullet
    else if(choose==6) entityStateY=3; // blue gem
    else if(choose==7) entityStateY=4; // green gem
    else if(choose==8) entityStateY=5; // yellow gem
    else if(choose==9) entityStateY=6; // red gem
    else if(choose==10) entityStateY=7; // purple gem
  }
}
