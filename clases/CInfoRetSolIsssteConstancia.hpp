#ifndef CINFORETSOLISSSTECONSTANCIA_HPP_
#define CINFORETSOLISSSTECONSTANCIA_HPP_
#include "../definiciones.hpp"
#include "../../sisaforecoppel/funcionesgenerales/CFuncionesGenerales.hpp"

#include "../clasessql/CRetirostotalesconstanciaissste.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>;
#include <string.h>;

class CInfoRetSolIsssteConstancia 
{
private:	

public:
	CInfoRetSolIsssteConstancia();
	~CInfoRetSolIsssteConstancia();

	CFuncionesGenerales objFG;
		
	short ReplicarRetSolIsssteConstancia(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore);

};
#endif
