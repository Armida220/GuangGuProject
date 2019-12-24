//********************************************************************************** 
//** �ļ����ƣ�CT3D_Vertex3d.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά������ඨ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-13
//********************************************************************************** 


#ifndef _CT3D_VERTEX3D_H_
#define _CT3D_VERTEX3D_H_
#include <osg/Vec3d>
#include "CT3D_MathEx.h"

	enum
	{
		VERTEXTYPE_V3f,				  // for Vertex3f
		VERTEXTYPE_V3d,				  // for Vertex3d

		VERTEXTYPE_V3fT2f,			  // for TexturedVertex3f
		VERTEXTYPE_V3dT2d,			  // for TexturedVertex3d
		
		VERTEXTYPE_V3fN3fC3f,		  // for ShadedVertex3f
		VERTEXTYPE_V3dN3dC3f,		  // for ShadedVertex3d
		
		VERTEXTYPE_V3fT2fN3fC3f,	  // for VersatileVertex3f
		VERTEXTYPE_V3dT2dN3dC3f,	  // for VersatileVertex3d

		VERTEXTYPE_V3fT2fT2fN3fC3f,	  // for SecondVersatileVertex3f
		VERTEXTYPE_V3dT2dT2dN3dC3f,	  // for SecondVersatileVertex3d

		VERTEXTYPE_V3fT2fT2fT2fN3fC3f,// for ThirdVersatileVertex3f
		VERTEXTYPE_V3dT2dT2dT2dN3dC3f,// for ThirdVersatileVertex3d

		VERTEXTYPE_V3dT2dN3dC3f_WithoutRGB,
		VERTEXTYPE_V3dT2dT2dN3dC3f_WithoutRGB,
		VERTEXTYPE_V3dT2dT2dT2dN3dC3f_WithoutRGB,

		VERTEXTYPE_V3fT2fN3fC3f_WithoutRGB,
		VERTEXTYPE_V3fT2fT2fN3fC3f_WithoutRGB,
		VERTEXTYPE_V3fT2fT2fT2fN3fC3f_WithoutRGB,

		VERTEXTYPE_V3fN3f,				//for VertexNormal3f
		VERTEXTYPE_V3dN3d,				//for VertexNormal3d

		//modify by yangling 20131208 begin
		VERTEXTYPE_End
		//modify by yangling 20131208 end
		
	};

	typedef struct tagPLANE3D 
	{
		double A, B, C, D;	
	}PLANE3D;

	typedef struct tagLocation
	{
		osg::Vec3d worldPosition;
		union
		{  
			struct
			{
				double dLongitude;//����
				double dLatitude;//γ��
				double dElevation;//�߳�
			};

			struct
			{
				double X,Y,Z;
			};
			struct
			{
				double dblX,dblY,dblZ;
			};
			struct
			{
				double x,y,z;
			};
		}; 

	}Location;//��λ

	typedef struct tagRotation
	{
		union
		{  
			struct
			{
				double dLongitudeDegree;//�ƾ��߷���
				double dLatitudeDegree;//��γ�߷���
				double dNormalDegree;//�Ʒ��߷���
			};

			struct
			{
				double X,Y,Z;
			};
			struct
			{
				double dblX,dblY,dblZ;
			};
			struct
			{
				double x,y,z;
			};
		}; 

	}Rotation;//��ת

	typedef struct tagZoom
	{
		union
		{  
			struct
			{
				double dLongitudeOrientation;//���߷���
				double dLatitudeOrientation;//γ�߷���
				double dNormalOrientation;//���߷���
			};

			struct
			{
				double X,Y,Z;
			};
			struct
			{
				double dblX,dblY,dblZ;
			};
			struct
			{
				double x,y,z;
			};
		}; 

	}Zoom;//����

#pragma region Vector2D

class  Vertex2d
{
	/** @defgroup Vertex2d Vertex2d-��ά����  
    *  @{
    */
public:
	/** @name ���ԣ���Ա������
	* @{
	*/
	
	/** ��,������ */
	double x;
    double y;
	/** @} */ // ���Խ�β

	/** @defgroup Vertex2d ��������Ա������
	* @{
	*/

    /** @name ��������������
	*  @{
	*/

	/** ���캯��1
	*/
	Vertex2d():x(0.0),y(0.0){}
	/** ���캯��2
	*/
	Vertex2d(double dx,double dy):x(dx),y(dy){}
	/** ���캯��3
	*/
	Vertex2d(const Vertex2d& rv):x(rv.x),y(rv.y){}
	/** @} */ // ����������������β

