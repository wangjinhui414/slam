#ifndef WORDTHREAD_H
#define WORDTHREAD_H

#include <QThread>
#include "memdata.h"
#include "slammainwindow.h"

class workthread : public QThread
{
    Q_OBJECT
public:
    explicit workthread(QThread *parent = nullptr);
    workthread(SlamMainWindow *wmain);

    ~workthread();
    SlamMainWindow *m_winmain;
protected:
    void run();
signals:
public slots:
    void recvsemquit();
};

#endif // WORDTHREAD_H
