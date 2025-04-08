#ifndef CINFOSOLICITANTE_HPP_
#define CINFOSOLICITANTE_HPP_
#include "../definiciones.hpp"
#include "../../sisaforecoppel/funcionesgenerales/CFuncionesGenerales.hpp"

#include "../clasessql/CSolicitante.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>;
#include <string.h>;

class CInfoSolicitante
{
private:	

public:
	CInfoSolicitante();
	~CInfoSolicitante();

	CFuncionesGenerales objFG;
		
	short ReplicarSolicitante(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore);

};
#endif
