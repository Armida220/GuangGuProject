//********************************************************************************** 
//** �ļ����ƣ�CT3D_ThirdVersatileVertex3fWithoutRGB.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�����ࣨȫ�ж��� �����壬
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-13
//********************************************************************************** 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#include "CT3D_SecondVersatileVertex3fWithoutRGB.h"


class /*DLL_EXPORT*/ ThirdVersatileVertex3fWithoutRGB : public Vertex3f
{
public:

    /** ���� */
    float nx; 
    float ny; 
    float nz;

    /** �������� */
    float tu; 
    float tv;

    /** �������� */
    float tu2; 
    float tv2;

    /** �������� */
    float tu3; 
    float tv3;

	
public:

	/** ���캯��1
	*/
	ThirdVersatileVertex3fWithoutRGB(float fx = 0.0,float fy = 0.0,float fz = 0.0,float fnx = 0.0,float fny = 0.0,float fnz = 0.0,float fu = 0.0,float fv = 0.0,float fu2 = 0.0,float fv2 = 0.0,float fu3 = 0.0,float fv3 = 0.0);

	/** ���캯��2
	*/
	ThirdVersatileVertex3fWithoutRGB(Vertex3f& vPos,Vertex3f& vNor,float fu,float fv,float fu2,float fv2,float fu3,float fv3);

	/** ���캯��3
	*/
	ThirdVersatileVertex3fWithoutRGB(Vertex3f& vPos,Vertex3f& vNor,Vertex2f& vTex,Vertex2f& vTex2,Vertex2f& vTex3);

	/** ��ö�����������	
	* @param 
	* @return ������������	
	*/
	Vertex2f GetThirdTexCoor() const
	{
		return Vertex2f(tu3,tv3);
	}

	/** ���ö�����������	
	* @param [in] vTex ������������		
	* @return
	*/
	void SetThirdTexCoor(const Vertex2f& vTex) 
	{
		tu3 = vTex.x;
		tv3 = vTex.y;
	}	
	static size_t sizeBuffer();
};


