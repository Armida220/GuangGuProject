#pragma once
#include <osgGA/GUIEventHandler>
#include <geometry.h>
#include <osgViewer/View>
#include <osgEarth/MapNode>
#include <osgEarthAnnotation\FeatureNode>
#include "EditDrawElmentTracker.h"
#include <GsReference.h>

GLOBE_NS
class ElementBox;
GLOBE_ENDNS

namespace GeoGlobe
{
	/****
	* �����ĵ�ͼ�������ͣ���װ�˵�����Ҽ���
	*/
	class GeoMapTool :public osgGA::GUIEventHandler
	{
	protected:
		std::string m_zToolName;

	public:
		GeoMapTool(osgEarth::MapNode* mapNode);
		virtual~GeoMapTool();

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) override;
		// ��갴�µ��¼�����
		virtual bool onMousePress(const osgGA::GUIEventAdapter& ea,const KERNEL_NAME::GsRawPoint3D& point);
		// ����ƶ����¼�����
		virtual bool onMouseMove(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		// ���̧����¼�����
		virtual bool onMouseUp(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		// ��ק����Ӧ�¼�
		virtual bool onMouseDrag(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point) { return false; };
		// ���̵İ����¼�
		virtual bool onKeyDown(const osgGA::GUIEventAdapter& ea) { return false; }
		// ���̵ĵ����¼�
		virtual bool onKeyUp(const osgGA::GUIEventAdapter& ea) { return false; }
		// �Ƿ񼤻�ʹ������
		virtual void SetEnable(bool enable);
		virtual void SetMonitorMouseMove(bool enable);
		virtual bool Enable();

		virtual void setMapNode( osgEarth::MapNode* mapNode);
		virtual osgEarth::MapNode* getMapNode();

		// �Ƿ���¼����¼�
		bool isPressKey(int key);

	protected:
		// ��װ�������
		virtual bool LeftMouseClick(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		// ����Ҽ�
		virtual bool RightMouseClick(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		// ��� ˫��
		virtual bool MouseDoubleClick(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		// ���λ��ת������γ�ȵķ���
		bool getLocationAt(osgViewer::View* view, double x, double y, KERNEL_NAME::GsRawPoint3D& point);
		// ����ת���� ��������
		bool PointToWorld(KERNEL_NAME::GsRawPoint3D&point, osg::Vec3d & outWorld);
		// ��������ת������γ��
		bool WorldToGeoPoint(osg::Vec3d & world, KERNEL_NAME::GsRawPoint3D& point);
		GLOBE_NAME::ElementBox* GetElementBox();
		//
		bool m_isEnable;
		bool m_isOpenMove;
		osg::ref_ptr<osgEarth::MapNode> m_mapNode;
		std::vector<int> m_CurPressKey;
		osgViewer::View* m_ptrCurView;// �ڲ�ʹ�õ�ǰview
	};

	/****************************************/
	//*--           NewPolygonLineTool        */
	/****************************************/
	class NewPolygonLineTool :public GeoMapTool
	{
	public:
		NewPolygonLineTool(osgEarth::MapNode* mapNode);
		virtual ~NewPolygonLineTool();
		// ��갴�µ��¼�����
		virtual bool onMousePress(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		// ����ƶ����¼�����
		virtual bool onMouseMove(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		// ���̧����¼�����
		virtual bool onMouseUp(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		// �Ƿ񼤻�ʹ������
		virtual void SetEnable(bool enable);

		/// \brief ���ôκ�����������߹���
		  virtual void FinishTracker();
		    /// \brief ���ڽ������̵��õķ���
		  virtual void OnFinishTracker(const std::vector<KERNEL_NAME::GsRawPoint3D> & points);
		    /// \brief ����������Ҫ
		  virtual void Update();
		    /// \brief ��������Ĺ���
		  virtual void Reset();
		    /// \brief ��ȡ���ƶ������Ҫ����С��ĸ���
		    /// \return ���ػ��ƶ������Ҫ����С�����
		    int MinPointCount()const;

		    /// \brief ���û��ƶ������Ҫ��С�����
		    /// \param min �����ֵ
		    void MinPointCount(int min);
		    /// \brief ��ȡ��Ҫ���������
		    ///
		    int MaxPointCount()const;
		    /// \brief ���û�����Ҫ�����ֵ
		    /// \param max �����ֵ
		    void MaxPointCount(int max);
	protected:
		virtual bool LeftMouseClick(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		virtual bool RightMouseClick(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);

	protected:
		    std::vector<KERNEL_NAME::GsRawPoint3D> m_Points;//�洢�ĵ�����
		    int m_MaxCount;//���
		    int m_MinCount;//��С������
		    double m_MouseTime;
		    bool m_isNeedAdd;
		    bool m_IsMouseDown;
		    float m_DownX;
		    float m_DownY;
		    bool m_isFinished;
	};

	/***********************
	*�򵥻��ƹ��ߵĹ���
	/*********************************/
	class DrawElementTool : public NewPolygonLineTool
	{
	public:
		DrawElementTool(osgEarth::MapNode* mapNode);
		virtual~DrawElementTool();
		/// \brief ���ڽ������̵��õķ���
		virtual void OnFinishTracker(const std::vector<KERNEL_NAME::GsRawPoint3D> & points);
		/// \brief ����������Ҫ
		virtual void Update();

		osg::Node* DisplayGroup();
	//	virtual bool MouseDoubleClick(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		// ��ɵ�ί�й���
		UTILITY_NAME::GsDelegate<void(const KERNEL_NAME::GsRawPoint3D&)> OnDoubleClickEvent;
		UTILITY_NAME::GsDelegate<void(const std::vector<KERNEL_NAME::GsRawPoint3D> &)> OnDrawFinishEvent;
	protected:
		virtual bool RightMouseClick(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		virtual bool MouseDoubleClick(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point) override;
		void CreateFeatrue();
		void Clear();
	protected:
		//
		//osgEarth::GeoInterpolation _geoInterpolation;
		//osg::ref_ptr<osg::Node> RubberBand;
		//osg::ref_ptr< osgEarth::Annotation::FeatureNode > _featureNode;
		//osg::ref_ptr< osgEarth::Features::Feature >  _feature;
		osg::ref_ptr<SimpleLineElement> m_SimpleLine;
		////�����Label
		//osgEarth::Symbology::Style m_SymStyle;
		//osg::ref_ptr<osg::Geometry> m_drawLine;
		//��ת����
		osg::ref_ptr<osg::MatrixTransform> mt;
		osg::ref_ptr<osg::Group> displayGroup;
	};
	/********************************************************
	* ����������ƵĹ��ߵķ�װ
	**********************************************************/
	class DrawRectElementTool :public DrawElementTool
	{
	public:
		DrawRectElementTool(osgEarth::MapNode* mapNode);
		virtual~DrawRectElementTool();

		
		virtual void OnFinishTracker(const std::vector<KERNEL_NAME::GsRawPoint3D> & points);
		/// \brief ����������Ҫ
		virtual void Update();
		///  \brief ��ȡ��ǰ����model
		int GetDrawModel();
		/// \brief ���õ�ǰmodel �Ĺ���
		/// \brief param model 1 �� �㡢2�����ߡ�3���桢4�Ǿ���
		void SetDrawModel(int model);
	protected:
		int m_DrawModel;// 1 �� �㡢2�����ߡ�3���桢4�Ǿ���
	};
}