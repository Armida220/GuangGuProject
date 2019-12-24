//********************************************************************************** 
//** �ļ����ƣ�CT3D_AABBox.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��Χ����Ķ���
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-14
//********************************************************************************** 
#include "ModelDef.h"
#include "CT3D_Vertex3d.h"
#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _CT3D_AABBOX_H_
#define _CT3D_AABBOX_H_

#include <vector>
using namespace std;

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))




class /*DLL_EXPORT*/ AABBox 
{
	/** @defgroup AABBox AABBox-�����Χ��  
    *  @{
    */

protected:

	/** @name ���ԣ���Ա������
	* @{
	*/
	/** ��С�� */
	Vertex3d m_VMin;

	/** ���� */
	Vertex3d m_VMax;

	

	/** @} */ // ���Խ�β

public:

	int m_nRecPlaneIndex;

	/** @defgroup AABBox ��������Ա������
	* @{
	*/
	
	
	/** @name ��������������
	*  @{
	*/

	/** ���캯��1
	*/
	AABBox();
	
	
	/** ���캯��2
	*/
	AABBox(const Vertex3d& vmin,const Vertex3d& vmax);
	
	
	/** ���캯��3
	*/
	AABBox(double minx,double miny,double minz,double maxx,double maxy,double maxz);
	
	
	/** ���캯��4
	*/
	AABBox(const AABBox& box);
	
	
	/** @} */ // ����������������β
	
	
	
	/** @name ���ݲ���
	*  @{
	*/

	/** ���AABB����С����λ��(X,Y,Z��С��
	* @return AABB����С����λ��
    */
	Vertex3d GetMin() const;
	

	/** ���AABB����󶥵�λ��(X,Y,Z���
	* @return AABB����󶥵�λ��
    */
	Vertex3d GetMax() const;
	
	
	/** �õ�AABB�����������
	* @param [in] vCorners AABB�������� 
    */
	void GetVertices(std::vector<Vertex3d>& vCorners) const;
	
	/** ����AABB����С����λ��(X,Y,Z��С��
	* @param [in] maxV AABB����󶥵�λ��
    */
	void SetMax(const Vertex3d& maxV);
	
	/** ����AABB����С����λ��(X,Y,Z��С��
	* @param [in] minV AABB����С����λ��
    */
	void SetMin(const Vertex3d& minV);
	
	
	/** @} */ // ���ݲ������β
	
	
	
	/** @name �������
	*  @{
	*/

	/** ����AABB�ĳ���
	* @return AABB�ĳ���
    */
	double Length() const;
	
	/** ����AABB�Ŀ��
	* @return AABB�Ŀ��
    */
	double Width() const;

	/** ����AABB�ĸ߶�
	* @return AABB�ĸ߶�
    */
	double Height() const;

	/** ����AABB�Խ��ߵĳ���
	* @return AABB�Խ��ߵĳ���
    */
	double Diagonal() const
	{
		return m_VMin.DVertexToVertex3d(m_VMax);
	}
	/** ����AABB��x����ĳ���
	* @return AABB��x����ĳ���
    */
	double XSize() const
	{
		return m_VMax.x - m_VMin.x;
	}

	/** ����AABB��y����ĳ���
	* @return AABB��y����ĳ���
    */
	double YSize() const
	{
		return m_VMax.y - m_VMin.y;
	}

	/** ����AABB��z����ĳ���
	* @return AABB��z����ĳ���
    */
	double ZSize() const
	{
		return m_VMax.z - m_VMin.z;
	}

	double MaxX() const;
	double MinX() const;
	double MaxY() const;
	double MinY() const;
	double MaxZ() const;
	double MinZ() const;

	/** ����AABB�����
	* @return AABB�����
    */
	double Volume() const;
	

	/** ����AABB�����ĵ�λ��
	* @return AABB�����ĵ�λ��
    */
	Vertex3d CenterPoint() const;
	

