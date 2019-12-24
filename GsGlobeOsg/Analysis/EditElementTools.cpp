#include "EditElementTools.h"
#include "globe/Element.h"
#include "globe/ElementBox.h"
#include <PlaceName/PlaceNode.h>
#include <PlaceName/GeoBillboard.h>
#include <osgEarthAnnotation/PlaceNode>
#include <placename/GeoBillboard.h>
#include <osgEarth/Registry>
#include <OsgCoreSingleton.h>


namespace GeoGlobe
{
	ElementSelectTool::ElementSelectTool(osgEarth::MapNode * mapNode):GeoMapTool(mapNode)
	{
		m_CurrSelectElement = NULL;
		m_TemSeletElement = NULL;
		m_isNeedAdd = false;
		m_MouseTime = 0;
		m_DownX = 0;
		m_DownY = 0;
		m_IsMouseDown = false;
		m_EnableSelect = false;
		m_isOpenMove = false;//�ر�����ƶ��¼��Ļ�ȡ
		m_rttPicker = new  osgEarth::Util::RTTPicker();
		m_RttPickerCallback = new RTTPickerCallBack(this);
		
		m_rttPicker->addChild(mapNode);
	}

	ElementSelectTool::~ElementSelectTool()
	{
		// �����ͷ�ȷ�� �Ƴ�ϸ��Ϣ
		GLOBE_NAME::OsgCoreSingleton::Instance()->OsgViewer()->removeEventHandler(m_rttPicker);
	}

