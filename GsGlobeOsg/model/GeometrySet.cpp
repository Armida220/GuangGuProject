//********************************************************************************** 
//** �ļ����ƣ�GeometrySet.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ���μ���ʵ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-11
//********************************************************************************** 
#include "GeometrySet.h"

GeometrySet::GeometrySet(void)
{
}

GeometrySet::~GeometrySet(void)
{
}
//********************************************************************************** 
//** �������ƣ� readBuff
//** ���������� �ӻ������ж�����
//** ��    �룺 buffer:Buffer���������           
//** ��    ���� ��
//** ����ֵ�����ζ����б�����
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
GeometryList& GeometrySet::readBuffer(Buffer &buffer)
{
    GeometryItem item;

    for(UINT i=0;i< m_uGeometryNum;i++)
    {
        //��ȡ����ID
        buffer.read((char*)&item.uID,sizeof(UINT64));
        
        //��ȡ��������
        buffer.read((char*)&item.byType,sizeof(byte));
       
        //��ȡ�������ݳ���
        buffer.read((char*)&item.uDataLen,sizeof(UINT));
        
        //���ݼ������ʹ�����Ӧ�ļ�����
        item.pGeometry = CGeometry::CreateGeometry(item.byType);
        
        //����Ӧ�Ļ�������ȡ����
        item.pGeometry->readBuffer(buffer);
        
        //��ȡ����ʱ��
        buffer.read((char*)&item.uFeatureCreateTime,sizeof(UINT64));
        //��ȡ����ʱ��
        buffer.read((char*)&item.uFeatureUpdateTime,sizeof(UINT64));
        m_GeometryList.push_back(item);
    }
     return m_GeometryList;
}


//********************************************************************************** 
//** �������ƣ� writeBuff
//** ���������� ������д��������
//** ��    �룺 buffer:Buffer���������          
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
void GeometrySet::writeBuffer(Buffer &buffer)
{
    for(UINT i=0;i< m_uGeometryNum;i++)
    {
        //д�뼸��ID
        buffer.write((char*)&m_GeometryList[i].uID,sizeof(UINT64));
        //д�뼸������
        buffer.write((char*)&m_GeometryList[i].byType,sizeof(byte));

        //д�뼸�����ݳ���
        buffer.write((char*)&m_GeometryList[i].uDataLen,sizeof(UINT));

        //����Ӧ�Ļ�����д������
        m_GeometryList[i].pGeometry->writeBuffer(buffer);

        //д�봴��ʱ��
        buffer.write((char*)&m_GeometryList[i].uFeatureCreateTime,sizeof(UINT64));

        //д�����ʱ��
        buffer.write((char*)&m_GeometryList[i].uFeatureUpdateTime,sizeof(UINT64));
    }
}
//**********************************************************************************
//** �������ƣ� setMaterialNum
//** ���������� ���ü�����ĸ���
//** ��    �룺 �ļ��ж�ȡҪ�صĸ���          
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
void  GeometrySet::setGeometryNum(UINT uMaterialNum)
{
    m_uGeometryNum = uMaterialNum;
}


//********************************************************************************** 
//** �������ƣ� getMaterialNum
//** ���������� �õ�������ĸ���
//** ��    �룺 ��          
//** ��    ���� ��
//** ����ֵ��Ҫ�صĸ���
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
UINT GeometrySet::getGeometryNum() const
{
	return m_uGeometryNum;
}

void GeometrySet::setGeometryList(GeometryList &v)
{
	m_GeometryList=v;
}
GeometryList& GeometrySet::getGeometryList()
{
	return m_GeometryList;
}
