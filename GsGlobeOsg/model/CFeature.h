//********************************************************************************** 
//** �ļ����ƣ�Feature.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� Ҫ���ඨ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-7
//********************************************************************************** 
#ifndef _FEATURE_H_
#define _FEATURE_H_

#include <osg/Referenced>
#include <string>
#include <vector>
#include <fstream>
#include "Buffer.h"
#include <osg/Vec3d>
#include "CT3D_Vertex3d.h"


//typedef struct tagLocation
//{
//	union
//	{  
//		struct
//		{
//			double dLongitude;//����
//			double dLatitude;//γ��
//			double dElevation;//�߳�
//		};
//
//		struct
//		{
//			double X,Y,Z;
//		};
//		struct
//		{
//			double dblX,dblY,dblZ;
//		};
//		struct
//		{
//			double x,y,z;
//		};
//	}; 
//
//}Location;//��λ
//
//typedef struct tagRotation
//{
//	union
//	{  
//		struct
//		{
//			double dLongitudeDegree;//�ƾ��߷���
//			double dLatitudeDegree;//��γ�߷���
//			double dNormalDegree;//�Ʒ��߷���
//		};
//
//		struct
//		{
//			double X,Y,Z;
//		};
//		struct
//		{
//			double dblX,dblY,dblZ;
//		};
//		struct
//		{
//			double x,y,z;
//		};
//	}; 
//
//}Rotation;//��ת
//
//typedef struct tagZoom
//{
//	union
//	{  
//		struct
//		{
//			double dLongitudeOrientation;//���߷���
//			double dLatitudeOrientation;//γ�߷���
//			double dNormalOrientation;//���߷���
//		};
//
//		struct
//		{
//			double X,Y,Z;
//		};
//		struct
//		{
//			double dblX,dblY,dblZ;
//		};
//		struct
//		{
//			double x,y,z;
//		};
//	}; 
//
//}Zoom;//����





using namespace std;

/**LOD�ṹ��*/
class LOD_INFO_BASE{
public:
	LOD_INFO_BASE();
	LOD_INFO_BASE(const LOD_INFO_BASE& lodInfo);

	virtual bool readBuffer(Buffer &buffer);
	virtual void writeBuffer(Buffer &buffer);
	virtual size_t sizeBuffer();

	
	void copy(const LOD_INFO_BASE& lodInfo);
public:
    byte	    byRelation;		//����һ����LOD�Ĺ�ϵ
    double		dSwitchIn;		//��LOD��ε�������Ӿ���
    double		dSwitchOut;		//��LOD��ε���Զ���Ӿ���
    UINT		unDataSize;		//��LOD��εļ�������������
    UINT	    unTriangleNum;	//��LOD��εļ�������������Ƭ����
    UINT	    unVertexNum;	//��LOD��εļ������ݶ�����
	//std::string dateName;
};

//��չLod��Ϣ
class  LOD_INFO : public LOD_INFO_BASE
{
public:
	virtual bool readBuffer(Buffer &buffer);
	virtual void writeBuffer(Buffer &buffer);
	virtual size_t sizeBuffer();

	void copy(const LOD_INFO& lodInfo);
public:
	UINT64      unGeometryID;   //��LOD��εļ������ݵ�ID
	std::string dateName;
	//std::vector<MTData> m_vecMTData; //��LOD��ε�ģ������Ӧ�Ĳ�������

	void clear();
};

typedef vector<LOD_INFO> LOD_INFOList;//Ҫ�ش���LOD��Ϣ�б�


//5.0.2
class  CFeature:public osg::Referenced
{
public:
//********************************************************************************** 
//** �������ƣ� CFeature
//** ���������� ���캯��
//** ��    �룺 ��          
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-07
//**********************************************************************************
    CFeature(void);

//********************************************************************************** 
//** �������ƣ� CFeature
//** ���������� �������캯��
//** ��    �룺 feature          
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-07
//**********************************************************************************
    CFeature( CFeature& feature );

//********************************************************************************** 
//** �������ƣ� ~CFeature
//** ���������� ��������
//** ��    �룺 ��          
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-07
//**********************************************************************************

    ~CFeature(void);
    

public:
	
	std::string _dbName;

    /** Ҫ��ID*/
    UINT64   m_nFID;
    
    /** Ҫ�����Ƴ���*/
    int m_strNameLen;
   
    /** Ҫ������*/
    std::string  m_strName;

    /** Ҫ�ض����Ӧ��Ҫ����id*/
    UINT64 m_nFCLID;
    
    /** Ҫ�����ͱ��볤��*/
    int m_nCodeLen;
    /** Ҫ�����ͱ���*/	
    string		 m_strCode; 

    /** ״̬*/
    int  m_nState;
    /** ��λ*/
    Location m_location;
    
    /** ��ת*/
    Rotation m_rotation;
    
    /** ����*/
    Zoom m_zoom;
 
    UINT64 m_uFeatureCreateTime;//Ҫ�ش���ʱ��
    UINT64 m_uFeatureUpdateTime;//Ҫ�ظ���ʱ��

    /** ��γ��AABB����С����λ��(X,Y,Z��С��[�����������]*/
   // Vertex3d m_MinVertex;
	osg::Vec3d m_MinVertex;
   
    /** ��γ��AABB����󶥵�λ��(X,Y,Z��С��[�����������]*/
  //  Vertex3d m_MaxVertex;
	osg::Vec3d m_MaxVertex;

