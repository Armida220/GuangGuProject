#pragma once
#include <AnalysisBase.h>

GLOBE_NS

class Layer;

//������б�����������
class GS_API OsgbProfileAnalysis :public AnalysisBase
{
public:
	/*
	ptrLayer����бͼ��
	bAutoCalc���Ƿ��Զ����㣬Ĭ��Ϊtrue�������Ϊfalse����������ʱ������㣬��ʱ��Ҫ�ֶ�����Calculate����
	dbStep����ֵ�ܶȣ�Ĭ��Ϊһ�٣���ֵԽ����Խ�ܡ����Խ׼ȷ����ʱԽ��
	*/
	OsgbProfileAnalysis(Layer* ptrLayer, bool bAutoCalc = true, double dbStep = 100.0);

	/*
	dbStep����ֵ�ܶȡ���ֵԽ����Խ�ܡ����Խ׼ȷ����ʱԽ��
	*/
	void Calculate(double dbStep = 100.0);

	virtual ~OsgbProfileAnalysis();

	//���ƽ����¼�
	UTILITY_NAME::GsDelegate<void()>& OnDrawFinish();
	//�������
	UTILITY_NAME::GsDelegate<void(const std::vector<double>&, const std::vector<double>&)>& OnCalcFinish();

private:

};

GS_SMARTER_PTR(OsgbProfileAnalysis);

GLOBE_ENDNS