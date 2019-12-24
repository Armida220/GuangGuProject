//********************************************************************************** 
//** �ļ����ƣ�CT3D_Vertex3d.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�������ʵ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-13
//********************************************************************************** 

#include "CT3D_Vertex3d.h"

size_t Vertex3d::sizeBuffer()
{
    size_t nSize = 3*sizeof(double);
    return nSize;
}
double Vertex3d::GetCrossAngle(const Vertex3d& rhv) const
{
	// TODO: Add your specialized code here.

	double dCosAngle = GetCrossAngleCos(rhv);
	double Angle;

	// ����ע�⣬���ǵ�acos����ֻ�ܼ���-1��1֮�䣬��˶���1��-1�ֿ�����
	if(fabs(dCosAngle - 1) < MathEx::TOL) 
		Angle = 0;
	else if(fabs(dCosAngle + 1) < MathEx::TOL)
		Angle = MathEx::ONE_PI;
	else
		Angle = acos( dCosAngle );
	return Angle;
}

double Vertex3d::GetCrossAcuteAngle(const Vertex3d& rhv) const
{
	double dCosAngle = GetCrossAcuteAngleCos(rhv);
	double Angle;

	// ����ע�⣬���ǵ�acos����ֻ�ܼ���-1��1֮�䣬��˶���1��-1�ֿ�����
	if(fabs(dCosAngle - 1) < MathEx::TOL) 
		Angle = 0;
	else if(fabs(dCosAngle + 1) < MathEx::TOL)
		Angle = MathEx::ONE_PI;
	else
		Angle = acos( dCosAngle );
	return Angle;
}



//##ModelId=49EF175701E4
double Vertex3d::GetCrossAngleCos(const Vertex3d& rhv) const
{
	// TODO: Add your specialized code here.
	double ddd = Length() * rhv.Length();
	if(fabs(ddd) < MathEx::TOL)
		return 1; // 0��������������ƽ�У���нǿ�����Ϊ��0�㣬cosֵΪ1
	return ((*this) * rhv) / ddd;
}

double Vertex3d::GetCrossAcuteAngleCos(const Vertex3d& rhv) const
{
	// TODO: Add your specialized code here.
	double ddd = Length() * rhv.Length();
	if(fabs(ddd) < MathEx::TOL)
		return 1; // 0��������������ƽ�У���нǿ�����Ϊ��0�㣬cosֵΪ1
	return fabs(((*this) * rhv)) / ddd;
}	
 double Vertex3d::GetProjectLengthInVector(Vertex3d& vVec) const
{
	// ��vVec�ϵ�ͶӰ����
	if(vVec == Vertex3d(0,0,0))
		return 0; 
	return ((*this) *vVec) / vVec.Length();
}
 double Vertex3d::GetProjectHeightInVector(Vertex3d& vVec) const
{
	double dHeightEx = 0.0;
	if(vVec == Vertex3d(0,0,0))
		dHeightEx = LenghtEx();
	else
	{
		double crossResult = (*this) * vVec;
		dHeightEx = LenghtEx() - crossResult * crossResult / vVec.LenghtEx();
	}
	return sqrt(dHeightEx);
}

double Vertex3d::DVertexToVertex2d(const Vertex3d& rhv) const
{
	return ((*this) - rhv).Length2d();
}
 double Vertex3d:: DVertexToVertex3d(const Vertex3d& rhv) const
{
	return ((*this) - rhv).Length();
}

  const Vertex3d operator+(const Vertex3d& lhv, const Vertex3d& rhv)
 {
	 Vertex3d vRes = lhv;
	 vRes += rhv;
	 return vRes;
 }

  const Vertex3d operator-(const Vertex3d& lhv, const Vertex3d& rhv)
 {
	 Vertex3d vRes = lhv;
	 vRes -= rhv;
	 return vRes;
 }

  const Vertex3d operator^(const Vertex3d& lhv, const Vertex3d& rhv)
 {
	 Vertex3d vRes = lhv;
	 vRes ^= rhv;
	 return vRes;
 }

  const Vertex3d operator*(const Vertex3d& lhv, double rhd)
 {
	 Vertex3d vRes = lhv;
	 vRes *= rhd;
	 return vRes;
 }

  const Vertex3d operator*(double lhd, const Vertex3d& rhv)
 {
	 Vertex3d vRes = rhv;
	 vRes *= lhd;
	 return vRes;
 }

  double operator*(const Vertex3d& lhv, const Vertex3d& rhv)
 {
	 // ���Vertex3d�����ݳ�Աxyz�����˽�еģ���ô��Ҫ�����������������Ϊfriend����ʹ������������������������Ϊfriend����Ϊ���õĶ�������ڲ�ʵ��
	 return lhv.x * rhv.x + lhv.y * rhv.y + lhv.z * rhv.z;
 }

  const Vertex3d operator/(const Vertex3d& lhv, double rhd)
 {
	 Vertex3d vRes = lhv;
	 vRes /= rhd;
	 return vRes;
 }

  const Vertex3d GetNormal(const Vertex3d& pt1,const Vertex3d& pt2,const Vertex3d& pt3)
  {
	  double w0,w1,w2,v0,v1,v2,nr,nx,ny,nz;
	  w0=pt1.x-pt2.x;
	  w1=pt1.y-pt2.y;
	  w2=pt1.z-pt2.z;
	  v0=pt3.x-pt2.x;
	  v1=pt3.y-pt2.y;
	  v2=pt3.z-pt2.z;
	  nx=(w1*v2-w2*v1);
	  ny=(w2*v0-w0*v2);
	  nz=(w0*v1-w1*v0);
	  nr=(double)sqrt(nx*nx+ny*ny+nz*nz);
	  if(nr)
	  {
		  return Vertex3d(-nx/nr,-ny/nr, -nz/nr);
	  }
	  else
	  {
		  return Vertex3d(0, 0, 1);
	  }
  }



