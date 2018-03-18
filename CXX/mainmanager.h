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
#include <QVector>

class MainManager : public QObject
{
	Q_OBJECT

	void setupLoaders();

public:
	ActiveInfo *Active;
	QueueLoader *Queue;
	StatusManager *Status;
	TrackManager *TrackMgr;
	QVector<Loader *> Loaders;
	DatabaseManager *DatabaseMgr;

	explicit MainManager(QObject *parent = nullptr);
};

#endif  // MAINMANAGER_H
