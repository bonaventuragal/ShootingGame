#include "fieldview.h"

FieldView::FieldView(QWidget *parent) : QGraphicsView(parent), mouseClick(true) {
	mouseClickTimer = new QTimer();
	connect(mouseClickTimer, SIGNAL(timeout()), this, SLOT(mouseClickTimeout()));
}

void FieldView::addUser() {
	user = new User();
	user->setPos(scene()->width() / 2 - 10, scene()->height() / 2 - 10);
	scene()->addItem(user);
}

void FieldView::spawn() {
	if(!mouseClickTimer->isActive()) {
		mouseClick = false;
		mouseClickTimer->start(300);
	}
}

void FieldView::mouseClickTimeout() {
	mouseClickTimer->stop();
	mouseClick = true;
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
	if(mouseClick) spawn();
}

void FieldView::mouseMoveEvent(QMouseEvent *event) {
	mouseClickPos = event->pos();
	if(mouseClick) spawn();
}
