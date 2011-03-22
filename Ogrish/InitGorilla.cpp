#include "stdafx.h"

void Application :: InitGorilla()
{
	mGorilla -> loadAtlas("test");
	// screen
	gor_screen = mGorilla -> createScreen(viewport, "test");
	
	// a layer
	gor_layer = gor_screen -> createLayer();//10,10, "", 15);

	// a rectangle
	gor_rect = gor_layer -> createRectangle(0, 0);
	gor_rect -> background_colour(ColourValue(0.3, 0.3, 0.3, 0.3));

	// a text caption
	gor_caption = gor_layer -> createCaption(7, 2, 2, string("Counter Cake"));

}