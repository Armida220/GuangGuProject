//********************************************************************************** 
//** �ļ����ƣ�CT3D_C3DSolid.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά����ʵ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-11
//********************************************************************************** 


#include "CT3D_3DModelObject.h"
#include "Buffer.h"

//********************************************************************************** 
//** �������ƣ� C3DModelObject
//** ���������� ���캯��
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
 C3DModelObject::C3DModelObject()
{
    m_byTypeID = GEOTYPE_3D_MODELOBJECT;
	m_lAdjacencyCount = 0;
	m_pAdjacencyTable = NULL;
}



 //********************************************************************************** 
 //** �������ƣ� ~C3DModelObject
 //** ���������� ��������
 //** ��    �룺 ��           
 //** ��    ���� ��
 //** ����ֵ��	��
 //** ��    �ߣ� ����
 //** �������ڣ� 2012-04-11
 //**********************************************************************************
 C3DModelObject::~C3DModelObject()
{
    int nSize = m_3DSurfaceList.size();
    for(int i = 0; i< nSize; i++)
    {
        if(m_3DSurfaceList[i].second!= NULL)
        {
            delete m_3DSurfaceList[i].second;
            m_3DSurfaceList[i].second = NULL;
        }
    }
    m_3DSurfaceList.clear();
 	m_vecD3dxMaterialParam.clear();

	if (m_pAdjacencyTable != NULL)
	{
		delete []m_pAdjacencyTable;
		m_pAdjacencyTable = NULL;
	}
	m_lAdjacencyCount = 0;
}

//********************************************************************************** 
//** �������ƣ� readBuffer
//** ���������� �����ݶ���buf
//** ��    �룺 Buffer����buf������           
//** ��    ���� ��
//** ����ֵ��	�ɹ�Ϊtrue��ʧ��Ϊfalse
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
bool C3DModelObject::readBuffer( Buffer & buf)
{
	
	bool bRet =C3DGeometry::readBuffer(buf);
	
	if(!bRet)
		return false;
	
	//��ȡ�����
    int nSurfaceNum = 0;
	buf.read((void*)&nSurfaceNum,sizeof(int));
    byte byType = 0;//ʵ�ʵ�������
	//��ȡ���б�
	for(int i=0;i< nSurfaceNum;i++)
	{
		UINT nSize=0;
        buf.read((void*)&nSize,sizeof(UINT));//����Ĵ�С
		
        //�õ�Surface��������
        memcpy(&byType, (byte*)buf.getCurPtr() + sizeof(UINT64),sizeof(byte));

		//������ʹ���
		if (255 == byType)
			continue;

        //���������
        C3DSurface* pSurface = (C3DSurface*)CreateGeometry(byType);
		if (NULL == pSurface)
			continue;

		if (!pSurface->readBuffer(buf))
		{
			SafeDelete(pSurface);
			return false;
		}
		
		_3DSurfacePair surfacepair(nSize,pSurface);
		m_3DSurfaceList.push_back(surfacepair);

	}
	//------------------------------------------------------------------
	int nCount1 = 0;
	buf.read((char*)&nCount1,sizeof(int));//��ϵ�����

	m_vecD3dxMaterialParam.reserve(nCount1);
	for(int i=0; i<nCount1; i++)
	{				
		unsigned char nSize = 0;
		buf.read((void*)&nSize,sizeof(unsigned char));//��i����ϵ��Ĵ�С

		//��i����ϵ��
		D3dxMaterialParam matParam;
		buf.read((void*)&matParam.nAttribId, sizeof(unsigned long));
		buf.read((void*)&matParam.nFaceStart, sizeof(unsigned long));
		buf.read((void*)&matParam.nFaceCount, sizeof(unsigned long));
		buf.read((void*)&matParam.nVertexStart, sizeof(unsigned long));
		buf.read((void*)&matParam.nVertexCount, sizeof(unsigned long));

		m_vecD3dxMaterialParam.push_back(matParam);
	}

	buf.read((char*)&m_lAdjacencyCount,sizeof(long));
	if(m_lAdjacencyCount > 0)
	{
		m_pAdjacencyTable = new unsigned long[m_lAdjacencyCount];
		buf.read((char*)m_pAdjacencyTable,sizeof(unsigned long) * m_lAdjacencyCount);
	}
	//------------------------------------------------------------------

	return true;
}

//********************************************************************************** 
//** �������ƣ� writeBuffer
//** ���������� ������д��buf
//** ��    �룺 Buffer����buf������           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
void C3DModelObject::writeBuffer(Buffer& buf)
{
	C3DGeometry::writeBuffer(buf);
	//д�������
    int nSurfaceNum = m_3DSurfaceList.size();
	buf.write((void*)&nSurfaceNum,sizeof(int));
	//д�����б�
	for(int i=0;i<nSurfaceNum;i++)
	{
		buf.write((void*)&m_3DSurfaceList[i].first,sizeof(UINT));
        m_3DSurfaceList[i].second->writeBuffer(buf);
	}

	//------------------------------------------------------------------
	int nCount1 = m_vecD3dxMaterialParam.size();	//��ϵ�����
	buf.write((char*)&nCount1, sizeof(int));

	for(int i=0; i<nCount1; i++)
	{				
		unsigned char nSize = 0;
		nSize = sizeof(D3dxMaterialParam);
		buf.write((void*)&nSize,sizeof(unsigned char));//��i����ϵ��Ĵ�С

		//��i����ϵ��
		buf.write((void*)&(m_vecD3dxMaterialParam[i].nAttribId), sizeof(unsigned long));
		buf.write((void*)&(m_vecD3dxMaterialParam[i].nFaceStart), sizeof(unsigned long));
		buf.write((void*)&(m_vecD3dxMaterialParam[i].nFaceCount), sizeof(unsigned long));
		buf.write((void*)&(m_vecD3dxMaterialParam[i].nVertexStart), sizeof(unsigned long));
		buf.write((void*)&(m_vecD3dxMaterialParam[i].nVertexCount), sizeof(unsigned long));
	}

	buf.write((char*)&m_lAdjacencyCount,sizeof(long));
	if(m_lAdjacencyCount > 0)
	{
		buf.write((char*)m_pAdjacencyTable,sizeof(unsigned long) * m_lAdjacencyCount);
	}
	//------------------------------------------------------------------
}



void C3DModelObject::set3DSurfaceList(const _3DSurfaceList& v3DSurfaceList)
{
	m_3DSurfaceList=v3DSurfaceList;
}
_3DSurfaceList& C3DModelObject::get3DSurfaceList()
{
	return m_3DSurfaceList;
}
int C3DModelObject::getSurfaceNum()
{
	return m_3DSurfaceList.size();
}

size_t C3DModelObject::sizeBuffer()
{
	size_t nSize = 0;
	nSize += C3DGeometry::sizeBuffer();
	nSize += sizeof(int);//�����
	for (int i=0;i<getSurfaceNum();i++)
	{
		nSize += sizeof(UINT);//���С
		nSize += m_3DSurfaceList[i].second->sizeBuffer();
	}

	//��ϵ��
	nSize += sizeof(int);						//��ϵ�����
	for (size_t i=0; i<m_vecD3dxMaterialParam.size(); i++)
	{
		nSize += sizeof(unsigned char);			//��ϵ���С
		nSize += sizeof(D3dxMaterialParam);		//��ϵ������
	}

	//�ڽӱ�
	nSize += sizeof(long);									//m_lAdjacencyCount
	nSize += sizeof(unsigned long)*m_lAdjacencyCount;		//m_pAdjacencyTable

	return nSize;
}
