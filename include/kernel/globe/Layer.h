#pragma once
#include <utility.h>
#include <GsReference.h>
#include <geometry.h>

GLOBE_NS

//�ж����ݵ���Դ����
enum StoreType
{
	eLocal,
	eServer,
	eWMTS,
	eWMS,
	eWFS,
	eGeoGlobeTile,
	eReadMap
};

enum DataType
{
	eImage,
	eTerrain,
	eModel,
	eVector,
	ePlanceName,
	ePipeline,
	eOPModel,
	eUnkown,
	eFeatureClassLayer,
	eRoad
};

class GS_API Layer :public GeoStar::Utility::GsRefObject
{
public:
	Layer();
	virtual ~Layer();

	//�����Ƿ�ɼ�
	virtual void Visible(bool bVisible) = 0;
	//��ȡ�Ƿ�ɼ�
	virtual bool Visible() const = 0;
	//��ȡͼ������
	virtual DataType LayerType();
	virtual StoreType StorageType();
	//���ͼ��ID
	virtual int UID() = 0;

	//���÷�Χ
	void Range(double dXMin, double dXMax, double dYMin, double dYMax);
	void setCenter(double dLongitude, double dLatitude, double dHeight);
	//��÷�Χ
	GsBox Range();
	void getCenter(double& dLongitude, double& dLatitude, double& dHeight);

	double Longitude();
	double Latitude();
	double Height();

	double xMin();
	double xMax();
	double yMin();
	double yMax();

	std::string LayerUrl();

	int Top();
	int Bottom();

	GsReference* Handle()
	{
		return m_ptrLayerHandle.p;
	}

protected:
	double m_dXMin;
	double m_dXMax;
	double m_dYMin;
	double m_dYMax;

	double m_dLongitude;
	double m_dLatitude;
	double m_dHeigh;

	int m_nTopLevel;
	int m_nBottomLevel;

	std::string m_strLayerUrl;
	bool m_bVisible;

	DataType m_LayerType;
	StoreType m_StoreType;

	GsReferencePtr m_ptrLayerHandle;
};

GS_SMARTER_PTR(Layer);

GLOBE_ENDNS

