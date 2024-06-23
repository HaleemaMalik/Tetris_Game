/* NAME: HALEEMA TAHIR MALIK
 * ROLL NO: 22I-0937
 * BSCS PF PROJECT*/

/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

#include <iostream>
//---Piece Starts to Fall When Game Starts---//

void fallingPiece(float& timer, float& delay, int&colorNum,int& l,int&r){

    if (timer>delay){
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
            
        }
        if (!anamoly()){
        	for(int i=0; i<4; i++)
        	gameGrid[point_2[i][1]][point_2[i][0]]=colorNum;
        	colorNum=1+rand() %7;
                int n=rand()%7;
				l=rand()%4; 
            //--- Un-Comment this Part When You Make BLOCKS array---//
           if(l!=0)
		   {
			 for (int i=0;i<4;i++){
                    point_1[i][0] = BLOCKS[n][i] % 2;
                    point_1[i][1] = BLOCKS[n][i] / 2;
                }
		   }
		   else if(l==0)
		   {
				for (int i=0;i<4;i++){
                    point_1[i][0] = r;
                    point_1[i][1] = r;
                }
		   }
				 
			
               
            
        }
        timer=0;
       
    }
}


/////////////////////////////////////////////
///*** START CODING YOUR FUNCTIONS HERE ***///

//FUNCTION:2 ---To move the block right
void MovePieceRight(int& delta_x ,float& timer, float& delay, int&colorNum){


    if (delta_x==1){							//This condition is for moving the block in x-axis +1 unit when the right key is pressed

        for(int i=0; i<4; i++){


            point_2[i][0]=point_1[i][0];        //assigning the  new position to previous position of blocks
            point_2[i][1]=point_1[i][1];
            point_1[i][0]+=delta_x;              //moving the block 1 unit to right

        }
        delta_x=0;

        if(!anamoly()){                         //anomaly function for avoiding blocks sticking to the boundary

            for(int i=0;i<4;i++){

                point_1[i][0]=point_2[i][0];
                point_1[i][1]=point_2[i][1];
            }
            delta_x=0;
        }


        if (!anamoly()){
            for(int i=0; i<4; i++)
                gameGrid[point_2[i][1]][point_2[i][0]]=colorNum;
            colorNum=1+rand() %7;
            int n=rand()%7;

            for (int i=0;i<4;i++){
                point_1[i][0] = BLOCKS[n][i] % 2;
                point_1[i][1] = BLOCKS[n][i] / 2;
            }

        }
        timer=0;

    }

}

//FUNCTION 3: ---To move the block left
void MovePieceLeft(int& delta_x ,float& timer, float& delay, int&colorNum){


    if (delta_x==-1){							    //This condition is for moving the block in x-axis -1 unit when the left key is pressed

        for(int i=0; i<4; i++){


            point_2[i][0]=point_1[i][0];            //assigning the  new position to previous position of blocks
            point_2[i][1]=point_1[i][1];
            point_1[i][0]+=delta_x;                 //moving the block 1 unit to left

        }
        delta_x=0;

        if(!anamoly())                                  //anomaly function for avoiding blocks sticking to the boundary
        {
            for(int i=0;i<4;i++)
            {
                point_1[i][0]=point_2[i][0];
                point_1[i][1]=point_2[i][1];
            }
            delta_x=0;
        }


        if (!anamoly()){
            for(int i=0; i<4; i++)
                gameGrid[point_2[i][1]][point_2[i][0]]=colorNum;
            colorNum=1+rand() %7;
            int n=rand()%7;
            //--- Un-Comment this Part When You Make BLOCKS array---//

            for (int i=0;i<4;i++){
                point_1[i][0] = BLOCKS[n][i] % 2;
                point_1[i][1] = BLOCKS[n][i] / 2;
            }
        }
        timer=0;
    }
}

//FUNCTION 4: ---To rotate the block
void Rotate(bool& rotate){


    if (rotate){							//if up key is pressed, the flag of rotate will be true

        int xcen = point_1[1][0];           //finding out the coordinates of center of rotation of a block
        int ycen = point_1[1][1];

        for(int i=0; i<4; i++){

            int x = point_2[i][1] - ycen;
            int y = point_2[i][0] - xcen;

            point_1[i][0] = xcen - x;
            point_1[i][1] = ycen + y;

        }

        if(!anamoly())
        {
            for(int i=0;i<4;i++)
            {
                point_1[i][0]=point_2[i][0];
                point_1[i][1]=point_2[i][1];
            }
            rotate=false;
        }

        rotate=false;
    }

}


//FUNCTION 5: ---To remove a line

