#pragma once
#include "preconfig.h" 
#include "object.h"
#include "any.h"
#include "configuration.h"
#include "timer.h"
UTILITY_NS


/// \brief �����л������೧
class GS_API GsSerializebleClassFactory :public GsRefObject
{
protected:
	GsSerializebleClassFactory();
public:
	virtual ~GsSerializebleClassFactory();

	/// \brief �������ʵ��
	/// \details  ���صĶ�������ü���Ϊ1
	virtual GsRefObject* CreateInstance(const char* className) = 0;
};
/// \brief GsSerializebleClassFactoryPtr
GS_SMARTER_PTR(GsSerializebleClassFactory);


/// \brief ����������л������೧���ϳ�һ������
class GS_API GsMultiSerializebleClassFactory :public GsSerializebleClassFactory
{ 
	GsVector<GsSerializebleClassFactoryPtr> m_AllFactory;
public:
	GsMultiSerializebleClassFactory();
	virtual ~GsMultiSerializebleClassFactory();
	
	/// \brief ����һ���೧
	void Add(GsSerializebleClassFactory* fac);
	/// \brief ��������೧
	void Clear();
	/// \brief ����
	int Count();
	/// \brief �Ƴ�һ��
	GsSerializebleClassFactoryPtr Remove(int i);

	/// \brief �������ʵ��
	/// \details  ���صĶ�������ü���Ϊ1
	virtual GsRefObject* CreateInstance(const char* className);

};
/// \brief GsMultiSerializebleClassFactoryPtr
GS_SMARTER_PTR(GsMultiSerializebleClassFactory);

/// \brief ���л�������ӿ�
class GS_API GsSerializeStream :public GsRefObject
{
protected:
	GsSerializebleClassFactoryPtr m_ptrClassFactory;
	GsRefObject* CreateInstance(const char* className);

	GsSerializeStream(); 
public:
	/// \brief �û�ʵ���Զ��������೧
	GsSerializebleClassFactory* ClassFactory();
	void ClassFactory(GsSerializebleClassFactory* fac);

	/// \brief ��ʼһ������洢����Ҫ����EndObject���
	virtual bool BeginObject(const char* name, const char* type) = 0;

	/// \brief ����һ������洢
	virtual bool EndObject( ) = 0;


	/// \brief �����������ƻ�ȡһ�����Ե�����
	virtual GsVarType PropertyType(const char* name) = 0;
	/// \brief �ж�һ�������Ƿ����
	virtual bool Exists(const char* name) = 0;

	/// \brief ������������
	/// \param const GsString& Name ��������
	/// \param GsAny * Value ����ֵ
	///\return �����Ƿ�ɹ�
	virtual bool SaveProperty(const char * strName,const GsAny & Value);
	
	/// \brief ��ȡ��������
	/// \param const GsString& Name ��������
	/// \param GsAny * DefaultValue Ĭ��ֵ
	///\return ����ֵ
	virtual GsAny LoadProperty(const char *  strName, const GsAny& DefaultValue);

	/// \brief ����ָ��key��ָ���ַ���ֵ
	/// \param const char* key  ��������
	/// \param const char* strValue ����ֵ
	virtual void Save(const char* key,const char* strValue) = 0;


	/// \brief ����ָ��key��ָ���ַ���ֵ
	/// \param const char* key  ��������
	/// \param const char* strValue ����ֵ
	virtual void Save(const char* key, const GsString & strValue) = 0;

	/// \brief ����ָ��key��ֵ32λ����ֵ
	/// \param const char* key  ��������
	/// \param  int value ����ֵ
	virtual void Save(const char* key,int value) = 0;


	/// \brief ����ָ��key���޷���32λ����ֵ
	/// \param const char* key  ��������
	/// \param  unsigned int value����ֵ
	virtual void Save(const char* key,unsigned int value) = 0;

	/// \brief ����ָ��key��64λ����ֵ
	/// \param const char* key  ��������
	/// \param  long long value ����ֵ
	virtual void Save(const char* key,long long value)= 0;

	/// \brief ����ָ��key���޷���64λ����ֵ
	/// \param const char* key  ��������
	/// \param  unsigned long long ����ֵ
	virtual void Save(const char* key,unsigned long long value) = 0;
	/// \brief ����ָ��key��boolֵ
	/// \param const char* key  ��������
	/// \param  bool value ֵ
	virtual void Save(const char* key,bool value) = 0;
	/// \brief ����ָ��key��floatֵ
	/// \param const char* key  ��������
	/// \param  float value ֵ
	virtual void Save(const char* key,float value) = 0;

