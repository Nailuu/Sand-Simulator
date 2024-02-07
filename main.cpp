#include <iostream>
#include <array>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Matrix.h"
#include "Element.h"

#define WIN_HEIGHT 800
#define WIN_WIDTH 800

#define ELEMENT_PIXEL_MULTIPLIER 5

#define CURSOR_BOX_MIN_SIZE ELEMENT_PIXEL_MULTIPLIER
#define CURSOR_BOX_MAX_SIZE ELEMENT_PIXEL_MULTIPLIER * 5

sf::VertexArray setCursorBox(sf::Vector2i localMousePos, int cursor_box_size);

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Sand Simulator");
    sf::VertexArray va;
    bool isButtonPressed = false;
    sf::Vector2i localMousePos = sf::Vector2i();
    int cursor_box_size = CURSOR_BOX_MIN_SIZE;

    Matrix matrix(WIN_HEIGHT, WIN_WIDTH, ELEMENT_PIXEL_MULTIPLIER);

    matrix.summonElement(400, 0, SAND);

    window.setMouseCursorVisible(false);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseWheelMoved)
            {
                if (event.mouseWheel.delta == 1 && cursor_box_size < CURSOR_BOX_MAX_SIZE)
                    cursor_box_size += ELEMENT_PIXEL_MULTIPLIER;
                else if (event.mouseWheel.delta == -1 && cursor_box_size > CURSOR_BOX_MIN_SIZE)
                    cursor_box_size -= ELEMENT_PIXEL_MULTIPLIER;
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    isButtonPressed = true;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    isButtonPressed = false;
                }
            }
        }

        if (isButtonPressed)
        {
            localMousePos = sf::Mouse::getPosition(window);
            matrix.summonElement(localMousePos.x, localMousePos.y, SAND);
        }

        va = setCursorBox(sf::Mouse::getPosition(window), cursor_box_size);

        matrix.update();

        window.clear(sf::Color::Black);
        window.draw(matrix);
        window.draw(va);
        window.display();
    }

    return 0;
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