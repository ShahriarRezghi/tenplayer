#ifndef ALBUMLOADER_H
#define ALBUMLOADER_H

#include <loader.h>

class AlbumLoader : public Loader
{
	Q_OBJECT

	QList<QStandardItem *> getSubItems(QStandardItem *item);

public:
	explicit AlbumLoader(QObject *parent = nullptr);

	// Loader interface
public:
	void load();
};

#endif  // ALBUMLOADER_H
