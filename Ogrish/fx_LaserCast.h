#include "stdafx.h"

struct LaserCast
{
public:
	// bool RaycastFromPoint(const Vector3 & point, const Vector3 & normal, Vector3 & result);
	void update();//float);

	LaserCast();
protected:
	bool execute();
// necessary objects
	// MaterialPtr matptr;
	Camera * cam;
	SceneNode
		* n_root,
		* n_laserdot,
		* n_laserbeam;
		//* n_bullet;
	Ray ray_cam;
	
	RaySceneQuery * RSQ;
	RaySceneQueryResult RSQR;
// tweakables
	float laser_width, & timeSinceLastFrame; //, bullet_speed, trace_width, trace_length;
	
// Billboards ////////////////////////
	BillboardSet * bb_dot;
	Billboard * bboard;
	BillboardChain * bb_beam;
// raycast function/ /////////////////
	Ogre :: Vector3
		closest_result,
		camera,
		result,
		* vertices;
	std::vector<Ogre :: Vector3> verts;
	std::vector<Ogre :: uint32> inds;
	size_t previous_vertex_count, previous_indice_count;
	Ogre :: uint32
		* indices,
		* hwBuf32;
	std::pair<bool, Ogre::Real> hit;
	float closest_distance;
	bool added_shared, use32bitindexes, new_closest_found, useSoftwareBlendingVertices;
	size_t
		vertex_count, index_count, index_start, last_index,
		current_offset,	shared_offset, next_offset, index_offset,
		offset,
		numTris;
		
//////////////////////////////////////
// other, late in getmeshinfo ////////
//////////////////////////////////////
	MeshPtr mesh_check;
	Ogre :: SubMesh* submesh;
	IndexData * index_data;
	HardwareIndexBufferSharedPtr ibuf;
	HardwareVertexBufferSharedPtr vbuf;
	Ogre :: Vector3 position;
	Ogre :: Quaternion orient;
	Ogre :: Vector3 scale;
	Ogre :: VertexData* vertex_data;
	const Ogre :: VertexElement* posElem;
};
