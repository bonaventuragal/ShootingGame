#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include "user.h"
#include "MovementCheck.h"
#include <QGraphicsView>
#include <QKeyEvent>

class FieldView : public QGraphicsView {

	Q_OBJECT

public:
	FieldView(QWidget *parent = nullptr);

protected:
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;

};

#endif // FIELDVIEW_H
