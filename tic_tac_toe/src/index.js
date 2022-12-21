import React, { useState, useEffect } from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';

// ------------------------------------------------------------------
// Square Function

const Square = (props) => {
  const handleSquareClick = async() => {
    console.log("Move Sent")
    console.log("Cookie" + props.cookie)
    let response = await fetch("http://localhost:4000/TakeMove/" + props.squareId + "/"+ props.boardId, {
      credentials: 'same-origin',
      method: 'POST',
      headers: {
        'Content-Type': "text/plain"
      },
      body: String(props.cookie), //Give backend client identifier (cookie)
    });
    props.onSquareClick();
    console.log("Move Response:" + response.text());
  }
  return (
      <button className="box" onClick={handleSquareClick}>
        {props.value}
      </button>
  );
}
  
  // ------------------------------------------------------------------
  // Board Function

const Board = (props) => {
  console.log(props.boardData)
  const squareList = props.boardData.map((square, i)=>{
    let value;
    if (square == "X" || square == "O") {
      value = square;
    } else {
      value = null;
    }

    return <Square
      value={value}
      player={props.player}
      squareId = {i+1}
      boardId = {props.boardId}
      key={i}
      onSquareClick = {props.onSquareClick}
      cookie = {props.cookie}
    />;
  })
  return (
    <div>
      <div className="status">Board ID : {props.boardId}</div> 
      <div className="status">Your Turn : {props.playerID}</div> 
      <div className="game-board">
        {squareList}
      </div>
    </div>
  );
}


  // ------------------------------------------------------------------
  // Game

const getBoard = async (boardId) => {
  const res = await fetch("http://localhost:4000/GetBoard/" + boardId);
  return await res.json();
}

const initializeGame = (setError, setBoardID, setIsLoaded, setPlayer, setWinningMethod, setBoardData) => {
  setError(null);
  setBoardID(null);
  setIsLoaded(true);
  setPlayer("X");
  setWinningMethod(null);
  setBoardData([]);
}

const promptUserCookie = () => {
  document.cookie = prompt("What is your name?");
}

const parseUserCookie = (setCookie) => {
  let cookie = document.cookie.split(';');
  cookie = cookie[cookie.length-1];
  cookie = cookie.trim();
  cookie = cookie.substring(0, cookie.length);
  if (cookie[cookie.length-1] == '='){
    cookie.slice(0, -1)
  }
  console.log(cookie);
  setCookie(cookie);
  return cookie;
}

const handleRestart = (setError, setBoardID, setIsLoaded, setPlayer, setWinningMethod, setBoardData) => {
  console.log("Handle Restart")
  window.history.pushState({}, '', "http://localhost:3000")
  initializeGame(setError, setBoardID, setIsLoaded, setPlayer, setWinningMethod, setBoardData)
}

const handleMultiplayerClick = (setBoardID, setError, parseUserCookie, setCookie, isPrivateGame) => {
  promptUserCookie();
  let cookie = parseUserCookie(setCookie);
  String(cookie)
  if (isPrivateGame != true){
    var postBody = String(cookie) + "$" + "false";
  }
  else {
    var postBody = String(cookie) + "$" + "true";
  }
  console.log("In Start Game handleClick " + cookie)
  fetch("http://localhost:4000/NewGame", {
    credentials: 'same-origin',
    method: 'POST',
    headers: {
      'Content-Type': "text/plain"
    },
    body: postBody, //Want to specify if this is a mutliplayer click or private lobby click
  })
    .then(res => res.json())
    .then(
      (result) =>{
        if (result[0] != "error"){
          console.log("New Game: " + result[0])
          console.log("Debug: " + result[1]) //Want to return the board ID and display for private lobby click
          console.log(result.length)
          for (var i=0; i < result.length; i++){
            console.log(result[i])
          }
          setBoardID(result[0])
          window.history.pushState({}, '', "http://localhost:3000/" + result[0]);
        }
        else {
          setError("Name taken. Pick a different name: ")
        }
      },
      (error) => {
          setError(error)
      }
    )
  console.log("<Start Game> clicked")
}

