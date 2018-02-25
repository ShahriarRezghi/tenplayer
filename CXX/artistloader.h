#ifndef ARTISTLOADER_H
#define ARTISTLOADER_H

#include "loader.h"

class ArtistLoader : public Loader
{
	Q_OBJECT

	QList<QStandardItem *> getSubItems(QStandardItem *item);

public:
	explicit ArtistLoader(QObject *parent = nullptr);

	// Loader interface
public:
	void load();
};

#endif  // ARTISTLOADER_H
