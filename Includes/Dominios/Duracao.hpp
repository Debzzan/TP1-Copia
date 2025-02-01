#ifndef DURACAO_DOMAIN_INTERFACE_HPP
#define DURACAO_DOMAIN_INTERFACE_HPP
#include "./Dominio.hpp"
#include <stdexcept>
#include <string>

using namespace std;

class Duracao : public Dominio
{
private:
    static const int DuracaoMinima = 0;
    static const int DuracaoMaxima = 360;

    void validar(string valor) override;

public:
    Duracao(string valor);
};

inline Duracao::Duracao(string valor)
{
    this->setValor(valor);
}


#endif 