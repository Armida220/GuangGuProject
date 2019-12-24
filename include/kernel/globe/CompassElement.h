#pragma once
#include "Element.h"
#include <GsReference.h>

GLOBE_NS

class GS_API CompassElement : public Element
{
public:

	void setRotation(double angle);

	virtual void Visible(bool bVisible);
	virtual bool Visible();

	/*����ڴ������Ͻǵ�λ��,zֵ���ᱻ����*/
	virtual void setPosition(double x, double y, double z);
	virtual void getPosition(double& x, double& y, double& z);

	/*����ָ�����������Ļ��λ��*/
	void setAlignment(Alignment Horiz, Alignment Vert);

	CompassElement();
	virtual~CompassElement();

protected:
	void creatCompass();
	void Build();

	GsReferencePtr m_ptrBoxHandle;
	
};
GS_SMARTER_PTR(CompassElement);

GLOBE_ENDNS