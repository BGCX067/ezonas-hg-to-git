#include "../stdafx.h"

void RayPick :: GetMeshInfo
(
	Entity *entity,
	const Ogre :: Vector3 & position,
	const Ogre :: Quaternion & orient,
	const Ogre :: Vector3 & scale
)
{
	bool added_shared = false;

	current_offset =
	shared_offset =
	next_offset =
	index_offset =
	vertex_count =
	index_count =
	0;

	Ogre :: MeshPtr mesh = entity->getMesh();

	useSoftwareBlendingVertices = entity->hasSkeleton();

	if (useSoftwareBlendingVertices)
		entity->_updateAnimation();

	// Calculate how many vertices and indices we're going to need
	for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
	{
		Ogre :: SubMesh* submesh = mesh->getSubMesh( i );

		// We only need to add the shared vertices once
		if(submesh->useSharedVertices)
		{
			if(!added_shared)
			{
				vertex_count += mesh->sharedVertexData->vertexCount;
				added_shared = true;
			}
		}
		else
			vertex_count += submesh->vertexData->vertexCount;

		// Add the indices
		index_count += submesh->indexData->indexCount;
	}


	// Allocate space for the vertices and indices
	vertices = new Ogre :: Vector3[vertex_count];
	indices = new Ogre :: uint32[index_count];

	added_shared = false;

	// Run through the submeshes again, adding the data into the arrays
	for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
	{
		Ogre :: SubMesh* submesh = mesh->getSubMesh(i);

		//----------------------------------------------------------------
		// GET VERTEXDATA
		//----------------------------------------------------------------
		Ogre :: VertexData* vertex_data;

		//When there is animation:
		if(useSoftwareBlendingVertices)
			vertex_data =
			submesh->useSharedVertices
				? entity->_getSkelAnimVertexData()
				: entity->getSubEntity(i)->_getSkelAnimVertexData();
		else
			vertex_data = submesh->useSharedVertices
				? mesh->sharedVertexData
				: submesh->vertexData;


		if((!submesh->useSharedVertices) || (submesh->useSharedVertices && !added_shared))
		{
			if(submesh->useSharedVertices)
			{
				added_shared = true;
				shared_offset = current_offset;
			}

			const Ogre :: VertexElement* posElem =
				vertex_data->vertexDeclaration->findElementBySemantic(Ogre :: VES_POSITION);

			Ogre :: HardwareVertexBufferSharedPtr vbuf =
				vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());

			unsigned char* vertex =
				static_cast<unsigned char*>
					(vbuf->lock(Ogre :: HardwareBuffer :: HBL_READ_ONLY));

			// There is _no_ baseVertexPointerToElement() which takes an Ogre :: Real or a double
			//  as second argument. So make it float, to avoid trouble when Ogre :: Real will
			//  be comiled/typedefed as double:
			//      Ogre :: Real* pReal;
			float* pReal;

			for
			(
				size_t j = 0;
				j < vertex_data->vertexCount;
				++j, vertex += vbuf->getVertexSize()
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

		void* hwBuf = ibuf->lock(Ogre :: HardwareBuffer :: HBL_READ_ONLY);

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
				indices[ index_offset++ ] = static_cast<Ogre :: uint32>(hwBuf16[k]) +
					static_cast<Ogre :: uint32>(offset);
		}

		ibuf->unlock();
		current_offset = next_offset;
	}
}
