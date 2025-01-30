#ifndef SENHA_DOMAIN_INTERFACE_H
#define SENHA_DOMAIN_INTERFACE_H
#include "./Dominio.hpp"

class Senha : public Dominio
{
private:
    void validar(string valor) override;

public:
    Senha(string valor);
};

inline Senha::Senha(string valor)
{
    this->setValor(valor);
}

#endif