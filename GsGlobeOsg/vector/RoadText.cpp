
#include "RoadText.h"
#include <OsgCoreSingleton.h>
#include <osgUtil/Tessellator>
#include <tool/CodeTransformHelp.h>
#include <osg/Depth>
#include <osgText/Text>
#include <OsgCoreSingleton.h>
#include <osgEarth/MapNode>
#include <LonAndLatElement.h>
#include <osgViewer/Viewer>

namespace GeoGlobe 
{

	//RoadText::RoadText(osg::Vec3d p0, osg::Vec3d p1, std::string strRoad, int nIndex, double dbSize, osg::Vec4 color, std::string strFont)
	//{
	//	m_PoseState = positive;
	//	m_DistState = Zero;
	//	m_vecStart = p0;
	//	m_vecEnd = p1;

	//	//Ҷ�ڵ�
	//	osg::ref_ptr<osg::Geode> textGeode = new osg::Geode;
	//	textGeode->addDrawable(createText(osg::Vec3(0.0f, 0.0f, 0.0f),strRoad, dbSize, color, strFont));

	//	//����Ƕ�
	//	//���ڶ�̬���ƵĻ���ֻ��Ҫ��������������Ļ�ϵ����λ�ã�pWin.x > pWin.x�����෴������aȡ��(-a)���ɣ�
	//	//������Ҫͳһ������Ļ�ڵ�Text��Ȼ��ÿ֡����һ�μ��㣬Ŀǰ�����ϲ���̫������
	//	float angle;
	//	if (p0.y() > p1.y() && p0.x() > p1.x())
	//	{
	//		angle = acos((p0.x() - p1.x()) / (p1 - p0).length());
	//	}
	//	else if (p0.y() <= p1.y() && p0.x() <= p1.x())
	//	{
	//		angle = acos((p1.x() - p0.x()) / (p1 - p0).length());
	//	}
	//	else if (p0.x() < p1.x() && p0.y() > p1.y())
	//	{
	//		angle = acos((p0.x() - p1.x()) / (p1 - p0).length()) + osg::PI;
	//	}
	//	else
	//	{
	//		angle = acos((p1.x() - p0.x()) / (p1 - p0).length()) + osg::PI;
	//	}

	//	m_Angle = angle;

	//	//��ת������ĽǶ�
	//	m_Trans = new osg::MatrixTransform();
	//	m_Trans->setMatrix(osg::Matrix::rotate(angle, 0, 0, 1));
	//	m_Trans->addChild(textGeode.get());

	//	textGeode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	//	textGeode->getOrCreateStateSet()->setAttributeAndModes(new osg::Depth(osg::Depth::ALWAYS, 0, 1, false));

	//	//ȡ����������ĵ�
	//	osg::Vec3d pC = (p1 + p0) / 2;
	//	m_vecPosition = pC;
	//	//�����ַŵ����ĵ�
	//	osg::ref_ptr<osgEarth::Util::ObjectLocatorNode> ptrLocator = new osgEarth::Util::ObjectLocatorNode(GLOBE_NAME::OsgCoreSingleton::Instance()->MapNode()->getMap());
	//	ptrLocator->addChild(m_Trans);
	//	ptrLocator->getLocator()->setPosition(pC);

	//	osg::ref_ptr<osg::LOD> ptrLOD = new osg::LOD();
	//	if (nIndex%3 == 0)
	//	{
	//		ptrLOD->addChild(ptrLocator, 0, 800);
	//	}
	//	else if(nIndex % 3 == 1)
	//	{
	//		ptrLOD->addChild(ptrLocator, 0, 1600);
	//	}
	//	else if(nIndex % 3 == 2)
	//	{
	//		ptrLOD->addChild(ptrLocator, 0, 2500);
	//	}