	/// \brief ����ָ��key��doubleֵ
	/// \param const char* key  ��������
	/// \param  double value ֵ
	virtual void Save(const char* key,double value) = 0;

	/// \brief ����ָ��key��GsRefObjectֵ
	/// \param const char* key  ��������
	/// \param  GsRefObject* value ֵ
	virtual bool Save(const char* key, GsRefObject* value) = 0;

	/// \brief �洢ʱ��
	/// \param const char* key  ��������
	/// \param  GsDateTime ʱ��
	virtual void Save(const char* key, const GsDateTime& time) = 0;


	/// \brief ����ָ��key�Ķ�����ֵ,�����Ƹ��ݲ�ͬ���͵���,����ʵ�ֲ�ͬ�ı�﷽ʽ,
	/// \brief �����Ľ�������תΪ base64����洢��xml,json, ������geometry ����תΪgeojson����gml,wkt��
	/// \param const char* key  ��������
	/// \param  GsAny * value ֵ
	virtual void Save(const char* key, const unsigned char* blob, int nlen) = 0;
	
	/// \brief �洢�Զ�������
	/// \param key  ��������
	/// \param type  ������������
	/// \param value ����ֵ
	virtual void Save(const char* key, const char* type, const char* value) = 0;


	/// \brief ����key��ȡ�ַ���
	/// \param const char* key ��ֵ
	/// \param const char* strDefaultValue Ĭ��ֵ
	///\return GsString �����ַ���
	virtual GsString LoadStringValue(const char* key, const char* strDefaultValue) = 0;
	/// \brief ����key��ȡ�ַ���
	/// \param const char* key ��ֵ
	/// \param const char* strDefaultValue Ĭ��ֵ
	///\return GsString �����ַ���
	virtual GsString LoadStringValue(const char* key, const GsString& strDefaultValue);

	/// \brief ����key��ȡintֵ
	/// \param const char* key ��ֵ
	/// \param int intDefaultvalue Ĭ��ֵ
	///\return int ����int
	virtual int LoadIntValue(const char* key, int intDefaultvalue) = 0;

	/// \brief ����key��ȡunsigned intֵ
	/// \param const char* key ��ֵ
	/// \param unsigned int uintDefaultvalue Ĭ��ֵ
	///\return int ����unsigned int
	virtual unsigned int  LoadUIntValue(const char* key, unsigned int uintDefaultvalue) = 0;


	/// \brief ����key��ȡlong longֵ
	/// \param const char* key ��ֵ
	/// \param long long llDefaultvalue Ĭ��ֵ
	///\return long long ����long long
	virtual long long LoadInt64Value(const char* key, long long llDefaultvalue) = 0;

	/// \brief ����key��ȡunsigned long longֵ
	/// \param const char* key ��ֵ
	/// \param unsigned long long llDefaultvalue Ĭ��ֵ
	///\return unsigned long long ����unsigned long long
	virtual unsigned long long LoadUInt64Value(const char* key, unsigned long long ullDefaultvalue) = 0;

	/// \brief ����key��ȡboolֵ
	/// \param const char* key ��ֵ
	/// \param bool bDefaultValue Ĭ��ֵ
	///\return bool ����bool
	virtual bool LoadBoolValue(const char* key, bool bDefaultValue) = 0;

	/// \brief ����key��ȡfloat ֵ
	/// \param const char* key ��ֵ
	/// \param float fDefaultValue Ĭ��ֵ
	///\return float ����float
	virtual	float LoadFloatValue(const char* key, float fDefaultValue) = 0;

	/// \brief ����key��ȡ double  ֵ
	/// \param const char* key ��ֵ
	/// \param  double dblDefaultValueĬ��ֵ
	///\return double ���� double 
	virtual double LoadDoubleValue(const char* key, double dblDefaultValue) = 0;
	
	/// \brief ����key��ȡ Time ֵ
	/// \param const char* key ��ֵ
	/// \param  const GsDateTime& defaultValueeĬ��ֵ
	///\return GsDateTime ���� ʱ��
	virtual GsDateTime LoadDateTimeValue(const char* key, const GsDateTime& defaultValue) = 0;

	/// \brief ����key��ȡ double  ֵ
	/// \param const char* key ��ֵ
	/// \param  GsRefObject* bDefaultValueĬ��ֵ
	///\return GsRefObject* ���� GsRefObject* 
	virtual GsRefObject* LoadObjectValue(const char* key) = 0;

