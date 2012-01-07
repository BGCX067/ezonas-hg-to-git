/* -------------------------------------------------------

The code in this file is not affected by the CameraControlSystem
license.

------------------------------------------------------- */

#define PLANE_SIZE 1000.0f

// ---------------------------------------------------------------------------
// Include CameraControlSystem header files
// ---------------------------------------------------------------------------
//#include <CCSCameraControlSystem.h>
//#include "CCSBasicCameraModes.h"
//#include "CCSFreeCameraMode.h"
//#include "CCSOrbitalCameraMode.h"

// Let include a custom camera mode
//#include "DummyCameraMode.h"

#include "stdafx.h"

// ----------------------------------------------------------------------------
// Include the main OGRE header files
// Ogre.h just expands to including lots of individual OGRE header files
// ----------------------------------------------------------------------------
#ifdef CCS_OGRE_1_7
     #include <OGRE/Ogre.h>
     #include <OGRE/OgreTextAreaOverlayElement.h>

     // ----------------------------------------------------------------------------
     // Include the OGRE example framework
     // This includes the classes defined to make getting an OGRE application running
     // a lot easier. It automatically sets up all the main objects and allows you to
     // just override the bits you want to instead of writing it all from scratch.
     // ----------------------------------------------------------------------------
     #include <OGRE/ExampleApplication.h>
//////#else
//     #include <Ogre.h>
//     #include <OgreTextAreaOverlayElement.h>
//
//     // ----------------------------------------------------------------------------
//     // Include the OGRE example framework
//     // This includes the classes defined to make getting an OGRE application running
//     // a lot easier. It automatically sets up all the main objects and allows you to
//     // just override the bits you want to instead of writing it all from scratch.
//     // ----------------------------------------------------------------------------
//     #include <ExampleApplication.h>
#endif


CCS::CameraControlSystem* mCameraCS = NULL;

// ----------------------------------------------------------------------------
// Misc
// ----------------------------------------------------------------------------
Ogre::TextAreaOverlayElement* mTextArea = 0;
bool mShowInformation = false;
SceneNode *headNode ;
SceneNode* atheneNode;
AnimationState* mAnimState;

// ----------------------------------------------------------------------------
// Define the application object
// This is derived from ExampleApplication which is the class OGRE provides to
// make it easier to set up OGRE without rewriting the same code all the time.
// You can override extra methods of ExampleApplication if you want to further
// specialise the setup routine, otherwise the only mandatory override is the
// 'createScene' method which is where you set up your own personal scene.
// ----------------------------------------------------------------------------
class CameraControlSystemDemoFrameListener : public ExampleFrameListener
{
public:
    SceneManager *mSceneMgr;
    Real mKeyBuffer;

    CameraControlSystemDemoFrameListener(RenderWindow* win, Camera* cam, SceneManager *sm)
            : ExampleFrameListener(win,cam)
            , mSceneMgr(sm)
            , mKeyBuffer(-1)
    {
    }

    Ogre::String getInfo()
    {
        Ogre::String text = "CameraControlSystem Demo\n\n";
        text += "Press \"SPACE\" to change the camera mode.\n\n";
        text += "Current camera mode: " + mCameraCS->getCameraModeName(mCameraCS->getCurrentCameraMode());

        return text;
    }

    bool frameStarted(const FrameEvent &e)
    {
        mKeyboard->capture();

        if( mKeyboard->isKeyDown(OIS::KC_ESCAPE) || mKeyboard->isKeyDown(OIS::KC_Q) )
			return false;

		// Show/Hide information
		if (mKeyboard->isKeyDown(OIS::KC_F1) && mKeyBuffer < 0)
        {
			mShowInformation = !mShowInformation;

			mKeyBuffer = 0.25f;
		}

        if (mKeyboard->isKeyDown(OIS::KC_SPACE) && mKeyBuffer < 0)
        {
            mCameraCS->setCurrentCameraMode(mCameraCS->getNextCameraMode());

            mKeyBuffer = 0.25f;
        }

		mTextArea->setCaption(getInfo());

        mAnimState->addTime(e.timeSinceLastFrame);

		mCameraCS->update(e.timeSinceLastFrame);

		mKeyBuffer -= e.timeSinceLastFrame;

        return true;
    }

