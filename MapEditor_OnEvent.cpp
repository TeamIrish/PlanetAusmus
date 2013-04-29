/*
Team: Matt Rundle, Benjamin Laws, Matt Mahan, Paul Kennedy
File: MapEditor_OnRender.cpp

This is the implementation file for the OnEvent() function of the MapEditor class, which inherits from
the Event class. This takes in user input and handles it by applying changes to game data.
*/

#include "MapEditor.h"
 
//==============================================================================
void MapEditor::OnEvent(SDL_Event* Event) {
	Event::OnEvent(Event);
}

//==============================================================================
// On left mouse button click
void MapEditor::OnLButtonDown(int MouseXPos, int MouseYPos)
{
	// if the main menu is up
	if(dispTitle && !(dispPlainTitleMenu)){

		// clicked "Start" button
		if(((MouseXPos > 361) && (MouseXPos < 442)) && ((MouseYPos > 307) && (MouseYPos < 330))){
			displayStartDepressedMenu = true;
			displayInitialMenu = false;
		}

		// clicked the "about" button
		if(((MouseXPos > 361) && (MouseXPos < 442)) && ((MouseYPos > 344) && (MouseYPos < 369))){
			displayAboutDepressedMenu = true;
			displayInitialMenu = false;
		}
	}

	// if the about screen is up
	else if(dispPlainTitleMenu){
		if(((MouseXPos > 601) && (MouseXPos < 630)) && ((MouseYPos > 159) && (MouseYPos < 181))){
			dispPlainTitleMenu = false;
			displayBackDepressedTitleMenu = true;
		}
	}
}

//=====================================================================
void MapEditor::OnLButtonUp(int MouseXPos, int MouseYPos)
{
	// on left mouse button up
	if(dispTitle) { // if we are on the title screen

		// if the start button is depressed
		if(displayStartDepressedMenu == true) {
			displayStartDepressedMenu = false;
			dispTitle = false; // exit the title screen and begin game
		}

		// if the about button is depressed
		if(displayAboutDepressedMenu == true) {
			displayAboutDepressedMenu = false;
			dispPlainTitleMenu = true; // display the about screen
		}

		// if the back button on the about screen is depressed
		if(displayBackDepressedTitleMenu == true) {
			displayBackDepressedTitleMenu = false;
			displayInitialMenu = true;
		}
	}
}
//==============================================================================
void MapEditor::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	switch(sym) {
	
		// left arrow key for face left
		case SDLK_LEFT:
		  Camera::CameraControl.numDirKeys++;
		  Camera::CameraControl.facingDir = 2;
		  break;

		// right arrow key for face right
		case SDLK_RIGHT:
		  Camera::CameraControl.numDirKeys++;
		  Camera::CameraControl.facingDir = 3;
		  break;

		// up arrow key for face up
		case SDLK_UP:
		  Camera::CameraControl.numDirKeys++;
		  Camera::CameraControl.facingDir = 1;
		  break;

		// down arrow key for face down
		case SDLK_DOWN:
		  Camera::CameraControl.numDirKeys++;
		  Camera::CameraControl.facingDir = 0;
		  break;

		// a key for move left
		case SDLK_a:
		  if(Running){
		    Camera::CameraControl.MovingLeft = true;
		    Camera::CameraControl.MovingRight = false;
		  }
		  break;

		// d key for move right
		case SDLK_d:
		  if(Running){
		    Camera::CameraControl.MovingRight = true;	
		    Camera::CameraControl.MovingLeft = false;	
		  }
		  break;

		// w key for move up
		case SDLK_w:
		  if(Running){
		    Camera::CameraControl.MovingUp = true;
		    Camera::CameraControl.MovingDown = false;
		  }
		  break;

		// s key for move down
		case SDLK_s:
		  if(Running){
		    Camera::CameraControl.MovingDown = true;
		    Camera::CameraControl.MovingUp = false;
		  }
		  break;

		// menu (toggles on and off)
		case SDLK_m:
		  dispMenu = !(dispMenu);
		  break;

		// play (when on title screen)
		case SDLK_p:
		  dispTitle = false;
		  break;
		// newgame (when on title screen)
		case SDLK_n:
		  if(dispTitle){
		    system("rm maps/*");
		  }
		  break;
		  
		// r key for replay (when on GameOver or YouWin screens)
		case SDLK_r:
		  if(!Running){
		    Replay = true;
		    OnExit();
		  }
		  break;

		// ESC key for quitting the game 
		case SDLK_ESCAPE:
		  if(dispTitle){
		    dispTitle = false;
		    Running = false;
		    Replay = false;
		  }
		  else{
		    if(Running)
		      OnStop();
		    else {
		      Replay = false;
		      OnExit();
		    }
		  }
		  break;

		// Objective (toggle on and off)
		case SDLK_o:
			dispObjective = !(dispObjective);
			break;

		// shoot with space bar
		case SDLK_SPACE:
			if(numPlayerBullets > 0) { // only if the player has any bullets left
				Mix_PlayChannel(-1, sfx2, 0); // laser noise, yo
				AddBullet();
				numPlayerBullets--; // decrement number of player's bullets
			}
		  break;

		default:
			break;
	}
}

//------------------------------------------------------------------------------
void MapEditor::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch(sym) {
         	case SDLK_LEFT:
		  if((--Camera::CameraControl.numDirKeys) == 0)
		    Camera::CameraControl.facingDir = -1;
		  break;

         	case SDLK_RIGHT:
		  if((--Camera::CameraControl.numDirKeys) == 0)
		    Camera::CameraControl.facingDir = -1;
		  break;

         	case SDLK_UP:
		  if((--Camera::CameraControl.numDirKeys) == 0)
		    Camera::CameraControl.facingDir = -1;
		  break;

         	case SDLK_DOWN:
		  if((--Camera::CameraControl.numDirKeys) == 0)
		    Camera::CameraControl.facingDir = -1;
		  break;

		case SDLK_a:
			Camera::CameraControl.MovingLeft = false;
			break;

		case SDLK_d:
			Camera::CameraControl.MovingRight = false;
			break;

		case SDLK_w:
			Camera::CameraControl.MovingUp = false;
			break;

		case SDLK_s:
			Camera::CameraControl.MovingDown = false;
			break;

		default:
		  break;
	}
}


//------------------------------------------------------------------------------
void MapEditor::OnStop(){
  Running = false;
}

void MapEditor::OnExit(){
  Quit = true;
}
