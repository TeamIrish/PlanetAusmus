// Matt Mahan, Benjamin Law, Matt Rundle, Paul Kennedy
// CSE20212 Final Project

#include"Objectives.h"


// constructor
Objectives::Objectives(){

	ObjectiveFont = NULL;
	ObjectiveFont = TTF_OpenFont("ice-sans-regular.ttf",14); // assign the font and size
	SDL_Color ObjectiveTextColor={255,255,255}; // assign color
	Objective=TTF_RenderText_Solid(ObjectiveFont,"test", ObjectiveTextColor);	
}

// cleanup
void Objectives::OnCleanup(){
  SDL_FreeSurface(Objective);
}
