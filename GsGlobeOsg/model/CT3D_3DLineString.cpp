//********************************************************************************** 
//** �ļ����ƣ�CT3D_C3DLineString.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�������ʵ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-11
//********************************************************************************** 


#include "CT3D_3DLineString.h"
#include "CT3D_ShadedVertex3d.h"
#include "CT3D_ShadedVertex3f.h"
#include "CT3D_TexturedVertex3d.h"
#include "CT3D_TexturedVertex3f.h"
#include "CT3D_ThirdVersatileVertex3d.h"
#include "CT3D_ThirdVersatileVertex3f.h"
#include "Buffer.h"


//********************************************************************************** 
//** �������ƣ� C3DLineString
//** ���������� ���캯��1
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************	
C3DLineString::C3DLineString()
{
    m_lVertNum = 0;
    m_vVertices = NULL;
    m_byTypeID = GEOTYPE_3D_LINESTRING;
    m_byVertexType = VERTEXTYPE_V3d;
    m_dLineWidth = 0.0;
}

//********************************************************************************** 
//** �������ƣ� C3DLineString
//** ���������� ���캯��2
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
C3DLineString::C3DLineString(int nVertNum, void* const vVertices, unsigned char vertexType, double dLineWidth):	
m_lVertNum(nVertNum), m_vVertices(vVertices), m_byVertexType(vertexType), m_dLineWidth(dLineWidth)
{
    m_byTypeID = GEOTYPE_3D_LINESTRING;
}

