#pragma once

#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class Drawer{

	ALLEGRO_DISPLAY* display;
	ALLEGRO_COLOR currColor;

public:
	Drawer(int displayX, int displayY);
	~Drawer();

	void	Flip();
	void	Clear();
	void	SetColor(uint8_t r, uint8_t g, uint8_t b);
	void	Rect(int x, int y, int w, int h);
	void	Circle(int x, int y, int r, bool filled);
	void	Line(int startX, int startY, int endX, int endY);
	void	Wait(float sec);
};

