#include "tagdata.h"

TagData::TagData() {}

void TagData::imageForTagMP3(const QString& trackURL, QImage& img) {
  TagLib::MPEG::File file(trackURL.toStdString().data());
  TagLib::ID3v2::Tag* tag = file.ID3v2Tag();

  TagLib::ID3v2::FrameList l = tag->frameList("APIC");

  if (l.isEmpty())
    return;

  TagLib::ID3v2::AttachedPictureFrame* f =
      static_cast<TagLib::ID3v2::AttachedPictureFrame*>(l.front());

  img.loadFromData((const uchar*)f->picture().data(), f->picture().size());
}

void TagData::imageForTagMP4(const QString& trackURL, QImage& img) {
  TagLib::MP4::File file(trackURL.toStdString().data());
  TagLib::MP4::Tag* tag = file.tag();

  if (tag->isEmpty())
    return;

  TagLib::MP4::ItemListMap itemsListMap = tag->itemListMap();
  TagLib::MP4::Item coverItem = itemsListMap["covr"];
  TagLib::MP4::CoverArtList coverArtList = coverItem.toCoverArtList();

  if (coverArtList.isEmpty())
    return;

  TagLib::MP4::CoverArt coverArt = coverArtList.front();

  img.loadFromData(
      (const uchar*)coverArt.data().data(), coverArt.data().size());
}

void TagData::imageForTagFLAC(const QString& TrackURL, QImage& img) {
  TagLib::FLAC::File file(TrackURL.toStdString().data());
  const TagLib::List<TagLib::FLAC::Picture*>& picList = file.pictureList();

  if (picList.isEmpty())
    return;

  TagLib::FLAC::Picture* coverArt = picList[0];

  img.loadFromData(
      (const uchar*)coverArt->data().data(), coverArt->data().size());
}

void TagData::imageForTagOGG(const QString& TrackURL, QImage& img) {
  TagLib::Ogg::Vorbis::File file(TrackURL.toStdString().data());
  auto tag = file.tag();
  const TagLib::List<TagLib::FLAC::Picture*>& picList = tag->pictureList();

  if (picList.isEmpty())
    return;

  TagLib::FLAC::Picture* coverArt = picList[0];

  img.loadFromData(
      (const uchar*)coverArt->data().data(), coverArt->data().size());
}

void TagData::imageForTagWAV(const QString& TrackURL, QImage& img) {
  TagLib::RIFF::WAV::File file(TrackURL.toStdString().data());
  TagLib::ID3v2::Tag* tag = file.ID3v2Tag();

  TagLib::ID3v2::FrameList l = tag->frameList("APIC");

  if (l.isEmpty())
    return;

  TagLib::ID3v2::AttachedPictureFrame* f =
      static_cast<TagLib::ID3v2::AttachedPictureFrame*>(l.front());

  img.loadFromData((const uchar*)f->picture().data(), f->picture().size());
}

bool TagData::parse(const QString& path) {
  QFileInfo info(path);
  TagLib::FileRef f(path.toStdString().data());

  TagLib::Tag* tag = f.tag();
  if (!tag)
    return false;

  auto map = f.file()->properties();

  title = TStringToQString(tag->title()).trimmed();
  album = TStringToQString(tag->album()).trimmed();
  artist = TStringToQString(tag->artist()).trimmed();
  genre = TStringToQString(tag->genre()).trimmed();
  year = tag->year();
  track = tag->track();
  albumArtist = getValue("ALBUMARTIST", map);

  auto cdnumber = getValue("DISCNUMBER", map);
  if (cdnumber.contains("/"))
    cdnumber = cdnumber.split("/").first();

  disc = cdnumber.toInt();

  if (album.isEmpty())
    album = "Unknown";
  if (artist.isEmpty())
    artist = "Unknown";

  if (title.isEmpty())
    title = info.completeBaseName();
  if (albumArtist.isEmpty())
    albumArtist = artist;

  return true;
}

void TagData::getArtwork(const QString& path, QImage& image) {
  auto suffix = QFileInfo(path).suffix();

  if (suffix == "mp3")
    imageForTagMP3(path, image);
  else if (suffix == "flac")
    imageForTagFLAC(path, image);
  else if (suffix == "m4a")
    imageForTagMP4(path, image);
  else if (suffix == "ogg")
    imageForTagOGG(path, image);
  else if (suffix == "wav")
    imageForTagWAV(path, image);
}

const QString TagData::getValue(
    const std::string& key,
    const TagLib::PropertyMap& map) {
  if (map.find(key) != map.end()) {
    auto data = map[key];
    if (data.size())
      return TStringToQString(data.front()).trimmed();
  }

  return QString();
}
