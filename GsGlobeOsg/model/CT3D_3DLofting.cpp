#include "CT3D_3DLofting.h"

//********************************************************************************** 
//** �������ƣ� C3DLofting
//** ���������� ���캯��
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
C3DLofting::C3DLofting(void)
{

}

//********************************************************************************** 
//** �������ƣ� ~C3DLofting
//** ���������� ��������
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
C3DLofting::~C3DLofting(void)
{
}

//********************************************************************************** 
//** �������ƣ� readBuffer
//** ���������� �ӻ������н�����ǰ���󣬲�����Ա������ֵ
//** ��    �룺 buf	������Buffer���������           
//** ��    ���� ��
//** ����ֵ��	�ɹ�Ϊtrue��ʧ��Ϊfalse
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
bool C3DLofting::readBuffer( Buffer & buf)
{
    bool bRet = C3DLineString::readBuffer(buf);
	//modify by yangling 20131208 begin
	if(!bRet)
	{
		return false;
	}
	//modify by yangling 20131208 end
    buf.read((char*)&m_MatID,sizeof(UID64));
    buf.read((char*)&m_SectionType,sizeof(byte));
    if( 0 ==m_SectionType )
    {
         buf.read((char*)&(m_SectionData.data.RTube.dDiameter),sizeof(double));
    }
    else if( 1 == m_SectionType )
    {
        buf.read((char*)&m_SectionData.data.SqTube.dSectionLength,sizeof(double));
        buf.read((char*)&m_SectionData.data.SqTube.dSectionWidth,sizeof(double));

    }
    else if (2 == m_SectionType)
    {
        //��ȡ�����С
        buf.read((char*)&m_SectionData.data.SpTube.uGeometrySize,sizeof(unsigned int));
        byte byGeometryType = 1;
        //��������ID
        char* p = (char*)buf.data() + buf.getPos()+sizeof(UID64);
        //��ȡ��������
        memcpy((char*)&byGeometryType,p,sizeof(byte));
        //��������       
        m_SectionData.data.SpTube.pGeometry  = Geometry::CreateGeometry(byGeometryType);
        //���ö���Ķ�����
        if(m_SectionData.data.SpTube.pGeometry != NULL)
        {
            m_SectionData.data.SpTube.pGeometry->readBuffer(buf);
        }
        p = NULL;
    }
	else
	{
		return false;
	}
	return true;
}

//********************************************************************************** 
//** �������ƣ� writeBuffer
//** ���������� �ѵ�ǰ����ĳ�Ա�������ݣ������һ��������
//** ��    �룺 buf	������Buffer���������           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
void C3DLofting::writeBuffer(Buffer& buf)
{
    C3DLineString::writeBuffer(buf);
    buf.write((char*)&m_MatID,sizeof(UID64));
    buf.write((char*)&m_SectionType,sizeof(byte));
    if( 0 ==m_SectionType )
    {
        buf.write((char*)&m_SectionData.data.RTube.dDiameter,sizeof(double));
    }
    else if( 1 == m_SectionType )
    {
        buf.write((char*)&m_SectionData.data.SqTube.dSectionLength,sizeof(double));
        buf.write((char*)&m_SectionData.data.SqTube.dSectionWidth,sizeof(double));

    }
    else if (2 == m_SectionType)
    {
        //�洢�����С
        buf.write((char*)&m_SectionData.data.SpTube.uGeometrySize,sizeof(unsigned int));
        //���ö����д����
        if(m_SectionData.data.SpTube.pGeometry != NULL)
        {
            m_SectionData.data.SpTube.pGeometry->writeBuffer(buf);
        }
    }
    else
    {

    }
}

void C3DLofting::setMatID(UID64 uMatID)
{
	m_MatID=uMatID;
}
UID64 C3DLofting::getMatID()
{
	return m_MatID;
}

void C3DLofting::setSectionType(byte bySectionType)
{
	m_SectionType=bySectionType;
}
byte C3DLofting::getSectionType()
{
	return m_SectionType;
}

void C3DLofting::setSectionData(SectionData sData)
{
	if(0==m_SectionType)
	{
		m_SectionData.data.RTube.dDiameter=sData.data.RTube.dDiameter;
	}
	if (1==m_SectionType)
	{
		m_SectionData.data.SqTube.dSectionLength=sData.data.SqTube.dSectionLength;
		m_SectionData.data.SqTube.dSectionWidth=sData.data.SqTube.dSectionWidth;
	}
	if(2==m_SectionType)
	{
		m_SectionData.data.SpTube.uGeometrySize=sData.data.SpTube.uGeometrySize;
		m_SectionData.data.SpTube.pGeometry=sData.data.SpTube.pGeometry;
	}
	
}
SectionData C3DLofting::getSectionData()
{
	
		return m_SectionData;
	
}

size_t C3DLofting::sizeBuffer()
{
	size_t nSize = 0;
	nSize += C3DLineString::sizeBuffer();
	nSize += sizeof(UINT64);//���ʶ���ID
	nSize += sizeof(byte);//��������

	if (0==getSectionType())
	{
		nSize += sizeof(double);//��ֱ��
	}
	if (1==getSectionType())
	{
		nSize += sizeof(double);//����泤��
		nSize += sizeof(double);//�������
		
	}
	if (2==getSectionType())
	{
		nSize += sizeof(UINT);//����漸�ζ����С
		nSize += getSectionData().data.SpTube.pGeometry->sizeBuffer();
	}
	return nSize;
}
