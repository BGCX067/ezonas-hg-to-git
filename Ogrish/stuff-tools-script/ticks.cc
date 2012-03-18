// Intro

// Every time that Bullet does a complete internal tick, it has the ability to call a callback of your choosing. This callback can happen before the simulation step or at the end of the simulation step. Such callback is useful to notify other parts of your application about the simulation or to modify velocities of bodies, for example, if you are building a spaceship and you want each spaceship to have an individual speed cap. No matter how many substeps Bullet will do, your spaceship can have its speed limited at the end of every tick, which helps framerate independance.
// The prototype function for the callback is this:
typedef void (*btInternalTickCallback)(btDynamicsWorld *world, btScalar timeStep);
// and the appropriate call to add it to the world is
void btDynamicsWorld::setInternalTickCallback(btInternalTickCallback cb, void* worldUserInfo=0,bool isPreTick=false);
// Simple example using the Simulation Tick Callbacks

// Your code to use it in its simplest form might look something like this:
void myTickCallback(btDynamicsWorld *world, btScalar timeStep) {
    printf("The world just ticked by %f seconds\n", (float)timeStep);
}

// And then somewhere after you construct the world:

mWorld->setInternalTickCallback(myTickCallback);
// Other example using the Simulation Tick Callbacks

// If you want to enjoy worldUserInfo, then you can call world->getWorldUserInfo() from inside the callback. Typically you'll use this if you have your own world object that contains the Bullet world via aggregation or composition. Pass static_cast<void *>(this) as the second parameter to setInternalTickCallback, and static_cast it back again inside your function.
// Your slightly more complex code to use the callbacks as described with your own world object will look like this:
static void myTickCallback(btDynamicsWorld *world, btScalar timeStep);

class MyPhysicsWorld
{
public:
    MyPhysicsWorld()
	{ mWorld->setInternalTickCallback(myTickCallback, static_cast<void *>(this));}

    void myProcessCallback(btScalar timeStep)
	{ printf("It's like a clock inside my head: %i\n", timeStep); }

protected:
    btDynamicsWorld *mWorld;
};

void myTickCallback(btDynamicsWorld *world, btScalar timeStep)
{
    MyPhysicsWorld *w = static_cast<MyPhysicsWorld *>(world->getWorldUserInfo());
    w->myProcessCallback(timeStep);
}
// More complex example using the Simulation Tick Callbacks

// If you want to specify forces on bodies inside the callback you should
// activate the pre-tick call of the callback function by passing true as third argument of setInternalTickCallback. (The reason for this is that Bullet will clear all forces after the usual (post-tick) call.)
// inside the callback function you should first clear all forces with clearForces (The reason is that Bullet might or might not have cleared forces and applied gravity. Clearing it again ensures that we are always in the same situation.)
// and then apply all forces using applyForce (and applyGravity if needed) on each body
// For rigid bodies the code would look something like this:
static void myTickCallback(btDynamicsWorld *world, btScalar timeStep);

class MyPhysicsWorld {
public:
    MyPhysicsWorld() {
          mWorld->setInternalTickCallback(myTickCallback, static_cast<void *>(this), true);
    }

     void myProcessCallback(btScalar timeStep) {
          btCollisionObjectArray objects = mWorld->getCollisionObjectArray();
          mWorld->clearForces();
          for (int i = 0; i < objects.size(); i++) {
               btRigidBody *rigidBody = btRigidBody::upcast(objects[i]);
               if (!rigidBody) {
                    continue;
               }
               rigidBody->applyGravity();
               rigidBody->applyForce(btVector3(-10., 0., 0.), btVector3(0., 0., 0.));
          }
          return;
     }

protected:
    btDynamicsWorld *mWorld;
};

void myTickCallback(btDynamicsWorld *world, btScalar timeStep) {
    MyPhysicsWorld *w = static_cast<MyPhysicsWorld *>(world->getWorldUserInfo());
    w->myProcessCallback(timeStep);
}
// Pre-tick callback example

// Sometimes it is useful to have a callback at the start of the simulation. In this case, use isPreTick = true as last argument to setInternalTickCallback.
// See for example the Bullet\Demos\DynamicControlDemo\MotorDemo.cpp
// page discussion view source history
// Log in
// navigation
// News
// Forum
// Downloads
// Wiki
// Recent changes
// Random page
// sitesupport
// search
    
// toolbox
// What links here
// Related changes
// Special pages
// Printable version
// Permanent link

