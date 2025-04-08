#ifndef CINFORETIROSTOTALESISSSTE_HPP_
#define CINFORETIROSTOTALESISSSTE_HPP_
#include "../definiciones.hpp"
#include "../struct.hpp"
#include "../../sisaforecoppel/funcionesgenerales/CFuncionesGenerales.hpp"

#include "../clasessql/CRetirostotalesissste.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>;
#include <string.h>;

class CInfoRetirosTotalesIssste 
{
private:	

public:
	CInfoRetirosTotalesIssste();
	~CInfoRetirosTotalesIssste();

	CFuncionesGenerales objFG;
	ST_SELLOBIOMETRICO_SUV	*stSelloBiometricoSuv;
		
	short ReplicarRetirosTotalesIssste(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore);
	void setStSelloBiometricoSuv(ST_SELLOBIOMETRICO_SUV *stSuv);
	void saveSelloBiometricoSuv(C_ODBC* odbcInfxSafreaf);

};
#endif
