#ifndef CODIGO_DOMAIN_INTERFACE_HPP
#define CODIGO_DOMAIN_INTERFACE_HPP
#include "./Dominio.hpp"

class Codigo : public Dominio
{
private:
  static const int TamanhoCodigo = 6;

  void validar(string valor) override;

public:
  Codigo();
  Codigo(string valor);
  static string GerarCodigoAleatorio();
};

inline Codigo::Codigo(string valor)
{
  this->setValor(valor);
}

#endif 