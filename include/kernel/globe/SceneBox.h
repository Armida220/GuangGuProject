#pragma once
#include <utility.h>
#include <geometry.h>

GLOBE_NS

class GS_API SceneBox :public GeoStar::Utility::GsRefObject
{
public:
	SceneBox();

	/*�жϵ�ǰ����Ƿ����*/
	bool IsPositive();

	/*ǿ���������̬��������������������κ���ת*/
	void PositiveAngle(double dbTime = 2.0);

	/*�ָ�����֮ǰ����̬*/
	void RestoreAngle(double dbTime = 2.0);

	/*�����Ƿ�̶��ӽǣ�������ת*/
	void setFixedAngle(const bool& bFixedAngle);

	/*����Ƿ�̶��ӽ�*/
	bool getFixedAngle();

	/*�����������������С����*/
	void setMinMaxDistance(double dbMinDistance = 1.0,double dbMaxDistance = DBL_MAX);

	/*����������������С����*/
	void getMinMaxDistance(double& dbMinDistance, double& dbMaxDistance);
	/**���õ��ε���С�߶�ֵ**/
	void setTerrainMinimumDistance(double minDistance);
	/**��ȡ���ε���С�߶�ֵ*/
	double getTerrainMinimumDistance();

	/*�ָ�������ά����״̬*/
	void Reset();

	void setHomePosition(const KERNEL_NAME::GsRawPoint3D& point);
	KERNEL_NAME::GsRawPoint3D& getHomePosition();

	/*��Χ��������*/
	void RangeFlyTo(double dXMin, double dXMax, double dYMin, double dYMax);

	/*��Χֱ�ӷ���*/
	void RangeGoTo(double dXMin, double dXMax, double dYMin, double dYMax);

	/*�㶯������*/
	void PointFlyTo(double dLongitude, double dLatitude, double dHeight);

	/*��ֱ�ӷ���*/
	void PointGoTo(double dLongitude, double dLatitude, double dHeight);

	/*
	��ֵ����
	dLongitude������
	dLatitude��γ��
	dHeight���߶�
	dHeading�������
	dPitch��������
	dRange�������߶�
	dTime������ʱ��
	*/
	void InterpolateFlyTo(double dLongitude, double dLatitude, double dHeight,double dHeading ,double dPitch, double dRange,double dTime);

	/*
	��õ�ǰ�ӽ�λ�ú���̬
	dLongitude������
	dLatitude��γ��
	dHeight���߶�
	dHeading�������
	dPitch��������
	dRange�������߶�
	*/
	void getViewpoint(double& dLongitude, double& dLatitude, double& dHeight, double& dHeading, double& dPitch, double& dRange);

	/*ͨ����Χ�õ������ĸ߶�*/
	double RangeToAltitude(double dxMin, double dxMax, double dyMin, double dyMax);

	/*�õ�ȫͼ��Χ*/
	void ViewExtent(double& dxMin, double& dxMax, double& dyMin, double& dyMax);

	/*ͨ����һ������н�������*/
	double HalfAngle(double dbAngle);

	/*�Ƿ�������*/
	void ThrowingEnable(bool bThrowingEnable);

	/*��ù���״̬*/
	bool ThrowingEnable();

	/*��γ��ת��Ļ����*/
	void LonLat2Window(double dbLon, double dbLat, double dbHeight, double& windowX, double& windowY);

	/*��Ļ����ת��γ��*/
	void Window2LonLat(double windowX, double windowY, double &dbLon, double& dbLat, double& dbHeight);

	/*��γ��ת��������*/
	void LonLat2World(double dbLon, double dbLat, double dbHeight, double& worldx, double& worldy,double& worldz);

	/*����ȷ����ת���������б��ƫ������*/
	void CorrectPosByOblique(KERNEL_NAME::GsRawPoint3D& point);

	/*�������б��ƫ������ת������ȷ����*/
	void DeCorrectPosByOblique(KERNEL_NAME::GsRawPoint3D& point);

	/*�õ���ǰ��������ĸ߶�*/
	double DistanceFromCameraToGround();

	/*�õ���ǰ����������������ת��,�õ����ǽǶ�ֵ*/
	double CameraNorthAngle();

	virtual ~SceneBox();

private:

	double m_dPreHeading;
	double m_dPrePitch;
};

GS_SMARTER_PTR(SceneBox);

GLOBE_ENDNS
