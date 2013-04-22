#include "MapEditor.h"
using namespace std;

// Save game
void MapEditor::OnSave() {

  ofstream savefile("maps/save.txt");
  if(!savefile){
    cout<<"Unable to save..."<<endl;
    return;
  }

  savefile<<playerHealth<<endl;
  savefile<<Camera::CameraControl.currentMapX<<endl;
  savefile<<Camera::CameraControl.currentMapY<<endl;
  savefile<<Camera::CameraControl.GetX()<<endl;
  savefile<<Camera::CameraControl.GetY()<<endl;
}
