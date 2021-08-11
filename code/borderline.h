#ifndef BORDERLINE_H
#define BORDERLINE_H

#include <QGraphicsLineItem>

class BorderLine : public QObject, public QGraphicsLineItem {

public:
	enum BorderType {Top, Bottom, Left, Right};
	enum {Type = UserType + 2};

	BorderLine(const QPointF &p1, const QPointF &p2, BorderType type);
	BorderType borderType() const;
	int type() const override;

private:
	BorderType m_borderType;

};

#endif // BORDERLINE_H
