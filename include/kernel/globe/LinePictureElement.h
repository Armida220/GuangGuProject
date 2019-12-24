#pragma once
#include "Element.h"
#include <GsReference.h>
#include "geometry.h"
#include "canvas.h"

GLOBE_NS


enum TextureType
{
	//��ͼ
	REAPTE=3,
	TO_EDGE=4
};

class GS_API LinePictureElement3D : public Element
{
public:
	LinePictureElement3D(float w,float pictureH,const char* image);
	LinePictureElement3D(float w, float pictureH, const char* image,LinePictureMixType type,TextureType textureType=REAPTE);
	virtual~LinePictureElement3D();
	// ���õ�
	void setPoints(const std::vector<KERNEL_NAME::GsRawPoint3D>& points);
	// ��ӵ�
	void AddPoint(KERNEL_NAME::GsRawPoint3D& point);
	KERNEL_NAME::GsRawPoint3D GetPoint(int index);
	int PointSize();
	std::vector<KERNEL_NAME::GsRawPoint3D> GetPoints();
	float GetLineScale();
	void SetLineScale(float);
	// �ߵ����ͼƬ·��
	std::string GetImageUrl();
	// ��ȡ�߿�
	float GetLineWidth();
	// �����߿�
	void SetLineWidth(float width);
	// ��ȡ��ͼƬ�ĸ߶�
	float GetImageHeight();
	//�Ƿ�ɼ�
	virtual bool Visible();
	// ����visible �ɼ�
	virtual void Visible(bool bVisible);
	//
	void SetLineColor(const KERNEL_NAME::GsColor& color);
	KERNEL_NAME::GsColor GetLineColor();
	// ����
	void SetFixLod(float fixlod);
	// lod ��ģʽ���
	float GetFixLod();
	// ��ȡ�����ʽ�Ĺ���
	// ��ΪCOLOR ģʽ����������ߵ���ɫ����
	LinePictureMixType GetPictureMixType();
	// ���ö���ִ����
	void SetAnimatorAction(AnimatorAction* action);
	// �ߵĶ���ִ����
	AnimatorAction* GetAnimatorAction();

protected:
	void reBuild();
private:
	GsReferencePtr m_ptrLinesGeom;
	GsReferencePtr m_ptrNodeLineGeom;
	GsReferencePtr m_ptrTranForm;
	GsReferencePtr m_ptrGeode;
	std::vector<KERNEL_NAME::GsRawPoint3D> m_linePoints;
	std::string m_imageUrl;
	LinePictureMixType m_MixType;

};

GS_SMARTER_PTR(LinePictureElement3D);

GLOBE_ENDNS