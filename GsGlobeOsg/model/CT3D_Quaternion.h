//********************************************************************************** 
//** �ļ����ƣ�CT3D_Quaternion.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��Ԫ���ඨ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-14
//********************************************************************************** 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_QUATERNION_49E34729030D_INCLUDED
#define _INC_QUATERNION_49E34729030D_INCLUDED

#include "ModelDef.h"
#include "CT3D_Vertex3d.h"

//##ModelId=49E34729030D
class  Quaternion 
{

	/** @defgroup Quaternion Quaternion-��Ԫ��
	*  @{
	*/
public:

	/** @name ���ԣ���Ա������
	* @{
	*/
	
	/** ��Ա���� */
	double x,y,z,w;
	
	/** @} */ // ���Խ�β

	/** @defgroup Material ��������Ա������
	* @{
	*/


	/** @name ��������������
	*  @{
	*/
private:
	//##ModelId=49E3473D0223
	Vertex3d* _v;
public:

	/** ���캯��1(Ĭ��Ϊ��Ԫ��Ԫ��)
	*/
	inline Quaternion (
		double fW = 1.0,
		double fX = 0.0, double fY = 0.0, double fZ = 0.0):w(fW),x(fX),y(fY),z(fZ){}	

	/** ���캯��2(�ɽǶȺ�����������Ԫ��)
	*/
	inline Quaternion( double rfAngle, const Vertex3d& rkAxis)
	{
		FromAngleAxis(rfAngle,rkAxis);
	}
	
	/** ���캯��3(����֪����Ԫ����������Ԫ��)
	*/
	inline Quaternion (const Quaternion& rkQ)
	{
		w = rkQ.w;
		x = rkQ.x;
		y = rkQ.y;
		z = rkQ.z;
	}

	


	/** @} */ // ����������������β

	/** @name �������
	*  @{
	*/

	/** ������ǵõ���Ԫ��	
	* @param[in]rRadian �뾶
	* @param[in]rkAxis ����
	* @return 
    */
	void FromAngleAxis ( double rRadian, const Vertex3d& rkAxis);
	/** ����Ԫ���õ��뾶����ת����	
	* @param[out]rRadian �뾶
	* @param[out]rkAxis ����
	* @return 
    */
	void ToAngleAxis (double& rRadian, Vertex3d& rkAxis) const;
	

	
	/** ��ֵ����	
	* @param[in]rkQ �������Ԫ��
	* @return ��Ԫ��������
    */
	inline Quaternion& operator= (const Quaternion& rkQ)
	{
		w = rkQ.w;
		x = rkQ.x;
		y = rkQ.y;
		z = rkQ.z;
		return *this;
	}

	Quaternion operator+ (const Quaternion& rkQ) const;
	Quaternion operator- (const Quaternion& rkQ) const;
	Quaternion operator* (const Quaternion& rkQ) const;
	Quaternion operator* (double fScalar) const;
	Vertex3d  operator* (const Vertex3d& v) const;

	Quaternion operator- () const;

	/** �ȼ��ж�	
	* @param[in]rkQ �������Ԫ��
	* @return 1-�ȼ�,0-���ȼ�
    */
	inline int operator== (const Quaternion& rhs) const //xx_0121
	{
		/*return (rhs.x == x) && 
			(rhs.y == y) &&
			(rhs.z == z) && 
			(rhs.w == w);*/

		return ( fabs(rhs.x - x) < MathEx::TOL ) &&
			( fabs(rhs.y - y) < MathEx::TOL ) &&
			( fabs(rhs.z - z) < MathEx::TOL ) &&
			( fabs(rhs.w - w) < MathEx::TOL );
	}
	/** ���ȼ��ж�	
	* @param[in]rkQ �������Ԫ��
	* @return 1-���ȼ�,0-�ȼ�
    */
	inline int operator!= (const Quaternion& rhs) const
	{
		return !operator==(rhs);
	}

    /** ���㵱ǰ��Ԫ���봫�����Ԫ���ĳ˻�	
	* @param[in]rkQ �������Ԫ��
	* @return ��ǰ��Ԫ���봫�����Ԫ���ĳ˻�
    */
	double Dot (const Quaternion& rkQ) const;  // dot product
	
