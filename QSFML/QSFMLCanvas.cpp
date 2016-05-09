#include "QSFMLCanvas.hpp"

#ifdef Q_WS_X11
    #include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif

namespace qsf
{
    QSFMLWidget::QSFMLWidget(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime)
        : QWidget(Parent),
          _initialized(false)
    {
        setAttribute(Qt::WA_PaintOnScreen);
        setAttribute(Qt::WA_OpaquePaintEvent);
        setAttribute(Qt::WA_NoSystemBackground);

        setFocusPolicy(Qt::StrongFocus);

        move(Position);
        resize(Size);

        refreshTimer.setInterval(FrameTime);
        frameClock.restart();
    }
    QSFMLWidget::~QSFMLWidget() {}
    void QSFMLWidget::showEvent(QShowEvent*)
    {
        if (!_initialized)
        {
            RenderWindow::create((sf::WindowHandle) winId());

            OnInit();

            connect(&refreshTimer, SIGNAL(timeout()), this, SLOT(repaint()));
            refreshTimer.start();
            _initialized = true;
        }
    }

    QPaintEngine* QSFMLWidget::paintEngine() const
    {
        return 0;
    }
    void QSFMLWidget::paintEvent(QPaintEvent*)
    {
        _frameTime = frameClock.restart();
        OnUpdate();
        RenderWindow::display();
    }

    void QSFMLWidget::OnInit()    {} /* TO BE DERIVED */
    void QSFMLWidget::OnUpdate()  {} /* TO BE DERIVED */

    bool QSFMLWidget::pollEvent(sf::Event& ev)
    {
        if(SfEvents.size() == 0)
            return false;

        ev = *(SfEvents.end() - 1);
        SfEvents.erase(SfEvents.end() - 1);

        return true;
    }
    void QSFMLWidget::pushEvent(sf::Event & ev)
    {
        SfEvents.push_back(ev);
    }
}
