//********************************************************************************** 
//** �ļ����ƣ�CT3D_ThirdVersatileVertex3dWithoutRGB.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�����ࣨȫ�ж��� ��ʵ��
//** �� �� �ˣ� ��
//** �������ڣ� 2012-08-27
//********************************************************************************** 

#include "CT3D_ThirdVersatileVertex3dWithoutRGB.h"

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
ThirdVersatileVertex3dWithoutRGB::ThirdVersatileVertex3dWithoutRGB(double dblx,double dbly,
                                     double dblz,double dblnx,
                                     double dblny,double dblnz,
                                     double dblu,double dblv,
									 double dblu2,double dblv2,
									 double dblu3,double dblv3)
:
Vertex3d(dblx,dbly,dblz),
nx(dblnx),
ny(dblny),
nz(dblnz),
tu(dblu),
tv(dblv),
tu2(dblu2),
tv2(dblv2),
tu3(dblu3),
tv3(dblv3)
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
ThirdVersatileVertex3dWithoutRGB::ThirdVersatileVertex3dWithoutRGB(Vertex3d& vPos,Vertex3d& vNor,double dblu,double dblv,double dblu2,double dblv2, double dblu3,double dblv3)
:Vertex3d(vPos),
nx(vNor.x),
ny(vNor.y),
nz(vNor.z),
tu(dblu),
tv(dblv),
tu2(dblu2),
tv2(dblv2),
tu3(dblu3),
tv3(dblv3)
{

}

/** ���캯��3
*/
ThirdVersatileVertex3dWithoutRGB::ThirdVersatileVertex3dWithoutRGB(Vertex3d& vPos,Vertex3d& vNor,Vertex2d& vTex,Vertex2d& vTex2,Vertex2d& vTex3)
:Vertex3d(vPos),
nx(vNor.x),
ny(vNor.y),
nz(vNor.z),
tu(vTex.x),
tv(vTex.y),
tu2(vTex2.x),
tv2(vTex2.y),
tu3(vTex3.x),
tv3(vTex3.y)
{

}

/** ��ö�����������	
* @param 
* @return ������������	
*/
Vertex2d ThirdVersatileVertex3dWithoutRGB::GetThirdTexCoor() const
{
	return Vertex2d(tu3,tv3);
}

/** ���ö�����������	
* @param [in] vTex ������������		
* @return
*/
void ThirdVersatileVertex3dWithoutRGB::SetThirdTexCoor(const Vertex2d& vTex) 
{
	tu3 = vTex.x;
	tv3 = vTex.y;
}

size_t ThirdVersatileVertex3dWithoutRGB::sizeBuffer()
{
    size_t nSize = Vertex3d::sizeBuffer() + 9* sizeof(double)/* + 3* sizeof(float)*/ ;
    return nSize;
}