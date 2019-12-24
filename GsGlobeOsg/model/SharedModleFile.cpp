//********************************************************************************** 
//** �ļ����ƣ�SharedModelFile.cpp
//** CopyRight (c) 2000-2012 ��󼪰���Ϣ�������޹�˾����һ��
//** �ļ������� ����ģ�������ļ�ʵ��
//** �� �� �ˣ� �
//** �������ڣ� 2012-04-11
//********************************************************************************** 

#include "SharedModleFile.h"
#include <sys/stat.h>
//********************************************************************************** 
//** �������ƣ� CSharedModelFile
//** ���������� ���캯��
//** ��    �룺 ��          
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
CSharedModleFile::CSharedModleFile(void)
{
}

//********************************************************************************** 
//** �������ƣ� ~CSharedModelFile
//** ���������� ��������
//** ��    �룺 ��          
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
CSharedModleFile::~CSharedModleFile(void)
{
}

//********************************************************************************** 
//** �������ƣ� read
//** ���������� ��ȡ�ļ�����
//** ��    �룺 ������f������           
//** ��    ���� ��
//** ����ֵ��	����ģ�Ͷ����б�
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
SharedModelList CSharedModleFile::read(std::ifstream & f)
{
	//�õ�ϵͳ���ݰ汾��
	f.read((char*)&m_SDMFileHeder.unDataVersion,sizeof(UINT));
	//�õ�У��λ
	f.read((char*)&m_SDMFileHeder.uCheckBit,sizeof(UINT64));
	//�õ��������
	f.read((char*)&m_SDMFileHeder.unObjectNum,sizeof(UINT));
	//�õ��ļ�ͷ��С
	size_t sFileHeadBuff=sizeof(UINT)+sizeof(UINT64)+sizeof(UINT)
		+m_SDMFileHeder.unObjectNum*(sizeof(UINT)+sizeof(UID64));

    UINT64 unSDMID=0;
    UINT unOffset=0;
    typedef pair <UINT64, UINT> Int_Pair;
    for(UINT i=0;i<m_SDMFileHeder.unObjectNum;i++)
    {
        f.read((char*)&unSDMID,sizeof(UINT64));
        f.read((char*)&unOffset,sizeof(UINT));
        m_SDMFileHeder.sdmidAndOffsetList.insert(Int_Pair(unSDMID,unOffset));
    }

	//�����ļ�ͷ
	f.seekg(sFileHeadBuff,ios::beg);
	size_t sFileBodyBuff=getFileSize()-sFileHeadBuff;
	char* p=new char[sFileBodyBuff];
	size_t readByte=0;
	if(p!=NULL)
	{
		while(!f.eof()&&readByte<getFileSize())
		{
			f.read(p+readByte,getFileSize()-readByte);
			readByte+=f.gcount();
		}

	}

    m_ReadBuf.attach((void*)p,sFileBodyBuff);
	p=NULL;
	for(UINT i=1;i<=m_SDMFileHeder.unObjectNum;i++)
	{
		//����ģ�Ͷ���ָ��
		SharedModelSharedPtr sharedmodel(new CSharedModel());
		//��ȡ�������
		sharedmodel->readBuffer(m_ReadBuf);

		//��ȡlod��Ϣ�������½ṹ���ӣ�
		sharedmodel->readlodBuffer(m_ReadBuf);

		m_SDMFileBody.m_ShareModelList.push_back(sharedmodel);
	}
	return m_SDMFileBody.m_ShareModelList;
}

