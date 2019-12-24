//********************************************************************************** 
//** �ļ����ƣ�CT3D_3DLinearRing.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά������������ʵ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-11
//********************************************************************************** 

#include "CT3D_3DTriangleMesh.h"
#include "CT3D_Vertex3d.h"
#include "CT3D_Vertex3f.h"
#include "CT3D_ShadedVertex3d.h"
#include "CT3D_ShadedVertex3f.h"
#include "CT3D_TexturedVertex3d.h"
#include "CT3D_TexturedVertex3f.h"
#include "CT3D_ThirdVersatileVertex3d.h"
#include "CT3D_ThirdVersatileVertex3dWithoutRGB.h"
#include "CT3D_ThirdVersatileVertex3fWithoutRGB.h"
#include "CT3D_ThirdVersatileVertex3f.h"
#include "CT3D_NormaledVertex3d.h"
#include "CT3D_NormaledVertex3f.h"
#include "Buffer.h"

//********************************************************************************** 
//** �������ƣ� C3DTriangleMesh
//** ���������� ���캯��
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
C3DTriangleMesh::C3DTriangleMesh()
{
    m_byTypeID = GEOTYPE_3D_TRIANGLEMESH;
    m_vVertexList = NULL;	
    m_lVertNum = 0;
    m_byVertexType = VERTEXTYPE_V3d;
    m_lTriangleList = NULL;
    m_lTriListSize = 0;
    m_lStripIndices = NULL;
    m_lStripListSize = 0;

}

//********************************************************************************** 
//** �������ƣ� ~C3DTriangleMesh
//** ���������� ��������
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
C3DTriangleMesh::~C3DTriangleMesh()
{
// 	SafeDeleteArray(m_lTriangleList);
// 	SafeDeleteArray(m_lStripIndices);

	FreeVertexBuffer();
	if (m_lStripIndices)
		BufferManager::FreeBuffer((unsigned char*)m_lStripIndices, sizeof(long)*m_lStripListSize);
	if (m_lTriangleList)
		BufferManager::FreeBuffer((unsigned char*)m_lTriangleList, sizeof(long)*m_lTriListSize);
}

//********************************************************************************** 
//** �������ƣ� GetVertexType
//** ���������� ��ö������ͱ���
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	�������ͱ���
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
byte C3DTriangleMesh::GetVertexType() const
{
    return m_byVertexType;
}


//********************************************************************************** 
//** �������ƣ� GetVertices
//** ���������� ��ö����б�
//** ��    �룺 vVertexList�ĵ�ַ           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
void C3DTriangleMesh::GetVertices(void*& vVertexList) const
{
    vVertexList = m_vVertexList;
}

//********************************************************************************** 
//** �������ƣ� GetVertices
//** ���������� ��ö����б�Ͷ����б���
//** ��    �룺 vVertexList	�����б�ĵ�ַ ��lVertNum	�����б��ȵĵ�ַ         
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
void C3DTriangleMesh::GetVertices(void*& vVertexList,long& lVertNum) const
{
    vVertexList = m_vVertexList;
    lVertNum = m_lVertNum;
}

//********************************************************************************** 
//** �������ƣ� GetVerticesNum
//** ���������� ��ö����б���
//** ��    �룺 ��         
//** ��    ���� ��
//** ����ֵ��	�����б���
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
long C3DTriangleMesh::GetVerticesNum() const
{
    return m_lVertNum;
}

//********************************************************************************** 
//** �������ƣ� GetTriangles
//** ���������� �������������
//** ��    �룺 �������������У�tr3d         
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
void C3DTriangleMesh::GetTriangles(vector<long>& tr3d)
{
    tr3d.reserve(m_lTriListSize);
    for(int i=0; i<m_lTriListSize; i++)
    {
        tr3d.push_back(m_lTriangleList[i]);
    }
}

//********************************************************************************** 
//** �������ƣ� GetStrips
//** ���������� �����������������
//** ��    �룺 �����������������У�st3d        
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
void C3DTriangleMesh::GetStrips(vector<long>& st3d)
{
    st3d.reserve(m_lStripListSize);
    for(int i=0; i<m_lStripListSize; i++)
    {
        st3d.push_back(m_lStripIndices[i]);
    }
}

//********************************************************************************** 
//** �������ƣ� GetTriangles
//** ���������� �����������������������
//** ��    �룺 ��������������lTriangleList�ĵ�ַ����������������lTriListSize�ĵ�ַ
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
void C3DTriangleMesh::GetTriangles(long*& lTriangleList, long& lTriListSize) const
{
    lTriListSize = m_lTriListSize;
    lTriangleList = m_lTriangleList;
}

//********************************************************************************** 
//** �������ƣ� GetStrips
//** ���������� ���������������������������
//** ��    �룺 ������������������lStripIndices�ĵ�ַ��������������������lStripListSize�ĵ�ַ       
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
void C3DTriangleMesh::GetStrips(long*& lStripIndices, long& lStripListSize) const
{
    lStripIndices = m_lStripIndices;
    lStripListSize = m_lStripListSize;
}

