void esp8266_init();

/*** Global variables and enum of websocket message types between server/client ***/

long CurrADC, RefADC, BaseADC; // hx711 scale variables
float RefKG = 2.0; // Reference weight as RefADC,BaseADC as empty 

enum WS_client_type {SET_REF, SET_BASE, SET_REFKG, SET_UXTIME};
char* WS_client_type_array[]={"SET_REF", "SET_BASE", "SET_REFKG", "SET_UXTIME"};
enum WS_server_type {SET_REF_OK, SET_BASE_OK, SET_REFKG_OK, SET_UXTIME_OK, ON_CHG} ;
char* WS_server_type_array[]={"SET_REF_OK", "SET_BASE_OK", "SET_REFKG_OK", "SET_UXTIME_OK", "ON_CHG"};

