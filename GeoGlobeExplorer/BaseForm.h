#ifndef _BASE_FORM_
#define _BASE_FORM_

#include <QWidget>
#include <QToolButton>
#include <QPainter>
#include <QStyle>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <qmath.h>
#include <QDialog>

#define BASE_SHADOWWIDTH  10

class BaseForm :public QDialog
{
public:

	BaseForm(QWidget *parent = 0);
	virtual ~BaseForm();

	Q_OBJECT

public:
	//������С����ť
	QToolButton *minButton;
	//���ڹرհ�ť
	QToolButton *closeButton;

public slots:
	void okBtnClick();
	void cancelBtnClick();

signals:
	void signalMouseReleaseEvent(QMouseEvent *event);

public:

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

	void createBaseMenu();
};

#endif