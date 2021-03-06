all: PlanetAusmus

PlanetAusmus: MapEditor.o MapEditor_OnInit.o MapEditor_OnEvent.o MapEditor_OnLoop.o MapEditor_OnRender.o MapEditor_OnCleanup.o MapEditor_OnSave.o MapEditor_MapGenerate.o Surface.o Event.o Camera.o Map.o Tile.o Entity.o Enemy.o Bullet.o Heart.o Objectives.o Timer.o Chest.o
	g++ MapEditor.o MapEditor_OnInit.o MapEditor_OnEvent.o MapEditor_OnLoop.o MapEditor_OnRender.o MapEditor_OnCleanup.o MapEditor_OnSave.o MapEditor_MapGenerate.o Surface.o Event.o Camera.o Map.o Tile.o Entity.o Enemy.o Bullet.o Heart.o Objectives.o Timer.o Chest.o -o PlanetAusmus -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -Wall

MapEditor.o: MapEditor.cpp MapEditor.h
	g++ -c MapEditor.cpp -Wall -Wno-write-strings
MapEditor_OnInit.o: MapEditor_OnInit.cpp
	g++ -c MapEditor_OnInit.cpp -Wall
MapEditor_OnEvent.o: MapEditor_OnEvent.cpp
	g++ -c MapEditor_OnEvent.cpp -Wall
MapEditor_OnLoop.o: MapEditor_OnLoop.cpp
	g++ -c MapEditor_OnLoop.cpp -Wall
MapEditor_OnRender.o: MapEditor_OnRender.cpp
	g++ -c MapEditor_OnRender.cpp -Wall
MapEditor_OnCleanup.o: MapEditor_OnCleanup.cpp
	g++ -c MapEditor_OnCleanup.cpp -Wall
MapEditor_OnSave.o: MapEditor_OnSave.cpp
	g++ -c MapEditor_OnSave.cpp -Wall
MapEditor_MapGenerate.o: MapEditor_MapGenerate.cpp
	g++ -c MapEditor_MapGenerate.cpp -Wall
Surface.o: Surface.cpp
	g++ -c Surface.cpp -Wall
Event.o: Event.cpp
	g++ -c Event.cpp -Wall
Camera.o: Camera.cpp
	g++ -c Camera.cpp -Wall
Map.o: Map.cpp
	g++ -c Map.cpp -Wall
Tile.o: Tile.cpp
	g++ -c Tile.cpp -Wall
Entity.o: Entity.cpp
	g++ -c Entity.cpp -Wall
Enemy.o: Enemy.cpp
	g++ -c Enemy.cpp -Wall
Objectives.o: Objectives.cpp
	g++ -c Objectives.cpp -Wall
Bullet.o: Bullet.cpp
	g++ -c Bullet.cpp -Wall
Heart.o: Heart.cpp
	g++ -c Heart.cpp -Wall
Chest.o: Chest.cpp
	g++ -c Chest.cpp -Wall
Timer.o: Timer.cpp
	g++ -c Timer.cpp -Wall

clean:
	rm -f *.o *~ PlanetAusmus maps/*
