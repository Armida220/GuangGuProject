// Copyright (C) 1991 - 1999 Rational Software Corporation


#include "CT3D_ShadedVertex3d.h"

//********************************************************************************** 
//** �������ƣ� ShadedVertex3d
//** ���������� ���캯��1
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
ShadedVertex3d::ShadedVertex3d(double dx,double dy,double dz,double dnx,double dny,double dnz,float r,float g, float b)
:Vertex3d(dx,dy,dz),
nx(dx),
ny(dy),
nz(dz),
r(r),
g(g),
b(b)
{

}

//********************************************************************************** 
//** �������ƣ� ShadedVertex3d
//** ���������� ���캯��2
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
ShadedVertex3d::ShadedVertex3d(Vertex3d& vPos,Vertex3d& vNor,Vertex3f& vColor)
:Vertex3d(vPos),
nx(vNor.x),
ny(vNor.y),
nz(vNor.z),
r(vColor.x), 
g(vColor.y), 
b(vColor.z)
{

}

//********************************************************************************** 
//** �������ƣ� sizeBuffer
//** ����������������ά��ṹ�Ĵ�С
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��ṹ��С
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-26
//**********************************************************************************
size_t ShadedVertex3d::sizeBuffer()
{
    size_t nSize = Vertex3d::sizeBuffer() + 3*(sizeof(double) + sizeof(float));
    return nSize;
}