    /** Ҫ��LOD���ܼ���*/
     byte m_byLodLeverNum;
    /** LOD��Ϣ*/
    LOD_INFOList m_LOD_Info_List;
public:
	int  _curLOD;
	inline void computeCurLOD(double distance)
	{
		for (int i=0;i<m_LOD_Info_List.size();i++)
		{
			double min=m_LOD_Info_List[i].dSwitchIn;
			double max=m_LOD_Info_List[i].dSwitchOut;
			if (distance<max&&distance>=min)
			{
				_curLOD=i;
				return;
			}
		}
		_curLOD=-1;
	}
	//********************************************************************************** 
	//** �������ƣ� readBuffer
	//** ���������� �ӻ������ж�����
	//** ��    �룺 buffer:Buffer���������           
	//** ��    ���� ��
	//** ����ֵ���ɹ�Ϊtrue��ʧ��Ϊfalse
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-11
	//**********************************************************************************
	virtual bool readBuffer(Buffer &buffer);

	//********************************************************************************** 
	//** �������ƣ� writeBuffer
	//** ���������� ������д��������
	//** ��    �룺 buffer:Buffer���������          
	//** ��    ���� ��
	//** ����ֵ����
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-11
	//**********************************************************************************
	virtual void writeBuffer(Buffer &buffer);
    
    //********************************************************************************** 
    //** �������ƣ� sizeBuffer
    //** ���������� �õ�Ҫ�ش�С
    //** ��    �룺 ��          
    //** ��    ���� ��
    //** ����ֵ��Ҫ�ش�С
    //** ��    �ߣ� ����
    //** �������ڣ� 2012-04-11
    //**********************************************************************************
    size_t sizeBuffer();

    //********************************************************************************** 
    //** �������ƣ� readBufferForService
    //** ���������� �ӻ������ж�����,�˴�����ȡҪ�ض����е�FeatureClassID
    //** ��    �룺 buffer:Buffer���������           
    //** ��    ���� ��
    //** ����ֵ���ɹ�Ϊtrue��ʧ��Ϊfalse
    //** ��    �ߣ� ����
    //** �������ڣ� 2012-04-11
    //**********************************************************************************
    virtual bool readBufferForService(Buffer &buffer);

    //********************************************************************************** 
    //** �������ƣ� writeBufferForService
    //** ���������� ������д�����������˴���д��Ҫ�ض����е�FeatureClassID
    //** ��    �룺 buffer:Buffer���������          
    //** ��    ���� ��
    //** ����ֵ����
    //** ��    �ߣ� ����
    //** �������ڣ� 2012-04-11
    //**********************************************************************************
    virtual void writeBufferForService(Buffer &buffer);

    //********************************************************************************** 
    //** �������ƣ� sizeBuffer
    //** ���������� �õ�Ҫ�ش�С,�˴�������Ҫ�ض����е�FeatureClassID
    //** ��    �룺 ��          
    //** ��    ���� ��
    //** ����ֵ��Ҫ�ش�С
    //** ��    �ߣ� ����
    //** �������ڣ� 2012-06-08
    //**********************************************************************************
    size_t sizeBufferForService();
    
private:

//********************************************************************************** 
//** �������ƣ� copy
//** ���������� ���������Ҫ�ض���ĸ�������
//** ��    �룺 feature:Ҫ�ض��������         
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-07
//**********************************************************************************
    void copy(const CFeature& feature);
public:
	void setFeatureID(UINT64 nfid);
	UINT64 getFeatureID();

	void setFeatureName(string strFeatureName);
	string getFeatureName();
	int getFeatureNameLen();

	void setFCLID(UINT64 nFCLID);
	UINT64 getFCLID();

	void setCode(string strCode);
	string getCode();
	int getCodeLen();

	void setStatus(int nState);
	int getStatus();

	void setLocation(Location v);
	Location getLocation();

	void setRotation(Rotation v);
	Rotation getRotation();

	void setZoom(Zoom v);
	Zoom getZoom();

	void setLodLeverNum(byte bLodLeverNum);
	byte getLodLeverNum();

	void setLOD_INFOList(LOD_INFOList& v);
	LOD_INFOList& getLOD_INFOList();

    //void getMinVertex(Vertex3d& minVertex);
    //void getMaxVertex(Vertex3d& maxVertex);

protected:

	//����������Ϣ
 	virtual void copyBaseInfo(const CFeature& feature);

	//��д������Ϣ
	//bForService �Ƿ�Ϊ�ͻ�������
	virtual bool readBaseInfo(Buffer& buffer, bool bForService);
	virtual void writeBaseInfo(Buffer& buffer, bool bForService);

	//��д����
	//bForService �Ƿ�Ϊ�ͻ�������
	virtual bool readBuffer(Buffer& buffer, bool bForService);
	virtual void writeBuffer(Buffer& buffer, bool bForService);

};

typedef vector<LOD_INFO_BASE> LodInofBaseList;//Ҫ�ش���LOD��Ϣ�б�

//5.0 feature�ṹ
class  CFeature50 : public CFeature
{
	LodInofBaseList m_vecLodInfo;
public:
	LodInofBaseList& getLOD_INFOList()
	{
		return m_vecLodInfo;
	}

protected:
	//��д����
	//bForService �Ƿ�Ϊ�ͻ�������
	virtual bool readBuffer(Buffer& buffer, bool bForService);
	virtual void writeBuffer(Buffer& buffer, bool bForService);
};

#endif