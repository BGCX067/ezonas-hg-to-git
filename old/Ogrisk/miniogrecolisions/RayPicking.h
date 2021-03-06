#include "../stdafx.h"

class RayPick
{
public:
	// bool RaycastFromPoint(const Vector3 & point, const Vector3 & normal, Vector3 & result);
	RayPick(Camera * camera, SceneManager * scmgr, Entity * ent)
	{
		cam = camera;
		ray_cursor = Ray(camera -> getPosition(), camera -> getDirection());
		ray_cam = Ray(camera -> getPosition(), camera -> getDirection());
		RSQ = scmgr -> createRayQuery(ray_cam);
		node = scmgr -> createSceneNode("hitpoint");
		node -> attachObject(ent);
	}
	void Update()
	{
		ray_cam = Ray(cam -> getPosition(), cam -> getDirection());
		if(RayCast() == true)
			node -> setPosition(result);
	}



protected:
	void GetMeshInfo();
	bool RayCast();
	Camera * cam;
	Entity * ent_check;
	MeshPtr * mesh_check;
	SceneNode * node, * hit;
	Ray ray_cam, ray_cursor;
	RaySceneQuery * RSQ;
	RaySceneQueryResult RSQR;
	//RSQR_iter_t rsqr_iter;
/***************************************************************************************/			
// raycast functions
/***************************************************************************************/			
	Ogre::Vector3
		closest_result,
		result,
		* vertices;

	Ogre :: uint32
		* indices,
		* hwBuf32;
	std::pair<bool, Ogre::Real> hit;
	float closest_distance;
	bool added_shared, use32bitindexes, new_closest_found, useSoftwareBlendingVertices;
	size_t
		vertex_count, index_count, index_start, last_index,
		current_offset,	shared_offset, next_offset, index_offset, // meshinfo
		offset,
		numTris;
/***************************************************************************************/			
// other, late in getmeshinfo
/***************************************************************************************/			
	IndexData * index_data;
	HardwareIndexBufferSharedPtr ibuf;
	HardwareVertexBufferSharedPtr vbuf;
	const Ogre :: Vector3 position;
	const Ogre :: Quaternion orient;
	const Ogre :: Vector3 scale;
	Ogre :: SubMesh* submesh;
	Ogre :: VertexData* vertex_data;
	const Ogre :: VertexElement* posElem;
};
