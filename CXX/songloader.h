#ifndef SONGLOADER_H
#define SONGLOADER_H

#include "loader.h"

class SongLoader : public Loader
{
	Q_OBJECT
public:
	explicit SongLoader(QObject *parent = nullptr);

	// Loader interface
public:
	void load();
};

#endif  // SONGLOADER_H
