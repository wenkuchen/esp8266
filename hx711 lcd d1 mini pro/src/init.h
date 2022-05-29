void esp8266_init();
typedef enum {
    SET_UTIME,SET_REFADC,SET_BASEADC,LCD_MSG,
    GET_ADC, GET_INFO
} WS_msg_type;