//********************************************************************************** 
//** �������ƣ� readBuffer
//** ���������� �����ݶ���buf
//** ��    �룺 Buffer����buf������           
//** ��    ���� ��
//** ����ֵ��	�ɹ�Ϊtrue��ʧ��Ϊfalse
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
bool C3DTriangleMesh::readBuffer( Buffer & buf)
{
   bool bRet = C3DSurface::readBuffer(buf);
   if(!bRet)
	   return false;
   
    //����������Ϣ************************

    //�������ͱ���
    buf.read((char*)&m_byVertexType,sizeof(unsigned char));
	
	if(m_byVertexType >= VERTEXTYPE_End || m_byVertexType < VERTEXTYPE_V3f)
		return false;
	
    //����������������<0��ʾ�������ݣ�
    buf.read((char*)&m_lVertNum,sizeof(long));
// 	if (m_lVertNum<=0)
// 		return false;

	//���ʣ��������� С�� ��������������ʾ���ݴ���
	int nVertexBufSize = (size_t)GetVertexStrideFromType(m_byVertexType) * m_lVertNum;
	if ( nVertexBufSize > buf.size() - buf.getPos() )
		return false;

	if(m_byVertexType == VERTEXTYPE_V3d)	
	{
		Vertex3d* pList = (Vertex3d*)BufferManager::AllocBuff(sizeof(Vertex3d) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		//��forѭ�������ֽڶ�������
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(double));
			buf.read(&pList[nNum].y,sizeof(double));
			buf.read(&pList[nNum].z,sizeof(double));
		}
		pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3f) 
	{
		Vertex3f* pList = (Vertex3f*)BufferManager::AllocBuff(sizeof(Vertex3f) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		//��forѭ�������ֽڶ�������
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(float));
			buf.read(&pList[nNum].y,sizeof(float));
			buf.read(&pList[nNum].z,sizeof(float));
		}
		pList = NULL;
	}
	else if (m_byVertexType == VERTEXTYPE_V3fN3f)
	{
		NormaledVertex3f* pList = (NormaledVertex3f*)BufferManager::AllocBuff(sizeof(NormaledVertex3f) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		//��forѭ�������ֽڶ�������
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(float));
			buf.read(&pList[nNum].y,sizeof(float));
			buf.read(&pList[nNum].z,sizeof(float));
			buf.read(&pList[nNum].nx,sizeof(float));
			buf.read(&pList[nNum].ny,sizeof(float));
			buf.read(&pList[nNum].nz,sizeof(float));   
		}
		pList = NULL;
	}
	else if (m_byVertexType == VERTEXTYPE_V3dN3d)
	{
		NormaledVertex3d* pList = (NormaledVertex3d*)BufferManager::AllocBuff(sizeof(NormaledVertex3d) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		//��forѭ�������ֽڶ�������
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(double));
			buf.read(&pList[nNum].y,sizeof(double));
			buf.read(&pList[nNum].z,sizeof(double));
			buf.read(&pList[nNum].nx,sizeof(double));
			buf.read(&pList[nNum].ny,sizeof(double));
			buf.read(&pList[nNum].nz,sizeof(double));   
		}
		pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3dT2d)
	{
		TexturedVertex3d* pList = (TexturedVertex3d*)BufferManager::AllocBuff(sizeof(TexturedVertex3d) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		//��forѭ�������ֽڶ�������
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(double));
			buf.read(&pList[nNum].y,sizeof(double));
			buf.read(&pList[nNum].z,sizeof(double));
			buf.read(&pList[nNum].tu,sizeof(double));
			buf.read(&pList[nNum].tv,sizeof(double));   
		}
		pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3fT2f)
	{
// 		m_vVertexList = new TexturedVertex3f[m_lVertNum];
// 		TexturedVertex3f* pList = (TexturedVertex3f*)m_vVertexList;
// 		if (NULL == m_vVertexList)
// 			return false;
		TexturedVertex3f* pList = (TexturedVertex3f*)BufferManager::AllocBuff(sizeof(TexturedVertex3f) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		//��forѭ�������ֽڶ�������
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(float));
			buf.read(&pList[nNum].y,sizeof(float));
			buf.read(&pList[nNum].z,sizeof(float));
			buf.read(&pList[nNum].tu,sizeof(float));
			buf.read(&pList[nNum].tv,sizeof(float));   
		}
		pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3dN3dC3f)
	{
// 		m_vVertexList = new ShadedVertex3d[m_lVertNum];
// 		ShadedVertex3d* pList = (ShadedVertex3d*)m_vVertexList;
// 		if (NULL == m_vVertexList)
// 			return false;
		ShadedVertex3d* pList = (ShadedVertex3d*)BufferManager::AllocBuff(sizeof(ShadedVertex3d) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		//��forѭ�������ֽڶ�������
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(double));
			buf.read(&pList[nNum].y,sizeof(double));
			buf.read(&pList[nNum].z,sizeof(double));
			buf.read(&pList[nNum].nx,sizeof(double));
			buf.read(&pList[nNum].ny,sizeof(double));
			buf.read(&pList[nNum].nz,sizeof(double));
			buf.read(&pList[nNum].r,sizeof(float));
			buf.read(&pList[nNum].g,sizeof(float));
			buf.read(&pList[nNum].b,sizeof(float));
		}
		pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3fN3fC3f)
	{
// 		m_vVertexList = new ShadedVertex3f[m_lVertNum];
// 		ShadedVertex3f* pList = (ShadedVertex3f*)m_vVertexList;
// 		if (NULL == m_vVertexList)
// 			return false;

		ShadedVertex3f* pList = (ShadedVertex3f*)BufferManager::AllocBuff(sizeof(ShadedVertex3f) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		//��forѭ�������ֽڶ�������
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(float));
			buf.read(&pList[nNum].y,sizeof(float));
			buf.read(&pList[nNum].z,sizeof(float));
			buf.read(&pList[nNum].nx,sizeof(float));
			buf.read(&pList[nNum].ny,sizeof(float));
			buf.read(&pList[nNum].nz,sizeof(float));
			buf.read(&pList[nNum].r,sizeof(float));
			buf.read(&pList[nNum].g,sizeof(float));
			buf.read(&pList[nNum].b,sizeof(float));
		}
		pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3dT2dN3dC3f)
	{
// 		VersatileVertex3d* pList=NULL;
// 		m_vVertexList = new VersatileVertex3d[m_lVertNum];
// 		pList = (VersatileVertex3d*)m_vVertexList;
// 		if (NULL == m_vVertexList)
// 			return false;

		VersatileVertex3d* pList=  (VersatileVertex3d*)BufferManager::AllocBuff(sizeof(VersatileVertex3d) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		//��forѭ�������ֽڶ�������
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(double));
			buf.read(&pList[nNum].y,sizeof(double));
			buf.read(&pList[nNum].z,sizeof(double));
			buf.read(&pList[nNum].nx,sizeof(double));
			buf.read(&pList[nNum].ny,sizeof(double));
			buf.read(&pList[nNum].nz,sizeof(double));
			buf.read(&pList[nNum].tu,sizeof(double));
			buf.read(&pList[nNum].tv,sizeof(double));
			buf.read(&pList[nNum].r,sizeof(float));
			buf.read(&pList[nNum].g,sizeof(float));
			buf.read(&pList[nNum].b,sizeof(float));

		}
		pList = NULL;

	}
	else if(m_byVertexType == VERTEXTYPE_V3dT2dN3dC3f_WithoutRGB)
	{
		// 		VersatileVertex3d* pList=NULL;
		// 		m_vVertexList = new VersatileVertex3d[m_lVertNum];
		// 		pList = (VersatileVertex3d*)m_vVertexList;
		// 		if (NULL == m_vVertexList)
		// 			return false;

		VersatileVertex3dWithoutRGB* pList = (VersatileVertex3dWithoutRGB*)BufferManager::AllocBuff(sizeof(VersatileVertex3dWithoutRGB) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		//��forѭ�������ֽڶ�������
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(double));
			buf.read(&pList[nNum].y,sizeof(double));
			buf.read(&pList[nNum].z,sizeof(double));
			buf.read(&pList[nNum].nx,sizeof(double));
			buf.read(&pList[nNum].ny,sizeof(double));
			buf.read(&pList[nNum].nz,sizeof(double));
			buf.read(&pList[nNum].tu,sizeof(double));
			buf.read(&pList[nNum].tv,sizeof(double));

		}
		pList = NULL;

	}
	else if(m_byVertexType == VERTEXTYPE_V3fT2fN3fC3f)
	{
// 		m_vVertexList = new VersatileVertex3f[m_lVertNum];
// 		VersatileVertex3f* pList=NULL;
// 		pList = (VersatileVertex3f*)m_vVertexList;
// 		if (NULL == m_vVertexList)
// 			return false;

		VersatileVertex3f* pList = (VersatileVertex3f*)BufferManager::AllocBuff(sizeof(VersatileVertex3f) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		//��forѭ�������ֽڶ�������
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(float));
			buf.read(&pList[nNum].y,sizeof(float));
			buf.read(&pList[nNum].z,sizeof(float)); 
			buf.read(&pList[nNum].nx,sizeof(float));
			buf.read(&pList[nNum].ny,sizeof(float));
			buf.read(&pList[nNum].nz,sizeof(float));
			buf.read(&pList[nNum].tu,sizeof(float));
			buf.read(&pList[nNum].tv,sizeof(float));
			buf.read(&pList[nNum].r,sizeof(float));
			buf.read(&pList[nNum].g,sizeof(float));
			buf.read(&pList[nNum].b,sizeof(float));
		}
		pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3fT2fN3fC3f_WithoutRGB)
	{
		// 		m_vVertexList = new VersatileVertex3f[m_lVertNum];
		// 		VersatileVertex3f* pList=NULL;
		// 		pList = (VersatileVertex3f*)m_vVertexList;
		// 		if (NULL == m_vVertexList)
		// 			return false;

		VersatileVertex3fWithoutRGB* pList = (VersatileVertex3fWithoutRGB*)BufferManager::AllocBuff(sizeof(VersatileVertex3fWithoutRGB) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		//��forѭ�������ֽڶ�������
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(float));
			buf.read(&pList[nNum].y,sizeof(float));
			buf.read(&pList[nNum].z,sizeof(float)); 
			buf.read(&pList[nNum].nx,sizeof(float));
			buf.read(&pList[nNum].ny,sizeof(float));
			buf.read(&pList[nNum].nz,sizeof(float));
			buf.read(&pList[nNum].tu,sizeof(float));
			buf.read(&pList[nNum].tv,sizeof(float));
		}
		pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3dT2dT2dN3dC3f)
	{
// 		m_vVertexList = new SecondVersatileVertex3d[m_lVertNum];
// 		SecondVersatileVertex3d* pList=NULL;
// 		pList = (SecondVersatileVertex3d*)m_vVertexList;
// 		if (NULL == m_vVertexList)
// 			return false;

		SecondVersatileVertex3d* pList = (SecondVersatileVertex3d*)BufferManager::AllocBuff(sizeof(SecondVersatileVertex3d) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(double));
			buf.read(&pList[nNum].y,sizeof(double));
			buf.read(&pList[nNum].z,sizeof(double));
			buf.read(&pList[nNum].nx,sizeof(double));
			buf.read(&pList[nNum].ny,sizeof(double));
			buf.read(&pList[nNum].nz,sizeof(double));
			buf.read(&pList[nNum].tu,sizeof(double));
			buf.read(&pList[nNum].tv,sizeof(double));
			buf.read(&pList[nNum].tu2,sizeof(double));
			buf.read(&pList[nNum].tv2,sizeof(double));
			buf.read(&pList[nNum].r,sizeof(float));
			buf.read(&pList[nNum].g,sizeof(float));
			buf.read(&pList[nNum].b,sizeof(float));
		}
		pList = NULL;

	}
	else if(m_byVertexType == VERTEXTYPE_V3dT2dT2dN3dC3f_WithoutRGB)
	{
		// 		m_vVertexList = new SecondVersatileVertex3d[m_lVertNum];
		// 		SecondVersatileVertex3d* pList=NULL;
		// 		pList = (SecondVersatileVertex3d*)m_vVertexList;
		// 		if (NULL == m_vVertexList)
		// 			return false;

		SecondVersatileVertex3dWithoutRGB* pList = (SecondVersatileVertex3dWithoutRGB*)BufferManager::AllocBuff(sizeof(SecondVersatileVertex3dWithoutRGB) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(double));
			buf.read(&pList[nNum].y,sizeof(double));
			buf.read(&pList[nNum].z,sizeof(double));
			buf.read(&pList[nNum].nx,sizeof(double));
			buf.read(&pList[nNum].ny,sizeof(double));
			buf.read(&pList[nNum].nz,sizeof(double));
			buf.read(&pList[nNum].tu,sizeof(double));
			buf.read(&pList[nNum].tv,sizeof(double));
			buf.read(&pList[nNum].tu2,sizeof(double));
			buf.read(&pList[nNum].tv2,sizeof(double));

		}
		pList = NULL;

	}
	else if(m_byVertexType == VERTEXTYPE_V3fT2fT2fN3fC3f)
	{
// 		m_vVertexList = new SecondVersatileVertex3f[m_lVertNum];
// 		SecondVersatileVertex3f* pList=NULL;
// 		pList = (SecondVersatileVertex3f*)m_vVertexList;
// 		if (NULL == m_vVertexList)
// 			return false;

		SecondVersatileVertex3f* pList = (SecondVersatileVertex3f*)BufferManager::AllocBuff(sizeof(SecondVersatileVertex3f) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(float));
			buf.read(&pList[nNum].y,sizeof(float));
			buf.read(&pList[nNum].z,sizeof(float)); 
			buf.read(&pList[nNum].nx,sizeof(float));
			buf.read(&pList[nNum].ny,sizeof(float));
			buf.read(&pList[nNum].nz,sizeof(float));
			buf.read(&pList[nNum].tu,sizeof(float));
			buf.read(&pList[nNum].tv,sizeof(float));
			buf.read(&pList[nNum].tu2,sizeof(float));
			buf.read(&pList[nNum].tv2,sizeof(float));
			buf.read(&pList[nNum].r,sizeof(float));
			buf.read(&pList[nNum].g,sizeof(float));
			buf.read(&pList[nNum].b,sizeof(float));
		}
		pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3fT2fT2fN3fC3f_WithoutRGB)
	{
		// 		m_vVertexList = new SecondVersatileVertex3f[m_lVertNum];
		// 		SecondVersatileVertex3f* pList=NULL;
		// 		pList = (SecondVersatileVertex3f*)m_vVertexList;
		// 		if (NULL == m_vVertexList)
		// 			return false;

		SecondVersatileVertex3fWithoutRGB* pList = (SecondVersatileVertex3fWithoutRGB*)BufferManager::AllocBuff(sizeof(SecondVersatileVertex3fWithoutRGB) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(float));
			buf.read(&pList[nNum].y,sizeof(float));
			buf.read(&pList[nNum].z,sizeof(float)); 
			buf.read(&pList[nNum].nx,sizeof(float));
			buf.read(&pList[nNum].ny,sizeof(float));
			buf.read(&pList[nNum].nz,sizeof(float));
			buf.read(&pList[nNum].tu,sizeof(float));
			buf.read(&pList[nNum].tv,sizeof(float));
			buf.read(&pList[nNum].tu2,sizeof(float));
			buf.read(&pList[nNum].tv2,sizeof(float));
		}
		pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3dT2dT2dT2dN3dC3f)
	{
// 		m_vVertexList = new ThirdVersatileVertex3d[m_lVertNum];
// 		
// 		ThirdVersatileVertex3d* pList=NULL;
// 		pList = (ThirdVersatileVertex3d*)m_vVertexList;
// 		if (NULL == m_vVertexList)
// 			return false;

		ThirdVersatileVertex3d* pList = (ThirdVersatileVertex3d*)BufferManager::AllocBuff(sizeof(ThirdVersatileVertex3d) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(double));
			buf.read(&pList[nNum].y,sizeof(double));
			buf.read(&pList[nNum].z,sizeof(double));
			buf.read(&pList[nNum].nx,sizeof(double));
			buf.read(&pList[nNum].ny,sizeof(double));
			buf.read(&pList[nNum].nz,sizeof(double));
			buf.read(&pList[nNum].tu,sizeof(double));
			buf.read(&pList[nNum].tv,sizeof(double));
			buf.read(&pList[nNum].tu2,sizeof(double));
			buf.read(&pList[nNum].tv2,sizeof(double));
			buf.read(&pList[nNum].tu3,sizeof(double));
			buf.read(&pList[nNum].tv3,sizeof(double));
			buf.read(&pList[nNum].r,sizeof(float));
			buf.read(&pList[nNum].g,sizeof(float));
			buf.read(&pList[nNum].b,sizeof(float));
		}
		pList = NULL;

	}
	else if(m_byVertexType == VERTEXTYPE_V3dT2dT2dT2dN3dC3f_WithoutRGB)
	{
		// 		m_vVertexList = new ThirdVersatileVertex3d[m_lVertNum];
		// 		
		// 		ThirdVersatileVertex3d* pList=NULL;
		// 		pList = (ThirdVersatileVertex3d*)m_vVertexList;
		// 		if (NULL == m_vVertexList)
		// 			return false;

		ThirdVersatileVertex3dWithoutRGB* pList = (ThirdVersatileVertex3dWithoutRGB*)BufferManager::AllocBuff(sizeof(ThirdVersatileVertex3dWithoutRGB) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(double));
			buf.read(&pList[nNum].y,sizeof(double));
			buf.read(&pList[nNum].z,sizeof(double));
			buf.read(&pList[nNum].nx,sizeof(double));
			buf.read(&pList[nNum].ny,sizeof(double));
			buf.read(&pList[nNum].nz,sizeof(double));
			buf.read(&pList[nNum].tu,sizeof(double));
			buf.read(&pList[nNum].tv,sizeof(double));
			buf.read(&pList[nNum].tu2,sizeof(double));
			buf.read(&pList[nNum].tv2,sizeof(double));
			buf.read(&pList[nNum].tu3,sizeof(double));
			buf.read(&pList[nNum].tv3,sizeof(double));

		}
		pList = NULL;

	}
	else if(m_byVertexType == VERTEXTYPE_V3fT2fT2fT2fN3fC3f)
	{
// 		m_vVertexList = new ThirdVersatileVertex3f[m_lVertNum];
// 	
// 		ThirdVersatileVertex3f* pList=NULL;
// 		pList = (ThirdVersatileVertex3f*)m_vVertexList;
// 		if (NULL == m_vVertexList)
// 			return false;

		ThirdVersatileVertex3f* pList = (ThirdVersatileVertex3f*)BufferManager::AllocBuff(sizeof(ThirdVersatileVertex3f) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(float));
			buf.read(&pList[nNum].y,sizeof(float));
			buf.read(&pList[nNum].z,sizeof(float)); 
			buf.read(&pList[nNum].nx,sizeof(float));
			buf.read(&pList[nNum].ny,sizeof(float));
			buf.read(&pList[nNum].nz,sizeof(float));
			buf.read(&pList[nNum].tu,sizeof(float));
			buf.read(&pList[nNum].tv,sizeof(float));
			buf.read(&pList[nNum].tu2,sizeof(float));
			buf.read(&pList[nNum].tv2,sizeof(float));
			buf.read(&pList[nNum].tu3,sizeof(float));
			buf.read(&pList[nNum].tv3,sizeof(float));
			buf.read(&pList[nNum].r,sizeof(float));
			buf.read(&pList[nNum].g,sizeof(float));
			buf.read(&pList[nNum].b,sizeof(float));
		}
		pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3fT2fT2fT2fN3fC3f_WithoutRGB)
	{
		// 		m_vVertexList = new ThirdVersatileVertex3f[m_lVertNum];
		// 	
		// 		ThirdVersatileVertex3f* pList=NULL;
		// 		pList = (ThirdVersatileVertex3f*)m_vVertexList;
		// 		if (NULL == m_vVertexList)
		// 			return false;

		ThirdVersatileVertex3fWithoutRGB* pList = (ThirdVersatileVertex3fWithoutRGB*)BufferManager::AllocBuff(sizeof(ThirdVersatileVertex3fWithoutRGB) * m_lVertNum);
		m_vVertexList = pList;
		if (NULL == m_vVertexList)
			return false;

		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(float));
			buf.read(&pList[nNum].y,sizeof(float));
			buf.read(&pList[nNum].z,sizeof(float)); 
			buf.read(&pList[nNum].nx,sizeof(float));
			buf.read(&pList[nNum].ny,sizeof(float));
			buf.read(&pList[nNum].nz,sizeof(float));
			buf.read(&pList[nNum].tu,sizeof(float));
			buf.read(&pList[nNum].tv,sizeof(float));
			buf.read(&pList[nNum].tu2,sizeof(float));
			buf.read(&pList[nNum].tv2,sizeof(float));
			buf.read(&pList[nNum].tu3,sizeof(float));
			buf.read(&pList[nNum].tv3,sizeof(float));
		}
		pList = NULL;
	}
    

	//������������
	buf.read((char*)&m_lTriListSize,sizeof(long));
	if(m_lTriListSize > 0)
	{
		if (sizeof(long)* m_lTriListSize > buf.size()-buf.getPos())
			return false;

		m_lTriangleList = (long*)BufferManager::AllocBuff(sizeof(long)*m_lTriListSize);

		//m_lTriangleList = new long[m_lTriListSize];
		if (NULL == m_lTriangleList)
			return false;

		buf.read((char*)m_lTriangleList,sizeof(long) * m_lTriListSize);
	}

	//����������������
	buf.read((char*)&m_lStripListSize,sizeof(long));
	if(m_lStripListSize > 0)
	{
		if (sizeof(long)* m_lStripListSize > buf.size()-buf.getPos())
			return false;

		m_lStripIndices = (long*)BufferManager::AllocBuff(sizeof(long)*m_lStripListSize);
	//	m_lStripIndices = new long[m_lStripListSize];
		if (NULL == m_lStripIndices)
			return false;

		buf.read((char*)m_lStripIndices,sizeof(long) * m_lStripListSize);
	}

	//�������Ϊ0 ��ʾ���ݴ���
