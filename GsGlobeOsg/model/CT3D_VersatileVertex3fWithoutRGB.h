//********************************************************************************** 
//** �ļ����ƣ�CT3D_VersatileVertex3fWithoutRGB.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�����ࣨȫ�ж��� �����壬
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-13
//********************************************************************************** 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _CT3D_VERSATILEVERTEX3FWITHOUTRGB_H_
#define _CT3D_VERSATILEVERTEX3FWITHOUTRGB_H_

#include "CT3D_Vertex3f.h"
#include "CT3D_Vertex3d.h"

class /*DLL_EXPORT*/ VersatileVertex3fWithoutRGB : public Vertex3f
{
	/** @defgroup VersatileVertex3fWithoutRGB VersatileVertex3fWithoutRGB-ȫ�ж���  
    *  @{
    */

public:
	/** @name ���ԣ���Ա������
	* @{
	*/
	
	/** ���� */
	float nx; 
    float ny; 
    float nz;
	
	/** �������� */
	float tu; 
    float tv;

	/** @} */ // ���Խ�β

public:

	/** @defgroup VersatileVertex3fWithoutRGB ��������Ա������
	* @{
	*/
	
	
	/** @name ��������������
	*  @{
	*/

	/** ���캯��1
	*/
	VersatileVertex3fWithoutRGB(float fx = 0.0,float fy = 0.0,float fz = 0.0,float fnx = 0.0,float fny = 0.0,float fnz = 0.0,float fu = 0.0,float fv = 0.0);
	  
	  
	  /** ���캯��2
	*/
	VersatileVertex3fWithoutRGB(Vertex3f& vPos,Vertex3f& vNor,float fu,float fv);
	 
	  /** ���캯��3
	*/
	  VersatileVertex3fWithoutRGB(Vertex3f& vPos,Vertex3f& vNor,Vertex2f& vTex);
	  
	
	/** @} */ // ����������������β
	
	
	
	/** @name ���ݲ���
	*  @{
	*/

	  /** ��ö��㷨����	
	* @param 
	* @return ���㷨����
    */
	  Vertex3f GetNormal() const
	  {
		  return Vertex3f(nx,ny,nz);
	  }

	   /** ���ö��㷨����
	* @param [in]  vNor ���㷨����	
	* @return
    */
	  void SetNormal(const Vertex3f& vNor) 
	  {
		  nx = vNor.x;
		  ny = vNor.y;
		  nz = vNor.z;
	  }
	  
	  /** ��ö�����������	
	* @param 
	* @return ������������	
    */
	  Vertex2f GetTexCoor() const
	  {
		  return Vertex2f(tu,tv);
	  }

	   /** ���ö�����������	
	* @param [in] vTex ������������		
	* @return
    */
	  void SetTexCoor(const Vertex2f& vTex) 
	  {
		  tu = vTex.x;
		  tv = vTex.y;
	  }
	
	static size_t sizeBuffer();
};

#endif
