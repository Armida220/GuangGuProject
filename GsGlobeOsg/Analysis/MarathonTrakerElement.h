#pragma once

#include <osgGA/GUIEventHandler>
#include <osgEarth/MapNode>
#include <osgEarthAnnotation/LabelNode>
#include <osgViewer/View>
#include <osg/Vec3d>

namespace GeoGlobe
{
	class SphereElement;
}

class MarathonTrakerElement : public osgGA::GUIEventHandler
{
public:
	MarathonTrakerElement();
	virtual ~MarathonTrakerElement();

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	bool pick(osgViewer::View* view, const osgGA::GUIEventAdapter& ea, osg::Vec3d& world);
	
	//����label
	osgEarth::Annotation::LabelNode* CreateLabel(osgEarth::MapNode* m_mapNode, osgEarth::GeoPoint mapPoint, std::string na);

	//�����
	osg::Node* createLineM(osg::Vec3d lbegin, osg::Vec3d lend,osg::Vec3d offset);
	
	double getDistance3D();
	std::vector<osg::Vec3d> getPickPoints();

	osg::Node* DisplayGroup();

	bool isFinish();
	void setPosition(GeoGlobe::SphereElement* ptrSphere, osg::Vec3d world);
	void setLinePosition(int nIndex, int nEndPoint, osg::Vec3d world);
	void UpateLabel(int nIndex,osg::Vec3d start, osg::Vec3d end);

private:
	osg::ref_ptr<osgEarth::MapNode> m_mapNode;
	bool m_bIsFirst;
	bool m_bIsFinished;

	osg::Vec3d m_vecOff;

	//ʰȡ�ĵ㼰����
	std::vector<osg::Vec3d> m_vecPickPoints;
	std::vector<osg::Node*> m_vecLines;
	std::vector<osgEarth::Annotation::LabelNode*> m_vecLabel;
	std::vector<GeoGlobe::SphereElement*> m_vecShpere;

	double m_Distance3D;

	//���ʰȡ�ĵ�
	osg::Vec3d m_vecWorld;

	//��Ƥ��
	osg::ref_ptr<osg::Node> RubberBand;

	//�����Label
	osg::ref_ptr<osgEarth::Annotation::LabelNode> m_ptrLabelNode;
	osgEarth::Symbology::Style m_SymStyle;

	//��ת����
	osg::ref_ptr<osg::MatrixTransform> mt; 

	osg::ref_ptr<osg::Group> displayGroup;
};
