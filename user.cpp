#include "user.h"

User::User() {
	for(int i = 0; i < 4; i++) movement[i] = MovementCheck::NotSet;

	timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(changeMovement()));
	timer->start(100);
}

QRectF User::boundingRect() const {
	return QRectF(0, 0, 20, 20);
}

void User::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->drawEllipse(boundingRect());
}

void User::setMovement(MovementCheck movement[]) {
	for(int i = 0; i < 4; i++) {
		if(movement[i] == MovementCheck::NotSet) continue;
		this->movement[i] = movement[i];
	}
}

void User::changeMovement() {
	qreal x = this->x();
	qreal y = this->y();
	if(movement[0] == MovementCheck::Moving) y -= 5;
	if(movement[1] == MovementCheck::Moving) y += 5;
	if(movement[2] == MovementCheck::Moving) x -= 5;
	if(movement[3] == MovementCheck::Moving) x += 5;
	setPos(x, y);
}
