#pragma once
#include <AnalysisBase.h>
//��б�����������
GLOBE_NS

class GS_API AreaAnalysis3D :public AnalysisBase
{
public:
	AreaAnalysis3D();

	virtual ~AreaAnalysis3D();

	UTILITY_NAME::GsDelegate<void(double)>& OnFinish();
private:

};

GS_SMARTER_PTR(AreaAnalysis3D);

GLOBE_ENDNS