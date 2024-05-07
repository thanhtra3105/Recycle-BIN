const circleElement = document.querySelector('.circle');
const percentageInput = document.querySelector('#percentageInput');

percentageInput.addEventListener('input', function() {
  const percentage = 12;
  const clipPathValue = `polygon(0 0, 0 100%, ${percentage}% 100%, ${percentage}% 0)`;
  circleElement.style.clipPath = clipPathValue;
});