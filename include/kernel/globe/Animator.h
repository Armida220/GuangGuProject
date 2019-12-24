#pragma once
#include "utility.h"
#include "geometry.h"
/*****************����ģ�ͷ�װ����*******************/
GLOBE_NS

//
enum ActionState
{
	Start,
	Stop
};
//

class GS_API Animator:public Utility::GsRefObject
{
public:
	Animator();
	virtual ~Animator();
};
GS_SMARTER_PTR(Animator);
/// \brief ���㶯������
class GS_API FloatAnimator :public Animator
{
public:
	FloatAnimator(const std::vector<float>& values, float startLife, float endLife, bool mode);
	FloatAnimator(const std::vector<float>& values);
	virtual ~FloatAnimator();
	//��ȡ��ǰֵ�Ĺ���
	virtual float GetValue(float a);
	std::vector<float>& GetFloats();
	float GetStartLife();
	float GetEndLife();
protected:
	float m_StartLife;
	float m_EndLife;
	bool m_Mode;
	std::vector<float> m_Values;
	float m_DurLife;
};

GS_SMARTER_PTR(FloatAnimator);
//·��������ֵ�Ĺ���

class GS_API DynamicPathAnimator :public FloatAnimator
{
public:
	DynamicPathAnimator();
	DynamicPathAnimator(const std::vector<float>& values, float startLife, float endLife);
	~DynamicPathAnimator();
	//
	virtual GeoStar::Kernel::GsRawPoint& GetRawPoint(float a);
	void AddDynamic(const GeoStar::Kernel::GsRawPoint & point);//��̬���Ŀ���
	virtual GeoStar::Kernel::GsRawPoint&  CurRawPoint();
	 //�켣��ǰָ��ĽǶ�
	virtual float CurAngle();
protected:
	void initalPath();
protected:
	std::vector<KERNEL_NAME::GsRawPoint> m_PathPoints;
	std::vector<double> m_SubLen;//ÿ�ε�Ч�����
	std::vector<float> m_Angles;//��ǰ�Ƕ�
	double m_PathLen;//·������
	int m_Index;//
	GeoStar::Kernel::GsRawPoint m_CurPoint;
};
GS_SMARTER_PTR(DynamicPathAnimator);
//
/// \brief ����ִ���ߣ�ָ��ʱ����Ƿ�ѭ�����ŵĹ���
class GS_API AnimatorAction:public Utility::GsRefObject
{
public:
	//������ִ��ʱ����λ���룬ѭ������
	AnimatorAction(int durtion, bool isLoop);
	AnimatorAction(int durtion, int loops, bool isLoop=true);
	~AnimatorAction();
	/// \brief ����û֡��ʱ����Ϣ�Ĺ���
	virtual float Update(int64_t time);//����ʱ�䴫��
	// ��ʼ
	void Start();
	// ֹͣ
	void Stop();
	// �Ƿ�ʼ
	bool isStart();
	int GetDurtion();
	bool IsLoop();
	void reSet();
	// �����¼��Ĺ���
	UTILITY_NAME::GsDelegate<void(ActionState)> OnAnimatorEvent;
protected:
	virtual void OnUpdate(float a) = 0;
protected:
	bool m_isStarted;
	int64_t m_AniTime;
	float m_Durtion;
	bool m_isLoop;
	int m_Loops;

};
GS_SMARTER_PTR(AnimatorAction);
// �ߵ���ʽ
class GS_API LineAnimatorAction :public AnimatorAction
{
public:
	LineAnimatorAction(int durtion, bool isLoop);
	LineAnimatorAction(int durtion, int loops, bool isLoop = true);
	~LineAnimatorAction();
	// ��ͼ������
	FloatAnimator *getTextCoord();
	// ����������
	void setTextCoord(FloatAnimator* animator);
	//͸������
	FloatAnimator* getAphla();
	// ����͸������
	void setAphla(FloatAnimator* animator);
	// ��ȡ�߿����Ŷ���
	FloatAnimator* getWidthScale();
	// �����߿����Ŷ���
	void setWidthScale(FloatAnimator* animator);
	FloatAnimator* getPrevice();
	void setPrevice(FloatAnimator* animator);
protected:
	virtual void OnUpdate(float a)override;
protected:
	FloatAnimatorPtr m_TextCoordAnimator;
	FloatAnimatorPtr m_ptrAphlaAnimator;//��͸������
	FloatAnimatorPtr m_ptrLineScaleAnimator;//�߿���
	FloatAnimatorPtr m_ptrPreviceAnimator;// ��ʾ�ߵİٷֱ�
};

GS_SMARTER_PTR(LineAnimatorAction);
//
class GS_API PointAnimatorAction :public AnimatorAction
{
public:
	PointAnimatorAction(int durtion, bool isLoop);
	PointAnimatorAction(int durtion, int loops, bool isLoop = true);
	~PointAnimatorAction();
	//͸������
	FloatAnimator* getAphla();
	// ����͸������
	void setAphla(FloatAnimator* animator);
	// ��ȡ���Ŷ���
	FloatAnimator* getScale();
	// �������Ŷ���
	void setScale(FloatAnimator* animator);
	// ��ת����
	FloatAnimator* getRota();
	//������ת����
	void setRota(FloatAnimator* animator);
protected:
	virtual void OnUpdate(float a)override;
protected:
	FloatAnimatorPtr m_ptrRotaAnimator;//��ת����
	FloatAnimatorPtr m_ptrAphlaAnimator;//��͸������
	FloatAnimatorPtr m_ptrScaleAnimator;//�߿���
};

GS_SMARTER_PTR(PointAnimatorAction);

GLOBE_ENDNS