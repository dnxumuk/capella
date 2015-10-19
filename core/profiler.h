#ifndef PROFILER_H
#define PROFILER_H
#include <QString>
#include <QDebug>
#include <time.h>

class Profiler
{
    private:
        QString message;
        clock_t startTick;
        clock_t finishTick;

        void    _getResults();
    public:
        Profiler();
        Profiler(QString &message);

        void start();
        void finish();
        void changeMessage(QString &newMessage);
        void changeMessage(QString newMessage);
};

#endif // PROFILER_H
