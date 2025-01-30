#ifndef DOMINIO_INTERFACE_H
#define DOMINIO_INTERFACE_H

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
    void setValor(const string &value);
    const string &getValor() const;
};

inline void Dominio::setValor(const string &value)
{
    validar(valor);
    this->valor = valor;
}

inline const string &Dominio::getValor() const
{
    return this->valor;
}

#endif // DOMAIN_INTERFACE_H