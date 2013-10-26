 /**
 * This file is under MIT Licence
 * Copyright (C) 2013 Alexandre BM <s@rednaks.tn>
 *   
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *   
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *   
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "hybridServer.h"


HybridServer::HybridServer() {
  hServer = new QTcpServer(this);
  if (!hServer->listen(QHostAddress::Any, 8080)) {
    std::cout << "Error, couldn't be able to listen on '0.0.0.0:8080'" << std::endl;
    std::cout << hServer->errorString().toStdString() << std::endl;
  }
  else {
    std::cout << "Listening on ..." << hServer->serverAddress().toString().toStdString() << ":" << hServer->serverPort() << std::endl;
    connect(hServer, SIGNAL(newConnection()), this, SLOT(newConnectionSlot()));
    
    mSize = 0;
  }
}

void HybridServer::newConnectionSlot() {
  QTcpSocket *client = hServer->nextPendingConnection();
  clients << client;
  std::cout << "We got a new connection :) " << std::endl;
  connect(client, SIGNAL(readyRead()), this, SLOT(recievedDataSlot()));
  connect(client, SIGNAL(disconnected()), this, SLOT(disconnectedClientSlot()));
}

void HybridServer::recievedDataSlot(){
  QTcpSocket *sock = qobject_cast<QTcpSocket*>(sender());

  if(sock == 0) {
    return;
  }

  char buffer[1024] = {0};
  sock->read(buffer, sock->bytesAvailable());
  /* TODO : 
     We must store clients in two diffrent containers
     One for raw sockets, and the other one for websocket clients
     To perform this, we can first check wether the socket is already
     registered (if it's a raw socket client, he must send a handshake message
     that we will define, wesocket client already have a defined protocol, 
     no need to define another one).
     */

}


void HybridServer::disconnectedClientSlot(){
  std::cout << "Not Implemented Yet" << std::endl;
}

