var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

window.addEventListener('load', onload);

function onload(event) {
initWebSocket();
initButton();
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
setTimeout(initWebSocket, 2000);
}

function updateScaleDOMs(csv_array){
    //typedef enum {CURR_ADC,BASE_ADC,REF_ADC,REF_KG} 
    //update_scale_WSenum;
    const RefKgADC = document.querySelector("#RefKgADC");
    const SetKgADC = document.querySelector("#SetKgADC");
    const CurrKgADC = document.querySelector("#CurrKgADC");
    
    let CURR_ADC = csv_array[1];
    let BASE_ADC = csv_array[2];
    let REF_ADC = csv_array[3];
    let REF_KG = csv_array[4];
    
    RefKgADC.innerHTML = "something new";
    SetKgADC.innerHTML = "something new";
    CurrKgADC.innerHTML = "something new";
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