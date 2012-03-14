#include "stdafx.h"
void Application :: init_bullets()
{
	bullet_speed = GetFloat("bullet_speed");
	nextbullet	 = 0;
	was_fired	 = false;
	trigger_state= false;
	time_stack	 = 0;
	fire_delay	 = GetFloat("fire_delay");
	offset_x	 = GetFloat("offset_x");
	offset_y	 = GetFloat("offset_y");
	
	n_bullet	.resize(BULLET_MAX);
	bb_dot		.resize(BULLET_MAX);
	bb_trace	.resize(BULLET_MAX);
	callbacks	.resize(BULLET_MAX);

	float trace_width	 = GetFloat("trace_width");
	float trace_length = GetFloat("trace_length");

	
	FOR(BULLET_MAX)
	{
		// trace
		bb_trace[i] = (BillboardChain *) bbchfact.createInstance ("bullet"+TO_STR(i), scmgr);
		bb_trace[i] -> setMaterialName("jokoon/bullet_trace");
		bb_trace[i] -> setTextureCoordDirection(BillboardChain :: TCD_V);
		bb_trace[i] -> setUseTextureCoords(true);
		bb_trace[i] -> setMaxChainElements(2);
		bb_trace[i] -> addChainElement (0, BillboardChain::Element
			(Vec3(0, 0, 0), trace_width, 0, ColourValue()));
		bb_trace[i] -> addChainElement (0, BillboardChain::Element
			(Vec3(0, 0, trace_length), trace_width, 0, ColourValue()));
		// dot
		bb_dot[i] = scmgr -> createBillboardSet();
		bb_dot[i] -> createBillboard(Vec3(0,0,0));
		bb_dot[i] -> setMaterialName("jokoon/bullet_dot");
		float scale = GetFloat("bullet_dot");
		bb_dot[i]
			-> getMaterial() -> getTechnique(0u) -> getPass(0u)
			-> getTextureUnitState(0u) -> setTextureScale(scale, scale);
		// nodes
		n_bullet[i] = n_root -> createChildSceneNode("bullet"+TO_STR(i));
		n_bullet[i] -> attachObject(bb_trace[i]);
		n_bullet[i] -> attachObject(bb_dot[i]);
	}
}
