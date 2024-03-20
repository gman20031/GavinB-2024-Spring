#pragma once


struct Position
{
	int x;
	int y;
};

bool operator==(const Position& lhs, const Position& rhs)
{
	return(
		lhs.x == rhs.x
	and lhs.y == rhs.y
	);
}

enum class Direction
{
	kUp = 'w',
	kDown = 's',
	kRight = 'd',
	kLeft = 'a',
};

//Box and Dots and box and dots and box and dots
class DotsAndBoxesGame
{
	Position m_CursorPosition;

	char** m_ppGameCharGrid;
	int m_boardWidth;
	int m_boardHeight;

	bool m_keepRunning;
	int m_playerCount;
	int m_currentPlayer;
	//Required tasks, 
	//	5x5 board, playable by two players
	void IntroSequence();
	int AskInteger(int min, int max);
	int AskInteger(int min);
	bool AskNumberOfPlayers();
	bool AskBoardSize();
	//	Implement core game loop.
	void Draw();//	Print board accurately
	void DrawSelected(); // require windows.h
	void ChangePlayer(int newPlayer);//	Allow players to take turns
	void GetGameInput();
	void HandleInput(int input);
	void MoveCursor(Direction direction);
	void SetCursor(Position newPosition);
	void InteractPressed();//	Add lines
	void AddLine(Position linePosition);
	//Extra tasks
	void Resize(int width, int height);//	Resizable boards
	void ChangePlayers(int numberPlayers);//	More than two players
	//	Game can finish
	void CheckBoxCompletion(Position boxPostion);//	Checks when box is complete
	void BoxCompleted();//	Checks who completed box
	void GivePlayerPoint();//	Tracks points
	bool NoBoxesRemaining();//	Check if game is done

	void ResetAll();
	void ResetScore();
	void DeleteGrid();
public:
	~DotsAndBoxesGame(); // for destroying the heap allocated 2dArray

	void Start();
};