	/** �������������ض�Ԫ������"=="�������ж������������Ƿ���ȡ�
	* @param [in] vt3d	��ǰ��Ҫ�жϵ�����������
	* @return 1-������������ȣ�0-���������겻��
	*/
	inline int operator==(const Vertex2d& vt2d) const
	{
		return (fabs(vt2d.x - x) < MathEx::TOL && fabs(vt2d.y - y) < MathEx::TOL);
	}

	/** �������������ض�Ԫ������"=="�������ж������������Ƿ���ȡ�
	* @param [in] vt3d	��ǰ��Ҫ�жϵ�����������
	* @return 1-������������ȣ�0-���������겻��
	*/
	inline int operator!=(const Vertex2d& vt2d) const
	{
		return !((*this) == vt2d);
	}

	/** �������������ض�Ԫ������"="�����ڶ�����������ĸ�ֵ��
	* @param [in] vt3d	��ǰ���ڸ�ֵ������������
	* @return ��ֵ������������꣬����ֵΪ������ʽ������������ֵ
	*/
	inline Vertex2d& operator=(const Vertex2d& vt2d)
	{
		x = vt2d.x;
		y = vt2d.y;
		return (*this);
	}

	/** �������������ض�Ԫ������"+="�����ڶ������ĸ��ϸ�ֵ���ӷ�����
	* @param [in] vt2d	��ǰ���ڸ��ϸ�ֵ������
	* @return 
	*/
	inline void operator+=(const Vertex2d& vt2d)
	{
		x += vt2d.x;
		y += vt2d.y;
	}

	/** �������������ض�Ԫ������"-="�����ڶ������ĸ��ϸ�ֵ��������
	* @param [in] vt3d	��ǰ���ڸ��ϸ�ֵ������
	* @return 
	*/
	inline void operator-=(const Vertex2d& vt2d)
	{
		x -= vt2d.x;
		y -= vt2d.y;
	}

	/** ��������������һԪ������"+"������ȡ������������ĵ�ǰֵ��
	* @param 
	* @return ����������ĵ�ǰֵ
	*/
	inline Vertex2d operator+() const
	{
		return (*this);
	}

	/** ��������������һԪ������"-"������ȡ��������������෴ֵ��
	* @param 
	* @return ������������෴ֵ
	*/
	inline Vertex2d operator-() const
	{
		return Vertex2d(-x,-y);
	}
	/** @}*/  // ���ݲ������β

	/** @} */ // ������β

	/** @} */ // ģ���β
};

class  Vertex2f
{
	/** @defgroup Vertex2f Vertex2f-��ά����  
    *  @{
    */
public:
	/** @name ���ԣ���Ա������
	* @{
	*/
	
	/** ��,������ */
	float x,y;
	/** @} */ // ���Խ�β

	/** @defgroup Vertex2d ��������Ա������
	* @{
	*/

    /** @name ��������������
	*  @{
	*/

	/** ���캯��1
	*/
	Vertex2f():x(0.0),y(0.0){}
	/** ���캯��2
	*/
	Vertex2f(float fx,float fy):x(fx),y(fy){}
	/** ���캯��3
	*/
	Vertex2f(const Vertex2f& rv):x(rv.x),y(rv.y){}
    /** @} */ // ����������������β
	
	/** @} */ // ������β

	/** @} */ // ģ���β
};


#pragma endregion Vector2D
//##ModelId=49E86360031F
class  Vertex3d 
{
	/** @defgroup Vertex3d Vertex3d-3d�򵥶��㣨���ࣩ
	*  @{
	*/
public:

	/** @name ���ԣ���Ա������
	* @{
	*/
	
	//##ModelId=49E8636A0373
	/** X����ֵ */
	double x;

	//##ModelId=49E86375038D
	/** Y����ֵ */
	double y;

	//##ModelId=49E8637C0243
	/** Z����ֵ */
	double z;

	/** @} */ // ���Խ�β

public:

	//���캯��
	Vertex3d():x(0.0),y(0.0),z(0.0){}

	Vertex3d(double dx,double dy,double dz):x(dx),y(dy),z(dz){}

	Vertex3d(const Vertex3d& rv):x(rv.x),y(rv.y),z(rv.z){}
	
 	Vertex3d(const tagLocation& rv):x(rv.x),y(rv.y),z(rv.z){}

 	Vertex3d(const tagRotation& rv):x(rv.x),y(rv.y),z(rv.z){}

 	Vertex3d(const tagZoom& rv):x(rv.x),y(rv.y),z(rv.z){}
	

	// ��������
	~Vertex3d(){}
	
	/** @} */ // ����������������β
	
	
	
