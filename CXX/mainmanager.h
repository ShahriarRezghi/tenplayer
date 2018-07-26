#ifndef MAINMANAGER_H
#define MAINMANAGER_H

#include "albumloader.h"
#include "artistloader.h"
#include "playlistloader.h"
#include "queueloader.h"
#include "recentlyaddedloader.h"
#include "recentlyplayedloader.h"
#include "songloader.h"
#include "trackmanager.h"

#include "activeinfo.h"
#include "databasemanager.h"
#include "pathmanager.h"
#include "statusmanager.h"

#include <QObject>
#include <QStandardPaths>
#include <QVector>
#include <QtConcurrent/QtConcurrent>

using QSP = QStandardPaths;

class MainManager : public QObject
{
	Q_OBJECT

	void setupLoaders();

	void eraseAll();

	void load();
	void refresh();
	void loadDir(const QString &dir);
	void loadFiles(const QStringList &files);

	static void loadStatic(MainManager *manager);
	static void refreshStatic(MainManager *manager);
	static void loadDirStatic(MainManager *manager, const QString &path);
	static void loadFilesStatic(MainManager *manager, const QStringList &list);

private slots:
	void clearAll();

public:
	QSize ArtworkSize;

	ActiveInfo *Active;
	QueueLoader *Queue;

	PathManager *PathMgr;
	StatusManager *Status;
	TrackManager *TrackMgr;
	DetailsManager *DetailsMgr;

	QVector<Loader *> Loaders;
	DatabaseManager *DatabaseMgr;

	explicit MainManager(QObject *parent = nullptr);

	bool playFromArguements(QStringList files);

public slots:
	void safeLoad();
	void safeRefresh();
	void safeLoadDir(const QString &path);
	void safeLoadFiles(const QStringList &list);

	void loaderClicked(const int &loader, const int &index);
	void trackClicked(const int &index);
	void loaderSearchClicked(const int &loader, const int &index);
	void trackActionTriggered(const int &type, const int &index,
							  const QVariant &extra = QVariant());
	void loaderActionTriggered(const int &loader, const int &type,
							   const int &index,
							   const QVariant &extra = QVariant());
	void loaderSearchActionTriggered(const int &loader, const int &type,
									 const int &index,
									 const QVariant &extra = QVariant());

	void search(const QString &text);
	void addPlaylist(const QString &name);

signals:
	void clearAllSignal();
};

#endif  // MAINMANAGER_H
