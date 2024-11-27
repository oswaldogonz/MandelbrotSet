#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"

using namespace sf;
using namespace std;

int main()
{
  int width=VideoMode::getDesktopMode().width/2;
  int height=VideoMode::getDesktopMode().height/2;
  videoMode vm(width, height);
  RenderWindow window(vm, "Mandelbrot Set", Style::Default);
  ComplexPlane plane(width, height);

  Font font;
  font.loadFromFile("KOMIKAP_.ttf");
  
  Text text;
  text.setFont(font);
  text.setCharacterSize(30);
  text.setFillColor(Color::White);
  text.setPosition(10, 10);
  while (window.isOpen())
  {
    Event event;
    while(window.pollEvent(event))
    {
      if(event.type==Event::Closed)
      {
        window.close();
      }
      if(event.type==Event::MouseButtonPressed))
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
        plane.setMouseLocation(event.mouseMove.x,event.mouseMove.y);
      }
    }
    if(Keyboard::isKeyPressed(Keyboard::Escape))
    {
      window.close();
    }

    plane.updateRender();
    plane.loadText(text);

    window.clear();
    window.draw(plane);
    //plane.draw(window, RenderStates::Default);
    window.draw(text);
    window.display();
  }
  return 0;
}
