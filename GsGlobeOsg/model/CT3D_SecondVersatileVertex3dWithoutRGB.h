//********************************************************************************** 
//** �ļ����ƣ�CT3D_SecondVersatileVertex3dWithoutRGB.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�����ࣨȫ�ж��� �����壬
//** �� �� �ˣ� ��
//** �������ڣ� 2013-08-27
//********************************************************************************** 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#include "CT3D_VersatileVertex3dWithoutRGB.h"


class /*DLL_EXPORT*/ SecondVersatileVertex3dWithoutRGB : public Vertex3d
{
    /** @defgroup VersatileVertex3d VersatileVertex3d-ȫ�ж���  
    *  @{
    */
public:
    /** ���� */
    double nx; 
    double ny; 
    double nz;

    /** �������� */
    double tu; 
    double tv;

    /** �������� */
    double tu2; 
    double tv2;
 
    /** @} */ // ���Խ�β
public:
    /** @name ��������������
    *  @{
    */

	//********************************************************************************** 
	//** �������ƣ� SecondVersatileVertex3dWithoutRGB
	//** ���������� ���캯��1
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ��
	//** �������ڣ� 2012-08-27
	//**********************************************************************************
    SecondVersatileVertex3dWithoutRGB(double dblx = 0.0,double dbly = 0.0,
        double dblz = 0.0,double dblnx = 0.0,
        double dblny = 0.0,double dblnz = 0.0,
        double dblu = 0.0,double dblv = 0.0,
		double dblu2 = 0.0,double dblv2 = 0.0);


	//********************************************************************************** 
	//** �������ƣ� SecondVersatileVertex3dWithoutRGB
	//** ���������� ���캯��2
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
    SecondVersatileVertex3dWithoutRGB(Vertex3d& vPos,Vertex3d& vNor,double dblu,double dblv,double dblu2,double dblv2);


    /** ���캯��3
    */
    SecondVersatileVertex3dWithoutRGB(Vertex3d& vPos,Vertex3d& vNor,Vertex2d& vTex,Vertex2d& vTex2);



    Vertex2d GetSecondTexCoor() const;

   

    void SetSecondTexCoor(const Vertex2d& vTex); 

    
    static size_t sizeBuffer();

};