    // Overriden
    virtual bool processUnbufferedKeyInput(const FrameEvent& evt)
	{
		processCamaraKeyInput();

		if( mKeyboard->isKeyDown(OIS::KC_ESCAPE) || mKeyboard->isKeyDown(OIS::KC_Q) )
			return false;

       	if( mKeyboard->isKeyDown(OIS::KC_F) && mTimeUntilNextToggle <= 0 )
		{
			mStatsOn = !mStatsOn;
			showDebugOverlay(mStatsOn);
			mTimeUntilNextToggle = 1;
		}

		if( mKeyboard->isKeyDown(OIS::KC_T) && mTimeUntilNextToggle <= 0 )
		{
			switch(mFiltering)
			{
			case TFO_BILINEAR:
				mFiltering = TFO_TRILINEAR;
				mAniso = 1;
				break;
			case TFO_TRILINEAR:
				mFiltering = TFO_ANISOTROPIC;
				mAniso = 8;
				break;
			case TFO_ANISOTROPIC:
				mFiltering = TFO_BILINEAR;
				mAniso = 1;
				break;
			default: break;
			}
			MaterialManager::getSingleton().setDefaultTextureFiltering(mFiltering);
			MaterialManager::getSingleton().setDefaultAnisotropy(mAniso);

			showDebugOverlay(mStatsOn);
			mTimeUntilNextToggle = 1;
		}

		if(mKeyboard->isKeyDown(OIS::KC_SYSRQ) && mTimeUntilNextToggle <= 0)
		{
			std::ostringstream ss;
			ss << "screenshot_" << ++mNumScreenShots << ".png";
			mWindow->writeContentsToFile(ss.str());
			mTimeUntilNextToggle = 0.5;
			mDebugText = "Saved: " + ss.str();
		}

		if(mKeyboard->isKeyDown(OIS::KC_R) && mTimeUntilNextToggle <=0)
		{
			mSceneDetailIndex = (mSceneDetailIndex+1)%3 ;
			switch(mSceneDetailIndex) {
				case 0 : mCamera->setPolygonMode(PM_SOLID); break;
				case 1 : mCamera->setPolygonMode(PM_WIREFRAME); break;
				case 2 : mCamera->setPolygonMode(PM_POINTS); break;
			}
			mTimeUntilNextToggle = 0.5;
		}

		static bool displayCameraDetails = false;
		if(mKeyboard->isKeyDown(OIS::KC_P) && mTimeUntilNextToggle <= 0)
		{
			displayCameraDetails = !displayCameraDetails;
			mTimeUntilNextToggle = 0.5;
			if (!displayCameraDetails)
				mDebugText = "";
		}

		// Print camera details
		if(displayCameraDetails)
			mDebugText = "P: " + StringConverter::toString(mCamera->getDerivedPosition()) +
						 " " + "O: " + StringConverter::toString(mCamera->getDerivedOrientation());

		// Return true to continue rendering
		return true;
	}

