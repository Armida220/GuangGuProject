#ifndef OSGEARTHFEATURES_FEATURE_GEOFEATURE_XML_GEO
#define OSGEARTHFEATURES_FEATURE_GEOFEATURE_XML_GEO 1

#include <osgEarth/Map>
#include <osgEarth/ModelLayer>
#include <osgEarth/Config>
#include <osgEarth/XmlUtils>
#include <osgEarth/FileUtils>
#include <osgEarthSymbology/Style>
#include <osgEarthFeatures/FeatureDisplayLayout>

#include <osgEarthDrivers/model_feature_geom/FeatureGeomModelOptions>

#include <osgDB/ReaderWriter>
#include <osgDB/FileNameUtils>
#include <osgDB/FileUtils>
#include <osgDB/Registry>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <map>
#include "Tool/CodeTransformHelp.h"

#include "GEOFeatureOptions.h"
#include "Vector/GEORasterizerOptions.h"

namespace GeoGlobe
{
	namespace GeoVector
	{
		

		//ȷ����ʸ��������Ⱦ�ķ�ʽ����դ�񻯵ķ�ʽ���߼��η�ʽ����
		enum GeoVectorRenderType
		{
			GEOVECTORMODEL,
			GEOVECTORIMAGE
		};
		////////////////////////����ʸ��Ҫ�ط���������صĽṹ��
		//������ɫ���㡢�ߡ��������geo_color��geo_pointStyle��geo_lineStyle��geo_polyStyle
		struct geo_color
		{
		    std::string value;
			int transparent;
		};

		struct geo_pointStyle
		{
			geo_color color;
			float size;
		};
		struct geo_polyStyle
		{
			geo_color FillColor;
			geo_color EdgeColor;
		    float width;
		};

		struct geo_lineStyle
		{
			geo_color color;
			float width;
		};

		struct GeoVectorXMLOptions
		{
			static double m_Xmin;
			static double m_Xmax;
			static double m_Ymin;
			static double m_Ymax;

