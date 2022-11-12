import React from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';
import './board.js';

class TicTacToe extends React.Component {
  constructor(props){
    super(props);
    this.state = {
      error: null,
      isLoaded: false,
      board_ID: "",
      isStartGame: false
    };
    this.handleClick = this.handleClick.bind(this); // Giving handClick acess to states and props
  }
  componentDidMount() { 
  // Invoked immediately after a component is mounted (inserted into the tree)
  // If you need to load data from a remote endpoint, this is a good place to instantiate the network request
    fetch("http://localhost:4000/NewGame")
      .then(res => res.text())
      .then(
        (result) =>{
          console.log(result)
          this.setState ({
            isLoaded: true,
            board_ID: result
          });
        },
        (error) => {
          this.setState({
            isLoaded: true,
            error
          });
        }
      )
    }

    handleClick () {
      this.setState({
        isStartGame: true
      })
      console.log("<Start Game> clicked")
    }

  render() {
    const { error, isLoaded, board_ID } = this.state;
    if (error) {
      return <div>Error: {error.message}</div>
    } else if (!isLoaded) {
      return <div>Loading...</div>
    } else if (!this.state.isStartGame){
      return(
        <div> 
          Welcome to Tic Tac Toe, here is your board ID {board_ID} 
          <div>
            <button onClick={this.handleClick}>
            Start Game
            </button>
          </div>
        </div>
      )
    } else{
      return(
        <div> Do something </div>
      )
      }
    }
}

  const root = ReactDOM.createRoot(document.getElementById("root"));
  root.render(<TicTacToe />);