#include "colorextractor.h"

void ColorExtractor::extractImage(const QString &source)
{
	QImage img(source);
	if (img.isNull()) return;
	img = img.scaled(m_reducedSize);
	maxHue(img);
}

void ColorExtractor::maxHue(const QImage &img)
{
	QVector<int> list(m_hueParts, 0);
	QVector<QVector<QPoint>> points(m_hueParts, QVector<QPoint>());

	int blackCount = 0;
	int whiteCount = 0;

	for (int i = 0; i < img.width(); ++i)
		for (int j = 0; j < img.height(); ++j)
		{
			QColor C = img.pixelColor(i, j);
			int ligthness = C.lightness();

			if (ligthness < m_lightnessSuppression * 256)
				++blackCount;
			else if (ligthness > (256 - m_lightnessSuppression * 256))
				++whiteCount;
			else
			{
				int hue = C.hslHue() / (360 / m_hueParts);

				++list[hue];
				points[hue] << QPoint(i, j);
			}
		}

	int maxhindex = maxIndex(list);
	int secondmaxhindex = secondMaxIndex(maxhindex, list);

	QVector<int> listofall;
	listofall << list[maxhindex] << list[secondmaxhindex] << whiteCount
			  << blackCount;

	int maxofall = maxIndex(listofall);
	int secondmaxofall = secondMaxIndex(maxofall, listofall, true);

	setSingleColor(listofall[secondmaxofall] / listofall[maxofall] <=
				   m_singlenessRelevance);

	if (maxofall == 0)
		applyMaxHue(m_firstColor, maxhindex, img, points[maxhindex]);
	else if (maxofall == 1)
		applyMaxHue(m_firstColor, secondmaxhindex, img,
					points[secondmaxhindex]);
	else if (maxofall == 2)
		m_firstColor = "White";
	else if (maxofall == 3)
		m_firstColor = "black";

	if (secondmaxofall == 0)
		applyMaxHue(m_secondColor, maxhindex, img, points[maxhindex]);
	else if (secondmaxofall == 1)
		applyMaxHue(m_secondColor, secondmaxhindex, img,
					points[secondmaxhindex]);
	else if (secondmaxofall == 2)
		m_secondColor = "White";
	else if (secondmaxofall == 3)
		m_secondColor = "black";

	emit firstColorChanged(m_firstColor);
	emit secondColorChanged(m_secondColor);
}

void ColorExtractor::applyMaxHue(QColor &color, int hueIndex, const QImage &img,
								 const QVector<QPoint> &points)
{
	auto pair = maxSAndL(img, points);
	color = QColor::fromHsl(hueIndex * (360 / m_hueParts),
							pair.first * (256 / m_saturationParts),
							pair.second * (256 / m_lightnessParts));
}

void ColorExtractor::extractItem(QQuickItem *item)
{
	if (item == nullptr) return;

	m_result = item->grabToImage(m_reducedSize);
	connect(m_result.data(), &QQuickItemGrabResult::ready, this,
			&ColorExtractor::resultReady);
}

void ColorExtractor::resultReady()
{
	auto *result = m_result.data();
	QImage img = result->image();
	if (img.isNull()) return;
	m_result.clear();

	maxHue(img);
}

QPair<int, int> ColorExtractor::maxSAndL(const QImage &img,
										 QVector<QPoint> points)
{
	QVector<int> llist(m_lightnessParts, 0);
	QVector<int> slist(m_saturationParts, 0);

	for (const QPoint &point : points)
	{
		int lightness =
			img.pixelColor(point).lightness() / (256 / m_lightnessParts);
		int saturation =
			img.pixelColor(point).hslSaturation() / (256 / m_saturationParts);

		++slist[saturation];
		++llist[lightness];
	}

	int maxlindex = maxIndex(llist);
	int maxsindex = maxIndex(slist);

	return QPair<int, int>(maxsindex, maxlindex);
}

