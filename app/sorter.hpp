#pragma once

#include <QObject>

#include <QFileInfo>
#include <QString>

#include <QThread>

/// SORTER ///
/// \brief Performs the sorting operation. Intended as a thread worker.
///
class Sorter : public QObject {
    Q_OBJECT

public:
    explicit Sorter(const QString& source, const QString& destination, QObject *parent = nullptr);

public slots:
    void operate();

signals:
    void output(const QString&, const QColor&);
    void done();

private:
    const QString source;
    const QString destination;

    void readDirectory(const QString& path);
    bool checkFile(const QFileInfo& path);
    QString moveSong(QFileInfo* path);
    QString sanitize(QString str);
};

/// SORTER_CONTROLLER ///
/// \brief Encapsulates and runs the file operation thread.
///
class Sorter_Controller : public QObject {
    Q_OBJECT

public:
    explicit Sorter_Controller(const QString& source, const QString& destination, QObject* parent = nullptr);

    Sorter* worker { nullptr };
    QThread thread;

    void start();

private slots:
    void listen(const QString& msg, const QColor& color);
    void finish();

signals:
    void output(const QString&, const QColor&);
    void run();
};
