#ifndef APRESENTACAO_INTERFACE_H
#define APRESENTACAO_INTERFACE_H

#include "../Dominios/Codigo.hpp"

class InterfaceApresentacao
{
protected:
  Codigo &CodigoUsuario;

public:
  InterfaceApresentacao(Codigo &CodigoUsuario) : CodigoUsuario(CodigoUsuario) {}

  virtual void Executar(Codigo &CodigoUsuario) = 0;
  virtual ~InterfaceApresentacao() {};
};

#endif 