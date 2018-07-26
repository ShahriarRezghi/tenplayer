#include "pathmanager.h"

#include <QSettings>

void PathManager::save()
{
	QSettings S;

	S.beginGroup("Paths");

	S.setValue("Files", m_files);
	S.setValue("Directories", m_dirs);

	S.endGroup();
}

void PathManager::load()
{
	QSettings S;

	S.beginGroup("Paths");

	m_files = S.value("Files", QStringList()).toStringList();
	m_dirs = S.value("Directories", QStringList()).toStringList();

	S.endGroup();
}

QString PathManager::urlToPath(const QString &url)
{
	return QUrl(url).toLocalFile();
}

void PathManager::filterFiles(QStringList &files)
{
	QStringList list;

	for (const QString &S : m_sft)
	{
		QRegExp rx(S);
		rx.setPatternSyntax(QRegExp::Wildcard);
		list << files.filter(rx);
	}

	list.removeDuplicates();
	files = list;
}

PathManager::PathManager(QObject *parent) : QObject(parent)
{
	m_sft << "*.mp3"
		  << "*.m4a"
		  << "*.ogg"
		  << "*.flac";

	load();
}

PathManager::~PathManager() { save(); }
void PathManager::setFiles(const QStringList &files)
{
	if (m_files == files) return;

	m_files = files;
	emit filesChanged(m_files);
}

void PathManager::setDirs(const QStringList &dirs)
{
	if (m_dirs == dirs) return;

	m_dirs = dirs;
	emit dirsChanged(m_dirs);
}

QStringList PathManager::filesInDirectory(const QString &path)
{
	QStringList fileList;

	QDir selectedDir(path);
	selectedDir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

	selectedDir.setNameFilters(m_sft);

	QDirIterator it(selectedDir, QDirIterator::Subdirectories);
	while (it.hasNext()) fileList << it.next();

	return fileList;
}

QStringList PathManager::getAllFiles()
{
	QStringList files;
	for (const QString &dir : m_dirs) files << filesInDirectory(dir);

	files << m_files;
	files.removeDuplicates();  // TODO too much?
	return files;
}

QStringList PathManager::addFiles(QStringList files)
{
	for (QString &file : files) file = urlToPath(file);
	filterFiles(files);

	for (const QString &S : m_files)
	{
		int index = files.indexOf(S);
		if (index != -1) files.removeAt(index);
	}

	if (files.count() == 0) return files;

	m_files << files;
	emit filesChanged(m_files);

	return files;
}

void PathManager::addDir(QString dir)
{
	dir = urlToPath(dir);
	if (m_dirs.indexOf(dir) != -1) return;

	m_dirs << dir;
	emit dirsChanged(m_dirs);
}

void PathManager::removeFile(const int &index)
{
	m_files.removeAt(index);
	emit filesChanged(m_files);
}

void PathManager::removeDir(const int &index)
{
	m_dirs.removeAt(index);

	emit dirsChanged(m_dirs);
}

QStringList PathManager::dirs() const { return m_dirs; }
QStringList PathManager::files() const { return m_files; }