int ColorExtractor::maxIndex(const QVector<int> list)
{
	int topIndex = 0;
	for (int i = 0; i < list.count(); ++i)
		if (list[topIndex] < list[i]) topIndex = i;

	return topIndex;
}

int ColorExtractor::secondMaxIndex(int maxIndex, const QVector<int> list,
								   bool avoidRange)
{
	int topIndex = 0;
	if (maxIndex == 0) topIndex = 1;

	for (int i = 0; i < list.count(); ++i)
	{
		if (!avoidRange)
		{
			if (abs(i - maxIndex) <= (m_hueParts / 15)) continue;
		}
		else
		{
			if (i == maxIndex) continue;
		}

		if (list[topIndex] < list[i]) topIndex = i;
	}

	return topIndex;
}

void ColorExtractor::setReducedSize(QSize reducedSize)
{
	if (m_reducedSize == reducedSize) return;

	m_reducedSize = reducedSize;
	emit reducedSizeChanged(m_reducedSize);
}

void ColorExtractor::setFirstColor(QColor firstColor)
{
	if (m_firstColor == firstColor) return;

	m_firstColor = firstColor;
	emit firstColorChanged(m_firstColor);
}

void ColorExtractor::setSecondColor(QColor secondColor)
{
	if (m_secondColor == secondColor) return;

	m_secondColor = secondColor;
	emit secondColorChanged(m_secondColor);
}

void ColorExtractor::setHueParts(int hueParts)
{
	if (m_hueParts == hueParts) return;

	m_hueParts = hueParts;
	emit huePartsChanged(m_hueParts);
}

void ColorExtractor::setLightnessParts(int lightnessParts)
{
	if (m_lightnessParts == lightnessParts) return;

	m_lightnessParts = lightnessParts;
	emit lightnessPartsChanged(m_lightnessParts);
}

void ColorExtractor::setSaturationParts(int saturationParts)
{
	if (m_saturationParts == saturationParts) return;

	m_saturationParts = saturationParts;
	emit saturationPartsChanged(m_saturationParts);
}

void ColorExtractor::setSinglenessRelevance(double singlenessRelevance)
{
	if (qFuzzyCompare(m_singlenessRelevance, singlenessRelevance)) return;

	m_singlenessRelevance = singlenessRelevance;
	emit singlenessRelevanceChanged(m_singlenessRelevance);
}

void ColorExtractor::setLightnessSuppression(double lightnessSuppression)
{
	if (qFuzzyCompare(m_lightnessSuppression, lightnessSuppression)) return;

	m_lightnessSuppression = lightnessSuppression;
	emit lightnessSuppressionChanged(m_lightnessSuppression);
}

void ColorExtractor::setSingleColor(bool singleColor)
{
	if (m_singleColor == singleColor) return;

	m_singleColor = singleColor;
	emit singleColorChanged(m_singleColor);
}

ColorExtractor::ColorExtractor(QObject *parent) : QObject(parent)
{
	m_hueParts = 90;
	m_singleColor = false;
	m_lightnessParts = 32;
	m_saturationParts = 32;
	m_singlenessRelevance = .2;
	m_lightnessSuppression = .04;
	m_reducedSize = QSize(50, 50);
}

double ColorExtractor::singlenessRelevance() const
{
	return m_singlenessRelevance;
}

double ColorExtractor::lightnessSuppression() const
{
	return m_lightnessSuppression;
}

QColor ColorExtractor::firstColor() const { return m_firstColor; }
QSize ColorExtractor::reducedSize() const { return m_reducedSize; }
QColor ColorExtractor::secondColor() const { return m_secondColor; }

bool ColorExtractor::singleColor() const { return m_singleColor; }

int ColorExtractor::hueParts() const { return m_hueParts; }
int ColorExtractor::lightnessParts() const { return m_lightnessParts; }
int ColorExtractor::saturationParts() const { return m_saturationParts; }
