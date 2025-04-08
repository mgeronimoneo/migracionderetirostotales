#ifndef CINFORETTOTPMGIMSS_HPP_
#define CINFORETTOTPMGIMSS_HPP_
#include "../definiciones.hpp"
#include "../struct.hpp"
#include "../../sisaforecoppel/funcionesgenerales/CFuncionesGenerales.hpp"

#include "../clasessql/CRetirostotalespmgimss.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>;
#include <string.h>;

class CInfoRetTotPmgImss 
{
private:	

public:
	CInfoRetTotPmgImss();
	~CInfoRetTotPmgImss();

	CFuncionesGenerales objFG;
	ST_SELLOBIOMETRICO_SUV	*stSelloBiometricoSuv;
		
	short ReplicarRetirosTotalesPmgImss(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore);
	void setStSelloBiometricoSuv(ST_SELLOBIOMETRICO_SUV *stSuv);
	void saveSelloBiometricoSuv(C_ODBC* odbcInfxSafreaf, int iTipo);
};
#endif
