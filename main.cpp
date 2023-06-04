





#include "mainwindow.h"
#include <QApplication>
#include "Utility.h"
#include <QPoint>
#include <QScreen>

int main(int argc, char *argv[])
{
    QPalette pal = QApplication::palette();
    pal.setColor(QPalette::Window, QColor(48, 48, 48));
    pal.setBrush(QPalette::WindowText, QBrush(QColor(Qt::gray)));
    //pal.setBrush(QPalette::HighlightedText, QBrush(QColor(Qt::yellow)));
    //pal.setColor(QPalette::Highlight, QColor(Qt::GlobalColor::black));
    QApplication::setPalette(pal);

    QApplication app(argc, argv);
    MainWindow w;
    w.showNormal();

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    QRect  screenVirtualGeometry = screen->virtualGeometry();
    qreal screenDpi = screen->physicalDotsPerInch();
    QSize screenSize = screen->size();

    w.move(w.pos().x() / 4, /*w.pos().y() / 2*/0);
    return app.exec();
}