//********************************************************************************** 
//** �������ƣ� ~C3DLineString
//** ���������� ��������
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
C3DLineString::~C3DLineString()
{
  ReleaseVertexArray(m_byVertexType,m_vVertices);
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
bool C3DLineString::readBuffer( Buffer & buf)
{
	
	
	 bool bRet = C3DCurve::readBuffer(buf);
	if(!bRet)
	{
		return false;
	}
	//ר����Ϣ******************************
	buf.read(&m_dLineWidth,sizeof(double));
	buf.read(&m_byVertexType, sizeof(byte));
	//modify by yangling 20131208 begin
	if(m_byVertexType >= VERTEXTYPE_End || m_byVertexType < VERTEXTYPE_V3f)
	{
		return false;
	}
	//modify by yangling 20131208 end
	buf.read(&m_lVertNum,sizeof(long));
	if(m_byVertexType == VERTEXTYPE_V3d)	
	{
        m_vVertices = new Vertex3d[m_lVertNum];
        Vertex3d* pList = (Vertex3d*)m_vVertices;
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
        m_vVertices = new Vertex3f[m_lVertNum];
        Vertex3f* pList = (Vertex3f*)m_vVertices;
        //��forѭ�������ֽڶ�������
        for (int nNum=0; nNum < m_lVertNum; nNum++)
        {
            buf.read(&pList[nNum].x,sizeof(float));
            buf.read(&pList[nNum].y,sizeof(float));
            buf.read(&pList[nNum].z,sizeof(float));
        }
        pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3dT2d)
	{
        m_vVertices = new TexturedVertex3d[m_lVertNum];
        TexturedVertex3d* pList = (TexturedVertex3d*)m_vVertices;
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
        m_vVertices = new TexturedVertex3f[m_lVertNum];
        TexturedVertex3f* pList = (TexturedVertex3f*)m_vVertices;
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
        m_vVertices = new ShadedVertex3d[m_lVertNum];
        ShadedVertex3d* pList = (ShadedVertex3d*)m_vVertices;
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
        m_vVertices = new ShadedVertex3f[m_lVertNum];
        ShadedVertex3f* pList = (ShadedVertex3f*)m_vVertices;
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
        m_vVertices = new VersatileVertex3d[m_lVertNum];
        VersatileVertex3d* pList=NULL;
        pList = (VersatileVertex3d*)m_vVertices;
        //��forѭ�������ֽڶ�������
        for (int nNum=0; nNum < m_lVertNum; nNum++)
        {
            buf.read(&pList[nNum].x,sizeof(double));
            buf.read(&pList[nNum].y,sizeof(double));
            buf.read(&pList[nNum].z,sizeof(double));
            buf.read(&pList[nNum].tu,sizeof(double));
            buf.read(&pList[nNum].tv,sizeof(double));
            buf.read(&pList[nNum].nx,sizeof(double));
            buf.read(&pList[nNum].ny,sizeof(double));
            buf.read(&pList[nNum].nz,sizeof(double));
            buf.read(&pList[nNum].r,sizeof(float));
            buf.read(&pList[nNum].g,sizeof(float));
            buf.read(&pList[nNum].b,sizeof(float));

        }
        pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3fT2fN3fC3f)
	{
        m_vVertices = new VersatileVertex3f[m_lVertNum];
        VersatileVertex3f* pList=NULL;
        pList = (VersatileVertex3f*)m_vVertices;
        //��forѭ�������ֽڶ�������
        for (int nNum=0; nNum < m_lVertNum; nNum++)
        {
            buf.read(&pList[nNum].x,sizeof(float));
            buf.read(&pList[nNum].y,sizeof(float));
            buf.read(&pList[nNum].z,sizeof(float));
            buf.read(&pList[nNum].tu,sizeof(float));
            buf.read(&pList[nNum].tv,sizeof(float));
            buf.read(&pList[nNum].nx,sizeof(float));
            buf.read(&pList[nNum].ny,sizeof(float));
            buf.read(&pList[nNum].nz,sizeof(float));
            buf.read(&pList[nNum].r,sizeof(float));
            buf.read(&pList[nNum].g,sizeof(float));
            buf.read(&pList[nNum].b,sizeof(float));
        }
        pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3dT2dT2dN3dC3f)
	{
		m_vVertices = new SecondVersatileVertex3d[m_lVertNum];
		SecondVersatileVertex3d* pList=NULL;
		pList = (SecondVersatileVertex3d*)m_vVertices;
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(double));
			buf.read(&pList[nNum].y,sizeof(double));
			buf.read(&pList[nNum].z,sizeof(double));
			buf.read(&pList[nNum].tu,sizeof(double));
			buf.read(&pList[nNum].tv,sizeof(double));
			buf.read(&pList[nNum].tu2,sizeof(double));
			buf.read(&pList[nNum].tv2,sizeof(double));
			buf.read(&pList[nNum].nx,sizeof(double));
			buf.read(&pList[nNum].ny,sizeof(double));
			buf.read(&pList[nNum].nz,sizeof(double));
			buf.read(&pList[nNum].r,sizeof(float));
			buf.read(&pList[nNum].g,sizeof(float));
			buf.read(&pList[nNum].b,sizeof(float));

		}
		pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3fT2fT2fN3fC3f)
	{
		m_vVertices = new SecondVersatileVertex3f[m_lVertNum];
		SecondVersatileVertex3f* pList=NULL;
		pList = (SecondVersatileVertex3f*)m_vVertices;
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(float));
			buf.read(&pList[nNum].y,sizeof(float));
			buf.read(&pList[nNum].z,sizeof(float));
			buf.read(&pList[nNum].tu,sizeof(float));
			buf.read(&pList[nNum].tv,sizeof(float));
			buf.read(&pList[nNum].tu2,sizeof(float));
			buf.read(&pList[nNum].tv2,sizeof(float));
			buf.read(&pList[nNum].nx,sizeof(float));
			buf.read(&pList[nNum].ny,sizeof(float));
			buf.read(&pList[nNum].nz,sizeof(float));
			buf.read(&pList[nNum].r,sizeof(float));
			buf.read(&pList[nNum].g,sizeof(float));
			buf.read(&pList[nNum].b,sizeof(float));
		}
		pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3dT2dT2dT2dN3dC3f)
	{
		m_vVertices = new ThirdVersatileVertex3d[m_lVertNum];
		ThirdVersatileVertex3d* pList=NULL;
		pList = (ThirdVersatileVertex3d*)m_vVertices;
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(double));
			buf.read(&pList[nNum].y,sizeof(double));
			buf.read(&pList[nNum].z,sizeof(double));
			buf.read(&pList[nNum].tu,sizeof(double));
			buf.read(&pList[nNum].tv,sizeof(double));
			buf.read(&pList[nNum].tu2,sizeof(double));
			buf.read(&pList[nNum].tv2,sizeof(double));
			buf.read(&pList[nNum].tu3,sizeof(double));
			buf.read(&pList[nNum].tv3,sizeof(double));
			buf.read(&pList[nNum].nx,sizeof(double));
			buf.read(&pList[nNum].ny,sizeof(double));
			buf.read(&pList[nNum].nz,sizeof(double));
			buf.read(&pList[nNum].r,sizeof(float));
			buf.read(&pList[nNum].g,sizeof(float));
			buf.read(&pList[nNum].b,sizeof(float));

		}
		pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3fT2fT2fT2fN3fC3f)
	{
		m_vVertices = new ThirdVersatileVertex3f[m_lVertNum];
		ThirdVersatileVertex3f* pList=NULL;
		pList = (ThirdVersatileVertex3f*)m_vVertices;
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.read(&pList[nNum].x,sizeof(float));
			buf.read(&pList[nNum].y,sizeof(float));
			buf.read(&pList[nNum].z,sizeof(float));
			buf.read(&pList[nNum].tu,sizeof(float));
			buf.read(&pList[nNum].tv,sizeof(float));
			buf.read(&pList[nNum].tu2,sizeof(float));
			buf.read(&pList[nNum].tv2,sizeof(float));
			buf.read(&pList[nNum].tu3,sizeof(float));
			buf.read(&pList[nNum].tv3,sizeof(float));
			buf.read(&pList[nNum].nx,sizeof(float));
			buf.read(&pList[nNum].ny,sizeof(float));
			buf.read(&pList[nNum].nz,sizeof(float));
			buf.read(&pList[nNum].r,sizeof(float));
			buf.read(&pList[nNum].g,sizeof(float));
			buf.read(&pList[nNum].b,sizeof(float));
		}
		pList = NULL;
	}
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
void C3DLineString::writeBuffer(Buffer& buf)
{
    C3DCurve::writeBuffer(buf);
	
	//ר����Ϣ******************************
	buf.write(&m_dLineWidth,sizeof(double));
	buf.write(&m_byVertexType, sizeof(unsigned char));
	buf.write((char*)&m_lVertNum,sizeof(long));
	

    if(m_byVertexType == VERTEXTYPE_V3d)	
    {
        Vertex3d* pList = (Vertex3d*)m_vVertices;
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
        Vertex3f* pList = (Vertex3f*)m_vVertices;
        //��forѭ�������ֽڶ�������
        for (int nNum=0; nNum < m_lVertNum; nNum++)
        {
            buf.write(&pList[nNum].x,sizeof(float));
            buf.write(&pList[nNum].y,sizeof(float));
            buf.write(&pList[nNum].z,sizeof(float));
        }
        pList = NULL;
    }
    else if(m_byVertexType == VERTEXTYPE_V3dT2d)
    {
        TexturedVertex3d* pList = (TexturedVertex3d*)m_vVertices;
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
        TexturedVertex3f* pList = (TexturedVertex3f*)m_vVertices;
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
        ShadedVertex3d* pList = (ShadedVertex3d*)m_vVertices;
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
        ShadedVertex3f* pList = (ShadedVertex3f*)m_vVertices;
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
        pList = (VersatileVertex3d*)m_vVertices;
        //��forѭ�������ֽڶ�������
        for (int nNum=0; nNum < m_lVertNum; nNum++)
        {
            buf.write(&pList[nNum].x,sizeof(double));
            buf.write(&pList[nNum].y,sizeof(double));
            buf.write(&pList[nNum].z,sizeof(double));
            buf.write(&pList[nNum].tu,sizeof(double));
            buf.write(&pList[nNum].tv,sizeof(double));
            buf.write(&pList[nNum].nx,sizeof(double));
            buf.write(&pList[nNum].ny,sizeof(double));
            buf.write(&pList[nNum].nz,sizeof(double));
            buf.write(&pList[nNum].r,sizeof(float));
            buf.write(&pList[nNum].g,sizeof(float));
            buf.write(&pList[nNum].b,sizeof(float));

        }
        pList = NULL;

    }
    else if(m_byVertexType == VERTEXTYPE_V3fT2fN3fC3f)
    {
        VersatileVertex3f* pList=NULL;
        pList = (VersatileVertex3f*)m_vVertices;
        //��forѭ�������ֽڶ�������
        for (int nNum=0; nNum < m_lVertNum; nNum++)
        {
            buf.write(&pList[nNum].x,sizeof(float));
            buf.write(&pList[nNum].y,sizeof(float));
            buf.write(&pList[nNum].z,sizeof(float));
            buf.write(&pList[nNum].tu,sizeof(float));
            buf.write(&pList[nNum].tv,sizeof(float));
            buf.write(&pList[nNum].nx,sizeof(float));
            buf.write(&pList[nNum].ny,sizeof(float));
            buf.write(&pList[nNum].nz,sizeof(float));
            buf.write(&pList[nNum].r,sizeof(float));
            buf.write(&pList[nNum].g,sizeof(float));
            buf.write(&pList[nNum].b,sizeof(float));
        }
        pList = NULL;

    }
	else if(m_byVertexType == VERTEXTYPE_V3dT2dT2dN3dC3f)
	{
		SecondVersatileVertex3d* pList=NULL;
		pList = (SecondVersatileVertex3d*)m_vVertices;
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.write(&pList[nNum].x,sizeof(double));
			buf.write(&pList[nNum].y,sizeof(double));
			buf.write(&pList[nNum].z,sizeof(double));
			buf.write(&pList[nNum].tu,sizeof(double));
			buf.write(&pList[nNum].tv,sizeof(double));
			buf.write(&pList[nNum].tu2,sizeof(double));
			buf.write(&pList[nNum].tv2,sizeof(double));
			buf.write(&pList[nNum].nx,sizeof(double));
			buf.write(&pList[nNum].ny,sizeof(double));
			buf.write(&pList[nNum].nz,sizeof(double));
			buf.write(&pList[nNum].r,sizeof(float));
			buf.write(&pList[nNum].g,sizeof(float));
			buf.write(&pList[nNum].b,sizeof(float));

		}
		pList = NULL;

	}
	else if(m_byVertexType == VERTEXTYPE_V3fT2fT2fN3fC3f)
	{
		SecondVersatileVertex3f* pList=NULL;
		pList = (SecondVersatileVertex3f*)m_vVertices;
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.write(&pList[nNum].x,sizeof(float));
			buf.write(&pList[nNum].y,sizeof(float));
			buf.write(&pList[nNum].z,sizeof(float));
			buf.write(&pList[nNum].tu,sizeof(float));
			buf.write(&pList[nNum].tv,sizeof(float));
			buf.write(&pList[nNum].tu2,sizeof(float));
			buf.write(&pList[nNum].tv2,sizeof(float));
			buf.write(&pList[nNum].nx,sizeof(float));
			buf.write(&pList[nNum].ny,sizeof(float));
			buf.write(&pList[nNum].nz,sizeof(float));
			buf.write(&pList[nNum].r,sizeof(float));
			buf.write(&pList[nNum].g,sizeof(float));
			buf.write(&pList[nNum].b,sizeof(float));
		}
		pList = NULL;

	}
	else if(m_byVertexType == VERTEXTYPE_V3dT2dT2dT2dN3dC3f)
	{
		ThirdVersatileVertex3d* pList=NULL;
		pList = (ThirdVersatileVertex3d*)m_vVertices;
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.write(&pList[nNum].x,sizeof(double));
			buf.write(&pList[nNum].y,sizeof(double));
			buf.write(&pList[nNum].z,sizeof(double));
			buf.write(&pList[nNum].tu,sizeof(double));
			buf.write(&pList[nNum].tv,sizeof(double));
			buf.write(&pList[nNum].tu2,sizeof(double));
			buf.write(&pList[nNum].tv2,sizeof(double));
			buf.write(&pList[nNum].tu3,sizeof(double));
			buf.write(&pList[nNum].tv3,sizeof(double));
			buf.write(&pList[nNum].nx,sizeof(double));
			buf.write(&pList[nNum].ny,sizeof(double));
			buf.write(&pList[nNum].nz,sizeof(double));
			buf.write(&pList[nNum].r,sizeof(float));
			buf.write(&pList[nNum].g,sizeof(float));
			buf.write(&pList[nNum].b,sizeof(float));
		}
		pList = NULL;
	}
	else if(m_byVertexType == VERTEXTYPE_V3fT2fT2fT2fN3fC3f)
	{
		ThirdVersatileVertex3f* pList=NULL;
		pList = (ThirdVersatileVertex3f*)m_vVertices;
		for (int nNum=0; nNum < m_lVertNum; nNum++)
		{
			buf.write(&pList[nNum].x,sizeof(float));
			buf.write(&pList[nNum].y,sizeof(float));
			buf.write(&pList[nNum].z,sizeof(float));
			buf.write(&pList[nNum].tu,sizeof(float));
			buf.write(&pList[nNum].tv,sizeof(float));
			buf.write(&pList[nNum].tu2,sizeof(float));
			buf.write(&pList[nNum].tv2,sizeof(float));
			buf.write(&pList[nNum].tu3,sizeof(float));
			buf.write(&pList[nNum].tv3,sizeof(float));
			buf.write(&pList[nNum].nx,sizeof(float));
			buf.write(&pList[nNum].ny,sizeof(float));
			buf.write(&pList[nNum].nz,sizeof(float));
			buf.write(&pList[nNum].r,sizeof(float));
			buf.write(&pList[nNum].g,sizeof(float));
			buf.write(&pList[nNum].b,sizeof(float));
		}
		pList = NULL;
	}
}

