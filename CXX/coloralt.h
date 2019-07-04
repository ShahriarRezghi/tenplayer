#ifndef COLORALT_H
#define COLORALT_H

#include <QColor>
#include <QObject>
#include <cmath>

class ColorAlt : public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY(ColorAlt)

public:
	ColorAlt(QObject *parent = 0);

public slots:
	QColor invert(QColor C);
	QColor hardInvert(const QColor &C);
	QColor softInvert(const QColor &C);

	double hue(const QColor &C);
	double lightness(const QColor &C);
	double saturation(const QColor &C);

	QColor darker(QColor C, const double &value = .1);
	QColor lighter(QColor C, const double &value = .1);
	QColor toMiddle(QColor C, const double &value = .1);
	QColor fromMiddle(QColor C, const double &value = .1);

	QColor lighten(QColor C, const double &value);
	QColor transparent(QColor C, const double &value);
	bool areDistant(const QColor &C1, const QColor &C2,
					const double &distance = .1);
};

#endif  // COLORALT_H
