//********************************************************************************** 
//** �ļ����ƣ�CT3D_3DGroup.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ������������ʵ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-14
//********************************************************************************** 
#include "CT3D_3DGroup.h"
#include "Buffer.h"

//********************************************************************************** 
//** �������ƣ� CreateObject
//** ���������� ����һ����ǰ�����������ڴ�ռ�
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
CGeometry* C3DGroup::CreateObject()
{
    return new C3DGroup;
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
bool C3DGroup::readBuffer( Buffer & buf)
{
    bool bRet = C3DGeometry::readBuffer(buf);
    if(!bRet)
	{
		return false;
	}
    //ָ����������Ķ�����Ϣ**************

    buf.read((char*)&m_nGeometryNum,sizeof(int));//���ж������

    CGeometry* pGeometry = NULL;
    byte byType = -1;
    m_vGeoCollection.reserve(m_nGeometryNum);
    for(int i=0; i<m_nGeometryNum; i++)
    {
    	
    	unsigned int  nSize = 0;
    	buf.read((char*)&nSize,sizeof(unsigned int));//�������Ĵ�С
    		
    	char* p = (char*)buf.data() + buf.getPos()+sizeof(UID64);//��������ID
    	memcpy((char*)&byType,p,sizeof(byte));//��ö���� ���� �Դ��б�����һ�����
    	pGeometry = CGeometry::CreateGeometry(byType);

		//������󴴽�ʧ��
		if (NULL == pGeometry)
			continue;

		//��ȡ�������ݣ������ȡʧ�ܣ�����False
    	if (!pGeometry->readBuffer(buf))
		{
			SafeDelete(pGeometry);
			return false;
		}
    	C3DGeometry* p3DGeometry = (C3DGeometry*) pGeometry;
        _GeometryPair geopair(nSize,p3DGeometry);
    	m_vGeoCollection.push_back(geopair);//��3DGeometry��ָ����ӵ���Լ��ζ���Ĵ洢�ṹ��
        p = NULL;
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
void C3DGroup::writeBuffer(Buffer& buf)
{	
    C3DGeometry::writeBuffer(buf);

    //ָ����������Ķ�����Ϣ**************

    int nCount = 0;
    buf.write((char*)&m_nGeometryNum,sizeof(int));//���ж������
    byte byType = -1;
    for(int i=0; i<m_nGeometryNum; i++)
    {

        buf.write((char*)& m_vGeoCollection[i].first,sizeof(unsigned int));//�������Ĵ�С
        m_vGeoCollection[i].second->writeBuffer(buf);
       
    }
}

size_t C3DGroup::sizeBuffer()
{
	size_t nSize = 0;

	nSize += C3DGeometry::sizeBuffer();
	nSize += sizeof(int);

	for (int i=0;i<getGeometryNum();i++)
	{
		nSize += sizeof(UINT);
		nSize += m_vGeoCollection[i].second->sizeBuffer();
	}
	return nSize;
}
