//********************************************************************************** 
//** �ļ����ƣ�CT3D_VersatileVertex3f.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�����ࣨȫ�ж��� ��ʵ�֣�
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-13
//********************************************************************************** 

#include "CT3D_ThirdVersatileVertex3f.h"

ThirdVersatileVertex3f::ThirdVersatileVertex3f(float fx,float fy,float fz,float fnx,float fny,float fnz,float fu,float fv,float fu2,float fv2,float fu3,float fv3,float fcr,float fcg,float fcb):
Vertex3f(fx,fy,fz),
nx(fnx),
ny(fny),
nz(fnz),
tu(fu),
tv(fv),
tu2(fu2),
tv2(fv2),
tu3(fu3),
tv3(fv3),
r(fcr),
g(fcg),
b(fcb)
{

}


/** ���캯��2
*/
ThirdVersatileVertex3f::ThirdVersatileVertex3f(Vertex3f& vPos,Vertex3f& vNor,float fu,float fv,float fu2,float fv2,float fu3,float fv3,float fcr,float fcg,float fcb)
:Vertex3f(vPos),
nx(vNor.x),
ny(vNor.y),
nz(vNor.z),
tu(fu),
tv(fv),
tu2(fu2),
tv2(fv2),
tu3(fu3),
tv3(fv3),
r(fcr),
g(fcg),
b(fcb)
{

}

ThirdVersatileVertex3f::ThirdVersatileVertex3f(Vertex3f& vPos,Vertex3f& vNor,Vertex2f& vTex,Vertex2f& vTex2,Vertex2f& vTex3,Vertex3f& vClr)
:Vertex3f(vPos),
nx(vNor.x),
ny(vNor.y),
nz(vNor.z),
tu(vTex.x),
tv(vTex.y),
tu2(vTex2.x),
tv2(vTex2.y),
tu3(vTex3.x),
tv3(vTex3.y),
r(vClr.x),
g(vClr.y),
b(vClr.z)
{

}

size_t ThirdVersatileVertex3f::sizeBuffer()
{
    size_t nSize = Vertex3f::sizeBuffer() +  12* sizeof(float) ;
    return nSize;
}