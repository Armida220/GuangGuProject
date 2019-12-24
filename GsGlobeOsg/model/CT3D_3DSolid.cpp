//********************************************************************************** 
//** �ļ����ƣ�CT3D_C3DSolid.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ��ά����ʵ��
//** �� �� �ˣ� ����
//** �������ڣ� 2012-04-11
//********************************************************************************** 


#include "CT3D_3DSolid.h"
#include "Buffer.h"

//********************************************************************************** 
//** �������ƣ� C3DSolid
//** ���������� ���캯��
//** ��    �룺 ��           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-11
//**********************************************************************************
 C3DSolid::C3DSolid()
{
    m_byTypeID = GEOTYPE_3D_SOLID;
}



 //********************************************************************************** 
 //** �������ƣ� ~C3DSolid
 //** ���������� ��������
 //** ��    �룺 ��           
 //** ��    ���� ��
 //** ����ֵ��	��
 //** ��    �ߣ� ����
 //** �������ڣ� 2012-04-11
 //**********************************************************************************
 C3DSolid::~C3DSolid()
{
	//return;
    int nSize = m_3DSurfaceList.size();
    for(int i = 0; i< nSize; i++)
    {
        if(m_3DSurfaceList[i].second!= NULL)
        {
            delete m_3DSurfaceList[i].second;
            m_3DSurfaceList[i].second = NULL;
        }
    }
    m_3DSurfaceList.clear();
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
bool C3DSolid::readBuffer( Buffer & buf)
{
	
	bool bRet =C3DGeometry::readBuffer(buf);

	
	if(!bRet)
		return false;
	
	//��ȡ�����
    int nSurfaceNum = 0;
	buf.read((void*)&nSurfaceNum,sizeof(int));
    byte byType = 0;//ʵ�ʵ�������
	//��ȡ���б�
	for(int i=0;i< nSurfaceNum;i++)
	{
		UINT nSize=0;
        buf.read((void*)&nSize,sizeof(UINT));//����Ĵ�С
		
        //�õ�Surface��������
        memcpy(&byType, (byte*)buf.getCurPtr() + sizeof(UINT64),sizeof(byte));

		//������ʹ���
		if (255 == byType)
			continue;

        //���������
        C3DSurface* pSurface = (C3DSurface*)CreateGeometry(byType);
		if (NULL == pSurface)
			/*return false*/
			continue;
		//if (buf.size()!=303401)
		//{

		//if (buf.size()==303401)
		//{
		//	//int a=0;
		//	//return true;
		//	return false;
		//}

		if (!pSurface->readBuffer(buf))
		{
			SafeDelete(pSurface);
			return false;
		}
		
		//if (buf.size()==303401)
		//{
		//	//int a=0;
		//	//return true;
		//	return false;
		//}


		_3DSurfacePair surfacepair(nSize,pSurface);

		m_3DSurfaceList.push_back(surfacepair);
		/*}*/
	//	return true;
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
void C3DSolid::writeBuffer(Buffer& buf)
{
	C3DGeometry::writeBuffer(buf);
	//д�������
    int nSurfaceNum = m_3DSurfaceList.size();
	buf.write((void*)&nSurfaceNum,sizeof(int));
	//д�����б�
	for(int i=0;i<nSurfaceNum;i++)
	{
		buf.write((void*)&m_3DSurfaceList[i].first,sizeof(UINT));
        m_3DSurfaceList[i].second->writeBuffer(buf);
	}
}



void C3DSolid::set3DSurfaceList(const _3DSurfaceList& v3DSurfaceList)
{
	m_3DSurfaceList=v3DSurfaceList;
}
_3DSurfaceList& C3DSolid::get3DSurfaceList()
{
	return m_3DSurfaceList;
}
int C3DSolid::getSurfaceNum()
{
	return m_3DSurfaceList.size();
}

size_t C3DSolid::sizeBuffer()
{
	size_t nSize = 0;
	nSize += C3DGeometry::sizeBuffer();
	nSize += sizeof(int);//�����
	for (int i=0;i<getSurfaceNum();i++)
	{
		nSize += sizeof(UINT);//���С
		nSize += m_3DSurfaceList[i].second->sizeBuffer();
	}
	return nSize;
}
