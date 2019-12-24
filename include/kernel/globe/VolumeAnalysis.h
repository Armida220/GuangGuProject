#pragma once
#include <AnalysisBase.h>

GLOBE_NS

class Layer;

//������б��������������������ڱȽϺ�ʱ�ڲ�ʹ�ö��̼߳���
class GS_API VolumeAnalysis :public AnalysisBase
{
public:
	/*
	ptrLayer����бͼ��
	bAutoCalc���Ƿ��Զ����㣬Ĭ��Ϊtrue�������Ϊfalse����������ʱ������㣬��ʱ��Ҫ�ֶ�����Calculate����
	dbElevation�����θ߶ȣ�������Դ˺���Ϊ��׼���㣬Ĭ��Ϊ0.0
	*/
	VolumeAnalysis(Layer* ptrLayer, bool bAutoCalc = true, double dbElevation = 0.0);

	/*
	dbElevation�����θ߶ȣ�������Դ˺���Ϊ��׼����
	*/
	void Calculate(double dbElevation);

	virtual ~VolumeAnalysis();

	//���ƽ����¼�
	UTILITY_NAME::GsDelegate<void()>& OnDrawFinish();
	//�������
	UTILITY_NAME::GsDelegate<void(double)>& OnCalcFinish();

private:

};

GS_SMARTER_PTR(VolumeAnalysis);

GLOBE_ENDNS