struct ContactSensorCallback : public btCollisionWorld::ContactResultCallback {
	
	//  Constructor, pass whatever context you want to have available when processing contacts
	/*  You may also want to set m_collisionFilterGroup and m_collisionFilterMask
	 *  (supplied by the superclass) for needsCollision() */
	ContactSensorCallback(btRigidBody& tgtBody , YourContext& context /*, ... */)
		: btCollisionWorld::ContactResultCallback(), body(tgtBody), ctxt(context) { }
	
	btRigidBody& body; // < The body the sensor is monitoring
	YourContext& ctxt; // < External information for contact processing
	
	//  If you don't want to consider collisions where the bodies are joined by a constraint, override needsCollision:
	/*  However, if you use a btCollisionObject for #body instead of a btRigidBody,
	 *  then this is unnecessaryŚcheckCollideWithOverride isn't available */
	virtual bool needsCollision(btBroadphaseProxy* proxy) const {
		// superclass will check m_collisionFilterGroup and m_collisionFilterMask
		if(!btCollisionWorld::ContactResultCallback::needsCollision(proxy))
			return false;
		// if passed filters, may also want to avoid contacts between constraints
		return body.checkCollideWithOverride(static_cast<btCollisionObject*>(proxy->m_clientObject));
	}
	
	//  Called with each contact for your own processing (e.g. test if contacts fall in within sensor parameters)
	virtual btScalar addSingleResult(btManifoldPoint& cp,
		const btCollisionObject* colObj0,int partId0,int index0,
		const btCollisionObject* colObj1,int partId1,int index1)
	{
		btVector3 pt; // will be set to point of collision relative to body
		if(colObj0==&body)
			pt = cp.m_localPointA;
		else
		{
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