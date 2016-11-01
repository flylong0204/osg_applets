/* -*-c++-*- OpenSceneGraph - 2008.6.16 by FreeSouth
 *
 * RambleSystem�����������࣬�������������
*/
//------------------------------//------------------------------
#pragma once
 
 
//------------------------------//------------------------------
#include <osgViewer/Viewer>
#include <osgGA/CameraManipulator>
#include <osgUtil/IntersectVisitor>
#include <osg/LineSegment>
//------------------------------//------------------------------
class   CSouth: public osgGA::CameraManipulator
{
public:
	CSouth(void);
public:
	~CSouth(void);

private:

	osg::ref_ptr<osg::Node>      m_node;
 
	unsigned int			m_nID;
	float					m_fMoveSpeed;
	osg::Vec3				m_vPosition;
	osg::Vec3				m_vRotation;


	bool m_bLeftButtonDown;
	float m_fpushX;
	bool m_bPeng;
	float m_fpushY;

public:
	void setPeng(bool peng) ;
	bool getPeng() ;
	void setFpeng() ;

	virtual void setNode(osg::Node*);

	// �麯��
	virtual void setByMatrix(const osg::Matrixd& matrix);
	// �麯��
	virtual void setByInverseMatrix(const osg::Matrixd& matrix);

	virtual osg::Matrixd getMatrix(void) const;
	// �õ������
	virtual osg::Matrixd getInverseMatrix(void)const ;
	// ��Ҫ�¼�������
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);
	// ��Ŀ�Ƕ�
	float m_fAngle;
	// λ�ñ任����
	void ChangePosition(osg::Vec3& delta);

	float getSpeed() ;
	void  setSpeed(float ) ;
	void SetPosition(osg::Vec3 &position) ;
	void SetPosition(double *) ;
	osg::Vec3 GetPosition() ;
	
	//����ҵ�λ��
	void computeHomePosition();
 
};
//------------------------------//------------------------------