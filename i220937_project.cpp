/* NAME: HALEEMA TAHIR MALIK
 * ROLL NO: 22I-0937
 * BSCS PF PROJECT*/

/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */

#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <iostream>

using namespace sf;
int main(){


    srand(time(0));

    RenderWindow window(VideoMode(320, 480), title);

    Texture obj1, obj2, obj3, obj4,obj5;
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */

    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/shadow.jpg");
    obj5.loadFromFile("img/bomb.png");

    Font font;
    font.loadFromFile("FontsFree-Net-aerial.ttf");
    Sprite sprite(obj1), background(obj2), frame(obj3), bomb(obj5);
    Sprite shadow(obj4);

    int delta_x=5, colorNum=1,l=3,r=rand()%9;
    float timer=0, delay=0.5;
    bool rotate=0;
    Clock clock;

    bool showMenu = true;                      //flag for showing menu

    while (window.isOpen()) {

        if (showMenu) {                        //while the menu is displayed
            window.clear(Color::Black);
            window.draw(background);

            //text that will be shown in menu
            Text Welcome(" WELCOME TO\n TETRIS",font,20);
            Welcome.setFillColor(sf::Color::White);
            Welcome.setStyle(sf::Text::Bold);
            Welcome.setPosition(10,120);
            window.draw(Welcome);

            Text Menu("Press\n 1- New Game\n 2- Exit Game\n 3- Back",font,16);
            Menu.setFillColor(sf::Color::White);
            Menu.setPosition(10,180);
            window.draw(Menu);

            window.display();

            //---Event Listening part for menu
            Event m;
            while (window.pollEvent(m)) {                    //Event is occurring - until the game is in running state
                if (m.type == Event::Closed)                   //If cross/close is clicked/pressed
                    window.close();                            //Opened window disposes
                if (m.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                    if (m.key.code == Keyboard::Num1 | m.key.code == Keyboard::Numpad1)            //Check if the other key pressed is 1
                    {
                        showMenu = false;                       //The menu window closes and the game starts
                        resetgame();
                    }
                        //add code -- reset values fed into sprite
                    else if (m.key.code == Keyboard::Num2 | m.key.code == Keyboard::Numpad2)     //Check if the other key pressed is 2
                    {
                        window.close();                       //The program terminates

                    }
                        else if(m.key.code == Keyboard::Num5 | m.key.code == Keyboard::Numpad3)
                        showMenu=false;                        //game resumes

                }
            }
        }
        else {
            if (endgame()) {                                   //when the game ends, endgame function is called

                //new window

                window.clear(Color::Black);
                window.draw(background);
                Text GameOver("Your Game Is Over!\n Press H to restart game.", font, 16);
                GameOver.setFillColor(sf::Color::White);
                GameOver.setPosition(10, 180);
                window.draw(GameOver);

                Text Cscore(std::string("Current Score: " + std::to_string(Currentscore)), font, 10);
                Cscore.setFillColor(sf::Color::White);
                Cscore.setPosition(10, 280);
                window.draw(Cscore);

                Text Hscore(std::string("Highest Score: " + std::to_string(Highestscore)), font, 10);
                Hscore.setFillColor(sf::Color::White);
                Hscore.setPosition(10, 300);
                window.draw(Hscore);


                window.display();
                //add key listen
                Event newmenu;
                while (window.pollEvent(newmenu)) {
                    if (newmenu.key.code == Keyboard::H) {
                        resetgame();
                        Currentscore=0;
                    }
                }


            }
            else {
                float time = clock.getElapsedTime().asSeconds();
                clock.restart();
                timer += time;

                //---Event Listening Part---//
                Event e;
                while (window.pollEvent(
                        e)) {                    //Event is occurring - until the game is in running state
                    if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                        window.close();                            //Opened window disposes
                    if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                        if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                            rotate = true;                         //Rotation gets on
                        else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                            delta_x = -1;                          //Change in X-Axis - Negative
                        else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                            delta_x = 1;                           //Change in X-Axis - Positive
                        else if (e.key.code == Keyboard::H) {
                            showMenu = true;
                        }
                        break;


                    }
                }
        if(l==0 )
            {

                delay=0.1;      
                fallingBomb(timer, delay, colorNum,l,r);
                delay=0.5;      
                window.clear(Color::Black);
                window.draw(background);
                Text text("Press H to escape to menu", font, 10);
                text.setFillColor(sf::Color::White);
                text.setPosition(1.5, 1);
                window.draw(text);

                Text score(std::string("Score: " + std::to_string(Currentscore)), font, 10);
                score.setFillColor(sf::Color::White);
                score.setPosition(230, 200);
                window.draw(score);

                for (int i = 0; i < M; i++) {
                    for (int j = 0; j < N; j++) {
                        if (gameGrid[i][j] == 0)
                            continue;
                        sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                        sprite.setPosition(j * 18, i * 18);
                        sprite.move(28, 31); //offset
                        window.draw(sprite);
                    }
                }
            for (int i=0; i<M; i++){
                for (int j=0; j<N; j++){
                    if (gameGrid2[i][j]==0)
                        continue;
                    bomb.setTextureRect(IntRect(gameGrid2[i][j]*18,0,18,18));
                    bomb.setPosition(j*18,i*18);
                    bomb.move(28,31); //offset
                    window.draw(bomb);
                }
            }
            
                for (int i=0; i<4; i++){
                bomb.setTextureRect(IntRect(colorNum*18,0,18,18));
                bomb.setPosition(point_1[i][0]*18,point_1[i][1]*18);
                bomb.move(28,31);
                window.draw(bomb);
            }
                for (int i = 0; i < 4; i++) {

                    shadow.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                    shadow.setPosition(Shadow_array[i][0] * 18, Shadow_array[i][1] * 18);
                    shadow.move(28, 31);
                    window.draw(shadow);
                }
                //---The Final on Which Everything is Drawn Over is Loaded---//
                window.draw(frame);
                //---The Window that now Contains the Frame is Displayed---//
                window.display();
            }
            else if(l!=0)
            {
                if (Keyboard::isKeyPressed(
                        Keyboard::Down))                    //Just another way to detect key presses without event listener
                    delay = 0.05;                                //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05


                ///////////////////////////////////////////////
                ///*** START CALLING YOUR FUNCTIONS HERE ***///

                fallingPiece(timer, delay, colorNum,l,r);                 //Example: fallingPiece() function is called here
                MovePieceRight(delta_x, timer, delay, colorNum);
                MovePieceLeft(delta_x, timer, delay, colorNum);
                Rotate(rotate);
                RemoveLine();
                Shadow();

                delay = 0.5;

                ///*** YOUR CALLING STATEMENTS END HERE ***///
                //////////////////////////////////////////////

                window.clear(Color::Black);
                window.draw(background);
                Text text("Press H to escape to menu", font, 10);
                text.setFillColor(sf::Color::White);
                text.setPosition(1.5, 1);
                window.draw(text);

                Text score(std::string("Score: " + std::to_string(Currentscore)), font, 10);
                score.setFillColor(sf::Color::White);
                score.setPosition(230, 200);
                window.draw(score);

                for (int i = 0; i < M; i++) {
                    for (int j = 0; j < N; j++) {
                        if (gameGrid[i][j] == 0)
                            continue;
                        sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                        sprite.setPosition(j * 18, i * 18);
                        sprite.move(28, 31); //offset
                        window.draw(sprite);
                    }
                }
                for (int i=0; i<M; i++){
                    for (int j=0; j<N; j++){
                        if (gameGrid2[i][j]==0)
                            continue;
                        bomb.setTextureRect(IntRect(gameGrid2[i][j]*18,0,18,18));
                        bomb.setPosition(j*18,i*18);
                        bomb.move(28,31); //offset
                        window.draw(bomb);
                    }
                 }
                for (int i = 0; i < 4; i++) {
                    sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                    sprite.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
                    sprite.move(28, 31);
                    window.draw(sprite);
                }
                for (int i = 0; i < 4; i++) {

                    shadow.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                    shadow.setPosition(Shadow_array[i][0] * 18, Shadow_array[i][1] * 18);
                    shadow.move(28, 31);
                    window.draw(shadow);
                }
                //---The Final on Which Everything is Drawn Over is Loaded---//
                window.draw(frame);
                //---The Window that now Contains the Frame is Displayed---//
                window.display();
            }
                
            }
        }
    }
    return 0;
}