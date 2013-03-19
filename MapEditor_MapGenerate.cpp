// Benjamin Laws, Matt Rundle, Matt Mahan, Paul Kennedy
// CSE 20212-01 Final Project
// Random Map Generator

#include "MapEditor.h"
#include <iostream>
#include <iomanip>
#include <valarray>
using namespace std;

void MapEditor::RandomMapGenerate(string savename,int cornervalues[4]){
  int tilevalue[40][40] = {{0}};
  int corners[4] = {0,0,39,39};
  // reference arrays: tileX and tileY in class header
  // tile order: lava,rock,snow,mountains,snow,rock,dirt,grass,grass,tree,evergreen,grass,grass,sand,water,deepwater

  // set unspecified corner values
  for(int i=0;i<4;i++){
    if(cornervalues[i]==-1){  // check other corners if unspecified
      for(int j=0;j<4;j++){
	if(cornervalues[j]!=-1){
	  cornervalues[i]=cornervalues[j]+pow(-1,rand()%2)*(rand()%10);  // set unspecified corner to some specified corner +/- up to 9
	  if(cornervalues[i]>95) cornervalues[i]=95;
	  if(cornervalues[i]<-1) cornervalues[i]=0;
	}
      }
      if(cornervalues[i]==-1) cornervalues[i]=rand()%96; // if still unspecified (should only happen to first corner of first map), set to random
    }
  }

  // set corners in map array
  int a=0;
  for(int i=0;i<40;i+=39){
    for(int j=0;j<40;j+=39){
      tilevalue[i][j]=cornervalues[a];
      cout<<"Output corner "<<a<<" value: "<<cornervalues[a]<<endl;
      a++;
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
    for(int j=0;j<40;j++) fptr<<setw(2)<<setfill('0')<<tilevalue[i][j]<<" ";
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
  if(tilevalue[(pos[0]+pos[2])/2][(pos[1]+pos[3])/2] > 95) tilevalue[(pos[0]+pos[2])/2][(pos[1]+pos[3])/2]=95;

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
