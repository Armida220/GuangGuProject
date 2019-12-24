#pragma once
#include "Element.h"
#include <canvas.h>
#include <event.h>
#include <Feature.h>

namespace GeoGlobe
{
	class BillBoardPicker;
}

GLOBE_NS

/*
�ṩһ������billboard��
��billboardֻ����һ��ͼ������֣��������ǵ����λ�ÿ�������
*/
class GS_API BillBoardElement :public Element
{
public:
	/*
	x,y,z��λ��
	strText����ʾ�ı�
	strIcon����ʾͼ��
	nMinLod����С�ɼ����루�����������
	nMaxLod�����ɼ����루�����������
	*/
	BillBoardElement(double x, double y, double z, std::string strText, std::string strIcon = "", int nMinLod = 0, int nMaxLod = INT_MAX);
	
	virtual void setPosition(double x, double y, double z);
	virtual void getPosition(double& x, double& y, double& z);

	/*�����û�����*/
	void setValue(std::string key,std::string value);
	/*ȡ���û�����*/
	void getValue(std::string& key, std::string& value);

	virtual ~BillBoardElement();
	
	//����ͼ��
	void Icon(std::string strIcon);
	//��ȡͼ��url
	std::string Icon();
	//ͼ��λ��
	void IconAlignment(Alignment alignment);
	//��ȡͼ��λ��
	Alignment IconAlignment();

	void Text(std::string strText);
	std::string Text();

	//����ϵͳ��Ҫ���������Ȼ������д��simhei.ttf
	void Font(std::string strFont);
	std::string Font();
	
	void CoverAutoHide(bool bAutoHide);
	bool CoverAutoHide();

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

	//������Ӱ��ɫ
	void setShadowColor(const KERNEL_NAME::GsColor& color);
	//�õ���Ӱ��ɫ
	const KERNEL_NAME::GsColor& getShadowColor();
	//������Ӱƫ��
	void setShadowOffset(const double& dbShadowOffset);
	//�õ���Ӱƫ��
	const double& getShadowOffset();
	//������Ӱλ��
	void setShadowPos(const ShadowStyle& m_eShadowPos);
	//�õ���Ӱλ��
	const ShadowStyle& getShadowPos();
	// ����lod
	void setLod(int minLod=0, int maxLod=INT_MAX);

	// ���ö���ִ����
	void SetAnimatorAction(AnimatorAction* action);
	// �ߵĶ���ִ����
	AnimatorAction* GetAnimatorAction();

	/*����ʰȡ*/
	static void StartPick();
	/*����ʰȡ*/
	static void EndPick();

	//void setText(double x, double y, double z);

	bool Visible();
	void Visible(bool bVisible);

	GsReference* LodHandle()
	{
		return m_ptrLodElement.p;
	}

	/*��ʰȡί��*/
	static UTILITY_NAME::GsDelegate<void(GLOBE_NAME::Feature*)>& OnPicked();
	/*����ί��*/
	UTILITY_NAME::GsDelegate<void(Element*)>& Updata();

protected:

	void CreateLabel(int dbMinLod , int dbMaxLod );

	static GeoGlobe::BillBoardPicker * m_Picker;
	static bool m_bIsPick;

	std::string m_strText;
	std::string m_strIcon;


	GsReferencePtr m_ptrLodElement;
	bool m_bVisible;
	bool m_bUpdateCallBack;
	Alignment m_iocnAlignment;
};

GS_SMARTER_PTR(BillBoardElement);

GLOBE_ENDNS
