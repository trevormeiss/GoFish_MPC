/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

namespace cpp gofish

/*****************
 * Types
 *****************/

struct ServerAddress {
  1: i16 port,
  2: string hostname
}

struct State {
  1: i16 numCards,
  2: i16 numBooks
}

exception InvalidOperation {
  1: i32 whatOp,
  2: string why
}


/*****************
 * Services
 *****************/

service Player {
  list<i16> request(1:string rank, 2:i16 index),
  bool validateRequest(1:string rank, 2:i16 index),
  i32 cardDrawn(1:i16 index),
  i32 getDeckShare(1:i16 index),
  State startTurn(1:i16 pNum),
  oneway void yourTurn(),
  bool bookAcquired(1:list<i32> indices),
}

service Initializer {
  bool connectToPlayer(1:ServerAddress serverAddress),
  bool setPlayerNum(1:i16 num),
  bool setPrime(1:i32 prime),
  bool sendDeckShares(1:list<i32> deckShares),
  bool drawHand(1:i16 numCards),
  i16 startGame()
}