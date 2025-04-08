#ifndef CINFORETCONSTANCIARETENCION_HPP_
#define CINFORETCONSTANCIARETENCION_HPP_
#include "../definiciones.hpp"
#include "../../sisaforecoppel/funcionesgenerales/CFuncionesGenerales.hpp"

#include "../clasessql/CRetconstanciaretencion.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>;
#include <string.h>;

class CInfoRetConstanciaRetencion 
{
private:	

public:
	CInfoRetConstanciaRetencion();
	~CInfoRetConstanciaRetencion();

	CFuncionesGenerales objFG;
		
	short ReplicarRetConstanciaRetencion(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore);

};
#endif
