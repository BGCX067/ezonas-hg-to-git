#include "stdafx.h"

void Application :: InitResources()
{
	// RESOURCES ////////////////////////////////////////
    ConfigFile cf;
#ifdef __APPLE__
    cf.load(macBundlePath() + "/Contents/Resources/"+"conf/resources_d.cfg");
	PRINTLOG(macBundlePath() + "/Contents/Resources/");
#else
    cf.load("conf/resources_d.cfg");
#endif

    ConfigFile :: SectionIterator sectionIter = cf.getSectionIterator();
    String sectionName, typeName, dataname;
    while (sectionIter.hasMoreElements())
    {
        sectionName = sectionIter.peekNextKey();
        ConfigFile :: SettingsMultiMap * settings = sectionIter.getNext();
        ConfigFile :: SettingsMultiMap :: iterator i;
        for (i = settings -> begin(); i != settings -> end(); ++i)
        {
            typeName = i -> first;
            dataname = i -> second;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
			Ogre::String archName;
            // OS X does not set the working directory relative to the app,
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location
            if (!Ogre::StringUtil::startsWith(dataname, "/", false)) // only adjust relative dirs
                dataname = Ogre::String(Ogre::macBundlePath() + "/Contents/Resources/" + dataname);
#endif
            ResourceGroupManager :: getSingleton().addResourceLocation(
				dataname, typeName, sectionName);
        }
	}
    ResourceGroupManager :: getSingleton().initialiseAllResourceGroups();
}