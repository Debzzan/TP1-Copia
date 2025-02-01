#ifndef DESTINO_AMBIENTE_INTERFACE_HPP
#define DESTINO_AMBIENTE_INTERFACE_HPP

#include "../Interfaces/Apresentacao.hpp"
#include "../Interfaces/Servicos.hpp"

class AmbienteDestino : public InterfaceApresentacao
{
private:
  InterfaceServicoDestino *ServicoDestino;

public:
    AmbienteDestino(Codigo &CodigoUsuario) : InterfaceApresentacao(CodigoUsuario) {};
    
    void setServicoDestino(InterfaceServicoDestino *ServicoDestino)
    {
        this->ServicoDestino = ServicoDestino;
    };
    
    void Executar(Codigo &CodigoUsuario) override;
    
    void Criar();
    
    void Atualizar();
    
    void Remover();
    
    void Ler();
    
    ~AmbienteDestino() override
    {
        delete ServicoDestino;

    }
    
};

#endif 