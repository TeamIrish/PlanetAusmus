/*
Team: Matt Rundle, Benjamin Laws, Matt Mahan, Paul Kennedy
File: MapEditor_OnRender.cpp

This is the implementation file for the OnRender() function of the MapEditor class. It handles the
rendering of graphics to the screen each iteration through the game loop.
*/

#include "MapEditor.h"
#include <string>
 
void MapEditor::OnRender() {

	/* render the maps */
  for(int i=0;i<4;i++){
    gameMap[i].OnRender( Surf_Display, Camera::CameraControl.GetX() + MAP_WIDTH * TILE_SIZE * (i%2), Camera::CameraControl.GetY() + MAP_HEIGHT * TILE_SIZE * (i/2) );
  }

  /* render entities (enemies, bullets) */
  for(int i = EntityList.size() - 1; i >= 0; --i){ // for each entity in the EntityList vector
    if( (EntityList[i]->OnRender(Surf_Display)) == false && debug) cout << "Error displaying entity " << i << endl;
  }

  /* render player character (or grave if game over) */
	// player is alive
	if(playerHealth > 0) {
	  Surface::OnDraw(Surf_Display,Player_Character,(WWIDTH-CHARACTER_W)/2,(WHEIGHT-CHARACTER_H)/2,Camera::CameraControl.playerStateX*CHARACTER_W,Camera::CameraControl.playerStateY*CHARACTER_H,CHARACTER_W,CHARACTER_H);
	  /* Render the heart bar */
	  Surface::OnDraw(Surf_Display,HeartBar,WWIDTH-HEARTBAR_W,0,0,HEARTBAR_H*(10-playerHealth),HEARTBAR_W,HEARTBAR_H);

	  /* render display of number of player's bullets */
	  // create a string stream to store the number
	  stringstream numBulletsStringStream;
	  numBulletsStringStream << numPlayerBullets;

	  // create the surface
	  Surface_NumPlayerBullets = TTF_RenderText_Solid(BulletDisplayFont, (numBulletsStringStream.str()).c_str(), XObjectiveTextColor);
	  if(Surface_NumPlayerBullets == NULL) cout << "Error displaying number of player's bullets." << endl;

	  // blit the bullet indicator
	  Surface::OnDraw(Surf_Display,BulletIndicator,WWIDTH - 45,WHEIGHT - 25,0,0,12,12);
	  // blit the bullet number display surface
	  Surface::OnDraw(Surf_Display, Surface_NumPlayerBullets, WWIDTH - 30, WHEIGHT - 30);
	}

	// player is dead
	else{
	  Surface::OnDraw(Surf_Display,Grave,(WWIDTH-CHARACTER_W)/2,(WHEIGHT-CHARACTER_H)/2);
	  Surface::OnDraw(Surf_Display,GameOverText,WWIDTH/2-225,WHEIGHT/2-130);
	}

	/* render objective (if desired) */
  if(dispObjective) {
    // string stream to store the objective text
    stringstream Current;
    Current << ObjPtr->CurrentObj;

    // create the surface
    Objective=TTF_RenderText_Solid(XObjectiveFont,(Current.str()).c_str(), XObjectiveTextColor);
    if(Objective==NULL) cout << "Error displaying text." << endl;

    // blit the background and objective text
    Surface::OnDraw(Surf_Display,ObjBackground,0,0);
    Surface::OnDraw(Surf_Display,Objective,1,1);
  }


	/* Render the menu (conditionally) */
	if(dispMenu == true) Surface::OnDraw(Surf_Display,Menu,(WWIDTH-MENU_W)/2,(WHEIGHT-MENU_H)/2);

	/* render the collected gems */
	for(int i=0;i<5;i++){
	  if(gotGem[i]) Surface::OnDraw(Surf_Display,Gems,WWIDTH-HEARTBAR_W+i*32,HEARTBAR_H,i*32,0,32,32);
	}

  // Refresh the buffer and display Surf_Display to screen
  SDL_Flip(Surf_Display);
}
