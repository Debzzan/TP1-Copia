#ifndef SENHA_DOMAIN_INTERFACE_HPP
#define SENHA_DOMAIN_INTERFACE_HPP
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