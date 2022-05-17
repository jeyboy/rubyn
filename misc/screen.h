#ifndef SCREEN
#define SCREEN

#include <qapplication.h>
#include <qscreen.h>
#include <qwidget.h>

class Screen {
public:
//    QList<QScreen *> QGuiApplication::screens()
//    const QRect QDesktopWidget::screenGeometry(int screen = -1) const
//    QGuiApplication::screenAt()


    static QList<QRect> screenRects(QWidget * target) {
        QList<QScreen *> screens = QGuiApplication::screens();
        QList<QScreen *>::iterator i;
        QList<QRect> res;

        QPoint pos = target -> mapToGlobal(target -> rect().topLeft());

        for(i = screens.begin(); i != screens.end(); ++i) {
            if ((*i) -> geometry().contains(pos)) {
                res.prepend((*i) -> availableGeometry());
            } else {
                res << (*i) -> availableGeometry();
            }
        }

        return res;
    }

    static QRect screenRect(QWidget * target) {
        QPoint pos = target -> mapToGlobal(target -> rect().topLeft());
        QScreen * screen = QGuiApplication::screenAt(pos);

        if (screen)
            return screen -> availableGeometry();
        else
            return QRect();
    }

    static void screenSize(int & width, int & height) {
        QScreen * screen = QGuiApplication::primaryScreen();
        width = screen -> size().width();
        height = screen -> size().height();
    }

    static void minimizeIfNeeded(int & width, int & height, float percentage) {
        int screen_width, screen_height;
        percentage /= 100;
        screenSize(screen_width, screen_height);

        width = qMin((int)(screen_width * percentage), width);
        height = qMin((int)(screen_height * percentage), height);
    }
};

#endif // SCREEN

