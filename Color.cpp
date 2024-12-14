#include "Color.hpp"

// gerir comentário para todas as funções

namespace prog {
    Color::Color() {
        // as variáveis ficam com os valores 0.
        _red = 0;
        _green = 0;
        _blue = 0;
    }
    Color::Color(const Color& other) {
        // copia os valores da variável other para a variável this.
        _red = other._red;
        _green = other._green;
        _blue = other._blue;
    }
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        // as variáveis ficam com os valores passados como parâmetro.
        _red = red;
        _green = green;
        _blue = blue;
    }
    rgb_value Color::red() const {
        // retorna o valor da variável _red.
        return _red;
    }
    rgb_value Color::green() const {
        // retorna o valor da variável _green.
        return _green;
    }
    rgb_value Color::blue() const {
        // retorna o valor da variável _blue.
        return _blue;
    }

    rgb_value& Color::red()  {
        // retorna a referência ao valor da variável _red.
        return _red;
    }
    rgb_value& Color::green()  {
        // retorna a referência ao valor da variável _green.
        return _green;
    }
    rgb_value& Color::blue()  {
        // retorna a referência ao valor da variável _blue.
        return _blue;
    }
}
