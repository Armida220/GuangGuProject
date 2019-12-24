#ifndef GEOGLOBE_MODEL_QUADMODELTILEDRIVER
#define GEOGLOBE_MODEL_QUADMODELTILEDRIVER 1

#include <Model/ModelOptions.h>
#include <Model/ModelTile.h>
#include <Model/ModelTilePagedLOD.h>
#include <osgEarthAnnotation/PlaceNode>
#include <osg/ShapeDrawable>
#include <Base/TilePagedLOD.h>

using namespace osgEarth::Annotation;
using namespace GeoGlobe::Base;

namespace GeoGlobe{ namespace Model{


	/*α�����ͨ��α������ܽ�ģ����Ƭ��DataBasePager(�߳�)�ķ�ʽ����*/
	class QuadModelTileDriver : public osgDB::ReaderWriter
	{
	public:
		QuadModelTileDriver() { supportsExtension("quadmodeltile","user defined format");}

		virtual const char* className()
		{
			return "User Defined Tile Engine";
		}

		//�Ӵ����url�н�����Ƭ�ļ���X��Y��
		void parseFileName(std::string uri,int& level,int& row,int& col) const
		{
			std::vector<std::string> vecStr;
			std::string lessExtension;
			std::string ext;
			lessExtension=osgDB::getNameLessExtension(uri);

			for (int i=0;i<3;i++)
			{
				ext=osgDB::getFileExtension(lessExtension);
				vecStr.push_back(ext);
				lessExtension=osgDB::getNameLessExtension(lessExtension);
			}
			level= atoi(std::string(vecStr[2]).c_str());
			row= atoi(std::string(vecStr[1]).c_str());
			col= atoi(std::string(vecStr[0]).c_str());
		}

		//�����ĸ�����Ƭ������4����ʹ���ܹ��ٴη���
		osg::Node * createTile(osg::Node* node,TileKey tileKey,ModelLayerOptions* options) const
		{
			//����PageLOD��ʵ��ģ����Ƭ�ٷ��ѵ�����
			osg::ref_ptr<ModelTilePagedLOD> tile=new ModelTilePagedLOD(options->_mapNode);
			tile->setName(tileKey.str());

			int level;
			unsigned int row,col;
			level=tileKey.getLevelOfDetail();
			tileKey.getTileXY(col,row);

			//����PageLOD�����ĵ㼰���Ӱ뾶��ǿ�ҽ����ȿ�osg����pagelod�Ľ̳�
			//�����о�������룬�����򼸺����к��Ĺ��ܶ���Χ��pagelodչ����
			//����α�������̬����ɾ����LOD�л�����PagedLod�ж�������
			double radius;
			osg::Vec3d center;
			osgEarth::GeoPoint gp=tileKey.getExtent().getBoundingGeoCircle().getCenter();
			gp.toWorld(center);
			radius=tileKey.getExtent().getBoundingGeoCircle().getRadius();
			float minRange = (float)(radius*6 );
			tile->setRangeMode( osg::LOD::DISTANCE_FROM_EYE_POINT );
			tile->setTileKey(tileKey);
			tile->setCenter  ( center );
			tile->setRadius(minRange);
			tile->_setting=options->_setting;
			tile->_spliteFactor=2.0f;

			if (node!=NULL)
			{
				ModelTile* tileNode =(ModelTile*) node;

				osg::Vec3d localPoint;
				osg::Vec3d worldPoint;
				double z;
				//options->_mapNode->getMapSRS()->transformFromWorld(tileNode->getCenter(),localPoint,&z);
				options->_mapNode->getMapSRS()->transformToWorld(osg::Vec3d(gp.x(),gp.y(),tileNode->_elevation),worldPoint);
				//tile->setInitialBound(osg::BoundingSphere(worldPoint,radius));
				//PageLOD�ĵ�һ����ģ����Ƭ����
				tile->addChild   ( tileNode);
				tile->setRange( 0, 0, 8000 );
				//PageLOD�ĵڶ���ָ����һ����QuadModelTile��Ҳ�����¼���4������Ƭ
				//tile->setFileName( 1, Stringify() <<"Model"<<"."<<level << "." << col <<"." <<row<<".quadmodeltile" );
				//tile->setRange( 1, 0, minRange );
				if (level == options->_minLevel - 2)
				{
					tile->setFileName( 1, Stringify() <<"Model"<<"."<<level << "." << col <<"." <<row<<".quadmodeltile" );
					tile->setRange( 1, 0, minRange );
				}
				tile->_normalTraverse=true;
			}
			//������Ƭû��ģ�����ݵ�Ҳ��Ҫ������ȥ
			//else if((level+1)<=options->_minLevel)
			else if(level == options->_minLevel - 2)
			{
				tile->setFileName(0, Stringify() <<"Model"<<"."<< level << "." << col <<"." <<row<<".quadmodeltile" );
				tile->setRange( 0, 0, minRange );
				tile->_normalTraverse=true;
				//tile->setCullingActive(false);
			} 
			else
			{
				//return NULL;
				return tile.release();
			}

			tile->setDatabaseOptions(options);
			return tile.release();
		}

