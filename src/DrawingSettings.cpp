#include "DrawingSettings.h"

DrawingSettings::DrawingSettings(DrawingSettings::DrawType type, const size_type& step)
:   m_type(type),
    m_step(step)
{}

void DrawingSettings::type(DrawingSettings::DrawType type)
{
    m_type = type;
}

DrawingSettings::DrawType DrawingSettings::type() const {
    return m_type;
}

void DrawingSettings::step(const DrawingSettings::size_type& value)
{
    m_step = value;
}

DrawingSettings::size_type DrawingSettings::step() const
{
    return m_step;
}
