#pragma once
#include "Element.h"
#include <GsReference.h>

namespace osg
{
	class StateSet;
}

GLOBE_NS

/*�����ṩ��һ��������Ƶ���Ļ���Ԫ��*/
class GS_API  StreamMovieElement :public Element
{
public:
	/*
	position������Ƶ�����ŵ�λ��
	nWidth����Ƶ��
	nHeight����Ƶ��
	dbFactor���������ӣ���Ƶ�ߴ��ȱ������ݸ�ֵ����(��ֵԽ����Ƶ���ųߴ�ԽС)
	*/
	StreamMovieElement(GsRawPoint3D position, int nWidth, int nHeight, double dbFactor);
	virtual~StreamMovieElement();

	//����λ�á���λΪ��γ�Ⱥ͸߶�
	void setPosition(GsRawPoint3D pos);
	GsRawPoint3D getPosition();

	bool Visible();
	void Visible(bool bVisible);

	/*
	gsAxle����ת�ᣬһ�������ֻ��Ҫz����ת(��GsRawPoint3D(0.0, 0.0, 1.0))
	dbDegree����ת�Ƕ�(�Ƕ���,��45��)
	*/
	void Rotate(GsRawPoint3D gsAxle, double dbDegree);

	void setRectangle(int nWidth, int nHeight);

	/*
	data��ͼƬ�ڴ��(Ŀǰֻ֧��YUV��ʽ,�����Ͽ���֧�����г�����ʽ(������ʽ��δ����)��ʹ��ffmpeg����)
	nWidth��ͼƬ��
	nHeight��ͼƬ��
	*/
	void AddImage(unsigned char* data ,int nWidth, int nHeight);

private:

	osg::StateSet* createState();

	double m_dbFactor;
	bool m_bVisible;
	GsReferencePtr m_ptrTransNode;
	GsReferencePtr m_ptrImageSequence;
	double m_xRot;// ��̬��ת��
	double m_yRot;
	double m_zRot;
};

GS_SMARTER_PTR(StreamMovieElement);

GLOBE_ENDNS