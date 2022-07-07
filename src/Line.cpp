#include "Line.h"

LineSegment::LineSegment(const LineSegment::size_type &points, const sf::Vector2f &left, const sf::Vector2f &right)
:   m_points(points),
    m_left(left),
    m_right(right)
{}


LineSegment::size_type LineSegment::length() const
{
    const sf::Vector2f vec = m_right - m_left;
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

LineSegment::size_type LineSegment::points() const
{
    return m_points;
}

void LineSegment::points(const LineSegment::size_type &value)
{
    assert(value != 0);

    m_points = value;
}

void LineSegment::left(const sf::Vector2f &value)
{
    m_left = value;
}

void LineSegment::right(const sf::Vector2f &value)
{
    m_right = value;
}

// [f:t)
LineSegment::container_type
LineSegment::dump(const size_type& from, const size_type& to) const
{
    assert(to <= points() && from <= to);

    container_type container;

    float dX = (m_right.x - m_left.x) / points();
    float dY = (m_right.y - m_left.y) / points();

    for(size_type i = from; i < to; i++)
        container.push_back(sf::Vector2f {
           m_left.x + dX * i,
           m_left.y + dY * i
        });

    return container;
}
