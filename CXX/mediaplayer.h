#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QMediaPlayer>
#include <QSettings>

class MediaPlayer : public QMediaPlayer
{
	Q_OBJECT

	Q_PROPERTY(int realVolume READ realVolume WRITE setRealVolume NOTIFY
				   realVolumeChanged)

	int m_realVolume;

private slots:
	void save();
	void read();

public:
	MediaPlayer(QObject *parent = nullptr);
	~MediaPlayer();

	int realVolume() const;

public slots:
	void setRealVolume(int realVolume);

signals:
	void realVolumeChanged(int realVolume);
};

#endif  // MEDIAPLAYER_H
