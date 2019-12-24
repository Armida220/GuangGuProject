#pragma once

//#include <phonon/phonon>
//#include <qurl.h>
#include <string>
#include <map>

using namespace std;
//using namespace Phonon;

class CMediaPlayer
{
public:
	CMediaPlayer(void);
	virtual ~CMediaPlayer(void);

	void AddSource(string sKey, string MediaFile);
	
	//����
	bool PlayMedia(string strKey);
	//ֹͣ
	bool StopMedia(string strKey);
	//�Ƴ�
	bool RemoveMedia(string strKey);
	//ֱ�Ӳ���
	void DirectPlayMedia(string strFilePath);

protected:
	map<string, string> m_mapMediaSource;
};

