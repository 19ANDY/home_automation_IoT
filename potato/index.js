var five = require("johnny-five");
var firebase = require("firebase");

var config = {
  apiKey: 'AIzaSyCayHhNjJ1Hx8_5D2xJuSNL3FTdq1aZNRs',
  authDomain: 'time-table-39a37.firebaseapp.com',
  databaseURL: 'https://time-table-39a37.firebaseio.com',
  projectId: 'time-table-39a37',
  storageBucket: 'time-table-39a37.appspot.com',
  messagingSenderId: '659109023202'
}

firebase.initializeApp(config);

var db = firebase.database();

var board = new five.Board();

board.on("ready", function() {
  var led1 = new five.Led(10);
  var led2 = new five.Led(11);
  var led3 = new five.Led(12);
  var led4 = new five.Led(13);

  db.ref('/alpha').on('value', (snapshot) => {
    var data = snapshot.val()
    console.log(data)
    data.one ? led1.on() : led1.off()
    data.two ? led2.on() : led2.off()
    data.three ? led3.on() : led3.off()
    data.four ? led4.on() : led4.off()
  })
});
