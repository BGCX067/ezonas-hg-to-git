// raycast from a point in to the scene.
// returns success or failure.
// on success the point is returned in the result.
bool OgreVisionEngine::RaycastFromPoint(const Vector3 &point,
                                        const Vector3 &normal,
                                        Vector3 &result)
{
    // create the ray to test
    Ogre::Ray ray(Ogre::Vector3(point.x, point.y, point.z),
                  Ogre::Vector3(normal.x, normal.y, normal.z));
 
    // check we are initialised
    if (m_pray_scene_query != NULL)
    {
        // create a query object
        m_pray_scene_query->setRay(ray);
 
        // execute the query, returns a vector of hits
        if (m_pray_scene_query->execute().size() <= 0)
        {
            // raycast did not hit an objects bounding box
            return (false);
        }
    }
    else
    {
        LOG_ERROR << "Cannot raycast without RaySceneQuery instance" << ENDLOG;
        return (false);
    }   
 
    // at this point we have raycast to a series of different objects bounding boxes.
    // we need to test these different objects to see which is the first polygon hit.
    // there are some minor optimizations (distance based) that mean we wont have to
    // check all of the objects most of the time, but the worst case scenario is that
    // we need to test every triangle of every object.
    Ogre::Real closest_distance = -1.0f;
    Ogre::Vector3 closest_result;
    Ogre::RaySceneQueryResult &query_result = m_pray_scene_query->getLastResults();
    for (size_t qr_idx = 0; qr_idx < query_result.size(); qr_idx++)
    {
        // stop checking if we have found a raycast hit that is closer
        // than all remaining entities
        if ((closest_distance >= 0.0f) &&
            (closest_distance < query_result[qr_idx].distance))
        {
             break;
        }
 
        // only check this result if its a hit against an entity
        if ((query_result[qr_idx].movable != NULL) &&
            (query_result[qr_idx].movable->getMovableType().compare("Entity") == 0))
        {
            // get the entity to check
            Ogre::Entity *pentity = static_cast<Ogre::Entity*>(query_result[qr_idx].movable);           
 
            // mesh data to retrieve         
            size_t vertex_count;
            size_t index_count;
            Ogre::Vector3 *vertices;
            unsigned long *indices;
 
            // get the mesh information
         OgreVE::GetMeshInformation(pentity->getMesh(), vertex_count, vertices, index_count, indices,             
                              pentity->getParentNode()->getWorldPosition(),
                              pentity->getParentNode()->getWorldOrientation(),
                              pentity->getParentNode()->_getDerivedScale());
 
            // test for hitting individual triangles on the mesh
            bool new_closest_found = false;
            for (int i = 0; i < static_cast<int>(index_count); i += 3)
            {
                // check for a hit against this triangle
                std::pair<bool, Ogre::Real> hit = Ogre::Math::intersects(ray, vertices[indices[i]],
                    vertices[indices[i+1]], vertices[indices[i+2]], true, false);
 
                // if it was a hit check if its the closest
                if (hit.first)
                {
                    if ((closest_distance < 0.0f) ||
                        (hit.second < closest_distance))
                    {
                        // this is the closest so far, save it off
                        closest_distance = hit.second;
                        new_closest_found = true;
                    }
                }
            }
 
         // free the verticies and indicies memory
            delete[] vertices;
            delete[] indices;
 
            // if we found a new closest raycast for this object, update the
            // closest_result before moving on to the next object.
            if (new_closest_found)
            {
                closest_result = ray.getPoint(closest_distance);               
            }
        }       
    }
 
    // return the result
    
	if (closest_distance >= 0.0f)
    {
        // raycast success
        result = closest_result;
        return (true);
    }
    else
    {
        // raycast failed
        return (false);
    } 
}