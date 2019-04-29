#ifndef QUERY_H
#define QUERY_H

#include <QString>
#include <QStringList>


class Query
{
public:
    Query();
    static QString userInfo();
    static QString trackQuery(QString id, QString market);
    static QString trackSeach(QStringList therms,QString market);

    static const QString autorizationUrl;
    static const QString accessTokenUrl;
    static const QString searchQueryUrl;
    static const QString userInfoUrl;
};



#endif // QUERY_H
