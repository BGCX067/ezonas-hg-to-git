#include "stdafx.h"
void Application :: update_physics()
{
	// mirror Node position with collision objects
	size_t sz = Nodes.size();
	//assert(colw->getCollisionObjectArray().size() == Nodes.size());
	for(size_t i = 0; i < sz; ++ i)
	{
		colw->getCollisionObjectArray()[i]-> getWorldTransform()
				.setOrigin(BtOgre::Convert::toBullet(Nodes[i]->_getDerivedPosition()));
		Nodes[i]->showBoundingBox(false);
	}
	colw->debugDrawWorld();
	col_dgb->step();

	// perform collision detection and retrieve collision results
	colw->performDiscreteCollisionDetection();
	/*size_t num = dispatcher->getNumManifolds();
	for(size_t i = 0; i < num; ++i)
	{
		btPersistentManifold* contactManifold = 
			colw -> getDispatcher() -> getManifoldByIndexInternal(i);

		static_cast<SceneNode*>
			(static_cast<btCollisionObject*>
				(contactManifold -> getBody0())
					-> getUserPointer())
						-> showBoundingBox(true);
		static_cast<SceneNode*>
			(static_cast<btCollisionObject*>
				(contactManifold -> getBody1())
					-> getUserPointer())
						-> showBoundingBox(true);

	}*/

}
