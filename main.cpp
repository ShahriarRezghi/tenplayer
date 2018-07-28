#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuickControls2/QQuickStyle>

#include <CXX/mainmanager.h>

// TODO support more file types
// TODO saving current tab doesn't work
// TODO put a slider so that the user can scale delegate sizes

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	qRegisterMetaType<QList<QStandardItem *>>("QList<QStandardItem *>");

	QGuiApplication app(argc, argv);
	QQuickStyle::setStyle("Material");

	MainManager M;
	bool x = M.playFromArguements(app.arguments());

	// TODO this is the old way of finding artwork sizes
	//	MM.setImageSize(QSize(app.primaryScreen()->geometry().width() / 5,
	//						  app.primaryScreen()->geometry().width()
	/// 5));

	QQmlApplicationEngine engine;
	auto *RC = engine.rootContext();

	RC->setContextProperty("AlbumModel", M.Loaders[AlbumLdr]->model());
	RC->setContextProperty("ArtistModel", M.Loaders[ArtistLdr]->model());
	RC->setContextProperty("SongModel", M.Loaders[SongLdr]->model());
	RC->setContextProperty("QueueModel", M.Loaders[QueueLdr]->model());
	RC->setContextProperty("PlaylistModel", M.Loaders[PlaylistLdr]->model());
	RC->setContextProperty("TrackModel", M.TrackMgr->model());

	RC->setContextProperty("AlbumSearchModel",
						   M.Loaders[AlbumLdr]->searchModel());
	RC->setContextProperty("ArtistSearchModel",
						   M.Loaders[ArtistLdr]->searchModel());
	RC->setContextProperty("SongSearchModel",
						   M.Loaders[SongLdr]->searchModel());

	RC->setContextProperty("RecentlyAddedModel",
						   M.Loaders[RecentlyAddedLdr]->model());
	RC->setContextProperty("RecentlyPlayedModel",
						   M.Loaders[RecentlyPlayedLdr]->model());

	RC->setContextProperty("MusicPlayer", M.Queue->player());
	RC->setContextProperty("MusicPlaylist", (M.Queue->playlist()));
	RC->setContextProperty("ActiveInfo", M.Active);
	RC->setContextProperty("StatusManager", M.Status);
	RC->setContextProperty("PathManager", M.PathMgr);
	RC->setContextProperty("DetailsManager", M.DetailsMgr);
	RC->setContextProperty("DetailsModel", M.DetailsMgr->model());

	RC->setContextProperty("MainManager", &M);

	engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
	if (engine.rootObjects().isEmpty()) return -1;

	if (x) M.Queue->player()->play();
	M.safeRefresh();

	return app.exec();
}
