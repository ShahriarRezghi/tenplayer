#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QMediaPlayer>
#include <QSettings>

class MediaPlayer : public QMediaPlayer {
  Q_OBJECT

  Q_PROPERTY(int realVolume READ realVolume WRITE setRealVolume NOTIFY
				 realVolumeChanged)

  Q_PROPERTY(QString durationString READ durationString NOTIFY durationStringChanged)
  Q_PROPERTY(QString positionString READ positionString NOTIFY positionStringChanged)

  int m_realVolume;

private slots:
  void save();
  void read();

public:
  MediaPlayer(QObject *parent = nullptr);
  ~MediaPlayer();

  QString posToTime(const qint64 &time) const;

  int realVolume() const;
  QString durationString() const;
  QString positionString() const;

public slots:
  void setRealVolume(int realVolume);

signals:
  void realVolumeChanged(int realVolume);

  void durationStringChanged();
  void positionStringChanged();
};

#endif // MEDIAPLAYER_H
