//********************************************************************************** 
//** �ļ����ƣ�SharedModel.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ����ģ������ʵ��
//** �� �� �ˣ� �
//** �������ڣ� 2012-04-11
//********************************************************************************** 

#include "SharedModel.h"


//********************************************************************************** 
//** �������ƣ� CSharedModel
//** ���������� ���캯��
//** ��    �룺 ��          
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
CSharedModel::CSharedModel(void)
{
	m_nModelObjectID=0;
	m_nSDMLen=-1;
    m_pGeometry = NULL;
}

//********************************************************************************** 
//** �������ƣ� ~CSharedModel
//** ���������� ��������
//** ��    �룺 ��          
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
CSharedModel::~CSharedModel(void)
{
    if(NULL!=m_pGeometry)
	{
		delete m_pGeometry;
	}
}

//********************************************************************************** 
//** �������ƣ� CFeatureClass
//** ���������� �������캯��
//** ��    �룺 sharedmodel������        
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
CSharedModel::CSharedModel(const CSharedModel& sharedmodel)
{
	copy(sharedmodel);
}

//********************************************************************************** 
//** �������ƣ� read
//** ���������� ��ȡ�ļ�����
//** ��    �룺 ������f������           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************

//********************************************************************************** 
//** �������ƣ� copy
//** ���������� ���������Ҫ�ض���ĸ�������
//** ��    �룺 sharedmodel:����ģ�Ͷ��������          
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
void CSharedModel::copy(const CSharedModel& sharedmodel)
{
	m_nModelObjectID=sharedmodel.m_nModelObjectID;
	m_nSDMLen=sharedmodel.m_nSDMLen;
	m_pGeometry = sharedmodel.m_pGeometry;
}

//********************************************************************************** 
//** �������ƣ� readBuffer
//** ���������� �ӻ������ж�����
//** ��    �룺 buffer:Buffer���������           
//** ��    ���� ��
//** ����ֵ���ɹ�Ϊtrue��ʧ��Ϊfalse
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
bool CSharedModel::readBuffer(Buffer &buffer)
{

	//��ȡģ�Ͷ���ID
	buffer.read((void*)&m_nModelObjectID,sizeof(UINT64));
	//��ȡ����ģ�����ݳ���
	buffer.read((void*)&m_nSDMLen,sizeof(int));
	//��ȡ����ģ�Ͷ��������
	buffer.setPos(buffer.getPos() +sizeof(UINT64)/*+sizeof(UINT64)+sizeof(int)*/);

	byte nType=0;
	buffer.read((void*)&nType,sizeof(byte));
	buffer.setPos(buffer.getPos() - 9);
	if (nType!=255)
	{
		
		m_pGeometry=CGeometry::CreateGeometry(nType);
		
		//buffer.setPos(buffer.getPos() + sizeof(UINT64)+sizeof(int));


		m_pGeometry->readBuffer(buffer);
	}
	else
	{
		return false;
	}
	return true;
}

//********************************************************************************** 
//** �������ƣ� writeBuffer
//** ���������� ������д��������
//** ��    �룺 buffer:Buffer���������          
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
void CSharedModel::writeBuffer(Buffer &buffer)
{
	//д��ģ�Ͷ���ID
	buffer.write((void*)&m_nModelObjectID,sizeof(UINT64));
	//д�빲��ģ�����ݳ���
	buffer.write((void*)&m_nSDMLen,sizeof(int));
	//д�빲��ģ�Ͷ��������
	int nType=m_pGeometry->getTypeID();
	
	if (nType!=255)
	{
		m_pGeometry->writeBuffer(buffer);
	}
}
void CSharedModel::setModelObjectID(UINT64 nModelObjectID)
{
	m_nModelObjectID=nModelObjectID;
}
UINT64 CSharedModel::getModelObjectID()
{
	return m_nModelObjectID;
}


void CSharedModel::setSDMLen(int nLen)
{
	m_nSDMLen=nLen;
}
int CSharedModel::getSDMLen()
{
	return m_nSDMLen;
}

void CSharedModel::setObjectData(CGeometry* pGeometry)
{
	m_pGeometry=pGeometry;
}
CGeometry* CSharedModel::getObjectData()
{
	return m_pGeometry;
}
//********************************************************************************** 
//** �������ƣ� sizeBuffer
//** ���������� �õ�����ģ�ʹ�С
//** ��    �룺 ��          
//** ��    ���� ��
//** ����ֵ������ģ�ʹ�С
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
size_t CSharedModel::sizeBuffer()
{
    size_t sSDMSize = 0;
    if(m_pGeometry != NULL)
    {
        sSDMSize = sizeof(UINT64) + sizeof(int) + m_pGeometry->sizeBuffer();
    }
    else
    {
        sSDMSize = sizeof(UINT64) + sizeof(int);
    }
    return sSDMSize;

}


void CSharedModel::readlodBuffer(Buffer &buffer)
{
	//��ȡlodInfo�ĸ���
	byte nLodCount = 0;
	buffer.read((char *)&nLodCount,sizeof(byte));
	for(byte nLodIndex = 0;nLodIndex<nLodCount;nLodIndex++)
	{
		LodInfo lodData;
		lodData.readBuffer(buffer);
		m_vecLodInfo.push_back(lodData);
	} 	
}

void CSharedModel::writeLodBuffer(Buffer &buffer)
{

	//д��lodInfo�ĸ���
	byte nLodCount = m_vecLodInfo.size();
	buffer.write((char *)&nLodCount,sizeof(byte));
	for(byte nLodIndex = 0;nLodIndex<nLodCount;nLodIndex++)
	{
		LodInfo lodData;
		m_vecLodInfo[nLodIndex].writeBuffer(buffer);
	} 
}

size_t CSharedModel::sizeLodBuffer()
{
	size_t nSLodSize = 0;
	nSLodSize += sizeof(byte);
	for(byte nLodIndex = 0;nLodIndex < m_vecLodInfo.size();nLodIndex ++)
	{
		nSLodSize += m_vecLodInfo[nLodIndex].sizeBuffer();
	}
	return nSLodSize;
}

byte CSharedModel::GetLodCount()
{
	return m_vecLodInfo.size();
}

void CSharedModel::ReleaseLodMTData()
{
	for (byte nLodIndex = 0;nLodIndex<m_vecLodInfo.size();nLodIndex++)
	{
		int nMTCount =m_vecLodInfo[nLodIndex].vecMTData.size();
		for(int nMTIndex = 0;nMTIndex<nMTCount;nMTIndex++)
		{
			MTData tempData =  m_vecLodInfo[nLodIndex].vecMTData[nMTIndex];
			if (tempData.pMTData)
			{
				delete []tempData.pMTData;
				tempData.pMTData = 0;
			}
		}
	}
}
