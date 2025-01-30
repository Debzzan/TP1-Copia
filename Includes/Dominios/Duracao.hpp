#ifndef DURACAO_DOMAIN_INTERFACE_H
#define DURACAO_DOMAIN_INTERFACE_H
#include "./Dominio.hpp"
#include <stdexcept>
#include <string>

using namespace std;

class Duracao : public Dominio
{
private:
    static const int DuracaoMinima = 0;
    static const int DuracaoMaxima = 360;

    void validar(string valor) override;

public:
    Duracao(string valor);
};

inline Duracao::Duracao(string valor)
{
    this->setValor(valor);
}

void Duracao::validar(string valor)
{
    int duration = stoi(valor);
    if (duration < DuracaoMinima || duration > DuracaoMaxima)
    {
        throw invalid_argument("Duração fora do intervalo permitido.");
    }
}

#endif // DURATION_DOMAIN_INTERFACE_H