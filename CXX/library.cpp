#include "mainmanager.h"

void MainManager::clearAll()
{
	for (auto loader : Loaders) loader->clear();
}

void MainManager::eraseAll()
{
	emit clearAllSignal();

	QDir(QString(Loader::ArtworkPath)
			 .remove(Loader::ArtworkPath.length() - 1, 1))
		.removeRecursively();

	QDir().mkdir(Loader::ArtworkPath);
	DatabaseMgr->clearTables();
}

void MainManager::load()
{
	Status->setLoading(true);
	Status->setStatus("Erasing All");

	eraseAll();

	Status->setTop(0);
	Status->setValue(0);
	Status->setStatus("Listing Files");

	QStringList files = PathMgr->getAllFiles();
	PathMgr->save();

	Status->setStatus("Importing To Database");

	DatabaseMgr->import(ArtworkSize, files);
	Status->setLoading(false);

	refresh();
}

void MainManager::refresh()
{
	Status->setRefreshing(true);

	Status->setTop(0);
	Status->setValue(0);
	Status->setStatus("Refreshing");

	Status->setFile("");

	for (auto loader : Loaders) loader->load();
	Status->setRefreshing(false);
}

void MainManager::loadDir(const QString &dir)
{
	Status->setLoading(true);
	emit clearAllSignal();

	Status->setTop(0);
	Status->setValue(0);
	Status->setStatus("Listing Files");

	PathMgr->addDir(dir);
	PathMgr->save();

	QStringList files = PathMgr->filesInDirectory(dir);
	Status->setStatus("Importing To Database");

	DatabaseMgr->import(ArtworkSize, files);
	Status->setLoading(false);
	refresh();
}

void MainManager::loadFiles(const QStringList &files)
{
	Status->setLoading(true);
	emit clearAllSignal();

	Status->setTop(0);
	Status->setValue(0);
	Status->setStatus("Listing Files");

	QStringList fileList = PathMgr->addFiles(files);
	PathMgr->save();

	Status->setStatus("Importing To Database");

	DatabaseMgr->import(ArtworkSize, fileList);
	Status->setLoading(false);
	refresh();
}
