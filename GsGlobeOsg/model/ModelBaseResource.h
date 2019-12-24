#ifndef MODEL_LODMODELTYPE
#define MODEL_LODMODELTYPE

#include <Model/CFeature.h>
#include <Model/CT3D_3DSurface.h>
#include <Model/CT3D_3DSolid.h>
#include <Model/CT3D_3DGeometry.h>
#include <Model/CT3D_3DGroup.h>
#include <Model/CT3D_3DModelObject.h>
#include <Model/CT3D_3DTriangleMesh.h>
#include <Model/Buffer.h>

namespace GeoGlobe
{
	//��Ƭ��ģ�͸�ʽ
	enum enumModelVersion
	{
		eModelVersionUnknownType = -1,
		eModelVersionKMZ,
		eModelVersionG3D,
		eModelVersionGMDL500,
		eModelVersionGMDL501,
		eModelVersionGMDL502,
		eModelVersionGMDL503, //USEGMDL503
		eModelVersionGMDL504, //Mixed 502503
		/// Texture package for 502, 503, 504
		eModelVersionGMDL505,
		eModelVersionGMDL506,
		eModelVersionGMDL507
	};

	//��������
	enum enumVertexCoordType
	{
		eVertexCoordTypeLocal,		//�ֲ���������
		eVertexCoordTypeSpherical,	//���� ��γ�ȶ�������
		eVertexCoordTypeCartesian	//�ѿ���,��������
	};
}

#endif // OSGEARTH_DRIVERS_MP_TERRAIN_ENGINE_TILE_PAGED_LOD