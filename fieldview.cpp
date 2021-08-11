#include "fieldview.h"

FieldView::FieldView(QWidget *parent) : QGraphicsView(parent), started(false), paused(false), score(0), level(1) {
	setFocusPolicy(Qt::StrongFocus);

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

	connect(user, SIGNAL(gameOver()), this, SLOT(stopGame()));
}

QPointF FieldView::randomSpawnPoint() {

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

void FieldView::clearView() {
	QList<QGraphicsItem*> itemList = scene()->items();
	for(int i = 0; i < itemList.size(); i++) {
		switch(itemList[i]->type()) {
		case User::Type: {
			User *user = (User*) itemList[i];
			user->deleteLater();
			break;
		}
		case Bullet::Type: {
			Bullet *bullet = (Bullet*) itemList[i];
			bullet->deleteLater();
			break;
		}
		case Enemy::Type: {
			Enemy *enemy = (Enemy*) itemList[i];
			enemy->deleteLater();
			break;
		}
		case BorderLine::Type: {
			BorderLine *borderLine = (BorderLine*) itemList[i];
			borderLine->deleteLater();
			break;
		}
		}
	}
	addBorder();
}

int FieldView::enemySpawnRate() {
	return std::max(250, 750 - (level - 1) * 50);
}

void FieldView::addBorder() {
	BorderLine *topLine = new BorderLine(scene()->sceneRect().topLeft(), scene()->sceneRect().topRight(), BorderLine::Top);
	BorderLine *bottomLine = new BorderLine(scene()->sceneRect().bottomLeft(), scene()->sceneRect().bottomRight(), BorderLine::Bottom);
	BorderLine *leftLine = new BorderLine(scene()->sceneRect().topLeft(), scene()->sceneRect().bottomLeft(), BorderLine::Left);
	BorderLine *rightLine = new BorderLine(scene()->sceneRect().topRight(), scene()->sceneRect().bottomRight(), BorderLine::Right);
	scene()->addItem(topLine);
	scene()->addItem(bottomLine);
	scene()->addItem(leftLine);
	scene()->addItem(rightLine);
}

void FieldView::start() {
	if(!started) {
		level = 1;
		score = 0;
		emit updateScore(score);

		addUser();

		// start enemy spawning time
		enemyTimer->start(enemySpawnRate());

		started = true;
		setFocus();

		emit info("Game started");
	}
}

void FieldView::pause() {
	if(started) {
		QList<QGraphicsItem*> itemList = scene()->items();
		if(!paused) {
			for(int i = 0; i < itemList.size(); i++) {
				if(itemList[i]->type() == Bullet::Type) {
					Bullet *bullet = (Bullet*) itemList[i];
					bullet->stopTimer();
				}
				if(itemList[i]->type() == Enemy::Type) {
					Enemy *enemy = (Enemy*) itemList[i];
					enemy->stopTimer();
				}
			}
			user->stopTimer();
			enemyTimer->stop();
			paused = true;
			emit info("Game paused");
		} else {
			for(int i = 0; i < itemList.size(); i++) {
				if(itemList[i]->type() == Bullet::Type) {
					Bullet *bullet = (Bullet*) itemList[i];
					bullet->startTimer();
				}
				if(itemList[i]->type() == Enemy::Type) {
					Enemy *enemy = (Enemy*) itemList[i];
					enemy->startTimer();
				}
			}
			user->startTimer();
			enemyTimer->start(enemySpawnRate());
			paused = false;
			setFocus();
			emit info("Game resumed");
		}
	}
}

void FieldView::stopGame() {
	if(started) {
		// stop timers to prevent unwanted udpate
		bulletTimer->stop();
		enemyTimer->stop();
		user->stopTimer();
		QList<QGraphicsItem*> itemList = scene()->items();
		for(int i = 0; i < itemList.size(); i++) {
			if(itemList[i]->type() == Bullet::Type) {
				Bullet *bullet = (Bullet*) itemList[i];
				bullet->stopTimer();
			}
			if(itemList[i]->type() == Enemy::Type) {
				Enemy *enemy = (Enemy*) itemList[i];
				enemy->stopTimer();
			}
		}

		clearView();
		started = false;
		paused = false;

		emit info("Game over");
	}
}

void FieldView::spawnBullet() {
	if(started && !paused) {
		// create new bullet
		Bullet *bullet = new Bullet();
		bullet->setPos(user->pos().x() + user->boundingRect().width() / 2, user->pos().y() + user->boundingRect().height() / 2 - bullet->boundingRect().height() / 2);
		bullet->setZValue(-1);
		bullet->setTarget(mouseClickPos);
		scene()->addItem(bullet);
		bullet->startTimer();
	}
}

void FieldView::spawnEnemy() {
	if(started && !paused) {
		enemyTimer->stop();

		// create new enemy
		Enemy *enemy = new Enemy();
		enemy->setPos(randomSpawnPoint());
		enemy->setTarget(user->pos());
		connect(user, SIGNAL(updatePos(QPointF)), enemy, SLOT(updateTargetPos(QPointF)));
		connect(enemy, SIGNAL(shot()), this, SLOT(enemyShot()));
		scene()->addItem(enemy);
		enemy->startTimer();

		enemyTimer->start(enemySpawnRate());
	}
}

void FieldView::enemyShot() {
	score += 1;
	emit updateScore(score);

	if(score % 25 == 0) {
		level++;
		emit info("Level up! Level: " + QString::number(level));
	}
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
	case Qt::Key_Space:
		pause();
		break;
	default:
		QGraphicsView::keyPressEvent(event);
		return;
	}

	if(started && !paused) user->setMovement(movement);
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

	if(started && !paused) user->setMovement(movement);
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
