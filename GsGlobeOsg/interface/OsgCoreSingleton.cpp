#include "OsgCoreSingleton.h"
#include <osg/Group>
#include <osgEarth/MapNode>
#include <osgViewer/Viewer>
#include <LonAndLatElement.h>
#include "tool/GGEarthManipulator.h"
#include "tool/GeoGlobleEvent.h"

GLOBE_NS

OsgCoreSingleton* OsgCoreSingleton::Instance()
{
	static OsgCoreSingleton* ptrSingleton = new OsgCoreSingleton();

	return ptrSingleton;
}

OsgCoreSingleton::OsgCoreSingleton()
{
	m_ptrRoot = NULL;
	m_ptrMapNode = NULL;
	m_ptrViewer = NULL;
	m_ptrManip = NULL;
	//m_Vector = NULL;
	m_ptrRTTPickGroup = NULL;
	m_ptrLonAndLat = NULL;
	m_ptrLayerBox = NULL;
	m_strSrs = "";
	m_vecOrigin = osg::Vec3d(0.0,0.0,0.0);
}

osg::Group* OsgCoreSingleton::Root()
{
	if (NULL == m_ptrRoot)
		m_ptrRoot = new osg::Group();

	return m_ptrRoot;
}

osg::Group* OsgCoreSingleton::RTTPickGroup()
{
	if (NULL == m_ptrRTTPickGroup)
		m_ptrRTTPickGroup = new osg::Group();

	return m_ptrRTTPickGroup;
}

osgEarth::MapNode* OsgCoreSingleton::MapNode()
{
	return m_ptrMapNode;
}

void OsgCoreSingleton::setSrsInfor(const std::string& strSrs, const osg::Vec3d& vecOrigin)
{
	m_strSrs = strSrs;
	m_vecOrigin = vecOrigin;
}

void OsgCoreSingleton::getSrsInfor(std::string& strSrs, osg::Vec3d& vecOrigin)
{
	strSrs = m_strSrs;
	vecOrigin = m_vecOrigin;
}

//���������бƫ�������㵽��ȷ�ľ�γ������
void OsgCoreSingleton::DeCorrectPosByOblique(osg::Vec3d& vecPos)
{
	osg::ref_ptr<osgEarth::SpatialReference> ptrSrs;
	osg::ref_ptr<const osgEarth::SpatialReference> ptrWgs84Srs;
	if (m_strSrs != "")
	{
		ptrSrs = osgEarth::SpatialReference::create(m_strSrs);
		ptrWgs84Srs = GLOBE_NAME::OsgCoreSingleton::Instance()->MapNode()->getMap()->getSRS();
	}

	//�õ���б��λ��
	osg::Vec3d vecLocator;
	if (ptrSrs)
		ptrSrs->transform(m_vecOrigin, ptrWgs84Srs, vecLocator);

	//����б��λ�㻻���ƫ�ƾ���
	osg::Matrixd matrix;
	OsgCoreSingleton::Instance()->MapNode()->getMapSRS()->getEllipsoid()->computeLocalToWorldTransformFromLatLongHeight(
		osg::DegreesToRadians(vecLocator.y()),
		osg::DegreesToRadians(vecLocator.x()),
		vecLocator.z(),
		matrix);

	//�������ת����������
	osg::Vec3d world;
	osgEarth::GeoPoint point = osgEarth::GeoPoint(ptrWgs84Srs, vecPos);
	point.toWorld(world);

	//�õ���б��λ������󲢽��ϲ��������껻����������б�ֲ�����
	osg::Matrixd inverse = osg::Matrixd::inverse(matrix);
	world = world*inverse;

	//�õ���б��������
	osg::Vec3d vecLocal = world + m_vecOrigin;
	
	//��ɾ�γ��
	if (ptrSrs)
		ptrSrs->transform(vecLocal, ptrWgs84Srs, vecPos);
}

void OsgCoreSingleton::CorrectPosByOblique(osg::Vec3d& vecPos)
{
	if (m_strSrs == "")
		return ;

	osg::ref_ptr<osgEarth::SpatialReference> ptrSrs;
	osg::ref_ptr<const osgEarth::SpatialReference> ptrWgs84Srs;
	if (m_strSrs != "")
	{
		ptrSrs = osgEarth::SpatialReference::create(m_strSrs);
		ptrWgs84Srs = GLOBE_NAME::OsgCoreSingleton::Instance()->MapNode()->getMap()->getSRS();
	}

	if (ptrWgs84Srs)
	{
		osg::Vec3d vecWgs84 = vecPos;
		osg::Vec3d vecOut;
		//�Ȱ������ת���ط�����
		if (ptrWgs84Srs != NULL)
			ptrWgs84Srs->transform(vecWgs84, ptrSrs, vecOut);

		//�õ���б��λ��
		osg::Vec3d vecLocator;
		if (ptrSrs)
			ptrSrs->transform(m_vecOrigin, ptrWgs84Srs, vecLocator);

		//����б��λ�㻻���ƫ�ƾ���
		osg::Matrixd matrix;
		OsgCoreSingleton::Instance()->MapNode()->getMapSRS()->getEllipsoid()->computeLocalToWorldTransformFromLatLongHeight(
			osg::DegreesToRadians(vecLocator.y()),
			osg::DegreesToRadians(vecLocator.x()),
			vecLocator.z(),
			matrix);

		//���õ��ĵط������㵽�������б��λ��ľֲ����꣬Ȼ���ٻ���ɾ�γ��
		osg::Vec3d finalPos = (vecOut - m_vecOrigin)*matrix;

		osgEarth::GeoPoint point;
		point.fromWorld(ptrWgs84Srs, finalPos);

		vecPos.x() = point.x();
		vecPos.y() = point.y();
	}
}

LonAndLatElement* OsgCoreSingleton::LonAndLat()
{
	return m_ptrLonAndLat;
}

void OsgCoreSingleton::RegisteMapNode(osgEarth::MapNode* ptrMapNode)
{
	m_ptrMapNode = ptrMapNode;
}

void OsgCoreSingleton::RegisteLonAndLatElement(LonAndLatElement* ptrLonAndLat)
{
	m_ptrLonAndLat = ptrLonAndLat;
}

void OsgCoreSingleton::RegisteElement(ElementBox * ptrElementBox)
{
	m_ptrElementBox = ptrElementBox;
}

void OsgCoreSingleton::RegisteLayerBox(LayerBox * ptrLayerBox)
{
	m_ptrLayerBox = ptrLayerBox;
}

ElementBox * OsgCoreSingleton::getElementBox()
{
	return m_ptrElementBox;
}

LayerBox * OsgCoreSingleton::getLayerBox()
{
	return m_ptrLayerBox;
}

osgViewer::Viewer* OsgCoreSingleton::OsgViewer()
{
	if (NULL == m_ptrViewer)
	{
		m_ptrViewer = new osgViewer::Viewer();
		//Ĭ������Զ����¼������ڽ�����̱߳��������⣬������д�������濼�Ǹ���
		m_ptrViewer->addEventHandler(new GLOBE_NAME::GeoGlobleEventHandler());
	}

	return m_ptrViewer;
}

EarthManipulator* OsgCoreSingleton::GGEarthManipulator()
{
	if (NULL == m_ptrManip)
		m_ptrManip = new EarthManipulator();

	return m_ptrManip;
}

OsgCoreSingleton::~OsgCoreSingleton()
{

}

GLOBE_ENDNS