	/** ���㵱ǰ��Ԫ����ģ	
	* @param
	* @return ��ǰ��Ԫ����ģ
    */
	double Norm () const;  // squared-length

    /** ��λ����ǰ��Ԫ����ģ,�����ص�λ��֮ǰ��Ԫ���ĳ���
	* @param
	* @return ��λ��֮ǰ����Ԫ���ĳ���
    */
	double normalise(void);
	
	/** ��ǰ��Ԫ������
	* @param
	* @return ��ǰ��Ԫ������
    */
	Quaternion Inverse () const;  // apply to non-zero quaternion
	Quaternion UnitInverse () const;  // apply to unit-length quaternion
	Quaternion Exp () const;
	Quaternion Log () const;

	/** Calculate the local roll element of this quaternion.
	@param reprojectAxis By default the method returns the 'intuitive' result
	that is, if you projected the local Y of the quaterion onto the X and
	Y axes, the angle between them is returned. If set to 0 though, the
	result is the actual yaw that will be used to implement the quaternion,
	which is the shortest possible path to get to the same orientation and 
	may involve less axial rotation. 
	*/
	double getRoll(int reprojectAxis = 1) const;
	/** Calculate the local pitch element of this quaternion
	@param reprojectAxis By default the method returns the 'intuitive' result
	that is, if you projected the local Z of the quaterion onto the X and
	Y axes, the angle between them is returned. If set to 1 though, the
	result is the actual yaw that will be used to implement the quaternion,
	which is the shortest possible path to get to the same orientation and 
	may involve less axial rotation. 
	*/
	double getPitch(int reprojectAxis = 1) const;
	/** Calculate the local yaw element of this quaternion
	@param reprojectAxis By default the method returns the 'intuitive' result
	that is, if you projected the local Z of the quaterion onto the X and
	Z axes, the angle between them is returned. If set to 1 though, the
	result is the actual yaw that will be used to implement the quaternion,
	which is the shortest possible path to get to the same orientation and 
	may involve less axial rotation. 
	*/
	double getYaw(int reprojectAxis = 1) const;		
	/// Equality with tolerance (tolerance is max angle difference)

	int equals(const Quaternion& rhs, double& tolerance) const;

	// spherical linear interpolation
	static Quaternion Slerp (double fT, const Quaternion& rkP,
		const Quaternion& rkQ, int shortestPath = 0);

	static Quaternion SlerpExtraSpins (double fT,
		const Quaternion& rkP, const Quaternion& rkQ,
		int iExtraSpins);

	// setup for spherical quadratic interpolation
	static void Intermediate (const Quaternion& rkQ0,
		const Quaternion& rkQ1, const Quaternion& rkQ2,
		Quaternion& rka, Quaternion& rkB);

	// spherical quadratic interpolation
	static Quaternion Squad (double fT, const Quaternion& rkP,
		const Quaternion& rkA, const Quaternion& rkB,
		const Quaternion& rkQ, int shortestPath = 0);

	// normalised linear interpolation - faster but less accurate (non-constant rotation velocity)
	static Quaternion nlerp(double fT, const Quaternion& rkP, 
		const Quaternion& rkQ, int shortestPath = 0);

	// cutoff for sine near zero
	static const double ms_fEpsilon;

	// special values
	static const Quaternion ZERO;
	static const Quaternion IDENTITY;

	void FromAxes (const Vertex3d* akAxis);
	void FromAxes (const Vertex3d& xAxis, const Vertex3d& yAxis, const Vertex3d& zAxis);
	void ToAxes (Vertex3d* akAxis) const;
	void ToAxes (Vertex3d& xAxis, Vertex3d& yAxis, Vertex3d& zAxis) const;
	/// Get the local x-axis
	Vertex3d xAxis(void) const;
	/// Get the local y-axis
	Vertex3d yAxis(void) const;
	/// Get the local z-axis
	Vertex3d zAxis(void) const;

	//##ModelId=49EC1D490196
	void Normalize();

	//##ModelId=49EF26290242
	

	//##ModelId=49EF269400DA
	Quaternion(const Vertex3d& xaxis, const Vertex3d& yaxis, const Vertex3d& zaxis);

    static size_t sizeBuffer();

};


#endif 