			//2?��????��
            //�������Ҫ�����������ļ�·�����Լ�map��������Ⱦ�ķ�ʽ����ʸ������
			//�������std::string xmlPath��ʸ��Ҫ�������ļ�������ʸ��ͼ���������Դ�����������
			//osgEarth::Map,ʸ��������Ҫ�����mapͼ��
			//GeoVectorRenderType ʸ�����ݵ���Ⱦ��ʽ��դ����߼��λ���
			static bool create(std::string xmlPath,osgEarth::Map* map,GeoVectorRenderType type)
			{
				if (!osgDB::fileExists(xmlPath))
				{
					OE_NOTICE << "XML not exists " << std::endl;
					return false;
				}
					  
				std::ifstream in(xmlPath.c_str());
				Config doc;
				doc.fromXML(in);

				if (doc.empty()||doc.children().empty())
				{
					OE_NOTICE << "Failed to get XML " << std::endl;
					return false;
				}

				/////////��ȡxml�����ļ��е�geomap�ڵ㣬��ȡʸ��ͼ�㼰��Ӧ��������
				Config geoMap = doc.child("geomapfile").child("geomap");

				std::map<std::string,std::string> Dataname_Stylename;
				Config geoMapLayers = geoMap.child("layers");

				for(ConfigSet::const_iterator i=geoMapLayers.children().begin();i!=geoMapLayers.children().end();++i)
				{
					Config geoFeatureLayer = *i;
					Dataname_Stylename.insert(std::map<std::string,std::string>::value_type(geoFeatureLayer.child("layersourcename").value(),geoFeatureLayer.child("layerstylename").value()));
				}

				std::string dataRootPath = osgDB::getFilePath(xmlPath);

				Config fdataSources = doc.child("geomapfile").child("geodatasources");
				Config fStyleGroups = doc.child("geomapfile").child("geostylegroups").child("geostylegroup");

				std::map<std::string,osgEarth::Symbology::Style> dataPath_osgStyle;

				for (ConfigSet::const_iterator i=fdataSources.children().begin();i!=fdataSources.children().end();++i)
				{
					const osgEarth::Config& dataSource=*i;
					std::string dname = dataSource.child("dataname").value();
					std::string dataSourcePath = dataRootPath+"/"+dname+".fcs";

					std::string name = dataSource.child("name").value();
					std::map<std::string,std::string>::iterator itr = Dataname_Stylename.find(name);

					if (itr ==Dataname_Stylename.end())
					{
						continue;
					}

					for (ConfigSet::const_iterator i= fStyleGroups.children().begin();i!=fStyleGroups.children().end();++i)
					{
						const osgEarth::Config& geoStyle = *i;
						
						if (geoStyle.child("name").value()==itr->second)
						{
							osgEarth::Symbology::Style osgStyle;

							if(geoStyle.child("type").value()=="point")
							{
								geo_pointStyle pointStyle;
								pointStyle.color.value = geoStyle.child("renditions").child("pointrendition").child("color").child("value").value();
								pointStyle.color.transparent = atoi(geoStyle.child("renditions").child("pointrendition").child("color").child("transparent").value().c_str());
								pointStyle.size = (float) atof(geoStyle.child("renditions").child("pointrendition").child("size").value().c_str());

								createStylefromGeostyle(pointStyle,osgStyle);
							}
							else if(geoStyle.child("type").value()=="polygon")
							{
								geo_polyStyle polyStyle;
								polyStyle.FillColor.value = geoStyle.child("renditions").child("polygonrendition").child("fillcolor").child("value").value();
								polyStyle.FillColor.transparent = atoi(geoStyle.child("renditions").child("polygonrendition").child("fillcolor").child("transparent").value().c_str());
								polyStyle.EdgeColor.value = geoStyle.child("renditions").child("PolygonRendition").child("EdgeColor").child("Value").value();
								polyStyle.EdgeColor.transparent = atoi(geoStyle.child("renditions").child("polygonrendition").child("edgecolor").child("transparent").value().c_str());
								polyStyle.width = (float) atof(geoStyle.child("renditions").child("polygonrendition").child("width").value().c_str());

								createStylefromGeostyle(polyStyle,osgStyle);
							}
							else if (geoStyle.child("type").value()=="line")
							{
								geo_lineStyle lineStyle;
								lineStyle.color.value = geoStyle.child("renditions").child("linerendition").child("color").child("value").value();
								lineStyle.color.transparent = atoi(geoStyle.child("renditions").child("linerendition").child("color").child("transparent").value().c_str());
								lineStyle.width = (float) atof(geoStyle.child("renditions").child("linerendition").child("width").value().c_str());

								createStylefromGeostyle(lineStyle,osgStyle);
							}

							dataPath_osgStyle.insert(std::map<std::string,osgEarth::Symbology::Style>::value_type(dataSourcePath,osgStyle));

							break;
						}
					}
				}

				for (std::map<std::string,osgEarth::Symbology::Style>::iterator itr=dataPath_osgStyle.begin();itr!=dataPath_osgStyle.end();++itr)
				{
					std::string dbpath=itr->first;
					osgEarth::Symbology::Style sty = itr->second;
					createOptionsandLayers(dbpath,sty,type,map);
				}
			}

