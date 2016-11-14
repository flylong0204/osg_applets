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

/* using namespace osg; */

int main( int argc, char** argv )
{
	osg::ref_ptr<osg::Group> root = new osg::Group;

	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints;
	hints->setDetailRatio(2.0f);
	osg::ref_ptr<osg::ShapeDrawable> clock_face, shape2;

	clock_face = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.05f), hints.get());
	clock_face->setColor(osg::Vec4(0.6f, 0.8f, 0.8f, 1.0f));

	shape2 = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.4f, 0.0f, 0.09f), 0.9f, 0.1f, 0.03f), hints.get());
	shape2->setColor(osg::Vec4(0.4f, 0.9f, 0.3f, 1.0f));


    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(clock_face.get());
	geode->addDrawable(shape2.get());

    osgViewer::Viewer viewer;
	root->addChild(geode.get());
    viewer.setSceneData( root.get() );
    return viewer.run();
}
