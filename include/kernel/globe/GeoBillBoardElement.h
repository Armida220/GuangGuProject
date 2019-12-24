#pragma once
#include "Element.h"
#include <canvas.h>
#include <event.h>

namespace GeoGlobe
{
	class BillBoardPicker;
}

GLOBE_NS

class Feature;
class AnimatorAction;

/*
�ṩ������ʽbillboard,��ͼ����������������һ����֧����
�ṩͼ��Ͳ��ṩͼ����ֲ�һ��
*/
class GS_API GeoBillBoardElement :public Element
{
public:
	/*
	x,y,z��λ��
	strText����ʾ�ı�(�����ṩ"\n"�Իس�)
	strIcon����ʾͼ��(����ṩ�˸�ֵ������Ĭ����ͼ���ұ߲�����һ����ͼ�����·����߰�����֧���������û�ṩ��ֵ���߻����������·����������ֱ�һ����ɫ͸���������)
	nTextCenterOffset����������˴˲������Ҳ�Ϊ-100�������ֻ���ͼ��ˮƽ������ʾ(Ĭ��������ͼ���Ҳ�)��ֵ����Ϊ�����ڴ�ֱ�����ƫ����������λ��
	nMinLod����С�ɼ����루�����������
	nMaxLod�����ɼ����루�����������
	*/
	GeoBillBoardElement(double x, double y, double z, std::string strText, std::string strIcon = "", int nTextCenterOffset = -100, int nMinLod = 0, int nMaxLod = INT_MAX);

	virtual void setPosition(double x, double y, double z);
	virtual void getPosition(double& x, double& y, double& z);

	virtual ~GeoBillBoardElement();

	void Text(std::string strText);
	std::string Text();

	//����ͼ��
	void Icon(std::string strIcon);
	//��ȡͼ��url
	std::string Icon();
	
	//����ͼ��
	void setImage(unsigned char* ptrData,int nWidth,int nHeight);

	//Ĭ�ϻ��Զ�����C:\Windows\FontsĿ¼�µ�����,����΢���ź�msyh.ttcֻ��Ҫ��������������(ע����Ҫ��׺��)�磺youclass->Font("msyh.ttc")
	//Ҳ�����Լ�ָ������·�����磺youclass->Font("./Font/msyh.ttc")
	void Font(std::string strFont);
	std::string Font();

	void CoverAutoHide(bool bAutoHide);
	bool CoverAutoHide();

	//����λ��
	void TextAlignment(const Alignment& alignment);
	//��ȡͼ��λ��
	Alignment TextAlignment();

	//���ñ�����ɫ��ֻ����û��ͼ���������Ч
	void setBackGrandColor(const KERNEL_NAME::GsColor& color);
	KERNEL_NAME::GsColor getBackGrandColor();

	//���ñ�����ɫ��ֻ����û��ͼ���������Ч
	void setOutLineColor(const KERNEL_NAME::GsColor& color);
	KERNEL_NAME::GsColor getOutLineColor();

	//��������ɫ
	void setLineColor(const KERNEL_NAME::GsColor& color);
	KERNEL_NAME::GsColor getLineColor();

	//�������߽Ƕ�,�ýǶ�Ϊ�����ˮƽ������ʱ��нǣ������Ϊ90����Ϊ��ֱ��
	void setPolylineAngle(const double& dbAngle);
	//������߽Ƕ�
	double getPolylineAngel();

	//���õײ��ߴ��߳���
	void setBottomLen(const double& dbBottomLen);
	//��õײ��ߴ��߳���
	double getBottomLen();

	//�������߳���
	void setPolylineLen(const double& dbPolylineLen);
	//������߳���
	double getPolylineLen();

	void HightLight();
	void CancelHightLight();

	// ���ö���ִ����
	void SetAnimatorAction(AnimatorAction* action);
	// ��ö���ִ����
	AnimatorAction* GetAnimatorAction();

	//������Ӱ��ɫ
	void setShadowColor(const KERNEL_NAME::GsColor& color);
	//�õ���Ӱ��ɫ
	KERNEL_NAME::GsColor getShadowColor();
	//������Ӱƫ��
	void setShadowOffset(const double& dbShadowOffset);
	//�õ���Ӱƫ��
	double getShadowOffset();
	//������Ӱλ��
	void setShadowPos(const ShadowStyle& m_eShadowPos);
	//�õ���Ӱλ��
	ShadowStyle getShadowPos();

	//�����ı���ɫ��r[0-255],g[0-255],b[0-255],a[0-1]
	void TextColor(int r ,int g, int b, int a = 1.0);
	void TextColor(KERNEL_NAME::GsColor color);
	KERNEL_NAME::GsColor TextColor();

	void TextSize(double dbSize);
	double TextSize();

	//�����ı�������ɫ��r[0-255],g[0-255],b[0-255],a[0-1]��ע�⣡������size����35ʱ����Ч�����쳣
	void TextHaloColor(int r, int g, int b, int a = 1.0);
	//�����Ƿ���Զ�̬���±����ı�
	void Dynamic(bool bDynamic);
	// ����lod
	void setLod(int minLod = 0, int maxLod = INT_MAX);

	/*�����û�����*/
	void setValue(std::string key, std::string value);
	/*ȡ���û�����*/
	void getValue(std::string& key, std::string& value);

	GsReference* LodHandle()
	{
		return m_ptrLodElement.p;
	}

	bool Visible();
	void Visible(bool bVisible);

	/*����ʰȡ*/
	static void StartPick();
	/*����ʰȡ*/
	static void EndPick();
	/*��ʰȡί��*/
	static UTILITY_NAME::GsDelegate<void(GLOBE_NAME::Feature*)>& OnPicked();
	/*����ί��*/
	UTILITY_NAME::GsDelegate<void(Element*)>& Updata();

protected:

	void CreateGeoBillboard(int nMinLod, int nMaxLod, int nTextCenterOffset);

	std::string m_strText;
	std::string m_strIcon;

	static GeoGlobe::BillBoardPicker * m_Picker;
	static bool m_bIsPick;

	Alignment m_textAlignment;

	GsReferencePtr m_ptrLodElement;
	bool m_bVisible;
	bool m_bUpdateCallBack;
};

GS_SMARTER_PTR(GeoBillBoardElement);

GLOBE_ENDNS
