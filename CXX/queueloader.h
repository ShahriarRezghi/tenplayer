#ifndef QUEUELOADER_H
#define QUEUELOADER_H

#include <loader.h>
#include <QMediaPlayer>

class QueueLoader : public Loader
{
	Q_OBJECT

public:
	explicit QueueLoader(QObject *parent = nullptr);
};

#endif  // QUEUELOADER_H
