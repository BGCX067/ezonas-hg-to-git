// Belette.cpp�: d�finit le point d'entr�e pour l'application console.
#include "stdafx.h"
//int _tmain(int argc, _TCHAR* argv[])
int main ()
{
    std::cout << "Hello World!" << std::endl;
 
    // Build the broadphase
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
 
    // Set up the collision configuration and dispatcher
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
 
    // The actual physics solver
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
 
    // The world.
    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-10,0));
 
    // Do_everything_else_here
 
 
    // Clean up behind ourselves like good little programmers
    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
 
    return 0;
}