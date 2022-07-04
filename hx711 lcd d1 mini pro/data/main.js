var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

var dCurrADC = document.querySelector("#CurrADC");
var dBaseADC = document.querySelector("#BaseADC");
var dRefADC = document.querySelector("#RefADC");
var dRefKG = document.querySelector("#CurrADC");

var dSetBase = document.querySelector("#SetBase");
var dSetRef = document.querySelector("#SetRef");
var dSetRefKG = document.querySelector("#SetRefKG");
var dInputKG = document.querySelector("#InputKG");

var dWeightInKg = document.querySelector("#WeightInKg");
var dWeightInLb = document.querySelector("#WeightInLb");

window.addEventListener('load', onload);

function onload(event) {
    initWebSocket();
    initButtons();
}

function initWebSocket() {
    console.log('Trying to open a WebSocket connection…ddd');
    websocket = new WebSocket(gateway);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;
}

function onOpen(event) {
    console.log('Connection opened 1!');
    console.log(event);
    //let ws_array = document.body.dataset.ToServerWStypes.split(/[ ,]+/);
    //console.log(ws_array);
}

function onMessage(event) {
//document.getElementById('state').innerHTML = event.data;
//console.log(event.data);
    
    console.log("event data: ");
    console.log(event.data);
    console.log(typeof(event.data));

    handleWSmessage(event.data);
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

function updateScaleDOMs(scale_obj){
    //typedef enum {CURR_ADC,BASE_ADC,REF_ADC,REF_KG} 
    //update_scale_WSenum;
    let curr_adc = parseInt(scale_obj.curr_adc);
    let base_adc = parseInt(scale_obj.base_adc);
    let ref_adc = parseInt(scale_obj.ref_adc);
    let ref_kg = parseFloat(scale_obj.ref_kg);

    dCurrADC.innerHTML = "Current ADC:" + scale_obj.curr_adc;
    if(!scale_obj.hasOwnProperty('curr_adc')) window.alert('bad obj key 1');
    dBaseADC.innerHTML = "Base ADC: " + scale_obj.base_adc;
    if(!scale_obj.hasOwnProperty('base_adc')) window.alert('bad obj key 2');
    dRefADC.innerHTML = "Ref ADC: " + scale_obj.ref_adc;
    if(!scale_obj.hasOwnProperty('ref_adc')) window.alert('bad obj key 3');
    dRefKG.innerHTML = "Ref KG: "+ scale_obj.ref_kg + "KG";
    if(!scale_obj.hasOwnProperty('ref_kg')) window.alert('bad obj key 4');

    dWeightInKg.innerHTML = 
        "Weight in KG: " + ((curr_adc-base_adc)/(ref_adc-base_adc)*ref_kg);
    dWeightInLb.innerHTML = 
        "Weight in LB: " + ((curr_adc-base_adc)/(ref_adc-base_adc)*ref_kg*2.205);
}

function handleWSmessage(ws_obj_str){ // object string from server websocket data
    console.log(ws_obj_str);
    let ws_obj = JSON.parse(ws_obj_str); // make it js object
    let op = parseInt(ws_obj.op_code); // read the int op_code
    let ws_array = document.body.dataset.toserverwstypes.split(","); // lower case dataset!
    //ToClientWStypes.split(/[ ,]+/);
    //input.split(/[ ,]+/);
    console.log(ws_array);
    // make array from csv document.body.dataset.ToClient_WStypes ;
 
    switch(ws_array[op]) {
        case "ON_CHG":  
            // update weight display here without alert
            updateScaleDOMs(ws_obj);
            break;
        case "SET_REF_OK":
            window.alert("SET_REF_OK");
            updateScaleDOMs(ws_obj);
            break;
        case "SET_BASE_OK":
            window.alert("SET_BASE_OK");
            updateScaleDOMs(ws_obj);
            break;
        case "SET_REFKG_OK":
            window.alert("SET_REFKG_OK");
            updateScaleDOMs(ws_obj);
            break;
        default:
            window.alert("invalid opcode: "+ ws_array[op]);
            break;
    }

}

function initButtons() {
/*
    typedef enum {SET_REF, SET_BASE, SET_REFKG, SET_UXTIME
} toServer_WStypes_enum;
*/
    document.querySelector("#SetRef").addEventListener('click', 
        function() {websocket.send('0');}); // SET_REF
    document.querySelector("#SetBase").addEventListener('click', 
        function() {websocket.send('1');}); // SET_BASE
    document.querySelector("#SetRefKG").addEventListener('click', 
        function() {websocket.send('2,'+dInputKG.value);}); // SET_REFKG
}
