// Contact Information

// The best way to determine if collisions happened between existing objects in the world, is to iterate over all contact manifolds. This should be done during a simulation tick (substep) callback, because contacts might be added and removed during several substeps of a single stepSimulation call.
// A contact manifold is a cache that contains all contact points between pairs of collision objects. A good way is to iterate over all pairs of objects in the entire collision/dynamics world:

	//Assume world->stepSimulation or world->performDiscreteCollisionDetection has been called

	int numManifolds = world->getDispatcher()->getNumManifolds();
	for (int i=0;i<numManifolds;i++)
	{
		btPersistentManifold* contactManifold =  world->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());
	
		int numContacts = contactManifold->getNumContacts();
		for (int j=0;j<numContacts;j++)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance()<0.f)
			{
				const btVector3& ptA = pt.getPositionWorldOnA();
				const btVector3& ptB = pt.getPositionWorldOnB();
				const btVector3& normalOnB = pt.m_normalWorldOnB;
			}
		}
	}
// See Bullet/Demos/CollisionInterfaceDemo for a sample implementation.
// btGhostObject

// A more efficient way is to iterate only over the pairs of objects that you are interested in. This can be done using a btGhostObject. A btGhostObject keeps track of its own overlapping pairs:
      btManifoldArray   manifoldArray;
      btBroadphasePairArray& pairArray = ghostObject->getOverlappingPairCache()->getOverlappingPairArray();
      int numPairs = pairArray.size();

      for (int i=0;i<numPairs;i++)
      {
         manifoldArray.clear();

         const btBroadphasePair& pair = pairArray[i];
         
         //unless we manually perform collision detection on this pair, the contacts are in the dynamics world paircache:
         btBroadphasePair* collisionPair = dynamicsWorld->getPairCache()->findPair(pair.m_pProxy0,pair.m_pProxy1);
         if (!collisionPair)
            continue;

         if (collisionPair->m_algorithm)
            collisionPair->m_algorithm->getAllContactManifolds(manifoldArray);

         for (int j=0;j<manifoldArray.size();j++)
         {
            btPersistentManifold* manifold = manifoldArray[j];
            btScalar directionSign = manifold->getBody0() == m_ghostObject ? btScalar(-1.0) : btScalar(1.0);
            for (int p=0;p<manifold->getNumContacts();p++)
            {
             	const btManifoldPoint&pt = manifold->getContactPoint(p);
                if (pt.getDistance()<0.f)
		{
			const btVector3& ptA = pt.getPositionWorldOnA();
			const btVector3& ptB = pt.getPositionWorldOnB();
			const btVector3& normalOnB = pt.m_normalWorldOnB;
			/// work here
		}
            }
         }
      }
// You have to add once some special callback to world to make the ghosts work.
btDiscreteDynamicsWorld* dynamicsWorld = CreateDiscreteDynamicsWorld(); // Assume the world is now initializing...
ghostPairCallback = new btGhostPairCallback();
dynamicsWorld->getPairCache()->setInternalGhostPairCallback(ghostPairCallback);
// See Bullet\Demos\CharacterDemo\CharacterDemo.cpp and src\BulletDynamics\Character\btKinematicCharacterController.cpp (btKinematicCharacterController::recoverFromPenetration) for a sample implementation.
// contactTest

// Bullet 2.76 onwards let you perform an instant query on the world (btCollisionWorld or btDiscreteDynamicsWorld) using the contactTest query. The contactTest query will peform a collision test against all overlapping objects in the world, and produces the results using a callback. The query object doesn't need to be part of the world. In order for an efficient query on large worlds, it is important that the broadphase aabbTest is accelerated, for example using the btDbvtBroadphase or btAxisSweep3 broadphase.
// An advantage of this method is that you can perform collision tests at a reduced temporal resolution if you do not need collision tests at every physics tic. It is also convenient to use with a pre-existing object in the world, whereas btGhostObject would require synchronizing with the target object. However, a downside is that collision detection is being duplicated for the target object (if it already exists in the world), so frequent or widespread collision tests may become less efficient than iterating over previously generated collision pairs.
// Usage example:
struct ContactSensorCallback : public btCollisionWorld::ContactResultCallback {
	
