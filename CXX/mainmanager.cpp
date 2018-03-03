#include "mainmanager.h"

MainManager::MainManager(QObject *parent) : QObject(parent) {}

void MainManager::setupLoaders()
{
	TrackMgr = new TrackManager(this);
	DatabaseMgr = new DatabaseManager(this);
	Queue = new QueueLoader(this);

	Loaders << new AlbumLoader(this) << new ArtistLoader(this)
			<< new SongLoader(this) << Queue << new RecentlyAddedLoader(this)
			<< new RecentlyPlayedLoader(this) << new PlaylistLoader(this);

	Loader::Queue = Queue;
	Loader::Track = TrackMgr;
	Loader::Query = DatabaseMgr->query();
	Loader::RecentlyPlayed = (RecentlyPlayedLoader *)Loaders[RecentlyPlayedLdr];
}
