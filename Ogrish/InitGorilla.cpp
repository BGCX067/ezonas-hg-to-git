#ifndef __APPLE__
#include "stdafx.h"
#endif

void Application :: InitGorilla()
{
	string fontname("test");

	int atlas_index;
	int w = viewport -> getActualWidth(),
		h = viewport -> getActualHeight();

	if(fontname == "dejavu") atlas_index = 9;
	if(fontname == "dejavuserif") atlas_index = 12;
	if(fontname == "test") atlas_index = 7;

	mGorilla -> loadAtlas(fontname);
	gor_screen = mGorilla -> createScreen(viewport, fontname);
	gor_layer = gor_screen -> createLayer(0);
	//gor_layer ->

	gor_rect = gor_layer -> createRectangle(0,0,300, 50);
	gor_rect -> background_colour(ColourValue(0.3f, 0.3f, 0.3f, 0.3f));

	gor_caption[0] = gor_layer -> createCaption(atlas_index, 0, 0,
		//string("Does the lazy fox quickly jumps over the brown dog ?"));
		string("Counter Cake is Zevil"));
	gor_caption[1] = gor_layer -> createCaption(atlas_index, 200, 2,
		string("-"));
	//gor_caption[2] = gor_layer -> createCaption(atlas_index, 300, 2,
	//	string("-"));
	//gor_caption[3] = gor_layer -> createCaption(atlas_index, 400, 2,
	//	string("-"));
	//gor_caption[0] -> align(Gorilla :: TextAlign_Centre);
	//gor_caption[0] -> vertical_align(Gorilla :: VerticalAlign_Middle);
	//gor_caption[0] -> 

	//gor_rect -> border(10, ColourValue());
}

