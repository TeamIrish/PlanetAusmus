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
		if(((MouseXPos > 155) && (MouseXPos < 182)) && ((MouseYPos > 146) && (MouseYPos < 166))){
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
				a_keyIsDown = true;
		  }
		  break;

		// d key for move right
		case SDLK_d:
		  if(Running){
		    Camera::CameraControl.MovingRight = true;	
		    Camera::CameraControl.MovingLeft = false;	
				d_keyIsDown = true;
		  }
		  break;

		// w key for move up
		case SDLK_w:
		  if(Running){
		    Camera::CameraControl.MovingUp = true;
		    Camera::CameraControl.MovingDown = false;
				w_keyIsDown = true;
		  }
		  break;

		// s key for move down
		case SDLK_s:
		  if(Running){
		    Camera::CameraControl.MovingDown = true;
		    Camera::CameraControl.MovingUp = false;
				s_keyIsDown = true;
		  }
		  break;

		// menu (toggles on and off)
		case SDLK_m:
		  dispMenu = !(dispMenu);
		  break;

		// play (when on title screen)
		case SDLK_p:
		  if(dispTitle && !(dispPlainTitleMenu)){
		     displayStartDepressedMenu = true;
		     displayInitialMenu = false;
		  }
		  break;
		// newgame (when on title screen)
		case SDLK_n:
		  if(dispTitle && !(dispPlainTitleMenu)){
		    system("rm -f maps/*");
		  }
		  break;
		  
		// r key for replay (when on GameOver or YouWin screens)
		case SDLK_r:
		  if(!Running){
		    Replay = true;
		    OnExit();
		  }
		  break;

		// ESC key for quitting the game from the title screen or mid-game
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
// handle events where a key comes up
void MapEditor::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	switch(sym) {
		// left directional key (for looking left) comes up
		case SDLK_LEFT:
			if((--Camera::CameraControl.numDirKeys) == 0)
				Camera::CameraControl.facingDir = -1;
		  break;

		// right directional key (for looking right) comes up
		case SDLK_RIGHT:
			if((--Camera::CameraControl.numDirKeys) == 0)
				Camera::CameraControl.facingDir = -1;
			break;

		// up directional key (for looking up) comes up
		case SDLK_UP:
			if((--Camera::CameraControl.numDirKeys) == 0)
				Camera::CameraControl.facingDir = -1;
			break;

		// down directional key (for looking down) comes up
		case SDLK_DOWN:
			if((--Camera::CameraControl.numDirKeys) == 0)
				Camera::CameraControl.facingDir = -1;
			break;

		// a key (for moving left) comes up
		case SDLK_a:
			// quit moving left
			Camera::CameraControl.MovingLeft = false;
			a_keyIsDown = false;
			// switch to moving right if the d key is down
			if(d_keyIsDown) Camera::CameraControl.MovingRight = true;
			break;

		// d key (for moving right) comes up
		case SDLK_d:
			// quit moving right
			Camera::CameraControl.MovingRight = false;
			d_keyIsDown = false;
			// switch to moving left if the a key is down
			if(a_keyIsDown) Camera::CameraControl.MovingLeft = true;
			break;

		// w key (for moving up) comes up
		case SDLK_w:
			// quit moving up
			Camera::CameraControl.MovingUp = false;
			w_keyIsDown = false;
			// switch to moving down if the s key is down
			if(s_keyIsDown) Camera::CameraControl.MovingDown = true;
			break;

		// s key (for moving down) comes up
		case SDLK_s:
			// quit moving down
			Camera::CameraControl.MovingDown = false;
			s_keyIsDown = false;
			// switch to moving up if the w key is down
			if(w_keyIsDown) Camera::CameraControl.MovingUp = true;
			break;

		// from the title screen, quit the title screen and play on p key coming up
		case SDLK_p:
			displayStartDepressedMenu = false;
			dispTitle = false; // exit the title screen and begin game
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
