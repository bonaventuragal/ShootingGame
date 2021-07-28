#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>

class Enemy : public QObject, public QGraphicsItem {

	Q_OBJECT

public:
	enum {Type = UserType + 3};

	Enemy();
	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	int type() const override;
	void setTarget(QPointF target);
	void startTimer();

private:
	QPolygonF polygon;
	QPointF target;
	QTimer *timer;
	qreal angle;
	qreal const PI = 3.14159265358979323846;

	qreal findAngle();
	bool detectCollision();

private slots:
	void forward();
	void updateTargetPos(QPointF pos);

};

#endif // ENEMY_H
