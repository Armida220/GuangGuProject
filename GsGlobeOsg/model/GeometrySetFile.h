#pragma once
#include "ModelDef.h"
#include <vector>
#include <utility>
#include<fstream>
#include <map>
#include <utility>
#include "ModelDef.h"
#include "CT3D_Geometry.h"
using namespace std;
typedef struct _tagGeometryItem
{
    UINT64 uID;//GeometryID
    byte byType;//������������
    UINT uDataLen;//�������ݳ���
    CGeometry* pGeometry;//����������
    UINT64 uFeatureCreateTime;//Ҫ�ش���ʱ��
    UINT64 uFeatureUpdateTime;//Ҫ�ظ���ʱ��
}GeometryItem;


typedef struct /*DLL_EXPORT*/ tagMTData
{
public:
	void readBuffer(Buffer& buffer)
	{
		buffer.read(&nDataLen, sizeof(nDataLen));
		pMTData = new char[nDataLen];
		buffer.read(pMTData, nDataLen);
	}

	void writeBuffer(Buffer& buffer)
	{
		buffer.write(&nDataLen, sizeof(nDataLen));
		buffer.write(pMTData, nDataLen);
	}

	void copy(const tagMTData& data)
	{
		nDataLen = data.nDataLen;
		if (nDataLen<=0)
		{
			pMTData = NULL;
			return;
		}

		pMTData = new char[nDataLen];
		memcpy(pMTData, data.pMTData, nDataLen);
	}
	int sizeBuffer()
	{
		int nSize = 0;
		nSize += sizeof(int) + nDataLen;
		return nSize;
	}
public:
	int nDataLen;
	char* pMTData;
}MTData;

typedef struct /*DLL_EXPORT*/ tagLOD
{
public:
	void readBuffer(Buffer& buffer)
	{
		buffer.read(&nIndex, sizeof(byte));
		//�������ݸ���
		int nSize = 0;
		buffer.read(&nSize,sizeof(int));
		for (int i = 0;i<nSize;i++)
		{
			MTData mtdata;
			mtdata.readBuffer(buffer);
			vecMTData.push_back(mtdata);
		}
	}

	void writeBuffer(Buffer& buffer)
	{
		buffer.write(&nIndex, sizeof(byte));
		//�������ݸ���
		int nSize = vecMTData.size();
		buffer.write(&nSize,sizeof(int));
		vector<MTData>::iterator it = vecMTData.begin();
		for (;it!=vecMTData.end();it++)
		{
			it->writeBuffer(buffer);
		}
	}

	void copy(const tagLOD& data)
	{
		nIndex = data.nIndex;
		for (int i = 0;i<data.vecMTData.size();i++)
		{
			MTData newData;
			newData.copy(data.vecMTData[i]);
			vecMTData.push_back(newData);
		}		
	}
	int sizeBuffer()
	{
		int nSize = 0;
		nSize += sizeof(nIndex) + sizeof(int);
		for (int i = 0;i<vecMTData.size();i++)
		{
			nSize += vecMTData[i].sizeBuffer();
		}
		return nSize;
	}
public:
	byte nIndex;
	vector<MTData> vecMTData;
}LodInfo; 

typedef struct _tagNewGeometryItem:public GeometryItem
{
	vector<LodInfo> vecLodInfo;
}NewGeometryItem;



typedef vector<GeometryItem>GeometryList;//�����б�
typedef vector<NewGeometryItem >NewGeometryList;
typedef map<UINT64,UINT> GeometryIDAndOffsetList;//�洢���ζ����ID��Offset�б�
typedef struct _tagGeometryFileHeader
{
    UINT uDataVersion;//���ݰ汾��
    UINT64 uCheckBit;//У��λ
    UINT unObjNum;//�������
    GeometryIDAndOffsetList IdAndOffsetList;//�������ID��Offset�б�

}GeometrySetFileHeader;//�ļ�ͷ

typedef struct _tagGeometrySetFileBody
{
    GeometryList m_GeometryList;//�����б�

}GeometrySetFileBody;//�ļ���

