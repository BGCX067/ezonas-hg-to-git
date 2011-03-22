#include "stdafx.h"

void Application :: InitGorilla()
{
	//string fontname("BLUH");
	mGorilla -> loadAtlas("george");
	// screen
	gor_screen = mGorilla -> createScreen(viewport, "george");
	
	// 
	// a layer
	gor_layer = gor_screen -> createLayer(0);//10,10, "", 15);

	// a text caption
	gor_rect = gor_layer -> createRectangle(10,10,12,12);
	gor_rect -> background_colour(ColourValue(0.3, 0.3, 0.3, 1));
	gor_rect -> border(10, ColourValue());
	gor_caption = gor_layer -> createCaption(16, 2, 2, string("Does the lazy fox quickly jumps over the brown dog ?"));

	//gor_mutext = gor_layer -> createMarkupText(7, 0, 0, "DUH DUH DUH");
	//gor_caption ->
}
	//gor_caption = gor_layer -> createCaption(16, 2, 2, string(
//		"Counter Cake"));
// "^&*.,;:\"~@#"));
	//"li.li,j'j!|l:i;li"));
	// a rectangle
