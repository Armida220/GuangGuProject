
#pragma once

#include "Element.h"
#include <GsReference.h>

GLOBE_NS

class GS_API ModelElement :public Element
{
public:
	ModelElement(std::string strUrl, double x, double y, double z);

	virtual~ModelElement();
	virtual bool Visible() ;
	virtual void Visible(bool bVisible);
	//����λ��
	virtual	void setPosition(double x, double y, double z);
	virtual void getPosition(double& x, double& y, double& z)override;
	std::string getModelUrl();
	//���λ��
	GsRawPoint3D getPosition();
	//����gsAxle����תdbAngle�Ƕ�
	void Rotate(GsRawPoint3D gsAxle, double dbAngle);
	double getdbAngle();
	//����ԭʼ��С*dbScale��
	void Scale(double dbScale);
	double getdbScale();

	void setTranslate(double x, double y, double z);

private:
	GsReferencePtr m_ptrMatrix;
	GsReferencePtr m_ptrModelNode;
	double m_dbAngle;
	double m_dbScale;
	std::string m_modelUrl;
	GsRawPoint3D m_rotaAxle;
	bool m_bVisible;
};

GS_SMARTER_PTR(ModelElement);

GLOBE_ENDNS