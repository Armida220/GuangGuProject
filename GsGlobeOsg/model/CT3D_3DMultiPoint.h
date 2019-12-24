//********************************************************************************** 
//** �ļ����ƣ�CT3D_3DMultiPoint.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά����ඨ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-13
//********************************************************************************** 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _CT3D_3DMULTIPOINT_H_
#define _CT3D_3DMULTIPOINT_H_

#include "ModelDef.h"
#include "CT3D_3DPoint.h"


class /*DLL_EXPORT*/ C3DMultiPoint :
	public C3DPoint
{

	/** @defgroup C3DPoint C3DMultiPoint-��ά���  
	*  @{
	*/

protected:
	/** @name ���ԣ���Ա������
	* @{
	*/

	/** �������ͱ��� */
	byte m_byVertexType;

	/** �������� */
	void *m_vVertices;

	/** ������ */
	long m_lVertNum;

	
public:

	/** @defgroup C3DMultiPoint ��������Ա������
	* @{
	*/

	/** @name ��������������
	*  @{
	*/

	//********************************************************************************** 
	//** �������ƣ� C3DMultiPoint
	//** ���������� ���캯��1
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************	
	C3DMultiPoint()
	{
		m_byTypeID = GEOTYPE_3D_MULTIPOINT;

		m_byVertexType = VERTEXTYPE_V3d;
		m_lVertNum = 0;
		m_vVertices = NULL;
	}

	//********************************************************************************** 
	//** �������ƣ� C3DMultiPoint
	//** ���������� ���캯��2
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
	C3DMultiPoint(long lVertNum, void* const vVertices):	
	m_lVertNum(lVertNum), m_vVertices(vVertices)
	{
		m_byTypeID = GEOTYPE_3D_MULTIPOINT;


	}

	//********************************************************************************** 
	//** �������ƣ� ~C3DMultiPoint
	//** ���������� ��������
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
	virtual ~C3DMultiPoint(void)
	{
		ReleaseVertexArray(m_byVertexType, m_vVertices);
	}

	/** @} */ // ����������������β


		/** @name ���ݲ���
	*  @{
	*/

	//********************************************************************************** 
	//** �������ƣ� GetVertexType
	//** ���������� ��ö������ͱ���
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	�������ͱ���
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
	byte GetVertexType() const
	{
		return m_byVertexType;
	}

	//********************************************************************************** 
	//** �������ƣ� GetVertices
	//** ���������� �����ά��㶥������
	//** ��    �룺 vVertices ������ֵ��һ����ά�����ָ�������           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
	void GetVertices( void*& vVertices ) const
	{
		vVertices = m_vVertices;
	}

	//********************************************************************************** 
	//** �������ƣ� GetVertices
	//** ���������� �����ά��㶥������
	//** ��    �룺 vVertices ������ֵ��һ����ά�����ָ������ã�vNum ������ֵ��һ����ά�����ָ�������           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
	void GetVertices( long& lVertNum, void*& vVertices ) const
	{
		lVertNum = m_lVertNum;
		vVertices = m_vVertices;
	}

	//********************************************************************************** 
	//** �������ƣ� GetVerticesEx
	//** ���������� �����ά��㶥������
	//** ��    �룺 ��λ������༯��vt3d           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
	void GetVerticesEx(vector<Vertex3d>& vt3d) const;

	//********************************************************************************** 
	//** �������ƣ� GetVerticesNum
	//** ���������� �����ά��㶥�����
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��ά��㶥�����
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
	long GetVerticesNum() const
	{
		return m_lVertNum;
	}

	



	/** @name �������
	*  @{
	*/

	//********************************************************************************** 
	//** �������ƣ� CreateObject
	//** ���������� ����һ����ǰ�����������ڴ�ռ�
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	���ٵĵ�ǰ������ڴ�ռ���׵�ַ
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
	CGeometry* CreateObject();

	//********************************************************************************** 
	//** �������ƣ� readBuffer
	//** ���������� �ӻ������н�����ǰ���󣬲�����Ա������ֵ
	//** ��    �룺 buf	������������           
	//** ��    ���� ��
	//** ����ֵ��	�ɹ�Ϊtrue��ʧ��Ϊfalse
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
	bool readBuffer( Buffer & buf);

	//********************************************************************************** 
	//** �������ƣ� writeBuffer
	//** ���������� �ѵ�ǰ����ĳ�Ա�������ݣ������һ��������
	//** ��    �룺 buf	������������           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
	void writeBuffer(Buffer& buf);
	
	

	virtual size_t sizeBuffer();

};

#endif //_INC_C3DMULTIPOINT_49F16898013X_INCLUDED