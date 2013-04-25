#include <iomanip>
#include <sstream>
#include <valarray>
#include <cstring>
#include "MapEditor.h"
#include "Camera.h"

Camera Camera::CameraControl;
 
Camera::Camera() {
  X = -(MAP_WIDTH*TILE_SIZE-WWIDTH/2);
  Y = -(MAP_HEIGHT*TILE_SIZE-WHEIGHT/2);
 
    TargetX = TargetY = NULL;
 
    TargetMode = TARGET_MODE_NORMAL;

    playerStateX = playerStateY = 0;
    facingDir = -1;
    numDirKeys = 0;

    animTimerMax=2;
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

// Check to make sure that the camera didn't move out of bounds - if so, change view
void Camera::CheckBounds(){
	if(Camera::CameraControl.GetX() > 0){
	  --currentMapX;
	  CameraControl.SetPos(MAP_WIDTH*TILE_SIZE*-1,CameraControl.GetY());
	  for(unsigned int i = 0; i < MapEditor::EntityList.size(); i++)
	    MapEditor::EntityList[i]->changePos(MAP_WIDTH*TILE_SIZE,0);
	  ChangeMapView();
	}
	if(Camera::CameraControl.GetX() < (-1*MAP_WIDTH*TILE_SIZE)){
	  ++currentMapX;
	  CameraControl.SetPos(0,CameraControl.GetY());
	  for(unsigned int i = 0;i < MapEditor::EntityList.size(); i++)
	    MapEditor::EntityList[i]->changePos(-MAP_WIDTH*TILE_SIZE,0);
	  ChangeMapView();
	}
	if(Camera::CameraControl.GetY() > 0){
	  --currentMapY;
	  CameraControl.SetPos(CameraControl.GetX(),MAP_HEIGHT*TILE_SIZE*-1);
	  for(unsigned int i = 0; i < MapEditor::EntityList.size(); i++)
	    MapEditor::EntityList[i]->changePos(0,MAP_WIDTH*TILE_SIZE);
	  ChangeMapView();
	}
	if(Camera::CameraControl.GetY() < (-1*MAP_HEIGHT*TILE_SIZE)){
	  ++currentMapY;
	  CameraControl.SetPos(CameraControl.GetX(),0);
	  for(unsigned int i = 0;i<MapEditor::EntityList.size(); i++)
	    MapEditor::EntityList[i]->changePos(0,-MAP_WIDTH*TILE_SIZE);
	  ChangeMapView();
	}

	// despawn enemies that are off the loaded maps
	for(unsigned int i = 0;i<MapEditor::EntityList.size(); i++){
	  if(MapEditor::EntityList[i]->getType()==ENTITY_TYPE_ENEMY){
	    int entX = MapEditor::EntityList[i]->getX();
	    int entY = MapEditor::EntityList[i]->getY();
	    if((entX<0 || entX>2*MAP_WIDTH*TILE_SIZE) && (entY<0 || entY>2*MAP_HEIGHT*TILE_SIZE)) MapEditor::EntityList[i]->makeDestroyable();
	  }
	}
}


bool Camera::ChangeMapView(){
  if(MapEditor::debug) cout<<"Changing map view..."<<endl;
  ostringstream ss;
  string Xstr,Ystr;
  int mapXCoord,mapYCoord;
  int corners[4];

  for(int i=0;i<4;i++){
    mapXCoord = currentMapX+(i%2);
    ss<<setw(3)<<setfill('0')<<mapXCoord;
    Xstr = ss.str(); // save in string
    ss.str("");  // clear stream

    mapYCoord = currentMapY+(i/2);
    ss<<setw(3)<<setfill('0')<<mapYCoord;
    Ystr = ss.str();
    ss.str("");  // clear stream
    MapEditor::filenameLoad[i] = MapEditor::filenameSave[i] = "maps/map"+Xstr+"_"+Ystr;

    ifstream file(MapEditor::filenameLoad[i].c_str());
    if(!file){  // file does not exist; make it
      if(MapEditor::debug) cout<<"Generating file "<<MapEditor::filenameLoad[i]<<endl;
      GetCornerValues(mapXCoord,mapYCoord,corners);
      MapEditor::RandomMapGenerate(MapEditor::filenameLoad[i],corners);
      MapEditor::runAddChests[i] = true;
    }
    file.close();
  }

  // tell program to load new view into memory
  MapEditor::runLoadMaps = true;

  if(MapEditor::debug) cout<<"View set to: "<<MapEditor::filenameLoad[0]<<" "<<MapEditor::filenameLoad[1]<<"\n             "<<MapEditor::filenameLoad[2]<<" "<<MapEditor::filenameLoad[3]<<endl;

  return true;
}

void Camera::GetCornerValues(int XCoord,int YCoord,int corners[]){
  ostringstream ss;
  string Xstr,Ystr,testmap;
  int tmp,value;
  char line[MAP_WIDTH*4];

  for(int i=0;i<4;i++){
    for(int j=0;j<3;j++){
      // get coords of one adjacent map
      tmp = XCoord-pow(-1,i)*((j+1)%2); // -1,0,-1,+1,0,+1,-1,0,-1,+1,0,+1
      ss<<setw(3)<<setfill('0')<<tmp;
      Xstr = ss.str(); // save in string
      ss.str("");  // clear stream

      tmp = YCoord-pow(-1,i/2)*((j+1)/2); // 0,-1,-1,0,-1,-1,0,+1,+1,0,+1,+1
      ss<<setw(3)<<setfill('0')<<tmp;
      Ystr = ss.str();
      ss.str("");  // clear stream

      // if map exists, get adjacent corner
      testmap = "maps/map"+Xstr+"_"+Ystr;
      ifstream file(testmap.c_str());
      if(file){
	switch(i+j){
	// get bottom-right: ij=02, ij=11, ij=20
	case 2:
	  for(int k=0;k<MAP_HEIGHT;k++) file.getline(line,sizeof(line)); // get to last line
	  value = atoi(strtok(line," "));
	  for(int k=0;k<MAP_WIDTH-1;k++) value = atoi(strtok(NULL," "));
	  break;

	// get top-right: ij=00, ij=22, ij=31
	case 0:
	case 4:
	  file.getline(line,sizeof(line));
	  value = atoi(strtok(line," "));
	  for(int k=0;k<MAP_WIDTH-1;k++) value = atoi(strtok(NULL," "));
	  break;

	case 1:
	case 3:
	case 5:
	  switch(i){
	  case 0:
	    // get bottom-left
	    for(int k=0;k<MAP_HEIGHT;k++) file.getline(line,sizeof(line)); // get to last line
	    value = atoi(strtok(line," "));
	    break;
	  case 1:
	    if(j==0){ // get top-left
	      file.getline(line,sizeof(line));
	      value = atoi(strtok(line," "));
	    }
	    else{  // get bottom-left
	      for(int k=0;k<MAP_HEIGHT;k++) file.getline(line,sizeof(line)); // get to last line
	      value = atoi(strtok(line," "));
	    }
	    break;
	  case 2:
	    // get top-left
	    file.getline(line,sizeof(line));
	    value = atoi(strtok(line," "));
	    break;
	  case 3:
	    if(j==2){ // get top-left
	      file.getline(line,sizeof(line));
	      value = atoi(strtok(line," "));
	    }
	    else{ // get bottom-left
	      for(int k=0;k<MAP_HEIGHT;k++) file.getline(line,sizeof(line)); // get to last line
	      value = atoi(strtok(line," "));
	    }
	  }
	  break;
	}// end outer switch
	corners[i] = value;
	if(MapEditor::debug) if(value!=-1) cout<<"  corner "<<i<<" found: "<<value<<endl;
	file.close();
	break; // move to next corner
      }
      else{  // file does not exist; set corner to -1, try next map
	corners[i]=-1;
	file.close();
      }
    }
  }
}

int Camera::TileToValue(int X,int Y){ 
  for(int i=0;i<NUM_TILES;i++){
    if(X==MapEditor::tileX[i] && Y==MapEditor::tileY[i]){
      return i*6;
    }
  }
  if(MapEditor::debug) cout<<"  unidentified tile type..."<<endl;
  return 50; // unidentifiable tile; set to middle value
}

void Camera::AnimateCharacter(){
  // set player direction
  if(MovingLeft) playerStateX = 2;
  else if(MovingRight) playerStateX = 3;
  else if(MovingDown) playerStateX = 0;
  else if(MovingUp) playerStateX = 1;
  else{  // not in motion
    playerStateY = 0;
    animationTimer = animTimerMax; // so that frame will change as soon as movement restarts
    if(facingDir!=-1) playerStateX = facingDir;
    return;
  }
  // arrow keys trump movement direction when setting what direction player is facing (so that player can shoot in any direction while moving)
  if(facingDir!=-1) playerStateX = facingDir;

  // set player animation frame
  if(animationTimer<animTimerMax) animationTimer++;
  else{
    animationTimer = 0;
    playerStateY = (playerStateY+1) % (PLAYER_MAX_ANIM_STATE+1);
  }
}

void Camera::setAnimTimer(int max){
  animTimerMax = max;
}
