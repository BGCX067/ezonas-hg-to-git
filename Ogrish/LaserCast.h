#ifdef FUCKSHIT
#include "stdafx.h"
//#endif
class LaserCast:
	public Ogre :: Singleton <LaserCast>
{
public:
	// bool RaycastFromPoint(const Vector3 & point, const Vector3 & normal, Vector3 & result);
	void update();//float);
    //static LaserCast * sglt();
    static LaserCast * getSingletonPtr(void);
	static LaserCast * Instantiate();

protected:
	LaserCast();
	bool execute();
// necessary objects
	// MaterialPtr matptr;
	Ogre::Camera * cam;
	Ogre::SceneNode
		* n_root,
		* n_laserdot,
		* n_laserbeam;
		//* n_bullet;
	Ogre::Ray ray_cam;
	
	Ogre::RaySceneQuery * RSQ;
	Ogre::RaySceneQueryResult RSQR;
// tweakables
	float laser_width, * frame_time; //, bullet_speed, trace_width, trace_length;
	
//////////////////////////////////////
// Billboards ////////////////////////
//////////////////////////////////////
	Ogre::BillboardSet
		//* bb_bullet, // do that later
		* bb_dot;
	Ogre::Billboard * bboard;
	Ogre::BillboardChain
		* bb_beam;
		//* bb_bullet;

//////////////////////////////////////
// raycast function/ /////////////////
//////////////////////////////////////
	Ogre :: Vector3
		closest_result,
		camera,
		result,
		* vertices;
#define OPTIM
#ifdef OPTIM
	std::vector<Ogre :: Vector3> verts;
	std::vector<Ogre :: uint32> inds;
	size_t previous_vertex_count, previous_indice_count;
#endif
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
	Ogre::Entity * ent_check;
	Ogre::MeshPtr mesh_check;
	Ogre :: SubMesh* submesh;
	Ogre::IndexData * index_data;
	Ogre::HardwareIndexBufferSharedPtr ibuf;
	Ogre::HardwareVertexBufferSharedPtr vbuf;
	Ogre :: Vector3 position;
	Ogre :: Quaternion orient;
	Ogre :: Vector3 scale;
	Ogre :: VertexData* vertex_data;
	const Ogre :: VertexElement* posElem;
};
#endif