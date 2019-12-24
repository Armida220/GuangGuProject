#include "GeometrySetFile.h"
#include <sys/stat.h>
CGeometrySetFile::CGeometrySetFile(void)
:m_ReadBuf(),
m_WriteBuf()
{
	//���ӳ�ʼ��
	m_nMemGeometryMax = 0;
}

CGeometrySetFile::~CGeometrySetFile(void)
{
    for(int i = 0; i < m_GeometrySetFileBody.m_GeometryList.size();i++)
    {
		SafeDelete(m_GeometrySetFileBody.m_GeometryList[i].pGeometry);
    }
	for(int i = 0; i < m_newGeometrySetFileBody.m_NewGeometryList.size();i++)
	{
		if(m_newGeometrySetFileBody.m_NewGeometryList[i].pGeometry != NULL)
		{
			delete m_newGeometrySetFileBody.m_NewGeometryList[i].pGeometry;
			m_newGeometrySetFileBody.m_NewGeometryList[i].pGeometry = NULL;
		}
	}
}

//********************************************************************************** 
//** �������ƣ� read
//** ���������� ���ļ��ж����ݵ���������
//** ��    �룺 f:�ļ����������������           
//** ��    ���� ��
//** ����ֵ����
//** ��    �ߣ� ����
//** �������ڣ� 2012-04-16
//**********************************************************************************
 GeometryList& CGeometrySetFile:: read(ifstream& f)
 {
	 setMemGeometryClear();
     //�õ�ϵͳ���ݰ汾��
     f.read((char*)&m_GeometrySetFileHeader.uDataVersion,sizeof(UINT));

     //�õ�У��λ
     f.read((char*)&m_GeometrySetFileHeader.uCheckBit,sizeof(UINT64));

     //�õ��������
     f.read((char*)&m_GeometrySetFileHeader.unObjNum,sizeof(UINT));
    
     UINT64 unGSID=0;
     UINT unOffset=0;
     typedef pair <UINT64, UINT> Int_Pair;
     for(UINT i=0;i<m_GeometrySetFileHeader.unObjNum;i++)
     {
         f.read((char*)&unGSID,sizeof(UINT64));
         f.read((char*)&unOffset,sizeof(UINT));
         m_GeometrySetFileHeader.IdAndOffsetList.insert(Int_Pair(unGSID,unOffset));
     }
     
     //�����ļ�ͷ
     f.seekg(2*sizeof(UINT) + sizeof(UINT64) + m_GeometrySetFileHeader.unObjNum*(sizeof(UINT64)+sizeof(UINT)),ios::beg);
    
     //���ü��������ĸ���
     //m_GeometrySetFileBody.GMSet.setGeometryNum(m_GeometrySetFileHeader.unObjNum);

     //�õ��ļ�ͷ��С
     size_t sFileHeadBuff=sizeof(UINT)+sizeof(UINT64)+sizeof(UINT)
         +m_GeometrySetFileHeader.unObjNum*(sizeof(UINT64)+sizeof(UINT));
      
     //�õ��ļ����С
     size_t sFileBodyBuff=getFileSize()-sFileHeadBuff;

     //char* p=new char[sFileBodyBuff];
     
     size_t readByte=0;
     if(m_pGeometry!=NULL)
     {
         while(!f.eof()&&readByte<getFileSize())
         {
             f.read(m_pGeometry+readByte,getFileSize()-readByte);
             readByte+=f.gcount();
         }

     }

     m_ReadBuf.set(m_pGeometry,sFileBodyBuff);
     //p=NULL;
     GeometryItem item;

     for(UINT i=0;i< m_GeometrySetFileHeader.unObjNum;i++)
     {
         //��ȡ����ID
         m_ReadBuf.read((char*)&item.uID,sizeof(UINT64));

         //��ȡ��������
         m_ReadBuf.read((char*)&item.byType,sizeof(byte));

		 if(255!=item.byType)
		 {    //��ȡ�������ݳ���
			 m_ReadBuf.read((char*)&item.uDataLen,sizeof(UINT));

			 //���ݼ������ʹ�����Ӧ�ļ�����
			 item.pGeometry = CGeometry::CreateGeometry(item.byType);

			 //����Ӧ�Ļ�������ȡ����
			 if( item.pGeometry!=NULL)
			 {
				 item.pGeometry->readBuffer(m_ReadBuf);
			 }
		 }
		 else
		 {
			item.uDataLen=0;
			item.pGeometry = NULL;	
		 }
         //��ȡ����ʱ��
         m_ReadBuf.read((char*)&item.uFeatureCreateTime,sizeof(UINT64));
         //��ȡ����ʱ��
         m_ReadBuf.read((char*)&item.uFeatureUpdateTime,sizeof(UINT64));
         m_GeometrySetFileBody.m_GeometryList.push_back(item);
     }
 
     return m_GeometrySetFileBody.m_GeometryList;
    
 }


 NewGeometryList& CGeometrySetFile:: readnew(ifstream& f)
 {
	 setMemGeometryClear();
	 //�õ�ϵͳ���ݰ汾��
	 f.read((char*)&m_GeometrySetFileHeader.uDataVersion,sizeof(UINT));

	 //�õ�У��λ
	 f.read((char*)&m_GeometrySetFileHeader.uCheckBit,sizeof(UINT64));

	 //�õ��������
	 f.read((char*)&m_GeometrySetFileHeader.unObjNum,sizeof(UINT));

	 UINT64 unGSID=0;
	 UINT unOffset=0;
	 typedef pair <UINT64, UINT> Int_Pair;
	 for(UINT i=0;i<m_GeometrySetFileHeader.unObjNum;i++)
	 {
		 f.read((char*)&unGSID,sizeof(UINT64));
		 f.read((char*)&unOffset,sizeof(UINT));
		 m_GeometrySetFileHeader.IdAndOffsetList.insert(Int_Pair(unGSID,unOffset));
	 }

	 //�����ļ�ͷ
	 f.seekg(2*sizeof(UINT) + sizeof(UINT64) + m_GeometrySetFileHeader.unObjNum*(sizeof(UINT64)+sizeof(UINT)),ios::beg);

	 //���ü��������ĸ���
	 //m_GeometrySetFileBody.GMSet.setGeometryNum(m_GeometrySetFileHeader.unObjNum);

	 //�õ��ļ�ͷ��С
	 size_t sFileHeadBuff=sizeof(UINT)+sizeof(UINT64)+sizeof(UINT)
		 +m_GeometrySetFileHeader.unObjNum*(sizeof(UINT64)+sizeof(UINT));

	 //�õ��ļ����С
	 size_t sFileBodyBuff=getFileSize()-sFileHeadBuff;

	 //char* p=new char[sFileBodyBuff];

	 size_t readByte=0;
	 if(m_pGeometry!=NULL)
	 {
		 while(!f.eof()&&readByte<getFileSize())
		 {
			 f.read(m_pGeometry+readByte,getFileSize()-readByte);
			 readByte+=f.gcount();
		 }

	 }

	 m_ReadBuf.set(m_pGeometry,sFileBodyBuff);
	 //p=NULL;
	 //NewGeometryItem item;

	 for(UINT i=0;i< m_GeometrySetFileHeader.unObjNum;i++)
	 {
		 NewGeometryItem item;

		 //��ȡ����ID
		 m_ReadBuf.read((char*)&item.uID,sizeof(UINT64));

		 //��ȡ��������
		 m_ReadBuf.read((char*)&item.byType,sizeof(byte));

		 if(255!=item.byType)
		 {    //��ȡ�������ݳ���
			 m_ReadBuf.read((char*)&item.uDataLen,sizeof(UINT));

			 //���ݼ������ʹ�����Ӧ�ļ�����
			 item.pGeometry = CGeometry::CreateGeometry(item.byType);

			 //����Ӧ�Ļ�������ȡ����
			 if( item.pGeometry!=NULL)
			 {
				 item.pGeometry->readBuffer(m_ReadBuf);
			 }
		 }
		 else
		 {
			 item.uDataLen=0;
			 item.pGeometry = NULL;	
		 }
		 //��ȡ����ʱ��
		 m_ReadBuf.read((char*)&item.uFeatureCreateTime,sizeof(UINT64));
		 //��ȡ����ʱ��
		 m_ReadBuf.read((char*)&item.uFeatureUpdateTime,sizeof(UINT64));

		 //��ȡlodInfo�ĸ���
		 byte nLodCount = 0;
		 m_ReadBuf.read((char *)&nLodCount,sizeof(byte));
		 for(byte nLodIndex = 0;nLodIndex<nLodCount;nLodIndex++)
		 {
			 LodInfo lodData;
			 lodData.readBuffer(m_ReadBuf);
			 item.vecLodInfo.push_back(lodData);
		 }
		 m_newGeometrySetFileBody.m_NewGeometryList.push_back(item);
		 //m_GeometrySetFileBody.m_GeometryList.push_back(item);
		 
	 }

	 return  m_newGeometrySetFileBody.m_NewGeometryList;

 }

 //********************************************************************************** 
 //** �������ƣ� writeObject
 //** ���������� �����ݿ��е���������д���ļ���
 //** ��    �룺 f:�ļ���������������
 //**            buf:Ҫд��Ķ����ڴ��
 //** ��    ���� ��
 //** ����ֵ����
 //** ��    �ߣ� ����
 //** �������ڣ� 2012-07-27
 //**********************************************************************************

 void CGeometrySetFile::writeObject(ofstream & f,Buffer& buf)
 {
     UINT64 nGeoID = 0;
     byte nGeoType = 0;
     UINT nDataLen = buf.size()-5 + sizeof(nGeoID)+sizeof(nGeoType)+sizeof(nDataLen)+2*sizeof(UINT64);
     UINT64 startTime =0;
    UINT64 endtime =0;
     //����buf��ͷ5���ֽ�          
       buf.setPos(5); 
       buf.read((void*)&nGeoID,sizeof(nGeoID));
       buf.read((void*)&nGeoType,sizeof(nGeoType));
       buf.setPos(5);

    //д�뼸������
        f.write((char*)&nGeoID,sizeof(nGeoID));
        f.write((char*)&nGeoType,sizeof(nGeoType));
        f.write((char*)&nDataLen,sizeof(nDataLen));
        f.write((char*)buf.getCurPtr(),buf.size()-5);

        f.write((char*)&startTime,sizeof(startTime));
        f.write((char*)&endtime,sizeof(endtime));
        m_objSizeList.push_back(make_pair(nGeoID,nDataLen));

             
 }

 //********************************************************************************** 
 //** �������ƣ� writeFileHeader
 //** ���������� Ϊ�����������ļ�����ļ�ͷ
 //** ��    �룺 f:�ļ���������������
 //**              glist:�����б�
 //** ��    ���� ��
 //** ����ֵ����
 //** ��    �ߣ� ����
 //** �������ڣ� 2012-07-27
 //**********************************************************************************
  void CGeometrySetFile::writeFileHeader(ofstream & f)
 {
     //��������
     byte byType = 255;
    
     //����ƫ����
     int nOffset = 0;
     //����������
     int nGeoSize = 0;
     UINT64 uGeoID = 0;
     char *p = NULL;
     //д���ļ�ͷ����

     //д��ϵͳ���ݰ汾��
     int nVersion =1;
     f.write((char*)&nVersion,sizeof(UINT));
     //д��У��λ
     char cCheckbits[2];
     cCheckbits[0]='g';
     cCheckbits[1]='s';
     f.write(cCheckbits,sizeof(UINT64));

     //д�뼸�θ���
     UINT nObjNum =m_objSizeList.size();
     f.write((char*)&nObjNum, sizeof(UINT));

     ObjectSizeList::iterator iter =m_objSizeList.begin();
     for(iter;iter != m_objSizeList.end();iter++)
     {
         //д�뼸��ID
         uGeoID = iter->first;
         f.write((char*)&uGeoID,sizeof(UID64));
         //д�뼸��ƫ����
         nOffset = getObjOffset(uGeoID);
         f.write((char*)&nOffset,sizeof(UINT));

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
size_t CGeometrySetFile::getFileSize()
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
void CGeometrySetFile::setFileName(string filename)
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
string CGeometrySetFile::getFileName()
{
    return m_strFileName;
}
GeometryList& CGeometrySetFile::getGeometryList()
{
	return m_GeometrySetFileBody.m_GeometryList;
}
NewGeometryList& CGeometrySetFile::getNewGeometryList()
{
	return m_newGeometrySetFileBody.m_NewGeometryList;
}
void CGeometrySetFile::Flush()
{
    if (m_GeometrySetFileHeader.IdAndOffsetList.size() > 0)
    {
        m_GeometrySetFileHeader.IdAndOffsetList.clear();
    }
    if(m_GeometrySetFileBody.m_GeometryList.size() > 0)
    {
        for(int i = 0; i < m_GeometrySetFileBody.m_GeometryList.size();i++)
        {
            delete m_GeometrySetFileBody.m_GeometryList[i].pGeometry;
            m_GeometrySetFileBody.m_GeometryList[i].pGeometry = NULL;
        }
        m_GeometrySetFileBody.m_GeometryList.clear();
        m_strFileName.clear();
        m_ReadBuf.clear();
        m_WriteBuf.clear();    
    }

	if(m_newGeometrySetFileBody.m_NewGeometryList.size() > 0)
	{
		for(int i = 0; i < m_newGeometrySetFileBody.m_NewGeometryList.size();i++)
		{
			delete m_newGeometrySetFileBody.m_NewGeometryList[i].pGeometry;
			m_newGeometrySetFileBody.m_NewGeometryList[i].pGeometry = NULL;
		}
		m_newGeometrySetFileBody.m_NewGeometryList.clear();
		m_strFileName.clear();
		m_ReadBuf.clear();
		m_WriteBuf.clear();    
	}
    m_objSizeList.clear();
}
//********************************************************************************** 
    //** �������ƣ� getGeometryNum
    //** ���������� �õ�������ĸ���
    //** ��    �룺 ��          
    //** ��    ���� ��
    //** ����ֵ��Ҫ�صĸ���
    //** ��    �ߣ� ����
    //** �������ڣ� 2012-04-16
    //**********************************************************************************
    UINT CGeometrySetFile::getGeometryNum() const
	{
		return m_GeometrySetFileBody.m_GeometryList.size();
	}
    //********************************************************************************** 
    //** �������ƣ� getObjOffset
    //** ���������� �õ�����ƫ����
    //** ��    �룺 GeoID:����ID��
    //** ��    ���� ��
    //** ����ֵ��ָ�����ε�ƫ����
    //** ��    �ߣ� ����
    //** �������ڣ� 2012-07-04
    //**********************************************************************************
    int CGeometrySetFile::getObjOffset(UINT64 nGeoID)
    {
        int nsize1 = 0;
        int nsize2 = 0;
        int nsize = -1;
        int index = 0;
        for(int i = 0; i < m_objSizeList.size();i++)
        {
            if(m_objSizeList[i].first == nGeoID)
            {
                index = i;
                break;
            }
        }

        //�����ļ�ͷƫ����
        //  nsize1 =(m_objSizeList.size() -index-1)*(sizeof(UINT64)+sizeof(UINT));
        UINT nVersion = 0;//�汾��
        UINT64 nCheckBit =0;//У��λ
        UINT nObjCount =0;//�������


        nsize1 = sizeof(nVersion) + sizeof(nCheckBit) + sizeof(nObjCount) +  m_objSizeList.size()*( sizeof(UINT64)+sizeof(UINT) );

        //�����ļ���ƫ����
        for(int i = 0; i < index;i++)
        {
            nsize2 += m_objSizeList[i].second;
        }
        nsize =nsize1 + nsize2; 


        return nsize;
    }
	void CGeometrySetFile::setMemGeometryMax(int MemMax)
	{
		m_nMemGeometryMax=MemMax;
	}
// 	void  CGeometrySetFile::setMemGeometry()
// 	{
// 		m_pGeometry=new char[m_nMemGeometryMax];
// 	}
	bool  CGeometrySetFile::setMemGeometry()
	{
		try
		{
			m_pGeometry=new char[m_nMemGeometryMax];
		}
		catch(...)
		{
			return false;
		}

		return true;
	}
	void  CGeometrySetFile::setMemGeometryClear()
	{
		memset(m_pGeometry,0,m_nMemGeometryMax);
	}
	void  CGeometrySetFile::deleteMemGeometry()
	{
		SafeDeleteArray(m_pGeometry);
	}