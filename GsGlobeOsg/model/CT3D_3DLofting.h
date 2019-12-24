//********************************************************************************** 
//** �ļ����ƣ�CT3D_3DLofting.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά����������Ķ���
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-15
//********************************************************************************** 
#pragma once
#include "CT3D_3DLineString.h"
#include "ModelDef.h"

typedef struct _tagRoundTube
{
    double dDiameter;//ֱ��
}RoundTube;//Բ��


typedef struct _tagSquareTube
{
    double dSectionLength;//����泤��
    double dSectionWidth;//�������
}SquareTube;//����


typedef struct _tagSpecialTube
{
    unsigned int uGeometrySize;//����漸�ζ����С
    CGeometry* pGeometry;//����漸�ζ���
}SpecialTube;//������״��
typedef struct _tagSectionData
{
    union
    {
        RoundTube RTube;
        SquareTube SqTube;
        SpecialTube SpTube; 
    
    }data;
}SectionData;

class /*DLL_EXPORT*/ C3DLofting :
    public C3DLineString
{
protected:
    UID64 m_MatID;//����ID
   //�������� 
    //0: Բ��
    //1:����
    //2:������״��
    byte m_SectionType;

    //��������
    SectionData m_SectionData;

public:
	//********************************************************************************** 
	//** �������ƣ� C3DLofting
	//** ���������� ���캯��
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
    C3DLofting(void);
public:
	//********************************************************************************** 
	//** �������ƣ� ~C3DLofting
	//** ���������� ��������
	//** ��    �룺 ��           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
    virtual ~C3DLofting(void);
   
	//********************************************************************************** 
	//** �������ƣ� readBuffer
	//** ���������� �ӻ������н�����ǰ���󣬲�����Ա������ֵ
	//** ��    �룺 buf	������Buffer���������           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
    bool readBuffer( Buffer & buf);

	//********************************************************************************** 
	//** �������ƣ� writeBuffer
	//** ���������� �ѵ�ǰ����ĳ�Ա�������ݣ������һ��������
	//** ��    �룺 buf	������Buffer���������           
	//** ��    ���� ��
	//** ����ֵ��	��
	//** ��    �ߣ� ����
	//** �������ڣ� 2012-04-16
	//**********************************************************************************
    void writeBuffer(Buffer& buf);

	void setMatID(UID64 uMatID);
	UID64 getMatID();

	void setSectionType(byte bySectionType);
	byte getSectionType();

	void setSectionData(SectionData sData);
	SectionData getSectionData();

	virtual size_t sizeBuffer();
};
