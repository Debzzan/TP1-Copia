#ifndef HORARIO_DOMAIN_INTERFACE_HPP
#define HORARIO_DOMAIN_INTERFACE_HPP

#include "./Dominio.hpp"

class Horario : public Dominio
{
private:
  static const int HoraMaxima = 23;
  static const int MinutoMaximo = 59;

  void validar(string valor) override;

public:
  Horario(string valor);
};

inline Horario::Horario(string valor)
{
  this->setValor(valor);
}

#endif