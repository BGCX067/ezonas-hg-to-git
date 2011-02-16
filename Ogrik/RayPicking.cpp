#include "stdafx.h"

bool RayPick :: RayCast()
{

	// execute the query, returns a vector of hits
	// raycast did not hit an objects bounding box:
	if (RSQ -> execute() . size() <= 0) return (false);

	RSQR = RSQ -> getLastResults();

/////////////////////////////////////////////////////////////////////////////////////////
	closest_distance = -1.0f;
    for (size_t qr_idx = 0; qr_idx < RSQR.size(); qr_idx++)
    {
        // stop checking if we have found a raycast hit that is closer
        // than all remaining entities
        if
		(
			(closest_distance >= 0.0f) &&
            (closest_distance < RSQR[qr_idx].distance)
		)
			break;

        // only check this result if its a hit against an entity
        if ((RSQR[qr_idx].movable != NULL) &&
            (RSQR[qr_idx].movable -> getMovableType().compare("Entity") == 0))
        {
            // get the entity to check
            ent_check = static_cast<Ogre::Entity*>(RSQR[qr_idx].movable);

    /* */   // get the mesh information #########################################//
	/* */	GetMeshInfo                                                          //
	/* */	(                                                                    //
	/* */		ent_check,                                            //
	/* */		// vertex_count,                                                 //
	/* */		// vertices,                                                     //
	/* */		// index_count,                                                  //
	/* */		// indices,                                                      //
	/* */		ent_check -> getParentNode() -> _getDerivedPosition(),           //
	/* */		ent_check -> getParentNode() -> _getDerivedOrientation(),        //
	/* */		ent_check -> getParentNode() -> _getDerivedScale()               //
	/* */		//ent_check -> getParentNode() -> getWorldPosition(),            //
	/* */		//ent_check -> getParentNode() -> getWorldOrientation(),         //
	/* */		//ent_check -> getParentNode() -> _getDerivedScale()             //
	/* */	);                                                                   //
    /* */     // ################################################################//

            // test for hitting individual triangles on the mesh
            new_closest_found = false;
            for (int i = 0; i < static_cast<int>(index_count); i += 3)
            {
                // check for a hit against this triangle
				hit = Ogre :: Math :: intersects
				(
					ray_cam,
					vertices[indices[i]],
                    vertices[indices[i+1]],
					vertices[indices[i+2]],
					true, false
				);

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
                closest_result = ray_cam.getPoint(closest_distance - 1.0f);
        }
    }
    // return the result
    if (closest_distance >= 0.0f)
    {
        // raycast success
        result = closest_result ;
        return true;
    }
    else
	{
		
		return false;
	}

}
