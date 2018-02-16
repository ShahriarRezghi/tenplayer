#ifndef LOADER_H
#define LOADER_H

#include "model.h"
#include "structs.h"

#include <QDebug>
#include <QObject>
#include <QtSql>
#include <functional>

class Loader : public QObject
{
	Q_OBJECT

protected:
	QmlModel *m_model;

	void sortModel(int role, bool asc = true);
	static QStandardItem *recordToItem(const QSqlRecord &record);
	QString getArtwork(const QString &album, const QString &albumArtist);
	static bool sortItemsByRole(int role, QStandardItem *I1, QStandardItem *I2);

	static void sortItemList(std::initializer_list<int> roles,
							 QList<QStandardItem *> &items);

	static std::function<bool(QStandardItem *, QStandardItem *)>
	getCompareFunction(int role);

public:
	static QSqlQuery *Query;
	static QString ArtworkPath;

public:
	explicit Loader(QObject *parent = nullptr);

	virtual void load() = 0;
	virtual void clear();
};

#endif  // LOADER_H
