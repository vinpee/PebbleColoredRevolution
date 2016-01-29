Pebble.addEventListener('showConfiguration', function(e) {  
  Pebble.openURL('http://vpeigneux.free.fr/revolution-color-config.html');
});

Pebble.addEventListener('webviewclosed', function(e) {
  // Prepare AppMessage payload
  var dict = {
    'color': e.response
  };
 console.log(e.response);  
  // Send settings to Pebble watchapp
  Pebble.sendAppMessage(dict, function(){
    console.log('Sent config data to Pebble');  
  }, function() {
    console.log('Failed to send config data!');
  });
});