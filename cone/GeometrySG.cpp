#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/StateSet>
#include <osg/StateAttribute>
#include <osg/ShadeModel>
#include <osg/CullFace>
#include <osg/PolygonMode>
#include <osg/LineWidth>

#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>

#include <osg/Projection>
#include <osg/Geometry>
#include <osg/Texture>
#include <osg/TexGen>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/PolygonOffset>
#include <osg/CullFace>
#include <osg/TextureCubeMap>
#include <osg/TexMat>
#include <osg/MatrixTransform>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/PolygonOffset>
#include <osg/CullFace>
#include <osg/Material>
#include <osg/PositionAttitudeTransform>
#include <osg/ArgumentParser>

#include <osg/Camera>
#include <osg/TexGenNode>

#include <iostream>

osg::ref_ptr<osg::Node>
createSceneGraph()
{
	osg::ref_ptr<osg::Group> root = new osg::Group;

	osg::Box* unitCube = new osg::Box( osg::Vec3(0,0,0), 1.0f); 
	osg::ShapeDrawable* unitCubeDrawable = new osg::ShapeDrawable(unitCube);
 	
	osg::Geode* basicShapesGeode = new osg::Geode();
	basicShapesGeode->addDrawable(unitCubeDrawable);

	osg::Sphere* unitSphere = new osg::Sphere( osg::Vec3(0,0,0), 1.0);
	osg::Geode* unitSphereGeode = new osg::Geode();
	osg::PositionAttitudeTransform* sphereXForm = new osg::PositionAttitudeTransform();
	osg::ShapeDrawable* unitSphereDrawable = new osg::ShapeDrawable(unitSphere);

	unitSphereGeode->addDrawable(unitSphereDrawable);
	sphereXForm->addChild(unitSphereGeode);
	sphereXForm->setPosition(osg::Vec3(2.5,0,0));

#if 1
	const float radius = 0.8f;
	const float height = 1.0f;
	osg::ref_ptr<osg::ShapeDrawable> shape;
	osg::ref_ptr<osg::Geode> geode_2 = new osg::Geode;
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints;
	hints->setDetailRatio(2.0f);

	shape = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(-3.0f, 0.0f, 0.0f), radius), hints.get());
	shape->setColor(osg::Vec4(0.6f, 0.8f, 0.8f, 1.0f));
	geode_2->addDrawable(shape.get());

	shape = new osg::ShapeDrawable(new osg::Box(osg::Vec3(6.0f, 0.0f, 0.0f), 2 * radius), hints.get());
	shape->setColor(osg::Vec4(0.4f, 0.9f, 0.3f, 1.0f));
	geode_2->addDrawable(shape.get());

	shape = new osg::ShapeDrawable(new osg::Box(osg::Vec3(8.0f, 0.0f, 0.0f), 0.1f, 2, 2), hints.get());
	shape->setColor(osg::Vec4(0.8f, 0.8f, 0.4f, 1.0f));
	geode_2->addDrawable(shape.get());

	shape = new osg::ShapeDrawable(new osg::Cone(osg::Vec3(0.0f, 0.0f, -3.0f), radius, height), hints.get());
	shape->setColor(osg::Vec4(0.2f, 0.5f, 0.7f, 1.0f));
	geode_2->addDrawable(shape.get());

	shape = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0.0f, 0.0f, 3.0f), radius, height), hints.get());
	shape->setColor(osg::Vec4(1.0f, 0.3f, 0.3f, 1.0f));
	geode_2->addDrawable(shape.get());

#endif

	root->addChild(basicShapesGeode);
	root->addChild(sphereXForm);
	root->addChild(geode_2);

	return root.get();
}
