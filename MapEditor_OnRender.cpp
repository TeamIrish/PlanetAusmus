#include "MapEditor.h"
 
void MapEditor::OnRender() {

  // render maps
  for(int i=0;i<4;i++){
    gameMap[i].OnRender(Surf_Display, Camera::CameraControl.GetX()+MAP_WIDTH*TILE_SIZE*(i%2), Camera::CameraControl.GetY()+MAP_HEIGHT*TILE_SIZE*(i/2));
  }

  // render player character
  Surface::OnDraw(Surf_Display,Player_Character,(WWIDTH-CHARACTER_W)/2,(WHEIGHT-CHARACTER_H)/2,Camera::CameraControl.playerStateX*CHARACTER_W,Camera::CameraControl.playerStateY*CHARACTER_H,CHARACTER_W,CHARACTER_H);

  // render enemies
  for(int i=0;i<EnemyList.size();i++){
    if((EnemyList[i]->OnRender(Surf_Display))==false) cout<<"Error displaying enemy "<<i<<endl;
  }

	if(dispMenu == true){
		Surface::OnDraw(Surf_Display,Menu,(WWIDTH-MENU_W)/2,(WHEIGHT-MENU_H)/2);
	}

  // Refresh the buffer and display Surf_Display to screen
  SDL_Flip(Surf_Display);
}
