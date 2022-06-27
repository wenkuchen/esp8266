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

function onClose(event) {
console.log('Connection closed');
//console.log(updateScaleDOMs([2,3,4,5,6]))
//setTimeout(initWebSocket, 2000);
}

function updateScaleDOMs(csv_array){
    //typedef enum {CURR_ADC,BASE_ADC,REF_ADC,REF_KG} 
    //update_scale_WSenum;
    const RefKgADC = document.querySelector("#RefKgADC");
    const SetKgADC = document.querySelector("#SetKgADC");
    const CurrKgADC = document.querySelector("#CurrKgADC");
    const w_kg = document.querySelector("#weightInKg");
    const w_lb = document.querySelector("#weightInLb");
    
    let curr_ADC = parseInt(csv_array[1]); console.log(csv_array[1]);
    let base_ADC = parseInt(csv_array[2]);
    let ref_ADC = parseInt(csv_array[3]);
    let ref_KG = parseFloat(csv_array[4]);
    let WeightInKg = (curr_ADC-base_ADC)/ref_ADC*ref_KG;
    let WeightInLb = WeightInKg*2.205;

    RefKgADC.innerHTML = "Reference ADC: " + ref_ADC;
    SetKgADC.innerHTML = "Set KG ADC: " + ref_KG;
    CurrKgADC.innerHTML = "Current ADC: " + curr_ADC;
    w_kg.innerHTML = "Weight in KG: " + WeightInKg;
    w_lb.innerHTML = "Weight in LB: " + WeightInLb;

}

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

function initButtons() {
    SetBase.addEventListener('click', (e)=> {websocket.send('something')});
    SetRef.addEventListener('click', (e)=> {websocket.send('something')});
    SetRefKG.addEventListener('click', (e)=> {websocket.send('something')});
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