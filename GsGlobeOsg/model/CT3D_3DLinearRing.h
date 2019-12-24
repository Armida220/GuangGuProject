//********************************************************************************** 
//** �ļ����ƣ�CT3D_3DLinearRing.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� �߻��ඨ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-11
//********************************************************************************** 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _CT3D_3DLINEARRING_H_
#define _CT3D_3DLINEARRING_H_

#include "ModelDef.h"

#include "CT3D_3DGeometry.h"

class  C3DLinearRing : public C3DGeometry
{

protected:

    /** �������ͱ��� */
    byte m_byVertexType;

    /** �߻������� */
    int m_nVertNum;

	/** �߻�������У���vectorװ�أ�ֱ�ӱ��涥����󣬶�������������� */
	void *m_vVertices;

	/** �ڻ������⻷�ı�־ 0���⻷ 1���ڻ�*/
	byte m_bInOrOutRing;
	

public:

    

	//********************************************************************************** 
	//** �������ƣ� C3DLinearRing
	//** ���������� ���캯��1
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-11
	//**********************************************************************************
	C3DLinearRing();
    
	//********************************************************************************** 
	//** �������ƣ� C3DLinearRing
	//** ���������� ���캯��2
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-11
	//**********************************************************************************
    C3DLinearRing(int nVertexNum, Vertex3d* const vVertices,int bInOrOutRing = 0);	
   
	
	
	//********************************************************************************** 
	//** �������ƣ� ~C3DPolygon
	//** ���������� ��������
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-11
	//**********************************************************************************
	virtual ~C3DLinearRing();
	
	//********************************************************************************** 
	//** �������ƣ� readBuffer
	//** ���������� �����ݶ���buf
	//** ��    �룺 Buffer����buf������           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� �
	//** �������ڣ� 2012-04-11
	//**********************************************************************************
	virtual bool readBuffer( Buffer & buf);
	
	//********************************************************************************** 
	//** �������ƣ� writeBuffer
	//** ���������� ������д��buf
	//** ��    �룺 Buffer����buf������           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� �
	//** �������ڣ� 2012-04-11
	//**********************************************************************************
	virtual void writeBuffer(Buffer& buf);

public:
	void setVertexType(byte byVertexType);
	byte getVertexType();

	void setVertNum(int VertNum);
	int getVertNum();

	void setInOrOutRing(byte bInOrOutRing);
	byte getInOrOutRing();

	void SetVertices( void* const vVertices)
	{
		m_vVertices = vVertices;
	}
	void GetVertices(void*& vVertices) const
	{
		vVertices = m_vVertices;
	}
    virtual size_t sizeBuffer();


};

#endif /* _INC_C3DLINEARRING_49E34728009C_INCLUDED */