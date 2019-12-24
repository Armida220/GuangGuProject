#ifndef RADARSPHERE_H
#define RADARSPHERE_H 1

#include <osgDB/ReadFile>
#include <osgearth/MapNode>

namespace GeoGlobe
{
	class RadarSphere : public osg::Geometry
{
public:

	RadarSphere( int iNumPartsLongtitude_half , int iNumPartsLatitude_half , osg::Vec3d& world, osg::ref_ptr<  osgEarth::MapNode > mapNode);

	void InitVertices(osg::Vec3d& world);//��ʼ������

	void AddFaces(osg::Node* node);//�����

	void setRadius(float r);

protected:

	double m_dRadius;//�뾶

	int m_iNumPartsLongtitude_half;//���߷ָ�Ŀ���(����)

	int m_iNumPartsLatitude_half;//γ�߷ָ�Ŀ���(����)
	
	osg::ref_ptr< osg::Vec3Array > m_pVertices;//Բ���ϵĸ���

	osg::Vec3d m_center;

	osg::ref_ptr< osgEarth::MapNode > m_mapNode;

	osg::ref_ptr<osg::Geode> pGeode;

	
};

} // namespace GeoGlobe

#endif