
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

  ComplexPlane plane(width, height);//figure out how to get height amd width

  Text text;
  Font font;
  font.loadFromFile("KOMIKAP_.ttf");//maybe change font
  text.setFont(font);
  text.setCharacterSize(50);
  text.setFillColor(Color::White);

  FloatRect textRect = text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  text.setPosition(1920 / 2.0f, 1080 / 2.0f);

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
          plane.zoomOut();
          plane.setCenter(event.mouseButton.x, event.mouseButton.y);
        }
        if(event.mouseButton.button == Mouse::Left)
        {
          plane.zoomIn();
          plane.setCenter(event.mouseButton.x, event.mouseButton.y);
        }
      }
      if(event.type == Event::MouseMoved)
      {
        plane.setMouseLocation(event.mouseMove.x,event.mouseMove.y)
      }
    }
    if(Keyboard::isKeyPressed(Keyboard::Escape))
    {
      window.close();
    }

    //Update Scene segment
    //Call updateRender on the ComplexPlane object
    //Call loadText on the ComplexPlane object
    complexPlane.updateRender();
    complexPlane.loadText(text);

    
    //Draw Scene segment
    //draw the ComplexPlane object
    //draw the Text object
    //Display the RenderWindow object
    window.clear();
    plane.draw(window, RenderStates::Default);
    window.draw(text);
    window.display();
    
  }
  
}
