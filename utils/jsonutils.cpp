#include "jsonutils.h"

#include <QJsonObject>
#include <QJsonArray>

template<>
QJsonDocument getJson<QJsonDocument>(const QJsonDocument &document)
{
    return document;
}

template<>
QJsonObject getJson<QJsonObject>(const QJsonDocument &document)
{
    if(!document.isObject())
        throw std::runtime_error("JSON document does not contain an object!");

    return document.object();
}

template<>
QJsonArray getJson<QJsonArray>(const QJsonDocument &document)
{
    if(!document.isArray())
        throw std::runtime_error("JSON document does not contain an object!");

    return document.array();
}
