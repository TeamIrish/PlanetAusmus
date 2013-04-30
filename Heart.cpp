#include "Heart.h"

Heart::Heart(int enemyX, int enemyY)
	: Entity("hearts.png",32,32,enemyX,enemyY,0)
{
  counter = 0;
}

void Heart::OnLoop()
{
  counter++;
  // make disappear after 20 sec.
  if(counter>400) destroy=true;
}

void Heart::onHit()
{
}

// save the hearts on the map to the save file
void Heart::OnSave(ofstream & savefile)
{
  savefile<<spritefilename<<endl;
  savefile<<width<<endl;
  savefile<<height<<endl;
  savefile<<X<<endl<<Y<<endl;
  savefile<<speed<<endl;
  savefile<<type<<endl;
  savefile<<entityStateX<<endl<<entityStateY<<endl;
}
