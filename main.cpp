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
void pop(sf::Vector2i localMousePos, int cursor_box_size, Matrix* matrix, sf::Mouse::Button button);

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Sand Simulator");
    window.setFramerateLimit(60);

    sf::VertexArray cursor_box;
    bool isButtonPressed = false;
    sf::Mouse::Button button = sf::Mouse::Button();

    int cursor_box_size = CURSOR_BOX_MIN_SIZE;

    Matrix matrix(WIN_HEIGHT, WIN_WIDTH, ELEMENT_PIXEL_MULTIPLIER);

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
                if (event.mouseButton.button == sf::Mouse::Left || event.mouseButton.button == sf::Mouse::Right)
                {
                    isButtonPressed = true;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left || event.mouseButton.button == sf::Mouse::Right)
                {
                    isButtonPressed = false;
                    button = event.mouseButton.button;
                }
            }
        }

        if (isButtonPressed)
        {
            pop(sf::Mouse::getPosition(window), cursor_box_size, &matrix, button);
        }

        cursor_box = setCursorBox(sf::Mouse::getPosition(window), cursor_box_size);
        matrix.update();

        window.clear(sf::Color::Black);
        window.draw(matrix.getVertexArray());
        window.draw(cursor_box);
        window.display();
    }

    return 0;
}

void pop(sf::Vector2i localMousePos, int cursor_box_size, Matrix *matrix, sf::Mouse::Button button)
{
    sf::Vector2f absolutePos = sf::Vector2f(localMousePos.x - (cursor_box_size / 2), localMousePos.y - (cursor_box_size / 2));

    for (std::uint16_t i = 0; i < cursor_box_size / ELEMENT_PIXEL_MULTIPLIER; i++)
    {
        for (std::uint16_t j = 0; j < cursor_box_size / ELEMENT_PIXEL_MULTIPLIER; j++)
        {
            int random = rand() % 3;
            if (random == 1)
            {
                if (button == sf::Mouse::Left)
                    matrix->summonElement(absolutePos.x + (i * ELEMENT_PIXEL_MULTIPLIER), absolutePos.y + (j * ELEMENT_PIXEL_MULTIPLIER), SAND);
                else if (button == sf::Mouse::Right)
                    matrix->summonElement(absolutePos.x + (i * ELEMENT_PIXEL_MULTIPLIER), absolutePos.y + (j * ELEMENT_PIXEL_MULTIPLIER), WATER);
            }
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