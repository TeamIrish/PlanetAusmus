#include <iomanip>
#include <sstream>
#include "MapEditor.h"
#include "Camera.h"
 
Camera Camera::CameraControl;
 
Camera::Camera() {
    X = -(WWIDTH/2);
	Y = -(WHEIGHT/2);
 
    TargetX = TargetY = NULL;
 
    TargetMode = TARGET_MODE_NORMAL;
}
 
void Camera::OnMove(int MoveX, int MoveY) {
    X += MoveX;
    Y += MoveY;
}
 
int Camera::GetX() {
    if(TargetX != NULL) {
        if(TargetMode == TARGET_MODE_CENTER) {
            return *TargetX - (WWIDTH / 2);
        }
 
        return *TargetX;
    }
 
    return X;
}
 
int Camera::GetY() {
    if(TargetY != NULL) {
        if(TargetMode == TARGET_MODE_CENTER) {
            return *TargetY - (WHEIGHT / 2);
        }
 
        return *TargetY;
    }
 
    return Y;
}
 
void Camera::SetPos(int X, int Y) {
    this->X = X;
    this->Y = Y;
}
 
void Camera::SetTarget(int* X, int* Y) {
    TargetX = X;
    TargetY = Y;
}

// Check to make sure that the camera didn't move out of bounds - if so, fix
void Camera::CheckBounds(){
	if(Camera::CameraControl.GetX() > 0){
	  //Camera::CameraControl.SetPos(0,Camera::CameraControl.GetY());
	  if(--currentMapX<0) currentMapX=999;
	  ChangeMapView();
	  CameraControl.SetPos(MAP_WIDTH*TILE_SIZE*-1,CameraControl.GetY());
	}
	if(Camera::CameraControl.GetX() < (MAP_WIDTH*TILE_SIZE*-1)){
	  //Camera::CameraControl.SetPos((MAP_WIDTH*TILE_SIZE*-1)+WWIDTH,Camera::CameraControl.GetY());
	  if(++currentMapX>999) currentMapX=0;
	  ChangeMapView();
	  CameraControl.SetPos(0,CameraControl.GetY());
	}
	if(Camera::CameraControl.GetY() > 0){
	  //Camera::CameraControl.SetPos(Camera::CameraControl.GetX(), 0);
	  if(--currentMapY<0) currentMapY=999;
	  ChangeMapView();
	  CameraControl.SetPos(CameraControl.GetX(),MAP_HEIGHT*TILE_SIZE*-1);
	}
	if(Camera::CameraControl.GetY() < (MAP_HEIGHT*TILE_SIZE*-1)){
	  //Camera::CameraControl.SetPos(Camera::CameraControl.GetX(),(MAP_HEIGHT*TILE_SIZE*-1)+WHEIGHT);
	  if(++currentMapY>999) currentMapY=0;
	  ChangeMapView();
	  CameraControl.SetPos(CameraControl.GetX(),0);
	}
}


bool Camera::ChangeMapView(){
  cout<<"Changing map view..."<<endl;
  ostringstream ss;
  string Xstr,Ystr;
  int mapCoord;

  for(int i=0;i<4;i++){
    mapCoord = (currentMapX+(i%2))>999 ? 0 : currentMapX+(i%2);  // allows wrap from 999 to 0 and vice versa
    ss<<setw(3)<<setfill('0')<<mapCoord;
    Xstr = ss.str(); // save in string
    ss.str("");  // clear stream

    mapCoord = (currentMapY+(i/2))>999 ? 0 : currentMapY+(i/2);  // allows wrap from 999 to 0 and vice versa
    ss<<setw(3)<<setfill('0')<<mapCoord;
    Ystr = ss.str();
    ss.str("");  // clear stream
    MapEditor::filenameLoad[i] = MapEditor::filenameSave[i] = "maps/map"+Xstr+Ystr;
    ifstream file(MapEditor::filenameLoad[i].c_str());
    if(!file){  // file does not exist; make it
      cout<<"Generating file "<<MapEditor::filenameLoad[i]<<endl;
      MapEditor::RandomMapGenerate(MapEditor::filenameLoad[i]);
    }
    file.close();
  }

  // tell program to load new view into memory
  MapEditor::runLoadMaps = true;

  cout<<"View set to: "<<MapEditor::filenameLoad[0]<<" "<<MapEditor::filenameLoad[1]<<"\n             "<<MapEditor::filenameLoad[2]<<" "<<MapEditor::filenameLoad[3]<<endl;

}
