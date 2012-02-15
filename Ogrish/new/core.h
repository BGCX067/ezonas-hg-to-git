struct core:
	public Ogre :: Singleton <core>,
	public FrameListener,
	public KeyListener,
	public MouseListener

{
	// singleton and overloaded stuff
    static CameraController * getSingletonPtr(void);
	static CameraController * Instantiate();
	
	// FrameListener
	bool frameRenderingQueued(const FrameEvent & evt);
	bool frameStarted(const FrameEvent & evt);
	bool frameEnded(const FrameEvent & evt);
	
	// KeyListener, MouseListener
	bool mouseMoved(const OIS::MouseEvent &e);
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool keyPressed(const OIS::KeyEvent &e);
	bool keyReleased(const OIS::KeyEvent &e);
	
	
};
