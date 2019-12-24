#pragma once
#include "GeoMapTools.h"
#include "EditDrawElmentTracker.h"
#include <osgEarthUtil/RTTPicker>
GLOBE_NS
class Element;
GLOBE_ENDNS

namespace GeoGlobe
{
	//****** elment ѡ����¼����� ��¼��ǰѡ���״̬��
	class ElementSelectTool :public GeoMapTool
	{
	public:
		ElementSelectTool(osgEarth::MapNode* mapNode);
		virtual ~ElementSelectTool();
		virtual bool onMousePress(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		// ���̧����¼�����
		virtual bool onMouseUp(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		// ���ߵļ���״̬
		virtual void SetEnable(bool enable);
		void setEnableSelect(bool enable);
		bool isEnableSelect();
		// ���õ�ǰѡ�е�element
		void SetSelected(GLOBE_NAME::Element* seleElement);
		// ѡ��ʱ�������¼���Ϣ
		UTILITY_NAME::GsDelegate<void(GLOBE_NAME::Element*, GLOBE_NAME::Element*)> OnSelectEvent;
	protected:
		// RTTPicker �ص��Ľṹ��
		struct RTTPickerCallBack:public osgEarth::Util::RTTPicker::Callback
		{
			ElementSelectTool * selectTool;
			RTTPickerCallBack(ElementSelectTool * tool);
			virtual void onHit(osgEarth::ObjectID id)override;
			virtual void onMiss()override;
		};
	protected:
		
		virtual bool LeftMouseClick(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		
		// ����ѡ��Ķ���Ĺ���
		GLOBE_NAME::Element* OnPickerElement(osgViewer::View* view, const osgGA::GUIEventAdapter& ea);

		// �Ե�ǰѡ�еĶ����Ƿ�����ѡ�񲢴����¼��ı��
		bool OnSelectElements(GLOBE_NAME::Element* seletEle,bool isSendEvent=true);
		// �ڲ����Ե��õ�ѡ��
		virtual void InterOnSelectElement(GLOBE_NAME::Element* oldElem, GLOBE_NAME::Element* newElem) {};
		// ȡ��ѡ��Ĺ���
		void CancelSelect();
	protected:
		double m_MouseTime;
		bool m_isNeedAdd;
		bool m_IsMouseDown;
		float m_DownX;
		float m_DownY;
		bool m_EnableSelect;
		// ��ǰѡ�е�element
		GLOBE_NAME::Element * m_CurrSelectElement;
		GLOBE_NAME::Element * m_TemSeletElement;//����ѡ��Ĺ���
		osg::ref_ptr< osgEarth::Util::RTTPicker> m_rttPicker;// rttp ѡ�����
		osg::ref_ptr<osgEarth::Util::RTTPicker::Callback> m_RttPickerCallback;
	};

	/**********************
	* �༭����Ĺ���
	****/
	class EditElementTool :public ElementSelectTool
	{
	public:
		enum EditMode
		{
			/// ��ת�����ű༭
			RotaAndScale = 1,
			/// �ڵ���Ϣ�ı༭�����Ƶ�Ͷ�λ��
			NodeEdit
		};
	public:
		EditElementTool(osgEarth::MapNode* mapNode);
		virtual ~EditElementTool();

		// ��갴�µ��¼�����
		virtual bool onMousePress(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		// ����ƶ����¼�����
		virtual bool onMouseMove(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		// ����϶��¼�����
		virtual bool onMouseDrag(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		// ���̧����¼�����
		virtual bool onMouseUp(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		// ���ռ����¼�
		virtual bool onKeyUp(const osgGA::GUIEventAdapter& ea);
		// ��ʼ�༭�Ĺ���
		void setEditElement(GLOBE_NAME::Element* editElement);
		// ��ʼ�༭���¼�
		UTILITY_NAME::GsDelegate<void(GLOBE_NAME::Element*)> OnEditElementEvent;
		// �����༭���¼�
		UTILITY_NAME::GsDelegate<void(GLOBE_NAME::Element*)> OnEndEditElementEvent;
		// ɾ��element �������¼�����
		UTILITY_NAME::GsDelegate<void(GLOBE_NAME::Element*)> OnDeleteElementEvent;
		//
	protected:
		// ��װ�������
		virtual bool LeftMouseClick(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);
		// ����Ҽ�
		virtual bool RightMouseClick(const osgGA::GUIEventAdapter& ea, const KERNEL_NAME::GsRawPoint3D& point);

		virtual void InterOnSelectElement(GLOBE_NAME::Element* oldElem, GLOBE_NAME::Element* newElem)override;
		// �ж��Ƿ�����һ���ڵ�
		int HitNode(const osgGA::GUIEventAdapter& ea);

		// �༭���µĹ���
		void OnUpdateEdit(int type);
		void CancelEdit();

	protected:// ��������Ĳ���
		 // �༭״̬���ͣ�0 ����ѡ��1��ѡ�н��б༭״̬��2���༭�ڵ� ��3: �ƶ�����ͼ��
		 int m_EditStateType = 0;
		 GLOBE_NAME::Element * m_CurEditElement;
		 KERNEL_NAME::GsRawPoint3D m_DownPoint, m_MovePoint;
		 EditMode m_EditMode;
		 osg::ref_ptr<EditDrawElmentTracker> m_EditDrawTracker;
	};
}
