#ifndef COLOREXTRACTOR_H
#define COLOREXTRACTOR_H

#include <QColor>
#include <QDebug>
#include <QHash>
#include <QImage>
#include <QObject>
#include <QPoint>
#include <QVector>
#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickItemGrabResult>

class ColorExtractor : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QSize reducedSize READ reducedSize WRITE setReducedSize NOTIFY
				   reducedSizeChanged)
	Q_PROPERTY(QColor firstColor READ firstColor WRITE setFirstColor NOTIFY
				   firstColorChanged)
	Q_PROPERTY(QColor secondColor READ secondColor WRITE setSecondColor NOTIFY
				   secondColorChanged)

	Q_PROPERTY(
		int hueParts READ hueParts WRITE setHueParts NOTIFY huePartsChanged)
	Q_PROPERTY(int lightnessParts READ lightnessParts WRITE setLightnessParts
				   NOTIFY lightnessPartsChanged)
	Q_PROPERTY(int saturationParts READ saturationParts WRITE setSaturationParts
				   NOTIFY saturationPartsChanged)
	Q_PROPERTY(bool singleColor READ singleColor WRITE setSingleColor NOTIFY
				   singleColorChanged)
	Q_PROPERTY(double singlenessRelevance READ singlenessRelevance WRITE
				   setSinglenessRelevance NOTIFY singlenessRelevanceChanged)
	Q_PROPERTY(double lightnessSuppression READ lightnessSuppression WRITE
				   setLightnessSuppression NOTIFY lightnessSuppressionChanged)

	QSize m_reducedSize;
	QColor m_firstColor;
	QColor m_secondColor;
	QSharedPointer<QQuickItemGrabResult> m_result;

	int m_hueParts;
	bool m_singleColor;
	int m_lightnessParts;
	int m_saturationParts;
	double m_singlenessRelevance;
	double m_lightnessSuppression;

	void maxHue(const QImage &img);
	int maxIndex(const QVector<int> list);
	int secondMaxIndex(int maxIndex, const QVector<int> list,
					   bool avoidRange = false);
	QPair<int, int> maxSAndL(const QImage &img, QVector<QPoint> points);
	void applyMaxHue(QColor &color, int hueIndex, const QImage &img,
					 const QVector<QPoint> &points);

private slots:
	void resultReady();

public:
	explicit ColorExtractor(QObject *parent = nullptr);

	QSize reducedSize() const;
	QColor firstColor() const;
	QColor secondColor() const;

	int hueParts() const;
	bool singleColor() const;
	int lightnessParts() const;
	int saturationParts() const;
	double singlenessRelevance() const;
	double lightnessSuppression() const;

public slots:
	void extractItem(QQuickItem *item);
	void extractImage(const QString &source);

public slots:
	void setFirstColor(QColor firstColor);
	void setReducedSize(QSize reducedSize);
	void setSecondColor(QColor secondColor);

	void setHueParts(int hueParts);
	void setSingleColor(bool singleColor);
	void setLightnessParts(int lightnessParts);
	void setSaturationParts(int saturationParts);
	void setSinglenessRelevance(double singlenessRelevance);
	void setLightnessSuppression(double lightnessSuppression);

signals:
	void firstColorChanged(QColor firstColor);
	void reducedSizeChanged(QSize reducedSize);
	void secondColorChanged(QColor secondColor);

	void huePartsChanged(int hueParts);
	void singleColorChanged(bool singleColor);
	void lightnessPartsChanged(int lightnessParts);
	void saturationPartsChanged(int saturationParts);
	void singlenessRelevanceChanged(double singlenessRelevance);
	void lightnessSuppressionChanged(double lightnessSuppression);
};

#endif  // COLOREXTRACTOR_H
