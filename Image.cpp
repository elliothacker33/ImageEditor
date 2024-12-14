#include "Image.hpp"

// An Image object represents an image. It has an associated width (width()) and height (height()), and must hold a 2D matrix of colors with these dimensions. Each (x, y) position in this matrix, where 0 <= x < width() and 0 <= y < height(), is called a pixel. Pixel (0,0) corresponds to the upper-left corner of the image, and pixel (width() - 1, height() - 1) corresponds to the lower-right corner of the image, as illustrated in Figure 2 below.
// What must be done?
// You should define appropriate fields to represent the image dimensions and the pixel matrix, and implement the member functions already provided in the initial skeleton. These are described in Table 4.
// If you find it necessary, you may define other member functions in the class.

namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    // Create image with width w, height h, and all pixels set to color fill. White is the default fill value, i.e., (255, 255, 255).
    _width=w;
    _height=h;
    _pixels=new Color*[_width];
    for(int i=0;i<_width;++i){
      _pixels[i]=new Color[_height];
    }
    for(int i=0;i<_width;++i){
      for(int j=0;j<_height;++j){
        _pixels[i][j]=fill;
      }
    }
   
  }
  // Destroy allocated space for Image
  Image::~Image()
  {
       for (int i = 0; i < _width; ++i) {
        delete[] _pixels[i];
      }
    delete[] _pixels;
  }
  // Getter for width field
  int Image::width() const
  {
    return _width;
  }
  // Getter for height field
  int Image::height() const
  {
    return _height;
  }
  // Return a reference to the pixel (x, y). If x or y are out of bounds, throw an std::out_of_range exception.
  Color &Image::at(int x, int y)
  {
    return _pixels[x][y];
  }
  // Return a const reference to the pixel (x, y). If x or y are out of bounds, throw an std::out_of_range exception.
  const Color &Image::at(int x, int y) const
  {
    return _pixels[x][y];
  }
}