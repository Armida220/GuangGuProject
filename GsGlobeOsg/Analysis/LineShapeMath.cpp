#include "LineShapeMath.h"


BaseLineMath::BaseLineMath()
{
}

BaseLineMath::~BaseLineMath()
{
}

int BaseLineMath::getCount()
{
	return m_Count;
}

osg::Vec3Array * BaseLineMath::VertexPoints()
{
	return m_Vertex;
}

osg::UShortArray * BaseLineMath::Indexs()
{
	return m_Index;
}

///************************************************************************************
/*-------------------------------------�ָ���-------------------------------------------------*/

osg::Vec3 zeorVec(0, 0, 0);

DotLine3DMath::DotLine3DMath()
{
}

DotLine3DMath::~DotLine3DMath()
{

}

void DotLine3DMath::start(int count, osg::Vec3& normal, double h, bool isClose)
{
	//���������зֵĶ������
	m_IsClose = isClose;
	m_Lenght = count;//����ĵ�ĸ���
	int newCount = m_Lenght * 6 - 8;//�����зֺ�Ľڵ����
	m_Count =  ((m_Lenght - 1) * 4 - 2) * 3;// �����θ���
	if (isClose)
	{
		newCount += 2;//��Ϊ�պϵģ���ڵ���2��
		m_Count += 6;// ������������Σ�6���ڵ㡣
	}
	m_Vertex = new osg::Vec3Array(newCount);//����洢
	m_CoorTextVertex = new osg::Vec2Array(newCount);//��������
	m_VertexOffset = new osg::Vec3Array(newCount);//����ı��˷���
	m_Index = new osg::UShortArray(m_Count);//�����εĻ��ƵĶ���������¼
	m_NormalVector = normal;
	m_CurPoints = 0;
	index = index2 = 0;
	mHeight = h;// �ܵ��ߵĳ���
	lenSum = 0;
}

void DotLine3DMath::addPoint(osg::Vec3d & point)
{
	m_CurPoints++;
	if (m_CurPoints == 1) {
		m_p1 = point;
		return;
	}
	m_p2 = point;
	// �������
	m_CurAngle = (point - m_p1);
	double len= m_CurAngle.normalize();// ת��������ĵ�λ����
	if (m_CurPoints == 2) {// ��һ�ε�
		m_FirstAngle = m_CurAngle;
	}
	else {//
		dotNodePoint(false);
	}
	// �����Ĳ��
	osg::Vec3 dir = m_CurAngle^m_NormalVector;
	dir.normalize();
	//���λ��
	setPoints(index, m_p1);
	setPoints(index + 1, m_p1);
	setPoints(index + 2, m_p2);
	setPoints(index + 3, m_p2);
	//�����ƫ����
	setVertexCoord(index, dir);
	setVertexCoord(index + 1, (zeorVec-dir));
	setVertexCoord(index + 2, dir);
	setVertexCoord(index + 3, zeorVec-dir);
	//������������
	setTextCoord(index, 0, (float)(lenSum / mHeight));
	setTextCoord(index + 1, 1, (float)(lenSum / mHeight));
	lenSum += len;
	setTextCoord(index + 2, 0, (float)(lenSum / mHeight));
	setTextCoord(index + 3, 1, (float)(lenSum / mHeight));
	//
	//��������ֵ,�������εĶ���
	(*m_Index)[index2] = (unsigned short)(index);
	(*m_Index)[index2 + 1] = (GLushort)(index + 1);
	(*m_Index)[index2 + 2] = (GLushort)(index + 2);
	index2 += 3;
	//
	(*m_Index)[index2] = (GLushort)(index + 1);
	(*m_Index)[index2 + 1] = (GLushort)(index + 2);
	(*m_Index)[index2 + 2] = (GLushort)(index + 3);
	index2 += 3;
	index += 4;
	m_p1 = m_p2;
	m_preAngle = m_CurAngle;

}

void DotLine3DMath::end()
{
	if (m_IsClose) {// ��Ϊ�պϵ����պϴ���
		m_preAngle = m_FirstAngle;
		dotNodePoint(true);
	}
}

osg::Vec2Array* DotLine3DMath::GetCoorTextVertex()
{
	return m_CoorTextVertex;
}

osg::Vec3Array* DotLine3DMath::GetVerTexOffset()
{
	return m_VertexOffset;
}

void DotLine3DMath::addDotPoint(osg::Vec3d & point)
{
}

void DotLine3DMath::dotNodePoint(bool isEnd)
{
	osg::Vec3 ab = m_CurAngle + m_preAngle;// ������ӵķ���
	osg::Vec3 dirab = ab^m_NormalVector;//�ڵ�ƽ�淽�������
	dirab.normalize();
	float axb = m_CurAngle*m_preAngle;//�жϷ�����==1 ��ͬ��
	int step = 2;
	if (axb < 0.999)//ͬ����Ĭ��
	{
		// ���� b-a�ķ���
		osg::Vec3d ba = m_CurAngle - m_preAngle;
		ba.normalize();//ת�ɵ�λ����
		float dirabXba = dirab*ba;
		if (dirabXba > 0) {
			step = 1;
			dirab = zeorVec - dirab;
		}//ȡ������
	}
	setPoints(index, m_p1);//points[index] = p1;
	setPoints(index + 1, m_p1);
	////��������
	setTextCoord(index + 1, 0.5f, (float)(lenSum / mHeight));
	lenSum += 0.01;
	setTextCoord(index, temlemate[4 + step][0], (float)(lenSum / mHeight));// texCoord[index] = temlemate[4 + step];
	lenSum += 0.01;
	////���귽��
	setVertexCoord(index,dirab); //coord[index] = new double[] { dx, dy };
	setVertexCoord(index + 1, 0.f,0.f);//coord[index+1] = new double[] { 0, 0 };
												  //����������
												  //��������ֵ,�������εĶ���
	(*m_Index)[index2] = (GLushort)(index - step);
	(*m_Index)[index2 + 1] = (GLushort)(index + 1);
	(*m_Index)[index2 + 2] = (GLushort)index;
	index2 += 3;
	//
	(*m_Index)[index2] = (GLushort)(index + 1);
	(*m_Index)[index2 + 1] = (GLushort)index;
	//����i�����Ĵ����򣬱�ţ���0����1
	(*m_Index)[index2 + 2] = (GLushort)(isEnd ? ((index - step + 4) % 2) : (index - step + 4));
	index2 += 3;
	index += 2;
}

void DotLine3DMath::setPoints(int index, osg::Vec3d & point)
{
	(*m_Vertex)[index] = point;
}

void DotLine3DMath::setVertexCoord(int index, float x, float y)
{
	(*m_VertexOffset)[index] = osg::Vec3(x, y, 0.0f);
}

void DotLine3DMath::setVertexCoord(int index, const osg::Vec3 & dirv)
{
	(*m_VertexOffset)[index] = dirv;
}

void DotLine3DMath::setTextCoord(int index, float x, float y)
{
	(*m_CoorTextVertex)[index] = osg::Vec2(x, y);
}