typedef struct _tagNewGeometrySetFileBody
{
	NewGeometryList m_NewGeometryList;//�����б�

}NewGeometrySetFileBody;//�ļ���

typedef vector<pair<UINT64,int>> ObjectSizeList;//ÿ������Ĵ�С�������ݴ����ݿ��е������ļ�ʱʹ��

class /*DLL_EXPORT*/ CGeometrySetFile
{
public:
    CGeometrySetFile(void);
    virtual ~CGeometrySetFile(void);

    //********************************************************************************** 
    //** �������ƣ� read
    //** ���������� ���ļ��ж����ݵ���������
    //** ��    �룺 f:�ļ����������������           
    //** ��    ���� ��
    //** ����ֵ����
    //** ��    �ߣ� ����
    //** �������ڣ� 2012-04-16
    //**********************************************************************************
    virtual GeometryList& read(ifstream& f);

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
    virtual void writeObject(ofstream & f,Buffer& buf);


    //********************************************************************************** 
    //** �������ƣ� writeFileHeader
    //** ���������� Ϊ�����������ļ�����ļ�ͷ
    //** ��    �룺 f:�ļ���������������
    //** ��    ���� ��
    //** ����ֵ����
    //** ��    �ߣ� ����
    //** �������ڣ� 2012-07-27
    //**********************************************************************************
    virtual void writeFileHeader(ofstream & f);

    //********************************************************************************** 
    //** �������ƣ� setGeometryNum
    //** ���������� ���ü�����ĸ���
    //** ��    �룺 �ļ��ж�ȡҪ�صĸ���          
    //** ��    ���� ��
    //** ����ֵ����
    //** ��    �ߣ� ����
    //** �������ڣ� 2012-04-16
    //**********************************************************************************
    void  setGeometryNum(UINT unMaterialNum);


    //********************************************************************************** 
    //** �������ƣ� getGeometryNum
    //** ���������� �õ�������ĸ���
    //** ��    �룺 ��          
    //** ��    ���� ��
    //** ����ֵ��Ҫ�صĸ���
    //** ��    �ߣ� ����
    //** �������ڣ� 2012-04-16
    //**********************************************************************************
    UINT getGeometryNum() const;
    void setFileName(string filename);
    string getFileName();
    void Flush();
    
private:
 
    GeometrySetFileHeader m_GeometrySetFileHeader;//�ļ�ͷ
    GeometrySetFileBody  m_GeometrySetFileBody;//�ļ���
	NewGeometrySetFileBody m_newGeometrySetFileBody;
    UINT m_unGeometryNum;//���������
    string m_strFileName;//�ļ�����
    size_t m_FileSize;//�ļ���С
    Buffer m_ReadBuf;//���ļ���������С
    Buffer m_WriteBuf;//д�ļ���������С
    ObjectSizeList m_objSizeList;//�����size�б�
	char* m_pGeometry;
	int m_nMemGeometryMax;
public:
    void setMemGeometryMax(int MemMax);

	//void  setMemGeometry();
	bool  setMemGeometry();

    void  deleteMemGeometry();

	void  setMemGeometryClear();

	GeometryList& getGeometryList();
	//********************************************************************************** 
    //** �������ƣ� getFileSize
    //** ���������� �õ��ļ���С
    //** ��    �룺 ��         
    //** ��    ���� ��
    //** ����ֵ���ļ���С
    //** ��    �ߣ� �
    //** �������ڣ� 2012-04-14
    //**********************************************************************************
	size_t getFileSize();

    //********************************************************************************** 
    //** �������ƣ� getObjOffset
    //** ���������� �õ�����ƫ����
    //** ��    �룺 GeoID:����ID��
    //** ��    ���� ��
    //** ����ֵ��ָ�����ε�ƫ����
    //** ��    �ߣ� ����
    //** �������ڣ� 2012-07-04
    //**********************************************************************************
   
    int getObjOffset(UINT64 nGeoID);
	NewGeometryList& CGeometrySetFile:: readnew(ifstream& f);
	NewGeometryList& getNewGeometryList();
};
