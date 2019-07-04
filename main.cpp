#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QScreen>
#include <QtQuickControls2/QQuickStyle>

#include <CXX/coloralt.h>
#include <CXX/colorextractor.h>
#include <CXX/mainmanager.h>

// TODO supporting all files tag data and for artworks: mp3, ogg, flac, m4a,
// wav. is this enough?
// TODO use appSettings.delegateScale to scale the delegates
// TODO delegate texts are bold. see how that looks.
// TODO right now busy indicator is shown when refreshing. should it?
// TODO check and optimize c++ and qml codes
// TODO error dialog is written. complete it
// check for being stuck on repeat when tracks are not found
// TODO important: remove descriptive comments

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    qmlRegisterType<ColorExtractor>("ColorExtractor", 1, 0, "ColorExtractor");
    qRegisterMetaType<QList<QStandardItem *>>("QList<QStandardItem *>");

    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    app.setOrganizationName("TenPlayer");
    app.setOrganizationDomain("");
    app.setApplicationName("TenPlayer");

    ColorAlt CA;
    MainManager M;
    bool x = M.playFromArguements(app.arguments());

    // TODO this is the old way of finding artwork sizes. is this right?
    //	M.setArtworkSize(QSize(app.primaryScreen()->geometry().width() / 5,
    //						   app.primaryScreen()->geometry().width()
    /// 5));
    M.setArtworkSize(QSize(512, 512));

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
    RC->setContextProperty("ColorAlt", &CA);

    engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
    if (engine.rootObjects().isEmpty()) return -1;

    if (x) M.Queue->player()->play();
    M.safeRefresh();

    return app.exec();
}
