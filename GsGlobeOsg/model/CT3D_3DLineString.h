//********************************************************************************** 
//** �ļ����ƣ�CT3D_C3DLineString.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά������Ķ���
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-11
//********************************************************************************** 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _CT3D_3DLINESTRING_H_
#define _CT3D_3DLINESTRING_H_

#include "ModelDef.h"
#include "CT3D_3DCurve.h"
#include "CT3D_Vertex3d.h"
#include "CT3D_Vertex3f.h"
#include "Buffer.h"


class /*DLL_EXPORT*/ C3DLineString 
: public C3DCurve
{

public:

    /** �߿� */
    double m_dLineWidth;

    /** �������ͱ��� */
    byte m_byVertexType;

    /** ������ */
    long m_lVertNum;

	/** �������У���vectorװ�� */
	void *m_vVertices;
public:

	//********************************************************************************** 
	//** �������ƣ� C3DLineString
	//** ���������� ���캯��1
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-11
	//**********************************************************************************	
	C3DLineString();
	

	//********************************************************************************** 
	//** �������ƣ� C3DLineString
	//** ���������� ���캯��2
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-11
	//**********************************************************************************
	C3DLineString(int nVertNum, void* const vVertices, unsigned char vertexType, double dLineWidth);
	
	
	//********************************************************************************** 
	//** �������ƣ� ~C3DLineString
	//** ���������� ��������
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-11
	//**********************************************************************************
	virtual ~C3DLineString();
	
	//********************************************************************************** 
	//** �������ƣ� readBuffer
	//** ���������� �����ݶ���buf
	//** ��    �룺 Buffer����buf������           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� �
	//** �������ڣ� 2012-04-11
	//**********************************************************************************
	bool readBuffer( Buffer & buf);
	
	//********************************************************************************** 
	//** �������ƣ� writeBuffer
	//** ���������� ������д��buf
	//** ��    �룺 Buffer����buf������           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� �
	//** �������ڣ� 2012-04-11
	//**********************************************************************************
	void writeBuffer(Buffer& buf);

	void setLineWidth(double dLineWidth);
	double getLineWidth();

	void setVertexType(byte byVertexType);
	byte getVertexType();


	void setVertNum(long lVertNum);
	long getVertNum();

	void SetVertices(void* const vVertices)
	{
		m_vVertices = vVertices;
	}

	void GetVertices(void*& vVertices) const
	{
		vVertices = m_vVertices;
	}

	virtual size_t sizeBuffer();
};

#endif 
