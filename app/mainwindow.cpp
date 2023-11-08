#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    openStartPage();
}

MainWindow::~MainWindow()
{
    if (start_page) {
        start_page->deleteLater();
    }
    else if (results) {
        results->deleteLater();
    }
}

void MainWindow::openStartPage()
{
    if (results) {
        results->deleteLater();
    }
    start_page = new Start_Page();
    connect(start_page, &Start_Page::confirmed,
            this, &MainWindow::startSort);
    setCentralWidget(start_page);
}

void MainWindow::startSort(const QString& source, const QString& destination)
{
    if (start_page) {
        start_page->deleteLater();
    }
    showMaximized();
    results = new Results(source, destination);
    setCentralWidget(results);
}
