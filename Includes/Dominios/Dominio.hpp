#ifndef DOMINIO_INTERFACE_HPP
#define DOMINIO_INTERFACE_HPP

#include <bits/stdc++.h>
#include <stdexcept>

using namespace std;

class Dominio
{
private:
    string valor;
    virtual void validar(string valor) = 0;

public:
    virtual ~Dominio() = default;
    void setValor(const string &valor);
    const string &getValor() const;
};

inline void Dominio::setValor(const string &valor)
{
    validar(valor);
    this->valor = valor;
}

inline const string &Dominio::getValor() const
{
    return this->valor;
}

#endif 