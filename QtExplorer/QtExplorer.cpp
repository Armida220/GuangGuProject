#include "QtExplorer.h"
#include <qpainter.h>
#include <qmath.h>
#include <QMouseEvent>
#include <QWidgetAction>
#include <QMenu>
#include <QPropertyAnimation>
#include <QDesktopWidget>
#include <QSplitter>
#include <QDockWidget>
#include <QTreeWidget>
#include <QListWidget>
#include <QDir>
#include <QTimer>
#include <QScrollBar>
#include <QFileDialog>

#include <geodatabase.h>
#include <OsgInterface.h>
#include "ObliqueImageLayer.h"

#ifdef _WIN32
#include <windows.h>
#include <WindowsX.h>
#endif // _WIN32

QtExplorer::QtExplorer(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.menuFilePushButton->setParent(ui.mainTabWidget);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	this->setMouseTracking(true);

	m_shadowSize = 10;
	mouse_press = false;
	m_bIsMaxSize = false;

	m_rect.setRect(230, 150, 1440, 760);

	//����ͼ�����ͣ������
	createDockWindows();
	ConnectSlots();

	m_mainSplitter = new QSplitter(Qt::Horizontal);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(m_mainSplitter->sizePolicy().hasHeightForWidth());
	m_mainSplitter->setSizePolicy(sizePolicy);
	m_mainSplitter->setHandleWidth(1);

	m_layermanaSplitter = new QSplitter(Qt::Vertical, m_mainSplitter);
	m_layermanaSplitter->addWidget(m_layerDockWidget);
	//m_layermanaSplitter->addWidget(m_vectorEditDockWidget);
	m_layermanaSplitter->setHandleWidth(1);

	m_osgWidgetSplitter = new QSplitter(Qt::Vertical, m_mainSplitter);

	m_ptrOsgViewerWidget = new GLOBE_NAME::GsGeospace3DQt();

	m_osgWidgetSplitter->addWidget(m_ptrOsgViewerWidget);
	m_osgWidgetSplitter->setHandleWidth(1);

	QList<int> listMain;
	listMain << 170;//���ý��մ��ڵ�����ֵ
	listMain << 1000;  //���õڶ������ڵ�����ֵ
	m_mainSplitter->setSizes(listMain);

	QList<int> listOsg;
	listOsg << 800;//���ý��մ��ڵ�����ֵ
	listOsg << 200;  //���õڶ������ڵ�����ֵ
	m_osgWidgetSplitter->setSizes(listOsg);


	ui.gridLayout->addWidget(m_mainSplitter, 2, 0, 1, 1);
	//ui.gridLayout->addWidget(ui.stateBarWidget, 3, 0, 1, 1);

	createActions();
	createFileMainMenu();
	//������С������󻯺͹رջ�����ť
	createBaseMenu();

	//��󻯴���
	QDesktopWidget * desktopWidget = QApplication::desktop();
	QRect rect = desktopWidget->availableGeometry();
	QPixmap maxPix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
	maxButton->setIcon(maxPix);
	maxButton->setToolTip(QString::fromLocal8Bit("��ԭ"));
	this->setGeometry(0, 0, rect.width(), rect.height());
}

void QtExplorer::AddImageSlot()
{
	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("�򿪱���Ӱ�����ݼ�"), ".", tr("Local Dataset(*.tile)"));

	if (!fileName.isEmpty())
	{
		//KERNEL_NAME::GsSqliteGeoDatabaseFactory fac;
		//KERNEL_NAME::GsConnectProperty conn ;
		//conn.Server = QFileInfo(fileName).absoluteDir().absolutePath().toStdString() ;
		//KERNEL_NAME::GsGeoDatabasePtr gdb = fac.Open(conn);
		//KERNEL_NAME::GsTileClassPtr tileclass = gdb->OpenTileClass("DOM1.tile");

		//GLOBE_NAME::Layer* ptrLayer = new GLOBE_NAME::ImageLayer(tileclass.p);

		GLOBE_NAME::LayerPtr ptrLayer = new GLOBE_NAME::ImageLayer(fileName.toLocal8Bit().data(),GLOBE_NAME::eLocal);
		//GLOBE_NAME::Layer* ptrLayer = new GLOBE_NAME::ImageLayer("http://192.168.43.49:9010/XL_IMAGE/services/tile", GLOBE_NAME::eGeoGlobeTile);
		if (ptrLayer)
		{
			m_ptrOsgViewerWidget->LayerBox()->AddLayer(ptrLayer);
			m_ptrOsgViewerWidget->SceneBox()->RangeFlyTo(ptrLayer->xMin(), ptrLayer->xMax(), ptrLayer->yMin(), ptrLayer->yMax());
		}
	}
}

