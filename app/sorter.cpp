#include "sorter.hpp"

#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>
#include <QtCore>

#include <taglib/fileref.h>

#include "color.hpp"

Sorter::Sorter(const QString& source, const QString& destination, QObject *parent)
    : QObject { parent }
    , source { source }
    , destination { destination }
{}

void Sorter::operate()
{
    readDirectory(source);
    emit done();
}

void Sorter::readDirectory(const QString& path)
{
    QDirIterator it(path);
    while (it.hasNext()) {
        QFileInfo* file = new QFileInfo(it.next());
        if (path.contains(file->absoluteFilePath())) {
            continue;
        }
        const QString& filename = file->absoluteFilePath();
        if (file->isDir()) {
            readDirectory(filename);
        }
        else {
            if (checkFile(*file)) {
                const QString& error = moveSong(file);
                if (error.length() != 0) {
                    emit output(error, Color::ERR);
                }
            }
            else {
                emit output ("DETECTED INCOMPATIBLE FILE TYPE AT " + filename, Color::ERR);
            }
        }
    }
    if(QDir(path).entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries).count() == 0) {
        QDir(path).removeRecursively();
    }
}

bool Sorter::checkFile(const QFileInfo& file_info)
{
    const QStringList extensions = {
        "mp3",
        "ogg",
        "flac",
        "wav",
        "mp4",
        "m4a",
        "aif",
        "aiff"
    };
    return extensions.contains(file_info.suffix(), Qt::CaseInsensitive);
}

QString Sorter::moveSong(QFileInfo* file_info)
{
    QString error;
    const QString& path = file_info->absoluteFilePath();
    // construct taglib object
    TagLib::FileRef* f = new TagLib::FileRef(path.toStdWString().c_str());
    TagLib::Tag* tag = f->tag();

    // read artist, album, and title to rename/move the file
    QString artist = sanitize(QString::fromStdWString(tag->artist().toWString()));
    const bool artist_check = (artist.size() > 0);

    QString album = sanitize(QString::fromStdWString(tag->album().toWString()));
    const bool album_check = (album.size() > 0);

    QString title = sanitize(QString::fromStdWString(tag->title().toWString()));
    const bool title_check = (title.size() > 0);

    const bool valid = (artist_check && album_check && title_check);

    const QString dest_dir(destination + "/" + artist + "/" + album);

    QDir dir(dest_dir);

    QString filename = dest_dir + "/" + sanitize(title) + "." + file_info->suffix();
    delete f;
    delete file_info;

    if (!valid) {
        error = "FILE LOCATED AT '" + path + "' IS MISSING: ";
        if (!artist_check) {
            error += "ARTIST ";
        }
        if (!album_check) {
            error += "ALBUM ";
        }
        if (!title_check) {
            error += "TITLE ";
        }
        return error;
    }

    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            emit output("FAILED TO CREATE DIRECTORY " + dir.absolutePath(), Color::ERR);
        }
    }

    QFile file(path);
    if (!file.rename(filename)) {
        error = "FAILED TO MOVE " + path;
    }
    return error;
}

QString Sorter::sanitize(QString str)
{
    const qsizetype n = str.size();
    for (qsizetype i = 0; i < n; i++) {
        if(str[i] == '\\'
        || str[i] == '/'
        || str[i] == ':'
        || str[i] == '*'
        || str[i] == '?'
        || str[i] == '"'
        || str[i] == '<'
        || str[i] == '>'
        || str[i] == '|'){
            str[i] = '-';
        }
    }
    return str;
}

Sorter_Controller::Sorter_Controller(const QString& source, const QString& destination, QObject* parent)
    : QObject { parent }
{
    worker = new Sorter(source, destination);
    worker->moveToThread(&thread);
    connect(this, &Sorter_Controller::run, worker, &Sorter::operate);
    connect(worker, &Sorter::output, this, &Sorter_Controller::listen);
    connect(worker, &Sorter::done, this, &Sorter_Controller::finish);

    thread.start();
}

void Sorter_Controller::start()
{
    emit run();
}

void Sorter_Controller::listen(const QString& msg, const QColor& color)
{
    emit output(msg, color);
}

void Sorter_Controller::finish()
{
    thread.quit();
    worker->deleteLater();
    emit output("<br>operation complete!", Color::COMPLETE);
}
