#include "stdafx.h"

class RayPick
{
public:
	// bool RaycastFromPoint(const Vector3 & point, const Vector3 & normal, Vector3 & result);
	RayPick(Camera * camera, SceneManager * scmgr, SceneNode * scnode)
	{
		cam = camera;
		root = scmgr -> getRootSceneNode();
		ray_cursor = Ray(camera -> getPosition(), camera -> getDirection());
		ray_cam = Ray(camera -> getPosition(), camera -> getDirection());
		RSQ = scmgr -> createRayQuery(ray_cam);
		node = scnode;
	}
	void Update()
	{
		ray_cam = Ray(cam -> getPosition(), cam -> getDirection());
		if(RayCast() == true)
		{
			root -> addChild(node);
			node -> setPosition(result);
		}
		else
		{
			root -> removeChild (node);
		}
			
		//cout << result.x << " " << result.y << " " << result.y << "\n";
	}
	void SetNode(SceneNode * n) {node = n;}


protected:
	void GetMeshInfo
	(
		Entity *entity,
		const Ogre :: Vector3 & position,
		const Ogre :: Quaternion & orient,
		const Ogre :: Vector3 & scale
	);
	bool RayCast();
	Camera * cam;
	Entity * ent_check;
	SceneNode * node;
	SceneNode * root;
	Ray ray_cam, ray_cursor;
	RaySceneQuery * RSQ;
	RaySceneQueryResult RSQR;
	//RSQR_iter_t rsqr_iter;
// raycast functions
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
// other, late in getmeshinfo
	IndexData * index_data;
	HardwareIndexBufferSharedPtr ibuf;

};
