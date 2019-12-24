#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtExplorer.h"
#include <QPainter>
#include <qt/GsGeospace3DQt.h>

class QTreeWidgetItem;
class QSplitter;
class QDockWidget;
class QListWidget;
class QTreeWidgetItem;
class QTreeWidget;
class QListWidgetItem;
class ViewerWidget;

namespace osg
{
	class Group;
}

#define PADDING 1
#define SHADOWWIDTH  0.5

enum Direction {
	UP = 0,
	DOWN = 1,
	LEFT,
	RIGHT,
	LEFTTOP,
	LEFTBOTTOM,
	RIGHTBOTTOM,
	RIGHTTOP,
	NONE
};

#define WINOWS_WIDTH 1366
#define WINOWS_HEIGHT 768

class MenuItemWidget : public QWidget
{
	Q_OBJECT

public:
	MenuItemWidget(const QPixmap& icon, const QString& text, QWidget *parent = 0)
	{
		QLabel* label_Icon = new QLabel(this);
		label_Icon->setFixedSize(32, 32);
		label_Icon->setScaledContents(true);
		label_Icon->setPixmap(icon);

		QLabel* label_Text = new QLabel(text, this);

		QHBoxLayout* layout = new QHBoxLayout;
		layout->setContentsMargins(20, 6, 50, 6);
		layout->setSpacing(10);
		layout->addWidget(label_Icon);
		layout->addWidget(label_Text);
		setLayout(layout);

		setFixedWidth(240);
	}
	~MenuItemWidget()
	{}

protected:
	void paintEvent(QPaintEvent* e) {
		QStyleOption opt;
		opt.init(this);
		QPainter p(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	}

private:
};

class QtExplorer : public QWidget
{
	Q_OBJECT

public:
	QtExplorer(QWidget *parent = Q_NULLPTR);
	//���Ʒ�����Ŀǰ�˷���ֻ��Ϊ�߿������ӰЧ��
	void paintEvent(QPaintEvent *event);
	//�ƶ��ľ���
	QPoint move_point;
	//��갴��
	bool mouse_press;
	//��갴���¼�
	void mousePressEvent(QMouseEvent *event);
	//����ͷ��¼�
	void mouseReleaseEvent(QMouseEvent *event);
	//����ƶ��¼�
	void mouseMoveEvent(QMouseEvent *event);
	//windows������Ϣ����Ŀǰ������WM_NCHITTEST��Ϣ��ʵ���ޱ߿������ק��С����
	//bool winEvent(MSG * message, long * result);
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);
	//����ͼ�����Dockwindow
	void createDockWindows();
	//�����ļ��˵�Ŀ¼
	void createFileMainMenu();
	//���˫����������󻯳���
	void mouseDoubleClickEvent(QMouseEvent * event);
	//�ڴ������ϽǴ��������С�����رմ��ڵȻ�����ť
	void createBaseMenu();
	void ConnectSlots();
	
	//����QAction
	void createActions();

public slots:
	bool closeWidget();
	//ȫ����������ʾ�����ڲۺ���
	void ShowFullOrNomalWindow();
	void AddImageSlot();
	void AddTerrainSlot();
	void AddPlaceNameSlot();
	void AddObliqueImage();

private:
	Ui::QtExplorerClass ui;

	//������С����ť
	QToolButton *minButton;
	//���ڹرհ�ť
	QToolButton *closeButton;
	//������󻯰�ť
	QToolButton *maxButton;
	//����������С����
	QToolButton *norButton;
	//��Ӱ�Ŀ��
	int m_shadowSize;
	//������һ�����������֮ǰ֮ǰ���ڵĳߴ�
	QRect m_rect;
	bool m_bIsMaxSize;

	//osg����������
	QSplitter *m_mainSplitter;
	//ͼ�����ͣ����������
	QSplitter *m_layermanaSplitter;
	//osg����������
	QSplitter *m_osgWidgetSplitter;

	//ͼ�����ͣ�����ڶ���
	QDockWidget *m_layerDockWidget;

