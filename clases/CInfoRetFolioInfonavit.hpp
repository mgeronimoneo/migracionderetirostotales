#ifndef CINFORETFOLIOINFONAVIT_HPP_
#define CINFORETFOLIOINFONAVIT_HPP_
#include "../definiciones.hpp"
#include "../../sisaforecoppel/funcionesgenerales/CFuncionesGenerales.hpp"

#include "../clasessql/CRetfolioinfonavit.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>;
#include <string.h>;

class CInfoRetFolioInfonavit 
{
private:	

public:
	CInfoRetFolioInfonavit();
	~CInfoRetFolioInfonavit();

	CFuncionesGenerales objFG;
		
	short ReplicarRetFolioInfonavit(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore);

};
#endif
