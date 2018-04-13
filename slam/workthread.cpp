#include "workthread.h"
#include <QDebug>


workthread::workthread(QThread *parent) : QThread(parent)
{

}

workthread::workthread(SlamMainWindow *wmain)
{
    m_winmain = wmain;
}
workthread::~workthread()
{
    quit();
}

void workthread::run()
{

    while(1)
    {

        QThread::msleep(1000);
    }


}
void workthread::recvsemquit()
{
    this->terminate();
    this->wait();
}
