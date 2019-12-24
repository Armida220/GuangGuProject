//********************************************************************************** 
//** �ļ����ƣ�CT3D_VersatileVertex3dWithoutRGB.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�����ࣨȫ�ж��� ��ʵ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-13
//********************************************************************************** 

#include "CT3D_VersatileVertex3dWithoutRGB.h"

/** @name ��������������
*  @{
*/

//********************************************************************************** 
//** �������ƣ� VersatileVertex3dWithoutRGB
//** ���������� ���캯��1
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
VersatileVertex3dWithoutRGB::VersatileVertex3dWithoutRGB(double dx,double dy,
                                     double dz,double dnx,
                                     double dny,double dnz,
                                     double du,double dv)
:
Vertex3d(dx,dy,dz),
nx(dnx),
ny(dny),
nz(dnz),
tu(du),
tv(dv)
{

}

//********************************************************************************** 
//** �������ƣ� VersatileVertex3dWithoutRGB
//** ���������� ���캯��2
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
VersatileVertex3dWithoutRGB::VersatileVertex3dWithoutRGB(Vertex3d& vPos,Vertex3d& vNor,double fu,double fv):
Vertex3d(vPos),
nx(vNor.x),
ny(vNor.y),
nz(vNor.z),
tu(fu),
tv(fv)
{

}

/** ���캯��3
*/
VersatileVertex3dWithoutRGB::VersatileVertex3dWithoutRGB(Vertex3d& vPos,Vertex3d& vNor,Vertex2d& vTex):
Vertex3d(vPos),
nx(vNor.x),
ny(vNor.y),
nz(vNor.z),
tu(vTex.x),
tv(vTex.y)
{

}

/** @name ���ݲ���
*  @{
*/

/** ��ö��㷨����	
* @param 
* @return ���㷨����
*/
Vertex3d VersatileVertex3dWithoutRGB::GetNormal() const
{
    return Vertex3d(nx,ny,nz);
}

/** ���ö��㷨����
* @param [in]  vNor ���㷨����	
* @return
*/
void VersatileVertex3dWithoutRGB::SetNormal(const Vertex3d& vNor) 
{
    nx = vNor.x;
    ny = vNor.y;
    nz = vNor.z;
}

/** ��ö�����������	
* @param 
* @return ������������	
*/
Vertex2d VersatileVertex3dWithoutRGB::GetTexCoor() const
{
    return Vertex2d(tu,tv);
}

/** ���ö�����������	
* @param [in] vTex ������������		
* @return
*/
void VersatileVertex3dWithoutRGB::SetTexCoor(const Vertex2d& vTex) 
{
    tu = vTex.x;
    tv = vTex.y;
}

size_t VersatileVertex3dWithoutRGB::sizeBuffer()
{
    size_t nSize = Vertex3d::sizeBuffer() + 5* sizeof(double)/* + 3* sizeof(float) */;
    return nSize;
}