	QDockWidget* tempLayerDockWidget;
	QTreeWidgetItem* tempTopImageItem;
	QTreeWidgetItem* tempTopTerrainItem;
	QTreeWidgetItem* tempTopVectorItem;
	QTreeWidgetItem* tempTopPlaceNameItem;
	QTreeWidgetItem* tempTopModelItem;
	QTreeWidgetItem* tempTopPipeModelItem;

	//����ͣ�����ڶ���
	QDockWidget *m_snapShootDockWidget;
	//ͼ�����ͣ�����ڶ���
	QDockWidget *m_layerDockWidget2;
	//ͼ�����ͼƬ����
	QListWidget* m_ptrSnapListWidget;

	//ͼ�����ͣ���������Ϳؼ����ڵ㼯
	QList<QTreeWidgetItem*> *m_listTopQTreeTtem;
	//ͼ�����ͣ������2���Ϳؼ����ڵ㼯
	QList<QTreeWidgetItem*> *m_listTopQTreeTtem2;
	//���οؼ�����
	QTreeWidget *m_topTreeView;
	//���οؼ�����2
	QTreeWidget *m_topTreeView2;
	//Ӱ��ͼ�㸸�ڵ�
	QTreeWidgetItem *m_topImageItem;
	//Ӱ��ͼ�㸸�ڵ�2
	QTreeWidgetItem *m_topImageItem2;
	//����ͼ�㸸�ڵ�
	QTreeWidgetItem *m_topTerrainItem;
	//����ͼ�㸸�ڵ�2
	QTreeWidgetItem *m_topTerrainItem2;
	//ʸ��ͼ�㸸�ڵ�
	QTreeWidgetItem *m_topVectorItem;
	//ʸ��ͼ�㸸�ڵ�2
	QTreeWidgetItem *m_topVectorItem2;
	//��ά����ͼ�㸸�ڵ�
	QTreeWidgetItem *m_topPlaceNameItem;
	//��ά����ͼ�㸸�ڵ�2
	QTreeWidgetItem *m_topPlaceNameItem2;
	//ģ��ͼ�㸸�ڵ�
	QTreeWidgetItem *m_topModelItem;
	//ģ��ͼ�㸸�ڵ�2
	QTreeWidgetItem *m_topModelItem2;
	//����ͼ�㸸�ڵ�
	QTreeWidgetItem *m_topPipeModelItem;
	//����ͼ�㸸�ڵ�2
	QTreeWidgetItem *m_topPipeModelItem2;
	//��ǰ��ѡ��ͼ��ڵ�
	QTreeWidgetItem *m_currentSelectedItem;
	//��ǰ��ѡ��ͼ��ڵ�2
	QTreeWidgetItem *m_currentSelectedItem2;
	QListWidgetItem *m_currentSelectedListWidgetItem;

	//���ر����ļ�Ŀ¼����
	QMenu *loadLocalDataMenu;
	//���ر����ļ�Ŀ¼����
	QMenu *loadLocalDataMenu2;
	//���ط�������Ŀ¼
	QMenu *loadServiceDataMenu;

	//���ص���Act
	QAction *addTerrainAct;
	//����Ӱ��Act
	QAction *addImageAct;
	//����ģ��Act
	QAction *addModelAct;
	//���ع���Act
	QAction *AddPipeModelAct;
	//������б��ӰAct
	QAction *addObliqueModelAct;
	//������ά����Act
	QAction *addPlaceNameAct;
	//������ά����Act2
	QAction *addPlaceName2Act;
	//����ʸ��Act
	QAction *addVectorAct;
	//����ʸ��Act2
	QAction *addVector2Act;
	//����Ӱ��Act2��Ҳ���ǵڶ�����
	QAction *addImage2Act;
	//���ص���Act2
	QAction *addTerrain2Act;
	//����ģ��Act2
	QAction *addModel2Act;
	//������б��ӰAct2
	QAction *addObliqueModel2Act;
	//���ع���Act2
	QAction *AddPipeModel2Act;

	QAction *addGeoTileServiceAct;
	QAction *addOGCServiceAct;


	GLOBE_NAME::GsGeospace3DQtPtr m_ptrOsgViewerWidget;

};
