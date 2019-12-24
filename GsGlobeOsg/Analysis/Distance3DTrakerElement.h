#pragma once

#include <osgGA/GUIEventHandler>
#include <osgEarth/MapNode>
#include <osgViewer/View>
#include <osg/Vec3d>
#include <placename/PlaceNode.h>
#include <event.h>

class Distance3DTrakerElement : public osgGA::GUIEventHandler
{
public:
	Distance3DTrakerElement();//, GeoGlobe::IConsultationWindow* consultationWnd);
	virtual ~Distance3DTrakerElement();

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	bool pick(osgViewer::View* view, const osgGA::GUIEventAdapter& ea, osg::Vec3d& world);
	
	//����label
	GeoGlobe::Annotation::PlaceNode* CreateLabel(osgEarth::MapNode* m_mapNode, osgEarth::GeoPoint mapPoint, std::string na);

	//�����
	osg::Node* createLine(osg::Vec3d lbegin, osg::Vec3d lend,osg::Vec3d offset);
	
	double getDistance3D();
	std::vector<osg::Vec3d> getPickPoints();

	osg::Node* DisplayGroup();

	UTILITY_NAME::GsDelegate<void(double)> OnFinish;

private:
	osg::ref_ptr<osgEarth::MapNode> m_mapNode;
	bool m_bIsFirst;
	bool m_bIsFinished;

	//ʰȡ�ĵ㼰����
	std::vector<osg::Vec3d> m_PickPoints;
	double m_Distance3D;

	bool m_isDrag;

	//���ʰȡ�ĵ�
	osg::Vec3d world;

	//��Ƥ��
	osg::ref_ptr<osg::Node> RubberBand;

	//�����Label
	osg::ref_ptr<GeoGlobe::Annotation::PlaceNode> m_ptrLabelNode;
	osgEarth::Symbology::Style m_SymStyle;

	//��ת����
	osg::ref_ptr<osg::MatrixTransform> mt; 

	osg::ref_ptr<osg::Group> displayGroup;
};
