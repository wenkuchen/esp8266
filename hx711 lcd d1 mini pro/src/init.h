void esp8266_init();

/*** Global variables and enum of websocket message types between server/client ***/
extern long CurrADC;
extern long LastADC;
extern long RefADC;
extern long BaseADC; // hx711 scale variables
extern float RefKG; // Reference weight as RefADC,BaseADC as empty 

typedef enum { ACTIVE, IDLE} scaleStateEnum;
extern scaleStateEnum scaleState;
typedef enum {SET_REF, SET_BASE, SET_REFKG, SET_UXTIME} toServer_WStypes_enum;
extern toServer_WStypes_enum toServer_WSenum;
typedef enum {SET_REF_OK, SET_BASE_OK, SET_REFKG_OK, SET_UXTIME_OK, ON_CHG} toClient_WStypes_enum;
extern toClient_WStypes_enum toClient_WSenum;
typedef enum {ON_UPDATE,BASE_ADC,REF_ADC,REF_KG} update_scale_WSenum;
extern update_scale_WSenum update_scaleWSenum;

extern int toServer_WStypes_len;
extern String toClient_WStypes;
extern int toClient_WStypes_len;
extern String update_scale_WS;
