#ifndef CONTA_ENTITY_INTERFACE_H
#define CONTA_ENTITY_INTERFACE_H

#include "../Dominios/Codigo.hpp"
#include "../Dominios/Senha.hpp"
#include "./Entidade.hpp"

class Conta : public Entidade
{
private:
    Codigo codigo;
    Senha senha;

public:
    Conta(const Codigo &codigo, const Senha &senha);

    void set(const Dominio &dominio, string NomeProprio) override;

    const Dominio &get(const string NomeProprio) const override;
};

#endif 