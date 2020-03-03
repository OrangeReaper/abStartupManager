#ifndef ABFUNCTIONS_H
#define ABFUNCTIONS_H

#include <QString>

class abFunctions
{
public:
    abFunctions();
    static void waitFor(int secs);
    static bool fileExists(QString path);
    static bool mkdir(QString path);
};

#endif // ABFUNCTIONS_H