// 	if (m_lStripListSize == 0 && m_lTriListSize == 0)
// 		return false;

	return true;
 }


    //********************************************************************************** 
    //** �������ƣ� writeBuffer
    //** ���������� ������д��buf
    //** ��    �룺 Buffer����buf������           
    //** ��    ���� ��
    //** ����ֵ��	��
    //** ��    �ߣ� ����
    //** �������ڣ� 2012-04-11
    //**********************************************************************************
    void C3DTriangleMesh::writeBuffer(Buffer& buf)
    {
        C3DSurface::writeBuffer(buf);

        //���������Ϣ**************************

        //�������ͱ���

        buf.write((char*)&m_byVertexType,sizeof(unsigned char));

        //�����б�
        buf.write((char*)&m_lVertNum,sizeof(long));

        if((m_lVertNum > 0) && m_vVertexList)
        {	
            if(m_byVertexType == VERTEXTYPE_V3d)	
            {
                Vertex3d* pList = (Vertex3d*)m_vVertexList;
                //��forѭ�������ֽڶ�������
                for (int nNum=0; nNum < m_lVertNum; nNum++)
                {
                    buf.write(&pList[nNum].x,sizeof(double));
                    buf.write(&pList[nNum].y,sizeof(double));
                    buf.write(&pList[nNum].z,sizeof(double));
                }
                pList = NULL;
            }
            else if(m_byVertexType == VERTEXTYPE_V3f) 
            {
                Vertex3f* pList = (Vertex3f*)m_vVertexList;
                //��forѭ�������ֽڶ�������
                for (int nNum=0; nNum < m_lVertNum; nNum++)
                {
                    buf.write(&pList[nNum].x,sizeof(float));
                    buf.write(&pList[nNum].y,sizeof(float));
                    buf.write(&pList[nNum].z,sizeof(float));
                }
                pList = NULL;
            }
			else if (m_byVertexType == VERTEXTYPE_V3fN3f)
			{
				NormaledVertex3f* pList = (NormaledVertex3f*)m_vVertexList;
				//��forѭ�������ֽڶ�������
				for (int nNum=0; nNum < m_lVertNum; nNum++)
				{
					buf.write(&pList[nNum].x,sizeof(float));
					buf.write(&pList[nNum].y,sizeof(float));
					buf.write(&pList[nNum].z,sizeof(float));
					buf.write(&pList[nNum].nx,sizeof(float));
					buf.write(&pList[nNum].ny,sizeof(float));   
					buf.write(&pList[nNum].nz,sizeof(float));   
				}
				pList = NULL;
			}
			else if (m_byVertexType == VERTEXTYPE_V3dN3d)
			{
				NormaledVertex3d* pList = (NormaledVertex3d*)m_vVertexList;
				//��forѭ�������ֽڶ�������
				for (int nNum=0; nNum < m_lVertNum; nNum++)
				{
					buf.write(&pList[nNum].x,sizeof(double));
					buf.write(&pList[nNum].y,sizeof(double));
					buf.write(&pList[nNum].z,sizeof(double));
					buf.write(&pList[nNum].nx,sizeof(double));
					buf.write(&pList[nNum].ny,sizeof(double));   
					buf.write(&pList[nNum].nz,sizeof(double));   
				}
				pList = NULL;
			}
            else if(m_byVertexType == VERTEXTYPE_V3dT2d)
            {
                TexturedVertex3d* pList = (TexturedVertex3d*)m_vVertexList;
                //��forѭ�������ֽڶ�������
                for (int nNum=0; nNum < m_lVertNum; nNum++)
                {
                    buf.write(&pList[nNum].x,sizeof(double));
                    buf.write(&pList[nNum].y,sizeof(double));
                    buf.write(&pList[nNum].z,sizeof(double));
                    buf.write(&pList[nNum].tu,sizeof(double));
                    buf.write(&pList[nNum].tv,sizeof(double));   
                }
                pList = NULL;
            }
            else if(m_byVertexType == VERTEXTYPE_V3fT2f)
            {
                TexturedVertex3f* pList = (TexturedVertex3f*)m_vVertexList;
                //��forѭ�������ֽڶ�������
                for (int nNum=0; nNum < m_lVertNum; nNum++)
                {
                    buf.write(&pList[nNum].x,sizeof(float));
                    buf.write(&pList[nNum].y,sizeof(float));
                    buf.write(&pList[nNum].z,sizeof(float));
                    buf.write(&pList[nNum].tu,sizeof(float));
                    buf.write(&pList[nNum].tv,sizeof(float));   
                }
                pList = NULL;
            }
            else if(m_byVertexType == VERTEXTYPE_V3dN3dC3f)
            {
                ShadedVertex3d* pList = (ShadedVertex3d*)m_vVertexList;
                //��forѭ�������ֽڶ�������
                for (int nNum=0; nNum < m_lVertNum; nNum++)
                {
                    buf.write(&pList[nNum].x,sizeof(double));
                    buf.write(&pList[nNum].y,sizeof(double));
                    buf.write(&pList[nNum].z,sizeof(double));
                    buf.write(&pList[nNum].nx,sizeof(double));
                    buf.write(&pList[nNum].ny,sizeof(double));
                    buf.write(&pList[nNum].nz,sizeof(double));
                    buf.write(&pList[nNum].r,sizeof(float));
                    buf.write(&pList[nNum].g,sizeof(float));
                    buf.write(&pList[nNum].b,sizeof(float));
                }
                pList = NULL;
            }
            else if(m_byVertexType == VERTEXTYPE_V3fN3fC3f)
            {
                ShadedVertex3f* pList = (ShadedVertex3f*)m_vVertexList;
                //��forѭ�������ֽڶ�������
                for (int nNum=0; nNum < m_lVertNum; nNum++)
                {
                    buf.write(&pList[nNum].x,sizeof(float));
                    buf.write(&pList[nNum].y,sizeof(float));
                    buf.write(&pList[nNum].z,sizeof(float));
                    buf.write(&pList[nNum].nx,sizeof(float));
                    buf.write(&pList[nNum].ny,sizeof(float));
                    buf.write(&pList[nNum].nz,sizeof(float));
                    buf.write(&pList[nNum].r,sizeof(float));
                    buf.write(&pList[nNum].g,sizeof(float));
                    buf.write(&pList[nNum].b,sizeof(float));
                }
                pList = NULL;

            }
            else if(m_byVertexType == VERTEXTYPE_V3dT2dN3dC3f)
            {
                VersatileVertex3d* pList=NULL;
                pList = (VersatileVertex3d*)m_vVertexList;
                //��forѭ�������ֽڶ�������
                for (int nNum=0; nNum < m_lVertNum; nNum++)
                {
                    buf.write(&pList[nNum].x,sizeof(double));
                    buf.write(&pList[nNum].y,sizeof(double));
                    buf.write(&pList[nNum].z,sizeof(double));    
                    buf.write(&pList[nNum].nx,sizeof(double));
                    buf.write(&pList[nNum].ny,sizeof(double));
                    buf.write(&pList[nNum].nz,sizeof(double));
					buf.write(&pList[nNum].tu,sizeof(double));
					buf.write(&pList[nNum].tv,sizeof(double));
                    buf.write(&pList[nNum].r,sizeof(float));
                    buf.write(&pList[nNum].g,sizeof(float));
                    buf.write(&pList[nNum].b,sizeof(float));

                }
                pList = NULL;

            }
			else if(m_byVertexType == VERTEXTYPE_V3dT2dN3dC3f_WithoutRGB)
			{
				VersatileVertex3dWithoutRGB* pList=NULL;
				pList = (VersatileVertex3dWithoutRGB*)m_vVertexList;
				//��forѭ�������ֽڶ�������
				for (int nNum=0; nNum < m_lVertNum; nNum++)
				{
					buf.write(&pList[nNum].x,sizeof(double));
					buf.write(&pList[nNum].y,sizeof(double));
					buf.write(&pList[nNum].z,sizeof(double));    
					buf.write(&pList[nNum].nx,sizeof(double));
					buf.write(&pList[nNum].ny,sizeof(double));
					buf.write(&pList[nNum].nz,sizeof(double));
					buf.write(&pList[nNum].tu,sizeof(double));
					buf.write(&pList[nNum].tv,sizeof(double));

				}
				pList = NULL;

			}
            else if(m_byVertexType == VERTEXTYPE_V3fT2fN3fC3f)
            {
                VersatileVertex3f* pList=NULL;
                pList = (VersatileVertex3f*)m_vVertexList;
                //��forѭ�������ֽڶ�������
                for (int nNum=0; nNum < m_lVertNum; nNum++)
                {
                    buf.write(&pList[nNum].x,sizeof(float));
                    buf.write(&pList[nNum].y,sizeof(float));
                    buf.write(&pList[nNum].z,sizeof(float));
                    buf.write(&pList[nNum].nx,sizeof(float));
                    buf.write(&pList[nNum].ny,sizeof(float));
                    buf.write(&pList[nNum].nz,sizeof(float));
					buf.write(&pList[nNum].tu,sizeof(float));
					buf.write(&pList[nNum].tv,sizeof(float));
                    buf.write(&pList[nNum].r,sizeof(float));
                    buf.write(&pList[nNum].g,sizeof(float));
                    buf.write(&pList[nNum].b,sizeof(float));
                }
                pList = NULL;

            }
			else if(m_byVertexType == VERTEXTYPE_V3fT2fN3fC3f_WithoutRGB)
			{
				VersatileVertex3fWithoutRGB* pList=NULL;
				pList = (VersatileVertex3fWithoutRGB*)m_vVertexList;
				//��forѭ�������ֽڶ�������
				for (int nNum=0; nNum < m_lVertNum; nNum++)
				{
					buf.write(&pList[nNum].x,sizeof(float));
					buf.write(&pList[nNum].y,sizeof(float));
					buf.write(&pList[nNum].z,sizeof(float));
					buf.write(&pList[nNum].nx,sizeof(float));
					buf.write(&pList[nNum].ny,sizeof(float));
					buf.write(&pList[nNum].nz,sizeof(float));
					buf.write(&pList[nNum].tu,sizeof(float));
					buf.write(&pList[nNum].tv,sizeof(float));
				}
				pList = NULL;

			}
			else if(m_byVertexType == VERTEXTYPE_V3dT2dT2dN3dC3f)
			{
				SecondVersatileVertex3d* pList=NULL;
				pList = (SecondVersatileVertex3d*)m_vVertexList;
				for (int nNum=0; nNum < m_lVertNum; nNum++)
				{
					buf.write(&pList[nNum].x,sizeof(double));
					buf.write(&pList[nNum].y,sizeof(double));
					buf.write(&pList[nNum].z,sizeof(double));    
					buf.write(&pList[nNum].nx,sizeof(double));
					buf.write(&pList[nNum].ny,sizeof(double));
					buf.write(&pList[nNum].nz,sizeof(double));
					buf.write(&pList[nNum].tu,sizeof(double));
					buf.write(&pList[nNum].tv,sizeof(double));
					buf.write(&pList[nNum].tu2,sizeof(double));
					buf.write(&pList[nNum].tv2,sizeof(double));
					buf.write(&pList[nNum].r,sizeof(float));
					buf.write(&pList[nNum].g,sizeof(float));
					buf.write(&pList[nNum].b,sizeof(float));
				}
				pList = NULL;
			}
			else if(m_byVertexType == VERTEXTYPE_V3dT2dT2dN3dC3f_WithoutRGB)
			{
				SecondVersatileVertex3dWithoutRGB* pList=NULL;
				pList = (SecondVersatileVertex3dWithoutRGB*)m_vVertexList;
				for (int nNum=0; nNum < m_lVertNum; nNum++)
				{
					buf.write(&pList[nNum].x,sizeof(double));
					buf.write(&pList[nNum].y,sizeof(double));
					buf.write(&pList[nNum].z,sizeof(double));    
					buf.write(&pList[nNum].nx,sizeof(double));
					buf.write(&pList[nNum].ny,sizeof(double));
					buf.write(&pList[nNum].nz,sizeof(double));
					buf.write(&pList[nNum].tu,sizeof(double));
					buf.write(&pList[nNum].tv,sizeof(double));
					buf.write(&pList[nNum].tu2,sizeof(double));
					buf.write(&pList[nNum].tv2,sizeof(double));
				}
				pList = NULL;
			}
			else if(m_byVertexType == VERTEXTYPE_V3fT2fT2fN3fC3f)
			{
				SecondVersatileVertex3f* pList=NULL;
				pList = (SecondVersatileVertex3f*)m_vVertexList;
				for (int nNum=0; nNum < m_lVertNum; nNum++)
				{
					buf.write(&pList[nNum].x,sizeof(float));
					buf.write(&pList[nNum].y,sizeof(float));
					buf.write(&pList[nNum].z,sizeof(float));
					buf.write(&pList[nNum].nx,sizeof(float));
					buf.write(&pList[nNum].ny,sizeof(float));
					buf.write(&pList[nNum].nz,sizeof(float));
					buf.write(&pList[nNum].tu,sizeof(float));
					buf.write(&pList[nNum].tv,sizeof(float));
					buf.write(&pList[nNum].tu2,sizeof(float));
					buf.write(&pList[nNum].tv2,sizeof(float));
					buf.write(&pList[nNum].r,sizeof(float));
					buf.write(&pList[nNum].g,sizeof(float));
					buf.write(&pList[nNum].b,sizeof(float));
				}
				pList = NULL;
			}
			else if(m_byVertexType == VERTEXTYPE_V3fT2fT2fN3fC3f_WithoutRGB)
			{
				SecondVersatileVertex3fWithoutRGB* pList=NULL;
				pList = (SecondVersatileVertex3fWithoutRGB*)m_vVertexList;
				for (int nNum=0; nNum < m_lVertNum; nNum++)
				{
					buf.write(&pList[nNum].x,sizeof(float));
					buf.write(&pList[nNum].y,sizeof(float));
					buf.write(&pList[nNum].z,sizeof(float));
					buf.write(&pList[nNum].nx,sizeof(float));
					buf.write(&pList[nNum].ny,sizeof(float));
					buf.write(&pList[nNum].nz,sizeof(float));
					buf.write(&pList[nNum].tu,sizeof(float));
					buf.write(&pList[nNum].tv,sizeof(float));
					buf.write(&pList[nNum].tu2,sizeof(float));
					buf.write(&pList[nNum].tv2,sizeof(float));
				}
				pList = NULL;
			}
			else if(m_byVertexType == VERTEXTYPE_V3dT2dT2dT2dN3dC3f)
			{
				ThirdVersatileVertex3d* pList=NULL;
				pList = (ThirdVersatileVertex3d*)m_vVertexList;
				for (int nNum=0; nNum < m_lVertNum; nNum++)
				{
					buf.write(&pList[nNum].x,sizeof(double));
					buf.write(&pList[nNum].y,sizeof(double));
					buf.write(&pList[nNum].z,sizeof(double));    
					buf.write(&pList[nNum].nx,sizeof(double));
					buf.write(&pList[nNum].ny,sizeof(double));
					buf.write(&pList[nNum].nz,sizeof(double));
					buf.write(&pList[nNum].tu,sizeof(double));
					buf.write(&pList[nNum].tv,sizeof(double));
					buf.write(&pList[nNum].tu2,sizeof(double));
					buf.write(&pList[nNum].tv2,sizeof(double));
					buf.write(&pList[nNum].tu3,sizeof(double));
					buf.write(&pList[nNum].tv3,sizeof(double));
					buf.write(&pList[nNum].r,sizeof(float));
					buf.write(&pList[nNum].g,sizeof(float));
					buf.write(&pList[nNum].b,sizeof(float));
				}
				pList = NULL;
			}
			else if(m_byVertexType == VERTEXTYPE_V3dT2dT2dT2dN3dC3f_WithoutRGB)
			{
				ThirdVersatileVertex3dWithoutRGB* pList=NULL;
				pList = (ThirdVersatileVertex3dWithoutRGB*)m_vVertexList;
				for (int nNum=0; nNum < m_lVertNum; nNum++)
				{
					buf.write(&pList[nNum].x,sizeof(double));
					buf.write(&pList[nNum].y,sizeof(double));
					buf.write(&pList[nNum].z,sizeof(double));    
					buf.write(&pList[nNum].nx,sizeof(double));
					buf.write(&pList[nNum].ny,sizeof(double));
					buf.write(&pList[nNum].nz,sizeof(double));
					buf.write(&pList[nNum].tu,sizeof(double));
					buf.write(&pList[nNum].tv,sizeof(double));
					buf.write(&pList[nNum].tu2,sizeof(double));
					buf.write(&pList[nNum].tv2,sizeof(double));
					buf.write(&pList[nNum].tu3,sizeof(double));
					buf.write(&pList[nNum].tv3,sizeof(double));
				}
				pList = NULL;
			}
			else if(m_byVertexType == VERTEXTYPE_V3fT2fT2fT2fN3fC3f)
			{
				ThirdVersatileVertex3f* pList=NULL;
				pList = (ThirdVersatileVertex3f*)m_vVertexList;
				for (int nNum=0; nNum < m_lVertNum; nNum++)
				{
					buf.write(&pList[nNum].x,sizeof(float));
					buf.write(&pList[nNum].y,sizeof(float));
					buf.write(&pList[nNum].z,sizeof(float));
					buf.write(&pList[nNum].nx,sizeof(float));
					buf.write(&pList[nNum].ny,sizeof(float));
					buf.write(&pList[nNum].nz,sizeof(float));
					buf.write(&pList[nNum].tu,sizeof(float));
					buf.write(&pList[nNum].tv,sizeof(float));
					buf.write(&pList[nNum].tu2,sizeof(float));
					buf.write(&pList[nNum].tv2,sizeof(float));
					buf.write(&pList[nNum].tu3,sizeof(float));
					buf.write(&pList[nNum].tv3,sizeof(float));
					buf.write(&pList[nNum].r,sizeof(float));
					buf.write(&pList[nNum].g,sizeof(float));
					buf.write(&pList[nNum].b,sizeof(float));
				}
				pList = NULL;
			}
		else if(m_byVertexType == VERTEXTYPE_V3fT2fT2fT2fN3fC3f_WithoutRGB)
		{
			ThirdVersatileVertex3fWithoutRGB* pList=NULL;
			pList = (ThirdVersatileVertex3fWithoutRGB*)m_vVertexList;
			for (int nNum=0; nNum < m_lVertNum; nNum++)
			{
				buf.write(&pList[nNum].x,sizeof(float));
				buf.write(&pList[nNum].y,sizeof(float));
				buf.write(&pList[nNum].z,sizeof(float));
				buf.write(&pList[nNum].nx,sizeof(float));
				buf.write(&pList[nNum].ny,sizeof(float));
				buf.write(&pList[nNum].nz,sizeof(float));
				buf.write(&pList[nNum].tu,sizeof(float));
				buf.write(&pList[nNum].tv,sizeof(float));
				buf.write(&pList[nNum].tu2,sizeof(float));
				buf.write(&pList[nNum].tv2,sizeof(float));
				buf.write(&pList[nNum].tu3,sizeof(float));
				buf.write(&pList[nNum].tv3,sizeof(float));
			}
			pList = NULL;
			}
		}

        //������������

        buf.write((char*)&m_lTriListSize,sizeof(long));
        if(m_lTriListSize > 0)
        {
            buf.write((char*)m_lTriangleList,sizeof(long) * m_lTriListSize);
        }

        //����������������

        buf.write((char*)&m_lStripListSize,sizeof(long));
        if(m_lStripListSize > 0)
        {
            buf.write((char*)m_lStripIndices,sizeof(long) * m_lStripListSize);
        }	

    }

	int C3DTriangleMesh::GetVertexStrideFromType(int nType)
	{

		switch (nType)
		{

		//case VERTEXTYPE_V3d:
		//	{	
		//		return Vertex3d::sizeBuffer();
		//	}
		//case  VERTEXTYPE_V3f:
		//	{
		//		return Vertex3f::sizeBuffer();
		//	}
		//case VERTEXTYPE_V3dT2d:
		//	{
		//		return TexturedVertex3d::sizeBuffer();
		//	}
		//case VERTEXTYPE_V3fT2f:
		//	{
		//		return TexturedVertex3f::sizeBuffer();	
		//	}
		//case  VERTEXTYPE_V3dN3dC3f:
		//	{
		//		return ShadedVertex3d::sizeBuffer();
		//	}
		//case  VERTEXTYPE_V3fN3fC3f:
		//	{
		//		return ShadedVertex3f::sizeBuffer();
		//	}
		case  VERTEXTYPE_V3dT2dN3dC3f:
			{
				return VersatileVertex3d::sizeBuffer();
			}
	/*	case  VERTEXTYPE_V3dT2dN3dC3f_WithoutRGB:
			{
				return VersatileVertex3dWithoutRGB::sizeBuffer();
			}
		case  VERTEXTYPE_V3fT2fN3fC3f:
			{
				return VersatileVertex3f::sizeBuffer();
			}
		case  VERTEXTYPE_V3fT2fN3fC3f_WithoutRGB:
			{
				return VersatileVertex3fWithoutRGB::sizeBuffer();
			}
		case  VERTEXTYPE_V3dT2dT2dN3dC3f:
			{
				return SecondVersatileVertex3d::sizeBuffer();
			}
		case  VERTEXTYPE_V3dT2dT2dN3dC3f_WithoutRGB:
			{
				return SecondVersatileVertex3dWithoutRGB::sizeBuffer();
			}
		case  VERTEXTYPE_V3fT2fT2fN3fC3f:
			{
				return SecondVersatileVertex3f::sizeBuffer();
			}
		case  VERTEXTYPE_V3fT2fT2fN3fC3f_WithoutRGB:
			{
				return SecondVersatileVertex3fWithoutRGB::sizeBuffer();
			}
		case  VERTEXTYPE_V3dT2dT2dT2dN3dC3f:
			{
				return ThirdVersatileVertex3d::sizeBuffer();
			}
		case  VERTEXTYPE_V3dT2dT2dT2dN3dC3f_WithoutRGB:
			{
				return ThirdVersatileVertex3dWithoutRGB::sizeBuffer();
			}
		case  VERTEXTYPE_V3fT2fT2fT2fN3fC3f:
			{
				return ThirdVersatileVertex3f::sizeBuffer();
			}
		case  VERTEXTYPE_V3fT2fT2fT2fN3fC3f_WithoutRGB:
			{
				return ThirdVersatileVertex3fWithoutRGB::sizeBuffer();
			}*/
		default:
			break;
		}

		return 0;
	}

