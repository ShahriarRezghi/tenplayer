#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QDebug>
#include <QObject>
#include <QtSql>

class DatabaseManager : public QObject
{
	Q_OBJECT

	QSqlQuery *m_query;
	QString m_databasePath;
	QSqlDatabase m_database;

	void createTables();
	void createDatabase();

public:
	explicit DatabaseManager(QObject *parent = nullptr);
	~DatabaseManager();

	QSqlQuery *query() const;
};

#endif  // DATABASEMANAGER_H