void QtExplorer::AddTerrainSlot()
{
	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("�򿪱��ص������ݼ�"), ".", tr("Local Dataset(*.tile)"));

	if (!fileName.isEmpty())
	{

		GLOBE_NAME::LayerPtr ptrLayer = new GLOBE_NAME::TerrainLayer(fileName.toLocal8Bit().data(), GLOBE_NAME::eLocal);
		//GLOBE_NAME::Layer* ptrLayer = new GLOBE_NAME::TerrainLayer("http://192.168.43.49:9010/WorldNewDEM/services/tile", GLOBE_NAME::eGeoGlobeTile);
		if (ptrLayer)
		{
			m_ptrOsgViewerWidget->LayerBox()->AddLayer(ptrLayer);
			m_ptrOsgViewerWidget->SceneBox()->RangeFlyTo(ptrLayer->xMin(), ptrLayer->xMax(), ptrLayer->yMin(), ptrLayer->yMax());
		}
	}
}

void QtExplorer::AddPlaceNameSlot()
{
	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("����ά�������ݼ�"), ".", tr("Local Dataset(*.tfg)"));

	if (!fileName.isEmpty())
	{

		GLOBE_NAME::LayerPtr ptrLayer = new GLOBE_NAME::PlaceNameLayer(fileName.toLocal8Bit().data(), GLOBE_NAME::eLocal);
		//GLOBE_NAME::LayerPtr ptrLayer = new GLOBE_NAME::PlaceNameLayer("http://192.168.43.49:9010/ChinaXCH/wtfs", GLOBE_NAME::eGeoGlobeTile);
		
		if (ptrLayer)
		{
			m_ptrOsgViewerWidget->LayerBox()->AddLayer(ptrLayer);
			m_ptrOsgViewerWidget->SceneBox()->RangeFlyTo(ptrLayer->xMin(), ptrLayer->xMax(), ptrLayer->yMin(), ptrLayer->yMax());
		}
	}
}

void QtExplorer::AddObliqueImage()
{
	QString qstrFileName = QFileDialog::getExistingDirectory(this);

	GLOBE_NAME::LayerPtr ptrLayer = new GLOBE_NAME::ObliqueImageLayer(qstrFileName.toLocal8Bit().data(), GLOBE_NAME::eLocal);

	//GLOBE_NAME::LayerPtr ptrLayer = new GLOBE_NAME::ObliqueImageLayer("http://192.168.51.77/data/jj3dmodeldata/data/", GLOBE_NAME::eServer);

	m_ptrOsgViewerWidget->LayerBox()->AddLayer(ptrLayer);

	m_ptrOsgViewerWidget->SceneBox()->PointFlyTo(ptrLayer->Longitude(), ptrLayer->Latitude(), ptrLayer->Height() + 30);
}

