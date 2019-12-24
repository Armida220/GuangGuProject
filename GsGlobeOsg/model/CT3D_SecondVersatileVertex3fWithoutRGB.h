//********************************************************************************** 
//** �ļ����ƣ�CT3D_SecondVersatileVertex3fWithoutRGB.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�����ࣨȫ�ж��� �����壬
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-13
//********************************************************************************** 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#include "CT3D_VersatileVertex3fWithoutRGB.h"

class /*DLL_EXPORT*/ SecondVersatileVertex3fWithoutRGB : public Vertex3f
{
	/** @defgroup VersatileVertex3f VersatileVertex3f-ȫ�ж���  
    *  @{
    */

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
	
public:
	/** ���캯��1
	*/
	SecondVersatileVertex3fWithoutRGB(float fx = 0.0,float fy = 0.0,float fz = 0.0,float fnx = 0.0,float fny = 0.0,float fnz = 0.0,float fu = 0.0,float fv = 0.0,float fu2 = 0.0,float fv2 = 0.0);
	  
	  
	  /** ���캯��2
	*/
	SecondVersatileVertex3fWithoutRGB(Vertex3f& vPos,Vertex3f& vNor,float fu,float fv,float fu2,float fv2);
	 
	  /** ���캯��3
	*/
	SecondVersatileVertex3fWithoutRGB(Vertex3f& vPos,Vertex3f& vNor,Vertex2f& vTex,Vertex2f& vTex2); 


	/** ��ö�����������	
	* @param 
	* @return ������������	
	*/
	Vertex2f GetSecondTexCoor() const
	{
		return Vertex2f(tu2,tv2);
	}

	/** ���ö�����������	
	* @param [in] vTex ������������		
	* @return
	*/
	void SetSecondTexCoor(const Vertex2f& vTex) 
	{
		tu2 = vTex.x;
		tv2 = vTex.y;
	}	
	static size_t sizeBuffer();
};

