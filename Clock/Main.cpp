#include <osgViewer/Viewer>
#include <osg/LineWidth>
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

#include <ctime>
#include <iostream>

double get_current_angle(int type)
{
	 struct tm *local; 
     time_t t;
	 double hour, min, sec;
	 double angle;

     t=time(0);
     local=localtime(&t);
	 hour = (double)(local->tm_hour);
	 min  = (double)(local->tm_min);
	 sec  = (double)(local->tm_sec);

	 std::cout << "Local hour is:" << local->tm_hour << std::endl;
	 std::cout << "Local min is:" << local->tm_min << std::endl;
	 std::cout << "Local sec is:" << local->tm_sec << std::endl;

	 switch (type) {
	 case (0):	/* hour */
		 if (hour > 12) {
			 hour = hour - 12;
		 }
		 angle  = (1.0 / 12.0) * 2 * osg::PI * hour;
		 angle += (1.0 / 12.0) * 2 * osg::PI * ((60 * min + sec) / (60 * 60));	/* second */ 
		 break;
	 case (1):	/* minute */
		 angle  = (1.0 / 60.0) * 2 * osg::PI * min;
		 angle += (1.0 / 60.0) * 2 * osg::PI * (sec / 60);	/* second */ 
		 break;
	 case (2):	/* second */
		 angle = (1.0 / 60.0) * 2 * osg::PI * sec;
		 break;
	 default:
		 break;
	 }

#if 0
    if (angle >= 0 && angle < ((osg::PI) / 2.0)) {
        angle = osg::PI / 2.0 - angle;
    } else {
        angle = -1 * (angle - osg::PI / 2.0);
    }
#endif
	angle = -1 * angle;
	return angle;
}

/* using namespace osg; */
class DynamicHourCallback : public osg::Drawable::UpdateCallback
{
public:
    DynamicHourCallback() : _angle(0.0) {}
    
    virtual void update( osg::NodeVisitor* nv, osg::Drawable* drawable )
    {
        osg::Geometry* geom = dynamic_cast<osg::Geometry*>( drawable );
        if ( !geom ) return;
        
        osg::Vec3Array* vertices = dynamic_cast<osg::Vec3Array*>( geom->getVertexArray() );
        if ( vertices )
        {
            osg::Vec3& pt = vertices->back();
            _angle = get_current_angle(0);
            pt.set( 5.0*cos(_angle), 5.0*sin(_angle), 0.4 );
            vertices->dirty();
        }
    }

protected:
    float _angle;
};

class DynamicMinCallback : public osg::Drawable::UpdateCallback
{
public:
    DynamicMinCallback() : _angle(0.0) {}
    
    virtual void update( osg::NodeVisitor* nv, osg::Drawable* drawable )
    {
        osg::Geometry* geom = dynamic_cast<osg::Geometry*>( drawable );
        if ( !geom ) return;
        
        osg::Vec3Array* vertices = dynamic_cast<osg::Vec3Array*>( geom->getVertexArray() );
        if ( vertices )
        {
            osg::Vec3& pt = vertices->back();
            _angle = get_current_angle(1);
            pt.set( 7.0*cos(_angle), 7.0*sin(_angle), 0.5 );
            vertices->dirty();
        }
    }

protected:
    float _angle;
};

class DynamicSecCallback : public osg::Drawable::UpdateCallback
{
public:
    DynamicSecCallback() : _angle(0.0) {}
    
