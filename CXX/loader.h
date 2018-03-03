#ifndef LOADER_H
#define LOADER_H

#include "activeinfo.h"
#include "model.h"
#include "pathmanager.h"
#include "statusmanager.h"
#include "structs.h"

#include <QDebug>
#include <QObject>
#include <functional>

class QueueLoader;
class TrackManager;
class RecentlyPlayedLoader;

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
	static ActiveInfo *Active;
	static QString ArtworkPath;

	static PathManager *Path;
	static StatusManager *Status;

	static QueueLoader *Queue;
	static TrackManager *Track;
	static RecentlyPlayedLoader *RecentlyPlayed;

public:
	explicit Loader(QObject *parent = nullptr);

	virtual void load() = 0;
	virtual void clear();

	QmlModel *model() const;
};

#endif  // LOADER_H
