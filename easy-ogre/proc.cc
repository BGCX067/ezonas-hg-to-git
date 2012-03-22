/*
	void putMesh3(const std::string& meshName, const Vector3& position)
	{ putMeshMat(meshName, "derp", position, false); }
	void putMesh2(const std::string& meshName, const Vector3& position)
	{ putMeshMat(meshName, "derp", position, false); }
	void putMesh(const std::string& meshName, const Vector3& position)
	{ putMeshMat(meshName, "derp", position, true); }
	void putMeshMat(const std::string& meshName, const std::string& matName,
		const Vector3& position, bool castShadows)
	{
		Entity* ent2 = scmgr->createEntity(meshName);
		SceneNode* sn = scmgr->getRootSceneNode()->createChildSceneNode();
		sn->attachObject(ent2);
		sn->setPosition(position);
		ent2->setMaterialName(matName);
		ent2->setCastShadows(castShadows);
	}
	void putmesh(string s, Vec3 pos)
	{
		NODE(s)->attachObject(ENTITY(s, s));
		scmgr->getSceneNode(s)->setPosition(pos);
		scmgr->getEntity(s)->setMaterialName("derp");	
	}
	void init_other()
	{
		// -- Ground plane
		Procedural::PlaneGenerator().setNumSegX(20).setNumSegY(20).setSizeX(150).setSizeY(150).setUTile(5.0).setVTile(5.0).realizeMesh("planeMesh");
		putMesh2("planeMesh", Vec3(0,0,0));

		// -- Road
		// The path of the road, generated from a simple spline
		Procedural::Path p = Procedural::CatmullRomSpline3().setNumSeg(8).addPoint(0,0,0).addPoint(0,0,10).addPoint(10,0,10).addPoint(20,0,0).close().realizePath().scale(2);
		// The shape that will be extruded along the path
		Procedural::Shape s = Procedural::Shape().addPoint(-1.2f,.2f).addPoint(-1.f,.2f).addPoint(-.9f,.1f).addPoint(.9f,.1f).addPoint(1.f,.2f).addPoint(1.2f,.2f).scale(2).setOutSide(Procedural::SIDE_LEFT);
		// This is an example use of a shape texture track, 
		// which specifies how texture coordinates should be mapped relative to the shape points
		Procedural::Track textureTrack = Procedural::Track(Procedural::Track::AM_POINT).addKeyFrame(0,0).addKeyFrame(2,.2).addKeyFrame(3,.8).addKeyFrame(5,1);
		// The extruder actually creates the road mesh from all parameters
		Procedural::Extruder().setExtrusionPath(&p).setShapeToExtrude(&s).setShapeTextureTrack(&textureTrack).setUTile(20.).realizeMesh("extrudedMesh");
		putMesh3("extrudedMesh", Vec3(0,0,0));

		// -- Pillar
		// The path of the pillar, just a straight line
		Procedural::Path pillarBodyPath = Procedural::LinePath().betweenPoints(Vector3(0,0,0), Vector3(0,5,0)).realizePath();
		// We're doing something custom for the shape to extrude
		Procedural::Shape pillarBodyShape;
		const int pillarSegs=64;
		for (int i=0;i<pillarSegs;i++)						
			pillarBodyShape.addPoint(.5*(1-.15*Math::Abs(Math::Sin(i/(float)pillarSegs*8.*Math::TWO_PI))) * 
						Vector2(Math::Cos(i/(float)pillarSegs*Math::TWO_PI), Math::Sin(i/(float)pillarSegs*Math::TWO_PI)));
		pillarBodyShape.close();
		// We're also setting up a scale track, as traditionnal pillars are not perfectly straight
		Procedural::Track pillarTrack = Procedural::CatmullRomSpline2().addPoint(0,1).addPoint(0.5,.95).addPoint(1,.8).realizeShape().convertToTrack(Procedural::Track::AM_RELATIVE_LINEIC);
		// Creation of the pillar body
		Procedural::TriangleBuffer pillarTB;
		Procedural::Extruder().setExtrusionPath(&pillarBodyPath).setShapeToExtrude(&pillarBodyShape).setScaleTrack(&pillarTrack).setCapped(false).setPosition(0,1,0).addToTriangleBuffer(pillarTB);
		// Creation of the top and the bottom of the pillar
		Procedural::Shape s3 = Procedural::RoundedCornerSpline2().addPoint(-1,-.25).addPoint(-1,.25).addPoint(1,.25).addPoint(1,-.25).close().realizeShape().setOutSide(Procedural::SIDE_LEFT);
		Procedural::Path p3;
		for (int i=0;i<32;i++)
		{
			Ogre::Radian r = (Ogre::Radian) (Ogre::Math::HALF_PI-(float)i/32.*Ogre::Math::TWO_PI);
			p3.addPoint(0,-.5+.5*i/32.*Math::Sin(r),-1+.5*i/32.*Math::Cos(r));
		}
		p3.addPoint(0,0,-1).addPoint(0,0,1);
		for (int i=0;i<32;i++)
		{
			Ogre::Radian r = (Ogre::Radian) (Ogre::Math::HALF_PI-(float)i/32.*Ogre::Math::TWO_PI);
			p3.addPoint(0,-.5+.5*(1-i/32.)*Math::Sin(r),1+.5*(1-i/32.)*Math::Cos(r));
		}
		Procedural::Extruder().setExtrusionPath(&p3).setShapeToExtrude(&s3).setPosition(0,6.,0).addToTriangleBuffer(pillarTB);
		//Procedural::BoxGenerator().setPosition(0,6.5,0).addToTriangleBuffer(pillarTB);
		Procedural::BoxGenerator().setPosition(0,.5,0).addToTriangleBuffer(pillarTB);
		pillarTB.transformToMesh("pillar");
		// We put the pillars on the side of the road
		for (int i=0;i<p.getSegCount();i++)
			if (i%2==0)
				putMeshMat("pillar", "derp", p.getPoint(i)+4*p.getAvgDirection(i).crossProduct(Ogre::Vector3::UNIT_Y).normalisedCopy(),false);

		// -- Jarre
		// 
		Procedural::TriangleBuffer tb;
		// Body
		Procedural::Shape jarreShape = Procedural::CubicHermiteSpline2().addPoint(Ogre::Vector2(0,0), Ogre::Vector2::UNIT_X, Ogre::Vector2::UNIT_X)
																.addPoint(Ogre::Vector2(2,3))
																.addPoint(Ogre::Vector2(.5,5), Ogre::Vector2(-1,1).normalisedCopy(), Ogre::Vector2::UNIT_Y)
																.addPoint(Ogre::Vector2(1,7), Ogre::Vector2(1,1).normalisedCopy()).realizeShape().thicken(.1).getShape(0);
		Procedural::Lathe().setShapeToExtrude(&jarreShape).addToTriangleBuffer(tb);
		// Handle 1
		Procedural::Shape jarreHandleShape = Procedural::CircleShape().setRadius(.2).realizeShape();
		Procedural::Path jarreHandlePath = Procedural::CatmullRomSpline3().addPoint(Ogre::Vector3(0,6.5,.75))
																.addPoint(Ogre::Vector3(0,6,1.5))
																.addPoint(Ogre::Vector3(0,5,.55)).setNumSeg(10).realizePath();					
		Procedural::Extruder().setShapeToExtrude(&jarreHandleShape).setExtrusionPath(&jarreHandlePath).addToTriangleBuffer(tb);		
		// Handle2
		jarreHandlePath.reflect(Ogre::Vector3::UNIT_Z);
		Procedural::Extruder().setShapeToExtrude(&jarreHandleShape).setExtrusionPath(&jarreHandlePath).addToTriangleBuffer(tb);		
		tb.transformToMesh("jarre");
		putMeshMat("jarre", "derp", Vector3(5,0,5),false);
		

	}*/
