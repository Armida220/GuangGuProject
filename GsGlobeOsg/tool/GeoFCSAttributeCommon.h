#ifndef OSGEARTHFEATURES_GEOFCSATTRIBUTECOMMON
#define OSGEARTHFEATURES_GEOFCSATTRIBUTECOMMON 1

#include <osgEarthFeatures/Common>
#include <osgEarthFeatures/Feature>
#include <osgEarthSymbology/Geometry>
#include <osgEarth/StringUtils>
#include <osgEarth/Config>

#include <osgDB/FileUtils>
#include <osgDB/FileNameUtils>

#include <osg/Notify>
#include <sqlite3.h>
#include "Vector/GeoFeature_SqliteApi.h"

using namespace osgEarth::Features;
using namespace osgEarth::Symbology;
using namespace GeoGlobe::GeoVector;

//���騰a?��GeoFeature_SqliteApi.h?D����?��o����ygetOidfromFeatureID
namespace GeoGlobe 
{ 
	namespace Tool
    {
		class GeoFCSAttributeCommon
		{
		public:
			GeoFCSAttributeCommon(std::string fcsPath) :
			  _fcsPath(fcsPath)
			{
				_geoFeaClasses=NULL;
				init(fcsPath);
			}
			~GeoFCSAttributeCommon()
			{
				if (_geoFeaClasses)
				{
					delete[] _geoFeaClasses;
				}
			}
		public:
            //���ȸ���·��������Ӧʸ�����ݿ��ļ�������
			bool init(std::string fcsPath)
			{
				if (!osgDB::fileExists(fcsPath))
				{
					OE_NOTICE << "fcs not exists " << std::endl;
					return false;
				}
				_geoFeaClasses = new GEOFeatureClass;
				_geoFeaClasses->init(fcsPath);
			}

            //����oid��ȡ�������Χ��
			bool getBoundBoxbyoidGeometry(int oid,osgEarth::Bounds& bds)
			{
				double xMin=180;//�����Сֵ�෴
				double xMax=-180;
				double yMin=90;
				double yMax=-90;
				
				GEOFeatureH handle;
				_geoFeaClasses->createGEOFeatureH(oid,&handle);

				if ( handle.valid() )
				{
                    int numPoints = handle.getGeomH()->getNumPoints();

					for(int i=0;i<numPoints;i++)
					{
						double x=0, y=0, z=0;
						handle.getGeomH()->getGeoPoint(i,x,y,z);
						if (x<xMin)
						{
							xMin=x;
						}
						if (x>xMax)
						{
							xMax=x;
						}
						if (y<yMin)
						{
							yMin=y;
						}
						if (y>yMax)
						{
							yMax=y;
						}
					}//for every geopoint
				}
				bds.xMin()=xMin;
				bds.xMax()=xMax;
				bds.yMin()=yMin;
				bds.yMax()=yMax;

				return true;
			}
			
			int getOIDfromFeatureID(LONGLONG feature_id)
			{
				int oid =-1;
				if (_geoFeaClasses)
				{
					oid=_geoFeaClasses->getOidfromFieldFeatureID(feature_id);
				}
				return oid;
			}
			//����FeatureID��ȡ��Χ��
			bool getBoundBoxbyFeatureID(LONGLONG fid,osgEarth::Bounds& bds)
			{
				int oid = getOIDfromFeatureID(fid);
				return getBoundBoxbyOID(oid,bds);
			}
            //����oid��ȡ��Χ��
			bool getBoundBoxbyOID(int oid,osgEarth::Bounds& bds)
			{
				if (_geoFeaClasses)
				{
					return _geoFeaClasses->getOidBoundBox(oid,bds);
				}
				return false;
			}
            //����Ҫ�ص�ID������������Ҫ�ر�
			template <typename T>
			void getAttributeTablesbyFIDs(std::vector<T>& fids,std::vector<AttributeTable>& attributeTables)
			{
				for(std::vector<T>::iterator i=fids.begin();i!=fids.end();i++)
				{
					T fid=*i;
					AttributeTable attr;
					getAttributeTablebyFID(fid,attr);
					attributeTables.push_back(attr);
				}
			}
			
			template <typename T>
			void getAttributeTablebyFID(T feature_id,osgEarth::Features::AttributeTable& attr)
			{
				if (_geoFeaClasses)
				{
					Config fields = _geoFeaClasses->_geoFeaMetatable.FiledsInfo.child("fields");

					createAttributeTable(fields,_geoFeaClasses,feature_id,attr);
				}
				
			}

			template <typename T>
			void createAttributeTable(Config fields,GEOFeatureClass* gfc,T feature_id,osgEarth::Features::AttributeTable& attr)
			{
				if (!gfc)
				{
					return;
				}
				AttributeValue& a=attr["layer"];
				a.first = ATTRTYPE_STRING;
				a.second.stringValue = osgDB::getNameLessAllExtensions(osgDB::getSimpleFileName(gfc->getdbPath()));
				a.second.set = true;

				//get the oid
				int oid=gfc->getOidfromFieldFeatureID(feature_id);
				AttributeValue& at=attr["OID"];
				at.first = ATTRTYPE_INT;
				at.second.intValue = oid;
				at.second.set = true;

				for (ConfigSet::const_iterator cfitr=fields.children().begin();cfitr!=fields.children().end();cfitr++)
				{
					Config field = *cfitr;
					std::string fieldname = field.child("name").value();
					AttributeValue& a=attr[fieldname];
					if(field.child("type").value()=="integer"||field.child("type").value()=="smallint")
					{
						a.first=ATTRTYPE_INT;
						a.second.intValue = gfc->excuteFieldSQLint(fieldname,oid);
						a.second.set = true;
					}
				
					if(field.child("type").value()=="text"||field.child("type").value()=="bigint"||field.child("type").value()=="any"||field.child("type").value()=="datetime")
					{
						a.first=ATTRTYPE_STRING;
						a.second.stringValue = gfc->excuteFieldSQLstring(fieldname,oid);
						a.second.set = true;
					}
					if(field.child("type").value()=="real")
					{
						a.first= ATTRTYPE_DOUBLE;
						a.second.doubleValue = gfc->excuteFieldSQLdouble(fieldname,oid);
						a.second.set = true;
					}

				}//for every field
			}
		public:
			std::string _fcsPath;
			GEOFeatureClass* _geoFeaClasses;
			
		};
    }
}


#endif // OSGEARTHFEATURES_GEOFCSATTRIBUTECOMMON

