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
	detectCollision();

	painter->setBrush(QBrush(Qt::green));
	painter->drawEllipse(boundingRect());
}

void User::setMovement(MovementCheck movement[]) {
	for(int i = 0; i < 4; i++) {
		if(movement[i] == MovementCheck::NotSet) continue;
		this->movement[i] = movement[i];
	}
}

void User::detectCollision() {
	QList<QGraphicsItem*> collidingList = scene()->collidingItems(this);
	for(int i = 0; i < collidingList.size(); i++) {

		// colliding with border
		if(collidingList[i]->type() == QGraphicsLineItem::Type) {
			BorderLine *border = (BorderLine*) collidingList.at(0);
			BorderLine::BorderType type = border->borderType();

			// reposition user
			switch(type) {
			case BorderLine::Top:
				setPos(pos().x(), pos().y() + 2);
				break;
			case BorderLine::Bottom:
				setPos(pos().x(), pos().y() - 2);
				break;
			case BorderLine::Left:
				setPos(pos().x() + 2, pos().y());
				break;
			case BorderLine::Right:
				setPos(pos().x() - 2, pos().y());
				break;
			}
		}
	}
}

void User::changeMovement() {
	qreal x = this->x();
	qreal y = this->y();

	// change position
	if(movement[0] == MovementCheck::Moving) y -= 5;
	if(movement[1] == MovementCheck::Moving) y += 5;
	if(movement[2] == MovementCheck::Moving) x -= 5;
	if(movement[3] == MovementCheck::Moving) x += 5;
	setPos(x, y);
}
