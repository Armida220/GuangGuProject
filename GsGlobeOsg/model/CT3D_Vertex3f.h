//********************************************************************************** 
//** �ļ����ƣ�CT3D_Vertex3f.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�����ඨ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-13
//********************************************************************************** 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _CT3D_VERTEX3F_H_
#define _CT3D_VERTEX3F_H_
#include"ModelDef.h"
#include "CT3D_MathEx.h"

//##ModelId=49E99AC50251
class /*DLL_EXPORT*/ Vertex3f 
{
	/** @defgroup Vertex3f Vertex3f-3f�򵥶��㣨���ࣩ 
    *  @{
    */
public:
	/** @name ���ԣ���Ա������
	* @{
	*/

	/** �ռ����� */
	float x; 
    float y; 
    float z;

	/** @} */ // ���Խ�β

public:

	/** @defgroup Vertex3f ��������Ա������
	* @{
	*/
	
	
	/** @name ��������������
	*  @{
	*/

	// ���캯�� ������ʼ���б�
	Vertex3f(float fx=0.0,float fy=0.0,float fz=0.0):x(fx),y(fy),z(fz){}
	
	// ���캯�� ���������캯������ʼ���б�
	Vertex3f(const Vertex3f& rv):x(rv.x),y(rv.y),z(rv.z){}
	
	// ��������
	~Vertex3f(){}
	
	/** @} */ // ����������������β
	
	
	
	/** @name ���ݲ���
	*  @{
	*/

	//##ModelId=49EECBA403C8
	/** ���������е�λ��
	* @param 
	* @return 
	*/
	inline void Normailize()
	{
		float dLength = Length();
		(*this) /= dLength; 
	}

	//##ModelId=49EECF9A0196
	/** �������������ض�Ԫ������"=="�������ж������������Ƿ���ȡ�
	* @param [in] vt3d	��ǰ��Ҫ�жϵ�����������
	* @return 1-������������ȣ�0-���������겻��
	*/
	inline int operator==(const Vertex3f& vt3d) const
	{
		return (fabs(vt3d.x - x) < MathEx::TOL_F && fabs(vt3d.y - y) < MathEx::TOL_F && fabs(vt3d.z - z) < MathEx::TOL_F);
	}

	//##ModelId=49EECF9A0196
	/** �������������ض�Ԫ������"=="�������ж������������Ƿ���ȡ�
	* @param [in] vt3d	��ǰ��Ҫ�жϵ�����������
	* @return 1-������������ȣ�0-���������겻��
	*/
	inline int operator!=(const Vertex3f& vt3d) const
	{
		return !((*this) == vt3d);
	}

	//##ModelId=49EED00902FD
	/** �������������ض�Ԫ������"="�����ڶ�����������ĸ�ֵ��
	* @param [in] vt3d	��ǰ���ڸ�ֵ������������
	* @return ��ֵ������������꣬����ֵΪ������ʽ������������ֵ
	*/
	inline Vertex3f& operator=(const Vertex3f& vt3d)
	{
		x = vt3d.x;
		y = vt3d.y;
		z = vt3d.z;
		return (*this);
	}

	//##ModelId=49EED0B6001F
	/** �������������ض�Ԫ������"+="�����ڶ������ĸ��ϸ�ֵ���ӷ�����
	* @param [in] vt3d	��ǰ���ڸ��ϸ�ֵ������
	* @return 
	*/
	inline void operator+=(const Vertex3f& vt3d)
	{
		x += vt3d.x;
		y += vt3d.y;
		z += vt3d.z;
	}

	//##ModelId=49EED0B8006D
	/** �������������ض�Ԫ������"-="�����ڶ������ĸ��ϸ�ֵ��������
	* @param [in] vt3d	��ǰ���ڸ��ϸ�ֵ������
	* @return 
	*/
	inline void operator-=(const Vertex3f& vt3d)
	{
		x -= vt3d.x;
		y -= vt3d.y;
		z -= vt3d.z;
	}

	//##ModelId=49EED0B8006D
	/** �������������ض�Ԫ������"^="�����ڶ������ĸ��ϸ�ֵ����ˣ�
	* @param [in] vt3d	��ǰ���ڸ��ϸ�ֵ������
	* @return 
	*/
	inline void operator^=(const Vertex3f& vt3d)
	{
		float dTempX,dTempY,dTempZ;
		dTempX = y * vt3d.z - z * vt3d.y;
		dTempY = z * vt3d.x - x * vt3d.z;
		dTempZ = x * vt3d.y - y * vt3d.x;
		x = dTempX; y = dTempY; z = dTempZ;
	}

	//##ModelId=49EED0B8006D
	/** �������������ض�Ԫ������"*="�����ڶ������ĸ��ϸ�ֵ�����ˣ�
	* @param [in] rhd	��ǰ���ڸ��ϸ�ֵ�ĳ���
	* @return 
	*/
	inline void operator*=(float rhd)
	{
		x *= rhd;
		y *= rhd;
		z *= rhd;
	}


	//##ModelId=49EED0B8006D
	/** �������������ض�Ԫ������"/="�����ڶ������ĸ��ϸ�ֵ����ˣ���
	* @param [in] rhd	��ǰ���ڸ��ϸ�ֵ�ĳ���
	* @return 
	*/
	inline void operator/=(float rhd)
	{
		if(fabs(rhd) < MathEx::TOL_F)	// �жϳ����Ƿ�Ϊ0����Ϊ0���򲻴���
			return;
		else
		{
			x /= rhd;
			y /= rhd;
			z /= rhd;
		}
	}

