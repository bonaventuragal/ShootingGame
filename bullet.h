#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <QPainter>

class Bullet : public QObject, public QGraphicsItem {
	Q_OBJECT
public:
	Bullet();
	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

	enum {Type = UserType + 1};
};

#endif // BULLET_H
