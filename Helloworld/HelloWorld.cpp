//By FreeSouth  ieysx@163.com  www.osgChina.org  2008 6 13

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Node>
#include "South.h"

void main()
{
    osgViewer::Viewer viewer;
	viewer.setSceneData(osgDB::readNodeFile("ceep.ive"));
	viewer.setCameraManipulator(new CSouth()) ;
    viewer.realize();
    viewer.run();
}