	/** @name ���ݲ���
	*  @{
	*/

	//##ModelId=49EECBA403C8
	/** �������ÿ�
	* @param 
	* @return 
	*/
	inline void Zero()
	{
		x = y = z =0.0;
	}
	/** ���������е�λ��
	* @param 
	* @return 
	*/
	inline void Normailize()
	{
		double dLength = Length();
		(*this) /= dLength; 
	}

	//##ModelId=49EECF9A0196
	/** �������������ض�Ԫ������"=="�������ж������������Ƿ���ȡ�
	* @param [in] vt3d	��ǰ��Ҫ�жϵ�����������
	* @return 1-������������ȣ�0-���������겻��
    */
	inline int operator==(const Vertex3d& vt3d) const
	{
		return (fabs(vt3d.x - x) < MathEx::TOL && fabs(vt3d.y - y) < MathEx::TOL && fabs(vt3d.z - z) < MathEx::TOL);
	}

	//##ModelId=49EECF9A0196
	/** �������������ض�Ԫ������"=="�������ж������������Ƿ���ȡ�
	* @param [in] vt3d	��ǰ��Ҫ�жϵ�����������
	* @return 1-������������ȣ�0-���������겻��
	*/
	inline int operator!=(const Vertex3d& vt3d) const
	{
		return !((*this) == vt3d);
	}

	//##ModelId=49EED00902FD
	/** �������������ض�Ԫ������"="�����ڶ�����������ĸ�ֵ��
	* @param [in] vt3d	��ǰ���ڸ�ֵ������������
	* @return ��ֵ������������꣬����ֵΪ������ʽ������������ֵ
    */
	inline Vertex3d& operator=(const Vertex3d& vt3d)
	{
		x = vt3d.x;
		y = vt3d.y;
		z = vt3d.z;
		return (*this);
	}

	inline Vertex3d& operator=(const tagLocation& vt3d)
	{
		x = vt3d.x;
		y = vt3d.y;
		z = vt3d.z;
		return (*this);
	}

	inline Vertex3d& operator=(const tagZoom& vt3d)
	{
		x = vt3d.x;
		y = vt3d.y;
		z = vt3d.z;
		return (*this);
	}

