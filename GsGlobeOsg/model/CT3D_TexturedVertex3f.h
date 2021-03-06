//********************************************************************************** 
//** 文件名称：CT3D_TexturedVertex3f.h
//** CopyRight (c) 2000-2012 武大吉奥信息技术有限公司开发一部
//** 文件描述： 三维顶点(仅作纹理映射的顶点)类的定义
//** 创 建 人： 杨灵
//** 创建日期： 2012-04-13
//********************************************************************************** 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#ifndef _CT3D_TEXTUREDVERT3F_H_
#define _CT3D_TEXTUREDVERT3F_H_
#include "CT3D_Vertex3f.h"

class /*DLL_EXPORT*/ TexturedVertex3f : public Vertex3f
{
	/** @defgroup TexturedVertex3f TexturedVertex3f-仅作纹理映射的顶点  
    *  @{
    */

public:

	/** 纹理坐标 */
	float tu; 
    float tv;

	/** @} */ // 属性结尾
public:


	//********************************************************************************** 
	//** 函数名称： TexturedVertex3f
	//** 功能描述： 构造函数1
	//** 输    入： 无           
	//** 输    出： 无
	//** 返回值：	无
	//** 作    者： 杨灵
	//** 创建日期： 2012-04-16
	//**********************************************************************************
	TexturedVertex3f(float dx=0.0,float dy=0.0,float dz=0.0,float du=0.0,float dv=0.0);
	
	
	//********************************************************************************** 
	//** 函数名称： TexturedVertex3f
	//** 功能描述： 构造函数2
	//** 输    入： 无           
	//** 输    出： 无
	//** 返回值：	无
	//** 作    者： 杨灵
	//** 创建日期： 2012-04-16
	//**********************************************************************************
	TexturedVertex3f(Vertex3f& vVertex,float fu=0.0,float fv=0.0);
	
    //********************************************************************************** 
    //** 函数名称： sizeBuffer
    //** 功能描述：计算三维点结构的大小
    //** 输    入： 无           
    //** 输    出： 无
    //** 返回值：	点结构大小
    //** 作    者： 杨灵
    //** 创建日期： 2012-04-26
    //**********************************************************************************
    static size_t sizeBuffer(); 
};

#endif 
