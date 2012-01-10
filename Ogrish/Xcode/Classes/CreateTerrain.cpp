#ifndef __APPLE__
#include "stdafx.h"
#endif
#ifdef USE_TERRAIN
void Application :: CreateTerrain()
{
	// terrain objects
	mGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
	mTerrain = OGRE_NEW Ogre::Terrain(scmgr);
	Ogre::Image img;
	img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	Ogre::Terrain::ImportData imp;
	imp.inputImage = & img;
	imp.terrainSize = img.getWidth();
	imp.worldSize = 500;
	imp.inputScale = 50;
	imp.minBatchSize = 33;
	imp.maxBatchSize = 65;

	imp.layerList.resize(1);
	imp.layerList[0].worldSize = 100;
	imp.layerList[0].textureNames.push_back("grass_green-01_diffusespecular.dds");
	imp.layerList[0].textureNames.push_back("grass_green-01_normalheight.dds");

	mTerrain->prepare(imp);
	mTerrain->load();
	
	mTerrain->freeTemporaryResources();
}
#endif