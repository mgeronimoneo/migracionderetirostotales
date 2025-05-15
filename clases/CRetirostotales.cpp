#include "CRetirostotales.hpp"

CRetirostotales::CRetirostotales()
{
	// TODO Auto-generated constructor stub
}

CRetirostotales::~CRetirostotales()
{
	// TODO Auto-generated destructor stub
}

short CRetirostotales::ReplicarSolicitudesRetirosTotales(C_ODBC* odbcAforeGlobal, C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore)
{
	CInformacion objInfoGen(odbcAforeGlobal);
	CMarca objMarca(odbcInfxSafreaf);
	CInfoMarca objInfoFechaHoraMarca(odbcServiciosAfore);

	//CAMPOS DE LA FUNCIÓN
	int 	iFolioServicio;
	int 	iFolioSolicitud;
	int 	iOrigenServicio;
	int 	iCodigoMedio;
	int 	iCodigoTipo;
	int 	iCodigoMotivo;
	int 	iPromotor;
	int 	iCodigoTermino;
	int 	iTipoGrupoServicio;
	int 	iTipoSolicitante;
	int 	iTipoIdentificador;
	int 	iIdpago;
	int		iMotivoretiro;
	char	cCurp[20] = {0};
	char	cCurpBen[20] = {0}; //Nueva 10/01/2018
	char	cNss[13] = {0};
	char	cTipoServicio[3] = {0};
	char	cFechaReclamo[10] = {0};
	char	cFechaInicio[10] = {0};
	char	cFechaFinEstimada[10] = {0};
	char	cFechaFinReal[10] = {0};
	char	cFechaAlta[10] = {0};
	char	cTipoOperacion[6] = {0};
	char	cCurpAgenteServicio[20] = {0};
	char	cCurpFuncionario[20] = {0};
	char	cSelloVoluntad[16] = {0};
	char	cSelloFuncionario[16] = {0};
	char 	cHoraFin[10] = {0};
	char	cSellotrabajador[16] = {0};
	//FIN CAMPOS DE LA FUNCIÓN
	//////////////////////
	char	cCurpSolBeneficiario[18] = {0}; //cur que se asignara en la tabla sello sub cuando se trate de un beneficiario
	//////////////////////

	char	cSql[2024] = {0};
	char	cSqlAux[2024] = {0};

	char 	cTexto[1024] = {0};
	char 	cTextoaux[1024] = {0};
	char 	cOutTexto[1024] = {0};
	char	Claveconsar[10] = {0};
	char 	cFechaTermino[10]  = {0};
	char 	cCurpPaGenteServicio[20]  = {0};
	char 	cFechaReclamoAux[10]  = {0};
	char 	cFechaInicioAux[10]  = {0};
	char 	cFechaFinEstimadaAux[10]  = {0};
	char 	cFechaFinRealAux[10]  = {0};
	char 	cFechaTerminoAux[10]  = {0};
	int 	iContRegistros = 0;
	int 	iRespuesta = 0;
	int 	iRespuestaQuery = 0;
	int		iExisteBD = 0;
	int 	iConsecutivo = 0;
	int		iEstatusmigracion = 0;
	int 	iValidamarca = 0;
	int 	iValidestatusmigracion = 0;
	int		iSellovalida = 0;
	int 	iIdentificador;
	short	shRet = 0;

	int 	iCodigo = 0;
	char 	cMarca[52] = {0};
	char 	cRechazo[52] = {0};

	char 	cFechaMarca[12] = {0};
	char    cHoraMarca[10] = {0};

	int 	iCodigoMarca = 0;
	bool	bPuedeMigrar = false;

	char cFechaActualizaMarca[10] = {0};
	char cTipoRetiro[1]  = {0};

	/**********************************************************************************************************************/
	/*************************************SE OBTIENE LA INFORMACION GENERAL************************************************/
	/**********************************************************************************************************************/
	memset(cSql, 0, sizeof(cSql));
	snprintf(cSql, sizeof(cSql), "SELECT COALESCE(folioservicio,0) AS folioservicio, "
						 "COALESCE(curp,' ') AS curp, "
						 "COALESCE(nss,' ') AS nss, "
						 "COALESCE(foliosolicitud, 0) AS foliosolicitud, "
						 "COALESCE(origenservicio, 0) AS origenservicio, "
						 "COALESCE(codigomedio, 0) AS codigomedio, "
						 "COALESCE(codigotipo, 0) AS codigotipo, "
						 "COALESCE(codigomotivo, 0) AS codigomotivo, "
						 "COALESCE(tiposervicio,' ') AS tiposervicio, "
						 "COALESCE(fechareclamo,'01011900') AS fechareclamo, "
						 "COALESCE(fechainicio,'01011900') AS fechainicio, "
						 "COALESCE(fechafinestimada, '01011900') AS fechafinestimada, "
						 "COALESCE(fechafinreal,'01011900') AS fechafinreal, "
						 "COALESCE(promotor, 0) AS promotor, "
						 "COALESCE(fechaalta, '01011900') AS fechaalta, "
						 "COALESCE(codigotermino, 0) AS codigotermino, "
						 "COALESCE(motivoretiro, 0) AS motivoretiro, "
						 "COALESCE(tipooperacion,' ') AS tipooperacion, "
						 "COALESCE(curpagenteservicio,' ') AS curpagenteservicio, "
						 "COALESCE(curpfuncionario, ' ') AS curpfuncionario, "
						 "COALESCE(sellovoluntad,' ') AS sellovoluntad, "
						 "COALESCE(sellofuncionario,' ') AS sellofuncionario, "
						 "COALESCE(tipogruposervicio, 0) AS tipogruposervicio, "
						 "COALESCE(tiposolicitante, 0) AS tiposolicitante, "
						 "COALESCE(tipoidentificador, 0) AS tipoidentificador, "
						 "COALESCE(idpago,0) AS idpago, "
						 "COALESCE(tiposolicitud,0) AS tiposolicitud, "
						 "COALESCE(horafin,' ')::char(8) AS horafin, "
						 "COALESCE(sellotrabajador,' ')::char(14) AS sellotrabajador "
		"FROM fnconsultarecserviciosaforereplicart02();");

	objInfoGen.ClearResults();
	if(objInfoGen.Exec(cSql))
	{
		objInfoGen.activarCols();
		while (objInfoGen.leer())
		{
			iContRegistros++;

			memset(cCurp, 0, sizeof(cCurp));
			memset(cNss, 0, sizeof(cNss));
			memset(cTipoServicio, 0, sizeof(cTipoServicio));
			memset(cFechaReclamo, 0, sizeof(cFechaReclamo));
			memset(cFechaInicio, 0, sizeof(cFechaInicio));
			memset(cFechaFinEstimada, 0, sizeof(cFechaFinEstimada));
			memset(cFechaFinReal, 0, sizeof(cFechaFinReal));
			memset(cFechaAlta, 0 , sizeof(cFechaAlta));
			memset(cTipoOperacion, 0 , sizeof(cTipoOperacion));
			memset(cCurpAgenteServicio, 0, sizeof(cCurpAgenteServicio));
			memset(cCurpFuncionario, 0, sizeof(cCurpFuncionario));
			memset(cSelloVoluntad, 0, sizeof(cSelloVoluntad));
			memset(cSelloFuncionario, 0, sizeof(cSelloFuncionario));
			memset(cHoraFin, 0, sizeof(cHoraFin));
			memset(cSellotrabajador, 0, sizeof(cSellotrabajador));

			iFolioServicio = objInfoGen.iFolioServicio;
			memmove(cCurp, objInfoGen.cCurp, sizeof(18));
			memmove(cNss, objInfoGen.cNss, sizeof(11));
			iFolioSolicitud = objInfoGen.iFolioSolicitud;
			iOrigenServicio = objInfoGen.iOrigenServicio;
			iCodigoMedio = objInfoGen.iCodigoMedio;
			iCodigoTipo = objInfoGen.iCodigoTipo;
			iCodigoMotivo = objInfoGen.iCodigoMotivo;
			memmove(cTipoServicio, objInfoGen.cTipoServicio, sizeof(1));
			memmove(cFechaReclamo, objInfoGen.cFechaReclamo, sizeof(8));
			memmove(cFechaInicio, objInfoGen.cFechaInicio, sizeof(8));
			memmove(cFechaFinEstimada, objInfoGen.cFechaFinEstimada, sizeof(8));
			memmove(cFechaFinReal, objInfoGen.cFechaFinReal, sizeof(8));
			iPromotor = objInfoGen.iPromotor;
			memmove(cFechaAlta, objInfoGen.cFechaAlta, sizeof(8));
			iCodigoTermino = objInfoGen.iCodigoTermino;
			iMotivoretiro = objInfoGen.iMotivoretiro;
			memmove(cTipoOperacion, objInfoGen.cTipoOperacion, sizeof(4));
			memmove(cCurpAgenteServicio, objInfoGen.cCurpAgenteServicio, sizeof(18));
			memmove(cCurpFuncionario, objInfoGen.cCurpFuncionario, sizeof(20));
			memmove(cSelloVoluntad, objInfoGen.cSelloVoluntad, sizeof(14));
			memmove(cSelloFuncionario, objInfoGen.cSelloFuncionario, sizeof(14));
			iTipoGrupoServicio = objInfoGen.iTipoGrupoServicio;
			iTipoSolicitante = objInfoGen.iTipoSolicitante;
			iTipoIdentificador = objInfoGen.iTipoIdentificador;
			iIdpago = objInfoGen.iIdpago;
			memmove(cHoraFin, objInfoGen.cHoraFin, sizeof(8));
			memmove(cSellotrabajador, objInfoGen.cSellotrabajador, sizeof(14));

			memset(cTexto, 0, sizeof(cTexto));
			snprintf(cTexto, sizeof(cTexto), "FOLIO QUE SE ESTA PROCESANDO -->[%i]",iFolioServicio);
			objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

			memset(cSql,0,sizeof(cSql));
			memset(cTexto,0,sizeof(cTexto));



				snprintf(cSql, sizeof(cSql), "select fnrettotvalidarfolioservicio from fnrettotvalidarfolioservicio('%s',%i,%i);", cTipoOperacion, objInfoGen.iFolioServicio,objInfoGen.iCodigoMotivo);
				objFG.fnSqlConsultarNumero(odbcServiciosAfore,cSql,iRespuesta, cTexto);

				iExisteBD = iRespuesta;

				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, sizeof(cTexto), "RESPUESTA DE LA FUNCION PARA EL FOLIO-->[%i] ---> [%i]",iFolioServicio,iExisteBD);
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

			

			if(iExisteBD == 1)
			{
				if(memcmp(cSelloVoluntad, "00000000000000", 14) == 0) // YAA RETIROS APP
				{
					iExisteBD = 1;
				}
				else
				{
					iExisteBD = -1;
					memset(cSql,0,sizeof(cSql));
					memset(cTexto,0,sizeof(cTexto));
					snprintf(cSql, sizeof(cSql), "select fnvalidarvigenciacus from fnvalidarvigenciacus('%s',%i);",objInfoGen.cCurp, objInfoGen.iFolioServicio);
					objFG.fnSqlConsultarNumero(odbcAforeGlobal,cSql,iRespuesta, cTexto);

					iExisteBD = iRespuesta;

					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, sizeof(cTexto), "RESPUESTA DE LA FUNCION \"FNVALIDARVIGENCIACUS\" PARA EL FOLIO-->[%i] ---> [%i]",iFolioServicio,iExisteBD);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
				}


				
				if(iExisteBD == 1)
				{

					memset(cSql,0,sizeof(cSql));
					memset(cTexto,0,sizeof(cTexto));
					snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_obten_ret_consecutivo();");
					objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSql, iRespuesta, cTexto);

					iConsecutivo = 0;
					iConsecutivo = iRespuesta;

					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, sizeof(cTexto), "CONSECUTIVO [%i] PARA EL FOLIO [%i] ",iConsecutivo,iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

					if (iConsecutivo == 0)
					{
						memset(cTexto, 0, sizeof(cTexto));
						snprintf(cTexto, sizeof(cTexto), "[%s][%s] Error al ejecutar al obtener el consecutivo...", __FILE__,__FUNCTION__);
						objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
					}
					else
					{
						memset(cSql, 0, sizeof(cSql));
						snprintf(cSql, sizeof(cSql), "select fnrettotactualizaconsecutivoserv from fnrettotactualizaconsecutivoserv(%i, '%s', %i, %i);", iConsecutivo, cTipoOperacion, iFolioServicio,objInfoGen.iCodigoMotivo);
						objFG.fnSqlConsultarNumero(odbcServiciosAfore, cSql, iRespuesta, cTexto);

						memset(cSql, 0, sizeof(cSql));
						//sprintf(cSql, "update recserviciosafore set consecutivomarca = %i where nss = '%s' and folioservicio = %i;", iConsecutivo, cNss, iFolioServicio);
						snprintf(cSql, sizeof(cSql), "select * from fnrettotactualizarecservicios(%i,%i,%i,'%s');", 1,iConsecutivo, iFolioServicio,cNss);
						objFG.fnSqlConsultarTexto(odbcAforeGlobal,(char*)cSql, (char*)cOutTexto);

						//objFG.fnArcGrabarLogx(RUTA_LOG, cSql);

						//SE EJECUTA LA FUNCIÓN MARCA PARA SAFRE
						/*memset(cSql,0,sizeof(cSql));
						memset(cTexto,0,sizeof(cTexto));
						if(memcmp(cSelloVoluntad, SELLOVACIO, 1) == 0)
						{
							iValidamarca = 0;
							iEstatusmigracion = 0;
							iSellovalida = 2;
						}
						else if(memcmp(cSelloVoluntad, SINSELLO, 1) == 0)
						{
							iValidamarca = 0;
							iEstatusmigracion = 0;
							iSellovalida = 1;
						}
						else
						{
							iValidamarca = 1;
						}*/

						/**********************************************************************************************************************/
						/*****************************************SE MARCAN LAS CUENTAS********************************************************/
						/**********************************************************************************************************************/

						iValidamarca = 1;   //QUITARRRRRRRRRRR ESTA LINEA
						if(iValidamarca != 0)
						{
							iCodigoMarca = 0;
							////////////////////////////////////// TIPO OPERACION '0520' IMSS ////////////////////////////////////////////////////

							/********************************************************************************************************************************/
							/*RETIROS PARA EL 271*/
							if(objInfoGen.iCodigoMotivo == 1029)
							{
								memset(cTipoRetiro, 0, sizeof(cTipoRetiro));
								snprintf(cTipoRetiro, sizeof(cTipoRetiro), "D");
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta_retiros(3, '%s', %i, '%s', %i);", cNss, iConsecutivo, cTipoRetiro, iPromotor);
								iCodigoMarca = 820;
							}
							else if(objInfoGen.iCodigoMotivo == 1030)
							{
								memset(cTipoRetiro, 0, sizeof(cTipoRetiro));
								snprintf(cTipoRetiro, sizeof(cTipoRetiro), "E");
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta_retiros(3, '%s', %i, '%s', %i);", cNss, iConsecutivo, cTipoRetiro, iPromotor);
								iCodigoMarca = 830;
							}
							else if(objInfoGen.iCodigoMotivo == 1031)
							{
								memset(cTipoRetiro, 0, sizeof(cTipoRetiro));
								snprintf(cTipoRetiro, sizeof(cTipoRetiro), "F");
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta_retiros(3, '%s', %i, '%s', %i);", cNss, iConsecutivo, cTipoRetiro, iPromotor);
								iCodigoMarca = 840;
							}
							else if(objInfoGen.iCodigoMotivo == 1032)
							{
								memset(cTipoRetiro, 0, sizeof(cTipoRetiro));
								snprintf(cTipoRetiro, sizeof(cTipoRetiro), "J");
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta_retiros(3, '%s', %i, '%s', %i);", cNss, iConsecutivo, cTipoRetiro, iPromotor);
								iCodigoMarca = 880;
							}
							else if(objInfoGen.iCodigoMotivo == 1033)
							{
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta(3, '%s', %i, 'H', %i);", cNss, iConsecutivo, iPromotor);
								iCodigoMarca = 860;
							}
							else if(objInfoGen.iCodigoMotivo == 1034)
							{
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta(3, '%s', %i, 'G', %i);", cNss, iConsecutivo, iPromotor);
								iCodigoMarca = 850;
							}
							else if(objInfoGen.iCodigoMotivo == 1052 )
							{
								memset(cTipoRetiro, 0, sizeof(cTipoRetiro));
								snprintf(cTipoRetiro, sizeof(cTipoRetiro), "M");
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta_retiros(3, '%s', %i, '%s', %i);", cNss, iConsecutivo, cTipoRetiro, iPromotor);
								iCodigoMarca = 825;
							}
							else if(objInfoGen.iCodigoMotivo == 1059)
							{
								memset(cTipoRetiro, 0, sizeof(cTipoRetiro));
								snprintf(cTipoRetiro, sizeof(cTipoRetiro), "F");
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta_retiros(3, '%s', %i, '%s', %i);", cNss, iConsecutivo, cTipoRetiro, iPromotor);
								iCodigoMarca = 840;
							}
							/********************************************************************************************************************************/

						    //if(objInfoGen.iCodigoMotivo == 2016)
							else if(objInfoGen.iCodigoMotivo == 2016)
							{
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta(3, '%s', %i, 'J', %i);", cNss, iConsecutivo, iPromotor);
								iCodigoMarca = 880;
							}
							else if(objInfoGen.iCodigoMotivo == 2017)
							{
								memset(cTipoRetiro, 0, sizeof(cTipoRetiro));
								snprintf(cTipoRetiro, sizeof(cTipoRetiro), "M");
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta_retiros(3, '%s', %i, '%s', %i);", cNss, iConsecutivo, cTipoRetiro, iPromotor);
								iCodigoMarca = 825;
							}
							else if(objInfoGen.iCodigoMotivo == 2037)
							{
								memset(cTipoRetiro, 0, sizeof(cTipoRetiro));
								snprintf(cTipoRetiro, sizeof(cTipoRetiro), "F");
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta_retiros(3, '%s', %i, '%s', %i);", cNss, iConsecutivo, cTipoRetiro, iPromotor);
								iCodigoMarca = 840;
							}
							else if(objInfoGen.iCodigoMotivo == 2038)
							{	
								memset(cTipoRetiro, 0, sizeof(cTipoRetiro));
								snprintf(cTipoRetiro, sizeof(cTipoRetiro), "P");
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta_retiros(3, '%s', %i, '%s', %i);", cNss, iConsecutivo, cTipoRetiro, iPromotor);
								iCodigoMarca = 835;
							}
							else if(objInfoGen.iCodigoMotivo == 2039)
							{
								memset(cTipoRetiro, 0, sizeof(cTipoRetiro));
								snprintf(cTipoRetiro, sizeof(cTipoRetiro), "E");
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta_retiros(3, '%s', %i, '%s', %i);", cNss, iConsecutivo, cTipoRetiro, iPromotor);
								iCodigoMarca = 830;
							}
							////////////////////////////////////// FIN TIPO OPERACION '0520' IMSS////////////////////////////////////////////////////

							////////////////////////////////////// TIPO OPERACION '0521' ISSSTE ////////////////////////////////////////////////////
							else if(objInfoGen.iCodigoMotivo == 851)
							{
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta(2, '%s', %i, 'A', %i);", cNss, iConsecutivo, iPromotor);
								iCodigoMarca = 851;
							}
							else if(objInfoGen.iCodigoMotivo == 852)
							{
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta(2, '%s', %i, 'B', %i);", cNss, iConsecutivo, iPromotor);
								iCodigoMarca = 852;
							}
							else if(objInfoGen.iCodigoMotivo == 853)
							{
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta(2, '%s', %i, 'C', %i);", cNss, iConsecutivo, iPromotor);
								iCodigoMarca = 853;
							}
							else if(objInfoGen.iCodigoMotivo == 854)
							{
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta(2, '%s', %i, 'D', %i);", cNss, iConsecutivo, iPromotor);
								iCodigoMarca = 854;
							}
							else if(objInfoGen.iCodigoMotivo == 855)
							{
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta(2, '%s', %i, 'E', %i);", cNss, iConsecutivo, iPromotor);
								iCodigoMarca = 855;
							}
							else if(objInfoGen.iCodigoMotivo == 858)
							{
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta(2, '%s', %i, 'K', %i);", cNss, iConsecutivo, iPromotor);
								iCodigoMarca = 858;
							}
							else if(objInfoGen.iCodigoMotivo == 859)
							{
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta(2, '%s', %i, 'M', %i);", cNss, iConsecutivo, iPromotor);
								iCodigoMarca = 859;
							}
							else if(objInfoGen.iCodigoMotivo == 863)
							{
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta(2, '%s', %i, 'I', %i);", cNss, iConsecutivo, iPromotor);
								iCodigoMarca = 864;
							}
							////////////////////////////////////// FIN TIPO OPERACION '0521'ISSSTE //////////////////////////////////////////////////

							////////////////////////////////////// TIPO OPERACION '0522' BANXICO ///////////////////////////////////////////////////
							else if(objInfoGen.iCodigoMotivo == 861)
							{
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta(2, '%s', %i, 'A', %i);", cNss, iConsecutivo, iPromotor);
								iCodigoMarca = 851;
							}
							else if(objInfoGen.iCodigoMotivo == 862)
							{
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta(2, '%s', %i, 'B', %i);", cNss, iConsecutivo, iPromotor);
								iCodigoMarca = 852;
							}

							//objFG.fnArcGrabarLogx(RUTA_LOG, cSql);

							////////////////////////////////////// FIN TIPO OPERACION '0522' BANXICO //////////////////////////////////////////////////

							////////////////////////////////////// TIPO OPERACION '0523' RP Y PG IMSS /////////////////////////////////////////////////
							else if(objInfoGen.iCodigoMotivo == 2018)
							{
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta(3, '%s', %i, 'S', %i);", cNss, iConsecutivo, iPromotor);
								iCodigoMarca = 841;
							}
							else if(objInfoGen.iCodigoMotivo == 2019)
							{
								snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_afop_marcarcuenta(3, '%s', %i, 'E', %i);", cNss, iConsecutivo, iPromotor);
								iCodigoMarca = 830;
							}
							////////////////////////////////////// FIN TIPO OPERACION '0523' RP Y PG IMSS /////////////////////////////////////////////

							////////////////////////////////////// TIPO OPERACION '0524' RP Y PG ISSSTE ///////////////////////////////////////////////
							/*else if(objInfoGen.iCodigoMotivo == 0857)
							{
								sprintf(cSql, "EXECUTE FUNCTION fn_afop_marcarcuenta(3, '%s', %i, '#', %i);", cNss, iConsecutivo, iPromotor);
								//iCodigoMarca = 856;
							}
							else if(objInfoGen.iCodigoMotivo == 0859)
							{
								sprintf(cSql, "EXECUTE FUNCTION fn_afop_marcarcuenta(3, '%s', %i, '#', %i);", cNss, iConsecutivo, iPromotor);
								//iCodigoMarca = 856;
							}

							////////////////////////////////////// FIN TIPO OPERACION '0524' RP Y PG ISSSTE ////////////////////////////////////////////
							else
							{
								bTipoOperacionOk = false;
							}*/

							memset(cTexto, 0, sizeof(cTexto));
							snprintf(cTexto, sizeof(cTexto), "MARCADO DE LA CUENTA [%s]", cSql);
							objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

							bPuedeMigrar = true;
							/****************************************************************************/
							if (iCodigoMarca > 0)
							{
								objMarca.ClearResults();
								if(objMarca.Exec(cSql))
								{
									objMarca.activarCols();

									if(objMarca.leer())
									{
										memset(cMarca, 0, sizeof(cMarca));
										iCodigo = 0;
										memset(cRechazo, 0, sizeof(cRechazo));

										memmove(cMarca, objMarca.cMarca_Res, sizeof(50));
										iCodigo = objMarca.iCod_Rechazo;
										memmove(cRechazo, objMarca.cRechazo_Desc, sizeof(50));

										memset(cTexto, 0, sizeof(cTexto));
										snprintf(cTexto, sizeof(cTexto), "Nss: [%s], FolioServicio: [%i], Marca: [%s], Codigo: [%i], Rechazo: [%s]",cNss, iFolioServicio, cMarca, iCodigo, cRechazo);
										objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

										if(iCodigo == 0)
										{
											iEstatusmigracion = 1;
											memset(cTexto, 0, sizeof(cTexto));
											snprintf(cTexto, sizeof(cTexto), "Convivencia Correcta, Nss [%s], FolioServicio: [%i]", cNss, iFolioServicio);
											objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

											memset(cTextoaux,0,sizeof(cTextoaux));
											memset(cSql,0,sizeof(cSql));
											snprintf(cSql, sizeof(cSql), "Update marcaoperativaactual Set correlativo = %i WHERE nss = '%s' and codigomarca = %i",iConsecutivo,cNss,iCodigoMarca);
											objFG.fnSqlEjecutarScrip(odbcServiciosAfore, cSql, cTextoaux);

											bPuedeMigrar = true;
										}
										else if(iCodigo != 0)
										{
											bPuedeMigrar = true;
											iEstatusmigracion = 0;
											memset(cTexto, 0, sizeof(cTexto));
											snprintf(cTexto, sizeof(cTexto), "Convivencia Incorrecta, Nss [%s], FolioServicio: [%i]", cNss, iFolioServicio);
											objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

											/*0520*/ /*TOTALES IMSS*/
											if( iCodigoMotivo == 1029 || iCodigoMotivo == 1030 || iCodigoMotivo == 1031 || iCodigoMotivo == 1032 || iCodigoMotivo == 1033 || iCodigoMotivo == 1034 || iCodigoMotivo == 1052 ||
												iCodigoMotivo == 1059 || iCodigoMotivo == 2039 || iCodigoMotivo == 2016 || iCodigoMotivo == 2017 || iCodigoMotivo == 2019 || iCodigoMotivo == 2037 || iCodigoMotivo == 2038)
											{
												memset(cTextoaux,0,sizeof(cTextoaux));
												memset(cSql,0,sizeof(cSql));
												snprintf(cSql, sizeof(cSql), "update retirostotalesimss set estadosolicitud = 20, entidad = 1, codrechazoent = 66, rechazocod = %i, migracionrettotsafre = 3 "
												"where foliosolicitud = %i ",iCodigo, objInfoGen.iFolioServicio);
												objFG.fnSqlEjecutarScrip(odbcServiciosAfore, cSql, cTextoaux);
											}
											/*0521*/ /*TOTALES ISSSTE*/
											else if(iCodigoMotivo == 851 || iCodigoMotivo == 852 || iCodigoMotivo == 853 || iCodigoMotivo == 854 || iCodigoMotivo == 855 || iCodigoMotivo == 858 || iCodigoMotivo == 863)
											{
												memset(cTextoaux,0,sizeof(cTextoaux));
												memset(cSql,0,sizeof(cSql));
												snprintf(cSql, sizeof(cSql), "update retirostotalesissste set estado_solicitud = 90, codigo_rechazo = 66, migracionrettotsafre = 3 where foliosolicitud = %i ", iFolioServicio);
												objFG.fnSqlEjecutarScrip(odbcServiciosAfore, cSql, cTextoaux);
											}
											/*0522*/ /*TOTALES ISSSTE BANXICO*/
											else if (iCodigoMotivo == 861 || iCodigoMotivo == 862)
											{
												memset(cTextoaux,0,sizeof(cTextoaux));
												memset(cSql,0,sizeof(cSql));
												snprintf(cSql, sizeof(cSql), "update retirostotalesissste set estado_solicitud = 90, codigo_rechazo = 66, migracionrettotsafre = 3 where foliosolicitud = %i ", iFolioServicio);
												objFG.fnSqlEjecutarScrip(odbcServiciosAfore, cSql, cTextoaux);
											}
											/*0523*/ /*PMG IMSS*/
											else if (iCodigoMotivo == 2018  /*|| iCodigoMotivo == 2019*/)
											{
												memset(cTextoaux,0,sizeof(cTextoaux));
												memset(cSql,0,sizeof(cSql));
												snprintf(cSql, sizeof(cSql), "update pensolicitudpmgimss set estadosolicitud = 90, codigorechazo = 66, migracionrettotsafre = 3 where foliosolicitud = %i ", iFolioServicio);
												objFG.fnSqlEjecutarScrip(odbcServiciosAfore, cSql, cTextoaux);
											}

											memset(cTextoaux,0,sizeof(cTextoaux));
											memset(cSql,0,sizeof(cSql));
											snprintf(cSql, sizeof(cSql), "DELETE FROM marcaoperativaactual WHERE nss = '%s' and codigomarca = %i", cNss,iCodigoMarca);
											objFG.fnSqlEjecutarScrip(odbcServiciosAfore, cSql, cTextoaux);
										}

										/*SE ACTUALIZA LA FECHA_INI EN LA TABLA CTA_ACT_MARCA A LA FECHA Y HORA EN QUE SE GENERO LA SOLICITUD*/
										memset(cSql,0,sizeof(cSql));
										memset(cTexto,0,sizeof(cTexto));

										memset(cFechaMarca, 0, sizeof(cFechaMarca));
										memset(cHoraMarca, 0, sizeof(cHoraMarca));

										snprintf(cSql, sizeof(cSql), "SELECT TRIM(COALESCE(fechamarca,''))::char(10) AS fechamarca, "
									  			  			 "TRIM(COALESCE(hora,''))::char(8) AS hora "
													"FROM fnrettotfechahoramarca('%s',%ld);",cNss,iConsecutivo);

										objInfoFechaHoraMarca.ClearResults();
										if(objInfoFechaHoraMarca.Exec(cSql))
										{
											objInfoFechaHoraMarca.activarCols();
											if(objInfoFechaHoraMarca.leer())
											{
												memset(cFechaMarca, 0, sizeof(cFechaMarca));
												memset(cHoraMarca, 0, sizeof(cHoraMarca));

												memmove(cFechaMarca, objInfoFechaHoraMarca.cFechaMarca, sizeof(10));
												memmove(cHoraMarca, objInfoFechaHoraMarca.cHoraMarca, sizeof(8));

												snprintf(cFechaActualizaMarca, sizeof(cFechaActualizaMarca), "MDY(%c%c,%c%c,%c%c%c%c)",
												cFechaMarca[5],
												cFechaMarca[6],
												cFechaMarca[8],
												cFechaMarca[9],
												cFechaMarca[0],
												cFechaMarca[1],
												cFechaMarca[2],
												cFechaMarca[3]
												);

												memset(cSqlAux,0, sizeof(cSqlAux));
												memset(cTexto,0, sizeof(cTexto));

												memset(cSqlAux, 0, sizeof(cSqlAux));
												snprintf(cSqlAux, sizeof(cSqlAux), "EXECUTE FUNCTION fn_actualiza_fechamarca(%s,'%s'::DATETIME HOUR TO SECOND,'%s',%i);", cFechaActualizaMarca, cHoraMarca,cNss,iConsecutivo);

												objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSqlAux, iRespuesta, cTexto);

												if (iRespuesta == 1)
												{
													memset(cTexto, 0, sizeof(cTexto));
													snprintf(cTexto, sizeof(cTexto), "SE ACTUALIZO LA FECHA Y HORA CON EL FOLIO: [%i]", iFolioServicio);
													objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
													objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
												}
												else
												{
													memset(cTexto, 0, sizeof(cTexto));
													snprintf(cTexto, sizeof(cTexto), "NO SE PUDO ACTUALIZAR LA FECHA Y HORA CON EL FOLIO: [%i]", iFolioServicio);
													objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

													memset(cTexto, 0, sizeof(cTexto));
													snprintf(cTexto, sizeof(cTexto), "QUERY: [%s]", cSqlAux);

													objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
													objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
												}
											}
											else
											{
												memset(cTexto, 0, sizeof(cTexto));
												snprintf(cTexto, sizeof(cTexto), "[%s][%s] Error al leer la informacion que arroja el query: %s %i %s", __FILE__,__FUNCTION__, cSql, errno, strerror(errno));
												objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
											}
										}
										else
										{
											memset(cTexto, 0, sizeof(cTexto));
											snprintf(cTexto, sizeof(cTexto), "[%s][%s] Error al Ejecutar el Query: %s %i %s", __FILE__,__FUNCTION__, cSql, errno, strerror(errno));
											objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
										}
									}
									else
									{
										memset(cTexto, 0, sizeof(cTexto));
										snprintf(cTexto, sizeof(cTexto), "[%s][%s] Error al leer la informacion: %s %i %s", __FILE__,__FUNCTION__, cSql, errno, strerror(errno));
										objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
									}
								}
								else
								{
									memset(cTexto, 0, sizeof(cTexto));
									snprintf(cTexto, sizeof(cTexto), "[%s][%s] Error al Ejecutar el Query: %s %i %s", __FILE__,__FUNCTION__, cSql, errno, strerror(errno));
									objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
									shRet = ERR_EXEC_SQL;

									bPuedeMigrar = true;
								}
							}
							/****************************************************************************/
							if (bPuedeMigrar == true)
							{
								//SE HACE EL LLAMADO AL LLENADO DE TODAS LAS TABLAS.

								//SECCION PARA LLENADO DE: BIOMETRICOS

								/*
								//VACIADO A BIOMETRICOS
								memset(cSql,0,sizeof(cSql));
								memset(cTexto,0,sizeof(cTexto));
								iIdpago = 1;  //QUITARRRRRRRRRRRRRRRR ESTA ASIGNACION: SOLO ES PARA PRUEBAS
								if (iTipoIdentificador > 0 && iTipoSolicitante > 0 && iIdpago > 0)
								{
									sprintf(cSql, "SELECT fnrettotguardainfobiometrica FROM fnrettotguardainfobiometrica(%i,'%s',%i,'%s','%s','%s','%s',%i,%i,%i);", iFolioServicio, cNss, iConsecutivo, cSelloVoluntad, cSelloFuncionario, cCurpAgenteServicio, cCurpFuncionario, iTipoIdentificador, iTipoSolicitante, iIdpago);
									objFG.fnSqlConsultarNumero(odbcAforeGlobal,cSql,iRespuesta, cTexto);

									memset(cSql,0,sizeof(cSql));
									memset(cTexto,0,sizeof(cTexto));
									sprintf(cSql, "EXECUTE FUNCTION fn_rettotguardainfobiometrica_infx(%i,'%s',%i,'%s','%s','%s','%s',%i,%i,%i);", iFolioServicio, cNss, iConsecutivo, cSelloVoluntad, cSelloFuncionario, cCurpAgenteServicio, cCurpFuncionario, iTipoIdentificador, iTipoSolicitante, iIdpago);
									objFG.fnSqlConsultarNumero(odbcInfxSafreaf,cSql,iRespuesta, cTexto);
								}
								else
								{
									sprintf(cTexto, "Folio de Servicio: %i, NO tiene un TipoIdentificador: %i, TipoSolicitante: %i, TipoPago: %i Verifique...", iFolioServicio, iTipoIdentificador, iTipoSolicitante, iIdpago);
									objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
								}
								//FIN DE VACIADO A BIOMETRICOS
								*/

								/*************************************INICIA LA MIGRACION PARA REC SERVICIOS*******************************************/
								objFG.fnArcGrabarLogx(RUTA_LOG,"***********************************REC _SOLICITUD***************************************");

								memset(cSqlAux, 0, sizeof(cSqlAux));
								snprintf(cSqlAux, sizeof(cSqlAux), "EXECUTE FUNCTION fn_afop_iud_rec_solicitud(%i,%i,'%s','%s',%i,%i,%i,%i,%i,'%s','%s','%s','%s','',%i,%i,'%s','',%i,%i);",
													1,
													iFolioServicio,
													cCurp,
													cNss,
													iFolioSolicitud,
													iOrigenServicio,
													iCodigoMedio,
													iCodigoTipo,
													iCodigoMotivo,
													cTipoServicio,
													cFechaReclamo,
													cFechaInicio,
													cFechaFinEstimada,
													//cFechaFinReal,
													iPromotor,
													iPromotor,
													cFechaAlta,
													//'Z',
													objInfoGen.iTipoSolicitud,
													iCodigoTermino
													);

								objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSqlAux, iRespuestaQuery, cTexto);

								if (iRespuestaQuery > 0)
								{
									memset(cTexto, 0, sizeof(cTexto));
									snprintf(cTexto, sizeof(cTexto), "SE MIGRO LA INFORMACION A REC SOLCITUD CON EL FOLIO: [%i]", iFolioServicio);
									objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
									objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");

									/*SE ACTUALIZA LA HORA FIN EN LA REC_SOLCITUD*/
									memset(cTextoaux,0,sizeof(cTextoaux));
							 		memset(cSql,0,sizeof(cSql));
							 		snprintf(cSql, sizeof(cSql), "UPDATE rec_solicitud SET tiempo_fin = '%s' WHERE folio_rec = %i AND n_seguro ='%s' ",cHoraFin,iFolioServicio,cNss);

									objFG.fnSqlEjecutarScrip(odbcInfxSafreaf, cSql, cTextoaux);
								}
								else
								{
									memset(cTexto, 0, sizeof(cTexto));
									snprintf(cTexto, sizeof(cTexto), "NO SE PUDO MIGRAR LA INFORMACION A REC SOLCITUD CON EL FOLIO: [%i]", iFolioServicio);
									objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

									memset(cTexto, 0, sizeof(cTexto));
									snprintf(cTexto, sizeof(cTexto), "QUERY: [%s]", cSqlAux);

									objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
									objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
								}

								/*************************************INICIA LA MIGRACION PARA RETMOTIVORETIRO*******************************************/
								objFG.fnArcGrabarLogx(RUTA_LOG,"***********************************RETMOTIVORETIRO***************************************");

								char 	cFechaReclamoRetiro[10]  = {0};

								snprintf(cFechaReclamoRetiro, sizeof(cFechaReclamoRetiro), "%c%c%c%c-%c%c-%c%c",
								cFechaReclamo[4],
								cFechaReclamo[5],
								cFechaReclamo[6],
								cFechaReclamo[7],
								cFechaReclamo[0],
								cFechaReclamo[1],
								cFechaReclamo[2],
								cFechaReclamo[3]
								);

								memset(cSqlAux, 0, sizeof(cSqlAux));
								snprintf(cSqlAux, sizeof(cTexto), "EXECUTE FUNCTION fn_guardarretmotivoretiroreplicart(%i,%i,'%s','%s','%s');",
													iFolioServicio,
													iMotivoretiro,
													cTipoServicio,
													cNss,
													cFechaReclamoRetiro
													);

								objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSqlAux, iRespuestaQuery, cTexto);

								if (iRespuestaQuery == 1)
								{
									memset(cTexto, 0, sizeof(cTexto));
									snprintf(cTexto, sizeof(cTexto), "SE MIGRO LA INFORMACION A RETMOTIVORETIRO CON EL FOLIO: [%i]", iFolioServicio);
									objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
									objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
								}
								else
								{
									memset(cTexto, 0, sizeof(cTexto));
									snprintf(cTexto, sizeof(cTexto), "NO SE PUDO MIGRAR LA INFORMACION A RETMOTIVORETIRO CON EL FOLIO: [%i]", iFolioServicio);
									objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

									memset(cTexto, 0, sizeof(cTexto));
									snprintf(cTexto, sizeof(cTexto), "QUERY: [%s]", cSqlAux);

									objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
									objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
								}
								//CURP DEL SOLICITANTE BENEFICIARIO
								memset(stSelloBiometricoSuv.cCurpSolicitante, 0, sizeof(stSelloBiometricoSuv.cCurpSolicitante));

								//validacion para el tiposolicitante
								if(iTipoSolicitante == ESBENEFICIARIO)
								{
									memset(cSql,0,sizeof(cSql));
									memset(cTexto,0,sizeof(cTexto));
									snprintf(cSql, sizeof(cSql), " SELECT COALESCE(TRIM(curpbenef),'') FROM retbeneficiario  WHERE foliosolicitud = %i ;",iFolioServicio);
									objFG.fnArcGrabarLogx(RUTA_LOG,cSql);
									CObtenerCurpSolBeneficiario objSolCurp(odbcServiciosAfore);
									if(objSolCurp.Exec(cSql))
									{
										objSolCurp.activarCols();
										if(objSolCurp.leer())
										{
											memset(cCurpBen, 0, sizeof(cCurpBen));
											memmove(cCurpBen, objSolCurp.curpbenef, sizeof(18));
											//memcpy(stSelloBiometricoSuv.cCurpSolBene, cCurpBen, strlen(cCurpBen));
											memmove(stSelloBiometricoSuv.cCurpSolicitante, cCurpBen, sizeof(cCurpBen));

											memset(cTexto, 0, sizeof(cTexto));
											snprintf(cTexto, sizeof(cTexto), "ES BENEFICIARIO LA CURP: [%s]",cCurp);
											objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
										}
									}
									else
									{
										memset(cTexto, 0, sizeof(cTexto));
										snprintf(cTexto, sizeof(cTexto), "NO SE PUDO OBTENER LA INFORMACION DE CURP DEL BENEFICIARIO CON EL FOLIO: [%i]", iFolioServicio);
										objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
									}
								}
								else
								{
									memmove(stSelloBiometricoSuv.cCurpSolicitante, cCurp, sizeof(cCurp));
									memset(cTexto, 0, sizeof(cTexto));
									snprintf(cTexto, sizeof(cTexto), "NO ES BENEFICIARIO EL FOLIO: [%i]  CURP: [%s]", iFolioServicio,cCurp);
									objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
								}

								///LLenado de la estructura
								//memcpy(cSellotrabajador, objInfoGen.cSellotrabajador, 14);
								memmove(stSelloBiometricoSuv.cNss, cNss, sizeof(cNss));
								//memcpy(stSelloBiometricoSuv.cIdsolicitante, iTipoSolicitante,3);
								//memcpy(stSelloBiometricoSuv.cCurpSolicitante, cCurp, strlen(cCurp));
								memmove(stSelloBiometricoSuv.cSellotrabajador, cSellotrabajador, sizeof(cSellotrabajador));
								memmove(stSelloBiometricoSuv.cCurpAgente, cCurpAgenteServicio, sizeof(cCurpAgenteServicio));
								stSelloBiometricoSuv.iConsecutivo		=iConsecutivo;
								stSelloBiometricoSuv.iIdsolicitante	=iTipoSolicitante;

								/*************************************INICIA LA MIGRACION PARA BENEFICIARIOS*******************************************/
								objBen.ReplicarBeneficiarios(iFolioServicio,odbcInfxSafreaf,odbcServiciosAfore);

								/*if (objInfoGen.iCodigoMotivo == 2016 || objInfoGen.iCodigoMotivo == 2017 || objInfoGen.iCodigoMotivo == 2019 || objInfoGen.iCodigoMotivo == 2037
									|| objInfoGen.iCodigoMotivo == 2038 || objInfoGen.iCodigoMotivo == 2039)*/ //CONDICIONES PARA 238
								if(
									objInfoGen.iCodigoMotivo ==  1029 ||
									objInfoGen.iCodigoMotivo ==  1030 ||
									objInfoGen.iCodigoMotivo ==  1031 ||
									objInfoGen.iCodigoMotivo ==  1032 ||
									objInfoGen.iCodigoMotivo ==  1033 ||
									objInfoGen.iCodigoMotivo ==  1034 ||
									objInfoGen.iCodigoMotivo ==  1052 ||
									objInfoGen.iCodigoMotivo ==  1059 ||
									objInfoGen.iCodigoMotivo ==  2039 ||
									objInfoGen.iCodigoMotivo ==  2016 ||
									objInfoGen.iCodigoMotivo ==  2017 ||
									objInfoGen.iCodigoMotivo ==  2019 ||
									objInfoGen.iCodigoMotivo ==  2037 ||
									objInfoGen.iCodigoMotivo ==  2038)  //CONDICIONES PARA EL 271
								{
									/**********************************INICIA LA MIGRACION PARA RETIROS TOTALES IMSS***************************************/
									objRetTotImss.setStSelloBiometricoSuv(&stSelloBiometricoSuv);
									objRetTotImss.ReplicarRetirosTotalesImss(iFolioServicio,odbcInfxSafreaf,odbcServiciosAfore);
								}

								/**********************************INICIA LA MIGRACION PARA REC SERVICIOS TIMBRADO*************************************/
								objRecServTimbrado.ReplicarRecServiciosTimbrado(iFolioServicio,odbcInfxSafreaf,odbcServiciosAfore);

								if (objInfoGen.iCodigoMotivo == 851 || objInfoGen.iCodigoMotivo == 852 || objInfoGen.iCodigoMotivo == 853 || objInfoGen.iCodigoMotivo == 854
									|| objInfoGen.iCodigoMotivo == 855 || objInfoGen.iCodigoMotivo == 858 || objInfoGen.iCodigoMotivo == 863 ||
									objInfoGen.iCodigoMotivo == 860 || objInfoGen.iCodigoMotivo == 861 || objInfoGen.iCodigoMotivo == 862)
								{
									/**********************************INICIA LA MIGRACION PARA RETIROS TOTALES ISSSTE*************************************/
									snprintf(cTexto, sizeof(cTexto), "CODIGO MOTIVO %i FOLIO: %i CURP: %s", objInfoGen.iCodigoMotivo,iFolioServicio,cCurp);
									objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
									objRetTotIssste.setStSelloBiometricoSuv(&stSelloBiometricoSuv);
									objRetTotIssste.saveSelloBiometricoSuv(odbcInfxSafreaf);
									objRetTotIssste.ReplicarRetirosTotalesIssste(iFolioServicio,odbcInfxSafreaf,odbcServiciosAfore);

									/*****************************INICIA LA MIGRACION PARA RET ISSSTE CONSTANCIA*******************************************/
									objRetSolConstancia.ReplicarRetSolIsssteConstancia(iFolioServicio,odbcInfxSafreaf,odbcServiciosAfore);
								}

								if (objInfoGen.iCodigoMotivo == 2018 /*|| objInfoGen.iCodigoMotivo == 2019*/)
								{
									/**********************************INICIA LA MIGRACION PARA PMG IMSS***************************************************/
									objRetTotPmgIms.setStSelloBiometricoSuv(&stSelloBiometricoSuv);
									objRetTotPmgIms.ReplicarRetirosTotalesPmgImss(iFolioServicio,odbcInfxSafreaf,odbcServiciosAfore);

									/**********************************INICIA LA MIGRACION PENDETALLE70***************************************************/
									objPenDet70.ReplicarDetalleOp70(iFolioServicio,odbcInfxSafreaf,odbcServiciosAfore);
								}

								/*****************************INICIA LA MIGRACION PARA RET SOLICITANTE*************************************************/
								objSolicitante.ReplicarSolicitante(iFolioServicio,odbcInfxSafreaf,odbcServiciosAfore);

								/*****************************INICIA LA MIGRACION PARA RET CONSTANCIA RETENCION****************************************/
								objRetencion.ReplicarRetConstanciaRetencion(iFolioServicio,odbcInfxSafreaf,odbcServiciosAfore);

								/*****************************INICIA LA MIGRACION PARA RETFOLIOINFONAVIT***********************************************/
								objRetFolioInfonavit.ReplicarRetFolioInfonavit(iFolioServicio,odbcInfxSafreaf,odbcServiciosAfore);

								/*****************************INICIA LA MIGRACION PARA RET NOTIFICA VIVIENDA***********************************************/
								objRetNotVivienda.ReplicarRetNotifVivienda(iFolioServicio,odbcInfxSafreaf,odbcServiciosAfore);

								/*****************************INICIA LA MIGRACION PARA RET CONFORMIDAD***********************************************/
								objRetConformidad.ReplicarRetConformidad(iFolioServicio,odbcInfxSafreaf,odbcServiciosAfore);

								/*****************************INICIA LA MIGRACION PARA ret_ctr_benef_det***********************************************/
								
								if(
									iCodigoMotivo ==  1029 || iCodigoMotivo ==  1030 || iCodigoMotivo ==  1031 ||
									iCodigoMotivo ==  1052 || iCodigoMotivo ==  1059 || iCodigoMotivo ==  2039 ||
									iCodigoMotivo ==  2017 || iCodigoMotivo ==  2037 || iCodigoMotivo ==  2038
									)  //CONDICIONES PARA EL 1979 -> 1029,1030,1031,1052,1059,2017,2037,2038,2039
								{
									/****************************INICIA LA MIGRACION PARA CONTROL BENEFICIARIOS RETIROS TOTALES IMSS****************************/
									objBen.replicaControlBeneficiarios(iFolioServicio, iConsecutivo, iCodigoMotivo, cTipoRetiro, odbcInfxSafreaf, odbcServiciosAfore);
								}

								/*SE ACTUALIZAN LOS FOLIOS MIGRADOS*/
								memset(cSql, 0, sizeof(cSql));
								snprintf(cSql, sizeof(cSql), "select * from fnrettotactualizarecservicios(%i,%i,%i,'%s');", 2,iConsecutivo, iFolioServicio,cNss);
								objFG.fnSqlConsultarTexto(odbcAforeGlobal,(char*)cSql, (char*)cOutTexto);
							}
						}
						else
						{
							/*
							if(objInfoGen.iCodigoMotivo == 1024 || objInfoGen.iCodigoMotivo == 1025)
							{
								if(objInfoGen.iCodigoMotivo == 1024)
								{
									iCodigoMarca = 875;
								}
								else if(objInfoGen.iCodigoMotivo == 1025)
								{
									iCodigoMarca = 870;
								}
								memset(cTextoaux,0,sizeof(cTextoaux));
								memset(cSql,0,sizeof(cSql));
								if(iSellovalida == 1)
								{
									sprintf(cSql, "update retirosparciales set estadosolicitud = 20, entidad = 1, codigorechazoent = 130, migracionretparsafre = 3 "
									"where foliosolicitud = %i ",objInfoGen.iFolioServicio);

									memset(cTexto, 0, sizeof(cTexto));
									sprintf(cTexto, "[%s][%s] La Solicitud es Rechazada por Sello de Voluntad Rechazado Nss [%s]", __FILE__,__FUNCTION__,cNss);
									objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
								}
								else if(iSellovalida == 2)
								{
									sprintf(cSql, "update retirosparciales set estadosolicitud = 20, entidad = 1, codigorechazoent = 131, migracionretparsafre = 3 "
									"where foliosolicitud = %i ",objInfoGen.iFolioServicio);

									memset(cTexto, 0, sizeof(cTexto));
									sprintf(cTexto, "[%s][%s] La Solicitud es Rechazada por Sello de Voluntad Nulo Nss [%s]", __FILE__,__FUNCTION__,cNss);
									objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
								}
								objFG.fnSqlEjecutarScrip(odbcServiciosAfore, cSql, cTextoaux);

								memset(cTextoaux,0,sizeof(cTextoaux));
								memset(cSql,0,sizeof(cSql));
								sprintf(cSql, "DELETE FROM marcaoperativaactual WHERE nss = '%s' and codigomarca = %i", cNss,iCodigoMarca);
								objFG.fnSqlEjecutarScrip(odbcServiciosAfore, cSql, cTextoaux);

							}
							else if(objInfoGen.iCodigoMotivo == 2024)
							{
								iCodigoMarca = 856;
								memset(cTextoaux,0,sizeof(cTextoaux));
								memset(cSql,0,sizeof(cSql));
								if(iSellovalida == 1)
								{
									sprintf(cSql, "update retirosparcialesissste set estadosolicitud = 90, codigorechazo = 130, migracionretparsafre = 3 where foliosolicitud = %i ", objRes.iFolioServicio);
									objFG.fnSqlEjecutarScrip(odbcServiciosAfore, cSql, cTextoaux);

									memset(cTexto, 0, sizeof(cTexto));
									sprintf(cTexto, "[%s][%s] La Solicitud es Rechazada por Sello de Voluntad Rechazado Nss [%s]", __FILE__,__FUNCTION__,cNss);
									objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
								}
								if(iSellovalida == 2)
								{
									sprintf(cSql, "update retirosparcialesissste set estadosolicitud = 90, codigorechazo = 131, migracionretparsafre = 3 where foliosolicitud = %i ", objRes.iFolioServicio);
									objFG.fnSqlEjecutarScrip(odbcServiciosAfore, cSql, cTextoaux);

									memset(cTexto, 0, sizeof(cTexto));
									sprintf(cTexto, "[%s][%s] La Solicitud es Rechazada por Sello de Voluntad Nulo Nss [%s]", __FILE__,__FUNCTION__,cNss);
									objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
								}

								memset(cTextoaux,0,sizeof(cTextoaux));
								memset(cSql,0,sizeof(cSql));
								sprintf(cSql, "DELETE FROM marcaoperativaactual WHERE nss = '%s' and iCodigoMarca = %i", cNss,iCodigoMarca);
								objFG.fnSqlEjecutarScrip(odbcServiciosAfore, cSql, cTextoaux);
							}
							*/
						}
					}
				}
				else if(iExisteBD == 0)
				{
					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, sizeof(cTexto), "[%s][%s] La solicitud No cuenta con una clave unica de servicio vigente, Para el Foliosolicitud:[%i]",__FILE__,__FUNCTION__,iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
				}
			
			}
			else if(iExisteBD == 0)
			{
				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, sizeof(cTexto), "[%s][%s] La solicitud No se Encuentra en la BD ServiciosAfore,Favor de Revisar Foliosolicitud:[%i]",__FILE__,__FUNCTION__,iFolioServicio);
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
			}
		}//end while

		memset(cTexto, 0, sizeof(cTexto));
		snprintf(cTexto, sizeof(cTexto), "[%s][%s] TotalRegistros procesados : %i",__FILE__,__FUNCTION__, iContRegistros);
		objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

	}//end if exec
	else
	{
		memset(cTexto, 0, sizeof(cTexto));
		snprintf(cTexto, sizeof(cTexto), "[%s][%s] Error al Ejecutar el Query: %s %i %s", __FILE__,__FUNCTION__, cSql, errno, strerror(errno));
		objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
		shRet = ERR_EXEC_SQL;
	}

	return shRet;
}
