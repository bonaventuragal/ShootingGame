#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include "user.h"
#include "borderline.h"
#include "bullet.h"
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

private:
	User *user;
	QTimer *bulletTimer;
	QPoint mouseClickPos;

private slots:
	void spawn();

protected:
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

};

#endif // FIELDVIEW_H
