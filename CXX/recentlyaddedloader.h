#ifndef RECENTLYADDEDLOADER_H
#define RECENTLYADDEDLOADER_H

#include "loader.h"

class RecentlyAddedLoader : public Loader
{
	Q_OBJECT
public:
	explicit RecentlyAddedLoader(QObject *parent = nullptr);

	// Loader interface
public:
	void load();
};

#endif  // RECENTLYADDEDLOADER_H