	//##ModelId=49EEE24C01C5
	/** ��������������һԪ������"+"������ȡ������������ĵ�ǰֵ��
	* @param 
	* @return ����������ĵ�ǰֵ
	*/
	inline Vertex3f operator+() const
	{
		return (*this);
	}

	//##ModelId=49EEE24C01C5
	/** ��������������һԪ������"-"������ȡ��������������෴ֵ��
	* @param 
	* @return ������������෴ֵ
	*/
	inline Vertex3f operator-() const
	{
		return Vertex3f(-x,-y,-z);
	}
	
	/** @} */ // ���ݲ������β
	
	
    /** ���ڼ�����ά��ṹ��С
    * @param 
    * @return 
    */
   static size_t sizeBuffer(); 
	/** @name �������
	*  @{
	*/

	//##ModelId=49EEDC6D030D
	/** ���ڼ��������ĳ��ȣ�ģ��
	* @param 
	* @return �����ĳ���
	*/
	inline float Length() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	//##ModelId=49EEDC7C0251
	/** ���ڼ��������ĳ��ȵ�ƽ��
	* @param 
	* @return �����ĳ��ȵ�ƽ��
	*/
	inline float LenghtEx() const
	{
		return x*x + y*y + z*z;
	}

	//##ModelId=49EEDD110128
	/** ���ڼ���������XOYƽ���ͶӰ�����ĳ���
	* @param 
	* @return ������XOYƽ���ͶӰ�����ĳ���
	*/
	inline float Length2d() const
	{
		return sqrt(x*x + y*y);
	}

	//##ModelId=49EEDD1D0290
	/** ���ڼ���������XOYƽ���ͶӰ�����ĳ��ȵ�ƽ��
	* @param 
	* @return ������XOYƽ���ͶӰ�����ĳ��ȵ�ƽ��
	*/
	inline float Length2dEx() const
	{
		return x*x + y*y;
	}

	//##ModelId=49EF16FB01E4
	/** ���ڼ���������X������ļн�
	* @param 
	* @return ������X������ļнǣ����ȱ�ʾ��
	*/
	inline float GetVecXDirection() const
	{
		return GetCrossAngle(Vertex3f(1,0,0));
	}

	//##ModelId=49EF16FB01E4
	/** ���ڼ���������Y������ļн�
	* @param 
	* @return ������Y������ļнǣ����ȱ�ʾ��
	*/
	inline float GetVecYDirection() const
	{
		return GetCrossAngle(Vertex3f(0,1,0));
	}

	//##ModelId=49EF16FB01E4
	/** ���ڼ���������Z������ļн�
	* @param 
	* @return ������Z������ļнǣ����ȱ�ʾ��
	*/
	inline float GetVecZDirection() const
	{
		return GetCrossAngle(Vertex3f(0,0,1));
	}

	//##ModelId=49EF174700BB
	/** ���ڼ��㵱ǰ�����봫�������ļн�
	* @param [in] rhv ��������
	* @return ��ǰ�����봫�������ļнǣ����ȱ�ʾ��
	*/
	float GetCrossAngle(const Vertex3f& rhv) const;

	//##ModelId=49EF175701E4
	/** ���ڼ��㵱ǰ�����봫�������ļнǵ�����ֵ
	* @param [in] rhv ��������
	* @return ��ǰ�����봫�������ļнǵ�����ֵ
	*/
	float GetCrossAngleCos(const Vertex3f& rhv) const;

    /** ���ڼ��㵱ǰ�����봫�������Ĳ������ĳ���
	* @param [in] rhv ��������
	* @return ��ǰ�����봫�������ĵĲ������ĳ���
    */
	float DVertexToVertex3d(const Vertex3f& rhv) const;

	/** ���ڼ��㵱ǰ�����봫�������Ĳ�������XOYƽ���ͶӰ�����ĳ���
	* @param [in] rhv ��������
	* @return ��ǰ�����봫�������ĵĲ�������XOYƽ���ͶӰ�����ĳ���
    */
	float DVertexToVertex2d(const Vertex3f& rhv) const;
	
	/** @} */ // ����������β
	
	/** @} */ // ������β

};

/*DLL_EXPORT*/ const Vertex3f operator+(const Vertex3f& lhv, const Vertex3f& rhv);


/*DLL_EXPORT*/ const Vertex3f operator-(const Vertex3f& lhv, const Vertex3f& rhv);


/*DLL_EXPORT*/ const Vertex3f operator^(const Vertex3f& lhv, const Vertex3f& rhv);


/*DLL_EXPORT*/ const Vertex3f operator*(const Vertex3f& lhv, float rhd);


/*DLL_EXPORT*/ const Vertex3f operator*(float lhd, const Vertex3f& rhv);


/*DLL_EXPORT*/ float operator*(const Vertex3f& lhv, const Vertex3f& rhv);


/*DLL_EXPORT*/ const Vertex3f operator/(const Vertex3f& lhv, float rhd);
	/** @} */ // ģ���β


#endif /* _INC_VERTEX3F_49E99AC50251_INCLUDED */
