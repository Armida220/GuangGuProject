#include "LodModel.h"

using namespace osg;

/*Lodģ�͵�������Ϣ*/
//osg::ref_ptr<ModelOptions> _options;
GeoGlobe::Model::LodModel::~LodModel()
{

}
/*���캯�������ø���ģ�͵�LOD���ӷ�Χ*/
GeoGlobe::Model::LodModel::LodModel(LodModelOptions* options):PagedLOD()
{
	_options=options;

	stringstream ss;
	ss<<options->_feature->m_nFID;
	setName(ss.str());

	_visble=true;
	osg::Vec3d maxVertex;
	_options->_mapNode->getMapSRS()->transformToWorld(osg::Vec3d(options->_feature->m_MaxVertex.x(),options->_feature->m_MaxVertex.y(),options->_feature->m_MaxVertex.z()),maxVertex);
	osg::Vec3d minVertex;
	_options->_mapNode->getMapSRS()->transformToWorld(osg::Vec3d(options->_feature->m_MinVertex.x(),options->_feature->m_MinVertex.y(),options->_feature->m_MinVertex.z()),minVertex);
	_modelRadius=(maxVertex-minVertex).length()/2;

    /*����ģ�͵�LOD��Χ*/
	LOD_INFOList lodList=options->_feature->getLOD_INFOList();
	for (int i=0;i<lodList.size();i++)
	{
		std::string modelName=_options->createModelName(lodList[i].unGeometryID,i);
		this->setFileName(i,modelName);

		if (i==lodList.size()-1)
		{
			this->setRange( i, 0, lodList[i].dSwitchOut*_options->_setting->_lodFactor+_modelRadius );
		}
		else
			this->setRange( i, lodList[i].dSwitchIn*_options->_setting->_lodFactor+_modelRadius, lodList[i].dSwitchOut*_options->_setting->_lodFactor+_modelRadius );

	}

    /*����ģ�͵����ĵ�*/
	this->setCenter(options->_centerPos);
	this->setDatabaseOptions(options);
};


std::string GeoGlobe::Model::LodModel::createModelName(std::string dbName,ULONGLONG featureKey,int lod)
{
	return Stringify() <<dbName<<"."<<featureKey <<"."<<lod<<".model";

};

			

/*����ģ�ͱ�ʰȡ���״̬*/
void GeoGlobe::Model::LodModel::select(bool select)
{
	getOrCreateStateSet()->setMode(GL_LIGHTING,select|osg::StateAttribute::PROTECTED);

}

void GeoGlobe::Model::LodModel::SetVisible(bool bVisble)
{
	_visble = bVisble;
}

void GeoGlobe::Model::LodModel::traverse(NodeVisitor& nv)
{
	if(!_visble)
		return;

	osg::PagedLOD::traverse(nv);
}

   

#if 0
void GeoGlobe::Model::LodModel::travseModel(int i,bool updateTimeStamp,double timeStamp,unsigned int frameNumber,int &lastChildTraversed,NodeVisitor& nv)
{
	if (i==-1&&i>=_children.size())
	{
		return;
	}

	Model* model = dynamic_cast<Model*>(_children[i].get());

			
	if (model->initModel())
	{

		if (updateTimeStamp)
		{
			_perRangeDataList[i]._timeStamp=timeStamp;
			_perRangeDataList[i]._frameNumber=frameNumber;
		}

						_children[i]->accept(nv);
						lastChildTraversed = (int)i;

	}
	else
	{
		travseModel(i-1,updateTimeStamp, timeStamp,frameNumber,lastChildTraversed,nv);
	}

}
#endif

