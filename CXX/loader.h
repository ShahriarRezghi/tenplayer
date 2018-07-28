#ifndef LOADER_H
#define LOADER_H

#include "activeinfo.h"
#include "detailsmanager.h"
#include "model.h"
#include "pathmanager.h"
#include "statusmanager.h"
#include "structs.h"

#include <QDebug>
#include <QObject>
#include <functional>

class QueueLoader;
class TrackManager;
class PlaylistLoader;
class RecentlyPlayedLoader;

class Loader : public QObject
{
	Q_OBJECT

	int m_searchRole;

	friend class MainManager;

protected:
	QmlModel *m_model;
	QmlModel *m_searchModel;

	void deleteSong(const QVariant &id);

	void createSearchModel(int searchRole);
	void sortModel(int role, bool asc = true);
	static QStandardItem *recordToItem(const QSqlRecord &record);
	static QString getArtwork(const QString &album, const QString &albumArtist);
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
	static DetailsManager *Details;

	static QueueLoader *Queue;
	static TrackManager *Track;
	static PlaylistLoader *Playlist;
	static RecentlyPlayedLoader *RecentlyPlayed;

public:
	explicit Loader(QObject *parent = nullptr);

	virtual void search(const QString &text);

	virtual void load() = 0;
	virtual void clear();
	virtual void clicked(const int &index) = 0;

	virtual void actionTriggered(const int &type, const int &index,
								 const QVariant &extra = QVariant()) = 0;

	virtual void searchActionTriggered(const int &type, const int &index,
									   const QVariant &extra);

	void searchClicked(const int &index);

	QmlModel *model() const;
	QmlModel *searchModel() const;

protected slots:
	virtual void addItemsToModel(const QList<QStandardItem *> &items);

signals:
	void addItemsToModelFromThread(const QList<QStandardItem *> &items);
};

#endif  // LOADER_H