void QtExplorer::createActions()
{
	loadServiceDataMenu = new QMenu(QString::fromLocal8Bit("���ط���"), this);

	addGeoTileServiceAct = new QAction(QString::fromLocal8Bit("������Ƭ����"), this);
	addGeoTileServiceAct->setIcon(QIcon(":/QMainWindow/Resources/icon/tile.png"));
	addGeoTileServiceAct->setStatusTip(QString::fromLocal8Bit("������Ƭ����"));
	connect(addGeoTileServiceAct, SIGNAL(triggered()), this, SLOT(addGeoServiceSlot()));
	loadServiceDataMenu->addAction(addGeoTileServiceAct);

	addOGCServiceAct = new QAction(QString::fromLocal8Bit("OGC����"), this);
	addOGCServiceAct->setIcon(QIcon(":/QMainWindow/Resources/icon/load_Service.png"));
	addOGCServiceAct->setStatusTip(QString::fromLocal8Bit("OGC����"));
	connect(addOGCServiceAct, SIGNAL(triggered()), this, SLOT(addOGCServiceSlot()));
	loadServiceDataMenu->addAction(addOGCServiceAct);

	loadLocalDataMenu = new QMenu(QString::fromLocal8Bit("����"), this);
	loadLocalDataMenu->setIcon(QIcon(":/QMainWindow/Resources/icon/localData.png"));
	loadLocalDataMenu->menuAction()->setStatusTip(QString::fromLocal8Bit("���ر�������"));

	addTerrainAct = new QAction(QString::fromLocal8Bit("����"), this);
	addTerrainAct->setIcon(QIcon(":/QMainWindow/Resources/icon/terraine.png"));
	addTerrainAct->setStatusTip(QString::fromLocal8Bit("����"));
	connect(addTerrainAct, &QAction::triggered, this, &QtExplorer::AddTerrainSlot);
	loadLocalDataMenu->addAction(addTerrainAct);

	addImageAct = new QAction(QString::fromLocal8Bit("Ӱ��"), this);
	addImageAct->setIcon(QIcon(":/QMainWindow/Resources/icon/Image.png"));
	addImageAct->setStatusTip(QString::fromLocal8Bit("Ӱ��"));
	connect(addImageAct, &QAction::triggered, this, &QtExplorer::AddImageSlot);
	loadLocalDataMenu->addAction(addImageAct);

	addModelAct = new QAction(QString::fromLocal8Bit("ģ��"), this);
	addModelAct->setIcon(QIcon(":/QMainWindow/Resources/icon/Model.png"));
	addModelAct->setStatusTip(QString::fromLocal8Bit("ģ��"));
	connect(addModelAct, SIGNAL(triggered()), this, SLOT(AddObliqueImage()));
	loadLocalDataMenu->addAction(addModelAct);

	AddPipeModelAct = new QAction(QString::fromLocal8Bit("����"), this);
	AddPipeModelAct->setIcon(QIcon(":/QMainWindow/Resources/icon/pipe.png"));
	AddPipeModelAct->setStatusTip(QString::fromLocal8Bit("����"));
	connect(AddPipeModelAct, SIGNAL(triggered()), this, SLOT(AddPipeModelSLot()));
	loadLocalDataMenu->addAction(AddPipeModelAct);

	addObliqueModelAct = new QAction(QString::fromLocal8Bit("��б"), this);
	addObliqueModelAct->setIcon(QIcon(":/QMainWindow/Resources/icon/obliq.png"));
	addObliqueModelAct->setStatusTip(QString::fromLocal8Bit("��б"));
	connect(addObliqueModelAct, SIGNAL(triggered()), this, SLOT(AddObliqueImage()));
	loadLocalDataMenu->addAction(addObliqueModelAct);

	addPlaceNameAct = new QAction(QString::fromLocal8Bit("����"), this);
	addPlaceNameAct->setIcon(QIcon(":/QMainWindow/Resources/icon/placename.png"));
	addPlaceNameAct->setStatusTip(QString::fromLocal8Bit("����"));
	connect(addPlaceNameAct, SIGNAL(triggered()), this, SLOT(AddPlaceNameSlot()));
	loadLocalDataMenu->addAction(addPlaceNameAct);

	addVectorAct = new QAction(QString::fromLocal8Bit("ʸ��"), this);
	addVectorAct->setIcon(QIcon(":/QMainWindow/Resources/icon/vector.png"));
	addVectorAct->setStatusTip(QString::fromLocal8Bit("ʸ��"));
	connect(addVectorAct, SIGNAL(triggered()), this, SLOT(AddVectorSLot()));
	loadLocalDataMenu->addAction(addVectorAct);

	this->ui.loadLocalDataToolButton->setPopupMode(QToolButton::InstantPopup);
	this->ui.loadLocalDataToolButton->setMenu(loadLocalDataMenu);
	this->ui.loadServerToolButton->setMenu(loadServiceDataMenu);
	this->ui.loadServerToolButton->setPopupMode(QToolButton::InstantPopup);
}

