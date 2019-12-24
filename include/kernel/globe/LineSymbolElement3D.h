#pragma once
#include "Element.h"
#include <canvas.h>
#include <GsReference.h>

GLOBE_NS

enum Mode
{
	LINES,
	LINE_STRIP,
	LINE_LOOP,
	POLYGON
};

class GS_API LineSymbolElement3D : public Element
{
public:
	LineSymbolElement3D(Mode model);
	virtual~LineSymbolElement3D();
	void AddPoint(double x, double y, double z);
	const std::vector<KERNEL_NAME::GsRawPoint3D> getPoints();
	//��ɫ��r[0-255],g[0-255],b[0-255],a[0-255]
	void setColor(int r, int g, int b, int a = 255.0);
	KERNEL_NAME::GsColor getColor();
	//�����߿�
	void setLineWidth(int nSize);
	int getLineWidth();

	/*
	gsAxle����ת�ᣬһ�������ֻ��Ҫz����ת(��GsRawPoint3D(0.0, 0.0, 1.0))
	dbDegree����ת�Ƕ�(�Ƕ���,��45��)
	*/
	void Rotate(GsRawPoint3D gsAxle, double dbDegree);

	void Finish();

private:
	KERNEL_NAME::GsRawPoint3D m_origin;
	GsReferencePtr m_ptrVertex;
	GsReferencePtr m_ptrDrawArray;
	GsReferencePtr m_ptrLinesGeom;
	GsReferencePtr m_ptrColors;

	int m_nSize;

	std::vector<KERNEL_NAME::GsRawPoint3D> m_points;

};

GS_SMARTER_PTR(LineSymbolElement3D);

GLOBE_ENDNS