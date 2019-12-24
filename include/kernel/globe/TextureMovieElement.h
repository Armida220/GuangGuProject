
#pragma once
#include "Element.h"
#include <GsReference.h>

GLOBE_NS

enum TexturePlane
{
	XYPlane,
	XZPlane
};

/*
������ƵԪ�أ��������������ϲ�����Ƶ(ֻ֧�ֱ���)
*/
class GS_API TextureMovieElement :public Element
{
public:
	/*
	strURL����Ƶ·��
	position����Ƶλ��(��γ��)
	dbScale������ֵ(��ֵԽ����Ƶ�ߴ�ԽС)
	plane��ָ��ƽ��(Ĭ����XYƽ�棬�������XZƽ���������)
	*/
	TextureMovieElement(std::string strURL, GsRawPoint3D position, double dbScale = 60.0, TexturePlane plane = XYPlane);
	const TexturePlane& getTexturePlane();
	
	//����λ�á���λΪ��γ�Ⱥ͸߶�
	void setPosition(GsRawPoint3D pos);
	GsRawPoint3D getPosition();

	/*
	gsAxle����ת�ᣬһ�������ֻ��Ҫz����ת(��GsRawPoint3D(0.0, 0.0, 1.0))
	dbDegree����ת�Ƕ�(�Ƕ���,��45��)
	*/
	void Rotate(GsRawPoint3D gsAxle,double dbDegree);

	virtual~TextureMovieElement();

private:

	GsReferencePtr m_ptrTransNode;
	TexturePlane m_eTexturePlane;
};

GS_SMARTER_PTR(TextureMovieElement);

GLOBE_ENDNS