//����ͼ�����ͣ������
void QtExplorer::createDockWindows()
{
	m_layerDockWidget = new QDockWidget(QString::fromLocal8Bit("ͼ�����"));
	m_layerDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	m_layerDockWidget2 = new QDockWidget(QString::fromLocal8Bit("ͼ�����2"));
	m_layerDockWidget2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	m_layerDockWidget2->hide();

	m_snapShootDockWidget = new QDockWidget(QString::fromLocal8Bit("���չ���"));
	m_ptrSnapListWidget = new QListWidget(m_snapShootDockWidget);
	m_ptrSnapListWidget->setIconSize(QSize(300, 128));
	m_ptrSnapListWidget->setResizeMode(QListView::Adjust);
	//����QListWidget����ʾģʽ
	m_ptrSnapListWidget->setViewMode(QListView::IconMode);
	//����QListWidget�еĵ�Ԫ��ɱ��϶�
	m_ptrSnapListWidget->setMovement(QListView::Static);
	m_ptrSnapListWidget->setFlow(QListView::TopToBottom);
	m_ptrSnapListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	m_ptrSnapListWidget->setMaximumHeight(100);
	m_ptrSnapListWidget->setMinimumHeight(50);

	m_snapShootDockWidget->setWidget(m_ptrSnapListWidget);

	m_listTopQTreeTtem = new QList<QTreeWidgetItem*>();
	m_listTopQTreeTtem2 = new QList<QTreeWidgetItem*>();

	m_topTreeView = new QTreeWidget(m_layerDockWidget);
	m_topTreeView->setHeaderHidden(true);
	m_topTreeView->setContextMenuPolicy(Qt::CustomContextMenu);

	m_topTreeView2 = new QTreeWidget(m_layerDockWidget2);
	m_topTreeView2->setHeaderHidden(true);
	m_topTreeView2->setContextMenuPolicy(Qt::CustomContextMenu);

	m_topImageItem = new QTreeWidgetItem();
	m_topImageItem->setText(0, QString::fromLocal8Bit("Ӱ��"));
	m_topImageItem->setCheckState(0, Qt::Checked);
	m_listTopQTreeTtem->push_back(m_topImageItem);

	m_topImageItem2 = new QTreeWidgetItem();
	m_topImageItem2->setText(0, QString::fromLocal8Bit("Ӱ��"));
	m_topImageItem2->setCheckState(0, Qt::Checked);
	m_listTopQTreeTtem2->push_back(m_topImageItem2);

	m_topTerrainItem = new QTreeWidgetItem();
	m_topTerrainItem->setText(0, QString::fromLocal8Bit("����"));
	m_topTerrainItem->setCheckState(0, Qt::Checked);
	m_listTopQTreeTtem->push_back(m_topTerrainItem);

	m_topTerrainItem2 = new QTreeWidgetItem();
	m_topTerrainItem2->setText(0, QString::fromLocal8Bit("����"));
	m_topTerrainItem2->setCheckState(0, Qt::Checked);
	m_listTopQTreeTtem2->push_back(m_topTerrainItem2);

	m_topVectorItem = new QTreeWidgetItem();
	m_topVectorItem->setText(0, QString::fromLocal8Bit("ʸ��"));
	m_topVectorItem->setCheckState(0, Qt::Checked);
	m_listTopQTreeTtem->push_back(m_topVectorItem);

	m_topVectorItem2 = new QTreeWidgetItem();
	m_topVectorItem2->setText(0, QString::fromLocal8Bit("ʸ��"));
	m_topVectorItem2->setCheckState(0, Qt::Checked);
	m_listTopQTreeTtem2->push_back(m_topVectorItem2);

	m_topPlaceNameItem = new QTreeWidgetItem();
	m_topPlaceNameItem->setText(0, QString::fromLocal8Bit("����"));
	m_topPlaceNameItem->setCheckState(0, Qt::Checked);
	m_listTopQTreeTtem->push_back(m_topPlaceNameItem);

	m_topPlaceNameItem2 = new QTreeWidgetItem();
	m_topPlaceNameItem2->setText(0, QString::fromLocal8Bit("����"));
	m_topPlaceNameItem2->setCheckState(0, Qt::Checked);
	m_listTopQTreeTtem2->push_back(m_topPlaceNameItem2);

	m_topModelItem = new QTreeWidgetItem();
	m_topModelItem->setText(0, QString::fromLocal8Bit("ģ��"));
	m_topModelItem->setCheckState(0, Qt::Checked);
	m_listTopQTreeTtem->push_back(m_topModelItem);

	m_topModelItem2 = new QTreeWidgetItem();
	m_topModelItem2->setText(0, QString::fromLocal8Bit("ģ��"));
	m_topModelItem2->setCheckState(0, Qt::Checked);
	m_listTopQTreeTtem2->push_back(m_topModelItem2);

	m_topPipeModelItem = new QTreeWidgetItem();
	m_topPipeModelItem->setText(0, QString::fromLocal8Bit("����"));
	m_topPipeModelItem->setCheckState(0, Qt::Checked);
	m_listTopQTreeTtem->push_back(m_topPipeModelItem);

	m_topPipeModelItem2 = new QTreeWidgetItem();
	m_topPipeModelItem2->setText(0, QString::fromLocal8Bit("����"));
	m_topPipeModelItem2->setCheckState(0, Qt::Checked);
	m_listTopQTreeTtem2->push_back(m_topPipeModelItem2);

	m_topTreeView->addTopLevelItems(*m_listTopQTreeTtem);
	m_topTreeView2->addTopLevelItems(*m_listTopQTreeTtem2);

	//��TreeView�ı߿���Ϊ�� ��ֹ�����ĸ�������ǲ����ڱ�
	m_topTreeView->setStyleSheet(QString::fromUtf8("border: 1px;"));
	m_topTreeView2->setStyleSheet(QString::fromUtf8("border: 1px;"));
	m_ptrSnapListWidget->setStyleSheet(QString::fromUtf8("border: 1px;"));

	//m_ptrSnapListWidget->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal{background:rgba(0,0,0,0.5);}");
	//m_ptrSnapListWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{background:rgba(0,0,0,0.5);}");
	m_topTreeView->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal{background:rgba(0,0,0,0);}");
	m_topTreeView->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{background:rgba(0,0,0,0);}");
	//m_topTreeView2->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal{background:rgba(0,0,0,0.5);}");
	//m_topTreeView2->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{background:rgba(0,0,0,0.5);}");

	m_layerDockWidget->setWidget(m_topTreeView);
	m_layerDockWidget->setMaximumWidth(500);
	//m_layerDockWidget2->setWidget(m_topTreeView2);
	//m_layerDockWidget2->setMaximumWidth(500);

	QString qstrStyle = QString::fromUtf8("\n"
		"QDockWidget::title {\n"
		"text-align: left;/* align the text to the left */\n"
		"background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
		"                                stop: 0 #FFFFFF, stop: 0.5 #DCE6F4,\n"
		"                                stop: 0.95 #DCE6F4, stop: 1.0 #E5F0FB);\n"
		"padding-left:5px;\n"
		"}\n"
		"\n"
		"QDockWidget::close-button,QDockWidget::float-button {\n"
		"border:1px solid transparent;\n"
		"background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
		"                                stop: 0 #FFFFFF, stop: 0.5 #DCE6F4,\n"
		"                                stop: 0.95 #DCE6F4, stop: 1.0 #E5F0FB);\n"
		"padding:0px;\n"
		"}\n"
		"\n"
		"QDockWidget::close-button:hover,QDockWidget::float-button:hover {\n"
		"background: rgba(220, 224, 231,150);\n"
		"}\n"
		"\n"
		"QDockWidget::close-button:pressed,QDockWidget::float-button:pressed {\n"
		"padding:1px-1px-1px1px;\n"
		"}	\n"
		"\n"
		"border: 1px solid #BAC9DB;\n"
		"background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
		"                                stop: 0 #FFFFFF, stop: 0.5 #DCE6"
		"F4,\n"
		"                                stop: 0.95 #DCE6F4, stop: 1.0 #E5F0FB);\n"
		"top: -1px;");

	m_layerDockWidget->setStyleSheet(qstrStyle);
	m_layerDockWidget2->setStyleSheet(qstrStyle);
	m_snapShootDockWidget->setStyleSheet(qstrStyle);
	m_snapShootDockWidget->hide();
	//addDockWidget(Qt::LeftDockWidgetArea, m_layerDockWidget);

	//connect(m_layerDockWidget, SIGNAL(topLevelChanged(bool)), this, SLOT(dockWidgetToplevelChange(bool)));
	connect(m_layerDockWidget, SIGNAL(visibilityChanged(bool)), this, SLOT(dockWidgetVisibilityChanged(bool)));

	connect(m_topTreeView, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(showMouseRightButtonSlot(const QPoint)));
	connect(m_topTreeView, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(doubleClickLocate(QTreeWidgetItem*, int)));
	connect(m_topTreeView, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(treeItemChanged(QTreeWidgetItem*, int)));

	connect(m_topTreeView2, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(showMouseRightButtonSlot2(const QPoint)));
	connect(m_topTreeView2, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(doubleClickLocate(QTreeWidgetItem*, int)));
	connect(m_topTreeView2, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(treeItemChanged(QTreeWidgetItem*, int)));

	connect(m_ptrSnapListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(SnapShootDoubleClickSlot(QListWidgetItem *)));
	connect(m_ptrSnapListWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(SnapShootMouseRightButtonSlot(const QPoint &)));
}

