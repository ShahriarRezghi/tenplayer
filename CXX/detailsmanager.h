#ifndef DETAILSMANAGER_H
#define DETAILSMANAGER_H

#include <QObject>

#include "model.h"
#include "structs.h"

class DetailsManager : public QObject
{
	Q_OBJECT

	QmlModel *m_model;

public:
	explicit DetailsManager(QObject *parent = nullptr);

	QStandardItemModel *model() const;

	void showItem(QStandardItem *item);
	void showItems(const QList<QStandardItem *> &items);
};

#endif  // DETAILSMANAGER_H
