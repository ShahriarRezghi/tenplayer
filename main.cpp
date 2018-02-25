#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuickControls2/QQuickStyle>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	QGuiApplication app(argc, argv);
	QQuickStyle::setStyle("Material");

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
	if (engine.rootObjects().isEmpty()) return -1;

	return app.exec();
}
