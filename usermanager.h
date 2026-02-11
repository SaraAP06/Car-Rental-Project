#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>

class userManager
{
public:
    static bool login(QString username, QString password);

    static bool registerUser(QString username, QString password);
};

#endif // USERMANAGER_H
