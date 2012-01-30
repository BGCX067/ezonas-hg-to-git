#ifdef PHYSICS
    // Build the broadphase
    btBroadphaseInterface* broadphase;// = new btDbvtBroadphase();
    // Set up the collision configuration and dispatcher
    btDefaultCollisionConfiguration* collisionConfiguration;// = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher;// = new btCollisionDispatcher(collisionConfiguration);
    // The actual physics solver
    //btSequentialImpulseConstraintSolver* solver;// = new btSequentialImpulseConstraintSolver;
    // The world.
    //btDiscreteDynamicsWorld* dynamicsWorld;// = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
	btCollisionWorld * collisionWorld;// = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
#endif
