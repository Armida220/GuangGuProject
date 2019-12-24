//********************************************************************************** 
//** �ļ����ƣ�CT3D_VersatileVertex3d.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�����ࣨȫ�ж��� ��ʵ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-13
//********************************************************************************** 

#include "CT3D_VersatileVertex3d.h"

/** @name ��������������
*  @{
*/

//********************************************************************************** 
//** �������ƣ� VersatileVertex3d
//** ���������� ���캯��1
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
VersatileVertex3d::VersatileVertex3d(double dx,double dy,
                                     double dz,double dnx,
                                     double dny,double dnz,
                                     double du,double dv,
                                     float dcr,float dcg ,
                                     float dcb)
:
Vertex3d(dx,dy,dz),
nx(dnx),
ny(dny),
nz(dnz),
tu(du),
tv(dv),
r(dcr),
g(dcg),
b(dcb)
{

}

//********************************************************************************** 
//** �������ƣ� VersatileVertex3d
//** ���������� ���캯��2
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
VersatileVertex3d::VersatileVertex3d(Vertex3d& vPos,Vertex3d& vNor,double fu,double fv,float fcr,float fcg,float fcb):
Vertex3d(vPos),
nx(vNor.x),
ny(vNor.y),
nz(vNor.z),
tu(fu),
tv(fv),
r(fcr),
g(fcg),
b(fcb)
{

}

/** ���캯��3
*/
VersatileVertex3d::VersatileVertex3d(Vertex3d& vPos,Vertex3d& vNor,Vertex2d& vTex,Vertex3f& vClr):
Vertex3d(vPos),
nx(vNor.x),
ny(vNor.y),
nz(vNor.z),
tu(vTex.x),
tv(vTex.y),
r(vClr.x),
g(vClr.y),
b(vClr.z)
{

}

/** @name ���ݲ���
*  @{
*/

/** ��ö��㷨����	
* @param 
* @return ���㷨����
*/
Vertex3d VersatileVertex3d::GetNormal() const
{
    return Vertex3d(nx,ny,nz);
}

/** ���ö��㷨����
* @param [in]  vNor ���㷨����	
* @return
*/
void VersatileVertex3d::SetNormal(const Vertex3d& vNor) 
{
    nx = vNor.x;
    ny = vNor.y;
    nz = vNor.z;
}

/** ��ö�����������	
* @param 
* @return ������������	
*/
Vertex2d VersatileVertex3d::GetTexCoor() const
{
    return Vertex2d(tu,tv);
}

/** ���ö�����������	
* @param [in] vTex ������������		
* @return
*/
void VersatileVertex3d::SetTexCoor(const Vertex2d& vTex) 
{
    tu = vTex.x;
    tv = vTex.y;
}

/** ��ö�����ɫ	
* @param 
* @return ������ɫ
*/
Vertex3f VersatileVertex3d::GetColor() const
{
    return Vertex3f(r,g,b);
}


/** ���ö�����ɫ
* @param [in] vClr	 ������ɫ
* @return
*/
void VersatileVertex3d::SetColor(const Vertex3f& vClr)
{
    r = vClr.x;
    g = vClr.y;
    b = vClr.z;
}
size_t VersatileVertex3d::sizeBuffer()
{
    size_t nSize = Vertex3d::sizeBuffer() + 5* sizeof(double) + 3* sizeof(float) ;
    return nSize;
}