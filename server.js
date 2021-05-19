'use strict';
var express = require('express');
var app = require('express')();
var http = require('http').Server(app);
var bodyParser = require('body-parser');

const shm = require('./shmnode/build/Debug/shmnode.node')

/*****************
*   ROUTING
******************/
app.use(express.static('public'));
app.use(bodyParser.json());       // to support JSON-encoded bodies
app.use(bodyParser.urlencoded({     // to support URL-encoded bodies
    extended: true
}));

app.post('/write', (req, res) => {
    var buf = Buffer.from(JSON.stringify(req.body));
    shm.write(buf);
    res.send(shm.read());
});

app.get('/read', (req, res) => {
    res.send(shm.read());
});

app.get('/', function (req, res) {
    res.send("it works!");
});

http.listen(8080, function () {
    console.log('listening on *:8080');
});
