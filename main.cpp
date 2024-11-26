#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "ComplexPlane.h"

int main()
{
  VideoMode vm(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "ComplexPlane.h"

using namespace sf;
using namespace std;

int main()
{
  VideoMode vm(VideoMode::getDesktopMode().width/2, VideoMode::getDesktopMode().height/2);
  RenderWindow window(vm, "Mandelbrot Set", Style::Default);

  ComplexPlane complexPlane(width, height);//figure out how to get height amd width
  }

text.setCharacterSize(24);
text.setFillColor(sf::Color::White);
text.setPosition(10.f, 10.f);
  Text messageText;
  Font font;
  font.loadFromFile("KOMIKAP_.ttf");//maybe change font
  messageText.setFont(font);
  messageText.setCharacterSize(50);
  messageText.setFillColor(Color::White);

  FloatRect textRect = messageText.getLocalBounds();
  messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

  while (window.isOpen())
  {
    Event event;
    while (window.pollEvent(event))
    {
      if(event.type == Event::Closed)
      {
        window.close();
      }
      if(event.type == Event::MouseButtoPressed))
      {
        if(event.mouseButton.button == Mouse::Right)
        {
          //Right click will zoomOut and call setCenter on the ComplexPlane object with the (x,y) pixel location of              the mouse click
        }
        if(event.mouseButton.button == Mouse::Left)
        {
          //Left click will zoomIn and call setCenter on the ComplexPlane object with the (x,y) pixel location of                the mouse click
        }
      }
      if(event.type == Event::MouseMoved)
      {
        //Call setMouseLocation on the ComplexPlane object to store the (x,y) pixel location of the mouse click
        //This will be used later to display the mouse coordinates as it moves
      }
    }
    if(Keyboard::isKeyPressed(Keyboard::Escape))
    {
      window.close();
    }

    //Update Scene segment
    //Call updateRender on the ComplexPlane object
    //Call loadText on the ComplexPlane object
    if()
    {
      
    }
    //Draw Scene segment
    //draw the ComplexPlane object
    //draw the Text object
    //Display the RenderWindow object
    window.clear();
    window.draw(messageText);
    window.display();
    
  }
  
}
/*
  ****************************************
  Update
  ****************************************
  */
  if(points.size() > 0)
  {
        ///generate more point(s)
        ///select random vertex
        ///calculate midpoint between random vertex and the last point in the vector
      ///push back the newly generated coord.
    int vertex = rand() % 3;
        Vector2f middle((points[points.size()-1].x + vertices[vertex].x) / 2.0f, (points[points.size()-1].y + vertices[vertex].y) / 2.0f);
        points.push_back(middle); 

  }

  /*
  ****************************************
  Draw
  ****************************************
  */
  window.clear();
  for(int i = 0; i < vertices.size(); i++)
  {
        RectangleShape rect(Vector2f(10,10));
        rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
        rect.setFillColor(Color::Blue);
        window.draw(rect);
  }
  for (int i = 0; i < points.size(); i++)
  {
        RectangleShape point(Vector2f(10, 10));
        point.setPosition(points[i].x, points[i].y);
        point.setFillColor(Color::Red);
        window.draw(point);
  }
  if(vertices.size()==0)
  {	
    window.draw(messageText);
  }
  if(vertices.size()==3&&points.size()==0)
  {
    messageText.setString("Add another point");
    window.draw(messageText);
  }
  window.display();
}
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"



   

    

    // Start the main loop
    while (window.isOpen()) {
        // Handle Input segment
        sf::Event event;
        while (window.pollEvent(event)) {
            // Handle window close event
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle mouse button pressed events
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Left click: zoom in
                    complexPlane.zoomIn();
                    complexPlane.setCenter(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    // Right click: zoom out
                    complexPlane.zoomOut();
                    complexPlane.setCenter(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                }
            }

            // Handle mouse moved event
            if (event.type == sf::Event::MouseMoved) {
                complexPlane.setMouseLocation(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            }

            // Handle keyboard input (Escape to close the window)
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        // Update Scene segment
        complexPlane.updateRender();
        complexPlane.loadText(text);

        // Draw Scene segment
        window.clear(sf::Color::Black);  // Clear with black background
        complexPlane.draw(window, sf::RenderStates::Default);  // Draw the ComplexPlane
        window.draw(text);  // Draw the text
        window.display();  // Display the content on the window
    }

    return 0;
}

