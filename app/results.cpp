#include "results.hpp"

#include "color.hpp"

Results::Results(const QString& source, const QString& destination, QWidget* parent)
    : QTextBrowser { parent }
{
    setStyleSheet(QString("background-color:%1").arg(Color::BACKGROUND.name()));
    displayMessage("Running...<br>", Color::STANDARD);
    sorter = new Sorter_Controller(source, destination);
    connect(sorter, &Sorter_Controller::output, this, &Results::displayMessage);
    sorter->start();
}

void Results::displayMessage(const QString& str, const QColor& color)
{
    QString html(QString("<span style=\"color:%1\">").arg(color.name()) + str + "</span>");
    append(html);
}
