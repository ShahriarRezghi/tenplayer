#include "databasemanager.h"

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
	m_databasePath =
		"/home/shahriar/.local/share/TenPlayer/Database";  // TODO set properly

	createDatabase();
	createTables();
}

DatabaseManager::~DatabaseManager() { delete m_query; }

void DatabaseManager::createTables()
{
	m_query = new QSqlQuery(m_database);

	//	bool x = m_query->exec(
	//		"CREATE TABLE IF NOT EXISTS music"
	//		"(title STRING, album STRING, artist STRING, "
	//		"albumartist STRING, track INTEGER, genre STRING, "
	//		"year INTEGER, path STRING);");

	//	if (!x) qDebug() << "Couldn't Create Music Table!";

	//	x = m_query->exec("CREATE TABLE IF NOT EXISTS playlist(name STRING);");

	//	if (!x) qDebug() << "Couldn't Create Playlist Table!";

	//	x = m_query->exec(
	//		"CREATE TABLE IF NOT EXISTS join(pid INTEGER, mid INTEGER, row "
	//		"INTEGER);");

	//	if (!x) qDebug() << "Couldn't Create Join Table!";
}

void DatabaseManager::createDatabase()
{
	m_database = QSqlDatabase::addDatabase("QSQLITE");
	m_database.setDatabaseName(m_databasePath);
	if (!m_database.open()) qDebug() << "Couldn't Open Database!";
}

QSqlQuery *DatabaseManager::query() const { return m_query; }
