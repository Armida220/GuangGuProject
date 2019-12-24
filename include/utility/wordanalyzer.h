#pragma once
#include "preconfig.h" 
#include "object.h"
#include "stringhelp.h"

UTILITY_NS
/// \brief �ַ��ִ���
class GS_API GsWordAnalyzer:public GsRefObject
{
public:
	GsWordAnalyzer(void);
	~GsWordAnalyzer(void);

	/// \brief ִ�зִʲ���
	/// \param strText �����ַ���
	/// \param vecSubStr �ִʺ�����ַ���
	virtual bool Analyse(const char* strText, GsVector<GsString>& vecSubStr);

	/// \brief ִ�зִʲ���
	/// \param strText �����ַ���
	/// \param vecSubStr �ִʺ�����ַ���
	virtual bool Analyse(const wchar_t* strText, GsVector<GsWString>& vecSubStr);
};
GS_SMARTER_PTR(GsWordAnalyzer);

/// \brief �򵥹���ִ���
class GS_API GsSimpleWordAnalyzer : public GsWordAnalyzer
{
public:
	GsSimpleWordAnalyzer(void);
	~GsSimpleWordAnalyzer(void);

	/// \brief ִ�зִʲ���
	/// \param strText �����ַ���
	/// \param vecSubStr �ִʺ�����ַ���
	virtual bool Analyse(const char* strText, GsVector<GsString>& vecSubStr);

	/// \brief ִ�зִʲ���
	/// \param strText �����ַ���
	/// \param vecSubStr �ִʺ�����ַ���
	virtual bool Analyse(const wchar_t* strText, GsVector<GsWString>& vecSubStr);

	/// \brief ���öԳ��ַ�����
	/// \detail �������ַ�������ʽ����<>[]{}()������������������������''
	void PairChars(const char* str);

	/// \brief ���������ַ�����
	/// \detail �������ַ�������ʽ����-#
	void LinkChars(const char* str);

public:
	// ִ�з�������
	bool DoAnalyseProcess(const wchar_t* strIn, wchar_t* strOut);
private:
	// �Գ��ַ�
	GsWString m_strPairs;
	// �����ַ�
	GsWString m_strLineChars;
};
GS_SMARTER_PTR(GsSimpleWordAnalyzer);

UTILITY_ENDNS