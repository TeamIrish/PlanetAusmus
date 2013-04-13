// Matt Mahan, Benjamin Law, Matt Rundle, Paul Kennedy
// CSE20212 Final Project

#include"MapEditor.h"


// constructor
Objectives::Objectives(){

	ifstream file("objectives.txt");
	string line;
	
	while(file){
		getline(file,line);
		list.push_back(line);
	}
	file.close();
	
	CurrentObj = list[0];
	if(MapEditor::debug) cout << "Objectives object constructed." << endl;
}

// update
int Objectives::Update(int LineNum){

	return 1;
}
