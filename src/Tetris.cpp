﻿#include "Tetris.hpp"
#include"colors.hpp"
#include"RoundedRectangleShape.hpp" 
#include<stdio.h>
void Tetris::drawText(sf::String content, int size, float x, float y,bool Gras=false )
{
    sf::Text text(content, font, size);
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y);
    if (Gras) text.setStyle(sf::Text::Bold);
    render.draw(text);
    
    
}
void Tetris::drawRectangle(float length, float width, float x, float y)
{
    sf::RoundedRectangleShape rectangle(sf::Vector2f(length, width), 10, 10);
    rectangle.setPosition(x, y);
    rectangle.setFillColor(lightBlue);
    render.draw(rectangle); 
}




void Tetris::draw()
{


    render.clear();

    sf::Texture BackgroundTexture;
    if (!BackgroundTexture.loadFromFile("assets/OIP.jpg")) std::cout << "no image " << std::endl;

    // G�rer l'erreur si le chargement de l'image �choue


// Cr�er un sprite pour afficher l'image
    sf::Sprite background;
    sf::Vector2u TextureSize;  //Added to store texture size.
    sf::Vector2u WindowSize;   //Added to store window size.
    TextureSize = BackgroundTexture.getSize();//Get size of texture.
    sf::Vector2u renderSize = render.getSize();
    float ScaleX = (float)renderSize.x / TextureSize.x;
    float ScaleY = (float)renderSize.y / TextureSize.y;     //Calculate scale.

    background.setTexture(BackgroundTexture);
    background.setScale(ScaleX, ScaleY);      //Set scale.  
    background.setColor(sf::Color(255, 255, 255, 150));
    render.draw(background);

    drawRectangle(300, 100, 550, 70);
    drawRectangle(250, 180, 550, 300);
    drawRectangle(300, 100, 550, 600);
    drawText("Score", 40, 650, 5);
    drawText("Next", 40, 640, 250);
    sf::Text scrtxt(std::to_string(score), font, 70);
    int scoresize=scrtxt.getGlobalBounds().width;
    drawText(std::to_string(score), 70, 550 + (300 - scoresize) / 2, 75,true);
    drawText("Level", 40, 650, 550);
    drawText(std::to_string(level), 70, 680, 610,true);
    if (gameOver)
    {
        drawText("Game Over ", 40, 600, 750);
        if (client != NULL) client->sendGameOver();

    }
    grid.draw(render, currentBlock.get_cell_postion());
    currentBlock.draw(render, 11, 11, Animated, clockAnimated);
    nextBlock.draw(render, nextBlock.next_x_offset,nextBlock.next_y_offset, false, clockAnimated);
    if (client == NULL)
    {
        // client->updatePieceState(&currentBlock);
         //client->updateState(&grid);
         //drawUserWorlds();
         //std::cout << "le client Null" << std::endl;
    }
    render.display();

}


void Tetris::drawUserWorlds()
{
    int cell_size = 35;
    int mini_cell_size = 20;
    int border = 15;
    int starty = 52;
    int startx = cell_size * 10 + 100;
    std::vector<sf::Color> colors = GetCellColors();


    int step = 0;
    int usr = -1;

    for (int n = 0; n < 2; n++) {

        int posy = step * mini_cell_size * 22 + step * 66;

        usr++;
        if (client->getId() == usr) {
            usr++;
        }



        step++;
        int** world = client->getUserWorld(usr);

        int k = 0;

        world[0][0] = 0;
        for (int i = 0; i < 22; ++i) {
            int temp = world[i][0];
            for (int j = 0; j < 9; ++j) {
                world[i][j] = world[i][j + 1];
            }
            world[i][9] = temp;
        }
        //std::cout << "client name " << client->getName(usr) << std::endl;

        drawText(client->getName(usr), 40, 500, posy,false);
        for (int x = 0; x < 22; x++) {
            for (int y = 0; y < 10; y++) {
                sf::RectangleShape rectangle1;
                int cell_value = world[x][y];

                sf::RectangleShape rectangle;
                rectangle1.setSize(sf::Vector2f(mini_cell_size - 1, mini_cell_size - 1));
                rectangle1.setPosition(y * mini_cell_size + 1000, posy + x * mini_cell_size + 50);
                rectangle1.setOutlineThickness(1);
                rectangle1.setOutlineColor(sf::Color::Cyan);

                rectangle1.setFillColor(colors[cell_value]);

                render.draw(rectangle1);
            }


        }
       // std::cout <<"client name "<< client->getName(usr) << std::endl;

        drawText(client->getName(usr), 40, 500, posy, false);
        int pieceID = client->getPieceID(usr);
        int* piece = client->getPiece(usr);

        for (int p = 0; p < 8; p += 2) {
            /*
            block.setColor(PIECE_COLOR[piece[p] - 1]);
            block.setPosition(posx + (p % 4 + piece_x) * tile, posy + (p / 4 + piece_y) * tile);
            render.draw(block);
            */
                    sf::RectangleShape rectangle;
                    rectangle.setSize(sf::Vector2f(mini_cell_size - 1, mini_cell_size - 1));
                    rectangle.setPosition(piece[p + 1] * mini_cell_size + 1000, posy + piece[p] * mini_cell_size + 50);
                    // colors[pieceID].a = 255;

                    rectangle.setFillColor(colors[pieceID]);

                    render.draw(rectangle);
                }

            }
            usr++;
            int** world = client->getUserWorld(usr);
            int posy = 300;
            int posx = 1000 + 22 * mini_cell_size;
            int k = 0;

            world[0][0] = 0;
            for (int i = 0; i < 22; ++i) {
                int temp = world[i][0];
                for (int j = 0; j < 9; ++j) {
                    world[i][j] = world[i][j + 1];
                }
                world[i][9] = temp;
            }
            drawText(client->getName(usr), 40, posx, posy,false);
            for (int x = 0; x < 22; x++) {
                for (int y = 0; y < 10; y++) {
                    sf::RectangleShape rectangle1;
                    int cell_value = world[x][y];

                    sf::RectangleShape rectangle;
                    rectangle1.setSize(sf::Vector2f(mini_cell_size - 1, mini_cell_size - 1));
                    rectangle1.setPosition(y * mini_cell_size + posx, posy + x * mini_cell_size + 11);
                    rectangle1.setOutlineThickness(1);
                    rectangle1.setOutlineColor(sf::Color::Cyan);

                    rectangle1.setFillColor(colors[cell_value]);

                    render.draw(rectangle1);
                }


            }

            int pieceID = client->getPieceID(usr);
            int* piece = client->getPiece(usr);

            for (int p = 0; p < 8; p += 2) {

                /*block.setColor(PIECE_COLOR[piece[p] - 1]);
                block.setPosition(posx + (p % 4 + piece_x) * tile, posy + (p / 4 + piece_y) * tile);
                window.draw(block);*/
                
                        sf::RectangleShape rectangle;
                        rectangle.setSize(sf::Vector2f(mini_cell_size - 1, mini_cell_size - 1));
                        rectangle.setPosition(piece[p + 1] * mini_cell_size + posx, posy + piece[p] * mini_cell_size + 11);
                        // colors[pieceID].a = 255;

                        rectangle.setFillColor(colors[pieceID]);

                        render.draw(rectangle);
                    }

    render.display();
}





