#pragma once
#include "AnalysisBase.h"
#include <GsReference.h>
#include <geometry.h>
GLOBE_NS

// ��������
enum DrawElementType
{
	// ���Ƶ�
	DRAWPOINT=1,
	// ������
	DRAWLINE,
	// ������
	DRAWPOLYGON,
	// ���ƾ���
	DRAWRECT
};

class GS_API DrawElmentAnalysis :public AnalysisBase
{
public:
	DrawElmentAnalysis();

	virtual ~DrawElmentAnalysis();


	 void SetEnable(bool enable);
	 void SetMonitorMouseMove(bool enable);
	 bool Enable();

	/// \brief ��ȡ���ƶ������Ҫ����С��ĸ���
	/// \return ���ػ��ƶ������Ҫ����С�����
	int MinPointCount();

	/// \brief ���û��ƶ������Ҫ��С�����
	/// \param min �����ֵ
	void MinPointCount(int min);
	/// \brief ��ȡ��Ҫ���������
	///
	int MaxPointCount();
	/// \brief ���û�����Ҫ�����ֵ
	/// \param max �����ֵ
	void MaxPointCount(int max);

	UTILITY_NAME::GsDelegate<void(const KERNEL_NAME::GsRawPoint3D&)> &OnMouseDoubleClickEvent();
	UTILITY_NAME::GsDelegate<void(const std::vector<KERNEL_NAME::GsRawPoint3D>& )> &OnDrawFinishEvent();

private:

};

GS_SMARTER_PTR(DrawElmentAnalysis);


//

class GS_API DrawRectElmentAnalysis :public DrawElmentAnalysis
{
public:
	DrawRectElmentAnalysis();
	virtual ~DrawRectElmentAnalysis();
	// ��ȡ��������
	DrawElementType GetDrawType();
	// ���û�������
	void SetDrawType(DrawElementType type);

	//�жϼ����Ƿ���
	bool isKeyPress(int key);
};

GS_SMARTER_PTR(DrawRectElmentAnalysis);
GLOBE_ENDNS