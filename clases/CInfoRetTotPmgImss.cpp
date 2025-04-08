#include "CInfoRetTotPmgImss.hpp"

CInfoRetTotPmgImss::CInfoRetTotPmgImss()
{
	// TODO Auto-generated constructor stub
}

CInfoRetTotPmgImss::~CInfoRetTotPmgImss()
{
	// TODO Auto-generated destructor stub
}
void CInfoRetTotPmgImss::setStSelloBiometricoSuv(ST_SELLOBIOMETRICO_SUV *stSuv)
{	
	char cTexto[5000] 		= {0};
	stSelloBiometricoSuv 	= stSuv;
	//memcpy(stSelloBiometricoSuv,stSuv,sizeof(stSuv));
	snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] stSelloBiometricoSuv: cNss[%s] iIdsolicitante[%i] cCurpSolicitante[%s] cSellotrabajador[%s] cCurpAgente[%s] iConsecutivo[%i]", __FILE__,__FUNCTION__,stSelloBiometricoSuv->cNss,stSelloBiometricoSuv->iIdsolicitante,stSelloBiometricoSuv->cCurpSolicitante,stSelloBiometricoSuv->cSellotrabajador,stSelloBiometricoSuv->cCurpAgente,stSelloBiometricoSuv->iConsecutivo);
	objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
}///Termina CInfoRetTotPmgImss::setStSelloBiometricoSuv(ST_SELLOBIOMETRICO_SUV *stSuv)

void CInfoRetTotPmgImss::saveSelloBiometricoSuv(C_ODBC *odbcInfxSafreaf, int iTipo)
{
	objFG.fnArcGrabarLogx(RUTA_LOG,"=========== TABLA : RET_SELLOSBIOMETRICOS_SUV ===========");
	char cSql[5000] 		= {0};
	char cTexto[5000] 		= {0};
	char cAux[5000]		= {0};
	int shRespuesta		=  0;

	memset(cSql,0, sizeof(cSql));
	memset(cTexto,0, sizeof(cTexto));	
	
	snprintf(cSql, strnlen(cSql, sizeof(cSql)), "EXECUTE FUNCTION fn_guardar_sellosuvtrabajador(3,'%s',%i,'%i','%s','%s','%s',%i);",
	stSelloBiometricoSuv->cNss, stSelloBiometricoSuv->iConsecutivo, stSelloBiometricoSuv->iIdsolicitante, stSelloBiometricoSuv->cCurpSolicitante, 
	stSelloBiometricoSuv->cSellotrabajador, stSelloBiometricoSuv->cCurpAgente,/*stSelloBiometricoSuv->cCurpSolBene,*/iTipo);	
	
	snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "QUERY: [%s]", cSql);
	objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
	
	objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSql, shRespuesta, cAux);	
	
	if (shRespuesta == 1)
	{
		snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "SE MIGRO LA INFORMACION CON EL CONSECUTIVO: [%i]", stSelloBiometricoSuv->iConsecutivo);
		objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
	}
	else
	{
		snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "NO SE PUDO MIGRAR LA INFORMACION CON EL CONSECUTIVO: [%i]", stSelloBiometricoSuv->iConsecutivo);
		objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);	
	}
}///Termina CInfoRetTotPmgImss::saveSelloBiometricoSuv()

