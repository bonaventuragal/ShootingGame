#include "fieldview.h"

FieldView::FieldView(QWidget *parent) : QGraphicsView(parent), bulletSpawn(true) {
	// timer for bullet spawning timeout
	bulletTimer = new QTimer();
	connect(bulletTimer, SIGNAL(timeout()), this, SLOT(mouseClickTimeout()));
}

void FieldView::addUser() {
	user = new User();
	user->setPos(scene()->width() / 2 - 10, scene()->height() / 2 - 10);
	scene()->addItem(user);
}

void FieldView::spawn() {
	if(!bulletTimer->isActive()) {
		// start bullet timeout
		bulletSpawn = false;
		bulletTimer->start(150);

		// create new bullet
		Bullet *bullet = new Bullet();
		bullet->setPos(user->pos().x() + user->boundingRect().width() / 2, user->pos().y() + user->boundingRect().height() / 2 - bullet->boundingRect().height() / 2);
		bullet->setZValue(-1);
		bullet->setTarget(mouseClickPos);
		scene()->addItem(bullet);
		bullet->startTimer();
	}
}

void FieldView::mouseClickTimeout() {
	// bullet spawn timeout done
	bulletTimer->stop();
	bulletSpawn = true;
}

void FieldView::keyPressEvent(QKeyEvent *event) {
	// array for tracking user input
	// 0 = W, 1 = S, 2 = A, 3 = D
	MovementCheck movement[4];
	for(int i = 0; i < 4; i++) movement[i] = MovementCheck::NotSet;

	switch(event->key()) {
	case Qt::Key_W:
		movement[0] = MovementCheck::Moving;
		break;
	case Qt::Key_S:
		movement[1] = MovementCheck::Moving;
		break;
	case Qt::Key_A:
		movement[2] = MovementCheck::Moving;
		break;
	case Qt::Key_D:
		movement[3] = MovementCheck::Moving;
		break;
	default:
		QGraphicsView::keyPressEvent(event);
		return;
	}

	user->setMovement(movement);
}

void FieldView::keyReleaseEvent(QKeyEvent *event) {
	// array for tracking user input
	// 0 = W, 1 = S, 2 = A, 3 = D
	MovementCheck movement[4];
	for(int i = 0; i < 4; i++) movement[i] = MovementCheck::NotSet;

	switch(event->key()) {
	case Qt::Key_W:
		movement[0] = MovementCheck::NotMoving;
		break;
	case Qt::Key_S:
		movement[1] = MovementCheck::NotMoving;
		break;
	case Qt::Key_A:
		movement[2] = MovementCheck::NotMoving;
		break;
	case Qt::Key_D:
		movement[3] = MovementCheck::NotMoving;
		break;
	default:
		QGraphicsView::keyPressEvent(event);
	}

	user->setMovement(movement);
}

void FieldView::mousePressEvent(QMouseEvent *event) {
	mouseClickPos = event->pos();

	// spawn bullet only if not in timeout
	if(bulletSpawn) spawn();
}

void FieldView::mouseMoveEvent(QMouseEvent *event) {
	mouseClickPos = event->pos();

	// spawn bullet only if not in timeout
	if(bulletSpawn) spawn();
}
