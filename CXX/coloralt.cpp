#include "coloralt.h"

QColor ColorAlt::hardInvert(const QColor &C)
{
	return C.lightnessF() >= .5 ? lighten(C, 0) : lighten(C, 1);
}

QColor ColorAlt::softInvert(const QColor &C)
{
	return C.lightnessF() >= .5 ? lighten(C, .1) : lighten(C, .9);
}

QColor ColorAlt::transparent(QColor C, const double &value)
{
	C.setAlphaF(value);

	return C;
}

QColor ColorAlt::darker(QColor C, const double &value)
{
	return lighten(C, std::max(C.lightnessF() - value, 0.0));
}

QColor ColorAlt::lighter(QColor C, const double &value)
{
	return lighten(C, std::min(C.lightnessF() + value, 1.0));
}

QColor ColorAlt::toMiddle(QColor C, const double &value)
{
	if (C.lightnessF() >= .5)
		return darker(C, value);
	else
		return lighter(C, value);
}

QColor ColorAlt::fromMiddle(QColor C, const double &value)
{
	if (C.lightnessF() < .5)
		return darker(C, value);
	else
		return lighter(C, value);
}

QColor ColorAlt::lighten(QColor C, const double &value)
{
	C.setHslF(C.hslHueF(), C.hslSaturationF(), value, C.alphaF());
	return C;
}

QColor ColorAlt::invert(QColor C)
{
	double L = C.lightnessF();
	L = L >= .5 ? .5 - L / 2 : 1 - L;
	return lighten(C, L);
}

bool ColorAlt::areDistant(const QColor &C1, const QColor &C2,
						  const double &distance)
{
	return std::abs(C1.lightnessF() - C2.lightnessF()) > distance;
}

ColorAlt::ColorAlt(QObject *parent) : QObject(parent) {}
double ColorAlt::hue(const QColor &C) { return C.hslHueF(); }
double ColorAlt::lightness(const QColor &C) { return C.lightnessF(); }
double ColorAlt::saturation(const QColor &C) { return C.hslSaturationF(); }
