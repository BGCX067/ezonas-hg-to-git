#include "stdafx.h"

void Application :: InitGorilla()
{
	string fontname("dejavuserif");
	mGorilla -> loadAtlas(fontname);
	gor_screen = mGorilla -> createScreen(viewport, fontname);
	gor_layer = gor_screen -> createLayer(0);

	gor_caption[0] = gor_layer -> createCaption(12, 2, 2,
		//string("Does the lazy fox quickly jumps over the brown dog ?"));
		string("Counter Cake is Zevil"));
	gor_caption[1] = gor_layer -> createCaption(12, 200, 2,
		string("-"));
	gor_rect = gor_layer -> createRectangle(100,100);
	gor_rect -> background_colour(ColourValue(1, 0.3, 0.3));
	//gor_rect -> border(10, ColourValue());
}

