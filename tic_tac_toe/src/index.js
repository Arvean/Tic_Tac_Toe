import React, { useState, useEffect } from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';

function TicTacToe(){
  const [error, seterror] = useState(null);
  const [board_ID, setboard_ID] = useState("");
  const [isLoaded, setisLoaded] = useState(false);
  const [isStartGame, setisStartGame] = useState(false);
  const [getplayer, setGetplayer] = useState(true);
  const [player, setPlayer] = useState("")
  const [didFetch, setDidFetch] = useState(false)

// ------------------------------------------------------------------
// Square Function

  const Square = ({square_state, setSquare_state, player}) => {
    const handle_square_click = () => {
      setSquare_state(player)
      setGetplayer(true)
    }
    return (
        <button className="box" onClick={handle_square_click}>
          {square_state}
        </button>
    );
  }
  
  // ------------------------------------------------------------------
  // Board Function

  const Board = (props) => {
    const [square1_state, setSquare1_state] = useState(1);
    const [square2_state, setSquare2_state] = useState(2);
    const [square3_state, setSquare3_state] = useState(3);
    const [square4_state, setSquare4_state] = useState(4);
    const [square5_state, setSquare5_state] = useState(5);
    const [square6_state, setSquare6_state] = useState(6);
    const [square7_state, setSquare7_state] = useState(7);
    const [square8_state, setSquare8_state] = useState(8);
    const [square9_state, setSquare9_state] = useState(9);
    return (
      <div>
        <div className="status">Next Player : {props.player}</div>
        <div className="game-board">
          <Square
            square_state={square1_state}
            setSquare_state={setSquare1_state}
            player={props.player}
          />
          <Square
            square_state={square2_state}
            setSquare_state={setSquare2_state}
          />
          <Square
            square_state={square3_state}
            setSquare_state={setSquare3_state}
          />
          <Square
            square_state={square4_state}
            setSquare_state={setSquare4_state}
          />
          <Square
            square_state={square5_state}
            setSquare_state={setSquare5_state}
          />
          <Square
            square_state={square6_state}
            setSquare_state={setSquare6_state}
          />
          <Square
            square_state={square7_state}
            setSquare_state={setSquare7_state}
          />
          <Square
            square_state={square8_state}
            setSquare_state={setSquare8_state}
          />
          <Square
            square_state={square9_state}
            setSquare_state={setSquare9_state}
          />
        </div>
      </div>
    );
  }


  // ------------------------------------------------------------------
  // Game

  useEffect(() => {
    if (didFetch == false) {
    fetch("http://localhost:4000/NewGame")
      .then(res => res.text())
      .then(
        (result) =>{
            console.log(result)
            setboard_ID(result)
            setisLoaded(true)
            setDidFetch(true)
        },
        (error) => {
            setisLoaded(true)
            seterror(error)
        }
      )
    }
  },[didFetch])

  useEffect(() => {
    if (getplayer && board_ID !=''){
      console.log("http://localhost:4000/Turn/" + board_ID)
      fetch("http://localhost:4000/Turn/" + board_ID)
      .then(res => res.text())
      .then(
        (result) =>{
            console.log(result)
            setPlayer(result)
            setGetplayer(false)
        },
        (error) => {
            seterror(error)
        }
      )
    }
  },[getplayer, board_ID])

  function handleClick () {
      setisStartGame(true)
    console.log("<Start Game> clicked")
  }

  if (error) {
    return <div>Error: {error.message}</div>
  } else if (!isLoaded) {
    return <div>Loading...</div>
  } else if (!isStartGame){
    return(
      <div> 
        Welcome to Tic Tac Toe, here is your board ID {board_ID} 
        <div>
          <button onClick={handleClick}>
          Start Game
          </button>
        </div>
      </div>
    )
  } else{
    return(
      <div> <Board
        player={player}
      /> </div>
    )
  }
}

  const root = ReactDOM.createRoot(document.getElementById("root"));
  root.render(<TicTacToe />);