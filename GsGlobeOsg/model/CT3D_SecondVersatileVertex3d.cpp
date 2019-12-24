//********************************************************************************** 
//** �ļ����ƣ�CT3D_SecondVersatileVertex3d.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�����ࣨȫ�ж��� ��ʵ��
//** �� �� �ˣ� ��
//** �������ڣ� 2013-08-27
//********************************************************************************** 

#include "CT3D_SecondVersatileVertex3d.h"

/** @name ��������������
*  @{
*/

//********************************************************************************** 
//** �������ƣ� SecondVersatileVertex3d
//** ���������� ���캯��1
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ��
//** �������ڣ� 2013-08-27
//**********************************************************************************
SecondVersatileVertex3d::SecondVersatileVertex3d(double dblx,double dbly,
                                     double dblz,double dblnx,
                                     double dblny,double dblnz,
                                     double dblu,double dblv,
									 double dblu2,double dblv2,
                                     float fcr,float fcg ,
                                     float fcb):
Vertex3d(dblx,dbly,dblz),
nx(dblnx),
ny(dblny),
nz(dblnz),
tu(dblu),
tv(dblv),
tu2(dblu2),
tv2(dblv2),
r(fcr),
g(fcg),
b(fcb)
{

}

//********************************************************************************** 
//** �������ƣ� SecondVersatileVertex3d
//** ���������� ���캯��2
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ��
//** �������ڣ� 2013-08-27
//**********************************************************************************
SecondVersatileVertex3d::SecondVersatileVertex3d(Vertex3d& vPos,Vertex3d& vNor,double dblu,double dblv,double dblu2,double dblv2, float fcr,float fcg,float fcb)
:Vertex3d(vPos),
nx(vNor.x),
ny(vNor.y),
nz(vNor.z),
tu(dblu),
tv(dblv),
tu2(dblu2),
tv2(dblv2),
r(fcr),
g(fcg),
b(fcb)

{

}

/** ���캯��3
*/
SecondVersatileVertex3d::SecondVersatileVertex3d(Vertex3d& vPos,Vertex3d& vNor,Vertex2d& vTex,Vertex2d& vTex2,Vertex3f& vClr)
:Vertex3d(vPos),
nx(vNor.x),
ny(vNor.y),
nz(vNor.z),
tu(vTex.x),
tv(vTex.y),
tu2(vTex2.x),
tv2(vTex2.y),
r(vClr.x),
g(vClr.y),
b(vClr.z)
{

}


/** ��ö�����������	
* @param 
* @return ������������	
*/
Vertex2d SecondVersatileVertex3d::GetSecondTexCoor() const
{
	return Vertex2d(tu2,tv2);
}



/** ���ö�����������	
* @param [in] vTex ������������		
* @return
*/
void SecondVersatileVertex3d::SetSecondTexCoor(const Vertex2d& vTex) 
{
	tu2 = vTex.x;
	tv2 = vTex.y;
}

size_t SecondVersatileVertex3d::sizeBuffer()
{
    size_t nSize = Vertex3d::sizeBuffer() + 7* sizeof(double) + 3* sizeof(float) ;
    return nSize;
}