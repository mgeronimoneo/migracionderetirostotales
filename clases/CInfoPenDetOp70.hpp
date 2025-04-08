#ifndef CINFOPENDETOP70_HPP_
#define CINFOPENDETOP70_HPP_
#include "../definiciones.hpp"
#include "../../sisaforecoppel/funcionesgenerales/CFuncionesGenerales.hpp"

#include "../clasessql/CPendetalleop70.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>;
#include <string.h>;

class CInfoPenDetOp70 
{
private:	

public:
	CInfoPenDetOp70();
	~CInfoPenDetOp70();

	CFuncionesGenerales objFG;
		
	short ReplicarDetalleOp70(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore);	

};
#endif
