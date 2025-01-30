#ifndef NOME_DOMAIN_INTERFACE_H
#define NOME_DOMAIN_INTERFACE_H
#include "./Dominio.hpp"

class Nome : public Dominio
{
private:
    void validar(string valor) override;

public:
    Nome(string valor);
};

inline Nome::Nome(string valor)

{
    this->setValor(valor);
}

#endif