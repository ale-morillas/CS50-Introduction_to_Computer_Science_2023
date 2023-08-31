document.addEventListener('DOMContentLoaded', () => {
    const popup = document.getElementById('popup');
    const closePopup = document.getElementById('closePopup');

    setTimeout(() => {
        popup.classList.add('show');
    }, 100);

    closePopup.addEventListener('click', () => {
        popup.classList.remove('show');
    });
});