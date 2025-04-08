#ifndef CINFORETNOTIFVIVIENDA_HPP_
#define CINFORETNOTIFVIVIENDA_HPP_
#include "../definiciones.hpp"
#include "../../sisaforecoppel/funcionesgenerales/CFuncionesGenerales.hpp"

#include "../clasessql/CRetnotificavivienda.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>;
#include <string.h>;

class CInfoRetNotifVivienda
{
private:	

public:
	CInfoRetNotifVivienda();
	~CInfoRetNotifVivienda();

	CFuncionesGenerales objFG;
		
	short ReplicarRetNotifVivienda(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore);

};
#endif
