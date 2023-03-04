/**
 * background.js‚É—¬‚·
 * */

console.log('extensions');

window.addEventListener("load", main, false);
function main(e) {
    console.log('load!!', e);
}
document.getElementById('test').addEventListener('click', () => {
    console.log('send');
    chrome.runtime.sendMessage({ test: 'output' });
}
    , false);

