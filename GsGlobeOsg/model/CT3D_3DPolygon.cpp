//********************************************************************************** 
//** �ļ����ƣ�CT3D_3DPolygon.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά�������ʵ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-11
//********************************************************************************** 


#include "CT3D_3DPolygon.h"

//********************************************************************************** 
//** �������ƣ� C3DPolygon
//** ���������� ���캯��
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
C3DPolygon::C3DPolygon()
{
    m_byTypeID = GEOTYPE_3D_POLYGON;
}


//********************************************************************************** 
//** �������ƣ� ~C3DPolygon
//** ���������� ��������
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
C3DPolygon::~C3DPolygon()
{
    int nCount = m_vecRingList.size();
    for(int i=0; i < nCount; i++)
    {
        if(m_vecRingList[i])
            delete m_vecRingList[i];
        m_vecRingList[i]= NULL;
    }
    m_vecRingList.clear();

}

//********************************************************************************** 
//** �������ƣ� readBuffer
//** ���������� �����ݶ���buf
//** ��    �룺 Buffer����buf������           
//** ��    ���� ��
//** ����ֵ��	�ɹ�Ϊtrue��ʧ��Ϊfalse
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
bool C3DPolygon::readBuffer( Buffer & buf)
{
	bool bRet =C3DSurface::readBuffer(buf);
	//modify by yangling 20131208 begin
	if(!bRet)
	{
		return false;
	}
	//modify by yangling 20131208 end
    int nLinearRingNum = 0;
	//��ȡ���Ի�����
	buf.read((char*)&nLinearRingNum,sizeof(int));
	//��ȡ���Ի��б�
    C3DLinearRing* pLinearRing =NULL;
    size_t nSize = 0;
	for(int i=0;i < nLinearRingNum;i++)
	{	
        buf.read((char*)&nSize,sizeof(unsigned int));//�������Ĵ�С
        pLinearRing = new C3DLinearRing();
        pLinearRing->readBuffer(buf);
        m_vecRingList.push_back(pLinearRing);
	}
	return true;
}
//********************************************************************************** 
//** �������ƣ� writeBuffer
//** ���������� ������д��buf
//** ��    �룺 Buffer����buf������           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
void C3DPolygon::writeBuffer(Buffer& buf)
{
	C3DSurface::writeBuffer(buf);
    int nSize = 0;
	//д�����Ի�����
    int nLinearRingNum = getLinearRingNum();
	buf.write((char*)&nLinearRingNum,sizeof(int));
	//д�����Ի��б�
	for(int i=0;i< nLinearRingNum;i++)
	{
        nSize = m_vecRingList[i]->sizeBuffer();
;		buf.write((char*)&nSize,sizeof(unsigned int));
        m_vecRingList[i]->writeBuffer(buf);
	}
}

int C3DPolygon::getLinearRingNum()
{
	return m_vecRingList.size();
}

void C3DPolygon::setLinearRingList(const  _3DLinearRingList& vRingList)
{
	m_vecRingList=vRingList;
}
 _3DLinearRingList& C3DPolygon::getLinearRingList()
{
	return m_vecRingList;
}
	
size_t C3DPolygon::sizeBuffer()
{
	size_t nSize = 0;
	nSize += C3DSurface::sizeBuffer();
	nSize += sizeof(int);//���Ի�����

	for (int i=0;i<getLinearRingNum();i++)
	{
		nSize += sizeof(UINT);//�߻���С����
		nSize += m_vecRingList[i]->sizeBuffer();//�߻���Сֵ
	}
	return nSize;
}