	//! Constructor, pass whatever context you want to have available when processing contacts
	/*! You may also want to set m_collisionFilterGroup and m_collisionFilterMask
	 *  (supplied by the superclass) for needsCollision() */
	ContactSensorCallback(btRigidBody& tgtBody , YourContext& context /*, ... */)
		: btCollisionWorld::ContactResultCallback(), body(tgtBody), ctxt(context) { }
	
	btRigidBody& body; //!< The body the sensor is monitoring
	YourContext& ctxt; //!< External information for contact processing
	
	//! If you don't want to consider collisions where the bodies are joined by a constraint, override needsCollision:
	/*! However, if you use a btCollisionObject for #body instead of a btRigidBody,
	 *  then this is unnecessary—checkCollideWithOverride isn't available */
	virtual bool needsCollision(btBroadphaseProxy* proxy) const {
		// superclass will check m_collisionFilterGroup and m_collisionFilterMask
		if(!btCollisionWorld::ContactResultCallback::needsCollision(proxy))
			return false;
		// if passed filters, may also want to avoid contacts between constraints
		return body.checkCollideWithOverride(static_cast<btCollisionObject*>(proxy->m_clientObject));
	}
	
	//! Called with each contact for your own processing (e.g. test if contacts fall in within sensor parameters)
	virtual btScalar addSingleResult(btManifoldPoint& cp,
		const btCollisionObject* colObj0,int partId0,int index0,
		const btCollisionObject* colObj1,int partId1,int index1)
	{
		btVector3 pt; // will be set to point of collision relative to body
		if(colObj0==&body) {
			pt = cp.m_localPointA;
		} else {
			assert(colObj1==&body && "body does not match either collision object");
			pt = cp.m_localPointB;
		}
		// do stuff with the collision point
		return 0; // not actually sure if return value is used for anything...?
	}
};

// USAGE:
btRigidBody* tgtBody /* = ... */;
YourContext foo;
ContactSensorCallback callback(*tgtBody, foo);
world->contactTest(tgtBody,callback);
// contactPairTest

// Bullet 2.76 onwards provides the contactPairTest to perform collision detection between two specific collision objects only. Contact results are passed on using the provided callback. They don't need to be inserted in the world. See btCollisionWorld::contactPairTest in Bullet/src/BulletCollision/CollisionDispatch/btCollisionWorld.h for implementation details.
// Contact Callbacks

// Be careful when using contact callbacks. They might be called too frequent for your purpose. Bullet supports custom callbacks at various points in the collision system. The callbacks themselves are very simply implemented as global variables that you set to point at appropriate functions. Before you can expect them to be called you must set an appropriate flag in your rigid body:
mBody->setCollisionFlags(mBody->getCollisionFlags() |
    btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
// There are three collision callbacks:
// gContactAddedCallback

// This is called whenever a contact is added. From here, you can modify some properties [eg friction] of the contact point
typedef bool (*ContactAddedCallback)(
    btManifoldPoint& cp,
    const btCollisionObject* colObj0,
    int partId0,
    int index0,
    const btCollisionObject* colObj1,
    int partId1,
    int index1);
// If your function returns false, then Bullet will assume that you did not modify the contact point properties at all.
// gContactProcessedCallback

// This is called immediately after the collision has been actually processed
typedef bool (*ContactProcessedCallback)(
    btManifoldPoint& cp,
    void* body0,void* body1);
// gContactDestroyedCallback

// This is called immediately after the contact point is destroyed.
typedef bool (*ContactDestroyedCallback)(
    void* userPersistentData);
// Trigger

// Collision objects with a callback still have collision response with dynamic rigid bodies. In order to use collision objects as trigger, you have to disable the collision response.
mBody->setCollisionFlags(mBody->getCollisionFlags() |
    btCollisionObject::CF_NO_CONTACT_RESPONSE));