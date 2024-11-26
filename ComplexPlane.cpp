#include "ComplexPlane.h"
#include <cmath>
#include <sstream>

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
  m_pixel_size={pixelWidth, pixelHeight};
  m_aspectRatio=(pixelHeight*1.0)/(pixelWidth*1.0);
  m_plane_center={0,0};
  m_plane_size={BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};
  m_zoomCount=0;
  m_state=State::Calculating;
  m_vArray.setPrimitiveType(Points);
  m_vArray.resize(pixelWidth* pixelHeight);
  
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
  target.draw(m_vArray);
}

void ComplexPlane::updateRender()
{
  if(m_state==State::Calculating)
  {
    for(int i=0; i<m_pixel_size.y; i++)
    {
      for(int j=0; j<m_pixel_size.x; j++)
      {
        m_vArray[j+i*m_pixel_size.x].position = { (float)j,(float)i };
        Vector2f coordinate=mapPixelToCoords(vector2i(j,i));
        int iteration=countIterations(coordinate);
        Uint8 r;
        Uint8 g;
        Uint8 b;
        iterationsToRGB(iteration, r, g, b);
        m_vArray[j+i*m_pixel_size.x].color = { r,g,b };
      }
    }
    m_state=State::Displaying;
  }
}
  
void ComplexPlane::zoomIn()
{
  m_zoomCount++;
  double x=BASE_WIDTH*pow(BASE_ZOOM, m_zoomCount);
  double y=BASE_HEIGHT*m_aspectRatio*pow(BASE_ZOOM, m_zoomCount);
  m_plane_size={x,y};
  m_state=State::Calculating;
}

void ComplexPlane::zoomOut()
{
  m_zoomCount--;
  double x=BASE_WIDTH*pow(BASE_ZOOM, m_zoomCount);
  double y=BASE_HEIGHT*m_aspectRatio*pow(BASE_ZOOM, m_zoomCount);
  m_plane_size={x,y};
  m_state=State::Calculating;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
  m_plane_center=mapPixelToCoords(mousePixel);
  m_state=State::Calculating;
}

void ComplexPlane::setMouseLocation(Vector2i mousPixel)
{
  m_mouseLocation=mapPixelToCoords(mousPixel);
}

void ComplexPlane::loadText(Text& text)
{
  ostringstream output;
  output<<"Mandelbrot Set"<<endl;
  output<<"Center: ("<<m_plane_center.x<<","<<m_plane_center.y<<")"<<endl;
  output<<"Cursor: ("<<m_mouseLocation.x<<","<<m_mouseLocation.y<<")"<<endl;
  output<<"Left-click to Zoom in"<<endl;
  output<<"Right-click to Zoom out"<<endl;
  text.setString(output.str());
}
int  ComplexPlane::countIterations(Vector2f coord)
{
    // Initialize z as the complex number 0 + 0i
    float zReal = 0.0f;
    float zImag = 0.0f;

    size_t iterations = 0;

    // Iterate and check for escape
    while (iterations < MAX_ITER)
    {
        // Calculate z^2 + c
        float zRealNew = zReal * zReal - zImag * zImag + coord.x;
        float zImagNew = 2.0f * zReal * zImag + coord.y;

        // Check if the magnitude of z exceeds the escape radius (typically 2)
        if ((zRealNew * zRealNew + zImagNew * zImagNew) > 4.0f)
        {
            // Point escapes, return the number of iterations
            return iterations;
        }

        // Update z with the new values
        zReal = zRealNew;
        zImag = zImagNew;

        // Increment iteration count
        iterations++;
    }

    // If we reach the max iterations, the point is considered in the set
    return MAX_ITER;
}



void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
  if(count==MAX_ITER)//black
  {
    r=0;
    g=0;
    b=0;
  }
  //purple
  else if(count<MAX_ITER/5)
  {
    r=255;
    g=0;
    b=255;
  }
  //Turquoise
  else if(count<(MAX_ITER/5)*2)
  {
    r=64;
    g=224;
    b=208;
  }
  //green
  else if(count<(MAX_ITER/5)*3)
  {
    r=0;
    g=255;
    b=0;
  }
  //yellow
  else if(count<(MAX_ITER/5)*4)
  {
    r=255;
    g=255;
    b=0;
  }
  else
  {
    r=255;
    g=0;
    b=0;
  }
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
  double real=((mousePixel.x*1.0)/m_pixel_size.x)*m_plane_size.x+(m_plane_center.x - m_plane_size.x / 2.0);
  double imaginary=((m_pixel_size.y-(mousePixel.y*1.0))/(m_pixel_size.y)*m_plane_size.y+(m_plane_center.y - m_plane_size.y / 2.0));
  return Vector2f(real,imaginary);
}

