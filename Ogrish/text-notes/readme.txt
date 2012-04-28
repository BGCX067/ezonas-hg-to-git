Zevil

This is a game I'm making, I'm mostly experimenting and features are missing

Controls:
	- F2/F3 to switch first person/3rd person camera
	- F1 to toggle console (no commands available yet)
	- WASD to move, mouse to turn, QE to ascend/descend
	- left click to shoot
	- '-' and '=' to adjust field of view
	
Libraries used:
Ogre3D ogre3d.org
Bullet physics bulletphysics.org
Gorilla GUI (2 tiny files to make some simple GUI and a console)

I want this game to feature both shooting and magical spells.

Some features:
 - Boxes turns white when close to each other (simple sphere collision). This will be used for spell distances and AI sight, but it was mainly to test bullet.
 - laser use a refactored function I found on the wiki to raycast at polygon level.
 - tracing bullets are simple billboards
 - office was modeled using sketchup and exported to the Ogre .mesh format
 - 3rd person camera system using scenenodes tree
 
Gameplay
 - I have coded a text-configurable, simple magic spell system, which can be applied to many targets (player or AI). I have not tested it yet.

Things left to do:
- level editor (doodads, procedural buildings with manual objects)
- Implement ENET networking library to do some networking P2P between 2 to 4 clients.