	//	GLOBE_NAME::OsgCoreSingleton::Instance()->MapNode()->addChild(ptrLOD);
	//	//GLOBE_NAME::OsgCoreSingleton::Instance()->LonAndLat()->Change().Add(this, &RoadText::OnChange);
	//}
	//�������һ����
	double g_length_level_4 = 150;
	double g_length_level_3 = g_length_level_4*2;
	double g_length_level_2 = g_length_level_3*2;
	double g_length_level_1 = g_length_level_2*2;
	double g_length_level_0 = g_length_level_1*2;
	RoadText::RoadText(double& fLineLength,osg::Vec3d p0, osg::Vec3d p1, const std::vector<osg::ref_ptr<osg::Geode> > &vTextGeode)
	{		
		m_PoseState = positive;
		m_DistState = Zero;
		m_vecStart = p0;
		m_vecEnd = p1;
		m_bCheck = false;
		

		//����Ƕ�
		//���ڶ�̬���ƵĻ���ֻ��Ҫ��������������Ļ�ϵ����λ�ã�pWin.x > pWin.x�����෴������aȡ��(-a)���ɣ�
		//������Ҫͳһ������Ļ�ڵ�Text��Ȼ��ÿ֡����һ�μ��㣬Ŀǰ�����ϲ���̫������
		float angle;
		if (p0.y() > p1.y() && p0.x() > p1.x())
		{
			angle = acos((p0.x() - p1.x()) / (p1 - p0).length());
		}
		else if (p0.y() <= p1.y() && p0.x() <= p1.x())
		{
			angle = acos((p1.x() - p0.x()) / (p1 - p0).length());
		}
		else if (p0.x() < p1.x() && p0.y() > p1.y())
		{
			angle = acos((p0.x() - p1.x()) / (p1 - p0).length()) + osg::PI;
		}
		else
		{
			angle = acos((p1.x() - p0.x()) / (p1 - p0).length()) + osg::PI;
		}

		m_Angle = angle;

		

		//------------------------��ط��޸���--------//
		//ȡ����������ĵ�
		//osg::Vec3d pC = (p1 + p0) / 2;
		//m_vecPosition = pC;
		osgEarth::GeoPoint gP;
		osgEarth::GeoPoint gP0(GLOBE_NAME::OsgCoreSingleton::Instance()->MapNode()->getMapSRS(), p0.x(), p0.y(), p0.z());
		osgEarth::GeoPoint gP1(GLOBE_NAME::OsgCoreSingleton::Instance()->MapNode()->getMapSRS(), p1.x(), p1.y(), p1.z());
		osg::Vec3d wP0;
		osg::Vec3d wP1;
		//ת���ѿ��������Է���������
		gP0.toWorld(wP0);
		gP1.toWorld(wP1);

		int countLast = fLineLength / g_length_level_4;
		double fRemainLast = fLineLength - g_length_level_4 * countLast;
		double fLengthThis = (wP1 - wP0).length();
		//�����ǰ�δ���0
		if (fLengthThis > 0)
		{
			double fRemainThis = fRemainLast + fLengthThis;
			//���ʣ���߶δ�����С���g_length_level_4����һֱѭ��
			int countThis = fRemainThis / g_length_level_4;
			osg::Vec3d positionText = wP0;
			osg::Vec3d p0p1 = wP1 - wP0;
			for (int i = 0; i < countThis; i++)
			{
				double ratio = (g_length_level_4 - fRemainLast) / fLengthThis;
				//ͨ����������
				positionText.x() += ratio * p0p1.x();
				positionText.y() += ratio * p0p1.y();
				positionText.z() += ratio * p0p1.z();
				
				//ת��γ�ȹ���ȥ
				gP.fromWorld(GLOBE_NAME::OsgCoreSingleton::Instance()->MapNode()->getMapSRS(), positionText);

				countLast++;
				osg::ref_ptr<osg::LOD> ptrLOD = new osg::LOD();
				//��LOD�ҽ�
				if (countLast % 1 == 0)
				{					
					ptrLOD->addChild(LocatorAndRotate(osg::Vec3d(gP.x(), gP.y(), gP.z()),angle,vTextGeode[0], true), 0, g_length_level_4*4);
				}
				if (countLast % 2 == 0)
				{
					ptrLOD->addChild(LocatorAndRotate(osg::Vec3d(gP.x(), gP.y(), gP.z()), angle, vTextGeode[1]), g_length_level_4 * 4, g_length_level_3 * 4);
				}
				if (countLast % 4 == 0)
				{
					ptrLOD->addChild(LocatorAndRotate(osg::Vec3d(gP.x(), gP.y(), gP.z()), angle, vTextGeode[2]), g_length_level_3 * 4, g_length_level_2 * 4);
				}
				if (countLast % 8 == 0)
				{
					ptrLOD->addChild(LocatorAndRotate(osg::Vec3d(gP.x(), gP.y(), gP.z()), angle, vTextGeode[3]), g_length_level_2 * 4, g_length_level_1 * 4);
				}
				if (countLast % 16 == 0)
				{
					ptrLOD->addChild(LocatorAndRotate(osg::Vec3d(gP.x(), gP.y(), gP.z()), angle, vTextGeode[4]), g_length_level_1 * 4, g_length_level_0 * 4);
				}
				//��0�´μ���
				fRemainLast = 0;
				GLOBE_NAME::OsgCoreSingleton::Instance()->MapNode()->addChild(ptrLOD);
			}
			
			GLOBE_NAME::OsgCoreSingleton::Instance()->LonAndLat()->Change().Add(this, &RoadText::OnChange);

			//�ۼӵ�ǰ��
			fLineLength += (wP1 - wP0).length();
		}
	}
	//osg::Vec3d(gP.x(), gP.y(), gP.z())
	osg::Node* RoadText::LocatorAndRotate(osg::Vec3d vPositionText,double angle, osg::Geode* textGeode, bool bCheck)
	{
		//�����ַŵ�ָ��λ��
		osgEarth::GeoTransform* ptrLocator = new osgEarth::GeoTransform();
		
		GLOBE_NAME::OsgCoreSingleton::Instance()->CorrectPosByOblique(vPositionText);
		if (bCheck)
		{
			m_vPtrLocators.push_back(ptrLocator);
		}

		osgEarth::GeoPoint point = osgEarth::GeoPoint(GLOBE_NAME::OsgCoreSingleton::Instance()->MapNode()->getMapSRS(),vPositionText);
		ptrLocator->setPosition(point);
		//��ת������ĽǶ�
		osg::MatrixTransform* Trans = new osg::MatrixTransform();
		Trans->setMatrix(osg::Matrix::rotate(angle, 0, 0, 1));
		Trans->addChild(textGeode);		
		ptrLocator->addChild(Trans);

		return ptrLocator;
	}
	void RoadText::OnChange()
	{
		if (m_bCheck)
		{
			return;
		}
		if (m_vPtrLocators.size() == 0)
		{
			m_bCheck = true;
			return;
		}


		//�߶ȴ���2500ֱ�ӷ���
		double dbDistance = m_scBox.DistanceFromCameraToGround();
		if (dbDistance > 500)
			return;

		double dbXMin, dbXMax, dbYMin, dbYMax;
		m_scBox.ViewExtent(dbXMin, dbXMax, dbYMin, dbYMax);

		osgEarth::GeoExtent extent = osgEarth::GeoExtent(GLOBE_NAME::OsgCoreSingleton::Instance()->MapNode()->getMapSRS(), dbXMin, dbYMin, dbXMax, dbYMax);
		
		osg::Vec3d eye, center, up;
		GLOBE_NAME::OsgCoreSingleton::Instance()->OsgViewer()->getCamera()->getViewMatrixAsLookAt(eye, center, up);

		for (int i = m_vPtrLocators.size() - 1; i >= 0; i--)
		{	
			osgEarth::GeoPoint transform = m_vPtrLocators[i]->getPosition();
			osg::Vec3d pL = osg::Vec3d(transform.x(), transform.y(), transform.z());
			osgEarth::GeoPoint pIn(GLOBE_NAME::OsgCoreSingleton::Instance()->MapNode()->getMapSRS(), pL.x(), pL.y(), pL.z());
			
			osg::Vec3d pInWorld;
			pIn.toWorld(pInWorld);
			
			double distance = (pInWorld - eye).length();
			double distance1 = (pInWorld - center).length();
			if (distance < 200)
			{				
				osgEarth::GeoPoint pOut;
				double dHeight = 1.0;
				Convert(pIn, pOut, dHeight);
				osg::Vec3d pO(pOut.x(), pOut.y(), pOut.z());
				osgEarth::GeoPoint point = osgEarth::GeoPoint(GLOBE_NAME::OsgCoreSingleton::Instance()->MapNode()->getMapSRS(), pO);
				m_vPtrLocators[i]->setPosition(point);
				m_vPtrLocators.erase(m_vPtrLocators.begin() + i);
			}
			
		}
		
		/*
		double winSX, winSY, winEX, winEY;
		m_scBox.LonLat2Window(m_vecStart.x(), m_vecStart.y(), m_vecStart.z(), winSX, winSY);
		m_scBox.LonLat2Window(m_vecEnd.x(), m_vecEnd.y(), m_vecEnd.z(), winEX, winEY);
		double angle = m_Angle;

		if ((m_vecStart.x() > m_vecEnd.x() && winSX < winEX) || (m_vecStart.x() < m_vecEnd.x() && winSX > winEX))
		{
			if (m_PoseState == positive)
			{
				m_Trans->setMatrix(osg::Matrix::rotate(angle + osg::PI, 0, 0, 1));
				m_PoseState = opposite;
			}
		}
		else if (m_PoseState == opposite)
		{
			m_Trans->setMatrix(osg::Matrix::rotate(angle, 0, 0, 1));
			m_PoseState = positive;
		}

		if (dbDistance < 800)
		{
			if (m_ptrText && m_dbCurrentCharacterSize != m_dbCharacterSize)
			{
				m_ptrText->setCharacterSize(m_dbCharacterSize);
				m_dbCurrentCharacterSize = m_dbCharacterSize;
			}
		}
		else if (dbDistance >= 800 && dbDistance < 1600)
		{
			if (m_ptrText && m_dbCurrentCharacterSize != m_dbCharacterSize * 2)
			{
				m_ptrText->setCharacterSize(m_dbCharacterSize * 2);
				m_dbCurrentCharacterSize = m_dbCharacterSize * 2;
			}
		}
		else if (dbDistance >= 1600 && dbDistance < 2500)
		{
			if (m_ptrText && m_dbCurrentCharacterSize != m_dbCharacterSize * 3)
			{
				m_ptrText->setCharacterSize(m_dbCharacterSize * 3);
				m_dbCurrentCharacterSize = m_dbCharacterSize * 3;
			}
		}*/
	}

