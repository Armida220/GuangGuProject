//********************************************************************************** 
//** �ļ����ƣ�CT3D_C3DSolid.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά����Ķ���
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-11
//********************************************************************************** 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#pragma warning(disable:4251)
#endif
#ifndef _CT3D_3DMODELOBJECT_H_
#define _CT3D_3DMODELOBJECT_H_

#include "ModelDef.h"
#include "CT3D_3DGeometry.h"
#include "CT3D_3DSurface.h"
#include <utility>
#include <vector>
#include <fstream>
using namespace std;

typedef pair<UINT,C3DSurface*> _3DSurfacePair;
typedef vector<_3DSurfacePair> _3DSurfaceList;//��ά�����б�

/** ��ϵ��*/
typedef struct _D3dxMaterialParam
{
	unsigned long nAttribId;			//���ʱ�ʶID
	unsigned long nFaceStart;			//��ʼ�������ʶID
	unsigned long nFaceCount;			//���������
	unsigned long nVertexStart;			//��ʼ�����ʶID
	unsigned long nVertexCount;			//�������

	_D3dxMaterialParam()
	{
		nAttribId = 0;
		nFaceStart = 0;
		nFaceCount = 0;
		nVertexStart = 0;
		nVertexCount = 0;
	}
} D3dxMaterialParam;

class /*DLL_EXPORT*/ C3DModelObject 
: public C3DGeometry
{

private:    

    /** ���б� */
	_3DSurfaceList m_3DSurfaceList;

	/** ��ϵ����*/
	std::vector<D3dxMaterialParam> m_vecD3dxMaterialParam;

	/** �ڽӱ�*/
	unsigned long* m_pAdjacencyTable;

	/**�ڽӱ����*/
	long m_lAdjacencyCount;

public:
	//********************************************************************************** 
	//** �������ƣ� C3DModelObject
	//** ���������� ���캯��
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-11
	//**********************************************************************************
	C3DModelObject();

	//********************************************************************************** 
	//** �������ƣ� ~C3DModelObject
	//** ���������� ��������
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-11
	//**********************************************************************************
	virtual ~C3DModelObject();
	

	//********************************************************************************** 
	//** �������ƣ� readBuffer
	//** ���������� �����ݶ���buf
	//** ��    �룺 Buffer����buf������           
	//** ��    ���� ��
	//** ����ֵ��	�ɹ�Ϊtrue��ʧ��Ϊfalse
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
	int getSurfaceNum();

	void set3DSurfaceList(const _3DSurfaceList& v3DSurfaceList);
	_3DSurfaceList& get3DSurfaceList();

	virtual size_t sizeBuffer();

	/** ��ȡ��ϵ�� */
 	void GetMaterialParamVec(vector<D3dxMaterialParam>& vecD3dxMaterialParam)
 	{
 		vecD3dxMaterialParam = m_vecD3dxMaterialParam;
 	}
 
 	/** ���ù�ϵ�� */
 	void SetMaterialParamVec(vector<D3dxMaterialParam>& vecD3dxMaterialParam)
 	{
 		m_vecD3dxMaterialParam = vecD3dxMaterialParam;
 	}

	/** ��ȡ�ڽӱ� */
	void GetAdjacencyTable(unsigned long*& pAdjacencyTable, long& lAdjacencyCount)
	{
		pAdjacencyTable = m_pAdjacencyTable;
		lAdjacencyCount = m_lAdjacencyCount;
	}

	/** �����ڽӱ� */
	void SetAdjacencyTable(unsigned long* pAdjacencyTable, long lAdjacencyCount)
	{
		m_pAdjacencyTable = pAdjacencyTable;
		m_lAdjacencyCount = lAdjacencyCount;
	}
 
};

#endif 
