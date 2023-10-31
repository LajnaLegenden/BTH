import * as puppeteer from 'puppeteer';
enum BoardState {
    NONE,
    ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT,
    UNREVEALED,
    FLAGGED
}
declare var document: any;
class Solver {
    /**
     *
     */

    private browser: puppeteer.Browser | undefined;
    private page: puppeteer.Page | undefined;
    private board: Record<string, BoardState> = {};
    private guessesMade: number = 0;
    private squares: puppeteer.ElementHandle[] | undefined;
    x: number = 16;
    y: number = 30;
    gameState = "playing"
    constructor() {
        this.init().then(() => {
            this.solve();
        });


    }

    async init() {
        this.browser = await puppeteer.launch({ headless: false });
        this.page = await this.browser.newPage();
        await this.page.goto('https://minesweeperonline.com/#');
        this.fixClass();
    }

    async updateBoard() {
        this.squares = await this.page?.$$('.square');
        //loop overt the squares
        for (let i = 0; i < this.squares!.length; i++) {
            let square = this.squares![i];
            let className = await square.evaluate((node) => node.className);
            let id = await square.evaluate((node) => node.id);
            let x = parseInt(id.split('_')[0]);
            let y = parseInt(id.split('_')[1]);
            this.board[`${x}_${y}`] = this.getBoardState(className);
        }


        let state = await this.page?.$eval("#face", (node) => node.className);
        if (state.includes("facesmile")) {
            this.gameState = "playing"
        }
        else if (state.includes("facedead"))
            this.gameState = "lost"
        else if (state.includes("facewin"))
            this.gameState = "won"
        else
            this.gameState = "playing"

    }

    getBoardState(className: string): BoardState {
        if (className.includes('blank'))
            return BoardState.UNREVEALED;
        if (className.includes('open0'))
            return BoardState.NONE;
        if (className.includes('open1'))
            return BoardState.ONE;
        if (className.includes('open2'))
            return BoardState.TWO;
        if (className.includes('open3'))
            return BoardState.THREE;
        if (className.includes('open4'))
            return BoardState.FOUR;
        if (className.includes('open5'))
            return BoardState.FIVE;
        if (className.includes('open6'))
            return BoardState.SIX;
        if (className.includes('open7'))
            return BoardState.SEVEN;
        if (className.includes('open8'))
            return BoardState.EIGHT;
        if (className.includes('bombflagged'))
            return BoardState.FLAGGED;
        return BoardState.UNREVEALED;
    }

    async solve() {
        console.log("Solving");
        await this.page?.waitForTimeout(5000);
        let playing = true;
        while (playing && this.guessesMade < 100) {
            if(this.gameState == "lost"){
                console.log("Lost");
                playing = false;
                break;
            }
            if (this.guessesMade == 0) {
                //click element with id 5_5
                await this.clickSquare(7, 15);
                this.guessesMade++;
            }

            //update board
            await this.updateBoard();

            for(let x = 1; x<=this.x; x++){
                for (let y = 1; y <= this.y; y++) {
                    if(this.board[`${x}_${y}`] == BoardState.ONE){
                         //cehck if only one unreavealed square aournd
                            let count = 0;
                            if(this.board[`${x-1}_${y-1}`] == BoardState.UNREVEALED)
                                count++;
                            if(this.board[`${x-1}_${y}`] == BoardState.UNREVEALED)
                                count++;
                            if(this.board[`${x-1}_${y+1}`] == BoardState.UNREVEALED)    
                                count++;
                            if(this.board[`${x}_${y-1}`] == BoardState.UNREVEALED)
                                count++;
                            if(this.board[`${x}_${y+1}`] == BoardState.UNREVEALED)
                                count++;
                            if(this.board[`${x+1}_${y-1}`] == BoardState.UNREVEALED)
                                count++;
                            if(this.board[`${x+1}_${y}`] == BoardState.UNREVEALED)
                                count++;
                            if(this.board[`${x+1}_${y+1}`] == BoardState.UNREVEALED)
                                count++;
                            if(count == 1){
                                

                    }
                }
            }

        }
        await this.page?.waitForTimeout(5000);
        this.printBoard();
        this.browser?.close();
    }

    async clickSquare(x: number, y: number) {
        //click square with class cell_x_y
        console.log(`Clicking square ${x} ${y}`);
        await this.page?.waitForSelector(`.cell_${x}_${y}`);
        let square = await this.page?.$(`.cell_${x}_${y}`);
        await square?.click();
        await this.fixClass();
    }

    printBoard() {
        console.log("Board:");
        for (let i = 1; i <= this.x; i++) {
            let row = "";
            for (let j = 1; j <= this.y; j++) {
                row += this.board[`${i}_${j}`] + " ";
            }
            //replace 0 with #
            
            row = row.replace(/0/g, " ");
            row = row.replace(/9/g, "#");
            console.log(row);
        }
    }

    async fixClass() {
        await this.page?.evaluate(() => {
            let s = document.querySelectorAll(".square")
            s.forEach((el: any) => {

                el.className += ` cell_${el.id.split("_")[0]}_${el.id.split("_")[1]}`
            })

        });
    }
}

let solver = new Solver();
