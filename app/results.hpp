#pragma once

#include <QTextBrowser>

#include <QColor>
#include <QString>

#include "sorter.hpp"

/// RESULTS ///
/// \brief Central widget for active sorting operations.
/// Contains the sorter itself and receives output signals from it.
///
class Results : public QTextBrowser
{
    Q_OBJECT
public:
    explicit Results(const QString& source, const QString& destination, QWidget* parent = nullptr);

public slots:
    void displayMessage(const QString& str, const QColor& color);

private:
    Sorter_Controller* sorter { nullptr };
};

