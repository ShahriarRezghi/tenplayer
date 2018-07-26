#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QDebug>
#include <QObject>
#include <QtSql>

#include "loader.h"
#include "tagdata.h"

class DatabaseManager : public QObject
{
	Q_OBJECT

	QSqlQuery *m_query;
	QString m_databasePath;
	QSqlDatabase m_database;

	void createTables();
	void createDatabase();

public:
	explicit DatabaseManager(const QString &databasePath,
							 QObject *parent = nullptr);
	~DatabaseManager();

	void import(const QSize &artworkSize, const QStringList &files);

	QSqlQuery *query() const;
	void clearTables();
};

#endif  // DATABASEMANAGER_H
