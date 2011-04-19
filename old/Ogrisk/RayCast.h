#include "stdafx.h"

class RayCast
{
public:
	// bool RaycastFromPoint(const Vector3 & point, const Vector3 & normal, Vector3 & result);
	RayCast(Camera * camera, SceneManager * scmgr);
	void update();
	void SetPos(Vec3 * v);
protected:
	//void GetMeshInfo();
	MaterialPtr matptr;
	bool execute();
	Camera * cam;
	SceneNode * node;
	Ray ray_cam, ray_cursor;
	RaySceneQuery * RSQ;
	RaySceneQueryResult RSQR;
	//RSQR_iter_t rsqr_iter;
/***************************************************************************************/
// raycast functions
/***************************************************************************************/
	Ogre::Vector3
		closest_result,
		* result,
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
	Entity * ent_check;
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
