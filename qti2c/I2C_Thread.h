#ifndef I2C__THREAD_H
#define I2C__THREAD_H

#include <qthread.h>

class I2C_Thread : public QThread
{
    public:
        void run();
        QString LocalTemp;
        QString RemoteTemp;
};
#endif // I2C__THREAD_H
