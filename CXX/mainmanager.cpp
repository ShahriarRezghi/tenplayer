#include "mainmanager.h"

MainManager::MainManager(QObject *parent) : QObject(parent)
{
	setupLoaders();
	connect(this, &MainManager::clearAllSignal, this, &MainManager::clearAll);
}

bool MainManager::playFromArguements(QStringList files)
{
	//	files << "/run/media/shahriar/MyFiles/All Music/Beta Music/Extreme –
	// More Than Words.mp3";

	files.removeFirst();
	if (files.isEmpty()) return false;

	auto toBeImportedFiles = PathMgr->addFiles(files);
	PathMgr->save();

	DatabaseMgr->import(ArtworkSize, toBeImportedFiles);

	QList<QStandardItem *> items;
	auto Query = DatabaseMgr->query();

	QString cmd = "SELECT rowid, * FROM music WHERE path IN (";
	for (int i = 0; i < files.size(); ++i) cmd += "?, ";
	cmd.remove(cmd.size() - 2, 2);
	cmd += ");";

	Query->prepare(cmd);
	for (const auto &file : files) Query->addBindValue(file);
	Query->exec();

	while (Query->next()) items << Loader::recordToItem(Query->record());
	Queue->addItems(items);

	return true;
}

void MainManager::setupLoaders()
{
	auto sep = QDir::separator();
	auto dataPath = QSP::writableLocation(QSP::AppDataLocation);

	ArtworkSize = QSize(512, 512);

	QString artworkPath = dataPath + sep + "artworks";
	QString databasePath = dataPath + sep + "database";

	if (!QDir(artworkPath).exists() && !QDir().mkdir(artworkPath))
		qDebug() << "failed to create artworks directory";

	Active = new ActiveInfo(this);
	Queue = new QueueLoader(this);
	PathMgr = new PathManager(this);
	Status = new StatusManager(this);
	TrackMgr = new TrackManager(this);
	DetailsMgr = new DetailsManager(this);
	DatabaseMgr = new DatabaseManager(databasePath, this);

	Loaders << new AlbumLoader(this) << new ArtistLoader(this)
			<< new SongLoader(this) << Queue << new RecentlyAddedLoader(this)
			<< new RecentlyPlayedLoader(this) << new PlaylistLoader(this);

	Loader::Queue = Queue;
	Loader::Path = PathMgr;
	Loader::Status = Status;
	Loader::Active = Active;
	Loader::Track = TrackMgr;
	Loader::Details = DetailsMgr;
	Loader::Query = DatabaseMgr->query();
	Loader::Playlist = static_cast<PlaylistLoader *>(Loaders[PlaylistLdr]);
	Loader::RecentlyPlayed =
		static_cast<RecentlyPlayedLoader *>(Loaders[RecentlyPlayedLdr]);

	Loader::ArtworkPath = artworkPath + QDir::separator();
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

void MainManager::trackClicked(const int &index) { TrackMgr->clicked(index); }

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

void MainManager::search(const QString &text)
{
	Loaders[AlbumLdr]->search(text);
	Loaders[ArtistLdr]->search(text);
	Loaders[SongLdr]->search(text);
}

void MainManager::addPlaylist(const QString &name)
{
	static_cast<PlaylistLoader *>(Loaders[PlaylistLdr])->addPlaylist(name);
}
