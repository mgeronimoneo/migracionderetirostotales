#include "CInfoRetNotifVivienda.hpp"

CInfoRetNotifVivienda::CInfoRetNotifVivienda()
{
	// TODO Auto-generated constructor stub
}

CInfoRetNotifVivienda::~CInfoRetNotifVivienda()
{
	// TODO Auto-generated destructor stub
}

short CInfoRetNotifVivienda::ReplicarRetNotifVivienda(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore)
{
	CRetnotificavivienda objRetNotViv(odbcServiciosAfore);

	char	cNss[13] = {0};
	//char	cFolionotifica[31] = {0};
	char 	cFoliooperacion[16] = {0};
	char	cClabe[16] = {0};
	char 	cGrupotrabajador[20] = {0};
	char	cSecpension[4] = {0};
	char	cRegimen[4] = {0};
	char	cTiporetiro[3] = {0};
	char	cTiposeguro[4] = {0};
	char	cTipopension[4] = {0};
	char	cTipoprestacion[4] = {0};
	char	cNombre[42] = {0};
	char	cPaterno[42] = {0};
	char	cMaterno[42] = {0};
	char	cRfc[15] = {0};
	char	cCurp[20] = {0};
	char	cNombrebenef[42] = {0};
	char	cPaternobenef[42] = {0};
	char	cMaternobenef[42] = {0};
	char	cRfcbenef[15] = {0};
	char	cCurpbenef[20] = {0};
	//char	cComentarios[129] = {0};
	//char	cReferenciapago[22] = {0};
	//char	cObservaciones[129] = {0};
	char	cFechacaptura[12] = {0};
	//char	cIndicador[3] = {0};
	//char	cDiaginfonavit[5] = {0};
	//char	cUsuariocarga[17] = {0};
	//char	cFechacarga[12] = {0};
	//char	cHoracarga[12] = {0};

	char cSql[2024] 		= {0};
	char cSqlAux[2024] 		= {0};
	char cTexto[2024] 		= {0};
	//char cTextoAux[2024] 	= {0};

	int 	iRespuesta = 9;

	objFG.fnArcGrabarLogx(RUTA_LOG,"***********************************ENTRA RET NOTIFICA VIVIENDA***************************************");
	memset(cTexto,0,sizeof(cTexto));
	snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "FOLIO QUE SE ESTA MIGRANDO: [%i]", iFolioServicio);
	objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

	//OBTENCIÓN DE LA INFORMACION QUE SE VA A MIGRAR DE RET CONSTANCIA RETENCION
	memset(cSql,0,sizeof(cSql));
	memset(cTexto,0,sizeof(cTexto));

	snprintf(cSql, strnlen(cSql, sizeof(cSql)), "SELECT  TRIM(COALESCE(cnss,''))::char(11) AS cnss, "
						       "COALESCE(bfoliocarga,0) AS bfoliocarga, "
						       "COALESCE(ifoliosolicitud,0) AS ifoliosolicitud, "
						       "COALESCE(bconsecutivo,0) AS bconsecutivo, "
						  //"TRIM(COALESCE(cfolionotifica,''))::char(29) AS cfolionotifica, "
						  "TRIM(COALESCE(cfoliooperacion,'')::char(14)) AS cfoliooperacion, "
						  "TRIM(COALESCE(cclabe,''))::char(18)::char(18) AS cclabe, "
						  "TRIM(COALESCE(cgrupotrabajador,''))::char(18) AS cgrupotrabajador, "
						  "TRIM(COALESCE(csecpension,''))::char(2) AS csecpension, "
						  "TRIM(COALESCE(cregimen,''))::char(2) AS cregimen, "
						  "TRIM(COALESCE(ctiporetiro,''))::char(1) AS ctiporetiro, "
						  "TRIM(COALESCE(ctiposeguro,''))::char(2) AS ctiposeguro, "
						  "TRIM(COALESCE(ctipopension,''))::char(2) AS ctipopension, "
						  "TRIM(COALESCE(ctipoprestacion,''))::char(2) AS ctipoprestacion, "
						       "COALESCE(isemanascotizadas,0) AS isemanascotizadas, "
						  "TRIM(COALESCE(cnombre,''))::char(40) AS cnombre, "
						  "TRIM(COALESCE(cpaterno,''))::char(40) AS cpaterno, "
						  "TRIM(COALESCE(cmaterno,''))::char(40) AS cmaterno, "
						  "TRIM(COALESCE(crfc,''))::char(13) AS crfc, "
						  "TRIM(COALESCE(ccurp,''))::char(18) AS ccurp, "
						       "COALESCE(ientidad,0) AS ientidad, "
						       "COALESCE(iidbenef,0) AS iidbenef, "
						  "TRIM(COALESCE(cnombrebenef,''))::char(40) AS cnombrebenef, "
						  "TRIM(COALESCE(cpaternobenef,''))::char(40) AS cpaternobenef, "
						  "TRIM(COALESCE(cmaternobenef,''))::char(40) AS cmaternobenef, "
						  "TRIM(COALESCE(crfcbenef,''))::char(13) AS crfcbenef, "
						  "TRIM(COALESCE(ccurpbenef,''))::char(18) AS ccurpbenef, "
						  //"TRIM(COALESCE(ccomentarios,''))::char(127) AS ccomentarios, "
						  //"TRIM(COALESCE(creferenciapago,''))::char(20) AS creferenciapago, "
						  //"TRIM(COALESCE(cobservaciones,''))::char(127) AS cobservaciones, "
						  "dfechacaptura::char(10) AS dfechacaptura "
						  //"TRIM(COALESCE(cindicador,''))::char(1) AS cindicador, "
						  //"TRIM(COALESCE(cdiaginfonavit,''))::char(3) AS cdiaginfonavit, "
						  //"TRIM(COALESCE(cusuariocarga,''))::char(15) AS cusuariocarga, "
						                //"dfechacarga::char(10) AS dfechacarga, "
						                //"thoracarga::char(8) AS thoracarga, "
						       //"COALESCE(iestado,0) AS iestado, " 
						       //"COALESCE(imigracionrettotsafre,0) AS imigracionrettotsafre "
						  "FROM fnconsultaretnotificaviviendareplicart(%i);",iFolioServicio);

	objRetNotViv.ClearResults();
	if(objRetNotViv.Exec(cSql))
	{
		objRetNotViv.activarCols();
		if(objRetNotViv.leer())
		{			
			memset(cNss, 0, sizeof(cNss));
			//memset(cFolionotifica, 0, sizeof(cFolionotifica));			
			memset(cFoliooperacion, 0, sizeof(cFoliooperacion));
			memset(cClabe, 0, sizeof(cClabe));
			memset(cGrupotrabajador, 0, sizeof(cGrupotrabajador));
			memset(cSecpension, 0, sizeof(cSecpension));
			memset(cRegimen, 0, sizeof(cRegimen));
			memset(cTiporetiro, 0, sizeof(cTiporetiro));
			memset(cTiposeguro, 0, sizeof(cTiposeguro));
			memset(cTipopension, 0, sizeof(cTipopension));
			memset(cTipoprestacion, 0, sizeof(cTipoprestacion));
		    memset(cNombre, 0, sizeof(cNombre));
		
			memset(cPaterno, 0, sizeof(cPaterno));
			memset(cMaterno, 0, sizeof(cMaterno));
			memset(cRfc, 0, sizeof(cRfc));
			memset(cCurp, 0, sizeof(cCurp));
			memset(cNombrebenef, 0, sizeof(cNombrebenef));
			memset(cPaternobenef, 0, sizeof(cPaternobenef));
			memset(cMaternobenef, 0, sizeof(cMaternobenef));
			memset(cRfcbenef, 0, sizeof(cRfcbenef));
			memset(cCurpbenef, 0, sizeof(cCurpbenef));
			//memset(cComentarios, 0, sizeof(cComentarios));			
			//memset(cReferenciapago, 0, sizeof(cReferenciapago));			
			//memset(cObservaciones, 0, sizeof(cObservaciones));			
			memset(cFechacaptura, 0, sizeof(cFechacaptura));			
			//memset(cIndicador, 0, sizeof(cIndicador));			
			//memset(cDiaginfonavit, 0, sizeof(cDiaginfonavit));
			//memset(cUsuariocarga, 0, sizeof(cUsuariocarga));			
			//memset(cFechacarga, 0, sizeof(cFechacarga));			
			//memset(cHoracarga, 0, sizeof(cHoracarga));

			memmove(cNss, objRetNotViv.cNss, sizeof(11));
			//memcpy(cFolionotifica, objRetNotViv.cFolionotifica, 29);
			memmove(cFoliooperacion, objRetNotViv.cFoliooperacion, sizeof(14));
			memmove(cClabe, objRetNotViv.cClabe, sizeof(18));
			memmove(cGrupotrabajador, objRetNotViv.cGrupotrabajador, sizeof(18));
			memmove(cSecpension, objRetNotViv.cSecpension, sizeof(2));
			memmove(cRegimen, objRetNotViv.cRegimen, sizeof(2));
			memmove(cTiporetiro, objRetNotViv.cTiporetiro, sizeof(1));
			memmove(cTiposeguro, objRetNotViv.cTiposeguro, sizeof(2));
			memmove(cTipopension, objRetNotViv.cTipopension, sizeof(2));
			memmove(cTipoprestacion, objRetNotViv.cTipoprestacion, sizeof(2));
			memmove(cNombre, objRetNotViv.cNombre, sizeof(40));
			memmove(cPaterno, objRetNotViv.cPaterno, sizeof(40));
			memmove(cMaterno, objRetNotViv.cMaterno, sizeof(40));
			memmove(cRfc, objRetNotViv.cRfc, sizeof(13));
			memmove(cCurp, objRetNotViv.cCurp, sizeof(18));
			memmove(cNombrebenef, objRetNotViv.cNombrebenef, sizeof(40));
			memmove(cPaternobenef, objRetNotViv.cPaternobenef, sizeof(40));
			memmove(cMaternobenef, objRetNotViv.cMaternobenef, sizeof(40));
			memmove(cRfcbenef, objRetNotViv.cRfcbenef, sizeof(13));
			memmove(cCurpbenef, objRetNotViv.cCurpbenef, sizeof(18));
			//memcpy(cComentarios, objRetNotViv.cComentarios, 127);
			//memcpy(cReferenciapago, objRetNotViv.cReferenciapago, 20);
			//memcpy(cObservaciones, objRetNotViv.cObservaciones, 127);

			//memcpy(cFechacaptura, objRetNotViv.cFechacaptura, 10);			
			snprintf(cFechacaptura, strnlen(cFechacaptura, sizeof(cFechacaptura)), "%c%c,%c%c,%c%c%c%c",
					objRetNotViv.cFechacaptura[5], 
					objRetNotViv.cFechacaptura[6],
					objRetNotViv.cFechacaptura[8], 
					objRetNotViv.cFechacaptura[9],
					objRetNotViv.cFechacaptura[0],
					objRetNotViv.cFechacaptura[1],
					objRetNotViv.cFechacaptura[2],
					objRetNotViv.cFechacaptura[3]);			

			//memcpy(cIndicador, objRetNotViv.cIndicador, 1);
			//memcpy(cDiaginfonavit, objRetNotViv.cDiaginfonavit, 3);
			//memcpy(cUsuariocarga, objRetNotViv.cUsuariocarga, 15);

			//memcpy(cFechacarga, objRetNotViv.cFechacarga, 10);
			/*sprintf(cFechacarga, "MDY(%c%c,%c%c,%c%c%c%c)",
					objRetNotViv.cFechacarga[5], 
					objRetNotViv.cFechacarga[6],
					objRetNotViv.cFechacarga[8], 
					objRetNotViv.cFechacarga[9],
					objRetNotViv.cFechacarga[0],
					objRetNotViv.cFechacarga[1],
					objRetNotViv.cFechacarga[2],
					objRetNotViv.cFechacarga[3]);*/

			//memcpy(cHoracarga, objRetNotViv.cHoracarga, 8);

			if (objRetNotViv.iFoliosolicitud == 0)
			{
				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "NO EXISTE INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
				objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
			}
			else
			{
				memset(cSqlAux,0, sizeof(cSqlAux));
				memset(cTexto,0, sizeof(cTexto));

				snprintf(cSqlAux, strnlen(cSqlAux, sizeof(cSqlAux)), "EXECUTE FUNCTION fn_guardarretiroamparopension_viviendareplicart(%i,'%s',%i,'%s','%s','%s','%s','%s','%s','%s','%s','%s',%i,'%s','%s','%s','%s','%s',%i,%i,'%s','%s','%s','%s','%s','%s');",
													objRetNotViv.iFoliocarga,
													cNss,
													objRetNotViv.iConsecutivo,
													cFoliooperacion,
													cClabe,
													cGrupotrabajador,
													cSecpension,
													cRegimen,
													cTiporetiro,
													cTiposeguro,
													cTipopension,
													cTipoprestacion,
													objRetNotViv.iSemanascotizadas,
													cNombre,
													cPaterno,
													cMaterno,
													cRfc,
													cCurp,
													objRetNotViv.iEntidad,
													objRetNotViv.iIdbenef,
													cNombrebenef,
													cPaternobenef,
													cMaternobenef,
													cRfcbenef,
													cCurpbenef,
													cFechacaptura
													);																

				objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSqlAux, iRespuesta, cTexto);

				if (iRespuesta == 1)
				{
					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "SE MIGRO LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
					objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
				}
				else
				{
					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "NO SE PUDO MIGRAR LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);			

					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "QUERY: [%s]", cSqlAux);					
					
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
					objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
				}
			}
		}
		else
		{
			memset(cTexto, 0, sizeof(cTexto));
			snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Error al leer la informacion que arroja el query: %s %i %s", __FILE__,__FUNCTION__, cSql, errno, strerror(errno));
			objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
		}
	}
	else
	{
		memset(cTexto, 0, sizeof(cTexto));
		snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Error al Ejecutar el Query: %s %i %s", __FILE__,__FUNCTION__, cSql, errno, strerror(errno));
		objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
	}
}