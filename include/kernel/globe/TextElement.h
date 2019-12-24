#pragma once
#include "Element.h"
#include <canvas.h>
#include <GsReference.h>

GLOBE_NS

class GS_API TextElement : public Element
{
public:
	TextElement(double x, double y, double z, std::string strText, int nMinLod = 0, int nMaxLod = INT_MAX);
	virtual~TextElement();

	void setText(std::string strText);
	//����UTF-8���ַ���
	std::string getText();

	//��ɫ��r[0-255],g[0-255],b[0-255],a[0-255]
	void setColor(int r, int g, int b, int a);
	KERNEL_NAME::GsColor getColor();

	//�������ִ�С
	void setTextSize(float fSize);
	float getTextSize();

	void setPosition(double x, double y, double z);
	KERNEL_NAME::GsRawPoint3D getPosition();
	virtual void getPosition(double& x, double& y, double& z)override;

	virtual bool Visible() ;
	virtual void Visible(bool bVisible);
	/*
	gsAxle����ת�ᣬһ�������ֻ��Ҫz����ת(��GsRawPoint3D(0.0, 0.0, 1.0))
	dbDegree����ת�Ƕ�(�Ƕ���,��45��)
	*/
	void Rotate(GsRawPoint3D gsAxle, double dbDegree);
	double getdbAngle();

private:
	GsReferencePtr m_ptrTextRef;
	GsReferencePtr m_ptrTransRef;
	GsReferencePtr m_ptrLocatorRef;
	double m_dbAngle;
	float m_fSize;
};

GS_SMARTER_PTR(TextElement);

GLOBE_ENDNS