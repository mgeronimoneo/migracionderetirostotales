#ifndef CINFORECSERVICIOSTIMBRADO_HPP_
#define CINFORECSERVICIOSTIMBRADO_HPP_
#include "../definiciones.hpp"
#include "../../sisaforecoppel/funcionesgenerales/CFuncionesGenerales.hpp"

#include "../clasessql/CTimbrado.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>;
#include <string.h>;

class CInfoRecServiciosTimbrado 
{
private:	

public:
	CInfoRecServiciosTimbrado();
	~CInfoRecServiciosTimbrado();

	CFuncionesGenerales objFG;
		
	short ReplicarRecServiciosTimbrado(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore);

};
#endif
