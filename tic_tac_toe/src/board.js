import React from 'react';
import ReactDOM from 'react-dom/client';

class Square extends React.Component {
    render() {
        return (
          <button className="square">
            {/* TODO */}
          </button>
        );
    }
}

class Board extends React.Component {
    ShowSquare(i) {
        return <Square />;
    }
    render() {
        return (
            <div>
              <div className="board-row">
                {this.renderSquare(0)}
                {this.renderSquare(1)}
                {this.renderSquare(2)}
              </div>
              <div className="board-row">
                {this.renderSquare(3)}
                {this.renderSquare(4)}
                {this.renderSquare(5)}
              </div>
              <div className="board-row">
                {this.renderSquare(6)}
                {this.renderSquare(7)}
                {this.renderSquare(8)}
              </div>
            </div>
        );
    }
}
    