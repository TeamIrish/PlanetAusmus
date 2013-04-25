#include "MapEditor.h"
using namespace std;

// Save game
void MapEditor::OnSave() {

  ofstream savefile("maps/save.txt");
  if(!savefile){
    cout<<"Unable to save..."<<endl;
    return;
  }

  // player state
  savefile<<playerHealth<<endl;
  savefile<<Camera::CameraControl.playerStateX<<endl;
  savefile<<Camera::CameraControl.playerStateY<<endl;
  savefile<<Camera::CameraControl.currentMapX<<endl;
  savefile<<Camera::CameraControl.currentMapY<<endl;
  savefile<<Camera::CameraControl.GetX()<<endl;
  savefile<<Camera::CameraControl.GetY()<<endl;
  savefile<<numPlayerBullets<<endl;

  // gems collected
  for(int i=0;i<5;i++) savefile<<gotGem[i]<<endl;

  // entities
  for(unsigned int i=0;i<EntityList.size();i++) EntityList[i]->OnSave(savefile);
}
