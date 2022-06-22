void esp8266_init();
void notifyWSclients(const char* );

/*** Global variables and enum of websocket message types between server/client ***/
extern long CurrADC;
extern long LastADC;
extern long RefADC;
extern long BaseADC; // hx711 scale variables
extern float RefKG; // Reference weight as RefADC,BaseADC as empty 
typedef enum {ACTIVE, IDLE
} scaleStateEnum;
typedef enum {SET_REF, SET_BASE, SET_REFKG, SET_UXTIME
} toServer_WStypes_enum;
typedef enum {SET_REF_OK, SET_BASE_OK, SET_REFKG_OK, SET_UXTIME_OK, ON_CHG
} toClient_WStypes_enum;
typedef enum {ON_UPDATE,BASE_ADC,REF_ADC,REF_KG
} update_scale_WSenum;

#define ToServer_WStypes "SET_REF,SET_BASE,SET_REFKG,SET_UXTIME"
#define ToClient_WStypes "SET_REF_OK,SET_BASE_OK,SET_REFKG_OK,SET_UXTIME_OK,ON_CHG";
#define Update_Scale_WS "ON_UPDATE,CURR_ADC123,BASE_ADC123,REF_ADC123,REF_KG23";
