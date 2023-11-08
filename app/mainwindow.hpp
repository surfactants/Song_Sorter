#pragma once

#include <QMainWindow>

#include "start_page.hpp"
#include "results.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Start_Page* start_page { nullptr };
    Results* results { nullptr };

private slots:
    void startSort(const QString& source, const QString& destination);
    void openStartPage();

signals:

};
