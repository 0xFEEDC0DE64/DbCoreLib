#pragma once

#include <QDataStream>

#include <array>

template<typename T, std::size_t L>
inline QDataStream &operator>>(QDataStream &s, std::array<T, L> &l)
{
    for(auto iter = std::begin(l); iter != std::end(l); iter++)
        s >> *iter;
    return s;
}

template<typename T, std::size_t L>
inline QDataStream &operator<<(QDataStream &s, const std::array<T, L> &l)
{
    for(auto iter = std::begin(l); iter != std::end(l); iter++)
        s << *iter;
    return s;
}
