#include "Tubes.h"

#include <OgreManualObject.h>
#include <OgreMaterialManager.h>
#include <OgreSceneManager.h>
#include <OgreStringConverter.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include <OgreHardwareVertexBuffer.h>
#include <OgreHardwareIndexBuffer.h>
#include <OgreSubMesh.h>


using namespace Ogre;


namespace Ogre
{



   SeriesOfTubes::SeriesOfTubes( 
      Ogre::SceneManager* sceneMgr, 
      const Ogre::uint numberOfSides /*= 0*/, 
      const Ogre::Real radius /*= 0.0*/)
      : mSceneMgr(sceneMgr),
      mSideCount(numberOfSides),
      mRadius(radius), 
      mTubeObject(0),
      mUniqueMaterial(false),            
      mSceneNode(0)
   {

   }

   SeriesOfTubes::~SeriesOfTubes()
   {
      _destroy();
   }

   void SeriesOfTubes::addPoint( const Ogre::Vector3& pos )
   {
      mLineVertices.push_back(pos);
   }

   void SeriesOfTubes::removePoint( const Ogre::uint pointNumber )
   {
      if (pointNumber < mLineVertices.size())
      {
         VVec::iterator it = mLineVertices.begin() + pointNumber;
         mLineVertices.erase(it);
      }
   }

   Ogre::ManualObject* SeriesOfTubes::createTubes( 
      const Ogre::String& name, 
      const Ogre::String& materialName, 
      bool uniqueMaterial /* = false*/,
      bool isDynamic /*= false*/,
      bool disableUVs /*= false*/, 
      bool disableNormals /*= false*/)
   {
      if (mTubeObject)
         return mTubeObject;

      mMaterial = MaterialManager::getSingleton().getByName(materialName);

      mUniqueMaterial = uniqueMaterial;

      if (mUniqueMaterial)
         mMaterial = mMaterial->clone(materialName + "_" + name);
              

      mTubeObject = mSceneMgr->createManualObject(name);

      mTubeObject->setDynamic(isDynamic);

      _update(disableUVs,disableNormals);

      if (mSceneNode)
         mSceneNode->attachObject(mTubeObject);


      return mTubeObject;

      
   }

   void SeriesOfTubes::_update(bool disableUVs /*= false*/, bool disableNormals /*= false*/)
   {
      if (mTubeObject == 0 || mLineVertices.size() < 2)
         return;

      if (mTubeObject->getDynamic() == true && mTubeObject->getNumSections() > 0)
         mTubeObject->beginUpdate(0);
      else
         mTubeObject->begin(mMaterial->getName());


      Quaternion qRotation(Degree(360.0/(Real)mSideCount),Vector3::UNIT_Z);

      const uint iVertCount = mSideCount + 1;      

      Vector3* vCoreVerts = new Vector3[iVertCount];
      Vector3 vPos = Vector3::UNIT_X * mRadius;      
      

      for (int i=0;i<iVertCount;i++)
      {
         vCoreVerts[i] = vPos;
         vPos = qRotation * vPos;
      }


      Vector3 vLineVertA, vLineVertB;
      Vector3 vLine;
      Real dDistance;
      int A,B,C,D;
      int iOffset;

      Vector3* vCylinderVerts = new Vector3[iVertCount * 2];
      
      for (int i=1;i<mLineVertices.size();i++)
      {
         vLineVertA = mLineVertices[i-1];
         vLineVertB = mLineVertices[i];

         vLine = vLineVertB - vLineVertA;
         dDistance = vLine.normalise();

         qRotation = Vector3::UNIT_Z.getRotationTo(vLine);         

         for (int j=0;j<iVertCount;j++)
         {
            vCylinderVerts[j] = (qRotation * vCoreVerts[j]);
            vCylinderVerts[j + iVertCount] = (qRotation * (vCoreVerts[j] + (Vector3::UNIT_Z * dDistance)));                        
         }

         Real u,v,delta;
         delta = 1.0 / (Real)(iVertCount-1);
         u = 0.0;
         v = 1.0;
         
         for (int j=0;j<(iVertCount*2);j++)
         {
            mTubeObject->position(vCylinderVerts[j] + vLineVertA);
            if (disableNormals == false)
            {
               mTubeObject->normal(vCylinderVerts[j].normalisedCopy());
            }
            if (disableUVs == false)
            {
               if (j == iVertCount){
                  u = 0.0;
                  v = 0.0;
               }
               mTubeObject->textureCoord(u,v);
               u += delta;
            }
         }

         iOffset = (i-1) * (iVertCount*2);
         for (int j=0;j<iVertCount;j++)
         {
            // End A: 0-(Sides-1)
            // End B: Sides-(Sides*2-1)                        
            A = ((j+1) % iVertCount);
            B = j;
            C = A + iVertCount;
            D = B + iVertCount;

            A += iOffset;
            B += iOffset;
            C += iOffset;
            D += iOffset;


            // Tri #1
            // C,B,A

            mTubeObject->triangle(C,B,A);

            // Tri #2
            // C,D,B

            mTubeObject->triangle(C,D,B);

         }
      }

      delete[] vCoreVerts;
      delete[] vCylinderVerts;
      vCoreVerts = 0;
      vCylinderVerts = 0;      

      if (mSceneNode)
         mSceneNode->removeAndDestroyAllChildren();
      

      Entity* pEnt = 0;
      SceneNode* pChildNode = 0;
      VVec::iterator it = mLineVertices.begin()+1;
      for (int i=1; it != (mLineVertices.end()-1);++it,i++)
      {
         if (mSpheresJoints.size() < i)
         {
            pEnt = mSceneMgr->createEntity(mTubeObject->getName() + "_SphereEnt" + StringConverter::toString(i),mSphereMesh->getName());
            pEnt->setMaterialName(mMaterial->getName());
            mSpheresJoints.push_back(pEnt);
         }
         else
         {
            pEnt = mSpheresJoints[i-1];
         }
         pEnt->setRenderingDistance(mSphereMaxVisDistance);
            
         if (mSceneNode)
         {
            pChildNode = mSceneNode->createChildSceneNode();
            pChildNode->setPosition((*it));            
            pChildNode->attachObject(pEnt);
         }
      }


        mTubeObject->end();



   }

   void SeriesOfTubes::_destroy()
   {
      if (mTubeObject)
      {
         if (mTubeObject->getParentSceneNode())
            mTubeObject->getParentSceneNode()->detachObject(mTubeObject);


         mSceneMgr->destroyManualObject(mTubeObject);
      }

      

      if (mUniqueMaterial)
      {
         MaterialManager::getSingleton().remove(mMaterial->getName());
      }
      mMaterial.setNull();

      if (mSpheresJoints.size() > 0)
      {
         Entity* pEnt = 0;
         SphereStorage::iterator it = mSpheresJoints.begin();
         for (; it != mSpheresJoints.end(); ++it)
         {
            pEnt = (*it);
            pEnt->getParentSceneNode()->detachObject(pEnt);
            mSceneMgr->destroyEntity(pEnt);
         }
      }

      if (mSphereMesh.isNull() == false)
      {
         MeshManager::getSingleton().remove(mSphereMesh->getName());
         mSphereMesh.setNull();
      }

      if (mSceneNode)
      {
         mSceneNode->removeAndDestroyAllChildren();
         mSceneNode->getParentSceneNode()->removeAndDestroyChild(mSceneNode->getName());
         mSceneNode = 0;
      }

   }   
}