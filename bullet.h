#ifndef BULLET_H
#define BULLET_H

#include "user.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>

class Bullet : public QObject, public QGraphicsItem {

	Q_OBJECT

public:
	enum {Type = UserType + 1};

	Bullet();
	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	int type() const override;
	void setTarget(QPoint target);
	void startTimer();

private:
	QTimer *timer;
	QPoint target;
	qreal angle;
	qreal const PI = 3.14159265358979323846;

	qreal findAngle();
	bool detectCollision() const;

private slots:
	void forward();

};

#endif // BULLET_H