size_t C3DTriangleMesh::sizeBuffer()
{
	size_t nSize = 0;
    nSize += C3DSurface::sizeBuffer();
	nSize+=sizeof(byte);//�������ͱ���
	nSize+=sizeof(long);//�����б���

	//���������綥������
	//*************************************************
	size_t nSize1 = nSize + GetVertexStrideFromType(m_byVertexType) * m_lVertNum;
	nSize1+=sizeof(long);//��������������
	nSize1+=sizeof(long)*m_lTriListSize;//������������
	nSize1+=sizeof(long);//������������������
	nSize1+=sizeof(long)*m_lStripListSize;//����������������
	return nSize1;

}



//********************************************************************************** 
//** �������ƣ� SetVertices
//** ���������� ���ö����б�Ͷ����б��ȣ���������
//** ��    �룺 vVertexList	�����б�ĵ�ַ ��lVertNum	�����б��ȵĵ�ַ  
//**			byVerType ��������
//**			lBufSize  ����Buffer����
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-06-9
//**********************************************************************************
void C3DTriangleMesh::SetVertices(void* vVertexList,long lVertNum, long lBufSize, byte byVerType)
{
	FreeVertexBuffer();

	m_vVertexList = vVertexList;
	m_lVertNum = lVertNum;
	m_byVertexType = byVerType;

}