	void processCamaraKeyInput()
	{
		if(mCameraCS->getCameraModeName(mCameraCS->getCurrentCameraMode()) == "Free")
        {
            CCS::FreeCameraMode* freeCameraMode = (CCS::FreeCameraMode*)mCameraCS->getCameraMode("Free");

			if(mKeyboard->isKeyDown(OIS::KC_A))
				//mTranslateVector.x = -mMoveScale;	// Move camera left
				freeCameraMode->goLeft();

			if(mKeyboard->isKeyDown(OIS::KC_D))
				//mTranslateVector.x = mMoveScale;	// Move camera RIGHT
				freeCameraMode->goRight();

			if(mKeyboard->isKeyDown(OIS::KC_UP) || mKeyboard->isKeyDown(OIS::KC_W) )
				//mTranslateVector.z = -mMoveScale;	// Move camera forward
				freeCameraMode->goForward();

			if(mKeyboard->isKeyDown(OIS::KC_DOWN) || mKeyboard->isKeyDown(OIS::KC_S) )
				//mTranslateVector.z = mMoveScale;	// Move camera backward
				freeCameraMode->goBackward();

			if(mKeyboard->isKeyDown(OIS::KC_PGUP))
				//mTranslateVector.y = mMoveScale;	// Move camera up
				freeCameraMode->goUp();

			if(mKeyboard->isKeyDown(OIS::KC_PGDOWN))
				//mTranslateVector.y = -mMoveScale;	// Move camera down
				freeCameraMode->goDown();

			if(mKeyboard->isKeyDown(OIS::KC_RIGHT))
				//mCamera->yaw(-mRotScale);
				freeCameraMode->yaw(-1);

			if(mKeyboard->isKeyDown(OIS::KC_LEFT))
				//mCamera->yaw(mRotScale);
				freeCameraMode->yaw(1);
		}
		else if(mCameraCS->getCameraModeName(mCameraCS->getCurrentCameraMode()) == "Orbital"
			|| mCameraCS->getCameraModeName(mCameraCS->getCurrentCameraMode()) == "Orbital (collidable)")
		{
			CCS::OrbitalCameraMode* orbitalCameraMode;

			if(mCameraCS->getCameraModeName(mCameraCS->getCurrentCameraMode()) == "Orbital")
			{
				orbitalCameraMode = (CCS::OrbitalCameraMode*)mCameraCS->getCameraMode("Orbital");
			}
			else
			{
				orbitalCameraMode = (CCS::OrbitalCameraMode*)mCameraCS->getCameraMode("Orbital (collidable)");
			}

			if(mKeyboard->isKeyDown(OIS::KC_A))
                orbitalCameraMode->yaw(1);

			if(mKeyboard->isKeyDown(OIS::KC_D))
                orbitalCameraMode->yaw(-1);

			if(mKeyboard->isKeyDown(OIS::KC_W))
                orbitalCameraMode->pitch(1);

			if(mKeyboard->isKeyDown(OIS::KC_S))
                orbitalCameraMode->pitch(-1);

			if(mKeyboard->isKeyDown(OIS::KC_PGUP))
                orbitalCameraMode->zoom(-1);

			if(mKeyboard->isKeyDown(OIS::KC_PGDOWN))
                orbitalCameraMode->zoom(1);
		}
	}

    // Overriden
	virtual bool processUnbufferedMouseInput(const FrameEvent& evt)
	{

		// Rotation factors, may not be used if the second mouse button is pressed
		// 2nd mouse button - slide, otherwise rotate
		const OIS::MouseState &ms = mMouse->getMouseState();
		if( ms.buttonDown( OIS::MB_Right ) )
		{
			//mTranslateVector.x += ms.X.rel * 0.13;
			//mTranslateVector.y -= ms.Y.rel * 0.13;
		}
		else
		{
			//mRotX = Degree(-ms.X.rel * 0.13);
			//mRotY = Degree(-ms.Y.rel * 0.13);

            if(mCameraCS->getCameraModeName(mCameraCS->getCurrentCameraMode()) == "Free")
            {
                CCS::FreeCameraMode* freeCameraMode = (CCS::FreeCameraMode*)mCameraCS->getCameraMode("Free");

				freeCameraMode->yaw(ms.X.rel);
                freeCameraMode->pitch(ms.Y.rel);
            }
		}


		return true;
	}

    // Overriden
	virtual void moveCamera()
	{
		// Make all the changes to the camera
		// Note that YAW direction is around a fixed axis (freelook style) rather than a natural YAW
		//(e.g. airplane)
		//mCamera->yaw(mRotX);
		//mCamera->pitch(mRotY);
		//mCamera->moveRelative(mTranslateVector);
	}

};

class CameraControlSystemDemo : public ExampleApplication
{
public:
    // Basic constructor
    CameraControlSystemDemo()
    {}

protected:

    // Overriden
    void createFrameListener(void) { };

    // Overriden
    void createCamera(void)
    {
        // Create the camera
        mCamera = mSceneMgr->createCamera("PlayerCam");

        // Position it at 500 in Z direction
        //mCamera->setPosition(Vector3(0,0,500));
        // Look back along -Z
        //mCamera->lookAt(Vector3(0,0,-300));
        mCamera->setNearClipDistance(5);
    }

