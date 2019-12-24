/*
WorkSpaceWritter�������ж���������ݽṹ����Щ�ṹ��Ӧ�����ļ���֯��ʽ�����ڲ�ͬ��ʽ�ļ����Լ�����֯��ʽ�����Բ�ͬ�����ඨ����Բ�ͬ�����ݽṹ��
WorkSpaceReader��Ϊ������࣬���ͨ�õ����ݽṹ����Щ�ṹ��Ӧ�����ڴ������ݵ���֯��ʽ����ͬ��ʽ���ļ����ݽ������Ϊͬ�������ݸ�ʽ��������Щ���ݽṹ�����ڳ�������С�
*/

#pragma once

#include <list>
#include <vector>
#include <map>
#include <string>

#include "osgEarth\XmlUtils"
#include "osgEarth\config"

/*
�����ռ��ļ���ȡ
*/
class WorkSpaceReader
{
public:
	WorkSpaceReader(const char *FilePath);
	virtual ~WorkSpaceReader(void);

	void ReadTerrainFileList(std::list<std::string> &listFiles, int nScreenIndex);
	void ReadImageFileList(std::list<std::string> &listFiles, int nScreenIndex);
	void ReadModelFileList(std::list<std::string> &listFiles, int nScreenIndex);
	void ReadVectorFileList(std::list<std::string> &listFiles, int nScreenIndex);
	//��б
	void ReadObliqueFileList(std::list<std::string> &listFiles, int nScreenIndex);
	//����
	void ReadPipeFileList(std::list<std::string> &listFiles, int nScreenIndex);
	//����
	void ReadPlaceNameFileList(std::list<std::string> &listFiles, int nScreenIndex);

	int ScreenNum();

	std::string ReadValue(std::string strKey);

protected:

	std::map<std::string, std::string> m_mapKeyValue;
	std::map<int, std::list<std::string>> m_listTerrainFileList;
	std::map<int, std::list<std::string>> m_listImageFileList;
	std::map<int, std::list<std::string>> m_listModelFileList;
	std::map<int, std::list<std::string>> m_listVectorFileList;
	std::map<int, std::list<std::string>> m_listObliqueFileList;
	std::map<int, std::list<std::string>> m_listPipeFileList;
	std::map<int, std::list<std::string>> m_listPlaceNameFileList;
	std::map<std::string, std::string>    m_makKV;
	int m_nScreenNum;
};

/*
xml��ʽ�����ռ��ļ���ȡ
*/
class XmlWSReader : public WorkSpaceReader
{
public:
	XmlWSReader(const char *FilePath);
	virtual ~XmlWSReader(void);
protected:
	virtual void Parse(const char *FilePath);
};


/*
�����ռ��ļ�д��
*/
class WorkSpaceWritter
{
public:
	WorkSpaceWritter();
	virtual ~WorkSpaceWritter(void);

	virtual void WriteTerrainFile(std::string strFile, int nScreenIndex) = 0;
	virtual void WriteImageFile(std::string strFile, int nScreenIndex) = 0;
	virtual void WriteModelFile(std::string strFile, int nScreenIndex) = 0;
	virtual void WriteVectorFile(std::string strFile, int nScreenIndex) = 0;
	virtual void WriteObliqueFile(std::string strFile, int nScreenIndex) = 0;
	virtual void WritePipeFile(std::string strFile, int nScreenIndex) = 0;
	virtual void WritePlaceNameFile(std::string strFile, int nScreenIndex) = 0;

	virtual void WriteValue(std::string strKey, std::string strValue) = 0;
	virtual void Save(const char *FilePath) = 0;
	virtual void Clear() = 0;

	virtual void ScerrnNum(int nScerrnNum);
	std::string FilePath(){return m_strPath;}

protected:
	int m_nScreenNum;
	std::string m_strPath;
};

/*
xml��ʽ�����ռ��ļ�д��
*/
class XmlWSWritter : public WorkSpaceWritter
{
public:
	XmlWSWritter();
	virtual ~XmlWSWritter(void);

	virtual void WriteTerrainFile(std::string strFile, int nScreenIndex);
	virtual void WriteImageFile(std::string strFile, int nScreenIndex);
	virtual void WriteModelFile(std::string strFile, int nScreenIndex);
	virtual void WriteVectorFile(std::string strFile, int nScreenIndex);
	virtual void WriteObliqueFile(std::string strFile, int nScreenIndex);
	virtual void WritePipeFile(std::string strFile, int nScreenIndex);
	virtual void WritePlaceNameFile(std::string strFile, int nScreenIndex);

	virtual void WriteValue(std::string strKey, std::string strValue);
	virtual void ScerrnNum(int nScerrnNum);
	virtual void Save(const char *FilePath);
	virtual void Clear();
protected:
	osgEarth::XmlDocument m_xmlDoc;
	std::map<int, std::string> m_listTerrainFileList;
	std::map<int, std::string> m_listImageFileList;
	std::map<int, std::string> m_listModelFileList;
	std::map<int, std::string> m_listVectorFileList;
	std::map<int, std::string> m_listObliqueFileList;
	std::map<int, std::string> m_listPipeFileList;
	std::map<int, std::string> m_listPlaceNameFileList;

	std::map<std::string, std::string> m_makKV;
};