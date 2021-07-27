#ifndef BORDERLINE_H
#define BORDERLINE_H

#include <QGraphicsLineItem>

class BorderLine : public QGraphicsLineItem {

public:
	enum BorderType {Top, Bottom, Left, Right};
	enum {Type = UserType + 2};

	BorderLine(const QPointF &p1, const QPointF &p2, BorderType type);
	BorderType borderType() const;

private:
	BorderType type;

};

#endif // BORDERLINE_H
