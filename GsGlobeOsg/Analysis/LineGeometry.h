#pragma once
#include <osg/Geometry>
#include "utility.h"
GLOBE_NS
class AnimatorAction;
GLOBE_ENDNS
namespace osg {

	class LineGeometry :public Geometry
	{
	public:
		LineGeometry();
		// �ߵĻ��ģʽ
		LineGeometry(float width,float imageH,osg::Image* lineImage,int mixMod, int textureType = 3);
		/** Copy constructor using CopyOp to manage deep vs shallow copy. */
		LineGeometry(const LineGeometry& geometry, const CopyOp& copyop = CopyOp::SHALLOW_COPY);
		//
		virtual void drawImplementation(RenderInfo& renderInfo) const;
		void SetLineLength(double length);
		void SetLineShape(osg::Array* vertexPoints, osg::Array* vertexDir, osg::Array* textcoord, osg::UShortArray* trangles);
		// �ߵ����ŵ�ϵ��
		void SetLineScale(float lineScale);
		float GetLineScale();
		float getLineWidth();//��ȡ�ߵĿ��
		void setLineWidth(float w);
		float getLineImageHeight();//�ߵ���ͼ����
		void setLineColor(const osg::Vec4& color);
		osg::Vec4 getLineColor();

		float getFixLod();
		void setFixLod(float fixLod);

		void setAnimatorAction(GLOBE_NAME::AnimatorAction* animatorAction);
		GLOBE_NAME::AnimatorAction* getAnimatorAction();

	protected:
		void BuildStats(int mixMod);
	protected:
		float m_lineWidth;
		float m_ImageHeigth;
		float m_LineWidthScale;
		float m_lineLenght;//�ߵ��ܳ���
		double m_LinePics;//
		float m_FixLod;//�̶���ʾ
		osg::ref_ptr<Image> m_lineImage;
		osg::StateSet * m_CurrStateSet;
		osg::ref_ptr<osg::Uniform> m_uniWidth;
		osg::ref_ptr<osg::Uniform> m_uniTextCoord;
		osg::ref_ptr<osg::Uniform> m_uniColor;//��ɫ�ı���
		osg::ref_ptr<osg::Uniform> m_uPrive;// �����ߵİٷֱ�
		float m_lineColorAphla;
		int m_TextureType;
		UTILITY_NAME::GsSmarterPtr<GLOBE_NAME::AnimatorAction> m_ptrAnimatorAction;
	};
}

