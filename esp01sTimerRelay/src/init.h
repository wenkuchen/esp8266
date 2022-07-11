void esp8266_init();
void notifyWSclients(const char* );

/*** Global variables and enum of websocket message types between server/client ***/
typedef enum {ACTIVE, IDLE
} timerStateEnum;
typedef enum {SET_REF, SET_BASE, SET_REFKG, SET_UXTIME
} toServer_WStypes_enum;
typedef enum {ON_CHG,SET_REF_OK, SET_BASE_OK, SET_REFKG_OK, SET_UXTIME_OK
} toClient_WStypes_enum;
typedef enum {OP_CODE,CURR_ADC,BASE_ADC,REF_ADC,REF_KG
} update_scale_WSenum;

#define ToServer_WStypes "SET_REF,SET_BASE,SET_REFKG,SET_UXTIME"
#define ToClient_WStypes "ON_CHG,SET_REF_OK,SET_BASE_OK,SET_REFKG_OK,SET_UXTIME_OK"