void QtExplorer::ConnectSlots()
{

}

//�ڴ������ϽǴ��������С�����رմ��ڵȻ�����ť
void QtExplorer::createBaseMenu()
{
	//������С������󻯡��رհ�ť
	minButton = new QToolButton(this);
	closeButton = new QToolButton(this);
	maxButton = new QToolButton(this);

	connect(minButton, SIGNAL(clicked()), this, SLOT(showMinimized()));
	//connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
	connect(closeButton, SIGNAL(clicked()), this, SLOT(closeWidget()));
	connect(maxButton, SIGNAL(clicked()), this, SLOT(ShowFullOrNomalWindow()));

	//��ȡ��С�����رհ�ťͼ��
	QPixmap minPix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
	QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
	QPixmap maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);

	//������С�����رհ�ťͼ��
	minButton->setIcon(minPix);
	minButton->setIconSize(QSize(32, 32));
	closeButton->setIcon(closePix);
	maxButton->setIcon(maxPix);

	//�������������ť�ϵ���ʾ��Ϣ
	minButton->setToolTip(QString::fromLocal8Bit("��С��"));
	maxButton->setToolTip(QString::fromLocal8Bit("���"));
	closeButton->setToolTip(QString::fromLocal8Bit("�ر�"));
	//������С�����رհ�ť����ʽ

	minButton->setStyleSheet("QToolButton{background-color:transparent;}"
		"QToolButton:hover{background-color:rgba(220, 224, 231,150);border:0px;}");

	closeButton->setStyleSheet("QToolButton{background-color:transparent;}"
		"QToolButton::hover{background-color:rgba(255, 0, 0,150);border:0px;}");

	maxButton->setStyleSheet("QToolButton{background-color:transparent;}"
		"QToolButton:hover{background-color:rgba(220, 224, 231,150);border:0px;}");
}

