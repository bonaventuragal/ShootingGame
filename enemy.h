#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>

class Enemy : public QObject, public QGraphicsItem {
	Q_OBJECT
public:
	Enemy();
};

#endif // ENEMY_H