			//��????��
			static bool create(std::string xmlPath,float height,osgEarth::Map* map,GeoVectorRenderType type)
			{
				if (!osgDB::fileExists(xmlPath))
				{
					OE_NOTICE << "XML not exists " << std::endl;
					return false;
				}

				std::ifstream in(xmlPath.c_str());
				Config doc;
				doc.fromXML(in);

				if (doc.empty()||doc.children().empty())
				{
					OE_NOTICE << "Failed to get XML " << std::endl;
					return false;
				}

				Config geoMap = doc.child("geomapfile").child("geomap");

				//�������ݼ������Ӧ�ķ�������������
				std::map<std::string,std::string> Dataname_Stylename;
				Config geoMapLayers = geoMap.child("layers");

				for(ConfigSet::const_iterator i=geoMapLayers.children().begin();i!=geoMapLayers.children().end();++i)
				{
					Config geoFeatureLayer = *i;
					Dataname_Stylename.insert(std::map<std::string,std::string>::value_type(geoFeatureLayer.child("layersourcename").value(),geoFeatureLayer.child("layerstylename").value()));
				}

				////////////////////////////////////////////////////����xml�ļ����ڵ�·��ȷ��ʸ��Ҫ��ͼ���������ڵ�·��
				//std::string dataRootPath =  doc.child("GeoMapFile").child("GeoConnections").child("GeoConnection").child("Address").value();
				std::string dataRootPath = osgDB::getFilePath(xmlPath);

				Config fdataSources = doc.child("geomapfile").child("geodatasources");
				Config fStyleGroups = doc.child("geomapfile").child("geostylegroups").child("geostylegroup");
				Config xmlGeoConnections = doc.child("geomapfile").child("geoconnections");

				std::map<std::string,osgEarth::Symbology::Style> dataPath_osgStyle;

				for (ConfigSet::const_iterator i = fdataSources.children().begin(); i != fdataSources.children().end(); ++i)
				{
					const osgEarth::Config& dataSource=*i;
					std::string dname = dataSource.child("dataname").value();
					
					std::string dataSourcePath;
					dataSourcePath += dataRootPath;

					for (ConfigSet::const_iterator it = xmlGeoConnections.children().begin(); it != xmlGeoConnections.children().end(); ++it)
					{
						string strtemp = (*it).child("name").value();
						string strhah = dataSource.child("connection").value();
						string strFuck = (*it).child("address").value();

						if ((*it).child("name").value() == dataSource.child("connection").value())
						{
							dataSourcePath += (*it).child("address").value();
							break;
						}
					}

					dataSourcePath += "/"+ CodeHelp::UTF8_To_string(dname)+".fcs";
					dataSourcePath = CodeHelp::String_To_UTF8(dataSourcePath);

					std::string name = dataSource.child("name").value();
					std::map<std::string,std::string>::iterator itr = Dataname_Stylename.find(name);

					if (itr ==Dataname_Stylename.end())
					{
						continue;
					}
					//����Ҫ�ط�����������
					for (ConfigSet::const_iterator i= fStyleGroups.children().begin();i!=fStyleGroups.children().end();++i)
					{
						const osgEarth::Config& geoStyle = *i;

						if (geoStyle.child("name").value()==itr->second)
						{
							osgEarth::Symbology::Style osgStyle;
							//�����µ�Ҫ������ת��ΪosgEarth�е�Ҫ������
							if(geoStyle.child("type").value()=="point")//������
							{
								geo_pointStyle pointStyle;
								pointStyle.color.value = geoStyle.child("renditions").child("pointrendition").child("color").child("value").value();
								pointStyle.color.transparent = atoi(geoStyle.child("renditions").child("pointrendition").child("color").child("transparent").value().c_str());
								pointStyle.size = (float) atof(geoStyle.child("renditions").child("pointrendition").child("size").value().c_str());

								createStylefromGeostyle(pointStyle,osgStyle);
							}
                            //���������
							else if(geoStyle.child("type").value()=="polygon")
							{
								geo_polyStyle polyStyle;
								polyStyle.FillColor.value = geoStyle.child("renditions").child("polygonrendition").child("fillcolor").child("value").value();
								polyStyle.FillColor.transparent = atoi(geoStyle.child("renditions").child("polygonrendition").child("fillcolor").child("transparent").value().c_str());
								polyStyle.EdgeColor.value = geoStyle.child("renditions").child("PolygonRendition").child("EdgeColor").child("Value").value();
								polyStyle.EdgeColor.transparent = atoi(geoStyle.child("renditions").child("polygonrendition").child("edgecolor").child("transparent").value().c_str());
								polyStyle.width = (float) atof(geoStyle.child("renditions").child("polygonrendition").child("width").value().c_str());

								createStylefromGeostyle(polyStyle,osgStyle);
							}
                            //������
							else if (geoStyle.child("type").value()=="line")
							{
								geo_lineStyle lineStyle;
								lineStyle.color.value = geoStyle.child("renditions").child("linerendition").child("color").child("value").value();
								lineStyle.color.transparent = atoi(geoStyle.child("renditions").child("linerendition").child("color").child("transparent").value().c_str());
								lineStyle.width = (float) atof(geoStyle.child("renditions").child("linerendition").child("width").value().c_str());

								createStylefromGeostyle(lineStyle,osgStyle);
							}

							dataPath_osgStyle.insert(std::map<std::string,osgEarth::Symbology::Style>::value_type(dataSourcePath,osgStyle));
							break;
						}
					}
				}

                //�Զ�ȡ����xml�ļ��е�ÿһ��ͼ����������Ӧ��osgEarth�е�Ҫ��ͼ��
				for (std::map<std::string,osgEarth::Symbology::Style>::iterator itr=dataPath_osgStyle.begin();itr!=dataPath_osgStyle.end();++itr)
				{
					std::string dbpath=itr->first;
					osgEarth::Symbology::Style sty = itr->second;
                    //����osgEarth��map�е�ʸ��Ҫ��ͼ��
					createOptionsandLayers(dbpath,height,sty,type,map);
				}
			}
			
