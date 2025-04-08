#define	SERV_DATABASE_AFO_GLOBAL			3
#define	SERV_DATABASE_INFORMIX				2

#define	USERSERVICIOSAFORE					"sysserviciosafore"
#define	BDSERVICIOSAFORE					"serviciosafore"


#define IP_ADMONAFORE						"/sysx/progs/afore/ipadmonafore.dat"
#define SIZE_BUFF_DAT						33

#define	USERADMONAFORE						"sysadmonafore"
#define	BDADMONAFORE						"admonafore"
#define	PASSADMONAFORE						"42e5de99b3b33b7905ad2bb8c29f1245"

#define	USERAFOREGLOBAL						"sysaforeglobal"
#define	BDAFOREGLOBAL						"aforeglobal"
#define	PASSAFOREGLOBAL						"a2901ba525795f1fd311642f98c9f160"

#define BD_SAFRE_AF							"safre_af"
#define USR_BD_SAFRE_AF						"syscoppel"
#define PWD_BD_SAFRE_AF						"545f78b743"

#define RUTA_LOG							"/sysx/progs/log/migracionderetirostotales"
#define RUTA_PASE 							"/sysx/progs/pase"

#define SELLOVACIO							" "
#define SINSELLO							"0"

//definicion para verificar
#define ESBENEFICIARIO                      2							   
//PARA EL MANEJO DE ERRORES
#define DEFAULT___										 0
#define OK__											 1
#define	ERR_NO_EXISTE_ARCHIVO_CNF						-1
#define	ERR_LECTURA_ARCHIVO_CNF							-2
#define ERR_EXEC_SQL									-3
#define ERR_CNX_BASE_DATO								-4
#define ERR_NO_HAY_REG_BD								-5
#define ERR_RESERVAR_MEM								-6
#define ERR_ACCEDER_SHM									-7
#define ERR_CONSULTA_AF_CONTROL							-8
#define ERR_CNX_INFX									-9
#define ERR_NO_EXISTEN_REG_REPLICAR		 				-17
#define SIN_FOLIO_CARGO_SIN_ESTADO_VALIDO 				-12
#define FOLIO_YA_REPLICADO								-13
#define ERROR_GENERAR_ARCHIVO_REPLICA					-14
#define ERROR_EJECUTAR_REVERSO							-15
#define ERROR_EN_CIFRAS									-16
#define	ERROR_AL_CREAR_ARCHIVO							-17
#define	ERROR_AL_ESCRIBIR_ARCHIVO						-18
		
#define TOTAL_OPCIONES									10
#define REPLICA_OPERACION_04							100
#define REPLICA_SOLICITUD_ADICIONALES					1
#define REPLICA_NIVEL_ESTUDIO							2
#define REPLICA_ACTUALIZACION_EIBENEFICIARIO			3
#define REPLICA_CURP_BENEFICIARIO_TRASPASOS_DIVERSOS	4