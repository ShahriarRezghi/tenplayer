#include "mediaplayer.h"
#include <QTime>

MediaPlayer::MediaPlayer(QObject *parent) : QMediaPlayer(parent)
{
	read();
	connect(this, &MediaPlayer::positionChanged, this, &MediaPlayer::positionStringChanged);
	connect(this, &MediaPlayer::durationChanged, this, &MediaPlayer::durationStringChanged);
}

MediaPlayer::~MediaPlayer() { save(); }

QString MediaPlayer::posToTime(const qint64 &time) const
{
	QTime t = QTime::fromMSecsSinceStartOfDay(time);
	QString ts;

	if (t.hour() > 0)
		ts = t.toString("h:mm:ss");
	else
		ts = t.toString("mm:ss");

	if (ts.isEmpty()) ts = "00:00";

	return ts;
}

void MediaPlayer::save()
{
	QSettings S;
	S.beginGroup("Player");
	S.setValue("volume", m_realVolume);
	S.endGroup();
}

void MediaPlayer::read()
{
	QSettings S;
	S.beginGroup("Player");
	setRealVolume(S.value("volume", 100).toInt());
	S.endGroup();
}

int MediaPlayer::realVolume() const { return m_realVolume; }

QString MediaPlayer::durationString() const
{
	return posToTime(duration());
}

QString MediaPlayer::positionString() const
{
	return posToTime(position());
}

void MediaPlayer::setRealVolume(int realVolume)
{
	if (m_realVolume == realVolume) return;

	m_realVolume = realVolume;
	emit realVolumeChanged(m_realVolume);

	auto value = QAudio::convertVolume(realVolume / qreal(100.0),
									   QAudio::LogarithmicVolumeScale,
									   QAudio::LinearVolumeScale);

	setVolume(qRound(value * 100));
	save();
}
