#include "query.h"

Query::Query()
{

}

const QString Query::autorizationUrl = "https://accounts.spotify.com/authorize";
const QString Query::accessTokenUrl = "https://accounts.spotify.com/api/token";
const QString Query::searchQueryUrl = "https://api.spotify.com/v1/search?q=";
const QString Query::userInfoUrl = "https://api.spotify.com/v1/me";
QString Query::userInfo(){
    return "";
}
QString Query::trackQuery(QString id, QString market)
{
    return  "https://api.spotify.com/v1/tracks/"+id+"?market="+market;
}
QString Query::trackSeach(QStringList therms,QString market)
{

    QString url = Query::searchQueryUrl;
    QStringList splitted = therms;
    bool first = true;
    for(QString str : splitted)
    {
        if(first){
            url.append(str);
            first = false;
        }
        else{
            url.append("%20");
            url.append(str);
        }


    }

    url.append("&");
    QString type = "type=track&market="+market;
    url.append(type);
    url.append("&limit=50");

    return url;
}

