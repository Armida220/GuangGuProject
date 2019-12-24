// Copyright (C) 1991 - 1999 Rational Software Corporation

#include "CT3D_Geometry.h"
#include "CT3D_Vertex3d.h"
#include "CT3D_Vertex3f.h"
#include "CT3D_TexturedVertex3d.h"
#include "CT3D_TexturedVertex3f.h"
#include "CT3D_ShadedVertex3d.h"
#include "CT3D_ShadedVertex3f.h"
#include "CT3D_ThirdVersatileVertex3d.h"
#include "CT3D_ThirdVersatileVertex3f.h"
#include "CT3D_3DCurve.h"
#include "CT3D_3DLinearRing.h"
#include "CT3D_3DLineString.h"
#include "CT3D_3DLofting.h"
#include "CT3D_3DGroup.h"
#include "CT3D_3DMultiPoint.h"
#include "CT3D_3DPoint.h"
#include "CT3D_3DPolygon.h"
#include "CT3D_3DReference.h"
#include "CT3D_3DSinglePoint.h"
#include "CT3D_3DSolid.h"
#include "CT3D_3DModelObject.h"
#include "CT3D_3DSurface.h"
#include "CT3D_3DFeatureInfoGroup.h"
#include "CT3D_3DTriangleMesh.h"
#include "CT3D_3DOblique.h"
#include "Buffer.h"




//********************************************************************************** 
//** �������ƣ� CGeometry
//** ���������� ���캯��1
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
CGeometry::CGeometry()
{

}

//********************************************************************************** 
//** �������ƣ� ~CGeometry
//** ���������� ��������
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
CGeometry:: ~CGeometry()
{

}


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
CGeometry::CGeometry(UID64 uFID,byte byTypeID, string strObjName)
{
    m_uFID = uFID;
    m_byTypeID = byTypeID;
    m_strObjName = strObjName;
    m_nObjNameLen = strObjName.length();
}

//********************************************************************************** 
//** �������ƣ� readBuffer
//** ���������� �ӻ����ȡ�����¼
//** ��    �룺 pBuffer ����           
//** ��    ���� ��
//** ����ֵ��	�ɹ�Ϊtrue��ʧ��Ϊfalse
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
bool CGeometry::readBuffer( Buffer & buf) 
{

	buf.read((char*)&m_uFID,sizeof(UID64));

	buf.read((char*)&m_byTypeID,sizeof(byte));

	buf.read((char*)&m_nObjNameLen,sizeof(int));

	char ca[4096];
	memset(ca,0,4096);
	//modify by yangling 20131208 begin
	if(m_nObjNameLen> 4096)
	{
		return false;
	}
	//modify by yangling 20131208 end
	buf.read(ca,m_nObjNameLen);
	m_strObjName.assign(ca);
	return true;
}

//********************************************************************************** 
//** �������ƣ� readBuffer
//** ���������� ������д�뻺��
//** ��    �룺 pBuffer ����           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
void CGeometry::writeBuffer(Buffer& buf) 
{
    buf.write((char*)&m_uFID,sizeof(UID64));

    buf.write((char*)&m_byTypeID,sizeof(byte));

    buf.write((char*)&m_nObjNameLen,sizeof(int));
    buf.write((char*)m_strObjName.c_str(),m_nObjNameLen);
}

//********************************************************************************** 
//** �������ƣ� CreateGeometry
//** ���������� ����һ����ǰ�����������ڴ�ռ�
//** ��    �룺 ���ζ��������           
//** ��    ���� ��
//** ����ֵ��	���ٵĵ�ǰ������ڴ�ռ���׵�ַ
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
CGeometry * CGeometry::CreateGeometry(byte byType) 
{
	if(byType == GEOTYPE_3D_TRIANGLEMESH)	
	{

		return (CGeometry*)new C3DTriangleMesh;
	}
	else if(byType == GEOTYPE_3D_POINT)
	{
		return (CGeometry*)new C3DPoint;
	}
		else if(byType == GEOTYPE_3D_OBLIQUE)
	{
		return (CGeometry*)new C3DOblique;
	}
	else if(byType == GEOTYPE_3D_FEATUREINFOGROUP)
	{
		return (CGeometry*)new C3DFeatureInfoGroup;
	}
	else if(byType == GEOTYPE_3D_SINGLEPOINT)
	{
		return (CGeometry*)new C3DSinglePoint;
	}
	else if(byType == GEOTYPE_3D_MULTIPOINT)
	{
		return (CGeometry*)new C3DMultiPoint;
	}

	else if(byType == GEOTYPE_3D_REFERENCE)
	{
		return (CGeometry*)new C3DReference;
	}

	else if(byType == GEOTYPE_3D_SURFACE)
	{
		return (CGeometry*)new C3DSurface;
	}
	else if(byType == GEOTYPE_3D_CURVE)
	{
		return (CGeometry*)new C3DCurve;
	}
	else if(byType == GEOTYPE_3D_GROUP)
	{
		return (CGeometry*)new C3DGroup;
	}

	else if(byType == GEOTYPE_3D_SOLID)
	{
		return (CGeometry*)new C3DSolid;
	}

	else if(byType == GEOTYPE_3D_MODELOBJECT)
	{
		return (CGeometry*)new C3DModelObject;
	}

	else if(byType == GEOTYPE_3D_POLYGON)
	{
		return (CGeometry*)new C3DPolygon;
	}
	else if(byType == GEOTYPE_3D_LINEARRING)
	{
		return (CGeometry*)new C3DLinearRing;
	}

	else if(byType == GEOTYPE_3D_LINESTRING)
	{
		return (CGeometry*)new C3DLineString;
	}
	else if(byType == GEOTYPE_3D_LOFTING)
	{
		return (CGeometry*)new C3DLofting;
	}
	else if(byType == GEOTYPE_3D_GEOMETRY)
	{
		return (CGeometry*)new C3DGeometry;
	}

	else
	{
		return NULL;
	}

    return NULL;
}

