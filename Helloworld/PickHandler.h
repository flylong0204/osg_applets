/* -*-c++-*- OpenSceneGraph - 2008.3.23 by FreeSouth
 *
 * RambleSystem�¼�����,��������򵥵��¼�
*/
//------------------------------//------------------------------
#pragma once

//------------------------------//------------------------------
#include <osgUtil/Optimizer>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Material>
#include <osg/Geode>
#include <osg/BlendFunc>
#include <osg/Depth>
#include <osg/Projection>
#include <osg/MatrixTransform>
#include <osg/Camera>
#include <osg/io_utils>
#include <osgText/Text>
#include <sstream>
//------------------------------//------------------------------
//�¼���
class  CPickHandler : public osgGA::GUIEventHandler 
{
public: 

	/**���캯��*/
    CPickHandler(osgText::Text* updateText):
        _updateText(updateText) {}
        
	/**��������*/
    ~CPickHandler() {}
    
	/**�¼������﷢��*/
    bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);

	/**PICK*/
    virtual void pick(osgViewer::Viewer* viewer, const osgGA::GUIEventAdapter& ea);

	/**LABEL*/
    void setLabel(const std::string& name)
    {
        if (_updateText.get()) _updateText->setText(name);
    }
    
protected:
	osg::Vec3 position ;
	osg::Vec3 center ;
	osg::Vec3 up ;
    osg::ref_ptr<osgText::Text>  _updateText;
};
//------------------------------//------------------------------
//HUD
class  CreateHUD

{
public:
	CreateHUD(){} ;
	~CreateHUD(){} ;

	osg::ref_ptr<osg::GraphicsContext::Traits> traits;
	


	/**����HUD*/
	osg::Node * createHUD(osgText::Text* updateText)
	{
		osg::Camera* hudCamera = new osg::Camera;
		hudCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
		hudCamera->setProjectionMatrixAsOrtho2D(0,1280,0,1024);
		hudCamera->setViewMatrix(osg::Matrix::identity());
		hudCamera->setRenderOrder(osg::Camera::POST_RENDER);
		hudCamera->setClearMask(GL_DEPTH_BUFFER_BIT);

		std::string timesFont("fonts//cour.ttf");

		osg::Vec3 position(0.,0.,0.0);

		{ 
			osg::Geode* geode = new osg::Geode();
			osg::StateSet* stateset = geode->getOrCreateStateSet();
			stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
			stateset->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
			geode->setName("The text label");
			geode->addDrawable( updateText );
			hudCamera->addChild(geode);
			updateText->setCharacterSize(20.0f);
			updateText->setFont(timesFont);
			updateText->setColor(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
			updateText->setText("");
			updateText->setPosition(position);
			updateText->setDataVariance(osg::Object::DYNAMIC);
		}    

    return hudCamera;

	}
} ;
//------------------------------//------------------------------