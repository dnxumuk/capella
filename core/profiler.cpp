#include "profiler.h"

Profiler::Profiler()
{
    message = QString("Profiler.");
}

Profiler::Profiler(QString &message)
{
     this->message = message;
}

void Profiler::start()
{
    startTick = clock();
}

void Profiler::finish()
{
    finishTick = clock();
    _getResults();
}

void Profiler::_getResults()
{
    double timeInSec = (double)(finishTick - startTick) / CLOCKS_PER_SEC;
    double fps       = (double) 1/timeInSec;
    if ( timeInSec < 1.0)
        qDebug() << "[" << message << "]. Time elapsed: " << timeInSec*1000 << " ms.  FPS: " << fps;
    else
        qDebug() << "[" << message << "]. Time elapsed: " << timeInSec      << " sec. FPS: " << fps;
}

void Profiler::changeMessage(QString &newMessage)
{
    message = newMessage;
}

void Profiler::changeMessage(QString newMessage)
{
    message = newMessage;
}
