#include "Drawer.h"

using namespace std;

Drawer::Drawer(int displayX, int displayY) :
	display{ nullptr }{

	if (!al_init())
		throw exception("ERROR: al_init()");

	if (!al_init_primitives_addon())
		throw exception("ERROR: al_init_primitives_addon()");

	display = al_create_display(displayX, displayY);
	if (display == nullptr)
		throw exception("ERROR: al_create_display(x, y)");

	currColor = al_map_rgb(0, 0, 0);
}


Drawer::~Drawer(){
	if (display != nullptr)
		al_destroy_display(display);
}

void Drawer::Flip(){
	al_flip_display();
}

void Drawer::SetColor(uint8_t r, uint8_t g, uint8_t b){
	currColor = al_map_rgb(r, g, b);
}

void Drawer::Rect(int x, int y, int w, int h){
	al_draw_rectangle(x, y, x + w, y + w, currColor, 1);
}

void Drawer::Clear(){
	al_clear_to_color(currColor);
}

void Drawer::Circle(int x, int y, int r, bool filled){
	if (filled)
		al_draw_filled_circle(x, y, r, currColor);
	else
		al_draw_circle(x, y, r, currColor, 1);
}

void Drawer::Line(int startX, int startY, int endX, int endY){
	al_draw_line(startX, startY, endX, endY, currColor, 1);
}

void Drawer::Wait(float sec){
	al_rest(sec);
}