		osg::Node * createTile2(osg::Node* node,TileKey& tileKey,ModelLayerOptions* options) const
		{
			osg::ref_ptr<TilePagedLOD> tile=new TilePagedLOD(tileKey,options->_mapNode);
			
			int level;
			unsigned int row,col;
			level=tileKey.getLevelOfDetail();
			tileKey.getTileXY(col,row);

			double radius;
			osg::Vec3d center;
			osgEarth::GeoPoint gp=tileKey.getExtent().getBoundingGeoCircle().getCenter();
			gp.toWorld(center);

		 osgEarth::GeoExtent extent = tileKey.getExtent();
			osgEarth::GeoPoint lowerLeft(extent.getSRS(), extent.xMin(), extent.yMin(), 0.0, ALTMODE_ABSOLUTE);
			osgEarth::GeoPoint upperRight(extent.getSRS(), extent.xMax(), extent.yMax(), 0.0, ALTMODE_ABSOLUTE);
			osg::Vec3d ll, ur;
			lowerLeft.toWorld( ll );
			upperRight.toWorld( ur );
			radius = (ur - ll).length() / 2.0;
			float minRange = (float)(radius*6 );

			tile->setRangeMode( osg::LOD::DISTANCE_FROM_EYE_POINT );
			//tile->setTileKey(tileKey);
			//tile->_mapNode=options->_mapNode;
			//tile->setInitialBound(osg::BoundingSphere(center,radius));
			/*tile->setCenter  ( center );
			tile->setRadius(minRange);*/
			//tile->getBound();
			/*node->setRadius(radius);
			node->setCen*/
			//node->setInitialBound(osg::BoundingSphere(tile->computeBound()));
			//tile->useAutoClamp();

			if (node!=NULL)
			{
				tile->addChild   ( node/*temp*/);
				tile->setFileName( 1, Stringify() <<"PlaceName"<<"."<<level << "." << col <<"." <<row<<".quadmodeltile" );
				/*tile->setCenter(tileNode->getBound().center());
				tile->setRadius(tileNode->getBound().radius());*/
					
				tile->setRange( 0, minRange, FLT_MAX );
				tile->setRange( 1, 0, minRange );
				/*bool c=tile->isCullingActive();
					
				int a=tile->getNumChildrenWithCullingDisabled();
				int b=0;*/
				/*tile->_normalTraverse=false;
				tile->_hasRealData=true;*/
			    //tile->useAutoClamp();
				//options->_mapNode->getTerrain()->addTerrainCallback(new AutoClampCallback(tile));
			}
			else if((level+1)<=options->_minLevel)
			{
				//tile->addChild   ( new PlaceNode(options->_mapNode,gp,"no"+tileKey.str()));
				
				tile->setFileName(0, Stringify() <<"PlaceName"<<"."<< level << "." << col <<"." <<row<<".quadmodeltile" );
				//tile->setRange( 0, minRange, FLT_MAX );
				tile->setRange( 0, 0, minRange );
				//tile->setCenter(center);
				//tile->_hasRealData=true;
				//tile->setInitialBound(osg::BoundingSphere(center,radius));
			}
			else 
				return NULL;

			tile->setDatabaseOptions(options);

			return tile.release();
		}

		std::string createModelTileName(std::string gmdxFile, TileKey& key) const
		{
			return Stringify() <<gmdxFile<<"_"<<key.str() <<".modelTile"; 
		}

