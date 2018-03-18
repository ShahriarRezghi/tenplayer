#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuickControls2/QQuickStyle>

#include <CXX/mainmanager.h>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	QGuiApplication app(argc, argv);
	QQuickStyle::setStyle("Material");

	MainManager M;

	QQmlApplicationEngine engine;
	auto *RC = engine.rootContext();

	RC->setContextProperty("AlbumModel", M.Loaders[AlbumLdr]->model());
	RC->setContextProperty("ArtistModel", M.Loaders[ArtistLdr]->model());
	RC->setContextProperty("SongModel", M.Loaders[SongLdr]->model());
	RC->setContextProperty("QueueModel", M.Loaders[QueueLdr]->model());
	RC->setContextProperty("PlaylistModel", M.Loaders[PlaylistLdr]->model());
	RC->setContextProperty("TrackModel", M.TrackMgr->model());

	RC->setContextProperty("RecentlyAddedModel",
						   M.Loaders[RecentlyAddedLdr]->model());
	RC->setContextProperty("RecentlyPlayedModel",
						   M.Loaders[RecentlyPlayedLdr]->model());

	RC->setContextProperty("MusicPlayer", M.Queue->player());
	RC->setContextProperty("MusicPlaylist", (M.Queue->playlist()));
	RC->setContextProperty("ActiveInfo", M.Active);
	RC->setContextProperty("StatusManager", M.Status);
	RC->setContextProperty("PathManager", M.PathMgr);

	RC->setContextProperty("MainManager", &M);

	engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
	if (engine.rootObjects().isEmpty()) return -1;

	return app.exec();
}
