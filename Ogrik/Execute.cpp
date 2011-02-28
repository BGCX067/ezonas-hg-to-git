#include "stdafx.h"

bool LaserCast :: execute()
{
	// execute the query, returns a vector of hits
	// LaserCast did not hit an objects bounding box:
	//if (RSQ == NULL) exit (0xdeadc0de);
	RSQ -> setRay(Ray(cam -> getDerivedPosition(), cam -> getDerivedDirection()));
	if (RSQ -> execute() . size() <= 0)
	{
		return false;
	}

	RSQR = RSQ -> getLastResults();
	closest_distance = -1.0f;
    for (size_t qr_idx = 0; qr_idx < RSQR.size(); qr_idx++)
    {
        // stop checking if we have found a LaserCast hit that is closer
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
/***************************************************************************************/			
/* from here i pasted the getmeshinfo method, to have maximum predeclared
attributes and minimum passed variables */
/***************************************************************************************/			
			added_shared = false;

			current_offset = shared_offset =
			next_offset = index_offset =
			vertex_count = index_count = 0;

			position = (ent_check -> getParentNode() -> _getDerivedPosition());
			orient = (ent_check -> getParentNode() -> _getDerivedOrientation());
			scale = (ent_check -> getParentNode() -> _getDerivedScale());
			mesh_check = ent_check -> getMesh();
			useSoftwareBlendingVertices = ent_check -> hasSkeleton();
			
			if (useSoftwareBlendingVertices)
				ent_check -> _updateAnimation();
			for (unsigned short i = 0; i < mesh_check -> getNumSubMeshes(); ++i)
			{
				submesh = mesh_check -> getSubMesh( i );

				// We only need to add the shared vertices once
				if(submesh -> useSharedVertices)
				{
					if(!added_shared)
					{
						vertex_count += mesh_check -> sharedVertexData -> vertexCount;
						added_shared = true;
					}
				}
				else
					vertex_count += submesh -> vertexData -> vertexCount;

				// Add the indices
				index_count += submesh -> indexData -> indexCount;
			}


			// Allocate space for the vertices and indices
			vertices = new Ogre :: Vector3[vertex_count];
			indices = new Ogre :: uint32[index_count];

			added_shared = false;

			// Run through the submeshes again, adding the data into the arrays
			for (unsigned short i = 0; i < mesh_check -> getNumSubMeshes(); ++i)
			{
				submesh = mesh_check -> getSubMesh(i);

				//----------------------------------------------------------------
				// GET VERTEXDATA
				//----------------------------------------------------------------
				//When there is animation:
				if(useSoftwareBlendingVertices)
					vertex_data =
					submesh -> useSharedVertices
						? ent_check -> _getSkelAnimVertexData()
						: ent_check -> getSubEntity(i) -> _getSkelAnimVertexData();
				else
					vertex_data = submesh -> useSharedVertices
						? mesh_check -> sharedVertexData
						: submesh -> vertexData;

				if
				(
					(!submesh -> useSharedVertices)
					||
					(submesh -> useSharedVertices && !added_shared)
				)
				{
					if(submesh -> useSharedVertices)
					{
						added_shared = true;
						shared_offset = current_offset;
					}

					// const Ogre :: VertexElement* posElem =
					posElem =
						vertex_data -> vertexDeclaration -> findElementBySemantic
															(Ogre :: VES_POSITION);

					vbuf =
						vertex_data -> vertexBufferBinding -> getBuffer(posElem -> getSource());

					unsigned char* vertex =
						static_cast<unsigned char*>
							(vbuf -> lock(Ogre :: HardwareBuffer :: HBL_READ_ONLY));

					// There is _no_ baseVertexPointerToElement() which takes an
					// Ogre :: Real or a double as second argument. So make it float,
					// to avoid trouble when Ogre :: Real will be comiled/typedefed
					//   as double: Ogre :: Real* pReal;
					float* pReal;

					for
					(
						size_t j = 0;
						j < vertex_data -> vertexCount;
						++j, vertex += vbuf -> getVertexSize()
					)
					{
						posElem -> baseVertexPointerToElement (vertex, &pReal);
						Ogre :: Vector3 pt (pReal[0], pReal[1], pReal[2]);
						vertices [current_offset + j] = (orient * (pt * scale)) + position;
					}

					vbuf -> unlock();
					next_offset += vertex_data -> vertexCount;
				}


				index_data = submesh -> indexData;
				numTris = index_data -> indexCount / 3;
				ibuf = index_data -> indexBuffer;

				use32bitindexes =
				(ibuf -> getType() == Ogre :: HardwareIndexBuffer :: IT_32BIT);

				void * hwBuf = ibuf -> lock(Ogre :: HardwareBuffer :: HBL_READ_ONLY);

				offset =
					(submesh -> useSharedVertices)
						? shared_offset
						: current_offset;
				
				index_start = index_data -> indexStart;
				last_index = numTris * 3 + index_start;

				if (use32bitindexes)
				{
					hwBuf32 = static_cast<Ogre :: uint32*>(hwBuf);
					for (size_t k = index_start; k < last_index; ++k)
						indices[index_offset++] =
							hwBuf32[k] + static_cast<Ogre :: uint32>(offset);
				}
				else
				{
					Ogre :: uint16* hwBuf16 = static_cast<Ogre :: uint16*>(hwBuf);
					for (size_t k = index_start; k < last_index; ++k)
						indices[ index_offset++ ] =
							static_cast<Ogre :: uint32>(hwBuf16[k]) +
							static_cast<Ogre :: uint32>(offset);
				}

				ibuf -> unlock();
				current_offset = next_offset;
			}

/***************************************************************************************/			
/* meshinfo method is supposed to end here */
/***************************************************************************************/			
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

            // if we found a new closest LaserCast for this object, update the
            // closest_result before moving on to the next object.
            if (new_closest_found)
                closest_result = ray_cam.getPoint(closest_distance - 1.0f);
        }
    }
    // return the result
    if (closest_distance >= 0.0f)
    {
        // LaserCast success
        result = closest_result;
		//matptr->setAmbient(0.5, 0.5, 0.5);
        return true;
    }
    else
		return false;

}