//********************************************************************************** 
//** �������ƣ� CreateGeometry
//** ���������� ���ݶ�������ɾ����������
//** ��    �룺 �������� iVertexType�����������ָ������pVertexPointer          
//** ��    ���� ��
//** ����ֵ��	0����ɾ���ɹ���-1�����ɹ�
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
long ReleaseVertexArray(unsigned char iVertexType, void*& pVertexPointer)
{
    if(NULL == pVertexPointer)
        return 0;

    switch(iVertexType)
    {
    case VERTEXTYPE_V3f:	// for Vertex3f
        {
            delete []((Vertex3f*)pVertexPointer);
            break;
        }
    case VERTEXTYPE_V3d:				// for Vertex3d
        {
            delete []((Vertex3d*)pVertexPointer);
            break;
        }
    case VERTEXTYPE_V3fT2f:			// for TexturedVertex3f
        {
            delete []((TexturedVertex3f*)pVertexPointer);
            break;
        }
    case VERTEXTYPE_V3dT2d:			// for TexturedVertex3d
        {
            delete []((TexturedVertex3d*)pVertexPointer);
            break;
        }
    case VERTEXTYPE_V3fN3fC3f:		// for ShadedVertex3f
        {
            delete []((ShadedVertex3f*)pVertexPointer);
            break;
        }
    case VERTEXTYPE_V3dN3dC3f:		// for ShadedVertex3d
        {
            delete []((ShadedVertex3d*)pVertexPointer);
            break;
        }
    case VERTEXTYPE_V3fT2fN3fC3f:	// for VersatileVertex3f
        {
            delete []((VersatileVertex3f*)pVertexPointer);
            break;
        }
    case VERTEXTYPE_V3dT2dN3dC3f:	// for VersatileVertex3d
        {
            delete []((VersatileVertex3d*)pVertexPointer);
            break;
        }
	case VERTEXTYPE_V3dT2dT2dN3dC3f:	// for VersatileVertex3d
		{
			delete []((SecondVersatileVertex3d*)pVertexPointer);
			break;
		}
	case VERTEXTYPE_V3fT2fT2fN3fC3f:	// for VersatileVertex3f
		{
			delete []((SecondVersatileVertex3f*)pVertexPointer);
			break;
		}
	case VERTEXTYPE_V3dT2dT2dT2dN3dC3f:	// for VersatileVertex3d
		{
			delete []((ThirdVersatileVertex3d*)pVertexPointer);
			break;
		}
	case VERTEXTYPE_V3fT2fT2fT2fN3fC3f:	// for VersatileVertex3f
		{
			delete []((ThirdVersatileVertex3f*)pVertexPointer);
			break;
		}
    default:
        {
            assert(0);
            return -1;
        }
    }

    pVertexPointer = NULL;
    return 0;
}
void CGeometry::setObjID(UID64 uFID)
{
	m_uFID=uFID;
}
UID64 CGeometry::getObjID()
{
	return m_uFID;
}

void CGeometry::setTypeID(byte byTypeID)
{
	m_byTypeID=byTypeID;
}
byte CGeometry::getTypeID()
{
	return m_byTypeID;
}

void CGeometry::setObjName(string strObjName)
{
	m_strObjName=strObjName;
}
string CGeometry::getObjName()
{
	return m_strObjName;
}
int CGeometry::getObjNameLen()
{
	return m_strObjName.size();
}
size_t CGeometry::sizeBuffer()
{
    size_t nSize = 0;


    nSize += sizeof(UINT64); //����ID
    nSize += sizeof(byte); //���ζ�������
    nSize += sizeof(int);  //���ζ������ֳ���
    nSize += m_strObjName.length(); //���ζ�������


    return nSize;
}