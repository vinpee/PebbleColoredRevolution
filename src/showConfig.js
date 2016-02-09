Pebble.addEventListener('showConfiguration', function(e) {  
  Pebble.openURL('http://vpeigneux.free.fr/RevolutionColorConfig');
});

function GColorFromHex(hex) {
  var hexNum = parseInt(hex, 16);
  var a = 192;
  var r = (((hexNum >> 16) & 0xFF) >> 6) << 4;
  var g = (((hexNum >>  8) & 0xFF) >> 6) << 2;
  var b = (((hexNum >>  0) & 0xFF) >> 6) << 0;
  return a + r + g + b;
}

Pebble.addEventListener('webviewclosed', function(e) {
  var configData = JSON.parse(decodeURIComponent(e.response));
  console.log('Configuration page returned: ' + JSON.stringify(configData));
  
  // Prepare AppMessage payload
  var dict = {};
  dict.KEY_TIME_COLOR = parseInt(configData.time_color, 10);
  dict.KEY_DATE_COLOR = parseInt(configData.date_color, 10);
  dict.KEY_SECOND_COLOR = parseInt(configData.second_color, 10);
  dict.KEY_DAY_COLOR = parseInt(configData.day_color, 10);  
  dict.KEY_BACKGROUND_COLOR = GColorFromHex(configData.background_color);  
  
  // Send settings to Pebble watchapp
  Pebble.sendAppMessage(dict, function(){
    console.log('Sent config data to Pebble');  
  }, function() {
    console.log('Failed to send config data!');
  });
});