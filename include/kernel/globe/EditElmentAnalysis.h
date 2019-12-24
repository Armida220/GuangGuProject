#pragma once
#include "AnalysisBase.h"
#include <GsReference.h>
#include <geometry.h>

GLOBE_NS

class Element;
// �༭���ߣ�����ʹ�ÿ���ѡ�ж��󲢽��б༭
class GS_API EditElmentAnalysis :public AnalysisBase
{
public:
	EditElmentAnalysis();

	virtual ~EditElmentAnalysis();


	 void SetEnable(bool enable);
	 void SetOpenMouseMove(bool enable);
	 bool Enable();
	 // ����ѡ�в��༭��element 
	 void SetSelectElment(Element* edit,bool isEvent);

	UTILITY_NAME::GsDelegate<void(GLOBE_NAME::Element*, GLOBE_NAME::Element*)>& OnSelectEvent();

	UTILITY_NAME::GsDelegate<void(GLOBE_NAME::Element*)>&OnEditElementEvent();
	// �����༭����Ϣ�¼�
	UTILITY_NAME::GsDelegate<void(GLOBE_NAME::Element*)>&OnEndEditElementEvent();
	// ɾ��element ����Ĺ���
	UTILITY_NAME::GsDelegate<void(GLOBE_NAME::Element*)>& OnDeleteElementEvent();
private:

};

GS_SMARTER_PTR(EditElmentAnalysis);

GLOBE_ENDNS