//********************************************************************************** 
//** �ļ����ƣ�FeatureClass.h
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� Ҫ����ʵ��
//** �� �� �ˣ� �
//** �������ڣ� 2012-04-11
//********************************************************************************** 


#include "FeatureClass.h"
//********************************************************************************** 
//** �������ƣ� CFeatureClass
//** ���������� ���캯��
//** ��    �룺 ��          
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
CFeatureClass::CFeatureClass(void)
{
	m_nFCLid=0;
	m_nFCLNameLen=-1;
	m_strFCLName="";
	m_nStatus=-1;
	m_nProNameLen=-1;
	m_strProName="";

}

//********************************************************************************** 
//** �������ƣ� ~CFeatureClass
//** ���������� ��������
//** ��    �룺 ��          
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
CFeatureClass::~CFeatureClass(void)
{
}

//********************************************************************************** 
//** �������ƣ� CFeatureClass
//** ���������� �������캯��
//** ��    �룺 featureclass������        
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
CFeatureClass::CFeatureClass(CFeatureClass& featureclass)
{
	copy(featureclass);
}

//********************************************************************************** 
//** �������ƣ� copy
//** ���������� ���������Ҫ�ض���ĸ�������
//** ��    �룺 featureclass:Ҫ�ض��������          
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
void  CFeatureClass::copy(const CFeatureClass& featureclass)
{
	//���������Ҫ�صĸ�������
	m_nFCLid=featureclass.m_nFCLid;
	m_nFCLNameLen=featureclass.m_nFCLNameLen;
	m_strFCLName=featureclass.m_strFCLName;
	m_nStatus=featureclass.m_nStatus;
	m_nProNameLen=featureclass.m_nProNameLen;
	m_strProName=featureclass.m_strProName;
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
bool CFeatureClass::readBuffer(Buffer &buffer)
{
	/**��ȡҪ����ID*/
	buffer.read((void *)&m_nFCLid,sizeof(int64));
	/**��ȡҪ�������Ƴ���*/
	buffer.read((void*)&m_nFCLNameLen,sizeof(int));
	char ca[4096];
    memset(ca,0,4096);
	/**��ȡҪ��������*/
	buffer.read((void*)ca,m_nFCLNameLen);
	//modify by yangling 20131208 begin
	if(m_nFCLNameLen > 4096)
	{
		return false;
	}
	//modify by yangling 20131208 end
	m_strFCLName.assign(ca);
	/**��ȡҪ����״̬*/
	buffer.read((void*)&m_nStatus,sizeof(int));
	/**��ȡ���Ա�����Ƴ���*/
	buffer.read((void*)&m_nProNameLen,sizeof(int));
	//�ٴγ�ʼ����ʱ�ַ���
	memset(ca,0,4096);
	//modify by yangling 20131208 begin
	if(m_nProNameLen > 4096)
	{
		return false;
	}
	//modify by yangling 20131208 end
	/**��ȡ���Ա������*/
	buffer.read((void*)ca,m_nProNameLen);
	m_strProName.assign(ca);
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
void CFeatureClass::writeBuffer(Buffer &buffer)
{
	/**д��Ҫ����ID*/
	buffer.write((void *)&m_nFCLid,sizeof(int64));
	/**д��Ҫ�������Ƴ���*/
	buffer.write((void*)&m_nFCLNameLen,sizeof(int));
	
	/**д��Ҫ��������*/
	buffer.write((void*)m_strFCLName.c_str(),m_nFCLNameLen);
	
	/**д��Ҫ����״̬*/
	buffer.write((void*)&m_nStatus,sizeof(int));
	/**д�����Ա�����Ƴ���*/
	buffer.write((void*)&m_nProNameLen,sizeof(int));
	
	/**д�����Ա������*/
	buffer.write((void*)m_strProName.c_str(),m_nProNameLen);
	
}
void CFeatureClass::setFCLID(UINT64 nFCLID)
{
	m_nFCLid=nFCLID;
}
UINT64 CFeatureClass::getFCLID()
{
	return m_nFCLid;
}

void CFeatureClass::setFCLName(string strFCLName)
{
	m_strFCLName=strFCLName;
}
string CFeatureClass::getFCLName()
{
	return m_strFCLName;
}
int CFeatureClass::getFCLNameLen()
{
	return m_strFCLName.size();
}

void CFeatureClass::setStatus(int nStatus)
{
	m_nStatus=nStatus;
}
int CFeatureClass::getStatus()
{
	return m_nStatus;
}

void CFeatureClass::setPropName(string strPropName)
{
	m_strProName=strPropName;
}
string CFeatureClass::getPropName()
{
	return m_strProName;
}
int CFeatureClass::getPropNameLen()
{
	return m_strProName.size();
}
//********************************************************************************** 
//** �������ƣ� sizeBuffer
//** ���������� �õ�Ҫ�����С
//** ��    �룺 ��          
//** ��    ���� ��
//** ����ֵ��Ҫ�����С
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
size_t CFeatureClass::sizeBuffer()
{
    size_t sFeatureClassSize = 0;
    sFeatureClassSize = sizeof(UINT64) + sizeof(int) + m_nFCLNameLen + sizeof(int) + sizeof(int) + m_nProNameLen;
    return sFeatureClassSize;
}