	/// \brief ����key��ȡ double  ֵ
	/// \param const char* key ��ֵ
	/// \param  GsRefObject* bDefaultValueĬ��ֵ
	///\return GsRefObject* ���� GsRefObject* 
	template<class T>
	GsSmarterPtr<T>  LoadObjectValueT(const char* key)
	{
		GsRefObject* ref = LoadObjectValue(key);
		if (!ref) return 0;
		T* o = dynamic_cast<T*>(ref);
		if (!o)
		{
			ref->Release();
			return 0;
		}
		return GsSmarterPtr<T>(o, false);
	}

	/// \brief ����key��ȡ GsAny  ֵ
	/// \param const char* key ��ֵ
	/// \param  GsAny* anyDefaultBlobĬ��ֵ
	///\return GsAny ���� GsAny 
	virtual GsAny LoadBlobValue(const char* key, const GsAny& anyDefaultBlob) = 0;

	/// \brief �����û��Զ������͵�����
	/// \param  key ��ֵ
	/// \param type ������������
	/// \return �������ݵ�ֵ
	virtual GsString LoadCustomValue(const char* key, GsString& type) = 0;

};
GS_SMARTER_PTR(GsSerializeStream);
/// \brief XML���л�����
class GS_API GsXMLSerializeStream :public GsSerializeStream
{
	Utility::GsStack<GsConfig> m_StackConfig;
public:
	using GsSerializeStream::LoadStringValue;

	/// \brief xml���л����캯��
	/// \param const char* strXML xml�ַ���
	GsXMLSerializeStream(const char* strXML=NULL);
	/// \brief ��ȡ���л���XML
	///\return GsString �ַ���
	virtual GsString XML();
	/// \brief �������л��ַ���
	/// \param const GsString& strXml �ַ���
	///\return void
	virtual void XML(const char * strXml);

	/// \brief ��ʼһ������洢����Ҫ����EndObject���
	virtual bool BeginObject(const char* name, const char* type) ;

	/// \brief ����һ������洢
	virtual bool EndObject( );


	/// \brief �����������ƻ�ȡһ�����Ե�����
	virtual GsVarType PropertyType(const char* name);
	/// \brief �ж�һ�������Ƿ����
	virtual bool Exists(const char* name);
	/// \brief �洢�Զ�������
	/// \param key  ��������
	/// \param type  ������������
	/// \param value ����ֵ
	virtual void Save(const char* key, const char* type, const char* value);
	/// \brief �����û��Զ������͵�����
	/// \param  key ��ֵ
	/// \param type ������������
	/// \return �������ݵ�ֵ
	virtual GsString LoadCustomValue(const char* key, GsString& type);



	/// \brief ����ָ��key��ָ���ַ���ֵ
	/// \param const char* key  ��������
	/// \param const char* strValue ����ֵ
	virtual void Save(const char* key, const char* strValue) ;


	/// \brief ����ָ��key��ָ���ַ���ֵ
	/// \param const char* key  ��������
	/// \param const char* strValue ����ֵ
	virtual void Save(const char* key, const GsString & strValue) ;

	/// \brief ����ָ��key��ֵ32λ����ֵ
	/// \param const char* key  ��������
	/// \param  int value ����ֵ
	virtual void Save(const char* key, int value) ;


	/// \brief ����ָ��key���޷���32λ����ֵ
	/// \param const char* key  ��������
	/// \param  unsigned int value����ֵ
	virtual void Save(const char* key, unsigned int value) ;

	/// \brief ����ָ��key��64λ����ֵ
	/// \param const char* key  ��������
	/// \param  long long value ����ֵ
	virtual void Save(const char* key, long long value) ;

	/// \brief ����ָ��key���޷���64λ����ֵ
	/// \param const char* key  ��������
	/// \param  unsigned long long ����ֵ
	virtual void Save(const char* key, unsigned long long value);
	/// \brief ����ָ��key��boolֵ
	/// \param const char* key  ��������
	/// \param  bool value ֵ
	virtual void Save(const char* key, bool value) ;
	/// \brief ����ָ��key��floatֵ
	/// \param const char* key  ��������
	/// \param  float value ֵ
	virtual void Save(const char* key, float value);

	/// \brief ����ָ��key��doubleֵ
	/// \param const char* key  ��������
	/// \param  double value ֵ
	virtual void Save(const char* key, double value);

	/// \brief ����ָ��key��GsRefObjectֵ
	/// \param const char* key  ��������
	/// \param  GsRefObject* value ֵ
	virtual bool Save(const char* key, GsRefObject* value);

