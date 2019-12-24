//********************************************************************************** 
//** �ļ����ƣ�CT3D_Vertex3f.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά������ʵ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-13
//********************************************************************************** 

#include "CT3D_Vertex3f.h"



size_t Vertex3f::sizeBuffer()
{
    size_t nSize = 3*sizeof(float);
    return nSize;
}
	//##ModelId=49EED0B8006D
	/** �������������ض�Ԫ������"*="�����ڶ������ĸ��ϸ�ֵ�����ˣ�
	* @param [in] m4x4	��ǰ���ڸ��ϸ�ֵ�ĳ���
	* @return 
    */

		//##ModelId=49EF174700BB
		float Vertex3f::GetCrossAngle(const Vertex3f& rhv) const
		{
			// TODO: Add your specialized code here.

			float dCosAngle = GetCrossAngleCos(rhv);
			float Angle;

			// ����ע�⣬���ǵ�acos����ֻ�ܼ���-1��1֮�䣬��˶���1��-1�ֿ�����
			if(fabs(dCosAngle - 1) < MathEx::TOL) 
				Angle = 0;
			else if(fabs(dCosAngle + 1) < MathEx::TOL)
				Angle = float(MathEx::ONE_PI);
			else
				Angle = acos( dCosAngle );
			return Angle;
		}

		//##ModelId=49EF175701E4
		float Vertex3f::GetCrossAngleCos(const Vertex3f& rhv) const
		{
			// TODO: Add your specialized code here.
			float ddd = Length() * rhv.Length();
			if(fabs(ddd) < MathEx::TOL)
				return 1; // 0��������������ƽ�У���нǿ�����Ϊ��0�㣬cosֵΪ1
			return ((*this) * rhv) / ddd;
		}

		float Vertex3f::DVertexToVertex2d(const Vertex3f& rhv) const
		{
			return ((*this) - rhv).Length2d();
		}
		float Vertex3f:: DVertexToVertex3d(const Vertex3f& rhv) const
		{
			return ((*this) - rhv).Length();
		}

		const Vertex3f operator+(const Vertex3f& lhv, const Vertex3f& rhv)
		{
			Vertex3f vRes = lhv;
			vRes += rhv;
			return vRes;
		}

		const Vertex3f operator-(const Vertex3f& lhv, const Vertex3f& rhv)
		{
			Vertex3f vRes = lhv;
			vRes -= rhv;
			return vRes;
		}

		const Vertex3f operator^(const Vertex3f& lhv, const Vertex3f& rhv)
		{
			Vertex3f vRes = lhv;
			vRes ^= rhv;
			return vRes;
		}

		const Vertex3f operator*(const Vertex3f& lhv, float rhd)
		{
			Vertex3f vRes = lhv;
			vRes *= rhd;
			return vRes;
		}

		const Vertex3f operator*(float lhd, const Vertex3f& rhv)
		{
			Vertex3f vRes = rhv;
			vRes *= lhd;
			return vRes;
		}

		float operator*(const Vertex3f& lhv, const Vertex3f& rhv)
		{
			// ���Vertex3f�����ݳ�Աxyz�����˽�еģ���ô��Ҫ�����������������Ϊfriend����ʹ������������������������Ϊfriend����Ϊ���õĶ�������ڲ�ʵ��
			return lhv.x * rhv.x + lhv.y * rhv.y + lhv.z * rhv.z;
		}

		const Vertex3f operator/(const Vertex3f& lhv, float rhd)
		{
			Vertex3f vRes = lhv;
			vRes /= rhd;
			return vRes;
		}

