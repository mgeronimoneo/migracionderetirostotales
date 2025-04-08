#ifndef CINFORETCONFORMIDAD_HPP_
#define CINFORETCONFORMIDAD_HPP_
#include "../definiciones.hpp"
#include "../../sisaforecoppel/funcionesgenerales/CFuncionesGenerales.hpp"

#include "../clasessql/CRetftoconformidad.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>;
#include <string.h>;

class CInfoRetConformidad 
{
private:	

public:
	CInfoRetConformidad();
	~CInfoRetConformidad();

	CFuncionesGenerales objFG;
		
	short ReplicarRetConformidad(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore);

};
#endif
