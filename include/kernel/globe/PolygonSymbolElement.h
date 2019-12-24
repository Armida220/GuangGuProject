#pragma once
#include "Element.h"
#include <canvas.h>
#include <globe/GsReference.h>

GLOBE_NS
// ����������
class GS_API PolygonSymbolElement : public Element
{
public:

	PolygonSymbolElement();
	virtual~PolygonSymbolElement();
	void AddPoint(double x, double y, double z);
	//����ɫ��r[0-255],g[0-255],b[0-255],a[0-255]
	//void setLineColor(int r, int g, int b, int a = 255);
	void setLineColor(const KERNEL_NAME::GsColor& lineColor);
	// ��ȡ�ߵ���ɫ
	KERNEL_NAME::GsColor getLineColor();
	//�������ɫ��r[0-255],g[0-255],b[0-255],a[0-255]
	//void setFillColor(int r, int g, int b, int a = 255);
	void setFillColor(const KERNEL_NAME::GsColor& fillcolor);
	// ��ȡ�������ɫ
	KERNEL_NAME::GsColor getFillColor();
	// ������ɫ����
	void setFaceColor(const KERNEL_NAME::GsColor& faceColor);
	//��ȡ������ɫ��
	KERNEL_NAME::GsColor getFaceColor();
	//��ȡ����߶�,Ĭ�ϸ߶�Ϊ0 ����ʾ����
	void setFaceHeight(float height);
	//��ȡ����߶�
	float getFaceHeight();
	// �����Ƿ��ڸǵ�����
	bool isDepthTest();
	// �����Ƿ��ڵ��Ĺ���
	void setDepthTest(bool cover);
	//void ClearFillColor();
	// �����߿�
	//void setLineSize(int nSize);
	virtual bool Visible();
	virtual void Visible(bool bVisible);
	// �����߿�
	void setLineWidth(float width);
	//��ȡ�߿�
	float getLineWidth();
	
	// ��ȡ��������
	const std::vector<KERNEL_NAME::GsRawPoint3D>& getPoints();
	// ����һϵ�е������
	void setPoints(const std::vector<KERNEL_NAME::GsRawPoint3D>& points);

protected:
	// 
	void reBuild();

protected:
	std::vector<KERNEL_NAME::GsRawPoint3D> m_Points;
	KERNEL_NAME::GsColor m_FillColor;
	KERNEL_NAME::GsColor m_LineColor;
	KERNEL_NAME::GsColor m_FaceColor;//������ɫ
	float m_LineWidth;
	float m_VerFaceHeight;//����߶�
	bool m_isDepthTest;// �Ƿ����ڵ�
	GsReferencePtr m_ptrLinesGeom;
	GsReferencePtr m_ptrPolygonGeom;//���
	GsReferencePtr m_ptrFacePolyGeom;//������Ƶ�
	GsReferencePtr m_ptrGeode;
};

GS_SMARTER_PTR(PolygonSymbolElement);

GLOBE_ENDNS