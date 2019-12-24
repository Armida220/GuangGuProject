
#include "Buffer.h"

Buffer::Buffer(){//Ĭ�Ϲ��캯��
	_data=0;
	_size=0;
	_alloc=false;
	_curpos=0;
}
void Buffer::clear(){//���Buffer
	if(_alloc && _data){
		delete  [] ((unsigned char*)_data);
	}
	_data = 0;
	_size=0;
	_alloc=false;
	_curpos=0;
}
Buffer::~Buffer(){//Ĭ����������
	clear();
}
Buffer::Buffer(void * d,size_t s,bool b_alloc){//���캯�������b_allocΪ�棬���������һ���СΪs���ڴ�飬������d�����ݣ���֮����ָ��d
	_size=s;
	_alloc=b_alloc;
	if(_alloc){
		_data = new char[_size];
		memcpy(_data,d,_size);
	}
	else{
		_data=d;
	}
	_curpos=0;
}
void Buffer::copy(const Buffer & b){//����Buffer���������b��_alloc��ԱΪ�٣��򿽱����Buffer������b����һ���ڴ�飬����Ϊ�ڴ�鿽��
	set(b._data,b._size,b._alloc);
	_curpos=0;
}
Buffer::Buffer(const Buffer & b){//�������캯��
	_data = 0;
	_size=0;
	_alloc=false;
	_curpos=0;
	copy(b);
}
Buffer Buffer::operator = (const Buffer & b){//�ȺŸ�ֵ����
	copy(b);
	return * this;
}
void Buffer::set(void * pv, size_t ss,bool b_alloc){//���û����������b_allocΪ�棬���������һ���СΪss���ڴ�飬������pv�����ݣ���֮����ָ��pv
	clear();
	_alloc = b_alloc;
	if(_alloc){
		_data = new char[ss];
		_size = ss;
		if(pv)
			memcpy(_data,pv,ss);
	}
	else{
		_data = pv;
		_size = ss;
	}
	_curpos=0;
}


void Buffer::attach(void * pv, size_t ss){
	clear();
	_data = pv;
	_size = ss;
	_alloc=true;
}
void* Buffer::detach(size_t & s){		
	s=_size;
	_alloc=false;
	void* p =_data;
	_data = 0;
	_curpos=0;
	return p;
}

void Buffer::write(size_t beginpos,void * cdata,size_t count)//��ָ����λ��beginpos�����д��count���ַ�
{
	if(beginpos+count<=_size){
		memcpy(((char*)_data)+beginpos,cdata,count);
	}
	else{
		char * p = new char [beginpos+count];
		memcpy(p,_data,beginpos);
		memcpy(p+beginpos,cdata,count);
		delete [] ((char*)_data);
		_data = p;
		_size = beginpos+count;

		// ���ڵ�����delete [] ((char*)_data); _data = p;  ��ˣ�����ڴ�����attach��ʽ�õ��ģ�
		//���ⲿ�Ĺ������޷�ʵ�����ڴ������,�����������Ĵ�������������clear���� [7-29-2010 �￨]
		_alloc = true;
	}
	_curpos = beginpos + count;
}

void Buffer::write(void * cdata, size_t count)
{
	if(_curpos+count<=_size){
		memcpy(((char*)_data)+_curpos,cdata,count);
		_curpos += count;
	}
	else{
		/**�޸�_curpos����Ϊ��ֵ[2009-09-17cuiyt]*/
		_size = _curpos+count;
		char * p = new char [_size];
		memcpy(p,_data,_curpos);
		memcpy(p+_curpos,cdata,count);
		delete [] ((char*)_data);
		_data = p;
		_curpos += count;	//_curpos���ӵ���ǰλ��[2009-09-17cuiyt]

		// ���ڵ�����delete [] ((char*)_data); _data = p;  ��ˣ�����ڴ�����attach��ʽ�õ��ģ�
		//���ⲿ�Ĺ������޷�ʵ�����ڴ������,�����������Ĵ�������������clear���� [7-29-2010 �￨]
		_alloc = true;
	}
}

bool Buffer::read(void * cdata, size_t count)
{
	if(_curpos+count<=_size){
		memcpy(cdata,((char*)_data)+_curpos,count);
		_curpos += count;
		return true;
	}
	else{
//		assert(0);
		return false;

	}
}

