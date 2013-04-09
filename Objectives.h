// Matt Mahan, Benjamin Law, Matt Rundle, Paul Kennedy
// CSE20212 Final Project

// Note: I started this as an objective system, but this feature can be used to display any message to the player


#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "Define.h"
#include "MapEditor.h"
#include <string>
#include <vector>

using namespace std;

class Objectives{
 public:
  Objectives();
  bool OnRender(SDL_Surface*);
  void OnCleanup();
  SDL_Surface *Objective;
  
 private:
  vector<string> list;
  TTF_Font *ObjectiveFont;
  SDL_Color ObjectiveTextColor;
  int ObjectiveStateX;
  int ObjectiveStateY;
  
};

#endif
