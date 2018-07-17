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

	virtual void clicked(const int &index) {}

	virtual void actionTriggered(const int &type, const int &index,
								 const QVariant &extra = QVariant())
	{
	}
};

#endif  // ARTISTLOADER_H
