// Benjamin Laws, Matt Rundle, Matt Mahan, Paul Kennedy
// CSE 20212-01 Final Project
// Random Map Generator

#include "MapEditor.h"
#include <iostream>
#include <valarray>
using namespace std;

void MapEditor::RandomMapGenerate(string savename,int cornervalues[4]){
  int tilevalue[40][40] = {{0}};
  int corners[4] = {0,0,39,39};
  // reference arrays: tileX and tileY in class header
  // tile order: lava,rock,snow,mountains,snow,rock,dirt,grass,grass,tree,evergreen,grass,grass,sand,water,deepwater

  // initialize corner tile values
  if(cornervalues==NULL){  // random if unspecified
    for(int i=0;i<40;i+=39){
      for(int j=0;j<40;j+=39) tilevalue[i][j]=rand()%100;
    }
  }
  else{  // set if specified
    int a=0;
    for(int i=0;i<40;i+=39){
      for(int j=0;j<40;j+=39){
	if(cornervalues[a]==-1) tilevalue[i][j]=rand()%100;
	else tilevalue[i][j]=cornervalues[a];
	a++;
      }
    }
  }

  // generate map recursively
  RMG_Recursion(corners,tilevalue);

  // intermix two types of trees
  for(int i=0;i<40;i++){
    for(int j=0;j<40;j++){
      if(tilevalue[i][j]/6==9 && rand()%2) tilevalue[i][j]+=6;
      else if(tilevalue[i][j]/6==10 && rand()%2) tilevalue[i][j]-=6;
    }
  }

  // write to file
  ofstream fptr;
  fptr.open(savename.c_str());
  if(fptr.is_open() == false) return;

  for(int i=0;i<40;i++){
    for(int j=0;j<40;j++) fptr<<tileX[tilevalue[i][j]/6]<<":"<<tileY[tilevalue[i][j]/6]<<" ";
    fptr<<endl;
  }
  fptr.close();
}

void MapEditor::RMG_Recursion(int pos[4],int tilevalue[40][40]){
  if(abs(pos[0]-pos[2])<2 && abs(pos[1]-pos[3])<2) return;  // base case

  // edges take average of nearest two corners
  tilevalue[(pos[0]+pos[2])/2][pos[1]] = (tilevalue[pos[0]][pos[1]]+tilevalue[pos[0]][pos[3]])/2; // left edge
  tilevalue[(pos[0]+pos[2])/2][pos[3]] = (tilevalue[pos[2]][pos[1]]+tilevalue[pos[2]][pos[3]])/2; // right edge
  tilevalue[pos[0]][(pos[1]+pos[3])/2] = (tilevalue[pos[0]][pos[1]]+tilevalue[pos[2]][pos[1]])/2; // top edge
  tilevalue[pos[2]][(pos[1]+pos[3])/2] = (tilevalue[pos[0]][pos[3]]+tilevalue[pos[2]][pos[3]])/2; // bottom edge

 // center takes average of four corners plus/minus random fluctuation based on distance
  tilevalue[(pos[0]+pos[2])/2][(pos[1]+pos[3])/2] = (tilevalue[pos[0]][pos[1]]+tilevalue[pos[0]][pos[3]]+tilevalue[pos[2]][pos[1]]+tilevalue[pos[2]][pos[3]])/4 + pow(-1,rand()%2)*(rand()%(pos[2]-pos[0]));
  if(tilevalue[(pos[0]+pos[2])/2][(pos[1]+pos[3])/2] < 0) tilevalue[(pos[0]+pos[2])/2][(pos[1]+pos[3])/2]=0;
  if(tilevalue[(pos[0]+pos[2])/2][(pos[1]+pos[3])/2] > 99) tilevalue[(pos[0]+pos[2])/2][(pos[1]+pos[3])/2]=99;

  // recursion
  int newpos[4] = {pos[0],pos[1],(pos[0]+pos[2])/2,(pos[1]+pos[3])/2};
  RMG_Recursion(newpos,tilevalue); // top-left quadrant
  newpos[1] = (pos[1]+pos[3])/2;
  newpos[3] = pos[3];
  RMG_Recursion(newpos,tilevalue); // top-right quadrant
  newpos[0] = (pos[0]+pos[2])/2;
  newpos[2] = pos[2];
  RMG_Recursion(newpos,tilevalue); // bottom-right quadrant
  newpos[1] = pos[1];
  newpos[3] = (pos[1]+pos[3])/2;
  RMG_Recursion(newpos,tilevalue); // bottom-left quadrant
}
