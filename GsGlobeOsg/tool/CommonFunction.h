#pragma once
#include <Tool/CommonStruct.h>
#include <vector>

//#ifdef MGDBACCESS_EXPORTS
//#define MGDBACCESS_INTERFACE __declspec(dllexport)
//#else
//#define MGDBACCESS_INTERFACE __declspec(dllimport)
//#endif
using namespace GG;
class  CCommonFunction
{
public:
	CCommonFunction(void);
	~CCommonFunction(void);

	//�ͷ���dll������ڴ�ռ�
	void FreeDllNewedMem(char* pMem);

	//����24�ֽڵ�ΨһKey
	static bool GenUniqueKey(unsigned char* strKey);

	//�Բ����н��б���
	static long long TileCoding(int level, int row, int col);
	//�Ա�����н���,�õ�������ֵ
	static bool TileUnCoding(long long tKey, int& level, int& row, int& col);

	//����������Ƭ�ֱ���
	static double GetZeroLevelTileSpan(double cellRes, int tileSize=256, int levelNums=1);

	//������Ƭ����Χ
	static GeoBox GetTileRange(long long tileKey, double zeroTileSpanX=180.0f, double zeroTileSpaY=180.0f, double xOrigin=-180.0f, double yOrigin=90.0f);

	//�����л��б���ֵ
	static unsigned long GetRowOrCol(const GG::GeoPoint& pt, int levelNo=0, double zeroTileSpan=180.0f, double xOrigin=-180.0f, double yOrigin=90.0f);

	//��������ͽ��������������ر���ֵ
	static long long GetTileKey(const GG::GeoPoint& pt, int levelNo=0, double zeroTileSpanX=180.0f, double zeroTileSpanY=180.0f, double xOrigin=-180.0f, double yOrigin=90.0f);
	//������Χ�ͽ��������������ر���ֵ����
	static std::vector<long long> GetTileKeySet(const GeoBox& box, int levelNo=0, double zeroTileSpanX=180.0f, double zeroTileSpanY=180.0f, double xOrigin=-180.0f, double yOrigin=90.0f);

//360�ȱ�׼����������
	static int StdGetLevelNo(double cellRes, int cellSize=256);
	static double StdGetCellRes(double cellRes, int cellSize=256);
	static long long StdGetTileKey(int level, const GG::GeoPoint& pt);
};

