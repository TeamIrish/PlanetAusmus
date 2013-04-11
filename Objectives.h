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
  string CurrentObj;
  
 private:
  vector<string> list;
  
};

#endif
