#pragma once
#include <utility.h>
#include <Layer.h>

GLOBE_NS

class GS_API LayerBox :public GeoStar::Utility::GsRefObject
{
public:
	LayerBox();

	//���һ��ͼ��
	void AddLayer(Layer* layer);
	//�Ƴ�һ��ͼ��
	void RemoveLayer(Layer* layer);
	//�Ƴ�����ͼ��
	void RemoveAllLayer();
	//�Ƴ�����Ӱ��ͼ��
	void RemoveAllImageLayer();
	//�Ƴ����е���ͼ��
	void RemoveAllTerrainLayer();
	//ͨ��ID��ͼ��
	Layer* LayerByUID(int nUID);
	//ͨ��index��Ӱ��ͼ��
	Layer* ImageAt(int nIndex);
	//Ӱ��ͼ����
	int ImageCount();
	//����ͼ����
	int TerrainCount();

	void MoveTo(Layer* layer,int nIndex);

	virtual ~LayerBox();

private:
	std::vector<LayerPtr> m_vecLayer;
	//std::vector<LayerPtr> m_vecTerrainLayer;
	//std::vector<LayerPtr> m_vecPlaceNameLayer;
};

GS_SMARTER_PTR(LayerBox);

GLOBE_ENDNS
