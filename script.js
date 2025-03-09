const offerSlider = document.querySelector('.offer-slider');
const offers = document.querySelectorAll('.offer');
const totalOffers = offers.length;

let currentOffer = 0;

function slideOffer() {
    currentOffer = (currentOffer + 1) % (totalOffers * 2); // Duplicate offers for a seamless loop
    const offset = -currentOffer * (100 / totalOffers);
    offerSlider.style.transform = `translateX(${offset}%)`;
}

let interval;

offerSlider.addEventListener('mouseenter', () => {
    interval = setInterval(slideOffer, 2000);
});

offerSlider.addEventListener('mouseleave', () => {
    clearInterval(interval);
});

slideOffer(); // Start sliding immediately