	/// \brief �洢ʱ��
	/// \param const char* key  ��������
	/// \param  GsDateTime ʱ��
	virtual void Save(const char* key, const GsDateTime& time);


	/// \brief ����ָ��key�Ķ�����ֵ,�����Ƹ��ݲ�ͬ���͵���,����ʵ�ֲ�ͬ�ı�﷽ʽ,
	/// \brief �����Ľ�������תΪ base64����洢��xml,json, ������geometry ����תΪgeojson����gml,wkt��
	/// \param const char* key  ��������
	/// \param  GsAny * value ֵ
	virtual void Save(const char* key, const unsigned char* blob, int nlen);

	/// \brief ����key��ȡ�ַ���
	/// \param const char* key ��ֵ
	/// \param const char* strDefaultValue Ĭ��ֵ
	///\return GsString �����ַ���
	virtual GsString LoadStringValue(const char* key, const char* strDefaultValue);

	/// \brief ����key��ȡintֵ
	/// \param const char* key ��ֵ
	/// \param int intDefaultvalue Ĭ��ֵ
	///\return int ����int
	virtual int LoadIntValue(const char* key, int intDefaultvalue);

	/// \brief ����key��ȡunsigned intֵ
	/// \param const char* key ��ֵ
	/// \param unsigned int uintDefaultvalue Ĭ��ֵ
	///\return int ����unsigned int
	virtual unsigned int  LoadUIntValue(const char* key, unsigned int uintDefaultvalue);


	/// \brief ����key��ȡlong longֵ
	/// \param const char* key ��ֵ
	/// \param long long llDefaultvalue Ĭ��ֵ
	///\return long long ����long long
	virtual long long LoadInt64Value(const char* key, long long llDefaultvalue);

	/// \brief ����key��ȡunsigned long longֵ
	/// \param const char* key ��ֵ
	/// \param unsigned long long llDefaultvalue Ĭ��ֵ
	///\return unsigned long long ����unsigned long long
	virtual unsigned long long LoadUInt64Value(const char* key, unsigned long long ullDefaultvalue);

	/// \brief ����key��ȡboolֵ
	/// \param const char* key ��ֵ
	/// \param bool bDefaultValue Ĭ��ֵ
	///\return bool ����bool
	virtual bool LoadBoolValue(const char* key, bool bDefaultValue);

	/// \brief ����key��ȡfloat ֵ
	/// \param const char* key ��ֵ
	/// \param float fDefaultValue Ĭ��ֵ
	///\return float ����float
	virtual	float LoadFloatValue(const char* key, float fDefaultValue);

	/// \brief ����key��ȡ double  ֵ
	/// \param const char* key ��ֵ
	/// \param  double dblDefaultValueĬ��ֵ
	///\return double ���� double 
	virtual double LoadDoubleValue(const char* key, double dblDefaultValue);

	/// \brief ����key��ȡ Time ֵ
	/// \param const char* key ��ֵ
	/// \param  const GsDateTime& defaultValueeĬ��ֵ
	///\return GsDateTime ���� ʱ��
	virtual GsDateTime LoadDateTimeValue(const char* key, const GsDateTime& defaultValue);

	/// \brief ����key��ȡ double  ֵ
	/// \param const char* key ��ֵ
	/// \param  GsRefObject* bDefaultValueĬ��ֵ
	///\return GsRefObject* ���� GsRefObject* 
	virtual GsRefObject* LoadObjectValue(const char* key);

	/// \brief ����key��ȡ GsAny  ֵ
	/// \param const char* key ��ֵ
	/// \param  GsAny* anyDefaultBlobĬ��ֵ
	///\return GsAny ���� GsAny 
	virtual GsAny LoadBlobValue(const char* key, const GsAny& anyDefaultBlob);

};
GS_SMARTER_PTR(GsXMLSerializeStream);

/// \brief ���л��ӿ���
class GS_API GsSerialize
{
public:
	~GsSerialize() {}
	/// \brief �������л�Ϊ��
	/// \param GsSerializeStream * pSerStream
	///\return �����Ƿ�ɹ�
	virtual bool Serialize(GsSerializeStream * pSerStream) = 0;
	/// \brief �����л�Ϊ����
	/// \param GsSerializeStream * pSerStream
	///\return �����Ƿ�ɹ�
	virtual bool DeSerialize(GsSerializeStream * pSerStream) = 0;

	/// \brief ��������
	virtual GsString ClassName() = 0;

};

UTILITY_ENDNS