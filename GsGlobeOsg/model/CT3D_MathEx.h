//********************************************************************************** 
//** �ļ����ƣ�CT3D_MathEx.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά��ѧ�ඨ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-13
//********************************************************************************** 

#ifndef _CT3D_MATH_H_
#define _CT3D_MATH_H_

//#pragma once
#include <math.h>
#include <functional>
#include <algorithm>
#include <iterator>
//#include "ModelDef.h"


//#ifdef /*DLL_EXPORT*/_EXPORTS
//#define /*DLL_EXPORT*/ __declspec(dllexport)
//#else
//#define /*DLL_EXPORT*/ __declspec(dllimport)
//#endif


class  MathEx
{
	/** @defgroup MathEx MathEx-��ѧ�� 
    *  @{
    */

public:

	
	/** @name ���ԣ���Ա������
	* @{
	*/
	
	/** ��Ա���� */	
	static const double  TOL ;
	static const double	 TOL_F;
	static const double  ONE_PI;
	static const double  TWO_PI ;
	static const double  HALF_PI ;
	static const double  dDegToRad;
	static const double  dRadToDeg;
	static const double  dDoubleMax;
	static const double  dDoubleMin;

	/** @} */ // ���Խ�β

	/** @defgroup MathEx ��������Ա������
	* @{
	*/

	/** @name ��������������
	*  @{
	*/
protected:
	/** ���캯��
	*/
	MathEx(void);
	/** ��������
	*/
	~MathEx(void);
	/** @} */ // ����������������β
	
	/** @name �������
	*  @{
	*/
public:

    /** �жϷ���
	* @param [in] iValue ������ֵ	
	* @return ����
    */
	static inline int ISign (int iValue){return ( iValue > 0 ? +1 : ( iValue < 0 ? -1 : 0 ) );}
	/** �жϷ���
	* @param [in] dValue ������ֵ	
	* @return ����
	* -1 ��ʾΪ��
	* --1 ��ʾΪ��
	* -0 ��ʾΪ0
    */
	static double Sign(double dValue);
	/** ���㷴����ֵ
	* @param [in] fValue ��������	
	* @return �Ƕ�
    */
	static double ACos (double fValue);	

	/** ���㷴����ֵ
	* @param [in] fValue ��������	
	* @return �Ƕ�
    */
	static double ASin (double fValue);

	/** ���㷴����ֵ
	* @param [in] dValue ��������	
	* @return �Ƕ�
    */
	static inline double ATan (double fValue) { return (atan(fValue)); }
	
	/** �������Һ���
	* @param [in] dValue ����	
	* @return ����ֵ
    */
	static inline double ATan2 (double fY, double fX) { return (atan2(fY,fX)); }

	/** �������Һ���
	* @param [in] dValue ����	
	* @return ����ֵ
    */
	static  double RadianToDegree(double angle);

	/** �������Һ���
	* @param [in] dValue ����	
	* @return ����ֵ
    */
	static double DegreeToRadian(double angle);

	/** ʹ�ñ�׼ģ��⣨STL���ķ���ʽ����������Դ��wikipedia
	* @param BidirectionalIterator:	�б�ĵ���������
	* @param Compare:��������ıȽϺ���
	* @return 
	*/
	template< typename BidirectionalIterator, typename Compare >
	static void quick_sortEx( BidirectionalIterator first, BidirectionalIterator last, Compare cmp ) {
		if( first != last ) {
			BidirectionalIterator left  = first;
			BidirectionalIterator right = last;
			BidirectionalIterator pivot = left++;

			while( left != right ) {
				if( cmp( *left, *pivot ) ) {
					++left;
				} else {
					while( (left != right) && cmp( *pivot, *right ) )
						right--;
					std::iter_swap( left, right );
				}
			}

			if(cmp( *pivot, *left ))
				--left;
			std::iter_swap( first, left );

			quick_sortEx( first, left, cmp );
			quick_sortEx( right, last, cmp );
		}
	}
	/** ʹ�ñ�׼ģ��⣨STL���ķ���ʽ����������Դ��wikipedia
	* @param BidirectionalIterator:	�б�ĵ�����
	* @return 
	*/
	template< typename BidirectionalIterator >
	static void quick_sort( BidirectionalIterator first, BidirectionalIterator last ) {
		quick_sortEx( first, last,
			std::less_equal< typename std::iterator_traits< BidirectionalIterator >::value_type >()
			);
	}
	/** @} */ // ����������β

	/** @} */ // ������β

	/** @} */ // ģ���β
	
};


#endif//_CT3D_MATH_H_
