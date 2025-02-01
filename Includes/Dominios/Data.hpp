#ifndef DATA_DOMAIN_INTERFACE_HPP
#define DATA_DOMAIN_INTERFACE_HPP
#include "./Dominio.hpp"

class Data: public Dominio
{
private:
  static const int DiasFevereiroBIS = 29;
  static const int DiasFevereiroNORMAL = 28;
  static const vector<int> DiasMes;
  static const int MesMaximo = 12;
  static const int AnoMaximo = 99;

  void validar(string valor) override;

public:
  Data(string valor);

  static int CalcularAlcanceDatas(string DataInicial, string DataFinal);

  static bool AlcanceDatas(string date, string DataInicial, string DataFinal);
};

inline Data::Data(string valor)
{
  this->setValor(valor);
}

#endif 