	//ת���㣬��һ�����꣬ת��������ı���ȥ
	//����Ϊ��ĵ�������pIn����Ҫ�߳�������dHeight
	//���Ϊ�����������pOut
	bool RoadText::Convert(const osgEarth::GeoPoint& pIn, osgEarth::GeoPoint& pOut, double dHeight)
	{
		//��������ı任���������1000�׸߶ȣ��յ��ȥ1000��
		//�������û��zֵ���������û�����ΪzΪ0
		osgEarth::GeoPoint pStart = pIn;
		pStart.z() += 1000;
		osgEarth::GeoPoint pEnd = pIn;
		pEnd.z() -= 1000;

		//�󽻵õ�����
		if (PickSurface(pStart, pEnd, pOut))
		{
			//̧��
			pOut.z() += dHeight;
			return true;
		}
		return false;
	}

	//����һ���߶Σ��������������������Ķ�����߶���Ҫ���
	//����Ϊ��ĵ�������pStart��pEnd,��Ҫ�߳�������dHeight
	//���Ϊ������ϣ���������ڵ�һ�����յ������һ�����м��ǿ�����Ҫ����ĵ�
	bool RoadText::Convert(const osgEarth::GeoPoint& pStart, const osgEarth::GeoPoint& pEnd, std::vector<osgEarth::GeoPoint> &vOut, double dHeight)
	{
		//�ȰѶ���θ�
		osgEarth::GeoPoint outStart, outEnd;
		Convert(pStart, outStart, dHeight);
		Convert(pEnd, outEnd, dHeight);

		//�������
		vOut.push_back(outStart);
		//�ж��ߺͳ�������
		osgEarth::GeoPoint p0 = outStart;
		osgEarth::GeoPoint p1 = outEnd;
		osgEarth::GeoPoint pResult;
		//��ѭ�����ã��㷨�Ǵ�������յ�ƽ�
		//ÿ������p0ֵ����Ϊ�µ���㣬һֱ��û�н���Ϊֹ
		while (PickSurface(p0, p1, pResult))
		{
			if (p0 == pResult || p1 == pResult)
			{
				break;
			}
			//̧�ߡ�����
			pResult.z() += dHeight;
			vOut.push_back(pResult);

			//�����µ����
			p0 = pResult;
		}
		//�����β
		vOut.push_back(outEnd);
		return true;
	}
	//��
	bool RoadText::PickSurface(osg::Vec3d start, osg::Vec3d end, osg::Vec3d& result)
	{
		//��������
		osg::ref_ptr<osgUtil::IntersectionVisitor> iv = new osgUtil::IntersectionVisitor;
		osg::ref_ptr<osgUtil::LineSegmentIntersector> ls = new osgUtil::LineSegmentIntersector(start, end);

		//�����
		osgUtil::LineSegmentIntersector::Intersections intersections;

		//ָ���������
		iv->setIntersector(ls.get());
		GLOBE_NAME::OsgCoreSingleton::Instance()->MapNode()->accept(*(iv.get()));

		//�õ���һ�����㣬Ҳ���Ǳ���
		if (ls->containsIntersections())
		{
			result = end;
			intersections = ls->getIntersections();
			osgUtil::LineSegmentIntersector::Intersections::iterator iter = intersections.begin();
			for (; iter != intersections.end(); iter++)
			{
				osg::Vec3 point = iter->getWorldIntersectPoint();
				//�������������ĵ㣬����µ�result
				if ((start - point).length() < (start - result).length())
				{
					result = point;
				}
			}
			return true;
		}
		return false;
	}

	bool RoadText::PickSurface(const osgEarth::GeoPoint& pStart, const osgEarth::GeoPoint& pEnd, osgEarth::GeoPoint& pResult)
	{
		//ת��Ϊ��������
		osg::Vec3d start, end, result;
		pStart.toWorld(start);
		pEnd.toWorld(end);
		//�󽻵õ�����
		if (PickSurface(start, end, result))
		{
			pResult.fromWorld(pStart.getSRS(), result);
			return true;
		}
		return false;
	}

}