//�����ļ��˵�Ŀ¼
void QtExplorer::createFileMainMenu()
{
	QMenu* menu = new QMenu(this);
	ui.menuFilePushButton->setMenu(menu);

	QWidgetAction* actionNew = new QWidgetAction(this);
	actionNew->setDefaultWidget(new MenuItemWidget(QPixmap(":/QMainWindow/Resources/icon/file_new.png"), QString::fromLocal8Bit("�½�"), this));
	menu->addAction(actionNew);

	QWidgetAction* actionOpen = new QWidgetAction(this);
	actionOpen->setDefaultWidget(new MenuItemWidget(QPixmap(":/QMainWindow/Resources/icon/file_open.png"), QString::fromLocal8Bit("��"), this));
	menu->addAction(actionOpen);
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(OpenWorkSpace()));

	QWidgetAction* actionSave = new QWidgetAction(this);
	actionSave->setDefaultWidget(new MenuItemWidget(QPixmap(":/QMainWindow/Resources/icon/file_save.png"), QString::fromLocal8Bit("����"), this));
	menu->addAction(actionSave);
	connect(actionSave, SIGNAL(triggered()), this, SLOT(SaveWorkSpace()));

	QWidgetAction* actionSaveAs = new QWidgetAction(this);
	actionSaveAs->setDefaultWidget(new MenuItemWidget(QPixmap(":/QMainWindow/Resources/icon/file_saveas.png"), QString::fromLocal8Bit("���Ϊ"), this));
	menu->addAction(actionSaveAs);
	//connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(saveAsWorkSpace())); 

	QWidgetAction* actioPrint = new QWidgetAction(this);
	actioPrint->setDefaultWidget(new MenuItemWidget(QPixmap(":/QMainWindow/Resources/icon/file_print.png"), QString::fromLocal8Bit("��ӡ"), this));
	menu->addAction(actioPrint);

	QWidgetAction* actionAout = new QWidgetAction(this);
	actionAout->setDefaultWidget(new MenuItemWidget(QPixmap(":/QMainWindow/Resources/icon/about.png"), QString::fromLocal8Bit("����"), this));
	menu->addAction(actionAout);

	QWidgetAction* actionExit = new QWidgetAction(this);
	actionExit->setDefaultWidget(new MenuItemWidget(QPixmap(":/QMainWindow/Resources/icon/exit.png"), QString::fromLocal8Bit("�˳�"), this));
	menu->addAction(actionExit);
	connect(actionExit, SIGNAL(triggered()), this, SLOT(closeWidget()));
}