//********************************************************************************** 
//** �������ƣ� write
//** ���������� ��ȡ�ļ�����
//** ��    �룺 ������f������           
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� �
//** �������ڣ� 2012-04-11
//**********************************************************************************
void CSharedModleFile::write(std::ofstream & f)
{
	if(m_FileSize != 0)
	{
		char* p = new char[m_FileSize];
		if(p != NULL)
		{
            m_WriteBuf.attach((void*)p,m_FileSize);
		}
		else
		{
			return;
		}
	}


	//д���ļ�ͷ����
	m_WriteBuf.write((char*)&(m_SDMFileHeder.unDataVersion),sizeof(UINT));
	m_WriteBuf.write((char*)&(m_SDMFileHeder.uCheckBit),sizeof(UINT64));
	m_WriteBuf.write((char*)&(m_SDMFileHeder.unObjectNum),sizeof(UINT));

    ObjectIDAndOffsetList::iterator iter;
    iter = m_SDMFileHeder.sdmidAndOffsetList.begin();

	for(UINT i=0;i<m_SDMFileHeder.sdmidAndOffsetList.size();i++)
	{
		m_WriteBuf.write((char*)&iter->first,sizeof(UID64));
		m_WriteBuf.write((char*)&iter->second,sizeof(UINT));
		iter++;
	}
    int nSize = 0;
	//д���ļ��岿�ֵ�������
	for(UINT i=0;i<m_SDMFileHeder.unObjectNum;i++)
	{
		m_SDMFileBody.m_ShareModelList[i]->writeBuffer(m_WriteBuf);
        nSize += m_SDMFileBody.m_ShareModelList[i]->sizeBuffer();
	}
    size_t writeByte=1024;
    size_t curWriteByte=0;
    size_t sFileSize = m_FileSize;
    m_WriteBuf.setPos(0);
    if(sFileSize % writeByte > 0)
    {
        for(int i = 0; i < sFileSize / writeByte; i++)
        {

            f.write((const char*)m_WriteBuf.getCurPtr(),writeByte);
            curWriteByte += writeByte;
            m_WriteBuf.setPos(curWriteByte);
        }
        f.write((const char*)m_WriteBuf.getCurPtr(),sFileSize % writeByte);
        curWriteByte += sFileSize % writeByte;
        m_WriteBuf.setPos(curWriteByte-1);//�ѵ��ļ�ĩβ
    }
    else
    {
        if(sFileSize / writeByte > 1)
        {
            for(int j = 0; j < sFileSize / writeByte; j++)
            {
                f.write((const char*)m_WriteBuf.getCurPtr(),writeByte);
                curWriteByte += writeByte;
                if(curWriteByte < sFileSize)
                {
                    m_WriteBuf.setPos(curWriteByte);
                }
                else
                {
                    m_WriteBuf.setPos(curWriteByte-1);
                }
            }
        }
        else
        {
            f.write((const char*)m_WriteBuf.getCurPtr(),writeByte);
        }

    }
}

//********************************************************************************** 
//** �������ƣ� getFileSize
//** ���������� �õ��ļ���С
//** ��    �룺 ��         
//** ��    ���� ��
//** ����ֵ���ļ���С
//** ��    �ߣ� �
//** �������ڣ� 2012-04-14
//**********************************************************************************
size_t CSharedModleFile::getFileSize()
{
	if(!m_strFileName.c_str())
	{
		return -1;
	}
	struct stat f_stat;
	if(stat(m_strFileName.c_str(),&f_stat)==-1)
	{
		return -1;
	}
	m_FileSize = f_stat.st_size;
	return f_stat.st_size;
}
//********************************************************************************** 
//** �������ƣ� setFileName
//** ���������� �����ļ�����
//** ��    �룺 �ļ�����         
//** ��    ���� ��
//** ����ֵ��	��
//** ��    �ߣ� �
//** �������ڣ� 2012-04-14
//**********************************************************************************
void CSharedModleFile::setFileName(string filename)
{
	m_strFileName=filename;
}
//********************************************************************************** 
//** �������ƣ� getFileName
//** ���������� �õ��ļ�����
//** ��    �룺 ��         
//** ��    ���� ��
//** ����ֵ��	�ļ�����
//** ��    �ߣ� �
//** �������ڣ� 2012-04-14
//**********************************************************************************
string CSharedModleFile::getFileName()
{
	return m_strFileName;
}
SharedModelList& CSharedModleFile::getSharedModelList()
{
	return m_SDMFileBody.m_ShareModelList;
}
void CSharedModleFile::Flush()
{
    if(m_SDMFileBody.m_ShareModelList.size()>0)
    {
                  
        m_SDMFileBody.m_ShareModelList.clear();
        
    }
}