    virtual void update( osg::NodeVisitor* nv, osg::Drawable* drawable )
    {
        osg::Geometry* geom = dynamic_cast<osg::Geometry*>( drawable );
        if ( !geom ) return;
        
        osg::Vec3Array* vertices = dynamic_cast<osg::Vec3Array*>( geom->getVertexArray() );
        if ( vertices )
        {
            osg::Vec3& pt = vertices->back();
            _angle = get_current_angle(2);
            pt.set( 9.0*cos(_angle), 9.0*sin(_angle), 0.6 );
            vertices->dirty();
        }
    }

protected:
    float _angle;
};
int main( int argc, char** argv )
{
	osg::ref_ptr<osg::Group> root = new osg::Group;

    /* hour */
    osg::ref_ptr<osg::Geode> geode_hour = new osg::Geode;
    osg::ref_ptr<osg::Vec3Array> vertices_hour = new osg::Vec3Array( 2 );
    (*vertices_hour)[0].set( float(0), 0.0, 0.4f );
    (*vertices_hour)[1].set( float(5), 0.0, 0.4f );

	osg::ref_ptr<osg::Geometry> geom_hour = new osg::Geometry;
    geom_hour->setVertexArray( vertices_hour.get() );
    geom_hour->addPrimitiveSet( new osg::DrawArrays(osg::DrawArrays::LINE_STRIP, 0, 2) );
    
    geom_hour->setInitialBound( osg::BoundingBox(osg::Vec3(-10.0,-10.0,-10.0), osg::Vec3(10.0,10.0,10.0)) );
    geom_hour->setUpdateCallback( new DynamicHourCallback );
    geom_hour->setUseDisplayList( false );
    geom_hour->setUseVertexBufferObjects( true );

    geode_hour->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    geode_hour->getOrCreateStateSet()->setAttribute( new osg::LineWidth(20.0) );
	geode_hour->addDrawable( geom_hour.get() );

    /* minute */
    osg::ref_ptr<osg::Geode> geode_minute = new osg::Geode;
    osg::ref_ptr<osg::Vec3Array> vertices_minute = new osg::Vec3Array( 2 );
    (*vertices_minute)[0].set( float(0), 0.0, 0.5f );
    (*vertices_minute)[1].set( float(7), 0.0, 0.5f );

	osg::ref_ptr<osg::Geometry> geom_minute = new osg::Geometry;
    geom_minute->setVertexArray( vertices_minute.get() );
    geom_minute->addPrimitiveSet( new osg::DrawArrays(osg::DrawArrays::LINE_STRIP, 0, 2) );
    
    geom_minute->setInitialBound( osg::BoundingBox(osg::Vec3(-10.0,-10.0,-10.0), osg::Vec3(10.0,10.0,10.0)) );
    geom_minute->setUpdateCallback( new DynamicMinCallback );
    geom_minute->setUseDisplayList( false );
    geom_minute->setUseVertexBufferObjects( true );

    geode_minute->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    geode_minute->getOrCreateStateSet()->setAttribute( new osg::LineWidth(15.0) );
	geode_minute->addDrawable( geom_minute.get() );

    /* second */
    osg::ref_ptr<osg::Geode> geode_second = new osg::Geode;
    osg::ref_ptr<osg::Vec3Array> vertices_second = new osg::Vec3Array( 2 );
    (*vertices_second)[0].set( float(0), 0.0, 0.6f );
    (*vertices_second)[1].set( float(9), 0.0, 0.6f );

	osg::ref_ptr<osg::Geometry> geom_second = new osg::Geometry;
    geom_second->setVertexArray( vertices_second.get() );
    geom_second->addPrimitiveSet( new osg::DrawArrays(osg::DrawArrays::LINE_STRIP, 0, 2) );
    
    geom_second->setInitialBound( osg::BoundingBox(osg::Vec3(-10.0,-10.0,-10.0), osg::Vec3(10.0,10.0,10.0)) );
    geom_second->setUpdateCallback( new DynamicSecCallback );
    geom_second->setUseDisplayList( false );
    geom_second->setUseVertexBufferObjects( true );

    geode_second->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    geode_second->getOrCreateStateSet()->setAttribute( new osg::LineWidth(10.0) );
	geode_second->addDrawable( geom_second.get() );

	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints;
	hints->setDetailRatio(2.0f);
	osg::ref_ptr<osg::ShapeDrawable> shape_clock_face;
    osg::ref_ptr<osg::Geode> geode_clock_face = new osg::Geode;

	shape_clock_face = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0.0f, 0.0f, 0.0f), 10.0f, 0.5f), hints.get());
	shape_clock_face->setColor(osg::Vec4(0.6f, 0.8f, 0.8f, 1.0f));

	geode_clock_face->addDrawable(shape_clock_face.get());

    osgViewer::Viewer viewer;
	root->addChild(geode_clock_face.get());
	root->addChild(geode_hour.get());
	root->addChild(geode_minute.get());
	root->addChild(geode_second.get());
	viewer.setSceneData( root.get() );

	return viewer.run();
}
