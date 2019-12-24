//********************************************************************************** 
//** �ļ����ƣ�CT3D_VersatileVertex3d.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�����ࣨȫ�ж��� �����壬
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-13
//********************************************************************************** 


#ifndef _CT3D_VERSATILEVERTEX3D_H_
#define _CT3D_VERSATILEVERTEX3D_H_

#include "CT3D_Vertex3d.h"
#include "CT3D_Vertex3f.h"


class /*DLL_EXPORT*/ VersatileVertex3d : public Vertex3d
{
    /** @defgroup VersatileVertex3d VersatileVertex3d-ȫ�ж���  
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

    /** ��ɫ */
    float r; 
    float g; 
    float b;

    /** @} */ // ���Խ�β


public:

    /** @defgroup VersatileVertex3d ��������Ա������
    * @{
    */


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
    VersatileVertex3d(double fx = 0.0,double fy = 0.0,
        double fz = 0.0,double fnx = 0.0,
        double fny = 0.0,double fnz = 0.0,
        double fu = 0.0,double fv = 0.0,
        float fcr = 0.0,float fcg = 0.0,
        float fcb =0.0);


	//********************************************************************************** 
	//** �������ƣ� VersatileVertex3d
	//** ���������� ���캯��2
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
    VersatileVertex3d(Vertex3d& vPos,Vertex3d& vNor,double fu,double fv,float fcr,float fcg,float fcb);


    /** ���캯��3
    */
    VersatileVertex3d(Vertex3d& vPos,Vertex3d& vNor,Vertex2d& vTex,Vertex3f& vClr);


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


    /** ��ö�����ɫ	
    * @param 
    * @return ������ɫ
    */
    Vertex3f GetColor() const;



    /** ���ö�����ɫ
    * @param [in] vClr	 ������ɫ
    * @return
    */
    void SetColor(const Vertex3f& vClr);


    /** �õ���ṹ��С
    * @param 
    * @return ��ṹ��С
    */
    static size_t sizeBuffer();

};


#endif
