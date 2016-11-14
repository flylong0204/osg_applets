//------------------------------//------------------------------
//By FreeSouth at 2008 3 22 ieysx@163.com  www.osgChina.org 
//------------------------------//------------------------------


#include "PickHandler.h"

//-----------------------------------------------------------------//------------------------------------------------------------
bool CPickHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	switch(ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::FRAME):
		{
			osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
			viewer ->getCamera() ->getViewMatrixAsLookAt(position, center, up) ;
			if (viewer) pick(viewer,ea);
			return false;
		}    
	default:
		return false;
	}

}
//-----------------------------------------------------------------//------------------------------------------------------------
void CPickHandler::pick(osgViewer::Viewer* viewer, const osgGA::GUIEventAdapter& ea)
{
	osgUtil::LineSegmentIntersector::Intersections intersections;

	std::string gdlist="";

	std::ostringstream os;

	os<<"Position X: "<<position[0]<<"     Y: "<<position[1]<<"     Z: "<<position[2] ;

	gdlist += os.str();

	setLabel(gdlist);
}
//-----------------------------------------------------------------//------------------------------------------------------------
// ´´½¨HUD
//-----------------------------------------------------------------//------------------------------------------------------------
