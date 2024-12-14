#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"

namespace prog
{
  class Image
  {
  private:
    int _width; // largura da imagem
    int _height; // altura da imagem
    Color**_pixels; // matriz de pixels
  public:
    Image(int w, int h, const Color &fill = {255, 255, 255}); // construtor
    ~Image(); // destrutor
    int width() const; // retorna a largura da imagem.
    int height() const; // retorna a altura da imagem.
    Color &at(int x, int y); // retorna a referência ao pixel (x, y).
    const Color &at(int x, int y) const; // retorna a referência constante ao pixel (x, y).
  };
}
#endif