	bool ElementSelectTool::onMousePress(const osgGA::GUIEventAdapter & ea, const KERNEL_NAME::GsRawPoint3D & point)
	{
		m_IsMouseDown = true;
		m_MouseTime = ea.getTime();
		m_DownX = ea.getX();
		m_DownY = ea.getY();
		return true;
	}
	bool ElementSelectTool::onMouseUp(const osgGA::GUIEventAdapter & ea, const KERNEL_NAME::GsRawPoint3D & point)
	{
		m_IsMouseDown = false;
		double upTime = ea.getTime();
		float dx = ea.getX() - m_DownX;
		float dy = ea.getY() - m_DownY;
		bool isSingleClick = (upTime - m_MouseTime < 1.5) && (dx*dx + dy*dy < 300);

		if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON && isSingleClick)
		{
			return LeftMouseClick(ea, point);
		}
		else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON&& isSingleClick)
		{
			return RightMouseClick(ea, point);
		}
		return false;
	}
	void ElementSelectTool::SetEnable(bool enable)
	{
		GeoMapTool::SetEnable(enable);
		if(!enable)
			GLOBE_NAME::OsgCoreSingleton::Instance()->OsgViewer()->removeEventHandler(m_rttPicker);
		if(enable)
			GLOBE_NAME::OsgCoreSingleton::Instance()->OsgViewer()->addEventHandler(m_rttPicker);
	}
	void ElementSelectTool::setEnableSelect(bool enable)
	{
		m_EnableSelect = enable;
		//��rtt �ڲ��Ƴ�event handler �����⣬��������Զ���handler �Ƴ�
		//if(enable)
		//	GLOBE_NAME::OsgCoreSingleton::Instance()->OsgViewer()->addEventHandler(m_rttPicker);
		//else {
		//	GLOBE_NAME::OsgCoreSingleton::Instance()->OsgViewer()->removeEventHandler(m_rttPicker);
		//}
	}
	bool ElementSelectTool::isEnableSelect()
	{
		return m_EnableSelect;
	}
	void ElementSelectTool::SetSelected(GLOBE_NAME::Element * seleElement)
	{
		OnSelectElements(seleElement, false);
	}
	bool ElementSelectTool::LeftMouseClick(const osgGA::GUIEventAdapter & ea, const KERNEL_NAME::GsRawPoint3D & point)
	{
		if(!m_EnableSelect)
		 return false;
		//������ͨ��osgearth ѡ��
		m_TemSeletElement = OnPickerElement(m_ptrCurView, ea);
		//��û��ѡ�������rtt ���̽���ѡ��
		if (m_TemSeletElement == NULL)
			m_rttPicker->pick(m_ptrCurView, ea.getX(), ea.getY(), m_RttPickerCallback);
		else {
			return OnSelectElements(m_TemSeletElement);
		}
		//ѡ���¼�����
		return true;
	}

	GLOBE_NAME::Element * ElementSelectTool::OnPickerElement(osgViewer::View * view, const osgGA::GUIEventAdapter & ea)
	{
		// osg �ڲ�ѡ�����Ĺ���
		//osgUtil::LineSegmentIntersector::Intersections intersections;
		//view->computeIntersections(ea.getX(), ea.getY(), intersections);
		float minx = ea.getX() - 5;
		float miny = ea.getY() - 5;
		osg::ref_ptr<osgUtil::PolytopeIntersector> intersector = new osgUtil::PolytopeIntersector(osgUtil::Intersector::WINDOW, minx, miny, minx+10, miny+10);
		intersector->setIntersectionLimit(osgUtil::Intersector::LIMIT_ONE_PER_DRAWABLE);
		osgUtil::IntersectionVisitor iv(intersector.get());

		view->getCamera()->accept(iv);

		GLOBE_NAME::ElementBox * elementBox=GetElementBox();
		osgUtil::PolytopeIntersector::Intersections intersections;
		if (intersector->containsIntersections())
		{
			intersections = intersector->getIntersections();
			osgUtil::PolytopeIntersector::Intersections::iterator hitr;
			for (hitr = intersections.begin(); hitr != intersections.end(); hitr++)
			{
				// the geodes are identified by name.
				osg::NodePath nodePath = hitr->nodePath;
				for (int i = 0; i < nodePath.size(); i++)
				{
					osg::ref_ptr<osg::Node> node = nodePath[i];
					if (node == NULL)
						continue;
					GLOBE_NAME::Element * findele = elementBox->findByNode(node);
					//if(findele->fin)
					//billboard ��GeoBillBord ��ʱʹ��rtt ���ʰȡ�ķ�ʽ
					if (findele && findele->Type()!=GLOBE_NAME::eBillboardElement&&findele->Type()!=GLOBE_NAME::eGeoBillBoardElement)
						return findele;
				}
			}
		}
		return NULL;
	}
	bool ElementSelectTool::OnSelectElements(GLOBE_NAME::Element * seletEle, bool isSendEvent)
	{
		if (seletEle == m_CurrSelectElement)
			return false;
		InterOnSelectElement(m_CurrSelectElement, seletEle);
		if (isSendEvent)
			OnSelectEvent(m_CurrSelectElement,seletEle);
		m_CurrSelectElement = seletEle;
		return true;

	}
	void ElementSelectTool::CancelSelect()
	{
		OnSelectElements(NULL, true);
	}
	//
	ElementSelectTool::RTTPickerCallBack::RTTPickerCallBack(ElementSelectTool * tool)
	{
		selectTool = tool;
	}
	void ElementSelectTool::RTTPickerCallBack::onHit(osgEarth::ObjectID id)
	{
		osg::Node* placeNode = NULL;
		placeNode = osgEarth::Registry::objectIndex()->get<GeoGlobe::PlaceName::GeoBillboard>(id);
		if (!placeNode)
			placeNode = osgEarth::Registry::objectIndex()->get<GeoGlobe::Annotation::PlaceNode>(id);

		if (placeNode)
		{
			GLOBE_NAME::ElementBox * elementBox =selectTool->GetElementBox();
			GLOBE_NAME::Element* ele = elementBox->findByNode(placeNode);
			if (ele)
			{
				selectTool->OnSelectElements(ele);
			}
		}
	}

	void ElementSelectTool::RTTPickerCallBack::onMiss()
	{

	}

	/*************************************************************************************
	* �༭���ߴ��벿��
	****************************************************************************************/

	EditElementTool::EditElementTool(osgEarth::MapNode * mapNode):ElementSelectTool(mapNode)
	{
		 m_EditStateType = 0;
		 m_CurEditElement=NULL;
		 m_EditMode=EditMode::NodeEdit;
		 m_EditDrawTracker = new EditDrawElmentTracker(this);
		 mapNode->addChild(m_EditDrawTracker);
		 setEnableSelect(true);
		 SetEnable(true);
	}
	EditElementTool::~EditElementTool()
	{
		getMapNode()->removeChild(m_EditDrawTracker);
	}
	bool EditElementTool::onMousePress(const osgGA::GUIEventAdapter & ea, const KERNEL_NAME::GsRawPoint3D & point)
	{
		ElementSelectTool::onMousePress(ea, point);
		// ����ѡ��״̬
		if (m_EditStateType == 0)
		{
			return false;
		}
		if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON && HitNode(ea)>-1)
		{
			//����ڵ����Ƶ���ƶ�ģʽ
			m_EditStateType = 2;
			m_MovePoint = point;
			return true;
		}
		else
		{
			m_EditStateType = 3;
		}
		return false;
	}
	bool EditElementTool::onMouseMove(const osgGA::GUIEventAdapter & ea, const KERNEL_NAME::GsRawPoint3D & point)
	{
		if (m_EditStateType == 0 || m_EditStateType == 3)
		{
			return ElementSelectTool::onMouseMove(ea, point);
		}
		else
			//if (m_EditStateType == 1)
			//{
			//	double dis = TOLERANCE * m_Display.DT.Resolution;
			//	m_EditDrawEle.HitPoint(Map, dis);
			//	UpdateMouseCursor();
			//	FireOnCursorChanged(Cursor);
			//}
			

		return false;
	}
	bool EditElementTool::onMouseDrag(const osgGA::GUIEventAdapter & ea, const KERNEL_NAME::GsRawPoint3D & point)
	{
		// �ƶ��ڵ�Ĺ���
		if (m_EditStateType == 2)
		{
			KERNEL_NAME::GsRawPoint3D offPoint = point - m_MovePoint;
			m_EditDrawTracker->MovePoint(offPoint, -1);
			m_MovePoint = point;
			return true;
		}
		return false;
	}
	bool EditElementTool::onMouseUp(const osgGA::GUIEventAdapter & ea, const KERNEL_NAME::GsRawPoint3D & point)
	{
		if (m_EditStateType == 2)//�༭״̬
		{
			m_EditStateType = 1;
			OnUpdateEdit(2);// �ڵ��ƶ�
			m_EditDrawTracker->UpdateElement();
		}
		else	if (m_EditStateType == 3)
			{
				m_EditStateType = 1;
			}
		// diaoyong ����ķ���
		ElementSelectTool::onMouseUp(ea, point);
		return false;
	}

	bool EditElementTool::LeftMouseClick(const osgGA::GUIEventAdapter & ea, const KERNEL_NAME::GsRawPoint3D & point)
	{
		// �����Ĵ������
		if (m_EditStateType == 0)
			return ElementSelectTool::LeftMouseClick(ea, point);
		// 
		int index = HitNode(ea);
		if (index > -1)
			return true;
		bool sucee = m_EditDrawTracker->AddPoint(point);
		if (sucee)// ������ʾelement��λ�ù���
			m_EditDrawTracker->UpdateElement();
		return sucee;
	}
	bool EditElementTool::RightMouseClick(const osgGA::GUIEventAdapter & ea, const KERNEL_NAME::GsRawPoint3D & point)
	{
		// �Ҽ������༭�Ĺ���
		GLOBE_NAME::Element* curElement = m_CurEditElement;
		CancelSelect();
		if (curElement)
			OnEndEditElementEvent(curElement);
		return false;
	}
	void EditElementTool::InterOnSelectElement(GLOBE_NAME::Element * oldElem, GLOBE_NAME::Element * newElem)
	{
		if (newElem == NULL)
		{
			CancelEdit();
		}
		else {
			setEditElement(newElem);
		}
	}

	// �ж��Ƿ�����һ���ߵĽڵ�����
	int EditElementTool::HitNode(const osgGA::GUIEventAdapter & ea)
	{
		osgUtil::LineSegmentIntersector::Intersections intersections;
		m_ptrCurView ->computeIntersections(ea.getX(), ea.getY(), intersections);
		//
		osgUtil::LineSegmentIntersector::Intersections::iterator hitr;
		for (hitr = intersections.begin(); hitr != intersections.end(); hitr++)
		{
			// the geodes are identified by name.
			osg::NodePath nodePath = hitr->nodePath;
			for (int i = 0; i < nodePath.size(); i++)
			{
				osg::ref_ptr<osg::Node> node = nodePath[i];
				if (node == NULL)
					continue;
				int index = m_EditDrawTracker->HitNode(node);
				if (index > -1)
					return index;
			}
		}
		//
		return -1;
	}

	bool EditElementTool::onKeyUp(const osgGA::GUIEventAdapter & ea)
	{
		if (m_CurEditElement)
		{
			// ɾ���ڵ�
			if (isPressKey(osgGA::GUIEventAdapter::KEY_Control_L) && ea.getKey() == osgGA::GUIEventAdapter::KEY_Delete)
			{
				GLOBE_NAME::Element* curElement = m_CurEditElement;
				CancelSelect();
				// ����ɾ���¼�
				OnDeleteElementEvent(curElement);
				return true;
			}
			//
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Delete)
			{
				bool issucess = m_EditDrawTracker->DeleCurNode();
				if (issucess)
					m_EditDrawTracker->UpdateElement();
				return issucess;
			}
				
		}
		return false;
	}

	// ��ʼ�༭��״̬��������
	void EditElementTool::setEditElement(GLOBE_NAME::Element * editElement)
	{
		bool isSucceEdit = m_EditDrawTracker->SetEditElement(editElement);
		if (!isSucceEdit)
			return;
		m_EditStateType = 1;
		setEnableSelect(false);
		m_CurEditElement = editElement;
		OnEditElementEvent(editElement);
		//��������
	}
	void EditElementTool::OnUpdateEdit(int type)
	{

	}
	void EditElementTool::CancelEdit()
	{
		if (m_EditStateType == 0)
		{
			return;
		}
		setEnableSelect(true);
		m_EditStateType = 0;
		//
		//
		m_CurEditElement = NULL;
		m_EditDrawTracker->CancelEdit();
	}

}