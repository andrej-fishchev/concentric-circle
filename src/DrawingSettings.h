#ifndef CONCENTRIC_CIRCLE_DRAWINGSETTINGS_H
#define CONCENTRIC_CIRCLE_DRAWINGSETTINGS_H

#include <ios>

class DrawingSettings
{
public:
    using size_type = std::size_t;

public:
    enum DrawType
    {
        DRAW_NONE = 0,
        DRAW_CYCLIC,
        DRAW_LEFT_TO_RIGHT,
        DRAW_RIGHT_TO_LEFT,

        DRAW_MAX
    };

public:
    DrawingSettings(DrawType type = DRAW_CYCLIC, const size_type& step = 1);

public:
    void type(DrawType type);
    DrawType type() const;

    void step(const size_type& value);
    size_type step() const;

private:
    DrawType m_type;
    size_type m_step;
};


#endif //CONCENTRIC_CIRCLE_DRAWINGSETTINGS_H
