#pragma once
#include <vector>

#include "Entity.h"

#define MOVECONCEPT 0

class GameWindow
{
	const char* m_title;
	int m_xPosition;
	int m_yPosition;
	int m_height;
	int m_width;

	bool m_keepRunning = true;
	SDL_Window* m_pDisplayWindow = nullptr;
	SDL_Renderer* m_graphicRenderer = nullptr;
	SDL_Color m_backgroundColor{ 255,255,255,255 };//black rn

	std::vector<Entity*> m_entityVector;

	void SetRenderColor(SDL_Color* newColor);
	void SetRenderColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void ClearWindowToBackgroundColor();
	void InitWindow();

	void HandleEvent(const SDL_Event& event);
	void DrawAll();
	void HandleKeyInput(const SDL_Event& event);
public:
	GameWindow();
	GameWindow(const char* title, int xPos, int yPos, int height, int width);

	void StartWindow();
	void StopWindow();

	SDL_Color& GetColorRef() { return m_backgroundColor; }
};