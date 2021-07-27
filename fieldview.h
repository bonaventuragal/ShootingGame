#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include "user.h"
#include "borderline.h"
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
	QTimer *mouseClickTimer;
	QPoint mouseClickPos;
	bool mouseClick;

	void spawn();

private slots:
	void mouseClickTimeout();

protected:
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

};

#endif // FIELDVIEW_H
