var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

window.addEventListener('load', (e) => initWebSocket());
document.addEventListener("DOMContentLoaded", () => {
  //wait till all dom's loaded or querySelector will result null
  btn1 = document.body.querySelector("#btn1");
  btn1.addEventListener("click", () => (container.style.border = "solid"));
  container = document.body.querySelector("#archWorkday");

  appendSVGwPath(container, "svgArch", "pathArch", markerArray);
  console.log(container);
});

/** Timer operation variables ****************/
let btn1, container;
const hourMarkers = "0,6,9,12,14,18,21,24";
console.log(hourMarkers);
const markerArray = hourMarkers.split(",").map((x) => parseInt(x, 10));
console.log(markerArray);
//for(i=0;i<24;i++) makeCheckbox(i%24+1);

/***** function definitions ******************************/

function appendSVGwPath(node, svgClass, pathClass, timerArchArray) {
  const dSvg = document.createElementNS("http://www.w3.org/2000/svg", "svg");
  const dPath = document.createElementNS("http://www.w3.org/2000/svg", "path");
  const dPath0 = document.createElementNS("http://www.w3.org/2000/svg", "path");

  dSvg.setAttribute("fill", "none");
  dSvg.setAttribute("viewBox", "0 0 240 160");
  dSvg.classList.add(svgClass);

  dPath.setAttribute("fill", "none");
  dPath.setAttribute("stroke-width", "12");
  dPath.setAttribute("stroke", "#ff2");
  dPath.setAttribute("d", "M 150 120 A 50 50 0 1 1 151 120");
  dPath.classList.add(pathClass);

  dPath0.setAttribute("fill", "none");
  dPath0.setAttribute("stroke-width", "18");
  dPath0.setAttribute("stroke", "#555");
  dPath0.setAttribute("d", "M 150 120 A 50 50 0 1 1 151 120");
  dPath0.classList.add(pathClass);

  let pathLen = dPath.getTotalLength();
  dPath.style.strokeDasharray = markerArray
    .map((x, idx, el) => {
      var prev = 0;
      if (idx > 0) prev = el[idx - 1];
      return ((x - prev) / 24) * pathLen;
    })
    .toString();

  dSvg.appendChild(dPath0);
  dSvg.appendChild(dPath);

  return node.appendChild(dSvg);
}
function makeCheckbox(i) {
  var boxes = document.getElementById("boxes");
  var box = document.createElement('div');
  box.classList.add("box");
  var checkbox = document.createElement('input');
  checkbox.type = "checkbox";
  //checkbox.name = "chkbox1";
  checkbox.id = "cbid" + i;
  box.appendChild(checkbox);
  var label = document.createElement('label');
  var tn = document.createTextNode(i);
  label.htmlFor = "cbid";
  label.appendChild(tn);
  box.appendChild(label);
  boxes.appendChild(box);
}

/*** wesocket functions  *********************/
function initWebSocket() {
  console.log('Trying to open a WebSocket connection…');
  websocket = new WebSocket(gateway);
  websocket.onopen = onOpen;
  websocket.onclose = onClose;
  websocket.onmessage = onMessage;
}

function onOpen(event) {
  console.log('Websocket Connection opened!');
  console.log(event);
  //let ws_array = document.body.dataset.ToServerWStypes.split(/[ ,]+/);
  //console.log(ws_array);
}

function onMessage(event) {
  //document.getElementById('state').innerHTML = event.data;
  //console.log(event.data);

  console.log("event data: ");
  console.log(event.data);
  console.log(typeof (event.data));

  handleWSmessage(event.data);
}

function onClose(event) {
  console.log('Connection closed');
  setTimeout(initWebSocket, 2000);
}

function handleWSmessage(ws_obj_str) { // object string from server websocket data
  console.log(ws_obj_str);
  //let ws_obj = JSON.parse(ws_obj_str); // make it js object
  //let op = parseInt(ws_obj.op_code); // read the int op_code
  let ws_array = document.body.dataset.toclientwstypes.split(","); // lower case dataset!
  //ToClientWStypes.split(/[ ,]+/);
  //input.split(/[ ,]+/);
  console.log(ws_array);
  // make array from csv document.body.dataset.ToClient_WStypes ;

  switch (ws_array[op]) {
    case "SEND_SCHED":
      // update weight display here without alert
      //updateScaleDOMs(ws_obj);
      break;
    case "SET_SCHED_OK":
      window.alert("SET_REF_OK");
      //updateScaleDOMs(ws_obj);
      break;
    case "SET_ALWAYS_ON_OK":
      window.alert("SET_ALWAYS_ON_OK");
      //updateScaleDOMs(ws_obj);
      break;
    case "SET_ALWAYS_OFF_OK":
      window.alert("SET_ALWAYS_OFF_OK");
      //updateScaleDOMs(ws_obj);
      break;
    case "SET_UXTIME_OK":
      window.alert("SET_UXTIME_OK");
      //updateScaleDOMs(ws_obj);
      break;
    default:
      window.alert("invalid opcode: " + ws_array[op]);
      console.log(ws_array[op]);
      break;
  }

}