    // Just override the mandatory create scene method
    void createScene(void)
    {
        // Set ambient light
        mSceneMgr->setAmbientLight(ColourValue(0.75, 0.75, 0.75));

        // Create a light
        Light* l = mSceneMgr->createLight("MainLight");
        // Accept default settings: point light, white diffuse, just set position
        // NB I could attach the light to a SceneNode if I wanted it to move automatically with
        //  other objects, but I don't
        l->setPosition(200,700,100);

        mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE);

        // Create a skydome
        mSceneMgr->setSkyDome(true, "Examples/CloudySky", 30, 5);

        // Put in a bit of fog for the hell of it
        mSceneMgr->setFog(FOG_EXP, ColourValue::White, 0.0001, 0.5);

		// Define a floor plane mesh
        Plane p;
        p.normal = Vector3::UNIT_Y;
        p.d = 180;
        MeshManager::getSingleton().createPlane("FloorPlane",
            ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            p,PLANE_SIZE*1000,PLANE_SIZE*1000,20,20,true,1,50,50,Vector3::UNIT_Z);

        Entity *ent = mSceneMgr->createEntity("floorEntity", "FloorPlane");
        ent->setMaterialName("Examples/RustySteel");
        ent->setCastShadows(false);
        SceneNode *floorNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("floorSceneNode");
		floorNode->attachObject(ent);

        // Add a head, give it it's own node
        // The Ogre head faces to Z
        headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("headSceneNode");
        ent = mSceneMgr->createEntity("head", "ogrehead.mesh");
        ent->setCastShadows(true);
        headNode->attachObject(ent);

        atheneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("atheneSceneNode");
        Entity *Athene = mSceneMgr->createEntity( "athene2", "athene.mesh" );
        Athene->setMaterialName("Examples/Athene/NormalMapped");
        Athene->setCastShadows(true);
        atheneNode->attachObject( Athene );
        atheneNode->setPosition(Ogre::Vector3(500,-100,500));

		// Obstacle for collisions detection
		/*SceneNode* barrelNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("barrelSceneNode");
        Entity *barrel = mSceneMgr->createEntity( "barrel", "barrel.mesh" );
        barrel->setCastShadows(true);
        barrelNode->attachObject( barrel );
        barrelNode->setPosition(Ogre::Vector3(1300,0,500));
		barrelNode->scale(40,40,40);
		mSceneMgr->showBoundingBoxes(true);*/

		// Create light node
        SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("lightSceneNode");
		lightNode->attachObject(l);

        createTextArea();

/*        // set up spline animation of node
        Animation* anim = mSceneMgr->createAnimation("HeadTrack", 100);
        // Spline it for nice curves
        anim->setInterpolationMode(Animation::IM_LINEAR);
        // Create a track to animate the camera's node
        NodeAnimationTrack* track = anim->createNodeTrack(0, headNode);
        // Setup keyframes
        TransformKeyFrame* key = track->createNodeKeyFrame(0); // startposition
        key->setTranslate(Vector3(0,0,0));
        key->setRotation(Ogre::Quaternion::IDENTITY);
        key = track->createNodeKeyFrame(100);
        key->setTranslate(Vector3(0,0,10000));
*/
        // set up spline animation of node
        Animation* anim = mSceneMgr->createAnimation("HeadTrack", 20);
        // Spline it for nice curves
        anim->setInterpolationMode(Animation::IM_SPLINE);
        // Create a track to animate the camera's node
        NodeAnimationTrack* track = anim->createNodeTrack(0, headNode);
        // Setup keyframes
        TransformKeyFrame* key = track->createNodeKeyFrame(0); // startposition
        key->setTranslate(Vector3(0,0,0));
        key->setRotation(Ogre::Quaternion::IDENTITY);
        key = track->createNodeKeyFrame(2.5);
        key->setTranslate(Vector3(0,0,1000));
        key->setRotation(Vector3::UNIT_Z.getRotationTo(Vector3(1000,0,1000)));
        key = track->createNodeKeyFrame(5);
        key->setTranslate(Vector3(1000,0,1000));
        key->setRotation(Vector3::UNIT_Z.getRotationTo(Vector3(1000,0,0)));
        key = track->createNodeKeyFrame(7.5);
        key->setTranslate(Vector3(1000,0,0));
        key->setRotation(Vector3::UNIT_Z.getRotationTo(Vector3::NEGATIVE_UNIT_X));
        key = track->createNodeKeyFrame(10);
        key->setTranslate(Vector3(0,0,0));

