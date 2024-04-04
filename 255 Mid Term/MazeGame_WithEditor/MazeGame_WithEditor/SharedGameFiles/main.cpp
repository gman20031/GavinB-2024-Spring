#include "MazeGameMenuSystem.h"

int main()
{
	ConsoleManip::ChangeConsoleTitle("Maze Game");
	MazeGameStartMenu menu;
	menu.StartMazeGame();
}
/*
	Todo:
	ability to play all maps in sucession
		-Select level or play all button
		-if play all
		-Load level from directory(default directory)
		-use next level functions
	Player vision drawn to wall
		-???
	!! DONE Ability to kill enemies !!
	
	Pushable boxes
		-take player postion and box position on collide
		-collide with the space opposite from the entity
			-Entity or normal object subclass?
	Dont redraw whole map in level editor
		-Only draw at cursor location when button is pressed.
		-however, cursor needs to be exact now not just abstract in postioning of level

*/