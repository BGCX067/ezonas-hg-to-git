class RayPick
{
public:
	GetMeshInformation();
	RaycastFromPoint();
	RayPick(Camera * camera, SceneManager * scmgr)
	{
		cursor_ray = Ray(camera -> getPosition(), camera -> getDirection());
		scmgr -> createRayQuery(cursor_ray);
	}
protected:
	Entity * ent, * ent_check;
	Ray cursor_ray;
	RaySceneQuery * RSQ;
	RaySceneQueryResult RSQR;
	RSQR_iter_t rsqr_iter;
// raycast function
	Ogre::Vector3
		closest_result,
		* vertices;
	
	size_t
		vertex_count,
		index_count;
	
	Ogre :: uint32 * indices;
	std::pair<bool, Ogre::Real> hit;

	bool added_shared, use32bitindexes;
	size_t
		current_offset,
		shared_offset,
		next_offset,
		index_offset,
		numTris,
		
		
		offset,
		index_start,
		last_index;
// other, late in getmeshinfo
	IndexData * index_data;
	HardwareIndexBufferSharedPtr ibuf;
	Ogre :: uint32* hwBuf32;
	
};