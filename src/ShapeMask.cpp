#include "ShapeMask.h"

ShapeMask::ShapeMask(const sf::Shape &shape)
:   m_points(),
    m_left(),
    m_right(),
    toRight(true)
{
//    std::cout << "Points: " << shape.getPointCount() << std::endl;

    for(size_type i = 0; i < shape.getPointCount(); i++)
        m_points.push_back(shape.getPoint(i));

//    std::cout << "Saved points: " << getPointCount() << std::endl;
};

sf::Shape& ShapeMask::makeDot(const sf::Shape& marker, const size_type& index)
{
    sf::Shape& copy = (sf::Shape&)marker;
    copy.setPosition(getPoint(index));

    return copy;
}

ShapeMask::size_type ShapeMask::right() const
{
    return m_right;
}

ShapeMask::size_type ShapeMask::left() const
{
    return m_left;
}

sf::Vector2f ShapeMask::getPoint(std::size_t index) const
{
    assert(index < m_points.size());
    return m_points.at(index);
}

std::size_t ShapeMask::getPointCount() const
{
    return m_points.size();
}

void ShapeMask::left(const size_type &value)
{
//    assert(value <= right() && value <= getPointCount());
    m_left = value;
}

void ShapeMask::right(const size_type &value)
{
//    assert(value >= left() && value <= getPointCount());
    m_right = value;
}

void ShapeMask::setPosition(const sf::Vector2f &vec)
{
    for(size_type i = 0; i < getPointCount(); i++)
        m_points[i] += vec;
}

// Marker ~ "Печатная головка"
void ShapeMask::draw(sf::RenderTarget& target, const sf::Shape& marker, const DrawingSettings& settings)
{
    switch (settings.type())
    {
        default:
        case DrawingSettings::DRAW_NONE:
            return;

        case DrawingSettings::DRAW_CYCLIC:
            if(right() == getPointCount() && toRight)
                toRight = false;

            if(right() == left() && !toRight)
                toRight = true;

            draw(target,
                 marker,
                 { ((toRight)
                            ? DrawingSettings::DRAW_LEFT_TO_RIGHT
                            : DrawingSettings::DRAW_RIGHT_TO_LEFT), settings.step() });

            break;
        case DrawingSettings::DRAW_LEFT_TO_RIGHT:
            right((right() + settings.step()) > getPointCount()
                            ? getPointCount()
                            : right() + settings.step());

            break;
        case DrawingSettings::DRAW_RIGHT_TO_LEFT:
            right(((long long)right() - (long long)settings.step()) < left()
                            ? left()
                            : right() - settings.step());
            break;
    };

    for(size_type x = left(), y = right(); x < y; x++)
        target.draw(makeDot(marker, x));
};

ShapeMask::ShapeMask(const ShapeMask::container_type &value)
:   m_right(),
    m_left(),
    m_points(value),
    toRight(true)
{}

ShapeMask &ShapeMask::operator+=(const ShapeMask &mask)
{
    this->addPoints(mask.getPoints(0, mask.getPointCount()));

    return *this;
}

ShapeMask::container_type
ShapeMask::getPoints(const size_type& left, const size_type& right) const
{
    assert(right <= getPointCount() && left <= right);

    return container_type(m_points.begin() + left, m_points.begin() + right);
}

void ShapeMask::addPoints(const ShapeMask::container_type &value)
{
    for(size_type i = 0; i < value.size(); i++)
        m_points.push_back(value.at(i));
}

void ShapeMask::excludePoints(const sf::CircleShape &shape)
{
    auto mathPoint = [shape = shape] (const sf::Vector2f& point) -> float {
        return std::sqrt(
                (point.x - shape.getGlobalBounds().width/2.f) * (point.x - shape.getGlobalBounds().width/2.f)
                + (point.y - shape.getGlobalBounds().height/2.f) * (point.y - shape.getGlobalBounds().height/2.f)
                );
    };

    float eRad = shape.getRadius();

    for(size_type i = 0, s = getPointCount(); i < s;)
    {
//        if(mathPoint(getPoint(i)) <= eRad)
        if(shape.getGlobalBounds().contains(getPoint(i)))
        {

            m_points.erase(m_points.begin() + i);
        }
        else i++;

        s = getPointCount();
    }
}

ShapeMask &ShapeMask::operator+=(const ShapeMask::container_type &container)
{
    this->addPoints(container);

    return *this;
}

void ShapeMask::clear()
{
    m_points.clear();

    left(0);
    right(0);
}
