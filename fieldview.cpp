#include "fieldview.h"

FieldView::FieldView(QWidget *parent) : QGraphicsView(parent) {

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
	}

	// pass movement input to user object
	QList<QGraphicsItem*> itemList = scene()->items();
	for(int i = 0; i < itemList.size(); i++) {
		if(itemList[i]->type() == QGraphicsItem::UserType) {
			User *item = (User*) itemList[i];
			item->setMovement(movement);
			break;
		}
	}
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

	// pass movement input to user object
	QList<QGraphicsItem*> itemList = scene()->items();
	for(int i = 0; i < itemList.size(); i++) {
		if(itemList[i]->type() == QGraphicsItem::UserType) {
			User *item = (User*) itemList[i];
			item->setMovement(movement);
			break;
		}
	}
}
