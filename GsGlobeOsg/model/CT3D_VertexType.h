//********************************************************************************** 
//** �ļ����ƣ�CT3D_VertexType.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ���ζ��㶨��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-7
//********************************************************************************** 
#ifndef _VERTEXTYPE_H_
#define _VERTEXTYPE_H_

//********************************************************************************** 
//**��Ƿ����壺	V-����ά����㣩
//**T�������꣨0�������
//**N-���ߣ�0.0��1.0��
//**C-��ɫ��0.0��1.0��
//**********************************************************************************
enum
{
    VERTEXTYPE_V3f ,				// for Vertex3f
    VERTEXTYPE_V3d,				// for Vertex3d

    VERTEXTYPE_V3fT2f,			// for TexturedVertex3f
    VERTEXTYPE_V3dT2d,			// for TexturedVertex3d

    VERTEXTYPE_V3fN3fC3f,		// for ShadedVertex3f
    VERTEXTYPE_V3dN3dC3f,		// for ShadedVertex3d

    VERTEXTYPE_V3fT2fN3fC3f,	// for VersatileVertex3f
    VERTEXTYPE_V3dT2dN3dC3f,	// for VersatileVertex3d
};


struct Vertex3f
{
    /** X����ֵ */
    float x;

    /** Y����ֵ */
    float y;

    /** Z����ֵ */
    float z;
};

struct Vertex3d
{
    /** X����ֵ */
    double x;

    /** Y����ֵ */
    double y;

    /** Z����ֵ */
    double z;
};

struct TexturedVertex3f
{
    /** X����ֵ */
    float x;

    /** Y����ֵ */
    float y;

    /** Z����ֵ */
    float z;
   
    /** �������� */
    float tu;
 
    /** �������� */
    float tv;
};


struct TexturedVertex3d
{
    /** X����ֵ */
    double x;

    /** Y����ֵ */
    double y;

    /** Z����ֵ */
    double z;

    /** �������� */
    double tu;

    /** �������� */
    double tv;
};

struct ShadedVertex3f
{
    /** X����ֵ */
    float x;

    /** Y����ֵ */
    float y;

    /** Z����ֵ */
    float z;

    /** X�ᷨ�� */
    float nx;
    
    /** Y�ᷨ�� */
    float ny;

    /** Z�ᷨ�� */
    float nz;
 
    /** ��ɫr,g,b���� */
    float r;
    float g;
    float b;
};

struct ShadedVertex3d
{
    /** X����ֵ */
    double x;

    /** Y����ֵ */
    double y;

    /** Z����ֵ */
    double z;

    /** X�ᷨ�� */
    double nx;

    /** Y�ᷨ�� */
    double ny;

    /** Z�ᷨ�� */
    double nz;
    
    /** ��ɫr,g,b���� */
    float r;
    float g;
    float b;
};

struct VersatileVertex3f
{/** X����ֵ */
    float x;

    /** Y����ֵ */
    float y;

    /** Z����ֵ */
    float z;

    /** �������� */
    float tu;

    /** �������� */
    float tv;

    /** X�ᷨ�� */
    float nx;

    /** Y�ᷨ�� */
    float ny;

    /** Z�ᷨ�� */
    float nz;

    /** ��ɫr,g,b���� */
    float r;
    float g;
    float b;
};

struct VersatileVertex3d
{/** X����ֵ */
    double x;

    /** Y����ֵ */
    double y;

    /** Z����ֵ */
    double z;

    /** �������� */
    double tu;

    /** �������� */
    double tv;

    /** X�ᷨ�� */
    double nx;

    /** Y�ᷨ�� */
    double ny;

    /** Z�ᷨ�� */
    double nz;

    /** ��ɫr,g,b���� */
    float r;
    float g;
    float b;
};
#endif