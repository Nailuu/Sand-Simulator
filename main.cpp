#include <iostream>
#include <array>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Matrix.h"
#include "Element.h"
#include "Statistics.h"
#include "Selector.h"

#define WIN_HEIGHT 800
#define WIN_WIDTH 800

#define ELEMENT_PIXEL_MULTIPLIER 5

#define CURSOR_BOX_MIN_SIZE ELEMENT_PIXEL_MULTIPLIER
#define CURSOR_BOX_MAX_SIZE ELEMENT_PIXEL_MULTIPLIER * 5

sf::VertexArray setCursorBox(sf::Vector2i localMousePos, int cursor_box_size);
void pop(sf::Vector2i localMousePos, int cursor_box_size, Matrix* matrix, ElementType type);

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Sand Simulator");
    //window.setFramerateLimit(60);

    sf::VertexArray cursor_box;
    bool isButtonPressed = false;

    int cursor_box_size = CURSOR_BOX_MIN_SIZE;

    Matrix matrix(WIN_HEIGHT, WIN_WIDTH, ELEMENT_PIXEL_MULTIPLIER);

    Statistics stats;

    Selector selector(WIN_WIDTH, WIN_HEIGHT);

    window.setMouseCursorVisible(false);

    sf::Clock clock;

    while (window.isOpen())
    {
        std::float_t currentTime = clock.restart().asSeconds();
        std::float_t fps = 1.0f / currentTime;
        stats.setFPS(fps);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseWheelMoved)
            {
                selector.changeSelection(event.mouseWheel.delta);
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    isButtonPressed = true;
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    isButtonPressed = false;
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.scancode == sf::Keyboard::Scancode::Q && cursor_box_size < CURSOR_BOX_MAX_SIZE)
                    cursor_box_size += ELEMENT_PIXEL_MULTIPLIER;

                else if (event.key.scancode == sf::Keyboard::Scancode::E && cursor_box_size > CURSOR_BOX_MIN_SIZE)
                    cursor_box_size -= ELEMENT_PIXEL_MULTIPLIER;
            }
        }

        if (isButtonPressed)
        {
            pop(sf::Mouse::getPosition(window), cursor_box_size, &matrix, selector.getSelectedElement());
        }

        cursor_box = setCursorBox(sf::Mouse::getPosition(window), cursor_box_size);
        matrix.update(&stats);

        window.clear(sf::Color(27, 25, 38, 255));
        window.draw(matrix.getVertexArray());
        window.draw(cursor_box);
        window.draw(stats);
        window.draw(selector);
        window.display();
    }

    return 0;
}

void pop(sf::Vector2i localMousePos, int cursor_box_size, Matrix *matrix, ElementType type)
{
    sf::Vector2f absolutePos = sf::Vector2f(localMousePos.x - (cursor_box_size / 2), localMousePos.y - (cursor_box_size / 2));

    for (std::uint16_t i = 0; i < cursor_box_size / ELEMENT_PIXEL_MULTIPLIER; i++)
    {
        for (std::uint16_t j = 0; j < cursor_box_size / ELEMENT_PIXEL_MULTIPLIER; j++)
        {
            if (type != STONE)
            {
                int random = rand() % 2;
                if (random == 1)
                {
                    matrix->summonElement(absolutePos.x + (i * ELEMENT_PIXEL_MULTIPLIER), absolutePos.y + (j * ELEMENT_PIXEL_MULTIPLIER), type);
                }
            }
            else
                matrix->summonElement(absolutePos.x + (i * ELEMENT_PIXEL_MULTIPLIER), absolutePos.y + (j * ELEMENT_PIXEL_MULTIPLIER), type);
        }
    }
}

sf::VertexArray setCursorBox(sf::Vector2i localMousePos, int cursor_box_size)
{
    sf::VertexArray va(sf::LineStrip, 5);

    va[0].position = sf::Vector2f(localMousePos.x - (cursor_box_size / 2), localMousePos.y - (cursor_box_size / 2));
    va[1].position = sf::Vector2f(localMousePos.x + (cursor_box_size / 2), localMousePos.y - (cursor_box_size / 2));
    va[2].position = sf::Vector2f(localMousePos.x + (cursor_box_size / 2), localMousePos.y + (cursor_box_size / 2));
    va[3].position = sf::Vector2f(localMousePos.x - (cursor_box_size / 2), localMousePos.y + (cursor_box_size / 2));
    va[4].position = sf::Vector2f(localMousePos.x - (cursor_box_size / 2), localMousePos.y - (cursor_box_size / 2));

    va[0].color = sf::Color::White;
    va[1].color = sf::Color::White;
    va[2].color = sf::Color::White;
    va[3].color = sf::Color::White;
    va[4].color = sf::Color::White;

    return va;
}