//********************************************************************************** 
//** �ļ����ƣ�CT3D_VersatileVertex3f.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�����ࣨȫ�ж��� �����壬
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-13
//********************************************************************************** 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _CT3D_VERSATILEVERTEX3F_H_
#define _CT3D_VERSATILEVERTEX3F_H_

#include "CT3D_Vertex3f.h"
#include "CT3D_Vertex3d.h"

class /*DLL_EXPORT*/ VersatileVertex3f : public Vertex3f
{
	/** @defgroup VersatileVertex3f VersatileVertex3f-ȫ�ж���  
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

	/** ��ɫ */
	float r; 
    float g; 
    float b;

	/** @} */ // ���Խ�β

public:

	/** @defgroup VersatileVertex3f ��������Ա������
	* @{
	*/
	
	
	/** @name ��������������
	*  @{
	*/

	/** ���캯��1
	*/
	VersatileVertex3f(float fx = 0.0,float fy = 0.0,float fz = 0.0,float fnx = 0.0,float fny = 0.0,float fnz = 0.0,float fu = 0.0,float fv = 0.0,float fcr = 0.0,float fcg = 0.0,float fcb = 0.0);
	  
	  
	  /** ���캯��2
	*/
	VersatileVertex3f(Vertex3f& vPos,Vertex3f& vNor,float fu,float fv,float fcr,float fcg,float fcb);
	 
	  /** ���캯��3
	*/
	  VersatileVertex3f(Vertex3f& vPos,Vertex3f& vNor,Vertex2f& vTex,Vertex3f& vClr);
	  
	
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
	  
	  /** ��ö�����ɫ	
	* @param 
	* @return ������ɫ
    */
	  Vertex3f GetColor() const
	  {
		  return Vertex3f(r,g,b);
	  }
	  
	  
	  /** ���ö�����ɫ
	* @param [in] vClr	 ������ɫ
	* @return
    */
	  void SetColor(const Vertex3f& vClr)
	  {
		  r = vClr.x;
		  g = vClr.y;
		  b = vClr.z;
	}

	
static size_t sizeBuffer();
};

#endif
