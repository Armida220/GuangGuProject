#pragma once
#include "QtFramework/geoqtframework_global.h"
#include <utility.h>
#include <map.h>


namespace GeoStar
{
	namespace Kernel
	{
		namespace QT
		{
			class GsGeoSpace2D;
		}
	}
}

GLOBE_NS

//ƽ��tracker
class GEOQTFRAMEWORK_EXPORT GsZoomPanTracker :public GsSymbolTracker
{
public:
	GsZoomPanTracker(GeoStar::Kernel::QT::GsGeoSpace2D* pMap);
	virtual ~GsZoomPanTracker();
	/// \brief ������갴����Ϣ
	virtual void OnMouseDown(GsButton eButton, int nKeyboard, const Utility::GsPT& pt)override;
	/// \brief ������굯����Ϣ
	virtual void OnMouseUp(GsButton eButton, int nKeyboard, const Utility::GsPT& pt)override;
	/// \brief ��������ƶ���Ϣ
	virtual void OnMouseMove(GsButton eButton, int nKeyboard, const Utility::GsPT& pt)override;
	//���ֵķŴ����С�Ĺ���
	virtual void OnMouseWheel(GsButton eButton, int nDelta, int nKeyboard, const Utility::GsPT& pt)override;

protected:
	//������Ⱦ��ͼ����
	void UpdateMap();
	//��ȡ��ͼ���
	GeoStar::Kernel::QT::GsGeoSpace2D* GeoSpace2D()const;
private:
	bool m_isMoved;
	GeoStar::Kernel::QT::GsGeoSpace2D * m_ptrGeoSpace2D;
};
//
class GEOQTFRAMEWORK_EXPORT GsPolylineTracker :public GsZoomPanTracker
{
public:
	GsPolylineTracker(GeoStar::Kernel::QT::GsGeoSpace2D* pMap);
	~GsPolylineTracker();
	//����
	virtual void Reset()override;
	//���ƶ�������ֵ
	int MaxPointCount()const;
	//���ö�������ֵ
	void MaxPointCount(int maxpoint);
	//��ȡ��Ҫ�����ٵ�
	int MinPointCount()const;
	//������Ҫ����С��
	void MinPointCount(int minPoint);
protected:
	/// \brief ������갴����Ϣ
	virtual void OnMouseDown(GsButton eButton, int nKeyboard, const Utility::GsPT& pt)override;
	/// \brief ������굯����Ϣ
	virtual void OnMouseUp(GsButton eButton, int nKeyboard, const Utility::GsPT& pt)override;
	/// \brief ��������ƶ���Ϣ
	virtual void OnMouseMove(GsButton eButton, int nKeyboard, const Utility::GsPT& pt)override;
	/// tracker���ƺ���������ͨ�����Ǵ˺����������ݡ�
	virtual void OnTrackerDraw(GsDisplay* pDisp)override;
	//����Tracker�Ĺ���
	virtual void FinishTracker();
	//����
	virtual void OnFinishTracker(const std::vector<GsRawPoint> & points);
	//���������
	virtual bool MouseLeftClick(GsButton eButton, int nKeyboard, const Utility::GsPT& pt);
	//�Ҽ���������
	virtual bool MouseRightClick(GsButton eButton, int nKeyboard, const Utility::GsPT& pt);
	//
	virtual bool OnDraw(GsDisplay* pDisp, const std::vector<GsRawPoint> & points);
private:
	std::vector<GsRawPoint> m_Points;
	int m_MaxCount;//���
	int m_MinCount;//��С������
	long m_MouseTime;
	bool m_isNeedAdd;
	bool m_IsMouseDown;
	float m_DownX;
	float m_DownY;
	bool m_isFinished;
};
//�������������
enum GEOQTFRAMEWORK_EXPORT GsMeasureType
{
	//���Ȳ���
	Length,
	//�������
	Area
};

//����Tracker��д
class GEOQTFRAMEWORK_EXPORT GsMeasureTracker :public GsPolylineTracker
{
public:
	GsMeasureTracker(GeoStar::Kernel::QT::GsGeoSpace2D* pMap);
	~GsMeasureTracker();
	//���ò�������
	GsMeasureType MeasureType()const;
	//��ȡ��������
	void MeasureType(GsMeasureType type);
protected:
	//�Ҽ���������
	virtual bool MouseRightClick(GsButton eButton, int nKeyboard, const Utility::GsPT& pt);
	virtual bool OnDraw(GsDisplay* pDisp, const std::vector<GsRawPoint> & points)override;
	//���Ƴ��Ȳ���
	void OnDrawLength(GsDisplay* pDisp, const std::vector<GsRawPoint> & points);
	//�����������
	void OnDrawArea(GsDisplay* pDisp, const std::vector<GsRawPoint> & points);
	//�����ı���ֵ
	void OnDrawText(GsDisplay* pDisp, const std::string& txt, const Utility::GsPTF& pt);

private:
	GsMeasureType m_MeasureType;
	GsSimpleLineSymbolPtr  m_ptrLineSymbol;
	GsSimpleFillSymbolPtr m_ptrFillSymbol;
	GsGeodesic * m_ptrGsGeoLine;
	GsGeodesicPolygon * m_ptrGsGeodesicPoly;
	GsSolidBrushPtr m_ptrTextBrush;
	GsStringFormatPtr m_ptrTextFormat;

};

//���Ƶ�Tracker��д���Ƶ������ͼ�ε�Tracker��д
class GEOQTFRAMEWORK_EXPORT GsDrawSymbolTracker :public GsPolylineTracker
{
public:
	GsDrawSymbolTracker(GeoStar::Kernel::QT::GsGeoSpace2D* pMap);
	~GsDrawSymbolTracker();
	/// \brief Geometry������ɵ��¼�
	Utility::GsDelegate<void(GsGeometry*)> OnDrawSymbolFinished;
protected:
	virtual bool OnDraw(GsDisplay* pDisp, const std::vector<GsRawPoint> & points)override;
	//�Ҽ���������
	virtual bool MouseRightClick(GsButton eButton, int nKeyboard, const Utility::GsPT& pt) override;
	//�����Ĵ������
	virtual void OnFinishTracker(const std::vector<GsRawPoint> & points)override;
	//
};


GLOBE_ENDNS
