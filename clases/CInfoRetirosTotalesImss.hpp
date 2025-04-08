#ifndef CINFORETIROSTOTALESIMSS_HPP_
#define CINFORETIROSTOTALESIMSS_HPP_
#include "../definiciones.hpp"
#include "../struct.hpp"
#include "../../sisaforecoppel/funcionesgenerales/CFuncionesGenerales.hpp"

#include "../clasessql/CRetirostotalesimss.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>;
#include <string.h>;

class CInfoRetirosTotalesImss 
{
private:	

public:
	CInfoRetirosTotalesImss();
	~CInfoRetirosTotalesImss();

	CFuncionesGenerales objFG;
	ST_SELLOBIOMETRICO_SUV *stSelloBiometricoSuv;
		
	short ReplicarRetirosTotalesImss(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore);
	void setStSelloBiometricoSuv(ST_SELLOBIOMETRICO_SUV *stSuv);
	void saveSelloBiometricoSuv(C_ODBC* odbcInfxSafreaf);
};
#endif