const handlePrivateClick = (setPrivateGameMenu) => {
  setPrivateGameMenu(true);
}

const handleCreateClick = (setBoardID, setError, parseUserCookie, setCookie) => {
  let isPrivateGame = true;
  handleMultiplayerClick(setBoardID, setError, parseUserCookie, setCookie, isPrivateGame);
}

const handleFindClick = (setBoardID, setError, parseUserCookie, setCookie) => {
  return 0;
}

function TicTacToe(){
  const [error, setError] = useState(null);
  const [boardId, setBoardID] = useState(null);
  const [isLoaded, setIsLoaded] = useState(true);
  const [player, setPlayer] = useState("X");
  const [playerID, setPlayerID] = useState(null);
  const [winningMethod, setWinningMethod] = useState(null);
  const [boardData, setBoardData] = useState([]);
  const [cookie, setCookie] = useState(null);
  const [privateGameMenu, setPrivateGameMenu] = useState(null);

  useEffect(() => { 
      const grabBoard = (async () => {
        if (boardId != null) {
          if (boardData == null) {
            setIsLoaded(false);
          }
          //console.log("This is board data: " + boardData)
          setBoardData(await getBoard(boardId));
          console.log("grab board")
        }
      })
      setInterval(() => {
        grabBoard()
        console.log("poll for board")
     }, 1000);
  }, [boardId])

  useEffect(() => {
    if (boardId != null) {
      console.log("http://localhost:4000/Turn/" + boardId)
      fetch("http://localhost:4000/Turn/" + boardId)
      .then(res => res.json())
      .then(
        (result) =>{
            console.log("ID player turn: " + result)
            setPlayer(String(result[0]));
            setPlayerID(String(result[1]));
        },
        (error) => {
            setError(error);
        }
      )
      fetch("http://localhost:4000/Gameover/" + boardId)
      .then(res => res.text())
      .then(
        (result) =>{
          console.log(result)
          if (result=="Game is not over."){
            setWinningMethod(null)
          } else {
            setWinningMethod(result);
          }
        }
      )
    }
  }, [boardData,boardId]) // Board_data is not changing however this is constantly running

  // Handle Refresh
  useEffect(() => {
    var split_URL = window.location.href.split('/')
    if (split_URL[3] != "") {
      setBoardID(split_URL[3])
      let cookie = parseUserCookie(setCookie);
    }
  }, [boardId]);

  const onSquareClick = async() => {
    setBoardData(await getBoard(boardId))
  }

  if (error) {
    return <div>Error: {error.message}</div>
  } else if (!isLoaded) {
    return <div>Loading...</div>
  } else if (boardId == null && privateGameMenu != true){
    return(
      <div> 
        Welcome to Tic Tac Toe
        <div>
          <button onClick={() => handleMultiplayerClick(setBoardID, setError, parseUserCookie, setCookie)}> 
          Multiplayer Game
          </button>
          <button onClick={() => handlePrivateClick(setPrivateGameMenu)}> 
          Private Lobby
          </button>
        </div>
      </div>
    )
  } else if (boardId == null && privateGameMenu == true){
    return(
      <div> 
        <div>
          <button onClick={() => handleCreateClick(setBoardID, setError, parseUserCookie, setCookie)}> 
          Create Game
          </button>
          <button onClick={() => handleFindClick()}> 
          Find Game
          </button>
        </div>
      </div>
    )
  } else if (winningMethod != null){
    return(
      <div>
        {winningMethod}
        <div>
          <button onClick={() => handleRestart(setError, setBoardID, setIsLoaded, setPlayer, setWinningMethod, setBoardData)}>
            Return to Home
          </button>
        </div>
      </div>
    )
  } else{
    return(
      <div> <Board
        player={player}
        playerID={playerID}
        boardId = {boardId}
        boardData = {boardData}
        onSquareClick = {onSquareClick}
        cookie = {cookie}
      /> </div>
    )
  }
}

  const root = ReactDOM.createRoot(document.getElementById("root"));
  root.render(
  <TicTacToe />
  );

  //docker build -rm -t tic_tac_toe .
  //docker run -p 4000:4000 tic_tac