             ///////////////////////////////////���ݼ���Ҫ������ת��ΪosgEarthҪ��������osgEarth::Symbology::Style
			//�Ե���������
			static bool createStylefromGeostyle(geo_pointStyle gStyle,osgEarth::Symbology::Style& output)
			{
				output.getOrCreate<PointSymbol>()->size()=gStyle.size;
				osgEarth::Symbology::Color tcolor(gStyle.color.value);
				output.getOrCreate<PointSymbol>()->fill()->color()=osgEarth::Symbology::Color(tcolor.r(),tcolor.g(),tcolor.b(),(float)(gStyle.color.transparent/(float)255));

				return true;
			}
            //�Զ���������Ĵ���
			static bool createStylefromGeostyle(geo_polyStyle gStyle,osgEarth::Symbology::Style& output,bool bline=false)
			{
				if (bline)
				{
					osgEarth::Symbology::Color tecolor(gStyle.EdgeColor.value);
					output.getOrCreateSymbol<osgEarth::Symbology::LineSymbol>()->stroke()->color()=osgEarth::Symbology::Color(tecolor.r(),tecolor.g(),tecolor.b(),(float)(gStyle.EdgeColor.transparent/(float)255));
					output.getOrCreateSymbol<osgEarth::Symbology::LineSymbol>()->stroke()->width() = gStyle.width;
					output.getOrCreateSymbol<osgEarth::Symbology::RenderSymbol>()->lighting() =false;
				}

				osgEarth::Symbology::Color tcolor(gStyle.FillColor.value);
				output.getOrCreate<PolygonSymbol>()->fill()->color()=osgEarth::Symbology::Color(tcolor.r(),tcolor.g(),tcolor.b(),(float)(gStyle.FillColor.transparent/(float)255));

				return true;
			}

             //���������Ĵ���
			static bool createStylefromGeostyle(geo_lineStyle gStyle,osgEarth::Symbology::Style& output)
			{
				osgEarth::Symbology::Color tcolor(gStyle.color.value);
				output.getOrCreateSymbol<osgEarth::Symbology::LineSymbol>()->stroke()->color()=osgEarth::Symbology::Color(tcolor.r(),tcolor.g(),tcolor.b(),(float)(gStyle.color.transparent/(float)255));
				output.getOrCreateSymbol<osgEarth::Symbology::LineSymbol>()->stroke()->width() = gStyle.width;
				output.getOrCreateSymbol<osgEarth::Symbology::RenderSymbol>()->lighting() =false;

				return true;
			}

