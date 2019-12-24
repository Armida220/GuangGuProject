//********************************************************************************** 
//** �ļ����ƣ�CT3D_3DGeometry.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά������ʵ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-11
//********************************************************************************** 

#include "CT3D_3DGeometry.h"

//********************************************************************************** 
//** �������ƣ� C3DGeometry
//** ���������� ���캯��
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
C3DGeometry::C3DGeometry()
{
	m_uFID = -1;
    m_byTypeID = GEOTYPE_3D_GEOMETRY;
    m_vMaxPos.x = 0.0;
    m_vMaxPos.y = 0.0;
    m_vMaxPos.z = 0.0;
    m_vMinPos.x = 0.0;
    m_vMinPos.y = 0.0;
    m_vMinPos.z = 0.0;
    m_strObjName="3DGeometry";
    m_nObjNameLen = m_strObjName.length();
}

//********************************************************************************** 
//** �������ƣ� ~C3DGeometry
//** ���������� ��������
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
C3DGeometry::~C3DGeometry()
{

}
//********************************************************************************** 
//** �������ƣ� CreateObject
//** ���������� ������ά���ζ���
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ�����ζ���ָ��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
CGeometry* C3DGeometry::CreateObject()
{
    return new C3DGeometry;
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
bool C3DGeometry::readBuffer( Buffer& buf)
{
	bool bRet = CGeometry::readBuffer(buf);
	if(!bRet)
	{
		return false;
	}
	//��ȡAABB����С����λ��(X,Y,Z��С)
	buf.read((char*)&m_vMinPos.x,sizeof(double));
    buf.read((char*)&m_vMinPos.y,sizeof(double));
    buf.read((char*)&m_vMinPos.z,sizeof(double));
	//��ȡAABB����󶥵�λ��(X,Y,Z���)
	buf.read((char*)&m_vMaxPos.x,sizeof(double));
    buf.read((char*)&m_vMaxPos.y,sizeof(double));
    buf.read((char*)&m_vMaxPos.z,sizeof(double));
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
void C3DGeometry::writeBuffer(Buffer& buf)
{
	CGeometry::writeBuffer(buf);
	//д��AABB����С����λ��(X,Y,Z��С)
	buf.write((char*)&m_vMinPos.x,sizeof(double));
    buf.write((char*)&m_vMinPos.y,sizeof(double));
    buf.write((char*)&m_vMinPos.z,sizeof(double));
	//д��AABB����󶥵�λ��(X,Y,Z���)
	buf.write((void*)&m_vMaxPos.x,sizeof(double));
    buf.write((void*)&m_vMaxPos.y,sizeof(double));
    buf.write((void*)&m_vMaxPos.z,sizeof(double));
}

void C3DGeometry::setMinPos(Vertex3d vMinPos)
{
	m_vMinPos=vMinPos;
}
Vertex3d& C3DGeometry::getMinPos()
{
	return m_vMinPos;
}

void C3DGeometry::setMaxPos(Vertex3d vMaxPos)
{
	m_vMaxPos=vMaxPos;
}
Vertex3d& C3DGeometry::getMaxPos()
{
	return m_vMaxPos;
}

size_t C3DGeometry::sizeBuffer()
{
    size_t nSize = 0;
    //nSize += CGeometry::sizeBuffer(); 
    //nSize += Vertex3d::sizeBuffer()*2; 
    return nSize;
}