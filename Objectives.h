// Matt Mahan, Benjamin Law, Matt Rundle, Paul Kennedy
// CSE20212 Final Project

// Note: I started this as an objective system, but this feature can be used to display any message to the player


#ifndef OBJECTIVES_H
#define OBJECTIVES_H

#include "MapEditor.h"

class Objectives{

 public:
  Objectives();
  string CurrentObj;
  int Update(int);
  
 private:
  vector<string> list;
  
};

#endif
