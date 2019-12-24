#include "DistanceLoD.h"
#include <osg/CullStack>
#include "OsgCoreSingleton.h"
#include <algorithm>
#include <osgEarthAnnotation/GeoPositionNode>
#include "globe/GGEarthManipulator.h"

namespace osg
{
	// �̳�lod ����lod�ķ�Χ�������������ľ���
	DistanceLOD::DistanceLOD(DistanceLODMODE lodModel ):osg::LOD(),
		m_LodMode(lodModel)
	{
		m_isVisible = true;
	}
	DistanceLOD::~DistanceLOD()
	{
	}
	void DistanceLOD::traverse(NodeVisitor & nv)
	{
		switch (nv.getTraversalMode())
		{
		case(NodeVisitor::TRAVERSE_ALL_CHILDREN):
			std::for_each(_children.begin(), _children.end(), NodeAcceptOp(nv));
			break;
		case(NodeVisitor::TRAVERSE_ACTIVE_CHILDREN):
		{
			if (!m_isVisible)
				break;
			float required_range = 0;
			osg::CullStack* cullStack = dynamic_cast<osg::CullStack*>(&nv);
			if (_rangeMode == DISTANCE_FROM_EYE_POINT)
			{
				// lod ���뵽�����
				required_range = (float)(GLOBE_NAME::OsgCoreSingleton::Instance()->GGEarthManipulator()->getDistance());// nv.getDistanceToViewPoint(getCenter(), true);
			}
			else
			{
				
				if (cullStack && cullStack->getLODScale())
				{
					required_range = cullStack->clampedPixelSize(getBound()) / cullStack->getLODScale();
				}
				else
				{
					// fallback to selecting the highest res tile by
					// finding out the max range
					for (unsigned int i = 0; i<_rangeList.size(); ++i)
					{
						required_range = osg::maximum(required_range, _rangeList[i].first);
					}
				}
			}

			unsigned int numChildren = _children.size();
			if (_rangeList.size()<numChildren) numChildren = _rangeList.size();

			for (unsigned int i = 0; i<numChildren; ++i)
			{
				if (_rangeList[i].first > required_range || required_range > _rangeList[i].second)
				{
					continue;
				}
				//���������ӵ��ֱ�ӿɼ���required_range�����������ĸ߶�
				if (cullStack&& required_range < 4900&& !_children[i]->getBound().contains(cullStack->getViewPointLocal()))
				{	
					float range = nv.getDistanceToViewPoint(_children[i]->getBound().center(), true)-_children[i]->getBound().radius();
					//���Ƶ㷶Χ���ӵ�ľ�����ڸ߶ȵ�1.5���Ͳ�����ʾ
					if (range > 1.5*required_range)
						continue;
				}
				if (m_LodMode == DISTANCECHILD )
				{
					float range= nv.getDistanceToViewPoint(_children[i]->getBound().center(), true);
					if(range >= _rangeList[i].first && range<_rangeList[i].second)
						_children[i]->accept(nv);
				}
				else {
					_children[i]->accept(nv);
				}
			}
			break;
		}
		default:
			break;
		}
	}
	bool DistanceLOD::Visible()
	{
		return m_isVisible;
	}
	void DistanceLOD::Visible(bool visible)
	{
		m_isVisible = visible;
	}
}