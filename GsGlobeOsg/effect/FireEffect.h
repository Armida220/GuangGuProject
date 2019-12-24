#ifndef GEOGLOBE_EFFECT_FIREEFFECT
#define GEOGLOBE_EFFECT_FIREEFFECT 1
#include <osg/LOD>
#include <osg/Group>
#include <osg/Geode>

#include <osgParticle/Particle>
#include <osgParticle/FireEffect>
#include <osgParticle/ParticleSystem>
#include <osgParticle/ParticleSystemUpdater>
#include <osgParticle/ModularEmitter>
#include <osgParticle/ModularProgram>
#include <osgParticle/RandomRateCounter>
#include <osgParticle/SectorPlacer>
#include <osgParticle/RadialShooter>
#include <osgParticle/AccelOperator>
#include <osgParticle/FluidFrictionOperator>
#include <osg/BlendFunc>
#include <osg/Depth>
#include <osgEarth/Map>
#include <osgEarthUtil/ObjectLocator>
namespace GeoGlobe
{
	namespace Effect
	{
	//ʵ�ֻ���������Ч�����ֻ�ǽ�osg�Դ��Ļ�����Ч��osgEarth��λ�����˸����ӣ�
	//�������ʵ������Ч������ο�osg�й���������Ч�Ĳ���
    class FireEffect:public osg::LOD
	{

	public:
		//osg�Դ��Ļ�������
		osg::ref_ptr<osgParticle::FireEffect> _fire;
		//��λ����������ϵͳ��λ���������ָ��λ��
		osg::ref_ptr<osgEarth::Util::ObjectLocatorNode> _locator;

		FireEffect(double lon,double lat,double altitude,osgEarth::Map* map,std::string EffectDirectory,float scale=1.2f,float intensity=5.0f)
		{

			//�������ӳ��ֵ�λ��
			_locator = new osgEarth::Util::ObjectLocatorNode( map );
			_locator->getLocator()->setPosition(osg::Vec3d(lon,lat,altitude) );



			//����osgĬ�ϵ�������Ч
			_fire=new osgParticle::FireEffect(osg::Vec3d(0,0,0),scale,intensity);
			//fireEffect->setWind(osg::Vec3d(0,0,10));
			//���þֲ�����ϵ
			_fire->setUseLocalParticleSystem(false);
			//��������
			_fire->setEmitterDuration(FLT_MAX);
			//����������λ��
			_fire->setTextureFileName(EffectDirectory+"/smoke.rgb");
			osg::Geode *geode = new osg::Geode;   
            geode->addDrawable(_fire->getParticleSystem());

            //����Ч�ŵ���λ����
			_locator->addChild(_fire);
			_locator->addChild(geode);


			//������Чλ��Զ��ʱ�򲻸��»�������
			osg::Vec3d center;
			map->getProfile()->getSRS()->transformToWorld(osg::Vec3d(lon,lat,altitude),center);
			this->setCenter(center);
			this->setRange(0,0,1000);
			this->addChild(_locator);

		}

	};


	}
}


#endif
