#pragma once
#include <utility.h>

GLOBE_NS

class Layer;
class Element;

/*�¼���������ͨ���¼���������������߳���������ݱ�������
 *Ŀǰֻ���ͼ���Element���ɰ�������
*/
class GS_API EventAdapter :public GeoStar::Utility::GsRefObject
{
public:
	EventAdapter();

	void AddLayer(Layer* ptrLayer);
	void AddElement(Element* ptrElement);

	virtual ~EventAdapter();

private:

};

GS_SMARTER_PTR(EventAdapter);

GLOBE_ENDNS
