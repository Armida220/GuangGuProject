#pragma once
#include <osg/Group>
#include <geometry.h>
#include <osgViewer/View>
#include <osgEarth/MapNode>
#include <osg/Geometry>
#include <osgEarthAnnotation/FeatureNode>
#include <GsReference.h>
#include "SphereElement.h"
GLOBE_NS
class Element;
GLOBE_ENDNS
namespace GeoGlobe
{
	class GeoMapTool;
	/******��װ�༭�����Ƶ�tracker�Ĺ���*****/
	class EditDrawElmentTracker :public osg::Group
	{
	public:
		EditDrawElmentTracker(GeoMapTool* mapNode);
		~EditDrawElmentTracker();
		// ���ñ༭����
		bool SetEditElement(GLOBE_NAME::Element* edit);
		// ȡ���༭����
		void CancelEdit();

		int GetNodeSize();
		int GetDrawMode();
		// �ж��Ƿ� ���еĽڵ�Ĺ��� -1 û���κνڵ����
		int HitNode(osg::Node* node);
		// ��ȡ��ǰ���еĽڵ����
		int GetCurrentIndex();
		bool AddPoint(const KERNEL_NAME::GsRawPoint3D& p);
		bool InsertPoint(const KERNEL_NAME::GsRawPoint3D& p, int index);
		void MovePoint(const KERNEL_NAME::GsRawPoint3D& p, int index);
		//ɾ����ǰ�ڵ�
		bool DeleCurNode();
		// ����elment ��λ����Ϣ
		void UpdateElement();

	protected:
		//
		void SetCurrNodeIndex(int index);

		osgEarth::MapNode* getMapNode();
		void CreateLineFeature();// �����߶���
		SphereElement* CreatePointNode(const KERNEL_NAME::GsRawPoint3D& p);
		void CreatePolygonFeature();// ������feature
		void DrawPointNode();// ���Ƶ����
		void DrawLineFeature();// �����ߵĹ���
		void DrawPolygonFeature();// ����������

	protected:
		std::vector<KERNEL_NAME::GsRawPoint3D> m_point; //����λ��
		std::vector <osg::ref_ptr<SphereElement>> m_NodePoints;
		osg::ref_ptr< osgEarth::Annotation::FeatureNode> m_featureNode;//�����ߵ���ʽ����
		osg::ref_ptr< osgEarth::Features::Feature>  m_feature;
		osg::Vec4i m_PointColor;
		osg::Vec4i m_LineColor;
		osg::Vec4i m_CurrPointColor;//��ǰ�ڵ���ɫ����
		float m_pointSize;// �ڵ��С
		float m_CurrPointSize;//��ǰ�ڵ��С		
		GLOBE_NAME::Element * m_CurElement;//��ǰ�༭��element
		int m_CurrentNodeIndex;//��ǰѡ�еĽڵ�
		int m_DrawMode;//�༭ģʽ�����ģʽ
		int m_GeomType;// 1 �ǵ㣬2 ���� ��3 ����
		//
		GeoMapTool* m_ptrMapTool;// ����tracker ��Ӧ�Ĳ�������

	};
	// ���Ƽ��ȵķ�װ
	class SimpleLineElement:public osg::MatrixTransform
	{
	public:
		SimpleLineElement();
		~SimpleLineElement();

		void SetLineWidth(float w);
		float GetLineWidth();

		void SetLineColor(const osg::Vec4& color);
		const osg::Vec4 &GetLineColor()const;

		void AddPoint(const osg::Vec3d& point);
		void SetPoints(osg::Vec3dArray & points);
		int GetPointCount();
		void Clear();
		void Init();

	private:
		osg::ref_ptr<osg::Geometry> m_Geom;
		osg::ref_ptr<osg::Vec3dArray> m_Points;
	};
}
