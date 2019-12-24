#ifndef OSGEARTHFEATURES_FEATURE_GEOFEATURE_XML
#define OSGEARTHFEATURES_FEATURE_GEOFEATURE_XML 1

#include <string>
#include <vector>
#include <osgearth/Bounds>
#include <osgEarthSymbology/Geometry>
#include <osgEarthFeatures/Feature>

namespace osgEarth
{
	class XmlElement;
	class XmlDocument;
	class SpatialReference;
};

namespace GeoGlobe
{
	namespace GeoVector
	{
		//��Ӧ����WFS�ļ��࣬һ��Ϊxml�ļ���ʽ
		class GEOWFSFeatureClass
		{
		public:
			GEOWFSFeatureClass(std::string xmlPath);
			GEOWFSFeatureClass();
			GEOWFSFeatureClass(osgEarth::XmlElement* root);
			~GEOWFSFeatureClass();

			void setRoot(osgEarth::XmlElement* root);
			osgEarth::XmlElement* getRoot();
			//��ȡWFSҪ��ͼ��ľ�γ�ȷ�Χ
			osgEarth::Bounds getBounds();

			//��ȡҪ�ظ���
			int getFeatureCount();
			//����xml�ļ��������꣬��ȡ���������
			void splitCoordinates(const std::string& src, std::vector<osg::Vec2d>& points);
			void splitCoordinates(const std::string& src, std::vector<osg::Vec3d>& points);

			//����ogc�е�gml��ʽ����Ҫ���࣬��������Ҫ��
			void createFeaturesfromGML(const osgEarth::SpatialReference* srs, osgEarth::Features::FeatureList& features);
			//����Ҫ�ص�oid�Ŵ�����Ҫ��
			void createFeaturesfromGMLbyOID(int oid, const osgEarth::SpatialReference* srs, osgEarth::Features::FeatureList& features);
			void createFeaturesfromGML(const osgEarth::SpatialReference* srs, float height, osgEarth::Features::FeatureList& features);
			void createFeaturesfromGML(const osgEarth::SpatialReference* srs, osgEarth::Features::FeatureList& features, float transparent, float height);

			//�����㼸����
			osgEarth::Symbology::Geometry* createPointfromGML(osgEarth::XmlElement* e_point);
			//�����߼�����
			osgEarth::Symbology::Geometry* createLinefromGML(osgEarth::XmlElement* e_line);
			//��������μ�����
			osgEarth::Symbology::Geometry* createPolyfromGML(osgEarth::XmlElement* e_poly);
            //������ͬ���͵ļ�����
			void createGeometryfromGML(osgEarth::XmlElement* e_geometry, std::vector< osg::ref_ptr<osgEarth::Symbology::Geometry> >& geoms);

			osgEarth::Symbology::Geometry* createPointfromGML(osgEarth::XmlElement* e_point, float height);
			osgEarth::Symbology::Geometry* createLinefromGML(osgEarth::XmlElement* e_line, float height);
			osgEarth::Symbology::Geometry* createPolyfromGML(osgEarth::XmlElement* e_poly, float height);

			void createGeometryfromGML(osgEarth::XmlElement* e_geometry, float height, std::vector< osg::ref_ptr<osgEarth::Symbology::Geometry> >& geoms);
			void CreatePolygon(osg::Vec3Array* ptrVertices, double x, double y, double z);
			osgText::Text* createText(const osg::Vec3& pos, const std::string& content, float size, osg::Vec4 color, std::string strFont);
			osgText::Font* getFont(std::string strFontName);
		public:
			osgEarth::XmlElement* _wfsFeatureCollection;
			osgEarth::XmlDocument* _doc;

			osg::ref_ptr<osgEarth::Features::Feature> m_ptrFeature;
			osg::Vec3d m_vecOrigin;
			std::string m_OriginSRS;
			std::string m_strRoadName;

			double m_dbElevation;
			double m_dbHigh;
			int m_nID;

			osg::ref_ptr<osgText::Font> m_font;

			int m_nsize;
			osg::Vec4d m_Color;
			std::string m_strFontFile;
			osg::Vec4d m_shadowColor;
			int m_eShadowPos;
			double m_dbOffset;
		};
	}
}

#endif