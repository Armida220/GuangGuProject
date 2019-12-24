//********************************************************************************** 
//** �ļ����ƣ�CT3D_ShadedVertex3f.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�����ࣨ���ڹ��ռ�����Ⱦɫ�ʵĶ��㣩ʵ�֣�
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-13
//********************************************************************************** 


#include "CT3D_ShadedVertex3f.h"

ShadedVertex3f::ShadedVertex3f(float fx,float fy,float fz,float fnx,float fny,float fnz,float fr,float fg, float fb)
:Vertex3f(fx,fy,fz),
nx(fnx),
ny(fny),
nz(fnz),
r(fr),
g(fg),
b(fb)
{

}

ShadedVertex3f::ShadedVertex3f(Vertex3f& vPos,Vertex3f& vNor,Vertex3f& vColor)
:Vertex3f(vPos),
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
size_t ShadedVertex3f::sizeBuffer()
{
    size_t nSize = Vertex3f::sizeBuffer() + 6*sizeof(float);
    return nSize;
}
