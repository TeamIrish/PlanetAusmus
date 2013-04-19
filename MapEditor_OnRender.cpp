/*
Team: Matt Rundle, Benjamin Laws, Matt Mahan, Paul Kennedy
File: MapEditor_OnRender.cpp

This is the implementation file for the OnRender() function of the MapEditor class. It handles the
rendering of graphics to the screen each iteration through the game loop.
*/

#include "MapEditor.h"
 
void MapEditor::OnRender() {

  // render maps
  for(int i=0;i<4;i++){
    gameMap[i].OnRender( Surf_Display, Camera::CameraControl.GetX() + MAP_WIDTH * TILE_SIZE * (i%2), Camera::CameraControl.GetY() + MAP_HEIGHT * TILE_SIZE * (i/2) );
  }

  // render entities (enemies, bullets)
  for(int i=0;i<EntityList.size();i++){
    if((EntityList[i]->OnRender(Surf_Display))==false && debug) cout<<"Error displaying entity "<<i<<endl;
  }

  // render player character (or grave if game over)
	if(playerHealth>0){
  	Surface::OnDraw(Surf_Display,Player_Character,(WWIDTH-CHARACTER_W)/2,(WHEIGHT-CHARACTER_H)/2,Camera::CameraControl.playerStateX*CHARACTER_W,Camera::CameraControl.playerStateY*CHARACTER_H,CHARACTER_W,CHARACTER_H);
	}else{
		Surface::OnDraw(Surf_Display,Grave,(WWIDTH-CHARACTER_W)/2,(WHEIGHT-CHARACTER_H)/2);
	}
  
  // render objective
  if(dispObjective==true){
  	stringstream Current;
  	Current << ObjPtr->CurrentObj; // making the c string
  	Objective=TTF_RenderText_Solid(XObjectiveFont,(Current.str()).c_str(), XObjectiveTextColor);
  	if(Objective==NULL) cout << "Error displaying text." << endl;
  	Surface::OnDraw(Surf_Display,ObjBackground,0,0);
  	Surface::OnDraw(Surf_Display,Objective,1,1);
  }


	// Render the heart bar
	Surface::OnDraw(Surf_Display,HeartBar,WWIDTH-HEARTBAR_W,0,0,HEARTBAR_H*(10-playerHealth),HEARTBAR_W,HEARTBAR_H);

	// Render the menu (conditionally)
	if(dispMenu == true){
		Surface::OnDraw(Surf_Display,Menu,(WWIDTH-MENU_W)/2,(WHEIGHT-MENU_H)/2);
	}

  // Refresh the buffer and display Surf_Display to screen
  SDL_Flip(Surf_Display);
}
