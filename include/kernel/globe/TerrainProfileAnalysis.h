#pragma once
#include <AnalysisBase.h>

GLOBE_NS

class GS_API TerrainProfileAnalysis :public AnalysisBase
{
public:
	TerrainProfileAnalysis();

	virtual ~TerrainProfileAnalysis();

	/// \brief ����������֮����¼�
	Utility::GsDelegate<void(std::list<double>&, std::list<double>&, AnalysisBase*)> OnTerrainAnalysisEvents;

// 	std::vector <double> GetElevationVec();
// 	std::vector <double> GetDistanceVec();

 private:
 	void OnFinishListener(std::list <double>&, std::list<double>&);
};

GS_SMARTER_PTR(TerrainProfileAnalysis);

GLOBE_ENDNS