	/** ȡ��AABB�İ˸�����֮һ
	* @param [in] iIndex
	*  - 0	Xmin,Ymin,Zmin
	*  - 1	Xmax,Ymin,Zmin
    *  - 2	Xmin,Ymax,Zmin
    *  - 3  Xmax,Ymax,Zmin
	*  - 4	Xmin,Ymin,Zmax
	*  - 5	Xmax,Ymin,Zmax
    *  - 6	Xmin,Ymax,Zmax
    *  - 7  Xmax,Ymax,Zmax
	* @return AABB�İ˸�����֮һ
    */
	Vertex3d FetchCornerPoint(int iIndex) const;

	/** �����봫��������AABB�ϵĵ�
	* @param [in] vVer �����
	* @return �봫��������AABB�ĵ�
    */
	Vertex3d GetClosestVertexToAnotherPt(Vertex3d& vVer) const;


	/** ���㴫�������ε�AABB����С����
	* @param [in] begVer,endVer�����߶ζ˵�
	* @return �봫��������AABB�ĵ�
	*/
	double GetClosestTriangleDisToAABBBox(Vertex3d& triPts1,Vertex3d& triPts2,Vertex3d& triPts3) const;

	/** �Ե�ǰAABB��������ȷ����������㣬������AABB�ڣ�����Ҫ����
	* @param [in] pnt �����
	* @return ���ź��AABB
    */
	AABBox Union(const Vertex3d& pnt);
	
	/** �Ե�ǰAABB��������ȷ����������㼯�����㼯��AABB�ڣ�����Ҫ����
	* @param [in] pnts ����㼯
	* @param [in] nPntNum �����ĸ���
	* @return ���ź��AABB
    */
	AABBox Union(const Vertex3d* pnts, int nPntNum);
	AABBox Union(const std::vector<Vertex3d>& pnts);

	/** �Ե�ǰAABB��������ȷ������������һ��AABBox��������AABB�ڣ�����Ҫ����
	* @param [in] otherEnvlp �����AABBox
	* @return ���ź��AABB
    */
	AABBox Union(const AABBox& otherEnvlp);

	/** ���ֵ�ǰAABB�����ĵ㲻�䣬��ԭ�л����ϣ��ֱ���x��y��z�����᷽������һ������
	* @param [in] dx x��������
	* @param [in] dy y��������
	* @param [in] dz z��������
	* @return ���ź��AABB
    */
	AABBox Inflate(double dx, double dy, double dz)
	{
		return Inflate(Vertex3d(dx,dy,dz));
	}

	/** ���ֵ�ǰAABB�����ĵ㲻�䣬��ԭ�л����ϣ��ֱ���x��y��z�����᷽������һ������
	* @param [in] vVec x��y��z�����������ϣ�������ʾ��
	* @return ���ź��AABB
    */
	AABBox Inflate(const Vertex3d& vVec)
	{
		m_VMin -= vVec;
		m_VMax += vVec;
		Vertex3d vMin = m_VMin;
		Vertex3d vMax = m_VMax;
		m_VMin.x = min(vMin.x,vMax.x);
		m_VMin.y = min(vMin.y,vMax.y);
		m_VMin.z = min(vMin.z,vMax.z);

		m_VMax.x = max(vMin.x,vMax.x);
		m_VMax.y = max(vMin.y,vMax.y);
		m_VMax.z = max(vMin.z,vMax.z);

		return *this;
	}

	/** ���ֵ�ǰAABB�����ĵ㲻�䣬��ԭ�л����ϣ��ֱ���x��y��z�����᷽���Сһ������
	* @param [in] dx x��������
	* @param [in] dy y��������
	* @param [in] dz z��������
	* @return ��С���AABB
    */
	AABBox Deflate(double dx, double dy, double dz)
	{
		return Deflate(Vertex3d(dx,dy,dz));
	}
	
	/** ���ֵ�ǰAABB�����ĵ㲻�䣬��ԭ�л����ϣ��ֱ���x��y��z�����᷽���Сһ������
	* @param [in] vVec x��y��z�����������ϣ�������ʾ��
	* @return ��С���AABB
    */
	AABBox Deflate(const Vertex3d& vVec)
	{
		return Inflate(-vVec);
	}

