#ifndef OSGEARTHFEATURES_FEATURE_GEOFEATURE_COMMON
#define OSGEARTHFEATURES_FEATURE_GEOFEATURE_COMMON 1

//#include "stdafx.h"
namespace GeoGlobe
{
	namespace GeoVector
	{
	//���¼��ζ��������趨��ö����
		enum geoGEOMETRYTYPE
		{
			GEO_GEOMETRY_UNKNOWN = 0,
			GEO_GEOMETRY_POINT = 1,
			GEO_GEOMETRY_PATH = 2,
			GEO_GEOMETRY_POLYGON = 3,
			GEO_GEOMETRY_COLLECTION = 4,
			GEO_GEOMETRY_MULTIPOINT = 5,
			GEO_GEOMETRY_POLYLINE = 6,
			GEO_GEOMETRY_ANNOTATION = 7,
			GEO_GEOMETRY_ENVELOPE = 8,
			GEO_GEOMETRY_LINE = 9,
			GEO_GEOMETRY_CIRCLEARC = 10,
			GEO_GEOMETRY_RING = 11
		};

//Ҫ�������У�������ͷ�ṹ��
		struct st_blob_head//blob?????
		{
			long		oid;
			long		oid2;
			geoGEOMETRYTYPE	type;
			long		coordnum;
			long		dim;
			long		infonum;
		} ;

	}
}

#endif//OSGEARTHFEATURES_FEATURE_GEOFEATURE_COMMON