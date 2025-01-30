#ifndef CODIGO_DOMAIN_INTERFACE_H
#define CODIGO_DOMAIN_INTERFACE_H
#include "./Dominio.hpp"

class Codigo : public Dominio
{
private:
  static const int TamanhoCodigo = 6;

  void validar(string value) override;

public:
  Codigo();
  Codigo(string value);
  static string GerarCodigoAleatorio();
};

inline Codigo::Codigo(string valor)
{
  this->setValor(valor);
}

#endif // CODE_DOMAIN_INTERFACE_H