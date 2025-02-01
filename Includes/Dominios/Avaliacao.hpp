#ifndef AVALIACAO_DOMAIN_INTERFACE_HPP
#define AVALIACAO_DOMAIN_INTERFACE_HPP
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