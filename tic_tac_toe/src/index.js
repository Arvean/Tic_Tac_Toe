import React, { useState, useEffect } from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';

// ------------------------------------------------------------------
// Square Function

const Square = (props) => {
  const handleSquareClick = async() => {
    console.log("Move Sent")
    await fetch("http://localhost:4000/TakeMove/" + props.squareId + "/"+ props.boardId);
    props.onSquareClick();
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
    />;
  })
  return (
    <div>
      <div className="status">Next Player : {props.player}</div> 
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

function TicTacToe(){
  const [error, setError] = useState(null);
  const [boardId, setBoardID] = useState(null);
  const [isLoaded, setIsLoaded] = useState(true);
  const [player, setPlayer] = useState("X");
  const [winningMethod, setWinningMethod] = useState(null);
  const [boardData, setBoardData] = useState([]);

  useEffect(() => { 
    const grabBoard = (async () => {
      if (boardId != null) {
        if (boardData == null) {
          setIsLoaded(false);
        }
        console.log("http://localhost:4000/GetBoard/" + boardId)
        setBoardData(await getBoard(boardId));
      }
    })
    grabBoard()
  }, [boardId])

  useEffect(() => {
    if (boardId != null) {
      console.log("http://localhost:4000/Turn/" + boardId)
      fetch("http://localhost:4000/Turn/" + boardId)
      .then(res => res.text())
      .then(
        (result) =>{
            setPlayer(result);
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
  }, [boardId, boardData])

  useEffect(() => {
    var split_URL = window.location.href.split('/')
    if (split_URL[3] != "") {
      setBoardID(split_URL[3])
    }
  }, []);

  const handleClick = () => {
    fetch("http://localhost:4000/NewGame")
      .then(res => res.text())
      .then(
        (result) =>{
            console.log("New Game: " + result)
            setBoardID(result)
            window.history.pushState({}, '', "http://localhost:3000/" + result);
        },
        (error) => {
            setError(error)
        }
      )
    console.log("<Start Game> clicked")
  }

  const onSquareClick = async() => {
    setBoardData(await getBoard(boardId))
  }

  if (error) {
    return <div>Error: {error.message}</div>
  } else if (!isLoaded) {
    return <div>Loading...</div>
  } else if (boardId == null){
    return(
      <div> 
        Welcome to Tic Tac Toe
        <div>
          <button onClick={() => handleClick(boardId)}>
          Start Game
          </button>
        </div>
      </div>
    )
  } else if (winningMethod != null){
    return(
      <div>
        {winningMethod}
      </div>
    )
  } else{
    return(
      <div> <Board
        player={player}
        boardId = {boardId}
        boardData = {boardData}
        onSquareClick = {onSquareClick}
      /> </div>
    )
  }
}

  const root = ReactDOM.createRoot(document.getElementById("root"));
  root.render(
  <TicTacToe />
  );
