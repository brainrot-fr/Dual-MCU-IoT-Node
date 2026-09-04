/**
 * Reads the #progress-data element's attributes (edited directly in
 * index.html) and renders the progress bar + labels. No build step,
 * no JSON file — just change data-percent / data-label in the HTML.
 */
(function () {
  var data = document.getElementById("progress-data");
  if (!data) return;

  var percent = Math.max(0, Math.min(100, parseInt(data.dataset.percent, 10) || 0));
  var label = data.dataset.label || "";

  var fill = document.getElementById("progress-fill");
  var track = document.getElementById("progress-track");
  var percentLabel = document.getElementById("progress-percent");
  var phaseLabel = document.getElementById("progress-label");
  var heroPhase = document.getElementById("hero-phase");

  if (phaseLabel) phaseLabel.textContent = label;
  if (percentLabel) percentLabel.textContent = percent + "%";
  if (track) {
    track.setAttribute("aria-valuenow", String(percent));
    track.setAttribute("aria-valuetext", percent + "% — " + label);
  }
  if (heroPhase) heroPhase.textContent = label + " (" + percent + "%)";

  if (fill) {
    // Defer to next frame so the CSS transition actually animates on load.
    requestAnimationFrame(function () {
      requestAnimationFrame(function () {
        fill.style.width = percent + "%";
      });
    });
  }
})();