//
// Created by nyood on 05.07.2022.
//

#ifndef CONCENTRIC_CIRCLE_SHAPMASK_H
#define CONCENTRIC_CIRCLE_SHAPMASK_H


#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "DrawingSettings.h"

class ShapeMask
//        : public sf::Drawable
{
public:

    using container_type = std::vector<sf::Vector2f>;
    using size_type = typename container_type::size_type;
    using marker_ptr = std::shared_ptr<sf::CircleShape>;

public:
    ShapeMask(const sf::Shape& shape);
    ShapeMask(const container_type& value = {{0,0}});
public:
    size_type left() const;
    size_type right() const;

    void left(const size_type& value);
    void right(const size_type& value);

    void addPoints(const container_type& value);
    void excludePoints(const sf::CircleShape& shape);

    void clear();

    virtual std::size_t getPointCount() const;
    virtual container_type getPoints(const size_type& left, const size_type& right) const;
    virtual sf::Vector2f getPoint(std::size_t index) const;

    void setPosition(const sf::Vector2f& vec);
    ShapeMask& operator += (const ShapeMask& mask);
    ShapeMask& operator += (const container_type& container);

public:
    virtual void draw(sf::RenderTarget& target, const sf::Shape& marker, const DrawingSettings& settings);

protected:
    sf::Shape& makeDot(const sf::Shape& marker, const size_type& index);

private:

    size_type m_left;
    size_type m_right;
    container_type m_points;

    bool toRight;
};


#endif //CONCENTRIC_CIRCLE_SHAPMASK_H
