#include "mediaplayer.h"

MediaPlayer::MediaPlayer(QObject *parent) : QMediaPlayer(parent) { read(); }

MediaPlayer::~MediaPlayer() { save(); }

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
