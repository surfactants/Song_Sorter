#pragma once

#include <QWidget>

#include <QLabel>
#include <QPushButton>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QFileDialog>

/// START PAGE ///
/// \brief Initial central widget for selecting source and destination directories.
///
class Start_Page : public QWidget
{
    Q_OBJECT
public:
    explicit Start_Page(QWidget *parent = nullptr);

    QVBoxLayout* main_layout { nullptr };

    QGridLayout* dir_layout { nullptr };
    enum Dir_Column {
        LABEL = 0,
        DIRECTORY = 1,
        BROWSE = 2,
        SPACE = 3
    };

    QLabel* source_label { nullptr };
    QLabel* source { nullptr };
    QPushButton* source_select { nullptr };

    QLabel* destination_label { nullptr };
    QLabel* destination { nullptr };
    QPushButton* destination_select { nullptr };

    QHBoxLayout* control_layout { nullptr };

    QPushButton* confirm { nullptr };

private:
    const static QString null_dir_label;

    bool sourceExists();
    bool destinationExists();

    QFileDialog* openDirectoryDialog();

private slots:
    void openSourceSelect();
    void openDestinationSelect();
    void selectSource(const QString& dir);
    void selectDestination(const QString& dir);
    void emitConfirmed();

signals:
    void confirmed(const QString&, const QString&);
};