        // Second round
        key = track->createNodeKeyFrame(11);
        key->setTranslate(Vector3(0,0,400));
        key->setRotation(Quaternion(Radian(3.14/4.0),Vector3::UNIT_Z));
        key = track->createNodeKeyFrame(11.5);
        key->setTranslate(Vector3(0,0,600));
        key->setRotation(Quaternion(Radian(-3.14/4.0),Vector3::UNIT_Z));
        key = track->createNodeKeyFrame(12.5);
        key->setTranslate(Vector3(0,0,1000));
        key->setRotation(Vector3::UNIT_Z.getRotationTo(Vector3(500,500,1000)));
        key = track->createNodeKeyFrame(13.25);
        key->setTranslate(Vector3(500,500,1000));
        key->setRotation(Vector3::UNIT_Z.getRotationTo(Vector3(1000,-500,1000)));
        key = track->createNodeKeyFrame(15);
        key->setTranslate(Vector3(1000,0,1000));
        key->setRotation(Vector3::UNIT_Z.getRotationTo(Vector3(1000,0,-500)));
        key = track->createNodeKeyFrame(16);
        key->setTranslate(Vector3(1000,0,500));
        key = track->createNodeKeyFrame(16.5);
        key->setTranslate(Vector3(1000,0,600));
        key = track->createNodeKeyFrame(17.5);
        key->setTranslate(Vector3(1000,0,0));
        key->setRotation(Vector3::UNIT_Z.getRotationTo(Vector3(-500,500,0)));
        key = track->createNodeKeyFrame(118.25);
        key->setTranslate(Vector3(500,500,0));
        key->setRotation(Quaternion(Radian(3.14),Vector3::UNIT_X) * Vector3::UNIT_Z.getRotationTo(Vector3(-500,-500,0)));
        key = track->createNodeKeyFrame(20);
        key->setTranslate(Vector3(0,0,0));

        // Create a new animation state to track this
        mAnimState = mSceneMgr->createAnimationState("HeadTrack");
        mAnimState->setEnabled(true);


        // Add frame listener
		mRoot->addFrameListener(new CameraControlSystemDemoFrameListener(mWindow, mCamera, mSceneMgr));

