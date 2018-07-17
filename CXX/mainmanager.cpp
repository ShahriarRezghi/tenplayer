#include "mainmanager.h"

MainManager::MainManager(QObject *parent) : QObject(parent) { setupLoaders(); }

void MainManager::setupLoaders()
{
	PathMgr = new PathManager(this);
	TrackMgr = new TrackManager(this);
	DatabaseMgr = new DatabaseManager(this);
	Queue = new QueueLoader(this);
	Status = new StatusManager(this);

	Loaders << new AlbumLoader(this) << new ArtistLoader(this)
			<< new SongLoader(this) << Queue << new RecentlyAddedLoader(this)
			<< new RecentlyPlayedLoader(this) << new PlaylistLoader(this);

	Loader::Status = Status;
	Loader::Queue = Queue;
	Loader::Track = TrackMgr;
	Loader::Query = DatabaseMgr->query();
	Loader::RecentlyPlayed =
		static_cast<RecentlyPlayedLoader *>(Loaders[RecentlyPlayedLdr]);

	QString artworkPath = QDir::currentPath() + QDir::separator() + "artworks";
	Loader::ArtworkPath = artworkPath + QDir::separator();  // TODO hardcoded
	if (!QDir(artworkPath).exists() && !QDir().mkdir(artworkPath))
		qDebug() << "failed to create artworks directory";
}

void MainManager::loadStatic(MainManager *manager) { manager->load(); }

void MainManager::refreshStatic(MainManager *manager) { manager->refresh(); }

void MainManager::loadDirStatic(MainManager *manager, const QString &path)
{
	manager->loadDir(path);
}

void MainManager::loadFilesStatic(MainManager *manager, const QStringList &list)
{
	manager->loadFiles(list);
}

void MainManager::safeLoad()
{
	QtConcurrent::run(&MainManager::loadStatic, this);
}

void MainManager::safeLoadDir(const QString &path)
{
	QtConcurrent::run(&MainManager::loadDirStatic, this, path);
}

void MainManager::safeLoadFiles(const QStringList &list)
{
	QtConcurrent::run(&MainManager::loadFilesStatic, this, list);
}

void MainManager::safeRefresh()
{
	QtConcurrent::run(&MainManager::refreshStatic, this);
}

void MainManager::loaderClicked(const int &loader, const int &index)
{
	Loaders[loader]->clicked(index);
}

void MainManager::loaderSearchClicked(const int &loader, const int &index)
{
	Loaders[loader]->searchClicked(index);
}

void MainManager::loaderActionTriggered(const int &loader, const int &type,
										const int &index, const QVariant &extra)
{
	Loaders[loader]->actionTriggered(type, index, extra);
}

void MainManager::trackActionTriggered(const int &type, const int &index,
									   const QVariant &extra)
{
	TrackMgr->actionTriggered(type, index, extra);
}

void MainManager::loaderSearchActionTriggered(const int &loader,
											  const int &type, const int &index,
											  const QVariant &extra)
{
	Loaders[loader]->searchActionTriggered(type, index, extra);
}