        //�����ĸ�����Ƭ��ģ��osgEarthʵ���Ĳ������β���д�ã��������ο�MPTerrainEngineDriver
		osg::ref_ptr<osg::Node> createNode(TileKey& tileKey,ModelLayerOptions* options) const
		{
			osg::ref_ptr<osg::Group> quad = new osg::Group();
			if (tileKey.getLOD()+2>options->_maxLevel)
				return quad.release();

			osg::ref_ptr<osg::Node> node[4];
			if (tileKey.getLOD()+2 >= options->_minLevel )
			{
				//�����ĸ�����Ƭ
				for(unsigned q=0; q<4; ++q)
				{
					//��ȡ����Ƭ��Keyֵ
					TileKey child = tileKey.createChildKey(q);
					std::string modelTileName=options->createModelTileName(child.getLevelOfDetail()+1,child.getTileX(),child.getTileY());
					if (!osgEarth::Registry::instance()->isBlacklisted(modelTileName))
					{
						//����ModelTile����Ƭ
						osg::ref_ptr<ModelTileOptions> modelTileOptions=new ModelTileOptions(child,options);
						osg::ref_ptr<GeoGlobe::Model::ModelTile> modelTile=new GeoGlobe::Model::ModelTile(modelTileOptions);
						if (modelTile->hasRealData())
						{
							node[q]=modelTile;
						}
						else
						{
							osgEarth::Registry::instance()->blacklist(modelTileName);
						}
					}
				}

			}

			bool makeTile ;

			// If there's a minimum LOD set, and we haven't reached it yet, make the tile.
			if ( tileKey.getLOD()+2 < options->_minLevel )
			{
				makeTile = true;
			}

			// Otherwise, only make the tile if at least one quadrant has REAL data
			else
			{
				makeTile = false;
				for(unsigned q=0; q<4; ++q)
				{
					if ( node[q] )
					{
						makeTile = true;
						break;
					}
				}
			}

			//Ϊ����Ƭ����PageLOD����������Ƭ�Ż��������
			//�����ǹ����������Ƭ���ݣ�������ʹ��Ƭ�����ٷ��ѵ�����������Ƚ��ƣ���Ҫ��Ϊ��Ӧ��OSG�ڲ��ķ�ҳ���ݹ������
			//ʵ���Ĳ�����̬���أ����������ѣ���Ҫ��ѧϰosg::PageLOD�������ݣ�����бӰ�񲿷֣��ҽ������������˼�
			//��Ϊ��������ԭ��ģ�ͺ͹��߻��Ǳ���ԭ��
			if ( makeTile )
			{
				for( unsigned q=0; q<4; ++q )
				{
					//Ϊÿ������Ƭ����ModelTilePagedLod
					osg::ref_ptr<osg::Node> tile=createTile((node[q]),tileKey.createChildKey(q),options);
					//��������ɹ��ͽ����������Ƭ����
					if (tile)
					{
						quad->addChild( tile );
					}
				}
			}
			return quad.release();
		}

		//�������ں���
		virtual ReadResult readNode(const std::string& uri, const Options* options) const
		{
			std::string ext = osgDB::getFileExtension(uri);

			if (acceptsExtension(ext))
			{
				osg::ref_ptr<ModelLayerOptions> modelLayerOptions=(ModelLayerOptions*)(options) ;

				//ͨ�����������URL��ȡ��Ƭ���ļ���,x,y����
				int level, row, col;
				parseFileName(uri,level, col, row);

				TileKey tileKey=TileKey(level,col,row,modelLayerOptions->_mapNode->getMap()->getProfile());

				//�����ĸ�����Ƭ��ģ��osgEarthʵ���Ĳ������β���д�ã��������ο�MPTerrainEngineDriver
				osg::ref_ptr<osg::Node> node=createNode(tileKey,modelLayerOptions);

				if (node.valid())
				{
					//return ReadResult( node.get(), ReadResult::FILE_LOADED );
					return ReadResult( node.release(), ReadResult::FILE_LOADED );
				}
				else
				{
					return ReadResult::FILE_NOT_FOUND;
				}
			}
			else
			{
				return ReadResult::FILE_NOT_HANDLED;
			}
		}
	};

	REGISTER_OSGPLUGIN(QuadModelTileDriver, QuadModelTileDriver);

}}

#endif
