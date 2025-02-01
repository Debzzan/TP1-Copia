#ifndef CONTROLADORA_INTERFACE_H
#define CONTROLADORA_INTERFACE_H

#include "./Interfaces/Apresentacao.hpp"

/**
 * @class Controladora
 * @brief Classe responsável por controlar os ambientes de apresentação.
 * 
 * Esta classe gerencia as diferentes interfaces de apresentação, como conta, viagem, destino, hospedagem e atividade.
 */
class Controladora
{
private:
    InterfaceApresentacao *AmbienteConta; ///< Ponteiro para o ambiente de apresentação de conta.
    InterfaceApresentacao *AmbienteViagem; ///< Ponteiro para o ambiente de apresentação de viagem.
    InterfaceApresentacao *AmbienteDestino; ///< Ponteiro para o ambiente de apresentação de destino.
    InterfaceApresentacao *AmbienteHospedagem; ///< Ponteiro para o ambiente de apresentação de hospedagem.
    InterfaceApresentacao *AmbienteAtividade; ///< Ponteiro para o ambiente de apresentação de atividade. 

public:
    Codigo CodigoUsuario = Codigo("000000"); ///< Código do usuário.
    
    /**
     * @brief Destrutor da classe Controladora.
     */
    ~Controladora();

    /**
     * @brief Define o ambiente de apresentação de conta.
     * @param AmbienteConta Ponteiro para o ambiente de apresentação de conta.
     */
    void setAmbienteConta(InterfaceApresentacao *AmbienteConta);

    /**
     * @brief Define o ambiente de apresentação de viagem.
     * @param AmbienteViagem Ponteiro para o ambiente de apresentação de viagem.
     */
    void setAmbienteViagem(InterfaceApresentacao *AmbienteViagem);

    /**
     * @brief Define o ambiente de apresentação de destino.
     * @param AmbienteDestino Ponteiro para o ambiente de apresentação de destino.
     */
    void setAmbienteDestino(InterfaceApresentacao *AmbienteDestino);

    /**
     * @brief Define o ambiente de apresentação de hospedagem.
     * @param AmbienteHospedagem Ponteiro para o ambiente de apresentação de hospedagem.
     */
    void setAmbienteHospedagem(InterfaceApresentacao *AmbienteHospedagem);

    /**
     * @brief Define o ambiente de apresentação de atividade.
     * @param AmbienteAtividade Ponteiro para o ambiente de apresentação de atividade.
     */
    void setAmbienteAtividade(InterfaceApresentacao *AmbienteAtividade);

    /**
     * @brief Executa a controladora.
     */
    void Executar();
};

#endif