#include "start_page.hpp"

#include <QCoreApplication>

const QString Start_Page::null_dir_label("No directory selected...");

Start_Page::Start_Page(QWidget *parent)
    : QWidget{ parent }
{
    // CREATE LAYOUTS
    main_layout = new QVBoxLayout(this);

    dir_layout = new QGridLayout();
    main_layout->addLayout(dir_layout);

    control_layout = new QHBoxLayout();
    main_layout->addLayout(control_layout);

    // DIR LAYOUT
    int row = 0;

    // SOURCE
    source_label = new QLabel("Source:");
    dir_layout->addWidget(source_label, row, LABEL);

    source = new QLabel(null_dir_label);
    dir_layout->addWidget(source, row, DIRECTORY);

    source_select = new QPushButton("Browse...");
    dir_layout->addWidget(source_select, row, BROWSE);
    connect(source_select, &QPushButton::clicked,
            this, &Start_Page::openSourceSelect);

    row++;

    // DESTINATION
    destination_label = new QLabel("Destination:");
    dir_layout->addWidget(destination_label, row, LABEL);

    destination = new QLabel(null_dir_label);
    dir_layout->addWidget(destination, row, DIRECTORY);

    destination_select = new QPushButton("Browse...");
    dir_layout->addWidget(destination_select, row, BROWSE);
    connect(destination_select, &QPushButton::clicked,
            this, &Start_Page::openDestinationSelect);

    row++;

    // CONFIRM
    confirm = new QPushButton("Sort");
    dir_layout->addWidget(confirm, row, BROWSE);
    connect(confirm, &QPushButton::clicked,
            this, &Start_Page::emitConfirmed);

    dir_layout->setColumnStretch(SPACE, 1);

    main_layout->addStretch();

    selectSource(null_dir_label);
    selectDestination(null_dir_label);
}

bool Start_Page::sourceExists()
{
    return QDir(source->text()).exists();
}

bool Start_Page::destinationExists()
{
    return QDir(destination->text()).exists();
}

QFileDialog* Start_Page::openDirectoryDialog()
{
    QFileDialog* dialog = new QFileDialog(nullptr, "Select Directory...");
    dialog->setFileMode(QFileDialog::Directory);
    dialog->setModal(true);
    dialog->setWindowModality(Qt::ApplicationModal);
    return dialog;
}

void Start_Page::openSourceSelect()
{
    QFileDialog* dialog = openDirectoryDialog();
    connect(dialog, &QFileDialog::fileSelected,
            this, &Start_Page::selectSource);
    if (sourceExists()) {
        dialog->setDirectory(source->text());
    }
    else if (destinationExists()) {
        dialog->setDirectory(destination->text());
    }
    else {
        dialog->setDirectory(QCoreApplication::applicationDirPath());
    }
    dialog->open();
}

void Start_Page::openDestinationSelect()
{
    QFileDialog* dialog = openDirectoryDialog();
    connect(dialog, &QFileDialog::fileSelected,
            this, &Start_Page::selectDestination);
    if (destinationExists()) {
        dialog->setDirectory(destination->text());
    }
    else if (sourceExists()) {
        dialog->setDirectory(source->text());
    }
    else {
        dialog->setDirectory(QCoreApplication::applicationDirPath());
    }
    dialog->open();
}

void Start_Page::selectSource(const QString& dir)
{
    source->setText(dir);
    confirm->setEnabled((sourceExists() && destinationExists()));
}

void Start_Page::selectDestination(const QString& dir)
{
    destination->setText(dir);
    confirm->setEnabled((sourceExists() && destinationExists()));
}

void Start_Page::emitConfirmed()
{
    emit confirmed(source->text(), destination->text());
}
