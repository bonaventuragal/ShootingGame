#ifndef USER_H
#define USER_H

#include "MovementCheck.h"
#include <QGraphicsItem>
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

private slots:
	void changeMovement();
};

#endif // USER_H
