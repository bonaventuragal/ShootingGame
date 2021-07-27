#ifndef USER_H
#define USER_H

#include "MovementCheck.h"
#include "borderline.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>

class User : public QObject, public QGraphicsItem {

	Q_OBJECT

public:
	User();
	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	void setMovement(MovementCheck movement[4]);

	enum {Type = UserType};

private:
	QTimer *timer;
	MovementCheck movement[4];

	void detectCollision();

private slots:
	void changeMovement();
};

#endif // USER_H
