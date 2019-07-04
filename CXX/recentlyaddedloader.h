#ifndef RECENTLYADDEDLOADER_H
#define RECENTLYADDEDLOADER_H

#include "loader.h"

class RecentlyAddedLoader : public Loader
{
    Q_OBJECT

public:
    explicit RecentlyAddedLoader(QObject* parent = nullptr);

public:
    void load();
    virtual void clicked(const int& index);
    virtual void actionTriggered(const int& type, const int& index,
                                 const QVariant& extra = QVariant());
};

#endif  // RECENTLYADDEDLOADER_H