void C3DTriangleMesh::SetTriangles(long* const lTriangleList, long lTriListSize)
{
	FreeIndexBuffer();
	m_lTriListSize = lTriListSize;
	m_lTriangleList = lTriangleList;
}

bool C3DTriangleMesh::DoubleVertex2FloatVertex(bool bInverseTexCood)
{
	byte nDestVerType = VERTEXTYPE_End;
	if (m_lVertNum<=0)
		return false;

	switch (m_byVertexType)
	{
	case VERTEXTYPE_V3f:			// for Vertex3f
	case VERTEXTYPE_V3fN3fC3f:		// for ShadedVertex3f
		{
			return true;
		}

	case VERTEXTYPE_V3fT2f:			// for TexturedVertex3f
		{
			TexturedVertex3f* pVerSrcBuf = (TexturedVertex3f*)m_vVertexList;
			for (int i=0; i<m_lVertNum;i++)
			{
				pVerSrcBuf[i].tv = 1.0f - pVerSrcBuf[i].tv;
			}
			return true;
		}

	case VERTEXTYPE_V3fT2fN3fC3f:	// for VersatileVertex3f
		{
			if (!bInverseTexCood)
				return true;

			VersatileVertex3f* pVerSrcBuf = (VersatileVertex3f*)m_vVertexList;
			for (int i=0; i<m_lVertNum;i++)
				pVerSrcBuf[i].tv = 1.0f - pVerSrcBuf[i].tv;
			return true;
		}

		//////////////////////////////////////////////////////////////////////////
		//double����

	case VERTEXTYPE_V3d:				// for Vertex3d
		{
			long nDestBuffer = sizeof(Vertex3f)*m_lVertNum;
			Vertex3f* pVerDestBuf = (Vertex3f*)BufferManager::AllocBuff(nDestBuffer);
			if (NULL == pVerDestBuf)
				return false;

			Vertex3d* pVerSrcBuf = (Vertex3d*)m_vVertexList;
			for (int i=0; i<m_lVertNum;i++)
			{
				pVerDestBuf[i].x = (float)pVerSrcBuf[i].x;
				pVerDestBuf[i].y = (float)pVerSrcBuf[i].y;
				pVerDestBuf[i].z = (float)pVerSrcBuf[i].z;
			}
			
			nDestVerType = VERTEXTYPE_V3f;
			SetVertices(pVerDestBuf, m_lVertNum, nDestBuffer, nDestVerType);
			return true;
		}
	case VERTEXTYPE_V3dT2d:			// for TexturedVertex3d
		{
			long nDestBuffer = sizeof(TexturedVertex3f)*m_lVertNum;
			TexturedVertex3f* pVerDestBuf ;/*= (TexturedVertex3f*)BufferManager::AllocBuff(nDestBuffer);*/
			if (NULL == pVerDestBuf)
				return false;

			TexturedVertex3d* pVerSrcBuf = (TexturedVertex3d*)m_vVertexList;

			for (int i=0; i<m_lVertNum;i++)
			{
				pVerDestBuf[i].x = (float)pVerSrcBuf[i].x;
				pVerDestBuf[i].y = (float)pVerSrcBuf[i].y;
				pVerDestBuf[i].z = (float)pVerSrcBuf[i].z;

				pVerDestBuf[i].tu = (float)pVerSrcBuf[i].tu;
				pVerDestBuf[i].tv = (float)(1.0 - pVerSrcBuf[i].tv);
			}

			nDestVerType = VERTEXTYPE_V3fT2f;
			SetVertices(pVerDestBuf, m_lVertNum, nDestBuffer, nDestVerType);
			return true;
		}

	case VERTEXTYPE_V3dN3dC3f:		// for ShadedVertex3d
		{
			long nDestBuffer = sizeof(ShadedVertex3f)*m_lVertNum;
			ShadedVertex3f* pVerDestBuf /*= (ShadedVertex3f*)BufferManager::AllocBuff(nDestBuffer)*/;
			if (NULL == pVerDestBuf)
				return false;

			ShadedVertex3d* pVerSrcBuf = (ShadedVertex3d*)m_vVertexList;

			for (int i=0; i<m_lVertNum;i++)
			{
				pVerDestBuf[i].x = (float)pVerSrcBuf[i].x;
				pVerDestBuf[i].y = (float)pVerSrcBuf[i].y;
				pVerDestBuf[i].z = (float)pVerSrcBuf[i].z;

				pVerDestBuf[i].nx = (float)pVerSrcBuf[i].nx;
				pVerDestBuf[i].ny = (float)pVerSrcBuf[i].ny;
				pVerDestBuf[i].nz = (float)pVerSrcBuf[i].nz;

				//color ��float
				pVerDestBuf[i].r = (float)pVerSrcBuf[i].r;
				pVerDestBuf[i].g = (float)pVerSrcBuf[i].g;
				pVerDestBuf[i].b = (float)pVerSrcBuf[i].b;
			}
			nDestVerType = VERTEXTYPE_V3fN3fC3f;
			SetVertices(pVerDestBuf, m_lVertNum, nDestBuffer, nDestVerType);
			return true;
		}
	case VERTEXTYPE_V3dT2dN3dC3f:	// for VersatileVertex3d
		{
			long nDestBuffer = sizeof(VersatileVertex3f)*m_lVertNum;
			VersatileVertex3f* pVerDestBuf /*= (VersatileVertex3f*)BufferManager::AllocBuff(nDestBuffer)*/;
			if (NULL == pVerDestBuf)
				return false;

			VersatileVertex3d* pVerSrcBuf = (VersatileVertex3d*)m_vVertexList;

			for (int i=0; i<m_lVertNum;i++)
			{
				pVerDestBuf[i].x = (float)pVerSrcBuf[i].x;
				pVerDestBuf[i].y = (float)pVerSrcBuf[i].y;
				pVerDestBuf[i].z = (float)pVerSrcBuf[i].z;

				pVerDestBuf[i].nx = (float)pVerSrcBuf[i].nx;
				pVerDestBuf[i].ny = (float)pVerSrcBuf[i].ny;
				pVerDestBuf[i].nz = (float)pVerSrcBuf[i].nz;

				pVerDestBuf[i].tu = (float)pVerSrcBuf[i].tu;
				pVerDestBuf[i].tv = (float)(1.0 - pVerSrcBuf[i].tv);

				//color ��float
				pVerDestBuf[i].r = (float)pVerSrcBuf[i].r;
				pVerDestBuf[i].g = (float)pVerSrcBuf[i].g;
				pVerDestBuf[i].b = (float)pVerSrcBuf[i].b;
			}

			nDestVerType = VERTEXTYPE_V3fT2fN3fC3f;
			SetVertices(pVerDestBuf, m_lVertNum, nDestBuffer, nDestVerType);
			return true;
		}
	case VERTEXTYPE_V3dT2dT2dN3dC3f:	// for VersatileVertex3d
		{
			long nDestBuffer = sizeof(SecondVersatileVertex3f)*m_lVertNum;
			SecondVersatileVertex3f* pVerDestBuf/* = (SecondVersatileVertex3f*)BufferManager::AllocBuff(nDestBuffer)*/;
			if (NULL == pVerDestBuf)
				return false;

			SecondVersatileVertex3d* pVerSrcBuf = (SecondVersatileVertex3d*)m_vVertexList;
			for (int i=0; i<m_lVertNum;i++)
			{
				pVerDestBuf[i].x = (float)pVerSrcBuf[i].x;
				pVerDestBuf[i].y = (float)pVerSrcBuf[i].y;
				pVerDestBuf[i].z = (float)pVerSrcBuf[i].z;

				pVerDestBuf[i].nx = (float)pVerSrcBuf[i].nx;
				pVerDestBuf[i].ny = (float)pVerSrcBuf[i].ny;
				pVerDestBuf[i].nz = (float)pVerSrcBuf[i].nz;

				pVerDestBuf[i].tu = (float)pVerSrcBuf[i].tu;
				pVerDestBuf[i].tv = (float)(1.0 - pVerSrcBuf[i].tv);

				pVerDestBuf[i].tu2 = (float)pVerSrcBuf[i].tu2;
				pVerDestBuf[i].tv2 = (float)(1.0 - pVerSrcBuf[i].tv2);

				//color ��float
				pVerDestBuf[i].r = (float)pVerSrcBuf[i].r;
				pVerDestBuf[i].g = (float)pVerSrcBuf[i].g;
				pVerDestBuf[i].b = (float)pVerSrcBuf[i].b;
			}

			nDestVerType = VERTEXTYPE_V3fT2fT2fN3fC3f;
			SetVertices(pVerDestBuf, m_lVertNum, nDestBuffer, nDestVerType);
			return true;
		}
	case VERTEXTYPE_V3dT2dT2dT2dN3dC3f:	// for VersatileVertex3d
		{
			long nDestBuffer = sizeof(ThirdVersatileVertex3f)*m_lVertNum;
			ThirdVersatileVertex3f* pVerDestBuf /*= (ThirdVersatileVertex3f*)BufferManager::AllocBuff(nDestBuffer)*/;
			if (NULL == pVerDestBuf)
				return false;

			ThirdVersatileVertex3d* pVerSrcBuf = (ThirdVersatileVertex3d*)m_vVertexList;

			for (int i=0; i<m_lVertNum;i++)
			{
				pVerDestBuf[i].x = (float)pVerSrcBuf[i].x;
				pVerDestBuf[i].y = (float)pVerSrcBuf[i].y;
				pVerDestBuf[i].z = (float)pVerSrcBuf[i].z;

				pVerDestBuf[i].nx = (float)pVerSrcBuf[i].nx;
				pVerDestBuf[i].ny = (float)pVerSrcBuf[i].ny;
				pVerDestBuf[i].nz = (float)pVerSrcBuf[i].nz;

				pVerDestBuf[i].tu = (float)pVerSrcBuf[i].tu;
				pVerDestBuf[i].tv = (float)(1.0 - pVerSrcBuf[i].tv);

				pVerDestBuf[i].tu2 = (float)pVerSrcBuf[i].tu2;
				pVerDestBuf[i].tv2 = (float)(1.0 - pVerSrcBuf[i].tv2);

				pVerDestBuf[i].tu3 = (float)pVerSrcBuf[i].tu3;
				pVerDestBuf[i].tv3 = (float)(1.0 - pVerSrcBuf[i].tv3);

				//color ��float
				pVerDestBuf[i].r = (float)pVerSrcBuf[i].r;
				pVerDestBuf[i].g = (float)pVerSrcBuf[i].g;
				pVerDestBuf[i].b = (float)pVerSrcBuf[i].b;
			}
			nDestVerType = VERTEXTYPE_V3fT2fT2fT2fN3fC3f;
			SetVertices(pVerDestBuf, m_lVertNum, nDestBuffer, nDestVerType);
			return true;
		}
	case VERTEXTYPE_V3dT2dN3dC3f_WithoutRGB:	// for VersatileVertex3dwithoutRGB
		{
			long nDestBuffer = sizeof(VersatileVertex3fWithoutRGB)*m_lVertNum;
			VersatileVertex3fWithoutRGB* pVerDestBuf /*= (VersatileVertex3fWithoutRGB*)BufferManager::AllocBuff(nDestBuffer)*/;
			if (NULL == pVerDestBuf)
				return false;

			VersatileVertex3dWithoutRGB* pVerSrcBuf = (VersatileVertex3dWithoutRGB*)m_vVertexList;

			for (int i=0; i<m_lVertNum;i++)
			{
				pVerDestBuf[i].x = (float)pVerSrcBuf[i].x;
				pVerDestBuf[i].y = (float)pVerSrcBuf[i].y;
				pVerDestBuf[i].z = (float)pVerSrcBuf[i].z;

				pVerDestBuf[i].nx = (float)pVerSrcBuf[i].nx;
				pVerDestBuf[i].ny = (float)pVerSrcBuf[i].ny;
				pVerDestBuf[i].nz = (float)pVerSrcBuf[i].nz;

				pVerDestBuf[i].tu = (float)pVerSrcBuf[i].tu;
				pVerDestBuf[i].tv = (float)(1.0 - pVerSrcBuf[i].tv);

				////color ��float
				//pVerDestBuf[i].r = (float)pVerSrcBuf[i].r;
				//pVerDestBuf[i].g = (float)pVerSrcBuf[i].g;
				//pVerDestBuf[i].b = (float)pVerSrcBuf[i].b;
			}

			nDestVerType = VERTEXTYPE_V3fT2fN3fC3f_WithoutRGB;
			SetVertices(pVerDestBuf, m_lVertNum, nDestBuffer, nDestVerType);
			return true;
		}
	case VERTEXTYPE_V3dT2dT2dN3dC3f_WithoutRGB:	// for VersatileVertex3d
		{
			long nDestBuffer = sizeof(SecondVersatileVertex3fWithoutRGB)*m_lVertNum;
			SecondVersatileVertex3fWithoutRGB* pVerDestBuf = (SecondVersatileVertex3fWithoutRGB*)BufferManager::AllocBuff(nDestBuffer);
			if (NULL == pVerDestBuf)
				return false;

			SecondVersatileVertex3dWithoutRGB* pVerSrcBuf = (SecondVersatileVertex3dWithoutRGB*)m_vVertexList;
			for (int i=0; i<m_lVertNum;i++)
			{
				pVerDestBuf[i].x = (float)pVerSrcBuf[i].x;
				pVerDestBuf[i].y = (float)pVerSrcBuf[i].y;
				pVerDestBuf[i].z = (float)pVerSrcBuf[i].z;

				pVerDestBuf[i].nx = (float)pVerSrcBuf[i].nx;
				pVerDestBuf[i].ny = (float)pVerSrcBuf[i].ny;
				pVerDestBuf[i].nz = (float)pVerSrcBuf[i].nz;

				pVerDestBuf[i].tu = (float)pVerSrcBuf[i].tu;
				pVerDestBuf[i].tv = (float)(1.0 - pVerSrcBuf[i].tv);

				pVerDestBuf[i].tu2 = (float)pVerSrcBuf[i].tu2;
				pVerDestBuf[i].tv2 = (float)(1.0 - pVerSrcBuf[i].tv2);

				////color ��float
				//pVerDestBuf[i].r = (float)pVerSrcBuf[i].r;
				//pVerDestBuf[i].g = (float)pVerSrcBuf[i].g;
				//pVerDestBuf[i].b = (float)pVerSrcBuf[i].b;
			}

			nDestVerType = VERTEXTYPE_V3fT2fT2fN3fC3f_WithoutRGB;
			SetVertices(pVerDestBuf, m_lVertNum, nDestBuffer, nDestVerType);
			return true;
		}
	case VERTEXTYPE_V3dT2dT2dT2dN3dC3f_WithoutRGB:	// for VersatileVertex3d
		{
			long nDestBuffer = sizeof(ThirdVersatileVertex3fWithoutRGB)*m_lVertNum;
			ThirdVersatileVertex3fWithoutRGB* pVerDestBuf /*= (ThirdVersatileVertex3fWithoutRGB*)BufferManager::AllocBuff(nDestBuffer)*/;
			if (NULL == pVerDestBuf)
				return false;

			ThirdVersatileVertex3dWithoutRGB* pVerSrcBuf = (ThirdVersatileVertex3dWithoutRGB*)m_vVertexList;

			for (int i=0; i<m_lVertNum;i++)
			{
				pVerDestBuf[i].x = (float)pVerSrcBuf[i].x;
				pVerDestBuf[i].y = (float)pVerSrcBuf[i].y;
				pVerDestBuf[i].z = (float)pVerSrcBuf[i].z;

				pVerDestBuf[i].nx = (float)pVerSrcBuf[i].nx;
				pVerDestBuf[i].ny = (float)pVerSrcBuf[i].ny;
				pVerDestBuf[i].nz = (float)pVerSrcBuf[i].nz;

				pVerDestBuf[i].tu = (float)pVerSrcBuf[i].tu;
				pVerDestBuf[i].tv = (float)(1.0 - pVerSrcBuf[i].tv);

				pVerDestBuf[i].tu2 = (float)pVerSrcBuf[i].tu2;
				pVerDestBuf[i].tv2 = (float)(1.0 - pVerSrcBuf[i].tv2);

				pVerDestBuf[i].tu3 = (float)pVerSrcBuf[i].tu3;
				pVerDestBuf[i].tv3 = (float)(1.0 - pVerSrcBuf[i].tv3);

				////color ��float
				//pVerDestBuf[i].r = (float)pVerSrcBuf[i].r;
				//pVerDestBuf[i].g = (float)pVerSrcBuf[i].g;
				//pVerDestBuf[i].b = (float)pVerSrcBuf[i].b;
			}
			nDestVerType = VERTEXTYPE_V3fT2fT2fT2fN3fC3f_WithoutRGB;
			SetVertices(pVerDestBuf, m_lVertNum, nDestBuffer, nDestVerType);
			return true;
		}
	default:
		return false;
	}

	return true;
}

void C3DTriangleMesh::FreeVertexBuffer()
{
	if (NULL != m_vVertexList)
	{
		BufferManager::FreeBuffer((unsigned char*)m_vVertexList, GetVertexStrideFromType(m_byVertexType)*m_lVertNum);
		m_vVertexList = NULL;
	}

	//ReleaseVertexArray(m_byVertexType, m_vVertexList);
}

void C3DTriangleMesh::FreeIndexBuffer()
{
	if (NULL != m_lTriangleList)
	{
//		BufferManager::FreeBuffer((unsigned char*)m_lTriangleList, sizeof(long)*m_lTriListSize);
		m_lTriangleList = NULL;
	}
}