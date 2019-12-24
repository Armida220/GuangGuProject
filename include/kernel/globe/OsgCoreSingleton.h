#pragma once

#include <utility.h>
#include <osg/Vec3d>

namespace osg
{
	class Vec3d;
}
namespace osg
{
	class Group;
}

namespace osgEarth
{
	class MapNode;
}

namespace osgViewer
{
	class Viewer;
}

GLOBE_NS

class LonAndLatElement;
class EarthManipulator;
class ElementBox;
class LayerBox;

class GS_API OsgCoreSingleton : public GeoStar::Utility::GsRefObject
{
public:

	static OsgCoreSingleton* Instance();

	/*ʰȡBillBoard����ĻԪ����Ҫʹ��osgearth�Դ���RTT����ʰȡ�����BillBoard�ӵ�MapNode��Ⱥ���У�
	ע������Ⱥ�飬����ֱ����Ϊ���Ӽӵ�MapNode���棬Ŀǰԭ����*/
	osg::Group* RTTPickGroup();
	osg::Group* Root();
	//osg::Group* Vector();

	osgEarth::MapNode* MapNode();
	LonAndLatElement* LonAndLat();

	//����ȷ�ľ�γ�������㵽�������бƫ������
	void CorrectPosByOblique(osg::Vec3d& vecPos);

	//���������бƫ�������㵽��ȷ�ľ�γ������
	void DeCorrectPosByOblique(osg::Vec3d& vecPos);

	void setSrsInfor(const std::string& strSrs, const osg::Vec3d& vecOrigin);
	void getSrsInfor(std::string& strSrs, osg::Vec3d& vecOrigin);

	ElementBox* getElementBox();
	LayerBox * getLayerBox();
	osgViewer::Viewer* OsgViewer();
	EarthManipulator* GGEarthManipulator();

	void RegisteMapNode(osgEarth::MapNode* ptrMapNode);
	void RegisteLonAndLatElement(LonAndLatElement* ptrLonAndLat);

	void RegisteElement(ElementBox * ptrElementBox);
	void RegisteLayerBox(LayerBox * ptrLayerBox);

protected:
	OsgCoreSingleton();
	virtual ~OsgCoreSingleton();

	std::string m_strSrs;
	osg::Vec3d m_vecOrigin;

	osg::Group* m_ptrRTTPickGroup;
	osg::Group* m_ptrRoot;
	//osg::Group* m_Vector;
	osgEarth::MapNode* m_ptrMapNode;
	osgViewer::Viewer* m_ptrViewer;
	EarthManipulator* m_ptrManip;
	LonAndLatElement* m_ptrLonAndLat;
	ElementBox * m_ptrElementBox;
	LayerBox * m_ptrLayerBox;
	//std::vector<osg::ref_ptr<osgEarth::Features::Feature> > m_vecFeatures;
};

GS_SMARTER_PTR(OsgCoreSingleton);

GLOBE_ENDNS