void RemoveLine() {
    //console out grid

    bool complete = false;
    for(int i = 0; i < M; i ++)
    {
        complete = false;
        for(int j =0; j < N ; j++)
        {
            if(gameGrid[i][j] == 0)
            {
                //this means line is incomplete
                break;
            }
            complete = true;
        }
        }

        //this means line is complete
        if(complete != false) {
            std::cout << "We completed a line" << std::endl;

            int max = M - 1;
            int complete_row = 0;                   //this will store the number of rows that are cleared

            for (int i = M - 1; i > 0; i--) {       //we will start to check the grid from bottom to top

                int x = 0;                          //this will store number of blocks
                for (int j = 0; j < N; j++) {

                    if (gameGrid[i][j]) {
                        x++;
                    }
                    gameGrid[max][j] = gameGrid[i][j];      //for replacing the top row with lower row
                }

                if (x < N)
                    max--;

                else
                    complete_row++;

            }
    switch (complete_row) {                                 //for passing the number of completed rows to switch to calculate the score

        case 1: {

            Currentscore += 10;

            break;
        }
        case 2: {

            Currentscore += 30;

            break;
        }

        case 3: {

            Currentscore += 60;

            break;
        }

        case 4: {

            Currentscore += 100;

            break;
        }
    }

            if(Highestscore<Currentscore)                       //if the current score is greater than the highest score, that will be saved in highest score
                Highestscore=Currentscore;
}

}


//FUNCTION 6: ---anomaly for shadow of blocks
bool Shadowanamoly(){

    for (int i=0;i<4;i++)

        if (Shadow_array[i][0]<0 || Shadow_array[i][0]>=N || Shadow_array[i][1]+1>=M)
            return 0;

        else if (gameGrid[Shadow_array[i][1]+1][Shadow_array[i][0]])
            return 0;

    return 1;
}

//FUNCTION 7: --- shadow of blocks
void Shadow(){

	for(int i=0; i<4 ; i++){

			Shadow_array[i][0]=point_1[i][0];               //storing the coordinates of new position in the shadow array
			Shadow_array[i][1]=point_1[i][1];

	}

	while (Shadowanamoly()){

                for (int i=0;i<4;i++){                      //to show the shadow above frame or blocks

                    Shadow_array[i][1]++;

                }
        }
}
//FUNCTION 8: --- to reset game
void resetgame(){

    for(int i =0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            point_1[i][j] = 0;                              //assigning the value of zero to coordinates to restart the game
            point_2[i][j] = 0;
        }
    }

    for (int i =0; i < M; i++)
    {
        for (int j =0; j <N; j++)
        {
            gameGrid[i][j] = 0;
        }
    }
    for (int i =0; i < M; i++)
    {
        for (int j =0; j <N; j++)
        {
            gameGrid2[i][j] = 0;
        }
    }
}
//FUNCTION 9: to end game
bool endgame(){

    for(int i=0; i<N ; i++) {

        if (gameGrid[0][i] > 0) {                               //when the top row will be completed, game will be over
            std::cout << "We are game is overs. You dead. Bye" << std::endl;
            return true;
        }
    }
            return false;

}

//FUnction 10: --- for falling bomb
void fallingBomb(float& timer, float& delay, int&colorNum,int& l,int&r){

    if (timer>delay){
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward

        }
        if (!anamoly()){

            for(int i=0; i<4; i++)
                gameGrid2[point_2[i][1]][point_2[i][0]]=colorNum;
            colorNum=1+rand() %7;
            int n=rand()%7;
            l=rand()%4;
            if(l!=0)
            {
                for (int i=0;i<4;i++){
                    point_1[i][0] = BLOCKS[n][i] % 2;
                    point_1[i][1] = BLOCKS[n][i] / 2;
                }
            }
            else if(l==0)
            {
                for (int i=0;i<4;i++){
                    point_1[i][0] = r;
                    point_1[i][1] = r;
                }

                r=rand()%9;
            }
            for(int i=0;i<M-1;i++)
            {
                for(int j=0;j<N;j++)
                {
                    if(gameGrid2[i][j]==gameGrid[i+1][j] && gameGrid2[i][j]!=0 && gameGrid[i+1][j]!=0)
                    {

                        for(int k=0;k<M;k++)
                        {
                            for(int h=0;h<N;h++)
                            {
                                gameGrid[k][h]=0;
                            }
                        }
                    }
                    else if(gameGrid2[i][j]!=gameGrid[i+1][j] && gameGrid2[i][j]!=0 && gameGrid[i+1][j]!=0)
                    {
                        gameGrid[i+1][j+1]=0;
                        gameGrid[i+2][j+2]=0;
                        gameGrid[i+1][j]=0;
                        gameGrid[i+2][j]=0;

                    }
                }
            }
            for(int i=0;i<M;i++)
            {
                for(int j=0;j<N;j++)
                {
                    gameGrid2[i][j]=0;
                }
            }

        }
        timer=0;

    }
}


///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
