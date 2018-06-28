// import { readFileSync } from 'fs';
// import * as https from 'https';
var fs = require('fs');
var https = require('https');
var privateKey = fs.readFileSync('/etc/letsencrypt/live/live.leafytree.jp/privkey.pem');
var certificate = fs.readFileSync('/etc/letsencrypt/live/live.leafytree.jp/fullchain.pem');

//
/// Setup the Symple server

var Symple = require('symple');
var sy = new Symple();
sy.loadConfig(__dirname + '/symple.json'); // see symple.json for options
sy.init();
console.log('Symple server listening on port ' + sy.config.port);


//
/// Setup the demo client web server

var express = require('express'),
  path = require('path'),
  app = express(),
  serverPort = parseInt(sy.config.port)
  clientPort = serverPort - 1;

app.set('port', clientPort);
app.set('view engine', 'ejs');
app.set('views', __dirname + '/');
app.use(express.static(__dirname + '/assets'));
//app.use(express.static(__dirname + '/node_modules/symple-client/src'));
//app.use(express.static(__dirname + '/node_modules/symple-client-player/src'));

app.get('/', function (req, res) {
  res.render('index', {
    port: serverPort,
    peer: {
      user: 'demo',
      name: 'Demo User',
      group: 'public'
    }
  });
});

const options = {
    key: privateKey,
    cert: certificate,
};

https.createServer(options, app).listen(app.get('port'), function(){
  console.log('Web server listening on port ' + app.get('port'));
});
