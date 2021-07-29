#ifndef USER_H
#define USER_H

#include "MovementCheck.h"
#include "borderline.h"
#include "enemy.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>

class User : public QObject, public QGraphicsItem {

	Q_OBJECT

public:
	enum {Type = UserType};

	User();
	~User();
	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	int type() const override;
	void setMovement(MovementCheck movement[4]);
	void startTimer();
	void stopTimer();

private:
	QTimer *timer;
	MovementCheck movement[4];

	void detectCollision();

private slots:
	void changeMovement();

signals:
	void updatePos(QPointF);
	void gameOver();

};

#endif // USER_H
