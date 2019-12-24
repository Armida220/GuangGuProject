//********************************************************************************** 
//** �ļ����ƣ�CT3D_3DFeatureInfoGroup.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��άҪ�������ʵ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-15
//********************************************************************************** 
#include "CT3D_3DFeatureInfoGroup.h"
#include "Buffer.h"



//********************************************************************************** 
//** �������ƣ� CreateObject
//** ���������� ����һ����ǰ�����������ڴ�ռ�
//** ��    �룺 ��            
//** ��    ���� ��
//** ����ֵ��	���ٵĵ�ǰ������ڴ�ռ���׵�ַ
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
CGeometry* C3DFeatureInfoGroup::CreateObject()
{
	return new C3DFeatureInfoGroup;
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
bool C3DFeatureInfoGroup::readBuffer( Buffer & buf)
{
    bool bRet = C3DGeometry::readBuffer(buf);
	if(!bRet)
	{
		return false;
	}
	int nCount = 0;
	buf.read((char*)&nCount,sizeof(int));

	FEATURE_INFO fi;
	m_vFeatureInfos.reserve(nCount);
	for(int i=0; i<nCount; i++)
	{
        buf.read((char*)&fi,sizeof(UID64)+ Envelope3D::sizeBuffer());
		
		m_vFeatureInfos.push_back(fi);
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
void C3DFeatureInfoGroup::writeBuffer(Buffer& buf)
{
    C3DGeometry::writeBuffer(buf);

	int nCount = m_vFeatureInfos.size();
	buf.write((char*)&nCount,sizeof(int));

	for(int i=0; i<nCount; i++)
	{
        buf.write(&(m_vFeatureInfos[i]), sizeof(UID64)+Envelope3D::sizeBuffer());
	}

}

void C3DFeatureInfoGroup::setFeatureinfoNum(int nFeatureinfoNum)
{
	m_nFeatureinfoNum=nFeatureinfoNum;
}
int C3DFeatureInfoGroup::getFeatureinfoNum()
{
	return m_nFeatureinfoNum;
}
size_t C3DFeatureInfoGroup::sizeBuffer()
{
	size_t nSize = 0;
	nSize+=C3DGeometry::sizeBuffer();
	nSize+=sizeof(int);//���ζ������
	nSize+=getFeatureinfoNum()*(sizeof(UID64)+Envelope3D::sizeBuffer());
	return nSize;
}
