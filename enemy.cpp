#include "enemy.h"

Enemy::Enemy() {
	polygon << QPointF(10., 0) << QPointF(0., 20.) << QPointF(20., 20.);

	timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(forward()));
	//	timer->start(100);
}

Enemy::~Enemy() {
	delete timer;
}

QRectF Enemy::boundingRect() const {
	return QRectF(0, 0, 20, 20);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setBrush(QBrush(Qt::red));

	if(!detectCollision()) {
		painter->drawPolygon(polygon);
	} else {
		// delete if colliding
		deleteLater();
	}

	Q_UNUSED(option)
	Q_UNUSED(widget)
}

int Enemy::type() const {
	return Enemy::Type;
}

void Enemy::setTarget(QPointF target) {
	this->target = target;
	angle = findAngle();
}

void Enemy::startTimer() {
	timer->start(100);
}

void Enemy::stopTimer() {
	timer->stop();
}

qreal Enemy::findAngle() {
	return std::atan2(target.y() - y(), target.x() - x()) * 180 / PI;
}

bool Enemy::detectCollision() {
	bool ret = false;
	QList<QGraphicsItem*> collidingList = scene()->collidingItems(this);
	for(int i = 0; i < collidingList.size(); i++) {
		// colliding with other enemy or other border does not count
		if(collidingList[i]->type() != Enemy::Type && collidingList[i]->type() != BorderLine::Type) ret = true;
	}
	return ret;
}

void Enemy::forward() {
	// prevent rotated graphic output
	setRotation(angle);
	setPos(mapToParent(4, 0));
	setRotation(0);
}

void Enemy::updateTargetPos(QPointF pos) {
	setTarget(pos);
}
