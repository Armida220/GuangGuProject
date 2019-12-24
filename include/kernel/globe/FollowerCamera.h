#pragma once
#include <utility.h>
#include <GsReference.h>
#include <Element.h>

GLOBE_NS

enum Modal
{
	//��ֵ���У������ڸ��²�Ƶ���Ķ���
	interp,
	//������У������ڸ���Ƶ���Ķ���
	follow
};

class GS_API FollowerCamera :public GeoStar::Utility::GsRefObject
{
public:

	FollowerCamera(Modal eModel = follow);

	virtual ~FollowerCamera();
	//����汻���ŷ���
	void Bind(Element* ptrElement);
	//������ŷ���
	void Unbind(Element* ptrElement);
	//���½�������
	void ReEstablish();
	//���ø���ģʽ
	void setModal(Modal eModel);

private:
	void Init();

	void OnPositionChange(KERNEL_NAME::GsRawPoint3D point);

	std::vector<KERNEL_NAME::GsRawPoint3D> m_vecPos;

	time_t m_preTime;

	GsReferencePtr m_ptrHandle;	
	ElementPtr m_ptrElement;
	Modal m_eModal;
};

GS_SMARTER_PTR(FollowerCamera);

GLOBE_ENDNS
