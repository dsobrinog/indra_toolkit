/*
******************************************************************************
*ID01                           IDENTIFICACION    
*
*    FICHERO   : HxComServ.h                   ID        :   
*    PROGRAMA  : STSS                            FECHA     : 27/Mar/2006
*    SISTEMA   : FMS&FBMS                        REVISION  : $Revision: 1.5 $
*    SUBSISTEMA: HOST                            AUTOR     : Ejecutivo
*    MODULO    : EJECUTIVO PRINCIPAL             COMPA�IA  : INDRA
******************************************************************************
*DF02                       DESCRIPCION FUNCIONAL            
*
*    Cabeceras funciones para comunicar el servidor RPC y el monitor de datos
*
******************************************************************************
*HC03                        HISTORIA DE CAMBIOS  
*
*    ED/REV     FECHA                                           AUTOR
*    N�-NCI:    DESCRIPCION DEL CAMBIO  
*
*    $Log: HxComServ.h,v $
*
*
*****************************************************************************/
/*%FIN*/

#ifndef _INDRA_SIM_EXECUTIVE_HXCOMSERV_H_
#define _INDRA_SIM_EXECUTIVE_HXCOMSERV_H_

#include <rpc/rpc.h>

#ifdef __cplusplus
extern "C"
{
#endif

    struct escribo_1_argument
    {
        char* arg1;
        char* arg2;
    };
    typedef struct escribo_1_argument escribo_1_argument;

    struct lista_monitor_argument
    {
        int   arg1;
        char* arg2;
    };
    typedef struct lista_monitor_argument lista_monitor_argument;

    struct lista_monitor_get_argument
    {
        int arg1;
    };
    typedef struct lista_monitor_get_argument lista_monitor_get_argument;

    struct lista_monitor_end_argument
    {
        int arg1;
    };
    typedef struct lista_monitor_end_argument lista_monitor_end_argument;

    struct monitor_close_argument
    {
        int arg1;
    };
    typedef struct monitor_close_argument monitor_close_argument;

//@@@@@@@@@@@@@@ #define DATDINPROG 0x20000001
#define DATDINPROG 0x50000001
#define DATDINVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define consulto 1
    extern int* consulto_1(const char*, CLIENT*);
    extern int* consulto_1_svc(char*, struct svc_req*);
#define leo 2
    extern char** leo_1(const char*, CLIENT*);
    extern char** leo_1_svc(char*, struct svc_req*);
#define escribo 3
    extern void* escribo_1(char*, const char*, CLIENT*);
    extern void* escribo_1_svc(char*, char*, struct svc_req*);
#define Get_var_address_ 4
    extern char** get_var_address__1(char*, CLIENT*);
    extern char** get_var_address__1_svc(char*, struct svc_req*);
#define lista_Monitor_substring_begin_ 5
    extern void* lista_monitor_substring_begin__1(int, char*, CLIENT*);
    extern void* lista_monitor_substring_begin__1_svc(int, char*, struct svc_req*);
#define lista_Monitor_substring_get_ 6
    extern char** lista_monitor_substring_get__1(int, CLIENT*);
    extern char** lista_monitor_substring_get__1_svc(int, struct svc_req*);
#define lista_Monitor_substring_end_ 7
    extern bool_t* lista_monitor_substring_end__1(int, CLIENT*);
    extern bool_t* lista_monitor_substring_end__1_svc(int, struct svc_req*);
#define killServer 8
    extern void* killserver_1(CLIENT*);
    extern void* killserver_1_svc(struct svc_req*);
#define getmodulename 9
    extern char** getmodulename_1(int, CLIENT*);
    extern char** getmodulename_1_svc(int, struct svc_req*);
#define initTiempoEjecutivo 10
    extern void* inittiempoejecutivo_1(CLIENT*);
    extern void* inittiempoejecutivo_1_svc(struct svc_req*);
#define initTiempoModulos 11
    extern void* inittiempomodulos_1(CLIENT*);
    extern void* inittiempomodulos_1_svc(struct svc_req*);
#define monitor_close_ 12
    extern void* monitor_close_1(int, CLIENT*);
    extern void* monitor_close_1_svc(int, struct svc_req*);
#define getmodulenameaux 13
    extern char** getmodulenameaux_1(int, CLIENT*);
    extern char** getmodulenameaux_1_svc(int, struct svc_req*);

    extern int datdinprog_1_freeresult(SVCXPRT*, xdrproc_t, caddr_t);

    enum RPCSRV_EXECUTIVE_READABLE_SIMPLE_VARIABLES
    {
        R_KSTATUSX,
        R_OPERMODE,
        R_SIMSTATUS,
        R_CYCLE,
        R_COMMAND,
        R_EJNUM,
        R_EJPID,
        NUM_RPCSERV_EXECUTIVE_READABLE_SIMPLE_VARIABLES
    };

    extern const char* rpcserv_executive_readable_simple_variables[];

#else /* K&R C */
#define consulto                       1
extern int*    consulto_1();
extern int*    consulto_1_svc();
#define leo                            2
extern char**  leo_1();
extern char**  leo_1_svc();
#define escribo                        3
extern void*   escribo_1();
extern void*   escribo_1_svc();
#define Get_var_address_               4
extern char**  get_var_address__1();
extern char**  get_var_address__1_svc();
#define lista_Monitor_substring_begin_ 5
extern void*   lista_monitor_substring_begin__1();
extern void*   lista_monitor_substring_begin__1_svc();
#define lista_Monitor_substring_get_   6
extern char**  lista_monitor_substring_get__1();
extern char**  lista_monitor_substring_get__1_svc();
#define lista_Monitor_substring_end_   7
extern bool_t* lista_monitor_substring_end__1();
extern bool_t* lista_monitor_substring_end__1_svc();
#define killServer                     8
extern void*   killserver_1();
extern void*   killserver_1_svc();
#define getmodulename                  9
extern char**  getmodulename_1();
extern char**  getmodulename_1_svc();
#define initTiempoEjecutivo            10
extern void*   inittiempoejecutivo_1();
extern void*   inittiempoejecutivo_1_svc();
#define initTiempoModulos              11
extern void*   inittiempomodulos_1();
extern void*   inittiempomodulos_1_svc();
#define monitor_close_                 12
extern void*   monitor_close_1();
extern void*   monitor_close_1_svc();
#define getmodulenameaux               13
extern char**  getmodulenameaux_1();
extern char**  getmodulenameaux_1_svc();

extern int    datdinprog_1_freeresult();
#endif /* K&R C */

    /* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
    extern bool_t xdr_escribo_1_argument(XDR*, escribo_1_argument*);
    extern bool_t xdr_lista_monitor_argument(XDR*, lista_monitor_argument*);
    extern bool_t xdr_lista_monitor_get_argument(XDR*, lista_monitor_get_argument*);
    extern bool_t xdr_lista_monitor_end_argument(XDR*, lista_monitor_end_argument*);
    extern bool_t xdr_monitor_close_argument(XDR*, monitor_close_argument*);
#else  /* K&R C */
extern bool_t xdr_escribo_1_argument();
extern bool_t xdr_lista_monitor_argument();
extern bool_t xdr_lista_monitor_get_argument();
extern bool_t xdr_monitor_close_argument();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif
extern int         pasa_aEntero(char* cadena);
extern int         get_rpcVersion(int num_ej);
extern const char* get_rpcLocalServer();

#endif // _INDRA_SIM_EXECUTIVE_HXCOMSERV_H_
