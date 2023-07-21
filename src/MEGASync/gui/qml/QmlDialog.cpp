#include "QmlDialog.h"
#include "MegaApplication.h"
#include "mega/types.h"

#include <QEvent>
#include <QScreen>

QmlDialog::QmlDialog(QWindow *parent)
    : QQuickWindow(parent)
    , mLoggingIn(false)
    , mCloseClicked(false)
{
    setFlags(flags() | Qt::Dialog);
    setIcon(QIcon(QString::fromUtf8("://images/app_ico.ico")));
}

QmlDialog::~QmlDialog()
{
}

bool QmlDialog::getLoggingIn() const
{
    return mLoggingIn;
}

void QmlDialog::setLoggingIn(bool value)
{
    if(mLoggingIn != value)
    {
        mLoggingIn = value;
        emit loggingInChanged();
    }
}

void QmlDialog::forceClose()
{
    setLoggingIn(false);
    if(!close())
    {
        hide();
    }
}

bool QmlDialog::event(QEvent *evnt)
{
    if(evnt->type() == QEvent::Close)
    {
        if(mLoggingIn)
        {
            emit closingButLoggingIn();
            return true;
        }
        else if(mega::NOTLOGGEDIN == MegaSyncApp->getMegaApi()->isLoggedIn()
               || mega::EPHEMERALACCOUNT == MegaSyncApp->getMegaApi()->isLoggedIn())
        {
            hide();
            return true;
        }
        else
        {
            emit finished();
        }
    }
    return QQuickWindow::event(evnt);
}