short CInfoRetTotPmgImss::ReplicarRetirosTotalesPmgImss(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore)
{
	CRetirostotalespmgimss objRetTotPmg(odbcServiciosAfore);
	
	/*pensolicitudpmgimss*/
	char cNss[13] 					= {0};
    char cCurp[20] 					= {0};
    char cSecpension[4] 				= {0};
    char cTiporetiro[3] 				= {0};
    char cRegimen[4] 				= {0};
    char cTiposeguro[4] 				= {0};
    char cTipopension[4] 				= {0};    
    char cFechainipen[17] 			= {0};
    char cFecharesolucion[17] 			= {0};
    char cFechasolicitud[17] 			= {0};
    char cFechapago[17] 				= {0};
    char cDiagregistro[5] 			= {0};
    char cFechacaptura[17] 			= {0};
    char cHoracaptura[10] 			= {0};
    char cUsuariocaptura[17] 			= {0};
    char cFechamodifica[17] 			= {0};
    char cHoramodifica[10] 			= {0};
    char cUsuariomodifica[17] 			= {0};
    char cFechaconfirma[17] 			= {0};
    char cHoraconfirma[10] 			= {0};
    char cUsuarioconfirma[17] 		= {0};
    /*************************/
    
    /*penctrpagodetimss*/
    char cNssctrdet[13]				= {0};
    char cFechapagoestimada[12] 		= {0};
    char cFecharecibeop79[12] 		= {0};
    char cFechaliquida[12] 			= {0};
    char cMarcaultpago[3]	 		= {0};
    int iTipocontrato = 0;
    /********************/

    /*penctrpagoimss*/
    char cNssctr[13]					= {0};
    /****************/

    char cSql[50000] 				= {0};
    char cTexto[5000] 				= {0};

	char cSqlTb1[5000] 			= {0};
	char cTextoTb1[5000] 			= {0};

	char cSqlTb2[5000] 			= {0};
	char cTextoTb2[5000] 			= {0};

	char cSqlTb3[5000] 			= {0};
	char cTextoTb3[5000] 			= {0};

	int iRespuestaTb1 				= 0;
	int iRespuestaTb2 				= 0;
	int iRespuestaTb3 				= 0;

	
	


	objFG.fnArcGrabarLogx(RUTA_LOG,"***********************************ENTRA PMG IMSS***************************************");
	memset(cTexto,0,sizeof(cTexto));
	snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "FOLIO QUE SE ESTA MIGRANDO: [%i]", iFolioServicio);
	objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

	//OBTENCIÓN DE LA INFORMACION QUE SE VA A MIGRAR DE PMG IMSS
	memset(cSql,0,sizeof(cSql));
	memset(cTexto,0,sizeof(cTexto));	
	
	snprintf(cSql, strnlen(cSql, sizeof(cSql)),   "SELECT TRIM(COALESCE(nss,' '))::Char(11) AS nss, "
					"COALESCE(consecutivo,0) AS consecutivo, "
					"COALESCE(seccontrato,0) AS seccontrato, "
					"COALESCE(foliocontrato,0) AS foliocontrato, "
					"COALESCE(foliolote,0) AS foliolote, "
					"COALESCE(foliosolicitud,0) AS foliosolicitud, "
					"TRIM(COALESCE(curp,' '))::Char(18) AS curp, "
					"TRIM(COALESCE(secpension,' '))::Char(2) AS secpension, "
					"TRIM(COALESCE(tiporetiro,' '))::Char(1) AS tiporetiro, "
					"TRIM(COALESCE(regimen,' '))::Char(2) AS regimen, "
					"TRIM(COALESCE(tiposeguro,' '))::Char(2) AS tiposeguro, "
					"TRIM(COALESCE(tipopension,' '))::Char(2) AS tipopension, "
					"COALESCE(tipoprestacion,0) AS tipoprestacion, "
					"COALESCE(importemensual,0.0) AS importemensual, "
					"TRIM(COALESCE(fechainipen,' '))::Char(10) AS fechainipen, "
					"TRIM(COALESCE(fecharesolucion,' '))::Char(10) AS fecharesolucion, "
					"TRIM(COALESCE(fechasolicitud,' '))::Char(10) AS fechasolicitud, "
					"TRIM(COALESCE(fechapago,' '))::Char(10) AS fechapago, "
					"COALESCE(estadosubviv,0) AS estadosubviv, "
					"TRIM(COALESCE(diagregistro,' '))::Char(3) AS diagregistro, "
					"COALESCE(grupo,0) AS grupo, "
					"TRIM(COALESCE(fechacaptura,' '))::Char(10) AS fechacaptura, "
					"TRIM(COALESCE(horacaptura,' '))::Char(8) AS horacaptura, "
					"TRIM(COALESCE(usuariocaptura,' '))::Char(15) AS usuariocaptura, "
					"TRIM(COALESCE(fechamodifica,' '))::Char(10) AS fechamodifica, "
					"TRIM(COALESCE(horamodifica,' '))::Char(8) AS horamodifica, "
					"TRIM(COALESCE(usuariomodifica,' '))::Char(15) AS usuariomodifica, "
					"TRIM(COALESCE(fechaconfirma,' '))::Char(10) AS fechaconfirma, "
					"TRIM(COALESCE(horaconfirma,' '))::Char(8) AS horaconfirma, "
					"TRIM(COALESCE(usuarioconfirma,' '))::Char(15) AS usuarioconfirma, "
					"COALESCE(codigorechazo,0) AS codigorechazo, "
					"COALESCE(estadosolicitud,0) AS estadosolicitud, "
					"COALESCE(foliosolicitudctrdet,0) AS foliosolicitudctrdet, "							  
					"TRIM(COALESCE(nssctrdet,' '))::Char(11) AS nssctrdet, "
					"COALESCE(consecutivoctrdet,0) AS consecutivoctrdet, "
					"COALESCE(seccontratoctrdet,0) AS seccontratoctrdet, "
					"COALESCE(folioop78,0) AS folioop78, "
					"COALESCE(folioliquida,0) AS folioliquida, "						      
					"TRIM(COALESCE(fechapagoestimada,' '))::Char(10) AS fechapagoestimada, "
					"TRIM(COALESCE(fecharecibeop79,' '))::Char(10) AS fecharecibeop79, "
					"TRIM(COALESCE(fechaliquida,' '))::Char(10) AS fechaliquida, "
					"COALESCE(nummensualidad,0) AS nummensualidad, "
					"COALESCE(mtopagopesos,0.0) AS mtopagopesos, "
					"COALESCE(motivocancela,0) AS motivocancela, "
					"COALESCE(estado,0) AS estado, "
					"COALESCE(foliopago,0) AS foliopago, "
					"TRIM(COALESCE(marcaultpago,' '))::Char(1) AS marcaultpago, "
					"COALESCE(foliosolicitudctr,0) AS foliosolicitudctr, "
					"TRIM(COALESCE(nssctr,' '))::Char(11) AS nssctr, "
					"COALESCE(consecutivoctr,0) AS consecutivoctr, "
					"COALESCE(foliolotectr,0) AS foliolotectr, "
					"COALESCE(estadoctr,0) AS estadoctr, "
					"COALESCE(nummensualidades,0) AS nummensualidades, "
					"COALESCE(pagomensualpesos,0.0) AS pagomensualpesos, "
					"COALESCE(pagoretroactivopesos,0.0) AS pagoretroactivopesos, "
					"COALESCE(devengadaspesos,0.0) AS devengadaspesos, "
					"COALESCE(tipocontrato,0) AS tipocontrato "
					"FROM fnconsultarpmgcontratoimssreplica01(%i);",iFolioServicio);	
					
	objRetTotPmg.ClearResults();
	if(objRetTotPmg.Exec(cSql))	
	{
		objRetTotPmg.activarCols();
		if(objRetTotPmg.leer())
		{			
			memset(cNss, 0, sizeof(cNss));
			memset(cCurp, 0, sizeof(cCurp));
			memset(cSecpension, 0, sizeof(cSecpension));
			memset(cTiporetiro, 0, sizeof(cTiporetiro));
			memset(cRegimen, 0, sizeof(cRegimen));
			memset(cTiposeguro, 0, sizeof(cTiposeguro));
			memset(cTipopension, 0, sizeof(cTipopension));
			memset(cFechainipen, 0, sizeof(cFechainipen));
			memset(cFecharesolucion, 0, sizeof(cFecharesolucion));
			memset(cFechasolicitud, 0, sizeof(cFechasolicitud));
			memset(cFechapago, 0, sizeof(cFechapago));			
			memset(cDiagregistro, 0, sizeof(cDiagregistro));
			memset(cFechacaptura, 0, sizeof(cFechacaptura));
			memset(cHoracaptura, 0, sizeof(cHoracaptura));
			memset(cUsuariocaptura, 0, sizeof(cUsuariocaptura));
			memset(cFechamodifica, 0, sizeof(cFechamodifica));
			memset(cHoramodifica, 0, sizeof(cHoramodifica));
			memset(cUsuariomodifica, 0, sizeof(cUsuariomodifica));
			memset(cFechaconfirma, 0, sizeof(cFechaconfirma));
			memset(cHoraconfirma, 0, sizeof(cHoraconfirma));
			memset(cUsuarioconfirma, 0, sizeof(cUsuarioconfirma));
			memset(cNssctrdet, 0, sizeof(cNssctrdet));
			memset(cFechapagoestimada, 0, sizeof(cFechapagoestimada));
			memset(cFecharecibeop79, 0, sizeof(cFecharecibeop79));
			memset(cFechaliquida, 0, sizeof(cFechaliquida));
			memset(cMarcaultpago, 0, sizeof(cMarcaultpago));
			memset(cNssctr, 0, sizeof(cNssctr));
					
			memmove(cNss, objRetTotPmg.cNss, sizeof(11));
			memmove(cCurp, objRetTotPmg.cCurp, sizeof(18));
			memmove(cSecpension, objRetTotPmg.cSecpension, sizeof(2));
			memmove(cTiporetiro, objRetTotPmg.cTiporetiro, sizeof(1));
			memmove(cRegimen, objRetTotPmg.cRegimen, sizeof(2));
			memmove(cTiposeguro, objRetTotPmg.cTiposeguro, sizeof(2));
			memmove(cTipopension, objRetTotPmg.cTipopension, sizeof(2));

			//memcpy(cFechainipen, objRetTotPmg.cFechainipen, 10);
			snprintf(cFechainipen, strnlen(cFechainipen, sizeof(cFechainipen)), "MDY(%c%c,%c%c,%c%c%c%c)",
					objRetTotPmg.cFechainipen[0], 
					objRetTotPmg.cFechainipen[1],
					objRetTotPmg.cFechainipen[3], 
					objRetTotPmg.cFechainipen[4],
					objRetTotPmg.cFechainipen[6],
					objRetTotPmg.cFechainipen[7],
					objRetTotPmg.cFechainipen[8],
					objRetTotPmg.cFechainipen[9]);		

			//memcpy(cFecharesolucion, objRetTotPmg.cFecharesolucion, 10);
			snprintf(cFecharesolucion, strnlen(cFecharesolucion, sizeof(cFecharesolucion)), "MDY(%c%c,%c%c,%c%c%c%c)",
					objRetTotPmg.cFecharesolucion[0], 
					objRetTotPmg.cFecharesolucion[1],
					objRetTotPmg.cFecharesolucion[3], 
					objRetTotPmg.cFecharesolucion[4],
					objRetTotPmg.cFecharesolucion[6],
					objRetTotPmg.cFecharesolucion[7],
					objRetTotPmg.cFecharesolucion[8],
					objRetTotPmg.cFecharesolucion[9]);

			//memcpy(cFechasolicitud, objRetTotPmg.cFechasolicitud, 10);
			snprintf(cFechasolicitud, strnlen(cFechasolicitud, sizeof(cFechasolicitud)), "MDY(%c%c,%c%c,%c%c%c%c)",
					objRetTotPmg.cFechasolicitud[0], 
					objRetTotPmg.cFechasolicitud[1],
					objRetTotPmg.cFechasolicitud[3], 
					objRetTotPmg.cFechasolicitud[4],
					objRetTotPmg.cFechasolicitud[6],
					objRetTotPmg.cFechasolicitud[7],
					objRetTotPmg.cFechasolicitud[8],
					objRetTotPmg.cFechasolicitud[9]);

			//memcpy(cFechapago, objRetTotPmg.cFechapago, 10);
			snprintf(cFechapago, strnlen(cFechapago, sizeof(cFechapago)), "MDY(%c%c,%c%c,%c%c%c%c)",
					objRetTotPmg.cFechapago[0], 
					objRetTotPmg.cFechapago[1],
					objRetTotPmg.cFechapago[3], 
					objRetTotPmg.cFechapago[4],
					objRetTotPmg.cFechapago[6],
					objRetTotPmg.cFechapago[7],
					objRetTotPmg.cFechapago[8],
					objRetTotPmg.cFechapago[9]);

			memmove(cDiagregistro, objRetTotPmg.cDiagregistro, sizeof(3));

			//memcpy(cFechacaptura, objRetTotPmg.cFechacaptura, 10);
			snprintf(cFechacaptura, strnlen(cFechacaptura, sizeof(cFechacaptura)), "MDY(%c%c,%c%c,%c%c%c%c)",
					objRetTotPmg.cFechacaptura[0], 
					objRetTotPmg.cFechacaptura[1],
					objRetTotPmg.cFechacaptura[3], 
					objRetTotPmg.cFechacaptura[4],
					objRetTotPmg.cFechacaptura[6],
					objRetTotPmg.cFechacaptura[7],
					objRetTotPmg.cFechacaptura[8],
					objRetTotPmg.cFechacaptura[9]);

			memmove(cHoracaptura, objRetTotPmg.cHoracaptura, sizeof(8));
			memmove(cUsuariocaptura, objRetTotPmg.cUsuariocaptura, sizeof(15));

			//memcpy(cFechamodifica, objRetTotPmg.cFechamodifica, 10);
			snprintf(cFechamodifica, strnlen(cFechamodifica, sizeof(cFechamodifica)), "MDY(%c%c,%c%c,%c%c%c%c)",
					objRetTotPmg.cFechamodifica[0], 
					objRetTotPmg.cFechamodifica[1],
					objRetTotPmg.cFechamodifica[3], 
					objRetTotPmg.cFechamodifica[4],
					objRetTotPmg.cFechamodifica[6],
					objRetTotPmg.cFechamodifica[7],
					objRetTotPmg.cFechamodifica[8],
					objRetTotPmg.cFechamodifica[9]);
			
			memmove(cHoramodifica, objRetTotPmg.cHoramodifica, sizeof(8));			
			memmove(cUsuariomodifica, objRetTotPmg.cUsuariomodifica, sizeof(15));

			//memcpy(cFechaconfirma, objRetTotPmg.cFechaconfirma, 10);
			snprintf(cFechaconfirma, strnlen(cFechaconfirma, sizeof(cFechaconfirma)), "MDY(%c%c,%c%c,%c%c%c%c)",
					objRetTotPmg.cFechaconfirma[0], 
					objRetTotPmg.cFechaconfirma[1],
					objRetTotPmg.cFechaconfirma[3], 
					objRetTotPmg.cFechaconfirma[4],
					objRetTotPmg.cFechaconfirma[6],
					objRetTotPmg.cFechaconfirma[7],
					objRetTotPmg.cFechaconfirma[8],
					objRetTotPmg.cFechaconfirma[9]);

			memmove(cHoraconfirma, objRetTotPmg.cHoraconfirma, sizeof(8));
			memmove(cUsuarioconfirma, objRetTotPmg.cUsuarioconfirma, sizeof(15));

			memmove(cNssctrdet, objRetTotPmg.cNssctrdet, sizeof(11));
			//memcpy(cFechapagoestimada, objRetTotPmg.cFechapagoestimada, 10);
			snprintf(cFechapagoestimada, strnlen(cFechapagoestimada, sizeof(cFechapagoestimada)), "MDY(%c%c,%c%c,%c%c%c%c)",
					objRetTotPmg.cFechapagoestimada[0], 
					objRetTotPmg.cFechapagoestimada[1],
					objRetTotPmg.cFechapagoestimada[3], 
					objRetTotPmg.cFechapagoestimada[4],
					objRetTotPmg.cFechapagoestimada[6],
					objRetTotPmg.cFechapagoestimada[7],
					objRetTotPmg.cFechapagoestimada[8],
					objRetTotPmg.cFechapagoestimada[9]);

			//memmove(cFecharecibeop79, objRetTotPmg.cFecharecibeop79, 10);
			snprintf(cFecharecibeop79, strnlen(cFecharecibeop79, sizeof(cFecharecibeop79)), "MDY(%c%c,%c%c,%c%c%c%c)",
					objRetTotPmg.cFecharecibeop79[0], 
					objRetTotPmg.cFecharecibeop79[1],
					objRetTotPmg.cFecharecibeop79[3], 
					objRetTotPmg.cFecharecibeop79[4],
					objRetTotPmg.cFecharecibeop79[6],
					objRetTotPmg.cFecharecibeop79[7],
					objRetTotPmg.cFecharecibeop79[8],
					objRetTotPmg.cFecharecibeop79[9]);

			//memcpy(cFechaliquida, objRetTotPmg.cFechaliquida, 10);
			snprintf(cFechaliquida, strnlen(cFechaliquida, sizeof(cFechaliquida)), "MDY(%c%c,%c%c,%c%c%c%c)",
					objRetTotPmg.cFechaliquida[0], 
					objRetTotPmg.cFechaliquida[1],
					objRetTotPmg.cFechaliquida[3], 
					objRetTotPmg.cFechaliquida[4],
					objRetTotPmg.cFechaliquida[6],
					objRetTotPmg.cFechaliquida[7],
					objRetTotPmg.cFechaliquida[8],
					objRetTotPmg.cFechaliquida[9]);

			memmove(cMarcaultpago, objRetTotPmg.cMarcaultpago, sizeof(1));			
			objFG.fnArcGrabarLogx(RUTA_LOG," 21 ");
			memmove(cNssctr, objRetTotPmg.cNssctr, sizeof(11));
			iTipocontrato = objRetTotPmg.iTipocontrato;

			if (objRetTotPmg.iFoliosolicitud == 0)
			{
				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "NO EXISTE INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
				objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
			}
			else if (objRetTotPmg.iGrupo == 0)
			{
				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "NO SE PUDO MIGRAR LA INFORMACION CON EL FOLIO: [%i] POR QUE NO PERTENECE A UN GRUPO VALIDO", iFolioServicio);
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
				objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
			}
			else
			{

				/**********************************************************************************************************************/
				/************************************************pensolicitudpmgimss***************************************************/
				/**********************************************************************************************************************/
				
				objFG.fnArcGrabarLogx(RUTA_LOG,"-*-*-*-*-*-*-*-*-*TABLA : pensolicitudpmgimss-*-*-*-*-*-*-*-*-*");
				
				memset(cSqlTb1,0, sizeof(cSqlTb1));
				memset(cTextoTb1,0, sizeof(cTextoTb1));

				snprintf(cSqlTb1, strnlen(cSqlTb1, sizeof(cSqlTb1)), "EXECUTE FUNCTION fn_guardarpensolicitudpmgreplica('%s',%i,%i,%i,%i,%i,'%s','%s','%s','%s','%s','%s',%i,%f,%s,%s,%s,%s,%i,'%s',%i,%s,'%s'::DATETIME HOUR TO SECOND,'%s',%s,'%s'::DATETIME HOUR TO SECOND,'%s',%s,'%s'::DATETIME HOUR TO SECOND,'%s',%i,%i);",
													cNss,
													objRetTotPmg.iConsecutivo,
													objRetTotPmg.iSeccontrato,
													objRetTotPmg.iFoliocontrato,
													objRetTotPmg.iFoliolote,
													objRetTotPmg.iFoliosolicitud,
													cCurp,
													cSecpension,
													cTiporetiro,
													cRegimen,
													cTiposeguro,
													cTipopension,
													objRetTotPmg.iTipoprestacion,
													0.0, //objRetTotPmg.dImportemensual 
													cFechainipen,
													cFecharesolucion,
													cFechasolicitud,
													cFechapago,
													objRetTotPmg.iEstadosubviv,
													cDiagregistro,
													objRetTotPmg.iGrupo,
													cFechacaptura,
													cHoracaptura,
													cUsuariocaptura,
													cFechamodifica,
													cHoramodifica,
													cUsuariomodifica,
													cFechaconfirma,
													cHoraconfirma,
													cUsuarioconfirma,
													objRetTotPmg.iCodigorechazo,
													objRetTotPmg.iEstadosolicitud
													);						
				
				objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSqlTb1, iRespuestaTb1, cTextoTb1);

				if (iRespuestaTb1 == 1)
				{
					memset(cTextoTb1, 0, sizeof(cTextoTb1));
					snprintf(cTextoTb1,  strnlen(cTextoTb1, sizeof(cTextoTb1)),"SE MIGRO LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTextoTb1);				
				}
				else
				{
					memset(cTextoTb1, 0, sizeof(cTextoTb1));
					snprintf(cTextoTb1, strnlen(cTextoTb1, sizeof(cTextoTb1)), "NO SE PUDO MIGRAR LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTextoTb1);

					memset(cTextoTb1, 0, sizeof(cTextoTb1));
					snprintf(cTextoTb1, strnlen(cTextoTb1, sizeof(cTextoTb1)), "QUERY: [%s]", cSqlTb1);

					objFG.fnArcGrabarLogx(RUTA_LOG, cTextoTb1);				
				}

				objFG.fnArcGrabarLogx(RUTA_LOG,"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
				
				/**********************************************************************************************************************/
				/************************************************penctrpagodetimss***************************************************/
				/**********************************************************************************************************************/		
				
				objFG.fnArcGrabarLogx(RUTA_LOG,"-*-*-*-*-*-*-*-*-*TABLA : penctrpagodetimss-*-*-*-*-*-*-*-*-*");

				memset(cSqlTb2,0, sizeof(cSqlTb2));
				memset(cTextoTb2,0, sizeof(cTextoTb2));

				snprintf(cSqlTb2, strnlen(cSqlTb2, sizeof(cSqlTb2)), "EXECUTE FUNCTION fn_guardarpenctrpagodetpmgreplica('%s',%i,%i,%i,%i,%s,%s,%s,%i,%f,%i,%i,%i,'%s');",												
													cNssctrdet,
													objRetTotPmg.iConsecutivoctrdet,
													objRetTotPmg.iSeccontratoctrdet,
													objRetTotPmg.iFolioop78,
													objRetTotPmg.iFolioliquida,
													cFechapagoestimada,
													cFecharecibeop79,
													cFechaliquida,
													objRetTotPmg.iNummensualidad,
													0.0, //objRetTotPmg.dMtopagopesos
													objRetTotPmg.iMotivocancela,
													objRetTotPmg.iEstado,
													objRetTotPmg.iFoliopago,
													cMarcaultpago
													);			
				
				objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSqlTb2, iRespuestaTb2, cTextoTb2);			

				if (iRespuestaTb2 == 1)
				{
					memset(cTextoTb2, 0, sizeof(cTextoTb2));
					snprintf(cTextoTb2, strnlen(cTextoTb2, sizeof(cTextoTb2)), "SE MIGRO LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTextoTb2);
					objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
				}
				else
				{
					memset(cTextoTb2, 0, sizeof(cTextoTb2));
					snprintf(cTextoTb2, strnlen(cTextoTb2, sizeof(cTextoTb2)), "NO SE PUDO MIGRAR LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTextoTb2);

					memset(cTextoTb2, 0, sizeof(cTextoTb2));
					snprintf(cTextoTb2, strnlen(cTextoTb2, sizeof(cTextoTb2)), "QUERY: [%s]", cSqlTb2);

					objFG.fnArcGrabarLogx(RUTA_LOG, cTextoTb2);
					objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
				}
							
				objFG.fnArcGrabarLogx(RUTA_LOG,"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");			
				
				/**********************************************************************************************************************/
				/************************************************penctrpagoimss***************************************************/
				/**********************************************************************************************************************/		
			
				objFG.fnArcGrabarLogx(RUTA_LOG,"-*-*-*-*-*-*-*-*-*TABLA : penctrpagoimss-*-*-*-*-*-*-*-*-*");

				memset(cSqlTb3,0, sizeof(cSqlTb3));
				memset(cTextoTb2,0, sizeof(cTextoTb2));

				snprintf(cSqlTb3, strnlen(cSqlTb3, sizeof(cSqlTb3)), "EXECUTE FUNCTION fn_guardarpenctrpagopmgreplica('%s',%i,%i,%i,%f,%f,%f,%i);",
													cNssctr,
													objRetTotPmg.iConsecutivoctr,
													objRetTotPmg.iFoliolotectr,													
													objRetTotPmg.iNummensualidades,
													0.0,//objRetTotPmg.dPagomensualpesos,
													0.0,//objRetTotPmg.dPagoretroactivopesos,
													0.0,//objRetTotPmg.dDevengadaspesos,
													objRetTotPmg.iEstadoctr
													);			
																
				objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSqlTb3, iRespuestaTb3, cTextoTb3);			

				if (iRespuestaTb3 == 1)
				{
					memset(cTextoTb3, 0, sizeof(cTextoTb3));
					snprintf(cTextoTb3, strnlen(cTextoTb3, sizeof(cTextoTb3)), "SE MIGRO LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTextoTb3);
					objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
				}
				else
				{
					memset(cTextoTb3, 0, sizeof(cTextoTb3));
					snprintf(cTextoTb3, strnlen(cTextoTb3, sizeof(cTextoTb3)), "NO SE PUDO MIGRAR LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTextoTb3);

					memset(cTextoTb3, 0, sizeof(cTextoTb3));
					snprintf(cTextoTb3, strnlen(cTextoTb3, sizeof(cTextoTb3)), "QUERY: [%s]", cSqlTb3);
					
					objFG.fnArcGrabarLogx(RUTA_LOG, cTextoTb3);
					objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
				}
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////ejecutar el metodo para guardar el SUV
				saveSelloBiometricoSuv(odbcInfxSafreaf,iTipocontrato);
				objFG.fnArcGrabarLogx(RUTA_LOG,"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
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