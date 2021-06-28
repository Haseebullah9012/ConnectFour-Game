
// Player Symbol Customization Feature
// setBoard Dimensions() Update
// My Details on Exit Feature
// Predefined Game Modes


//The Game Board
var board = []; 
for(r=0; r<12; r++)
    board[r] = []; 

var rows = document.getElementById("Rows").value = 4; //Total Default Rows of the Board
var cols = document.getElementById("Cols").value = 4; //Total Default Columns of the Board
var konnect = document.getElementById("Konnect").value = 3; //The Default Konnect-Number Goal of the Game
var players = document.getElementById("Players").value = 2; //Total Default Number of Players

var r,c; //For Loop-controls Row & Column
var k; // For Loop-control Konnect
var p; //For Loop-control and also Player Number

var emp = ""; //Empty Board's Mark
var player = [emp,'X','O','I','H','E','V','Z','M']; //The Player's Default Marks

var validated; // The FormValidation Condition
var a,b; //The Player Inputs


//The HTMl Elements
var Docs = document.getElementById("docs"); //The Docs Container
var configure = document.getElementById("Configure"); //The Configuration Options Conatiner
var play = document.getElementById("play"); //The Play Button
var newGame = document.getElementById("newGame"); //The New Game Button
var Info = document.getElementById("info"); //The Player Info Text
var GameContainer = document.getElementById("game-container"); //The Board-Game Container


//Starting Element States
newGame.style.display = "none";
Info.style.display = "none";
GameContainer.style.display = "none";


function Play()
{
    configuration();
    if(validated == true) {
        Docs.style.display = "none";
        configure.style.display = "none";
        play.style.display = "none";
        
        newGame.style.display = "block";
        Info.style.display = "block";
        printBoard();
    }
}

function NewGame()
{
    resetBoard();
    
    Docs.style.display = "block";
    configure.style.display = "block";
    play.style.display = "block";
    
    newGame.style.display = "none";
    Info.style.display = "none";
}


function resetBoard() {
    GameContainer.classList.remove("end");
    GameContainer.style.display = "none";
    
    Info.classList.remove("large");
    newGame.classList.remove("big");
    
    while(GameContainer.hasChildNodes())
        for(r=0; r<rows; r++)
            for(c=0; c<cols; c++)
                GameContainer.removeChild(board[r][c]);
}

function configuration() {
    rows = document.getElementById("Rows").value;
    cols = document.getElementById("Cols").value;
    konnect = document.getElementById("Konnect").value;
    players = document.getElementById("Players").value;
    players++; //Because the Index 0 of player Symbols-Array is Empty
    p = 1; //Default First Turn

    let RowsValid = true;
    let ColsValid = true;
    let KonnectValid = true;
    let PlayersValid = true;
        
    if(isNaN(rows) || !(rows>=2 && rows<=12)) {
        RowsValid = false;
        document.getElementById("Rows").classList.add("invalid");
    }
    else {
        RowsValid = true;
        document.getElementById("Rows").classList.remove("invalid");
    }
    
    if(isNaN(cols) || !(cols>=2 && cols<=12)) {
        ColsValid = false;
        document.getElementById("Cols").classList.add("invalid");
    }
    else {
        ColsValid = true;
        document.getElementById("Cols").classList.remove("invalid");
    }
    
    if(isNaN(konnect) || !(konnect>=2 && konnect<=8)) {
        KonnectValid = false;
        document.getElementById("Konnect").classList.add("invalid");
    }
    else if(!(konnect<=rows || konnect<=cols) && !(rows>=8 || cols>=8)) {
        KonnectValid = false;
        document.getElementById("Konnect").classList.add("invalid");
    }
    else {
        KonnectValid = true;
        document.getElementById("Konnect").classList.remove("invalid");
    }

    if(isNaN(players) || !(players>=2 && players<=8)) {
        PlayersValid = false;
        document.getElementById("Players").classList.add("invalid");
    }
    else {
        PlayersValid = true;
        document.getElementById("Players").classList.remove("invalid");
    } 
    
    if(RowsValid==true && ColsValid==true && KonnectValid== true && PlayersValid==true)
        validated = true;
    else
        validated = false;
}

