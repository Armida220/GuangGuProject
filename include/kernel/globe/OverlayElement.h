
#pragma once
#include "Element.h"
#include <GsReference.h>
#include <Layer.h>

namespace osg
{
	class Node;
}

GLOBE_NS

/*
���Խ�����Ԫ����Ⱦ��������������ͼ�������ϣ����罫��Ƶ����Ԫ��������б������
*/
class GS_API OverlayElement :public Element
{
public:

	/*
	ע�⣬��ͶӰͼ��ptrBaseLayer�ᵱ��OverlayElement���ӽڵ���Ⱦ��
	���Բ���Ҫ�ӵ�LayerBox����ptrBaseLayer�ᱻ��Ⱦ���β��һḲ��ͶӰЧ��
	*/
	OverlayElement(Element* ptrElement, Layer* ptrBaseLayer);

	/*
	����ͶӰ��������򵥵�Ͷ��Y�᷽��(0.0,1.0,0.0)
	�������ȷ֪��ҪͶ�ķ�������ô˷���
	*/
	void setProjectDirection(double x, double y, double z);
	/*
	����ӽڵ㼴���ںϽڵ�,������б����
	ע�⣺�ⲿ����Ҫ������Ŀǰֻ���ڲ������Ժ���ܻ���ģ�
	*/
	static void addChild(osg::Node* ptrNode);
	
	//��Ӵ�ͶӰ��Ԫ�أ�����һ����Ƶ
	void addOverlaySubgraph(Element* ptrElement);

	//�Ƴ���ͶӰ��Ԫ��
	void removeOverlaySubgraph(Element* ptrElement);
	//�Ƴ������ӽڵ㣬��������ӵ���б����
	void removeChildren();

	virtual~OverlayElement();

	static GsReferencePtr m_ptrOverlayNode;

};

GS_SMARTER_PTR(OverlayElement);

GLOBE_ENDNS