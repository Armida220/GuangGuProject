//********************************************************************************** 
//** �ļ����ƣ�CT3D_VersatileVertex3dWithoutRGB.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�����ࣨȫ�ж��� �����壬
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-13
//********************************************************************************** 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _CT3D_VERSATILEVERTEX3DWITHOUTRGB_H_
#define _CT3D_VERSATILEVERTEX3DWITHOUTRGB_H_

#include "CT3D_Vertex3d.h"
#include "CT3D_Vertex3f.h"


class /*DLL_EXPORT*/ VersatileVertex3dWithoutRGB : public Vertex3d
{
    /** @defgroup VersatileVertex3dWithoutRGB VersatileVertex3dWithoutRGB-ȫ�ж���  
    *  @{
    */
public:
    /** @name ���ԣ���Ա������
    * @{
    */

    /** ���� */
    double nx;
    double ny; 
    double nz;

    /** �������� */
    double tu; 
    double tv;

    /** @} */ // ���Խ�β


public:

    /** @defgroup VersatileVertex3dWithoutRGB ��������Ա������
    * @{
    */


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
    VersatileVertex3dWithoutRGB(double fx = 0.0,double fy = 0.0,
        double fz = 0.0,double fnx = 0.0,
        double fny = 0.0,double fnz = 0.0,
        double fu = 0.0,double fv = 0.0);


	//********************************************************************************** 
	//** �������ƣ� VersatileVertex3dWithoutRGB
	//** ���������� ���캯��2
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
    VersatileVertex3dWithoutRGB(Vertex3d& vPos,Vertex3d& vNor,double fu,double fv);


    /** ���캯��3
    */
    VersatileVertex3dWithoutRGB(Vertex3d& vPos,Vertex3d& vNor,Vertex2d& vTex);


    /** @} */ // ����������������β



    /** @name ���ݲ���
    *  @{
    */

    /** ��ö��㷨����	
    * @param 
    * @return ���㷨����
    */
    Vertex3d GetNormal() const;


    /** ���ö��㷨����
    * @param [in]  vNor ���㷨����	
    * @return
    */
    void SetNormal(const Vertex3d& vNor); 


    /** ��ö�����������	
    * @param 
    * @return ������������	
    */
    Vertex2d GetTexCoor() const;


    /** ���ö�����������	
    * @param [in] vTex ������������		
    * @return
    */
    void SetTexCoor(const Vertex2d& vTex); 


    /** �õ���ṹ��С
    * @param 
    * @return ��ṹ��С
    */
    static size_t sizeBuffer();

};


#endif
