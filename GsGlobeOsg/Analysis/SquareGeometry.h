#pragma once
#include <osg/Geometry>
#include "utility.h"

GLOBE_NS
class AnimatorAction;
GLOBE_ENDNS

namespace osg
{
	//
	class SquareGeometry :public osg::Geometry
	{
	public:
		// ��ɫģʽ
		SquareGeometry(float w, float h);
		// ͼƬģʽ
		SquareGeometry(float w, float h, osg::Image* lineImage,int mode=2);
		~SquareGeometry();
		
		virtual void drawImplementation(RenderInfo& renderInfo) const;
		//������ɫ
		void setColor(const osg::Vec4& color);
		// ��ȡ��ɫ
		osg::Vec4 getColor();
		float getWidth();
		float getHeight();
		//���ö������Բ���
		void setAnimatorAction(GLOBE_NAME::AnimatorAction* animatorAction);
		// ��ȡ�������Բ���
		GLOBE_NAME::AnimatorAction* getAnimatorAction();
	protected:
		void build();

	protected:
		float m_width;
		float m_height;
		osg::ref_ptr<Image> m_Image;
		osg::ref_ptr<osg::Uniform> m_uniColor;//��ɫ�ı���
		osg::ref_ptr<osg::Uniform> m_uCirle;//�뾶
		osg::ref_ptr<osg::Uniform> m_uniRota;// ƽ����ת�����Ų���
		int m_SquareMode;// ģʽ Բ����ɢЧ�����㷢��Ч����ԭʼͼƬ��Ⱦ
		float m_lineColorAphla;
		UTILITY_NAME::GsSmarterPtr<GLOBE_NAME::AnimatorAction> m_ptrAnimatorAction;
	};
}


