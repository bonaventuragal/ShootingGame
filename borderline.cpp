#include "borderline.h"

BorderLine::BorderLine(const QPointF &p1, const QPointF &p2, BorderType type) : QGraphicsLineItem(QLineF(p1, p2)), m_borderType(type) {

}

BorderLine::BorderType BorderLine::borderType() const {
	return m_borderType;
}

int BorderLine::type() const {
	return BorderLine::Type;
}
