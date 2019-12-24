#ifndef GEOGLOBE_MODEL_LODMODEL
#define GEOGLOBE_MODEL_LODMODEL 1
#include <osg/PagedLOD>
#include <osg/CullStack>
#include <algorithm>
//#include <Model/ModelDriver.h>
#include <osg/ShapeDrawable>
#include <Model/Model.h>
#include <Tool/GlobalSetting.h>

//#include <QuadTreeNode/Model.h>

using namespace osg;
namespace GeoGlobe
{

	namespace Model
	{
		/*Lodģ�ͣ�������ģ�͵ļ���������ֻ����ʵ��ģ�͵�LOD��̬���ȵĹ�����
		 �о�����֮ǰ�������˽�pagedlod����ֻ����ԭ��������������΢��д��������ؼ�������traverse������
		 �ⲿ�ֱȽϸ��ӣ���ΪԴ����󲿷ֶ����õ�pagelod������Ҳû����ʲôע��*/

		class LodModel : public osg::PagedLOD
		{
		public:
			//LodModel();
			//LodModel(const LodModel&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);
			/*Lodģ���Ƿ�ʰȡ*/
			bool _selectd;
			
			bool _visble;
			/*Lodģ�Ͱ�Χ�а뾶*/
			double _modelRadius;
			//virtual void accept(osg::NodeVisitor& nv) 
			//{ 
			//	if (nv.validNodeMask(*this)) 
			//	{ 
			//		nv.pushOntoNodePath(this); nv.apply(*this); nv.popFromNodePath(); 
			//	} 
			//}
			/*Lodģ�͵�������Ϣ*/
			//osg::ref_ptr<ModelOptions> _options;
			~LodModel();
			/*���캯�������ø���ģ�͵�LOD���ӷ�Χ*/
			LodModel(LodModelOptions* options);

			osg::ref_ptr<LodModelOptions> _options;

			std::string createModelName(std::string dbName,ULONGLONG featureKey,int lod);


            /*����ģ�ͱ�ʰȡ���״̬*/
			void select(bool select);

			void SetVisible(bool bVisble);

			void traverse(NodeVisitor& nv);


#if 0
			void travseModel(int i,bool updateTimeStamp,double timeStamp,unsigned int frameNumber,int &lastChildTraversed,NodeVisitor& nv);
#endif
		};
	}
}
#endif
