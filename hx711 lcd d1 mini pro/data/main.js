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

function handleWSmessage(ws_cvs){
    console.log(ws_cvs);
    let cvs_msg_array = ws_cvs.split(",");
    let op = document.body.dataset.ToClient_WStypes[cvs_msg_array[0]];

    switch(op) {
        case "ON_CHG":
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