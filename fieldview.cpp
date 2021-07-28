#include "fieldview.h"

FieldView::FieldView(QWidget *parent) : QGraphicsView(parent) {
	// timer for bullet spawning timeout
	bulletTimer = new QTimer();
	connect(bulletTimer, SIGNAL(timeout()), this, SLOT(spawnBullet()));

	enemyTimer = new QTimer();
	connect(enemyTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
}

void FieldView::addUser() {
	user = new User();
	user->setPos(scene()->width() / 2 - 10, scene()->height() / 2 - 10);
	scene()->addItem(user);

	// start enemy spawning time
	enemyTimer->start(750);
}

QPointF FieldView::randomSpawnPoint() {
//	srand(time(NULL));

	// set random spawn area (top, bottom, left, right)
	int random = rand() % 4;

	// set random pos
	qreal x = 0, y = 0;
	switch(random) {
	case 0:
		// top
		y = 0;
		x = rand() % (int) (sceneRect().width() - 20);
		break;
	case 1:
		// bottom
		y = height() - 40;
		x = rand() % (int) (sceneRect().width() - 20);
		break;
	case 2:
		// left
		x = 0;
		y = rand() % (int) (sceneRect().height() - 20);
		break;
	case 3:
		// right
		x = width() - 40;
		y = rand() % (int) (sceneRect().height() - 20);
		break;
	}
	return QPointF(x, y);
}

void FieldView::spawnBullet() {
	// create new bullet
	Bullet *bullet = new Bullet();
	bullet->setPos(user->pos().x() + user->boundingRect().width() / 2, user->pos().y() + user->boundingRect().height() / 2 - bullet->boundingRect().height() / 2);
	bullet->setZValue(-1);
	bullet->setTarget(mouseClickPos);
	scene()->addItem(bullet);
	bullet->startTimer();
}

void FieldView::spawnEnemy() {
	// create new enemy
	Enemy *enemy = new Enemy();
	enemy->setPos(randomSpawnPoint());
	enemy->setTarget(user->pos());
	connect(user, SIGNAL(updatePos(QPointF)), enemy, SLOT(updateTargetPos(QPointF)));
	scene()->addItem(enemy);
	enemy->startTimer();
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
	spawnBullet();
	bulletTimer->start(150);
}

void FieldView::mouseMoveEvent(QMouseEvent *event) {
	mouseClickPos = event->pos();
}

void FieldView::mouseReleaseEvent(QMouseEvent *event) {
	bulletTimer->stop();

	Q_UNUSED(event)
}
