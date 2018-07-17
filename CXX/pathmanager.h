#ifndef PATHMANAGER_H
#define PATHMANAGER_H

#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QObject>
#include <QRegExp>
#include <QStringList>
#include <QUrl>

class PathManager : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QStringList dirs READ dirs WRITE setDirs NOTIFY dirsChanged)
	Q_PROPERTY(QStringList files READ files WRITE setFiles NOTIFY filesChanged)

	QStringList m_dirs;
	QStringList m_files;

	QStringList m_sft;

	void load();
	QString urlToPath(const QString &url);

public:
	explicit PathManager(QObject *parent = nullptr);
	~PathManager();

	void save();

	QStringList dirs() const;
	QStringList files() const;

	QStringList getAllFiles();
	void filterFiles(QStringList &files);
	QStringList filesInDirectory(const QString &path);

public slots:
	void setDirs(const QStringList &dirs);
	void setFiles(const QStringList &files);

	void addDir(QString dir);
	QStringList addFiles(QStringList files);

	void removeDir(const int &index);
	void removeFile(const int &index);

signals:
	void dirsChanged(const QStringList &dirs);
	void filesChanged(const QStringList &files);
};

#endif  // PATHMANAGER_H