	/** ����AABBΪ�գ�������С���λ����Ϊ������������λ����Ϊ�������
    */
	inline void Empty()
	{
		const double big_number = 1e37f;
		m_VMin.x = m_VMin.y = m_VMin.z = big_number;
		m_VMax.x = m_VMax.y = m_VMax.z = -big_number;
	}


	/** �жϵ�ǰAABB�Ƿ�Ϊ��
	* @return �Ƿ�Ϊ��
    */
	int IsEmpty() const
	{
	//	return ((m_VMin.x > m_VMax.x) || (m_VMin.y > m_VMax.y) || (m_VMin.z > m_VMax.z)); //xx_0128
		return ( ( ( m_VMin.x - m_VMax.x ) > MathEx::TOL ) ||
				 ( ( m_VMin.y - m_VMax.y ) > MathEx::TOL ) ||
				 ( ( m_VMin.z - m_VMax.z ) > MathEx::TOL ) );
	}

	/** �Ե�ǰAABBƽ��һ������
	* @param [in] vVec ƽ������
	* @return	ƽ�ƺ��AABB
    */
	AABBox Offset(const Vertex3d& vVec)
	{
		m_VMax += vVec;
		m_VMin += vVec;
		return *this;
	}

	/** ����ǰAABB�봫���AABB�����󽻣����õ��󽻺��AABB
	* @param [in] otherbox �����AABB	
	* @param [out] retBox �󽻺�õ���AABB	
	* @return	1 -- �ཻ��0 -- ���룻2 -- ������ 3 -- ��������  
    */
	int  Intersect(const AABBox& otherbox, AABBox& retBox) const;

	/** �ж�һ�����Ƿ��ڰ�Χ����
	* @param [in] vPt �����	
	* @return	1 -- �ڰ�Χ���ڣ�0 -- �ڰ�Χ���⣻  
    */
	int IsPointInBox(const Vertex3d& vPt) const;

	/** ��ǰAABBBOX �봫���AABBBOX �Ƿ��ཻ
	* @param [in] inBox �����������
	* @return	1 -- �ڰ�Χ���ڣ�0 -- �ڰ�Χ���⣻  
	*/
	int IsBoxIntersectWithGivenBox(const AABBox& inBox) const;

	/** ��ǰAABBBOX �봫���AABBBOX �ڸ��������ͶӰ�Ƿ��ཻ
	* @param [in] inBox		������������
	* @param [in] proAxis	����ͶӰ��,ȡֵ��x����y����z��
	* @return	1 -- ͶӰ�ཻ�����ٽӣ���������0 -- ͶӰ���ཻ��  
	*/
	int IsBoxIntersectWithGivenBox2D(const AABBox& inBox, char proAxis = 'z', AABBox* intersectBox = NULL) const;

	/** ���ز�����"=",���ڶԵ�ǰAABB�ĸ�ֵ
	* @param [in] rha �����AABB	
	* @return ��ֵ���AABB 
    */
	AABBox& operator=(const AABBox& rha)
	{
		m_VMax = rha.m_VMax;
		m_VMin = rha.m_VMin;
		return (*this);
	}

	/** ���ز�����"==",�жϴ���AABB�Ƿ��뵱ǰAABB���
	* @param [in] otherbox �����AABB	
	* @return 1 -- ��ȣ�0 -- ����
    */
	int operator==(const AABBox& otherbox) const
	{
		return m_VMax == otherbox.m_VMax && m_VMin == otherbox.m_VMin;
	}
	



	/** �жϵ�ǰAABB������������2D�ϵĹ�ϵ���������ཻ������
	* @param [in] ptArray ���������
	* @return 1 -- ͶӰ�ཻ�����ٽӣ���������0 -- ͶӰ���ཻ�� 
	*/
	int IsBoxintersectWithPolygon2D( vector<Vertex3d>& ptArray );

    static size_t sizeBuffer();

};

typedef AABBox Envelope3D;

#endif /* _INC_AABBOXENVELOPE3D_49E347290251_INCLUDED */
