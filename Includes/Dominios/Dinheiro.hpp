#ifndef MONEY_DOMAIN_INTERFACE_H
#define MONEY_DOMAIN_INTERFACE_H
#include "./Dominio.hpp"

class Dinheiro : public Dominio
{
private:
    static constexpr float DinheiroMaximo = 200000.00;
    static constexpr float DinheiroMinimo = 0.00;

    void validar(string valor) override;

public:
    Dinheiro(string valor);
};

inline Dinheiro::Dinheiro(string valor)
{
    this->setValor(valor);
}

#endif // MONEY_DOMAIN_INTERFACE_H