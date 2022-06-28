var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

var CurrADC = document.querySelector("#CurrADC");
var BaseADC = document.querySelector("#BaseADC");
var RefADC = document.querySelector("#RefADC");
var RefKG = document.querySelector("#CurrADC");

var SetBase = document.querySelector("#SetBase");
var SetRef = document.querySelector("#SetRef");
var SetRefKG = document.querySelector("#SetRefKG");
var InputKG = document.querySelector("#InputKG");

var WeightInKg = document.querySelector("#WeightInKg");
var WeightInLb = document.querySelector("#WeightInLb");

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
//console.log(updateScaleDOMs([2,3,4,5,6]))
//setTimeout(initWebSocket, 2000);
}

function updateScaleDOMs(scale_obj){
    //typedef enum {CURR_ADC,BASE_ADC,REF_ADC,REF_KG} 
    //update_scale_WSenum;
 
    CurrADC = parseInt(scale_obj.curr_adc);
    if(!scale_obj.hasOwnProperty('curr_adc')) window.alert('bad obj key 1');
    BaseADC = parseInt(scale_obj.base_adc);
    if(!scale_obj.hasOwnProperty('base_adc')) window.alert('bad obj key 2');
    RefADC = parseInt(scale_obj.ref_adc);
    if(!scale_obj.hasOwnProperty('ref_adc')) window.alert('bad obj key 3');
    RefKG = parseFloat(scale_obj.ref_kg);
    if(!scale_obj.hasOwnProperty('ref_kg')) window.alert('bad obj key 4');

    WeightInKg = (CurrADC-BaseADC)/(RefADC-BaseADC)*RefKG;
    WeightInLb = WeightInKg*2.205;

    RefKgADC.innerHTML = "Reference ADC: " + RefADC;
    SetKgADC.innerHTML = "Set KG ADC: " + RefKG;
    CurrKgADC.innerHTML = "Current ADC: " + CurrADC;
    WeightInKg.innerHTML = "Weight in KG: " + WeightInKg;
    WeightInLb.innerHTML = "Weight in LB: " + WeightInLb;

}

function handleWSmessage(ws_obj_str){ // object string from server websocket data
    console.log(ws_obj_str);
    let ws_obj = JSON.parse(ws_obj_str); // make it an object
    let op = ws_obj.op_code.parseInt(); // read the int opcode
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
            break;
        case "SET_REFKG_OK":
            window.alert("SET_REFKG_OK");
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
        (e)=> {websocket.send('0')});
    SetBase.addEventListener('click', 
        (e)=> {websocket.send('1')});
    SetRefKG.addEventListener('click', 
        (e)=> {
            RefKG = InputKG.value;
            websocket.send('2,'+RefKG)});
}
/**** ********************************************
function initButton() {
document.getElementById('bON').addEventListener('click', toggleON);
document.getElementById('bOFF').addEventListener('click', toggleOFF);
}
function toggleON(event) {
websocket.send('bON');
}
function toggleOFF(event) {
websocket.send('bOFF');
}
*************************************/