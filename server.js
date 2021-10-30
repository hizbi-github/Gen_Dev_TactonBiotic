


const httpServer = require("http");

const realTimeServer = require("ws");

const fileHandler = require("fs");

const qs = require("querystring");

const urlHandler = require("url");

// const postDataHandler = require("body-parser")

//const port = process.env.PORT;

const port = 3000;



let remoteClients = {};

let robotClients = {};


let remoteControlStatus = 
{    
  "DecreaseTrt" : false,

  "IncreaseTrt" : false,

  "DPad_Down" : false,

  "DPad_Left" : false,

  "DPad_Right" : false,

  "DPad_Up" : false,

  "FrontFace_Axe" : false,

  "FrontFace_Circle" : false,

  "FrontFace_Square" : false,

  "FrontFace_Triangle" : false
}



const backendServer = httpServer.createServer(function(req, res)
{
  
  if (req.url == "/")
  {
    res.writeHead(200, {"Content-Type": "text/html"})
    
    fileHandler.createReadStream("src/pages/index.html").pipe(res);
    
    res.end;
  }
  
  
  if (req.url == "/public/frontend.css")
  {
    res.writeHead(200, {"Content-Type": "text/css"})
    
    // console.log("Before FileHandler!");
    
    fileHandler.createReadStream("public/frontend.css").pipe(res);
    
    res.end;
  }
  
  
  if (req.url == "/client.js")
  {
    res.writeHead(200, {"Content-Type": "text/javascript"})
    
    // console.log("Before FileHandler!");
    
    fileHandler.createReadStream("./client.js").pipe(res);
    
    res.end;
  }
  
  
  if (req.method == "POST")
  {
    let requestBody = '';
    
    req.on('data', function(data) 
    {
      requestBody += data;
    });

    req.on('end', function() 
    {      
      console.log(requestBody);

      res.write("Recieved POST Request!");

      res.end;
    });
   
   }             

})


const realTimeComs = new realTimeServer.Server({ server: backendServer });


realTimeComs.on("connection", function connection(coms, client) 
{
  coms.send("Connection Succesful!");
  
  
  let clientURL = new URLSearchParams(client.url.substring(2));
  let clientType = clientURL.get("client");
  let clientName = clientURL.get("name_id");
  
  
  if (clientURL.get("client") == "remote")
  {
    remoteClients[clientURL.get("name_id")] = coms;
    console.log(remoteClients);
  }
  
  if (clientURL.get("client") == "robot")
  {
    robotClients[clientURL.get("name_id")] = coms;
    console.log(robotClients);
  }
  
  
  console.log("Client " + clientName + " Connected for RealTime Coms!");
    
  
  coms.on("message", function incoming(stateData) 
  {            
    let parsedMessage = JSON.parse(stateData);
    
    remoteClients[parsedMessage.name_id].send("State Recieved!");
    robotClients[parsedMessage.name_id].send(stateData);
    
    console.log(parsedMessage.name_id + ":" + parsedMessage.name + ":" + parsedMessage.state);
  });
});



backendServer.listen(port, function(error)
{
  if (error)
  {
    console.log("Something went wrong", error);
  }
  else
  {
    console.log("Server is listening on universal port: " + port);
  }
});














////import * as  express from 'express';
////import * as https from 'https';
////import * as socketIo from 'socket.io';


//let express = require('express');
//let http = require('http');
//let socketIo = require('socket.io');


//let webApp = express();

//webApp.get('/', (req, res) => res.send("Hello TactonBiotic"));

//let webAppServer = http.Server(webApp);



//webAppServer.listen(3000);



//let socketIo_Instance = socketIo(webAppServer);

//socketIo_Instance.on('connection', (socket) =>
//{

//  socket.emit('hello', 
//  {

//    greeting: 'Hello again!'

//  });

//});