        setupCameraControlSystem();
    }

    void setupCameraControlSystem()
    {
        // By default, Ogre::camera points to -Z

        // Create the camera system using the previously created ogre camera.
		mCameraCS = new CCS::CameraControlSystem(mSceneMgr, "CameraControlSystem", mCamera);

        // -------------------------------------------------------------------------------------
        // Register a "Fixed" camera mode. In this mode the camera position and orientation
        // never change.

        CCS::FixedCameraMode* camMode1;
        camMode1 = new CCS::FixedCameraMode(mCameraCS);
        mCameraCS->registerCameraMode("Fixed (2)",camMode1);
        camMode1->setCameraPosition(Ogre::Vector3(-500,0,-500));
        float roll = 0; float yaw = 225; float pitch = 10;
        camMode1->setCameraOrientation( Quaternion(Radian(Degree(roll)),Vector3::UNIT_Z)
            * Quaternion(Radian(Degree(yaw)),Vector3::UNIT_Y)
            * Quaternion(Radian(Degree(pitch)),Vector3::UNIT_X));

        // -------------------------------------------------------------------------------------
        // Register another "Fixed" camera mode with a different camera position.

        camMode1 = new CCS::FixedCameraMode(mCameraCS);
        mCameraCS->registerCameraMode("Fixed",camMode1);
        //camMode1->setCameraPosition(Ogre::Vector3(PLANE_SIZE,PLANE_SIZE,PLANE_SIZE));
        camMode1->setCameraPosition(Ogre::Vector3(1500,500,1500));
        roll = 0; yaw = 45; pitch = -20;
        camMode1->setCameraOrientation( Quaternion(Radian(Degree(roll)),Vector3::UNIT_Z)
            * Quaternion(Radian(Degree(yaw)),Vector3::UNIT_Y)
            * Quaternion(Radian(Degree(pitch)),Vector3::UNIT_X));

        // -------------------------------------------------------------------------------------
        // Register a "FixedTracking" camera mode. In this mode the camera position is fixed
        // and the camera always points to the target.

        CCS::FixedTrackingCameraMode* camMode2;
        camMode2 = new CCS::FixedTrackingCameraMode(mCameraCS);
        mCameraCS->registerCameraMode("FixedTracking",camMode2);
        camMode2->setCameraPosition(Ogre::Vector3(500,0,-100));

        // -------------------------------------------------------------------------------------
        // Register a "Chase" camera mode with default tightness (0.01). In
        // this mode the camera follows the target. The second parameter is the relative position
        // to the target. The orientation of the camera is fixed by a yaw axis (UNIT_Y by default).

        CCS::ChaseCameraMode* camMode3;
        camMode3 = new CCS::ChaseCameraMode(mCameraCS,Ogre::Vector3(0,0,-200));
        mCameraCS->registerCameraMode("Chase(0.01 tightness)",camMode3);

        // -------------------------------------------------------------------------------------
        // Register another "ChaseCameraMode" camera mode with max tightness value.

        camMode3 = new CCS::ChaseCameraMode(mCameraCS,Ogre::Vector3(0,0,-200));
        mCameraCS->registerCameraMode("Chase(0.2 tightness)",camMode3);
        camMode3->setCameraTightness(0.2);

        // -------------------------------------------------------------------------------------
        // Register a "ChaseFreeYawAxis" camera mode with max tightness. This mode is
        // similar to "Chase" camera mode but the camera orientation is not fixed by
        // a yaw axis. The camera orientation will be the same as the target.

        camMode3 = new CCS::ChaseFreeYawAxisCameraMode(mCameraCS,Ogre::Vector3(0,0,-200)
            , Ogre::Radian(0),Ogre::Radian(Ogre::Degree(180)),Ogre::Radian(0));
        mCameraCS->registerCameraMode("ChaseFreeYawAxis(0.01 tightness)",camMode3);
        camMode3->setCameraTightness(0.05);

        // -------------------------------------------------------------------------------------
        // Register another "ChaseFreeYawAxis" camera mode with 0.05 tightness value.

        camMode3 = new CCS::ChaseFreeYawAxisCameraMode(mCameraCS,Ogre::Vector3(0,0,-200)
            , Ogre::Radian(0),Ogre::Radian(Ogre::Degree(180)),Ogre::Radian(0));
        mCameraCS->registerCameraMode("ChaseFreeYawAxis(0.1 tightness)",camMode3);
        camMode3->setCameraTightness(0.3);


        // -------------------------------------------------------------------------------------
        // Register a "FirstPerson" camera mode.

        CCS::FirstPersonCameraMode* camMode4 = new CCS::FirstPersonCameraMode(mCameraCS,Ogre::Vector3(0,17,-16)
            , Ogre::Radian(0),Ogre::Radian(Ogre::Degree(180)),Ogre::Radian(0));
        mCameraCS->registerCameraMode("FirstPerson",camMode4);

		// -------------------------------------------------------------------------------------
        // Register another "FirstPerson" camera mode where the character is hidden.

		camMode4 = new CCS::FirstPersonCameraMode(mCameraCS,Ogre::Vector3(0,17,-16)
            , Ogre::Radian(0),Ogre::Radian(Ogre::Degree(180)),Ogre::Radian(0));
        mCameraCS->registerCameraMode("FirstPerson (character hidden)",camMode4);
		camMode4->setCharacterVisible(false);

        // -------------------------------------------------------------------------------------
        // Register a "PlaneBinded" camera mode. In this mode the camera is constrained to the
		// limits of a plane. The camera always points to the target, perpendicularly to the plane.

        Ogre::Plane* mPlane = new Ogre::Plane(Ogre::Vector3::UNIT_Z, Ogre::Vector3(0,0,-200));
        CCS::PlaneBindedCameraMode* camMode5 = new CCS::PlaneBindedCameraMode(mCameraCS, *mPlane);
        mCameraCS->registerCameraMode("PlaneBinded (XY)",camMode5);

        // -------------------------------------------------------------------------------------
        // Register another "PlaneBinded" camera mode using a top point of view.

        mPlane = new Ogre::Plane(Ogre::Vector3::UNIT_Y, Ogre::Vector3(0,1000,0));
        camMode5 = new CCS::PlaneBindedCameraMode(mCameraCS, *mPlane, Ogre::Vector3::UNIT_Z);
        mCameraCS->registerCameraMode("PlaneBinded (XZ)",camMode5);

        // -------------------------------------------------------------------------------------
        // Register a "ThroughTarget" camera mode. In this mode the camera points to a given
        // position (the "focus") throuh the target. The camera orientation is fixed by a yaw axis.

        CCS::ThroughTargetCameraMode* camMode6 = new CCS::ThroughTargetCameraMode(mCameraCS, 400);
        mCameraCS->registerCameraMode("ThroughTarget",camMode6);
        camMode6->setCameraFocusPosition(atheneNode->_getDerivedPosition() - Ogre::Vector3(0,100,0));

        // -------------------------------------------------------------------------------------
        // Register another "ThroughTarget" camera mode. In this case the "focus" is the
        // target and vice versa.

        camMode6 = new CCS::ThroughTargetCameraMode(mCameraCS, 400, true);
        mCameraCS->registerCameraMode("ThroughTarget (inverse)",camMode6);
        camMode6->setCameraFocusPosition(atheneNode->_getDerivedPosition() + Ogre::Vector3(0,100,0));

        // -------------------------------------------------------------------------------------
        // Register a "ClosestToTarget" camera mode. In this camera mode the position of the
        // camera is chosen to be the closest to the target of a given list. The camera
        // orientation is fixed by a yaw axis.

        CCS::ClosestToTargetCameraMode* camMode7 = new CCS::ClosestToTargetCameraMode(mCameraCS);
        mCameraCS->registerCameraMode("ClosestToTarget",camMode7);

        Ogre::Vector3* camPos1 = new Ogre::Vector3(-400,0,-400);
        Ogre::Vector3* camPos2 = new Ogre::Vector3(-400,0,1400);
        Ogre::Vector3* camPos3 = new Ogre::Vector3(1400,0,1400);

        camMode7->addCameraPosition(*camPos1);
        camMode7->addCameraPosition(*camPos2);
        camMode7->addCameraPosition(*camPos3);

        // -------------------------------------------------------------------------------------
        // Register an "Attached" camera mode. In this mode the camera node is attached to the
        // target node as a child.

        CCS::AttachedCameraMode* camMode8 = new CCS::AttachedCameraMode(mCameraCS,Ogre::Vector3(200,0,0)
            , Ogre::Radian(0),Ogre::Radian(Ogre::Degree(90)),Ogre::Radian(0));
        mCameraCS->registerCameraMode("Attached (lateral)",camMode8);

		camMode8 = new CCS::AttachedCameraMode(mCameraCS,Ogre::Vector3(0,50,-200)
            , Ogre::Radian(0),Ogre::Radian(Ogre::Degree(180)),Ogre::Radian(0));
        mCameraCS->registerCameraMode("Attached (back/top)",camMode8);

        // -------------------------------------------------------------------------------------
        // Register a "Free" camera mode. In this mode the camera is controlled by the user.
        // The camera orientation is fixed to a yaw axis.

        CCS::FreeCameraMode* camMode9 = new CCS::FreeCameraMode(mCameraCS);
        mCameraCS->registerCameraMode("Free",camMode9);
        camMode9->setMoveFactor(30);

        // -------------------------------------------------------------------------------------
        // Register a "FixedDirection" camera mode. In this mode the
		// target is always seen from the same point of view.

        CCS::FixedDirectionCameraMode* camMode10 = new CCS::FixedDirectionCameraMode(mCameraCS, Ogre::Vector3(-1,-1,-1), 1000);
        mCameraCS->registerCameraMode("Fixed direction",camMode10);

		// -------------------------------------------------------------------------------------
        // Register another "FixedDirection" camera mode with a 0.01 tightness value.

		camMode10 = new CCS::FixedDirectionCameraMode(mCameraCS, Ogre::Vector3(-1,-1,-1), 1000);
        mCameraCS->registerCameraMode("Fixed direction (0.01 tightness)",camMode10);
		camMode10->setCameraTightness(0.01);

		// -------------------------------------------------------------------------------------
        // Register an "Orbital" camera mode. This is basically an attached camera mode where the user
	    // can mofify the camera position. If the scene focus is seen as the center of a sphere, the camera rotates arount it

        CCS::OrbitalCameraMode* camMode12 = new CCS::OrbitalCameraMode(mCameraCS, 200);
        mCameraCS->registerCameraMode("Orbital",camMode12);
		camMode12->setZoomFactor(100);
		camMode12->setRotationFactor(50);

		// -------------------------------------------------------------------------------------
        // Register a collidable orbital camera mode.
		//

		CCS::OrbitalCameraMode* camMode13 = new CCS::OrbitalCameraMode(mCameraCS, 200);
        mCameraCS->registerCameraMode("Orbital (collidable)",camMode13);
		camMode13->setZoomFactor(100);
		camMode13->setRotationFactor(50);
		camMode13->setZoom(400);
		camMode13->setYaw(Radian(Degree(90)));
		camMode13->setCollisionsEnabled(true);
		// ** Uncomment for custom collisions calculation. By default the collisions are based on ogre basic raycast feature **
		//camMode13->collisionDelegate = CCS::CollidableCamera::newCollisionDelegate(this
		//	, &CameraControlSystemDemo::CustomCollisionDetectionFunction);
		

		// -------------------------------------------------------------------------------------
        // Register the custom "Dummy" camera mode defined previously. It basically goes forward
		// and backward constantly

        DummyCameraMode* camMode14 = new DummyCameraMode(mCameraCS, 400);
        mCameraCS->registerCameraMode("Dummy",(CCS::CameraControlSystem::CameraMode*)camMode14);

        // Set the camera target
        mCameraCS->setCameraTarget(headNode);

        mCameraCS->setCurrentCameraMode(camMode1);
    }

	void createTextArea()
	{
		// Create a panel
		Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
			OverlayManager::getSingleton().createOverlayElement("Panel", "CameraControlSystemParametersPanel"));
		panel->setMetricsMode(Ogre::GMM_PIXELS);
		panel->setPosition(10, 10);
		panel->setDimensions(400, 400);

		// Create a text area
		mTextArea = static_cast<Ogre::TextAreaOverlayElement*>(
			OverlayManager::getSingleton().createOverlayElement("TextArea", "CameraControlSystemParametersTextArea"));
		mTextArea->setMetricsMode(Ogre::GMM_PIXELS);
		mTextArea->setPosition(0, 0);
		mTextArea->setDimensions(100, 100);
		mTextArea->setCaption("CameraControlSystem demo");
		mTextArea->setCharHeight(20);
		mTextArea->setFontName("BlueHighway");
		mTextArea->setColourBottom(ColourValue(0.3, 0.5, 0.3));
		mTextArea->setColourTop(ColourValue(0.5, 0.7, 0.5));

		// Create an overlay, and add the panel
		Ogre::Overlay* overlay = OverlayManager::getSingleton().create("OverlayName");
		overlay->add2D(panel);

		// Add the text area to the panel
		panel->addChild(mTextArea);

		// Show the overlay
		overlay->show();
	}

	void destroyScene()
	{
		mCameraCS->deleteAllCameraModes();
	}

	Ogre::Vector3 CustomCollisionDetectionFunction(Ogre::Vector3 cameraTargetPosition, Ogre::Vector3 cameraPosition)
	{
		// Here you have to implement your custom collision code.
		// The returning value is the desired camera position.
		// In this method you usually have to calculate (using OgreNewt, NxOgre, OgreODE, OgreBullet... code)
		// the first intersection between the camera target and the camera (in this order).

		return cameraPosition;
	}
};

// ----------------------------------------------------------------------------
// Main function, just boots the application object
// ----------------------------------------------------------------------------
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main(int argc, char **argv)
#endif
{
	try
	{
		CameraControlSystemDemo app;
		app.go();
	}
	catch (Ogre::Exception &e)
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL );
#else
        std::cerr << "An exception has occured: " << e.getFullDescription();
#endif

		return -1;
	}

	return 0;
}
