#pragma once

#include <QFileDialog>

class File_Dialog : public QFileDialog
{
    Q_OBJECT
public:
    File_Dialog();

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

