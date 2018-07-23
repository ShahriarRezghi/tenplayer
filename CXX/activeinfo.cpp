#include "activeinfo.h"

ActiveInfo::ActiveInfo(QObject *parent) : QObject(parent)
{
	setRepeatable(false);
	setShufflable(false);
}

void ActiveInfo::setTitleInfo(const QString &titleInfo)
{
	m_titleInfo = titleInfo;
}

void ActiveInfo::setAlbumInfo(const QString &albumInfo)
{
	m_albumInfo = albumInfo;
}

void ActiveInfo::setArtistInfo(const QString &artistInfo)
{
	m_artistInfo = artistInfo;
}

void ActiveInfo::setArtworkInfo(const QString &artworkInfo)
{
	m_artworkInfo = artworkInfo;
}

void ActiveInfo::setQueueRow(int queueRow) { m_queueRow = queueRow; }

int ActiveInfo::queueRow() const { return m_queueRow; }

QString ActiveInfo::titleInfo() const { return m_titleInfo; }

QString ActiveInfo::albumInfo() const { return m_albumInfo; }

QString ActiveInfo::artistInfo() const { return m_artistInfo; }

QString ActiveInfo::artworkInfo() const { return m_artworkInfo; }

bool ActiveInfo::repeatable() const { return m_repeatable; }

bool ActiveInfo::shufflable() const { return m_shufflable; }

void ActiveInfo::setRepeatable(bool repeatable)
{
	if (m_repeatable == repeatable) return;

	m_repeatable = repeatable;
	emit repeatableChanged(m_repeatable);
}

void ActiveInfo::setShufflable(bool shufflable)
{
	if (m_shufflable == shufflable) return;

	m_shufflable = shufflable;
	emit shufflableChanged(m_shufflable);
}
