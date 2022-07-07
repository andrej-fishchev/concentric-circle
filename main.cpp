#include <vector>
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "src/ShapeMask.h"
#include "src/Line.h"

#define SCAST($1,$2) static_cast<$1>($2)
#define RAND($1,$2) rand() % $1 + $2

auto getRandomColor = [] (const sf::Uint8& alpha) -> sf::Color
{
    return
    {SCAST(sf::Uint8, RAND(150, 105)),
     SCAST(sf::Uint8, RAND(150, 105)),
     SCAST(sf::Uint8, RAND(150, 105)),
         alpha
    };
};

int main()
{
    std::size_t size = 15;

    std::srand(std::time(NULL));

    DrawingSettings drawingSettings
        {DrawingSettings::DRAW_CYCLIC };

    sf::CircleShape marker
        {5.f, 20};
    marker.setFillColor(getRandomColor(200));

    sf::CircleShape innerMarker
        { 5.f, 20 };
    innerMarker.setFillColor(getRandomColor(200));

    sf::RenderWindow window
    {
        sf::VideoMode {1280, 720 },
        "CircleRenderer",
        sf::Style::Close | sf::Style::Titlebar
    };

    auto createCircle = []
            (sf::RenderWindow& win,
            const float& radius = 10,
            const std::size_t& points = 30) -> sf::CircleShape
    {
        sf::CircleShape circle { radius, points };
        circle.setOrigin(circle.getGlobalBounds().width/2, circle.getGlobalBounds().height/2);
        circle.setPosition(win.getSize().x/2.f - 25.f, win.getSize().y/2.f - 25.f);
//        circle.setFillColor(getRandomColor(255));
        return circle;
    };

    sf::CircleShape circleShape {marker.getRadius() * size, 100};
    circleShape.setPosition({
        window.getSize().x/2.f - (size - 1) * marker.getRadius() - 2,
        window.getSize().y/2.f - (size - 1) * marker.getRadius() - 2
    });

    circleShape.setOutlineThickness(marker.getRadius());
    circleShape.setOutlineColor({
        0,
        0,
        0,
        150
    });

    ShapeMask innerMask;
    ShapeMask bufferMask;
    LineSegment lineSegment;

    for(std::size_t i = 1; i <= size; i++)
    {
        bufferMask =
            {createCircle(window, marker.getRadius() * i + 1, 300)};

        bufferMask.setPosition({
            window.getSize().x/2.f - marker.getRadius() * i,
            window.getSize().y/2.f - marker.getRadius() * i
        });

        if(i > 1)
        {
            lineSegment = LineSegment{
                4,
                innerMask.getPoint(innerMask.getPointCount() - 1),
                bufferMask.getPoint(0)
            };

            innerMask += lineSegment.dump(0, lineSegment.points());
        }

        innerMask += bufferMask.getPoints(0,
                                          (i == size)
                                            ? bufferMask.getPointCount()
                                            : bufferMask.getPointCount() - 5);
    }

    marker.setRadius(2.f);

    sf::Event event {};
    sf::Uint32 ticks = 0;
    sf::Uint32 tickrate = 512;

    while(window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Q:
                        bufferMask.clear();
                        bufferMask += innerMask;

                        break;

                    case sf::Keyboard::W:
                        bufferMask.clear();
                        bufferMask += innerMask;
                        bufferMask.excludePoints(createCircle(window, 25.f, 100));

                        break;
                    case sf::Keyboard::Up:
                        if(tickrate >> 2)
                            tickrate >>= 2;
                        break;

                    case sf::Keyboard::Down:
                        tickrate <<= 2;
                        break;

                    case sf::Keyboard::Right:
                        drawingSettings.step(drawingSettings.step() + 1);
                        break;

                    case sf::Keyboard::Left:
                        if(drawingSettings.step())
                            drawingSettings.step(drawingSettings.step() - 1);
                        break;

                    case sf::Keyboard::Space:
                        marker.setFillColor(getRandomColor(255));
                        break;

                    case sf::Keyboard::Num1:
                        drawingSettings.type(DrawingSettings::DRAW_RIGHT_TO_LEFT);
                        break;

                    case sf::Keyboard::Num2:
                        drawingSettings.type(DrawingSettings::DRAW_CYCLIC);
                        break;

                    case sf::Keyboard::Num3:
                        drawingSettings.type(DrawingSettings::DRAW_LEFT_TO_RIGHT);
                        break;

                    default: break;
                }
            }
        }

        if (!(ticks % tickrate))
        {
            window.clear(sf::Color::White);
            window.draw(circleShape);

            bufferMask.draw(window, marker, drawingSettings);

            window.display();
        }

        ticks++;

        if (ticks == UINT32_MAX)
            ticks = 0;
    }
}
