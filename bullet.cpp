#include "bullet.h"

Bullet::Bullet() {

}

QRectF Bullet::boundingRect() const {
	return QRectF(0, 0, 10, 4);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->drawRect(boundingRect());
}
