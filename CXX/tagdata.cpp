#include "tagdata.h"

TagData::TagData() {}

void TagData::imageForTagMP3(const QString &trackURL,
							 QImage &img)  // TagLib::ID3v2::Tag *tag
{
	TagLib::MPEG::File file(trackURL.toStdString().data());  // f2.ID3v2Tag()
	TagLib::ID3v2::Tag *tag = file.ID3v2Tag();

	TagLib::ID3v2::FrameList l = tag->frameList("APIC");

	if (l.isEmpty()) return;

	TagLib::ID3v2::AttachedPictureFrame *f =
		static_cast<TagLib::ID3v2::AttachedPictureFrame *>(l.front());

	img.loadFromData((const uchar *)f->picture().data(), f->picture().size());
}

void TagData::imageForTagMP4(const QString &trackURL,
							 QImage &img)  // TagLib::MP4::Tag *tag
{
	TagLib::MP4::File file(trackURL.toStdString().data());
	TagLib::MP4::Tag *tag = file.tag();

	if (tag->isEmpty()) return;

	TagLib::MP4::ItemListMap itemsListMap = tag->itemListMap();
	TagLib::MP4::Item coverItem = itemsListMap["covr"];
	TagLib::MP4::CoverArtList coverArtList = coverItem.toCoverArtList();

	if (coverArtList.isEmpty()) return;

	TagLib::MP4::CoverArt coverArt = coverArtList.front();

	img.loadFromData((const uchar *)coverArt.data().data(),
					 coverArt.data().size());
}

void TagData::imageForTagFLAC(const QString &TrackURL, QImage &img)
{
	TagLib::FLAC::File file(TrackURL.toStdString().data());
	const TagLib::List<TagLib::FLAC::Picture *> &picList = file.pictureList();

	if (picList.isEmpty()) return;

	TagLib::FLAC::Picture *coverArt = picList[0];

	img.loadFromData((const uchar *)coverArt->data().data(),
					 coverArt->data().size());
}

bool TagData::parse(const QString &path)
{
	QFileInfo info(path);

	TagLib::FileRef f(path.toStdString().data());
	TagLib::Tag *tag = f.tag();

	if (!tag) return false;

	title = TStringToQString(tag->title()).trimmed();

	if (title.isEmpty()) title = info.completeBaseName();

	album = TStringToQString(tag->album()).trimmed();
	artist = TStringToQString(tag->artist()).trimmed();
	genre = TStringToQString(tag->genre()).trimmed();
	year = tag->year();
	track = tag->track();

	if (album.isEmpty()) album = "Unknown";
	if (artist.isEmpty()) artist = "Unknown";

	if (info.suffix() == "mp3")
	{
		TagLib::MPEG::File audioFile(path.toStdString().data());
		TagLib::ID3v2::Tag *tag = audioFile.ID3v2Tag(true);

		TagLib::ByteVector id = "TPE2";
		if (!tag->frameList(id).isEmpty())
			albumArtist =
				TStringToQString(tag->frameList(id).front()->toString())
					.trimmed();
	}
	else if (info.suffix() == "m4a")
	{
		TagLib::MP4::File audioFile(path.toStdString().data());
		TagLib::MP4::Tag *tag = audioFile.tag();

		if (tag != nullptr)
		{
			TagLib::MP4::ItemListMap map = tag->itemListMap();
			TagLib::StringList list = map["aART"].toStringList();

			if (list.size() != 0)
				albumArtist = TStringToQString(list.front()).trimmed();
		}
	}

	if (albumArtist.isEmpty()) albumArtist = artist;
	return true;
}

void TagData::getArtwork(const QString &path, QImage &image)
{
	QFileInfo info(path);

	if (info.suffix() == "mp3")
		imageForTagMP3(path, image);
	else if (info.suffix() == "flac")
		imageForTagFLAC(path, image);
	else if (info.suffix() == "m4a")
		imageForTagMP4(path, image);
}
