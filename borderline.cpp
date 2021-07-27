#include "borderline.h"

BorderLine::BorderLine(const QPointF &p1, const QPointF &p2, BorderType type) : QGraphicsLineItem(QLineF(p1, p2)), type(type) {

}

BorderLine::BorderType BorderLine::borderType() const {
	return type;
}