//���Ʒ�����Ŀǰ�˷���ֻ��Ϊ�߿������ӰЧ��
void QtExplorer::paintEvent(QPaintEvent *event)
{
	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRect(SHADOWWIDTH, SHADOWWIDTH, this->width() - 3, this->height() - 3);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillPath(path, QBrush(Qt::white));

	QColor color(21, 160, 245, 50);
	for (int i = 0; i < SHADOWWIDTH; i++)
	{
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRect(SHADOWWIDTH - i, SHADOWWIDTH - i, this->width() - (SHADOWWIDTH - i) * 2, this->height() - (SHADOWWIDTH - i) * 2);
		color.setAlpha(150 - qSqrt(i) * 50);
		painter.setPen(color);
		painter.drawPath(path);
	}

	minButton->setGeometry(this->width() - 99, 11, 32, 32);
	maxButton->setGeometry(this->width() - 67, 11, 32, 32);
	closeButton->setGeometry(this->width() - 35, 11, 32, 32);
}


//��갴���¼�
void QtExplorer::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		mouse_press = true;
		//�������ڴ����λ�ã�����ʹ��event->globalPos() - this->pos()��
		move_point = event->pos();;
	}
}

//����ƶ��¼�
void QtExplorer::mouseMoveEvent(QMouseEvent *event)
{
	int w = this->height();
	QPoint p = event->pos();

	//��������������
	if (mouse_press && move_point.y() >= 0 && move_point.y() <= (this->height() - 100))
	{
		//����������Ļ��λ��
		QPoint move_pos = event->globalPos();

		//�ƶ�������λ��
		this->move(move_pos - move_point);
	}
}

