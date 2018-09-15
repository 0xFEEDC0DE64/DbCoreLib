#pragma once

#include <array>
#include <assert.h>
#include <algorithm>

template<typename T, unsigned int width, unsigned int height>
class FixedSizeMatrix
{
public:
    explicit FixedSizeMatrix();
    FixedSizeMatrix(const std::array<std::array<T, width>, height>& data);
    FixedSizeMatrix(const FixedSizeMatrix<T, width, height> &other);

    auto& operator=(const FixedSizeMatrix<T, width, height>& other);
    auto& operator=(const std::array<std::array<T, width>, height>& data);

    [[nodiscard]] auto operator==(const FixedSizeMatrix<T, width, height>& other) const;
    [[nodiscard]] auto operator!=(const FixedSizeMatrix<T, width, height>& other) const;

    [[nodiscard]] auto& operator()(unsigned int x, unsigned int y);
    [[nodiscard]] const auto& operator()(unsigned int x, unsigned int y) const;

    void rotateLeft();
    void rotateRight();
    void rotate180();
    void mirrorHorizontally();
    void mirrorVertically();

    [[nodiscard]] auto asRotatedLeft() const;
    [[nodiscard]] auto asRotatedRight() const;
    [[nodiscard]] auto asRotated180() const;
    [[nodiscard]] auto asMirroredHorizontally() const;
    [[nodiscard]] auto asMirroredVertically() const;

private:
    std::array<std::array<T, width>, height> m_data;
};

template<typename T, unsigned int width, unsigned int height>
FixedSizeMatrix<T, width, height>::FixedSizeMatrix() {}

template<typename T, unsigned int width, unsigned int height>
FixedSizeMatrix<T, width, height>::FixedSizeMatrix(const std::array<std::array<T, width>, height>& data) : m_data(data) {}

template<typename T, unsigned int width, unsigned int height>
FixedSizeMatrix<T, width, height>::FixedSizeMatrix(const FixedSizeMatrix<T, width, height>& other) : m_data(other.m_data) {}

template<typename T, unsigned int width, unsigned int height>
auto& FixedSizeMatrix<T, width, height>::operator=(const FixedSizeMatrix<T, width, height>& other)
{
    if(&other != this)
        m_data = other.m_data;
    return *this;
}

template<typename T, unsigned int width, unsigned int height>
auto& FixedSizeMatrix<T, width, height>::operator=(const std::array<std::array<T, width>, height>& data)
{
    m_data = data;
    return *this;
}

template<typename T, unsigned int width, unsigned int height>
auto FixedSizeMatrix<T, width, height>::operator==(const FixedSizeMatrix<T, width, height>& other) const
{
    return m_data == other.m_data;
}

template<typename T, unsigned int width, unsigned int height>
auto FixedSizeMatrix<T, width, height>::operator!=(const FixedSizeMatrix<T, width, height>& other) const
{
    return m_data != other.m_data;
}

template<typename T, unsigned int width, unsigned int height>
auto& FixedSizeMatrix<T, width, height>::operator()(unsigned int x, unsigned int y)
{
    assert(x < width);
    assert(y < height);
    return m_data[y][x];
}

template<typename T, unsigned int width, unsigned int height>
const auto& FixedSizeMatrix<T, width, height>::operator()(unsigned int x, unsigned int y) const
{
    assert(x < width);
    assert(y < height);
    return m_data[y][x];
}

template<typename T, unsigned int width, unsigned int height>
void FixedSizeMatrix<T, width, height>::rotateLeft()
{
    static_assert(width == height, "Rotating in place only works when width matches height");

    //TODO
}

template<typename T, unsigned int width, unsigned int height>
void FixedSizeMatrix<T, width, height>::rotateRight()
{
    static_assert(width == height, "Rotating in place only works when width matches height");

    //TODO
}

template<typename T, unsigned int width, unsigned int height>
void FixedSizeMatrix<T, width, height>::rotate180()
{
    //for(unsigned int y = 0; y < height / 2; y++)
    //    for(unsigned int x = 0; x < width; x++)
    //        std::swap(m_data[height-y-1][width-x-1], m_data[y][x]);

    mirrorHorizontally();
    mirrorVertically();
}

template<typename T, unsigned int width, unsigned int height>
void FixedSizeMatrix<T, width, height>::mirrorHorizontally()
{
    //for(unsigned int y = 0; y < height / 2; y++)
    //    for(unsigned int x = 0; x < width; x++)
    //        std::swap(m_data[height-y-1][x], m_data[y][x]);

    std::reverse(std::begin(m_data), std::end(m_data));
}

template<typename T, unsigned int width, unsigned int height>
void FixedSizeMatrix<T, width, height>::mirrorVertically()
{
    //for(unsigned int y = 0; y < height; y++)
    //    for(unsigned int x = 0; x < width / 2; x++)
    //        std::swap(m_data[y][width-x-1], m_data[y][x]);

    for(unsigned int y = 0; y < height; y++)
        std::reverse(std::begin(m_data[y]), std::end(m_data[y]));
}

template<typename T, unsigned int width, unsigned int height>
auto FixedSizeMatrix<T, width, height>::asRotatedLeft() const
{
    std::array<std::array<T, height>, width> data;

    for(unsigned int y = 0; y < height; y++)
        for(unsigned int x = 0; x < width; x++)
            data[width-x-1][y] = m_data[y][x];

    return FixedSizeMatrix<T, height, width>(data);
}

template<typename T, unsigned int width, unsigned int height>
auto FixedSizeMatrix<T, width, height>::asRotatedRight() const
{
    std::array<std::array<T, height>, width> data;

    for(unsigned int y = 0; y < height; y++)
        for(unsigned int x = 0; x < width; x++)
            data[x][height-y-1] = m_data[y][x];

    return FixedSizeMatrix<T, height, width>(data);
}

template<typename T, unsigned int width, unsigned int height>
auto FixedSizeMatrix<T, width, height>::asRotated180() const
{
    std::array<std::array<T, width>, height> data;

    for(unsigned int y = 0; y < height; y++)
        for(unsigned int x = 0; x < width; x++)
            data[height-y-1][width-x-1] = m_data[y][x];

    return FixedSizeMatrix<T, width, height>(data);
}

template<typename T, unsigned int width, unsigned int height>
auto FixedSizeMatrix<T, width, height>::asMirroredHorizontally() const
{
    std::array<std::array<T, width>, height> data;

    for(unsigned int y = 0; y < height; y++)
        for(unsigned int x = 0; x < width; x++)
            data[height-y-1][x] = m_data[y][x];

    return FixedSizeMatrix<T, width, height>(data);
}

template<typename T, unsigned int width, unsigned int height>
auto FixedSizeMatrix<T, width, height>::asMirroredVertically() const
{
    std::array<std::array<T, width>, height> data;

    for(unsigned int y = 0; y < height; y++)
        for(unsigned int x = 0; x < width; x++)
            data[y][width-x-1] = m_data[y][x];

    return FixedSizeMatrix<T, width, height>(data);
}