	inline Vertex3d& operator=(const tagRotation& vt3d)
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
	inline void operator+=(const Vertex3d& vt3d)
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
	inline void operator-=(const Vertex3d& vt3d)
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
	inline void operator^=(const Vertex3d& vt3d)
	{
		double dTempX,dTempY,dTempZ;
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
	inline void operator*=(double rhd)
	{
		x *= rhd;
		y *= rhd;
		z *= rhd;
	}

	
	/** �������������ض�Ԫ������"*="�����ڶ������ĸ��ϸ�ֵ�����ˣ�
	* @param [in] v	��ǰ���ڸ��ϸ�ֵ�ĳ���
	* @return 
    */
	inline void operator*=(const Vertex3d& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
	}



	//##ModelId=49EED0B8006D
	/** �������������ض�Ԫ������"/="�����ڶ������ĸ��ϸ�ֵ����ˣ���
	* @param [in] rhd	��ǰ���ڸ��ϸ�ֵ�ĳ���
	* @return 
    */
	inline void operator/=(double rhd)
	{
		if(fabs(rhd) < MathEx::TOL)	// �жϳ����Ƿ�Ϊ0����Ϊ0���򲻴���
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
	inline Vertex3d operator+() const
	{
		return (*this);
	}

	//##ModelId=49EEE24C01C5
	/** ��������������һԪ������"-"������ȡ��������������෴ֵ��
	* @param 
	* @return ������������෴ֵ
    */
	inline Vertex3d operator-() const
	{
		return Vertex3d(-x,-y,-z);
	}
	
	/** @} */ // ���ݲ������β
	
	
	
	/** @name �������
	*  @{
	*/

	//##ModelId=49EEDC6D030D
	/** ���ڼ��������ĳ��ȣ�ģ��
	* @param 
	* @return �����ĳ���
    */
	inline double Length() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	//##ModelId=49EEDC7C0251
	/** ���ڼ��������ĳ��ȵ�ƽ��
	* @param 
	* @return �����ĳ��ȵ�ƽ��
    */
	inline double LenghtEx() const
	{
		return x*x + y*y + z*z;
	}

	//##ModelId=49EEDD110128
	/** ���ڼ���������XOYƽ���ͶӰ�����ĳ���
	* @param 
	* @return ������XOYƽ���ͶӰ�����ĳ���
    */
	inline double Length2d() const
	{
		return sqrt(x*x + y*y);
	}

	//##ModelId=49EEDD1D0290
	/** ���ڼ���������XOYƽ���ͶӰ�����ĳ��ȵ�ƽ��
	* @param 
	* @return ������XOYƽ���ͶӰ�����ĳ��ȵ�ƽ��
    */
	inline double Length2dEx() const
	{
		return x*x + y*y;
	}

	//##ModelId=49EF16FB01E4
	/** ���ڼ���������X������ļн�
	* @param 
	* @return ������X������ļнǣ����ȱ�ʾ��
    */
	inline double GetVecXDirection() const
	{
		return GetCrossAngle(Vertex3d(1,0,0));
	}

	//##ModelId=49EF16FB01E4
	/** ���ڼ���������Y������ļн�
	* @param 
	* @return ������Y������ļнǣ����ȱ�ʾ��
    */
	inline double GetVecYDirection() const
	{
		return GetCrossAngle(Vertex3d(0,1,0));
	}

	//##ModelId=49EF16FB01E4
	/** ���ڼ���������Z������ļн�
	* @param 
	* @return ������Z������ļнǣ����ȱ�ʾ��
    */
	inline double GetVecZDirection() const
	{
		return GetCrossAngle(Vertex3d(0,0,1));
	}
    /** ���ڼ�����ά��ṹ��С
    * @param 
    * @return 
    */
   static size_t sizeBuffer(); 

	//##ModelId=49EF174700BB
	/** ���ڼ��㵱ǰ�����봫�������ļн�
	* @param [in] rhv ��������
	* @return ��ǰ�����봫�������ļнǣ����ȱ�ʾ��
    */
	double GetCrossAngle(const Vertex3d& rhv) const;

	/** ���ڼ��㵱ǰ�����봫�������ļн�(���)
	* @param [in] rhv ��������
	* @return ��ǰ�����봫�������ļн�(���)�����ȱ�ʾ��
    */
	double GetCrossAcuteAngle(const Vertex3d& rhv) const;

	/** ���ڼ��㵱ǰ�����봫�������ļн�(���)������ֵ
	* @param [in] rhv ��������
	* @return ��ǰ�����봫�������ļн�(���)������ֵ
    */
	double GetCrossAcuteAngleCos(const Vertex3d& rhv) const;

	//##ModelId=49EF175701E4
	/** ���ڼ��㵱ǰ�����봫�������ļнǵ�����ֵ
	* @param [in] rhv ��������
	* @return ��ǰ�����봫�������ļнǵ�����ֵ
    */
	double GetCrossAngleCos(const Vertex3d& rhv) const;

    /** ���ڼ��㵱ǰ�����봫�������Ĳ������ĳ���
	* @param [in] rhv ��������
	* @return ��ǰ�����봫�������ĵĲ������ĳ���
    */
	double DVertexToVertex3d(const Vertex3d& rhv) const;

    /** ���ڼ��㵱ǰ�����봫�������Ĳ�������XOYƽ���ͶӰ�����ĳ���
	* @param [in] rhv ��������
	* @return ��ǰ�����봫�������ĵĲ�������XOYƽ���ͶӰ�����ĳ���
    */
	double DVertexToVertex2d(const Vertex3d& rhv) const;

	void GetAlphaBeta(double& a, double& b) const;
	
    /** ���ڼ��㵱ǰ�����ڴ��������ϵ�ͶӰ����
	* @param [in] rhv ��������
	* @return ��ǰ�����ڴ��������ϵ�ͶӰ����
    */
	double GetProjectLengthInVector(Vertex3d& vVec) const;

	/** ���ڼ��㵱ǰ�����ڴ��������ϵ�ͶӰ�߶�
	* @param [in] rhv ��������
	* @return ��ǰ�����ڴ��������ϵ�ͶӰ�߶�
    */
	double GetProjectHeightInVector(Vertex3d& vVec) const;



};



 const Vertex3d operator+(const Vertex3d& lhv, const Vertex3d& rhv);


 const Vertex3d operator-(const Vertex3d& lhv, const Vertex3d& rhv);


 const Vertex3d operator^(const Vertex3d& lhv, const Vertex3d& rhv);


 const Vertex3d operator*(const Vertex3d& lhv, double rhd);


 const Vertex3d operator*(double lhd, const Vertex3d& rhv);


 double operator*(const Vertex3d& lhv, const Vertex3d& rhv);


 const Vertex3d operator/(const Vertex3d& lhv, double rhd);

 
 const Vertex3d GetNormal(const Vertex3d& v1,const Vertex3d& v2,const Vertex3d& v3);

 /** @} */ // ģ���β



#endif 