function printBoard() {

    Info.textContent = "Player " + p + "'s Turn";
    GameContainer.style.display = "block";

    for(r=0; r<rows; r++) {
        for(c=0; c<cols; c++) {
            board[r][c] = document.createElement('button');
            board[r][c].textContent = emp;
            board[r][c].dataset.x = r, board[r][c].dataset.y = c;
            board[r][c].classList.add("square");
            board[r][c].addEventListener("click", turn);
            
            GameContainer.appendChild(board[r][c]);
        }
        //GameContainer.append(" ");
    }
    
    setBoardDimensions();
}

function setBoardDimensions() {
    
    var Board_width, Board_height; //For Board Dimensions
    var Square; //For Square Dimensions

    if(rows>=cols) {
        if(rows==2)
            Square = 160/rows;
        else if(rows==3)
            Square = 250/rows;
        else if(rows==4)
            Square = 320/rows;
        else
            Square = 520/rows;
    }
    else if (cols>=rows){
        if(cols==2)
            Square = 160/cols;
        else if(cols==3)
            Square = 250/cols;
        else if(cols==4)
            Square = 320/cols;
        else
            Square = 520/cols;
    }
    
    Board_width = Square*cols + 5;
    Board_height = Square*rows + 3;

    GameContainer.style.width = Board_width + "px";
    GameContainer.style.height = Board_height + "px";
    
    for(r=0; r<rows; r++) {
        for(c=0; c<cols; c++) {
            board[r][c].style.width = Square + "px";
            board[r][c].style.height = Square + "px";
        }
    }
}


//On User Inpput
function turn() {
    a = parseInt($(this).data('x'));
    b = parseInt($(this).data('y'));
    
    if(board[a][b].textContent == emp) {
        board[a][b].textContent = player[p];
            
        if(over() == true) {
            Info.textContent = "Player " + p + " Won!";
            Info.classList.add("large");
            GameContainer.classList.add("end");
            newGame.classList.add("big");
            return;
        }
        
        if(draw() == true) {
            Info.textContent = "Its a Draw!";
            Info.classList.add("large");
            GameContainer.classList.add("end");
            newGame.classList.add("big");
            return;
        }
        
        //Ready Next Player
        p++;
        if(!(p <= players-1)) {
            p = 1;
        }
        Info.textContent = "Player " + p + "'s Turn";
    }
}

function over()
{
    //Resolved the Bug by Limiting the Rows (r) and Columns (c) to Stay in the Array Board-Size
    
    for(r=0; r<rows; r++) {
        for(c=0; c<cols-konnect+1; c++) {
        
            for(k=0; k<konnect; k++)
                if(board[r][c+k].textContent != player[p])
                    break;
            if(k==konnect)
                return true; //Horizontally
        }
    }
    
    for(r=0; r<rows-konnect+1; r++) {
        for(c=0; c<cols; c++) {
    
            for(k=0; k<konnect; k++)
                if(board[r+k][c].textContent != player[p])
                    break;
            if(k==konnect)
                return true; //Vertically
        }
    }
    
    for(r=0; r<rows-konnect+1; r++) {
        for(c=0; c<cols-konnect+1; c++) {
    
            for(k=0; k<konnect; k++)
                if(board[r+k][c+k].textContent != player[p])
                    break;
            if(k==konnect)
                return true; //Diagonally-Right
        }
    }
    
    
    for(r=0; r<rows-konnect+1; r++) {
        for(c=cols-1; c>konnect-2; c--) {
    
            for(k=0; k<konnect; k++)
                if(board[r+k][c-k].textContent != player[p])
                    break;
            if(k==konnect)
                return true; //Diagonally-Left
        }
    }
    
    return false;
}

function draw()
{
	for(r=0; r<rows; r++)
		for(c=0; c<cols; c++)
			if(board[r][c].textContent == emp) //false if even one space is empty
				return false;
	return true;
}
