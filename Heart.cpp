#include "Heart.h"

Heart::Heart(int enemyX, int enemyY) : Entity("hearts.png",32,32,enemyX,enemyY,0){}

void Heart::OnLoop(){}

void Heart::onHit(){}

void Heart::OnSave(ofstream & savefile){
  savefile<<spritefilename<<endl;
  savefile<<width<<endl;
  savefile<<height<<endl;
  savefile<<X<<endl<<Y<<endl;
  savefile<<speed<<endl;
  savefile<<type<<endl;
  savefile<<entityStateX<<endl<<entityStateY<<endl;
}
