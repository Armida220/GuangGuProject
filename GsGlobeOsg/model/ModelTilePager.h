#ifndef GEOGLOBE_MODEL_TILEPAGER
#define GEOGLOBE_MODEL_TILEPAGER 1

#include <osgEarth/Map>
#include <osgEarth/MapNode>
#include <osgDB/FileNameUtils>
#include <osgDB/ReaderWriter>
#include "Model/ModelOptions.h"

using namespace osgEarth;
namespace GeoGlobe
{
	namespace Model
	{
		//�򻯵���Ƭ�Ĳ���������ɲο�osgEarth2.7��PageTest������
		class ModelTilePager : public osg::Group
		{
		public:
			//ModelTilePager(const osgEarth::Profile* profile):
			//  _profile( profile ),
			//	  _rangeFactor( 1.5 ),
			//	  _additive(false),
			//	  _minLevel(0),
			//	  _maxLevel(30),
			//	  _west(-180),
			//	  _east(180),
			//	  _south(-90),
			//	  _north(90),
			//	  _visible(true)
			//  {
			//	  _options = new osgDB::Options;
			//	  _options->setUserData( this );

			//  }

			  ModelTilePager(const osgEarth::Profile* profile,ModelLayerOptions* options):
			      _profile( profile ),
				   _options( options ),
				  _rangeFactor( 1.0 ),
				  _additive(false),
				  _minLevel(0),
				  _maxLevel(30),
				  _west(-180),
				  _east(180),
				  _south(-90),
				  _north(90),
				  _visible(true)
			  {
				  _options->setUserData( this );
			  }

			  void build()
			  {
				  addChild( buildRootNode() );
			  }
			  //additive��ʾ�����ӽڵ�ʱ�����ظ��ڵ�����
			  bool getAdditive() { return _additive; }
			  void setAdditive(bool additive) { _additive = additive; }
			  
			  //ͼ��Ԫ��Ϣ�����úͶ�ȡ
			  unsigned int getMinLevel() const { return _minLevel; }
			  void setMinLevel(unsigned int minLevel) { _minLevel = minLevel; }

			  unsigned int getMaxLevel() const { return _maxLevel; }
			  void setMaxLevel(unsigned int maxLevel) { _maxLevel = maxLevel; }

			  void setExtend(double west,double east,double north,double south)
			  {
				  _west = west;
				  _east = east;
				  _north = north;
				  _south = south;
			  }

			  //������Ƭ�İ�Χ�У�����������ᵼ����Ƭ���ѳ�������Ĭ�����޵��εĵر�Ϊ׼��
			  //�����ʵ���θ��ڵ���뾶����ڣ��ᵼ����Ƭ���ѳ�����
			  osg::BoundingSphered getBounds(const TileKey& key)
			  {
				  int samples = 6;

				  GeoExtent extent = key.getExtent();

				  double xSample = extent.width() / (double)samples;
				  double ySample = extent.height() / (double)samples;

				  osg::BoundingSphered bs;
				  for (int c = 0; c < samples+1; c++)
				  {
					  double x = extent.xMin() + (double)c * xSample;
					  for (int r = 0; r < samples+1; r++)
					  {
						  double y = extent.yMin() + (double)r * ySample;
						  osg::Vec3d world;

						  GeoPoint samplePoint(extent.getSRS(), x, y, 0, ALTMODE_ABSOLUTE);

						  GeoPoint wgs84 = samplePoint.transform(osgEarth::SpatialReference::create("epsg:4326"));
						  wgs84.toWorld(world);
						  bs.expandBy(world);
					  }
				  }
				  return bs;
			  }

              //�����Ĳ������ڵ�
			  osg::Node* buildRootNode()
			  {
				  //����������Ƭ
				  osg::Group* root = new osg::Group;
				  std::vector< TileKey > keys;
				  GeoExtent ext=GeoExtent(_profile->getSRS(),_west,_south,_east,_north);
				  _profile->getIntersectingTiles(ext,_minLevel,keys);

				  for (unsigned int i = 0; i < keys.size(); i++)
				  {
					  root->addChild( createPagedNode( keys[i] ) );
				  }
				  return root;
			  }

