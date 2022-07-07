#ifndef CONCENTRIC_CIRCLE_LINE_H
#define CONCENTRIC_CIRCLE_LINE_H

#include <cassert>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class LineSegment
{
public:
    using size_type = std::size_t;
    using container_type = std::vector<sf::Vector2f>;
public:
    explicit LineSegment(const size_type& points = 30,
                const sf::Vector2f& left = {1.f, 1.f},
                const sf::Vector2f& right = {10.f, 1.f});

public:
    size_type length() const;
    size_type points() const;

    void points(const size_type& value);
    void left(const sf::Vector2f& value);
    void right(const sf::Vector2f& value);

    container_type dump(const size_type& from, const size_type& to) const;
private:
    size_type m_points;
    sf::Vector2f m_left;
    sf::Vector2f m_right;
};


#endif //CONCENTRIC_CIRCLE_LINE_H
