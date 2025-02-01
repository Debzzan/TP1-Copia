#ifndef DESTINO_ENTITY_INTERFACE_H
#define DESTINO_ENTITY_INTERFACE_H

#include "../Dominios/Codigo.hpp"
#include "../Dominios/Nome.hpp"
#include "../Dominios/Data.hpp"
#include "../Dominios/Avaliacao.hpp"
#include "./Entidade.hpp"


class Destino : public Entidade
{
private:

    Codigo codigo;
    Nome nome;
    Data chegada;
    Avaliacao avaliacao;
    Data partida;


public:
    Destino(const Codigo &codigo, const Nome &nome, const Data &chegada, const Data &partida, const Avaliacao &avaliacao);

    void set(const Dominio &dominio, string NomeProprio) override;

    const Dominio &get(const string NomeProprio) const override;
};

#endif 