             //����ָ��Keyֵ����Ƭ������ֻ���麯����ͨ����д�ⲿ��ʵ�־���Ӧ��
			  virtual osg::Node* createNode( const TileKey& key )
			  {
				  return NULL;
			  }
              //Ϊ�������Ƭ���PageLOD���ԣ�ʵ���ٷ�������
			  osg::PagedLOD* createPagedNode( const TileKey& key )
			  {
				  osg::BoundingSphered tileBounds = getBounds( key );

				  osg::PagedLOD* plod = new osg::PagedLOD;
				  plod->setCenter( tileBounds.center() );
				  plod->setRadius( tileBounds.radius() );

				  // Create the actual data for this tile.
				  osg::Node* node = createNode( key );
				  if (!node && key.getLevelOfDetail() < _minLevel)
				  {              
					  // If we couldn't create any data, just create an empty group.  That's ok.
					  node = new osg::Group;
				  }
				  if (!node) return 0;
				  plod->addChild( node );

				  if(key.getLevelOfDetail() >= _maxLevel)
				  {
					  plod->setRange( 0, 0, FLT_MAX );
					  return plod;
				  }

				  std::stringstream buf;
				  buf << key.getLevelOfDetail() << "_" << key.getTileX() << "_" << key.getTileY() << ".modeltile_pager";

				  std::string uri = buf.str();

				  // Now setup a filename on the PagedLOD that will load all of the children of this node.
				  plod->setFileName(1, uri);
				  plod->setDatabaseOptions( _options.get() );

				  // Setup the min and max ranges.

				  // This setups a replacement mode where the parent will be completely replaced by it's children.
				  float minRange = (float)(tileBounds.radius() * _rangeFactor);

				  if (!_additive)
				  {
					  // Replace mode, the parent is replaced by it's children.
					  plod->setRange( 0, minRange, FLT_MAX );
					  plod->setRange( 1, 0, minRange );
				  }
				  else
				  {
					  // Additive, the parent remains and new data is added
					  plod->setRange( 0, 0, FLT_MAX );
					  plod->setRange( 1, 0, minRange );
				  }

				  return plod;
			  }

			//��������
			virtual void traverse(NodeVisitor& nv)
			{
				//������ò��ɼ��Ͳ�����
				if(!_visible)
					return;

				//�����ӽڵ�
				for(NodeList::iterator itr=_children.begin();
					itr!=_children.end();
					++itr)
				{
					(*itr)->accept(nv);
				}
			}

              //���ɳ����Ĳ���
			  osg::Node* loadKey( const TileKey& key )
			  {       
				  osg::ref_ptr< osg::Group >  group = new osg::Group;
				  //�����ĸ��ӽڵ�
				  for (unsigned int i = 0; i < 4; i++)
				  {
					  TileKey childKey = key.createChildKey( i );

					  osg::PagedLOD* plod = createPagedNode( childKey );
					  if (plod)
					  {
						  group->addChild( plod );
					  }
				  }
				  if (group->getNumChildren() > 0)
				  {
					  return group.release();
				  }
				  return 0;
			  }

			  const osgEarth::Profile* getProfile()
			  {
				  return _profile.get();
			  }

			  //Ϊtrue��ʾ�����¼���Ƭʱ�ϼ���Ƭ���ᱻ�������������
			  bool _additive;
			  double _rangeFactor;

			  //�����С����
			  unsigned int _minLevel;
			  unsigned int _maxLevel;
			  //��γ�ȷ�Χ
			  double _west;
			  double _east;
			  double _north;
			  double _south;
			  //���ĵ�λ��
			  osg::Vec2d _centerGeo;
			  //�Ƿ�ɼ�
			  bool _visible;

		public:
			  //����������������ϵ
			  osg::ref_ptr< const osgEarth::Profile > _profile;
			  osg::ref_ptr< ModelLayerOptions > _options;
		};

        /*α�����ʵ��ģ��ʵʱ����*/
		struct ModelTilePagerPseudoLoader : public osgDB::ReaderWriter
		{
			ModelTilePagerPseudoLoader()
			{
				supportsExtension( "modeltile_pager", "" );
			}

			const char* className()
			{ // override
				return "Simple Pager";
			}

            /*α�����ں���*/
			ReadResult readNode(const std::string& uri, const Options* options) const
			{
				if ( !acceptsExtension( osgDB::getLowerCaseFileExtension(uri) ) )
					return ReadResult::FILE_NOT_HANDLED;

				unsigned lod, x, y;
				sscanf( uri.c_str(), "%d_%d_%d.%*s", &lod, &x, &y );

				ModelTilePager* pager = dynamic_cast< ModelTilePager*>(const_cast<Options*>(options)->getUserData());
				if (pager)
				{
					return pager->loadKey( TileKey( lod, x, y, pager->getProfile() ) );
				}

				return ReadResult::ERROR_IN_READING_FILE;
			}
		};

		REGISTER_OSGPLUGIN(modeltile_pager, ModelTilePagerPseudoLoader);
	}
}
#endif