			/////////////////////////////////////create Option and Layer
			//���ݻ�ȡ��xmlʸ��Ҫ�������ļ��е������Լ���Ⱦ��ʽ������osgEarth�е�ʸ��ͼ������༰����Ӧͼ��
		    static bool createOptionsandLayers(std::string dbPath,osgEarth::Symbology::Style& osgStyle,GeoVectorRenderType type,osgEarth::Map* map)
			{
				if (type == GEOVECTORMODEL)
				{
					GEOFeatureOptions geoFeaOpt;
					geoFeaOpt.url()=dbPath;

					FeatureDisplayLayout layout;
					osg::ref_ptr<StyleSheet> stys=new StyleSheet;
					//geoFeaOpt.createLayoutandStyle(layout,stys);
					//����ʸ��ͼ��
					geoFeaOpt.createLayoutandStyle(layout,osgStyle,stys);

					osgEarth::Drivers::FeatureGeomModelOptions geomOptions;
					geomOptions.featureOptions() = geoFeaOpt;
					geomOptions.layout()=layout;
					geomOptions.styles() = stys.release();
					geomOptions.depthTestEnabled()=false;
					/*geomOptions.styles() = new StyleSheet();
					Style style;
					style.setName("style");
					LineSymbol* ls = style.getOrCreateSymbol<LineSymbol>();
					ls->stroke()->color() = Color::Yellow;
					ls->stroke()->width() = 2.0f;
					style.getOrCreate<PolygonSymbol>()->fill()->color()=Color(Color::Cyan, 0.5);
					geomOptions.styles()->addStyle(style);*/
					//geomOptions.enableLighting() = false;

					osgEarth::ModelLayerOptions layerOptions( dbPath, geomOptions );
					osg::ref_ptr<osgEarth::ModelLayer> mlayer=new osgEarth::ModelLayer(layerOptions);
					//mlayer->setOpacity(0.3);
					map->addModelLayer(mlayer);
				}
                 //��ʸ��դ�񻯵ķ�ʽ��Ⱦ
				else if (type == GEOVECTORIMAGE)
				{
					GEOFeatureOptions geoFeaOpt;
					geoFeaOpt.url()=dbPath;
					
					GeoGlobe::GeoVector::GEORasterizerOptions rasterOptions;
					rasterOptions.featureOptions()=geoFeaOpt;
					rasterOptions.styles() = new StyleSheet();
					rasterOptions.styles()->addStyle(osgStyle);

					osgEarth::Drivers::ImageLayerOptions ilo=osgEarth::Drivers::ImageLayerOptions(dbPath,rasterOptions);
					ilo.maxLevel()=15;
					map->addImageLayer(new ImageLayer(ilo));
					//map->addImageLayer(new ImageLayer(dbPath,rasterOptions));
				}

				return false;
			}
            //���ݻ�ȡ��xmlʸ��Ҫ�������ļ��е������Լ���Ⱦ��ʽ������osgEarth�е�ʸ��ͼ������༰����Ӧͼ�㣬����ʸ��̧��һ���߶�
			static bool createOptionsandLayers(std::string dbPath,float height,osgEarth::Symbology::Style& osgStyle,GeoVectorRenderType type,osgEarth::Map* map)
			{
				if (type == GEOVECTORMODEL)
				{
					GEOFeatureOptions geoFeaOpt;
					geoFeaOpt.height()=height;
					geoFeaOpt.url()=dbPath;

					FeatureDisplayLayout layout;
					osg::ref_ptr<StyleSheet> stys=new StyleSheet;
					//geoFeaOpt.createLayoutandStyle(layout,stys);
					geoFeaOpt.createLayoutandStyle(layout,osgStyle,stys);

					m_Xmin = geoFeaOpt.m_Xmin; 
					m_Xmax = geoFeaOpt.m_Xmax;
					m_Ymin = geoFeaOpt.m_Ymin;
					m_Ymax = geoFeaOpt.m_Ymax;

					osgEarth::Drivers::FeatureGeomModelOptions geomOptions;
					geomOptions.featureOptions() = geoFeaOpt;
					geomOptions.layout()=layout;
					geomOptions.styles() = stys.release();
					geomOptions.depthTestEnabled()=false;
					//geomOptions.depthTestEnabled()=false();
					/*geomOptions.styles() = new StyleSheet();
					Style style;
					style.setName("style");
					LineSymbol* ls = style.getOrCreateSymbol<LineSymbol>();
					ls->stroke()->color() = Color::Yellow;
					ls->stroke()->width() = 2.0f;
					style.getOrCreate<PolygonSymbol>()->fill()->color()=Color(Color::Cyan, 0.5);
					geomOptions.styles()->addStyle(style);*/
					//geomOptions.enableLighting() = false;

					osgEarth::ModelLayerOptions layerOptions( dbPath, geomOptions );
					map->addModelLayer( new osgEarth::ModelLayer(layerOptions) );

				}
				else if (type == GEOVECTORIMAGE)
				{
					GEOFeatureOptions geoFeaOpt;
					geoFeaOpt.url()=dbPath;
					
					GeoGlobe::GeoVector::GEORasterizerOptions rasterOptions;
					rasterOptions.featureOptions()=geoFeaOpt;
					rasterOptions.styles() = new StyleSheet();
					rasterOptions.styles()->addStyle(osgStyle);

					map->addImageLayer( new ImageLayer(dbPath, rasterOptions) );
				}

				return false;
			}
		};

	}
}
#endif