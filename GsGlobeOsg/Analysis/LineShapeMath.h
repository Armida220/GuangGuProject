#pragma once
#include <osg\Array>
/// \brief  �����ߵļ������
class BaseLineMath
{
public:
	const float temlemate[7][2] = { { 0, 0.26f },{ 1, 0.26f },{ 0, 0.74f },{ 1, 0.74f },{ 0.5f, 0.5f },{ 1.f, 0.5f },{ 0.f, 0.5f } };

	const float template2[4][2] = { { 0, 0 },{ 1, 0 },{ 0, 0.25f },{ 1, 0.25f } };
	const float template3[4][2] = { { 0, 0.75f },{ 1, 0.75f },{ 0, 1 },{ 1, 1 } };

	BaseLineMath();
	~BaseLineMath();
	/**
	* �зֳɵ����������εĸ���
	*
	* @return
	*/
	int getCount();

	virtual void start(int count, float w, double h, bool isClose) {};

	virtual void addPoint(osg::Vec3d& point) {};

	virtual void end() = 0;
	// ��ȡ��ά��Ĺ���
	virtual osg::Vec3Array* VertexPoints();
	// ��ȡ�����еĹ���
	virtual osg::UShortArray* Indexs();

protected:
	osg::Vec3Array* m_Vertex;
	osg::UShortArray* m_Index;
	int m_Count;
};


/*****************
* ���Ը��ݷ�������ƫ�ƵĹ���
***/
class DotLine3DMath :public BaseLineMath
{
public:
	DotLine3DMath();
	~DotLine3DMath();

	virtual void start(int count, osg::Vec3& normal, double h, bool isClose) ;
	virtual void addPoint(osg::Vec3d& point) ;
	virtual void end()override;
	// ���ƫ�����Ĺ���
	osg::Vec2Array* GetCoorTextVertex();
	// ���ƫ�����Ĺ���
	osg::Vec3Array* GetVerTexOffset();
protected:
	/// \brief ��ӵ�Ĺ���
	void addDotPoint(osg::Vec3d& point);
	/// \brief ��ӽ����Ĵ���
	void dotNodePoint(bool isEnd);
	//
	//���ýڵ�����
	void setPoints(int index, osg::Vec3d & point);
	// �ڵ�ƫ����
	void setVertexCoord(int index, float x, float y);

	void setVertexCoord(int index,const osg::Vec3& dirv);
	//������������
	void setTextCoord(int index, float x, float y);
protected:
	osg::Vec2Array* m_CoorTextVertex;//����������ͼ����
	osg::Vec3Array* m_VertexOffset;//ƫ��������
	int m_Lenght;
	double  mHeight;
	//
	double  lenSum;
	int index = 0, index2 = 0;
	int m_CurPoints;
	bool m_IsClose;//�Ƿ�Ϊ�պϵ���
	osg::Vec3d m_p1, m_p2;
	osg::Vec3 m_NormalVector;//��������
	osg::Vec3d m_preAngle, m_CurAngle, m_FirstAngle;//��һ����������ǰ��������һ��������ֵ��
};
