// Copyright (C) 1991 - 1999 Rational Software Corporation


#ifndef _CT3D_GEOMETRY_H_
#define _CT3D_GEOMETRY_H_ 1
#include "Model/ModelDef.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Model/CT3D_Vertex3d.h"
#include "Model/Buffer.h"
using namespace std;

	enum
	{
		GEOTYPE_3D_GEOMETRY = 0,
		GEOTYPE_3D_POINT = 1,
		GEOTYPE_3D_SURFACE =3,
		GEOTYPE_3D_CURVE = 4,
        GEOTYPE_3D_GROUP = 5,
		GEOTYPE_3D_SOLID = 7,
		GEOTYPE_3D_TRIANGLEMESH = 12,
		GEOTYPE_3D_POLYGON = 15,
		GEOTYPE_3D_LINEARRING = 16,
		GEOTYPE_3D_LINESTRING = 18,
		GEOTYPE_3D_REFERENCE = 20,
		GEOTYPE_3D_SINGLEPOINT = 26,
		GEOTYPE_3D_MULTIPOINT = 27,
		GEOTYPE_3D_FEATUREINFOGROUP = 29,
		GEOTYPE_3D_LOFTING = 35,
        //�����������40��ʼ
		GEOTYPE_3D_MODELOBJECT = 41,   
		GEOTYPE_3D_OBLIQUE=42
        

	};

class /*DLL_EXPORT*/ CGeometry
{

protected:

	/** Ҫ��ID*/
	UID64 m_uFID;

	/** ���ζ�������ͣ�ÿ�����Ͷ�Ӧһ����� */
	byte m_byTypeID;

	/** ���ζ�������ֳ���*/
	int m_nObjNameLen;

	/** ���ζ��������*/
	string m_strObjName;

public:
	//********************************************************************************** 
	//** �������ƣ� CGeometry
	//** ���������� ���캯��1
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
	CGeometry();

	//********************************************************************************** 
	//** �������ƣ� C3DGeometry
	//** ���������� ���캯��2
	//** ��    �룺 uFID:Ҫ��ID
	//**            byTypeID:��������ID
	//**            strObjName: ���ζ�������
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-11
	//************************************************************************************
    CGeometry(UID64 uFID,byte byTypeID, string strObjName);

	//********************************************************************************** 
	//** �������ƣ� ~CGeometry
	//** ���������� ��������
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
	virtual ~CGeometry();	
	
public:
	//********************************************************************************** 
	//** �������ƣ� readBuffer
	//** ���������� �ӻ����ȡ�����¼
	//** ��    �룺 pBuffer ����           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
    virtual bool readBuffer( Buffer & buf) ;

	//********************************************************************************** 
	//** �������ƣ� readBuffer
	//** ���������� ������д�뻺��
	//** ��    �룺 pBuffer ����           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
    virtual void writeBuffer(Buffer& buf) ;
	
	//********************************************************************************** 
	//** �������ƣ� CreateGeometry
	//** ���������� ����һ����ǰ�����������ڴ�ռ�
	//** ��    �룺 ���ζ��������           
	//** ��    ���� ��
	//** ����ֵ��	���ٵĵ�ǰ������ڴ�ռ���׵�ַ
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
    static CGeometry * CreateGeometry(byte byType); 
public:
	virtual void setObjID(UID64 uFID);
	virtual UID64 getObjID();

	virtual void setTypeID(byte byTypeID);
	virtual byte getTypeID();

	virtual void setObjName(string strObjName);
	virtual string getObjName();
	virtual int getObjNameLen();

    virtual size_t sizeBuffer();
};

typedef CGeometry Geometry;

//********************************************************************************** 
//** �������ƣ� CreateGeometry
//** ���������� ���ݶ�������ɾ����������
//** ��    �룺 �������� iVertexType�����������ָ������pVertexPointer          
//** ��    ���� ��
//** ����ֵ��	0����ɾ���ɹ���-1�����ɹ�
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
/*DLL_EXPORT*/ long ReleaseVertexArray(unsigned char iVertexType, void*& pVertexPointer);



#endif /* _INC_CGEOMETRY_49E53136004E_INCLUDED */