void C3DLineString::setLineWidth(double dLineWidth)
{
	m_dLineWidth=dLineWidth;
}
double C3DLineString::getLineWidth()
{
	return m_dLineWidth;
}

void C3DLineString::setVertexType(byte byVertexType)
{
	m_byVertexType=byVertexType;
}
byte C3DLineString::getVertexType()
{
	return m_byVertexType;
}


void C3DLineString::setVertNum(long lVertNum)
{
	m_lVertNum=lVertNum;
}
long C3DLineString::getVertNum()
{
	return m_lVertNum;
}
size_t C3DLineString::sizeBuffer()
{
	size_t nSize = 0;
	nSize += C3DCurve::sizeBuffer();
	nSize += sizeof(double);//�߿�
	nSize += sizeof(byte);//�������ͱ���
	nSize += sizeof(long);//������
	
	//��ά���߶�������
	//*************************************************

	if(m_byVertexType == VERTEXTYPE_V3d)	
	{	
		nSize += Vertex3d::sizeBuffer() * m_lVertNum;
	}
	else if(m_byVertexType == VERTEXTYPE_V3f)
	{
		nSize += Vertex3f::sizeBuffer() * m_lVertNum;
	}
	else if(m_byVertexType == VERTEXTYPE_V3dT2d)
	{
		nSize += TexturedVertex3d::sizeBuffer() * m_lVertNum;
	}
	else if(m_byVertexType == VERTEXTYPE_V3fT2f)
	{
		nSize += TexturedVertex3f::sizeBuffer() * m_lVertNum;	
	}
	else if(m_byVertexType == VERTEXTYPE_V3dN3dC3f)
	{
		nSize += ShadedVertex3d::sizeBuffer() * m_lVertNum;
	}
	else if(m_byVertexType == VERTEXTYPE_V3fN3fC3f)
	{
		nSize += ShadedVertex3f::sizeBuffer() * m_lVertNum;
	}
	else if(m_byVertexType == VERTEXTYPE_V3dT2dN3dC3f)
	{
		nSize += VersatileVertex3d::sizeBuffer() * m_lVertNum;
	}
	else if(m_byVertexType == VERTEXTYPE_V3fT2fN3fC3f)
	{
		nSize += VersatileVertex3f::sizeBuffer() * m_lVertNum;
	}  
	else if(m_byVertexType == VERTEXTYPE_V3dT2dT2dN3dC3f)
	{
		nSize += SecondVersatileVertex3d::sizeBuffer() * m_lVertNum;
	}
	else if(m_byVertexType == VERTEXTYPE_V3fT2fT2fN3fC3f)
	{
		nSize += SecondVersatileVertex3f::sizeBuffer() * m_lVertNum;
	}  
	else if(m_byVertexType == VERTEXTYPE_V3dT2dT2dT2dN3dC3f)
	{
		nSize += ThirdVersatileVertex3d::sizeBuffer() * m_lVertNum;
	}
	else if(m_byVertexType == VERTEXTYPE_V3fT2fT2fT2fN3fC3f)
	{
		nSize += ThirdVersatileVertex3f::sizeBuffer() * m_lVertNum;
	}  

	return nSize;
}

