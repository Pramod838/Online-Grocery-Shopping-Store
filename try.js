let index = 0;
displayImages();
function displayImages() {
  let i;
  const images = document.getElementsByClassName("image");
  for (i = 0; i < images.length; i++) {
    images[i].style.display = "none";
  }
  index++;
  if (index > images.length) {
    index = 1;
  }
  images[index-1].style.display = "block";
  setTimeout(displayImages, 2000); 
}

  document.addEventListener("DOMContentLoaded", function () {
    const searchInput = document.getElementById("search-input");
    const searchButton = document.getElementById("search-button");
    const products = document.querySelectorAll(".product");
    const addToCartBtns = document.querySelectorAll(".b1");

    searchButton.addEventListener("click", function () {
      const searchTerm = searchInput.value.toLowerCase();

      products.forEach(function (product) {
        const productTitle = product.querySelector("h3").textContent.toLowerCase();
        if (productTitle.includes(searchTerm)) {
          product.style.display = "block";
        } else {
          product.style.display = "none";
        }
      });
    });

    // Add click event listeners to "Add to Cart" buttons
    addToCartBtns.forEach(function (btn, index) {
      btn.addEventListener("click", function () {
        // Get product details from the clicked button's parent
        const selectedProduct = products[index];
        const productName = selectedProduct.querySelector("h3").textContent;
        const productPrice = selectedProduct.querySelector("p").textContent;

        // Here, you can add the product to the cart (implement your logic)
        // For now, let's just log the details to the console
        console.log("Product added to cart:", productName, "-", productPrice);
      });
    });
  });