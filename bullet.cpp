#include "bullet.h"

Bullet::Bullet() {
	timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(forward()));
}

QRectF Bullet::boundingRect() const {
	return QRectF(0, 0, 15, 3);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setBrush(QColor(0x00F7FF));
	if(!detectCollision()) painter->drawEllipse(boundingRect());
	// delete bullet if colliding
	else {
		delete timer;
		deleteLater();
	}

	Q_UNUSED(option)
	Q_UNUSED(widget)
}

int Bullet::type() const {
	return Bullet::Type;
}

bool Bullet::detectCollision() const {
	bool ret = false;
	QList<QGraphicsItem*> collidingList = scene()->collidingItems(this);
	for(int i = 0; i < collidingList.size(); i++) {
		// colliding with user or other bullet does not count
		if(collidingList[i]->type() != User::Type && collidingList[i]->type() != Bullet::Type) ret = true;
	}
	return ret;
}

void Bullet::setTarget(QPoint target) {
	this->target = target;
	angle = findAngle();
	setRotation(angle);
}

void Bullet::startTimer() {
	// bullet movement time
	timer->start(10);
}

qreal Bullet::findAngle() {
	return std::atan2(target.y() - y(), target.x() - x()) * 180 / PI;
}

void Bullet::forward() {
	setPos(mapToParent(4, 0));
}
