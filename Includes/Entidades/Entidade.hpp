#ifndef ENTIDADE_INTERFACE_H
#define ENTIDADE_INTERFACE_H

#include "../Dominios/Dominio.hpp"

class Entidade
{
private:
public:
  virtual ~Entidade() = default;

  virtual void set(const Dominio &dominio, string NomeProprio) = 0;

  virtual const Dominio &get(const string NomeProprio) const = 0;
};

#endif 