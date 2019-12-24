
#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#include "CT3D_SecondVersatileVertex3d.h"


class /*DLL_EXPORT*/ ThirdVersatileVertex3d : public Vertex3d
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

    /** �������� */
    double tu3; 
    double tv3;


    /** ��ɫ */
    float r; 
    float g; 
    float b;
    /** @name ���ԣ���Ա������
    */
   
    /** @} */ // ���Խ�β


public:




    /** @name ��������������
    *  @{
    */

	//********************************************************************************** 
	//** �������ƣ� VersatileVertex3d
	//** ���������� ���캯��1
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ��
	//** �������ڣ� 2013-08-27
	//**********************************************************************************
    ThirdVersatileVertex3d(double dblx = 0.0,double dbly = 0.0,
        double dblz = 0.0,double dblnx = 0.0,
        double dblny = 0.0,double dblnz = 0.0,
        double dblu = 0.0,double dblv = 0.0,
		double dblu2 = 0.0,double dblv2 = 0.0,
		double dblu3 = 0.0,double dblv3 = 0.0,
        float fcr = 0.0,float fcg = 0.0,
        float fcb =0.0);


	//********************************************************************************** 
	//** �������ƣ� VersatileVertex3d
	//** ���������� ���캯��2
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ��
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
    ThirdVersatileVertex3d(Vertex3d& vPos,Vertex3d& vNor,double dblu,double dblv,double dblu2,double dblv2,double dblu3,double dblv3 ,float fcr,float fcg,float fcb);


    /** ���캯��3
    */
    ThirdVersatileVertex3d(Vertex3d& vPos,Vertex3d& vNor,Vertex2d& vTex,Vertex2d& vTex2,Vertex2d& vTex3,Vertex3f& vClr);


	/** ��ö�����������	
    * @param 
    * @return ������������	
    */
    Vertex2d GetThirdTexCoor() const;

   
		/** ���ö�����������	
    * @param [in] vTex ������������		
    * @return
    */
    void SetThirdTexCoor(const Vertex2d& vTex); 


    /** �õ���ṹ��С
    * @param 
    * @return ��ṹ��С
    */
    static size_t sizeBuffer();

};


