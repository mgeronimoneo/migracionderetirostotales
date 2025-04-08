#ifndef CINFOBENEFICIARIOS_HPP_
#define CINFOBENEFICIARIOS_HPP_
#include "../definiciones.hpp"
#include "../../sisaforecoppel/funcionesgenerales/CFuncionesGenerales.hpp"

#include "../clasessql/CBeneficiario.hpp"
#include "../clasessql/CControlBeneficiario.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>;
#include <string.h>;

class CInfoBeneficiarios 
{
private:	

public:
	CInfoBeneficiarios();
	~CInfoBeneficiarios();

	CFuncionesGenerales objFG;
		
	short ReplicarBeneficiarios(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore);
	void replicaControlBeneficiarios(int iFolioServicio, int iConsecutivo, int iCodigoMotivo, char *cTipoRetiro, C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore);

};
#endif
