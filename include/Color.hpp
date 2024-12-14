#ifndef __prog_Color_hpp__
#define __prog_Color_hpp__

namespace prog
{
  typedef unsigned char rgb_value; // tipo de dados para as cores.
  class Color
  {
    private:
    // variáveis que guardam os valores de cada cor.
      rgb_value _red;
      rgb_value _green;
      rgb_value _blue;
    public:
      Color(); // construtor
      Color(const Color& c); // construtor de cópia
      Color(rgb_value r, rgb_value g, rgb_value b); // construtor com parâmetros
      rgb_value red() const; // retorna o valor da variável _red.
      rgb_value& red(); // retorna a referência ao valor da variável _red.
      rgb_value green() const; // retorna o valor da variável _green.
      rgb_value& green(); // retorna a referência ao valor da variável _green.
      rgb_value blue() const; // retorna o valor da variável _blue.
      rgb_value& blue(); // retorna a referência ao valor da variável _blue.
  };
}
#endif
