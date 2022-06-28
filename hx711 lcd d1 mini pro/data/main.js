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
    console.log('Trying to open a WebSocket connection…');
    websocket = new WebSocket(gateway);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;
}

function onOpen(event) {
    console.log('Connection opened');
}

function onMessage(event) {
//document.getElementById('state').innerHTML = event.data;
//console.log(event.data);
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
    let op = ws_obj.op_code.parseInt(); // read the int op_code
    let ws_array =document.body.dataset.ToClient_WStypes.split(',');
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

/*
function handleWSmessage(ws_csv){
    console.log(ws_csv);
    let csv_msg_array = ws_csv.split(",");
    let op = document.body.dataset.ToClient_WStypes[csv_msg_array[0]];
    // websocket op code stored in the first item of the cvs message

    switch(op) {
        case "ON_CHG":  // var f = parseInt("2string"); f->2
            // parseFloat("10.33") + "<br>" +
            // update weight display here
            updateScaleDOMs(csv_msg_array);
            break;
        case "SET_REF_OK":
            window.alert("SET_REF_OK");
            break;
        case "SET_BASE_OK":
            window.alert("SET_BASE_OK");
            break;
        case "SET_REFKG_OK":
            window.alert("SET_REFKG_OK");
            break;
        default:
            break;
    }

}

function onMessage(event) {
//document.getElementById('state').innerHTML = event.data;
//console.log(event.data);
handleWSmessage(event.data);
}
*/

function initButtons() {
/*
    typedef enum {SET_REF, SET_BASE, SET_REFKG, SET_UXTIME
} toServer_WStypes_enum;
*/
    SetRefKG.addEventListener('click', 
        (e)=> {websocket.send('0')}); // SET_REF
    SetBase.addEventListener('click', 
        (e)=> {websocket.send('1')}); // SET_BASE
    SetRefKG.addEventListener('click', 
        (e)=> {websocket.send('2,'+InputKG.value)}); // SET_REFKG
}
