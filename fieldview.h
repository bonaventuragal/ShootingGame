#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include "user.h"
#include "borderline.h"
#include "bullet.h"
#include "enemy.h"
#include "MovementCheck.h"
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QPoint>

class FieldView : public QGraphicsView {

	Q_OBJECT

public:
	FieldView(QWidget *parent = nullptr);
	void addUser();
	void addBorder();

private:
	User *user;
	QTimer *bulletTimer;
	QTimer *enemyTimer;
	QPoint mouseClickPos;
	bool started;
	bool paused;

	QPointF randomSpawnPoint();
	void clearView();

private slots:
	void start();
	void pause();
	void stopGame();
	void spawnBullet();
	void spawnEnemy();

protected:
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

signals:
	void info(QString);

};

#endif // FIELDVIEW_H
