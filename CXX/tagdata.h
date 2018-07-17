#ifndef TAGDATA_H
#define TAGDATA_H

// TagLib Headers
#include <taglib/attachedpictureframe.h>
#include <taglib/fileref.h>
#include <taglib/flacfile.h>
#include <taglib/flacpicture.h>
#include <taglib/id3v2tag.h>
#include <taglib/mp4coverart.h>
#include <taglib/mp4file.h>
#include <taglib/mp4item.h>
#include <taglib/mp4tag.h>
#include <taglib/mpegfile.h>
#include <taglib/tag.h>
#include <taglib/taglib.h>
#include <taglib/tpropertymap.h>
#include <taglib/tpropertymap.h>
#include <taglib/tstring.h>

#include <QDebug>
#include <QFileInfo>
#include <QImage>
#include <QString>

struct TagData
{
public:
	QString title;
	QString artist;
	QString album;
	QString genre;
	QString albumArtist;
	int track;
	int year;

	TagData(const QString &path);

	static void imageForTagMP3(const QString &trackURL, QImage &img);
	static void imageForTagMP4(const QString &trackURL, QImage &img);
	static void imageForTagFLAC(const QString &TrackURL, QImage &img);

	void parse(const QString &path);
	void getArtwork(const QString &path, QImage &image);
};

#endif  // TAGDATA_H
