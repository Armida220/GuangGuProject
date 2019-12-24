#include "BaseForm.h"


BaseForm::BaseForm(QWidget *parent)
{
	//���ô����Ի��ô��ڹر�ʱ���Լ�����
	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_TranslucentBackground);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	//this->setMouseTracking(true);

	mouse_press = false;
	createBaseMenu();

	//this->setWindowModality(Qt::WindowModal);
	this->setEnabled(true);
}


BaseForm::~BaseForm()
{

}

//�ڴ������ϽǴ��������С�����رմ��ڵȻ�����ť
void BaseForm::createBaseMenu()
{
	//������С������󻯡��رհ�ť
	//minButton = new QToolButton(this);
	closeButton= new QToolButton(this);
	//minButton->hide();
	closeButton->hide();

	//connect(minButton,SIGNAL(clicked()),this,SLOT(showMinimized()));
	//connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

	//��ȡ��С�����رհ�ťͼ��
	//QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
	QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);

	//������С�����رհ�ťͼ��
	//minButton->setIcon(minPix);
	//minButton->setIconSize(QSize(32,32));
	closeButton->setIcon(closePix);

	//������С�����رհ�ť�ڽ����λ��
	//minButton->setGeometry(this->width()-67,11,32,32);
	closeButton->setGeometry(this->width()-35,11,32,32);

	//�������������ť�ϵ���ʾ��Ϣ
	//minButton->setToolTip(QString::fromLocal8Bit("��С��"));
	closeButton->setToolTip(QString::fromLocal8Bit("�ر�"));
	//������С�����رհ�ť����ʽ

	//minButton->setStyleSheet("QToolButton{background-color:transparent;}"
	//	"QToolButton:hover{background-color:rgba(220, 224, 231,150);border:0px;}");

	closeButton->setStyleSheet("QToolButton{background-color:transparent;}"
		"QToolButton::hover{background-color:rgba(255, 0, 0,150);border:0px;}");
}

//��갴���¼�
void BaseForm::mousePressEvent(QMouseEvent *event)
{  
	if(event->button() == Qt::LeftButton)
	{
		mouse_press = true;
		//�������ڴ����λ�ã�����ʹ��event->globalPos() - this->pos()��
		move_point = event->pos();;
	}
}

//����ƶ��¼�
void BaseForm::mouseMoveEvent(QMouseEvent *event)
{
	//��������������
	if(mouse_press)
	{
		//����������Ļ��λ��
		QPoint move_pos = event->globalPos();

		//�ƶ�������λ��
		this->move(move_pos - move_point);

		QRect rect;
		rect = QApplication::desktop()->screenGeometry();

		int nWidth = this->width();
		int nheight = this->height();

		if(this->width()==rect.width() && this->height() ==rect.height())
		{
			QPixmap maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
			//maxButton->setIcon(maxPix);
			showNormal();
		}
	}
}

//����ͷ��¼�
void BaseForm::mouseReleaseEvent(QMouseEvent *event)
{
	//�������Ϊδ������
	mouse_press = false;

	emit signalMouseReleaseEvent(event);
}

//���Ʒ�����Ŀǰ�˷���ֻ��Ϊ�߿������ӰЧ��
void BaseForm::paintEvent(QPaintEvent *event)
{
	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRect(BASE_SHADOWWIDTH, BASE_SHADOWWIDTH, this->width()-20, this->height()-20);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillPath(path, QBrush(Qt::white));

	QColor color(0, 0, 0);
	for(int i=0; i<BASE_SHADOWWIDTH; i++)
	{
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRect(BASE_SHADOWWIDTH-i, BASE_SHADOWWIDTH-i, this->width()-(BASE_SHADOWWIDTH-i)*2, this->height()-(BASE_SHADOWWIDTH-i)*2);
		color.setAlpha(150 - qSqrt(i)*50);
		painter.setPen(color);
		painter.drawPath(path);
	}

	//minButton->setGeometry(this->width()-74,10,32,32);
	closeButton->setGeometry(this->width()-42,10,32,32);
} 

void BaseForm::okBtnClick()
{
	this->close();
}

void BaseForm::cancelBtnClick()
{
	this->close();
}