//���˫����������󻯳���
void QtExplorer::mouseDoubleClickEvent(QMouseEvent * event)
{
	if (event->pos().y() >= 0 && event->pos().y() <= 57)
	{
		ShowFullOrNomalWindow();
	}
	else if (event->pos().y() >= 55 && event->pos().y() <= 150)
	{
		//hideOrShowTabWidget();
	}
}

//����ͷ��¼�
void QtExplorer::mouseReleaseEvent(QMouseEvent *event)
{
	//�������Ϊδ������
	mouse_press = false;
}

//windows������Ϣ����Ŀǰ������WM_NCHITTEST��Ϣ��ʵ���ޱ߿������ק��С����
bool QtExplorer::nativeEvent(const QByteArray &eventType, void *message, long *result)
//bool QtExplorer::winEvent(MSG * message, long * result)
{
	MSG* msg = (MSG*)message;

	switch (msg->message)
	{
		case WM_NCHITTEST:
		{
			int nX = GET_X_LPARAM(msg->lParam) - this->geometry().x();
			int nY = GET_Y_LPARAM(msg->lParam) - this->geometry().y();

			QWidget* widget = this->childAt(nX, nY);

			//ָ������������
			if (widget/* && widget != this->centralWidget()*/)
			{
				return false;
			}
			else
			{
				*result = HTCAPTION;
			}

			if ((nX >= 0) && (nX < m_shadowSize))
				*result = HTLEFT;
			if ((nX > this->width() - m_shadowSize) && (nX < this->width()))
				*result = HTRIGHT;
			if ((nY >= 0) && (nY < m_shadowSize))
				*result = HTTOP;
			if ((nY > this->height() - m_shadowSize) && (nY < this->height()))
				*result = HTBOTTOM;
			if ((nX >= 0) && (nX < m_shadowSize) && (nY >= 0)
				&& (nY < m_shadowSize))
				*result = HTTOPLEFT;
			if ((nX > this->width() - m_shadowSize) && (nX < this->width())
				&& (nY >= 0) && (nY < m_shadowSize))
				*result = HTTOPRIGHT;
			if ((nX >= 0) && (nX < m_shadowSize)
				&& (nY > this->height() - m_shadowSize) && (nY < this->height()))
				*result = HTBOTTOMLEFT;
			if ((nX > this->width() - m_shadowSize - 2) && (nX < this->width())
				&& (nY > this->height() - m_shadowSize - 2) && (nY < this->height()))
				*result = HTBOTTOMRIGHT;

			//m_maximize = this->isMaximize();
			return true;
		}
	}

	return QWidget::nativeEvent(eventType, message, result);
}

//�رճ��򽥱��˳�����Ч���ۺ���
bool QtExplorer::closeWidget()
{
	//���涯�����ı�͸���ȵķ�ʽ��ʧ1 - 0����
	QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
	animation->setDuration(500);
	animation->setStartValue(1);
	animation->setEndValue(0);
	animation->start();
	connect(animation, SIGNAL(finished()), this, SLOT(close()));

	return true;
}

//ȫ����������ʾ�����ڲۺ���
void QtExplorer::ShowFullOrNomalWindow()
{
	QDesktopWidget * desktopWidget = QApplication::desktop();
	QRect rect = desktopWidget->availableGeometry();

	if (this->width() == rect.width() && this->height() == rect.height())
	{
		QPixmap maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
		maxButton->setIcon(maxPix);
		maxButton->setToolTip(QString::fromLocal8Bit("���"));

		this->setGeometry(m_rect);

		m_bIsMaxSize = false;
	}
	else
	{
		m_rect = QRect(this->geometry());
		QPixmap maxPix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
		maxButton->setIcon(maxPix);
		maxButton->setToolTip(QString::fromLocal8Bit("��ԭ"));
		this->setGeometry(0, 0, rect.width(), rect.height());

		m_bIsMaxSize = true;
	}
}