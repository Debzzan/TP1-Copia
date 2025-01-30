#ifndef AVALIACAO_DOMAIN_INTERFACE_H
#define AVALIACAO_DOMAIN_INTERFACE_H
#include "./Dominio.hpp"

class Avaliacao : public Dominio
{
private:
    void validar(string valor) override;

public:
    Avaliacao(string valor);
};

inline Avaliacao::Avaliacao(string valor)
{
    this->setValor(valor);
}

#endif