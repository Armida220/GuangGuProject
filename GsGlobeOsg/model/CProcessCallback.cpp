#include <Model/CProcessCallback.h>

//////////////////////////////////////////////////////////////////////////
#pragma region ��������

void CProcessGeometry::SetCallBack(CProcessCallback* pDoSplite)
{
	m_pDoSplite = pDoSplite;
}
void CProcessGeometry::SetGeometry(CGeometry* pGeometry)
{
	m_pGeometry = pGeometry;
}

void CProcessGeometry::DoSplite()
{
	if (NULL == m_pGeometry || NULL == m_pDoSplite)
		return;

	SpliteGeometry(m_pGeometry);
}

void CProcessGeometry::SpliteGeometry(CGeometry* pGeometry)
{
	if (pGeometry == NULL)
		return;

	switch (pGeometry->getTypeID())
	{
		//��
	case GEOTYPE_3D_GROUP:
		SpliteGroup(dynamic_cast<C3DGroup*>(pGeometry));
		break;

	case GEOTYPE_3D_SOLID:
		SpliteSolid(dynamic_cast<C3DSolid*>(pGeometry));
		break;
	case GEOTYPE_3D_MODELOBJECT:
		SpliteModelObj(dynamic_cast<C3DModelObject*>(pGeometry));
		break;
		//������
	case GEOTYPE_3D_SURFACE:
		SpliteSurface(dynamic_cast<C3DSurface*>(pGeometry));
		break;

		//����������
	case GEOTYPE_3D_TRIANGLEMESH:
		//SpliteTriangleMesh(dynamic_cast<C3DTriangleMesh*>(pGeometry));
		m_pDoSplite->SpliteOne(pGeometry);
		break;

	case GEOTYPE_3D_REFERENCE:			//��ά�ο� ��ʱ��ʵ��
		m_pDoSplite->SpliteOne(pGeometry);
		break;

	case GEOTYPE_3D_GEOMETRY:			//����
	case GEOTYPE_3D_CURVE:				//��ά����	���ݽṹ��û�л�����Ϣ
	case GEOTYPE_3D_LOFTING:			//��ά�������� ���ݽṹ��û�л�����Ϣ
	case GEOTYPE_3D_FEATUREINFOGROUP:	//Ҫ����Ϣ���� ��ʱ��ʵ��

	case GEOTYPE_3D_POINT:				//��\��������
	case GEOTYPE_3D_SINGLEPOINT:		//����
	case GEOTYPE_3D_MULTIPOINT:			//���
	case GEOTYPE_3D_LINEARRING:			//����
	case GEOTYPE_3D_LINESTRING:			//��ά����
	case GEOTYPE_3D_POLYGON:			//�����
	default:
		break;
	}

}

void CProcessGeometry::SpliteGroup(C3DGroup* pGroup)
{
	if (pGroup == NULL)
		return ;

	_GeometryList pGeoCollection;
	pGroup->GetCollection(pGeoCollection);
	int num = pGeoCollection.size();
	for (int j = 0; j < num; j++)
	{
		SpliteGeometry(pGeoCollection[j].second);
	}
}
void CProcessGeometry::SpliteSolid(C3DSolid* pSolid)
{
	if (pSolid == NULL)
		return;

	//��ÿһ������в��
	_3DSurfaceList& surlist = pSolid->get3DSurfaceList();
	for ( size_t i = 0; i < surlist.size(); i++ )
	{
		SpliteSurface(surlist.at(i).second);
	}
}

void CProcessGeometry::SpliteModelObj(C3DModelObject* pModelObject)
{
	if (pModelObject == NULL)
		return;

	//��ÿһ������в��
	_3DSurfaceList& surlist = pModelObject->get3DSurfaceList();
	for ( size_t i = 0; i < surlist.size(); i++ )
	{
		SpliteSurface(surlist.at(i).second);
	}
	pModelObject->GetMaterialParamVec(m_vecD3dxMaterialParam);
	pModelObject->GetAdjacencyTable(m_pAdjacencyTable, m_nAdjacencyTableCount);
}

void CProcessGeometry::SpliteSurface(C3DSurface* pSurface)
{
	SpliteGeometry(dynamic_cast<C3DGeometry*>(pSurface));
}