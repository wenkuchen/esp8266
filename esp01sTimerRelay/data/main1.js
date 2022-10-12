let btn1 = document.querySelector("#btn1");
let container = document.querySelector("#archWorkday");
console.log(container);
btn1.addEventListener("click", () => (container.style.color = "green"));

let hourMarkers = "0,6,9,12,14,18,21,24";
const markerArray = hourMarkers.split(",").map((x) => parseInt(x, 10));

console.log(markerArray);

appendSVGwPath(container, "svgArch", "pathArch", markerArray);
console.log(container);

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
