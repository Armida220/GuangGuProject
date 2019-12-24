#ifndef OSGEARTHFEATURES_FEATURE_GEOFEATURE_SOURCE_GEOWFS
#define OSGEARTHFEATURES_FEATURE_GEOFEATURE_SOURCE_GEOWFS 1

#include <osgEarth/Registry>
#include <osgEarth/FileUtils>
#include <osgEarth/StringUtils>
#include <osgEarth/GeoData>
#include <osgEarth/Bounds>
#include <osgEarth/Cache>
#include <osgEarthFeatures/FeatureSource>
#include <osgEarthFeatures/Filter>
#include <osgEarthFeatures/BufferFilter>
#include <osgEarthFeatures/ScaleFilter>
#include <osgEarthFeatures/GeometryUtils>
#include "tool/CodeTransformHelp.h"


#include <osg/Notify>
#include <osgDB/FileNameUtils>
#include <osgDB/FileUtils>
#include <list>


#include "GEOWFSFeatureOptions.h"
#include "GEOWFS.h"
#include "GeoFeature_XmlApi.h"
#define GEO_SCOPED_LOCK GDAL_SCOPED_LOCK
#define LC "[GEO FeatureSource] "

namespace GeoGlobe
{
	namespace GeoVector
	{
		
		using namespace osgEarth::Features;

		//����WFS�����Ӧ��Ҫ������Դ
		class GEOWFSFeatureSource : public FeatureSource
		{
		public:
					//���캯�����������GEOWFSFeatureOptions��ʸ��̧�߸߶���͸����
			GEOWFSFeatureSource(const GEOWFSFeatureOptions& options);

			/** Destruct the object, cleaning up and OGR handles. */
			virtual ~GEOWFSFeatureSource();

			//FeatureSource�ĳ�ʼ���࣬�ڼ�������֮ǰ����
			//virtual Status initialize(const osgDB::Options* dbOptions);
			virtual Status initialize(const osgDB::Options* readOptions);
			//����Ҫ�صĸ����࣬���������ݷ�Χ���ռ�����ϵ��
			const FeatureProfile* createFeatureProfile();

			FeatureProfile* getFeatureProfile();

			bool getFeatures(const std::string& buffer, FeatureList& features);
			bool getFeatures(const std::string& buffer, FeatureList& features, float height);
		    //����Ҫ��ͼ������ƻ�ȡ����Ҫ�����ݵ�url
			std::string createAllURL();
			//����һ���ľ�γ�ȷ�Χ��ȡҪ�ص�url
			std::string createBoundURL(osgEarth::Bounds bds);
			std::string createOidURL(int oid);
			void saveResponse(const std::string buffer, const std::string& filename);
			bool getFeatures(std::istream& buffer, FeatureList& features);
			bool getFeatures(std::istream& buffer, FeatureList& features, float height);
			bool getFeatures(std::istream& buffer, FeatureList& features, float transparent = 1.0, float height = 0.0);

			virtual FeatureCursor* createFeatureCursor(const Symbology::Query& query, ProgressCallback* progress);

			virtual bool supportsGetFeature() const
			{
				return false;
			}
			virtual Feature* getFeature(FeatureID fid);

			virtual bool isWritable() const;

			virtual const FeatureSchema& getSchema() const;

			virtual osgEarth::Symbology::Geometry::Type getGeometryType() const;


		private:
			const GEOWFSFeatureOptions         _options;  
		   // osg::ref_ptr< GEOWFSCapabilities > _capabilities;
			osg::ref_ptr< FeatureProfile >  _featureProfile;
			FeatureSchema                   _schema;
			osg::ref_ptr<CacheBin>          _cacheBin;
			osg::ref_ptr<const osgDB::Options>    _dbOptions;    
			std::string                     _xmlPath;
			std::string m_OriginSRS;

			osg::ref_ptr< GEOWFSCapabilities> _capabilities;

			float                           _geoHeight;
			float                           _transparent;
		};
	}
}
#endif