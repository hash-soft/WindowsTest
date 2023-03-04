/**
 * Native‚É—¬‚·
 * */

console.log('back');

//var port = chrome.runtime.connectNative('my_native_message_example');

chrome.runtime.onMessage.addListener((request, sender, sendResponse) => {
    /*chrome.runtime.sendNativeMessage(
        'NativeTest',
        request,
        function(response)
        {
            var message = decodeURIComponent(response);
            console.log(message);
        }
    );*/
    chrome.runtime.sendNativeMessage("native_message_test", request)
        .then(response => {
            console.log("Received " + response);
        }).catch(error => {
            console.log(`Error: ${error}`);
        });
    console.log(request);

});

/*
D:\\source\\repos\\WindowsTest\\ExtensionReciver\\bin\\Release\\net6.0\\ExtensionReciver.exe
c:\\windows\\system32\\notepad.exe
*/