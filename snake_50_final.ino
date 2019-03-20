#include <FastLED.h>

#define NUM_LEDS 50
const int M=10;
const int N=5;

const int snake_max=50;
int snake[snake_max];
int slength;
int headr;
int headc;

int food;
int score;

const int  buttonPinN = 5;
const int  buttonPinS = 6;
const int  buttonPinE = 9;
const int  buttonPinW = 10;

int valN = 0;
int valS = 0;
int valE = 0;
int valW = 0;

int old_valN = 0;
int old_valS = 0;
int old_valE = 0;
int old_valW = 0;

int stateN = 0;
int stateS = 0;
int stateE = 0;
int stateW = 0;

int flagN = 0;
int flagS = 0;
int flagE = 0;
int flagW = 0;

CRGB leds[NUM_LEDS];

const int grid[M][N]={ 
    {0,1,2,3,4},
    {9,8,7,6,5},
    {10,11,12,13,14},
    {19,18,17,16,15},
    {20,21,22,23,24},
    {29,28,27,26,25},
    {30,31,32,33,34},
    {39,38,37,36,35},
    {40,41,42,43,44},
    {49,48,47,46,45},
};
void setup() {
 
  pinMode(buttonPinN, INPUT);
  pinMode(buttonPinS, INPUT);
  pinMode(buttonPinE, INPUT);
  pinMode(buttonPinW, INPUT);

  FastLED.addLeds<NEOPIXEL,13>(leds, NUM_LEDS);
  Serial.begin(9600);
  
  initializeSnake(0,2,3);
  
  
 
}

void initializeSnake(int lheadr,int lheadc, int s){
    FastLED.clear();
    headc=lheadc;
    headr=lheadr;
    slength=s;
    for(int i=0;i<slength;i++){  
       if(lheadc<0){
          lheadc=N-1;
       }   
       snake[i]={grid[lheadr][lheadc]};     
       lheadc--;
    }
  showSnake(snake);
  generateFood();
  
}

void showScore(){
 
   /*
    leds[grid[9][5]] = CRGB(50,0,50);
    leds[grid[10][5]] = CRGB(50,0,50);
    leds[grid[11][5]] = CRGB(50,0,50);
    
    leds[grid[9][7]] = CRGB(50,0,50);
    leds[grid[10][7]] = CRGB(50,0,50);
    leds[grid[11][7]] = CRGB(50,0,50);

    leds[grid[9][3]] = CRGB(50,0,50);
    leds[grid[10][3]] = CRGB(50,0,50);
    //leds[grid[11][4]] = CRGB(50,0,50);
    
    //leds[grid[9][5]] = CRGB(50,0,50);
  //  leds[grid[10][5]] = CRGB(50,0,50);
    leds[grid[11][2]] = CRGB(50,0,50);
    
    leds[grid[9][1]] = CRGB(50,0,50);
    leds[grid[10][1]] = CRGB(50,0,50);
   // leds[grid[11][6]] = CRGB(50,0,50);

*/


   leds[grid[3][4]] = CRGB(0,0,50);
   leds[grid[3][5]] = CRGB(0,0,50);
   leds[grid[16][4]] = CRGB(0,0,50);
   leds[grid[16][5]] = CRGB(0,0,50);
   
   leds[grid[4][3]] = CRGB(0,0,50);
   leds[grid[4][6]] = CRGB(0,0,50);
   leds[grid[15][3]] = CRGB(0,0,50);
   leds[grid[15][6]] = CRGB(0,0,50);
   
   leds[grid[5][2]] = CRGB(0,0,50);
   leds[grid[5][7]] = CRGB(0,0,50);
   leds[grid[6][2]] = CRGB(0,0,50);
   leds[grid[6][7]] = CRGB(0,0,50);
   leds[grid[13][2]] = CRGB(0,0,50);
   leds[grid[13][7]] = CRGB(0,0,50);
   leds[grid[14][2]] = CRGB(0,0,50);
   leds[grid[14][7]] = CRGB(0,0,50);

   leds[grid[7][1]] = CRGB(0,0,50);
   leds[grid[8][1]] = CRGB(0,0,50);
   leds[grid[9][1]] = CRGB(0,0,50);
   leds[grid[10][1]] = CRGB(0,0,50);
   leds[grid[11][1]] = CRGB(0,0,50);
   leds[grid[12][1]] = CRGB(0,0,50);
   leds[grid[7][8]] = CRGB(0,0,50);
   leds[grid[8][8]] = CRGB(0,0,50);
   leds[grid[9][8]] = CRGB(0,0,50);
   leds[grid[10][8]] = CRGB(0,0,50);
   leds[grid[11][8]] = CRGB(0,0,50);
   leds[grid[12][8]] = CRGB(0,0,50);


   leds[grid[8][3]] = CRGB(0,0,50);
   leds[grid[8][6]] = CRGB(0,0,50);
   leds[grid[11][3]] = CRGB(0,0,50);
   leds[grid[11][6]] = CRGB(0,0,50);
  
   leds[grid[12][4]] = CRGB(0,0,50);
   leds[grid[12][5]] = CRGB(0,0,50);


   leds[grid[4][4]] = CRGB::Yellow;
   leds[grid[4][5]] = CRGB::Yellow;
   
   leds[grid[5][3]] = CRGB::Yellow;
   leds[grid[5][4]] = CRGB::Yellow;
   leds[grid[5][5]] = CRGB::Yellow;
   leds[grid[5][6]] = CRGB::Yellow;
   
   leds[grid[6][3]] = CRGB::Yellow;
   leds[grid[6][4]] = CRGB::Yellow;
   leds[grid[6][5]] = CRGB::Yellow;
   leds[grid[6][6]] = CRGB::Yellow;
  
   leds[grid[7][2]] = CRGB::Yellow;
   leds[grid[7][3]] = CRGB::Yellow;
   leds[grid[7][4]] = CRGB::Yellow;
   leds[grid[7][5]] = CRGB::Yellow;
   leds[grid[7][6]] = CRGB::Yellow;
   leds[grid[7][7]] = CRGB::Yellow;
   
   leds[grid[8][2]] = CRGB::Yellow;
   leds[grid[8][4]] = CRGB::Yellow;
   leds[grid[8][5]] = CRGB::Yellow;
   leds[grid[8][7]] = CRGB::Yellow;
   
   leds[grid[9][2]] = CRGB::Yellow;
   leds[grid[9][3]] = CRGB::Yellow;
   leds[grid[9][4]] = CRGB::Yellow;
   leds[grid[9][5]] = CRGB::Yellow;
   leds[grid[9][6]] = CRGB::Yellow;
   leds[grid[9][7]] = CRGB::Yellow;
   
   leds[grid[10][2]] = CRGB::Yellow;
   leds[grid[10][3]] = CRGB::Yellow;
   leds[grid[10][4]] = CRGB::Yellow;
   leds[grid[10][5]] = CRGB::Yellow;
   leds[grid[10][6]] = CRGB::Yellow;
   leds[grid[10][7]] = CRGB::Yellow;
   
   leds[grid[11][2]] = CRGB::Yellow;
   leds[grid[11][4]] = CRGB::Yellow;
   leds[grid[11][5]] = CRGB::Yellow;
   leds[grid[11][7]] = CRGB::Yellow;
  
   leds[grid[12][2]] = CRGB::Yellow;
   leds[grid[12][3]] = CRGB::Yellow;
   leds[grid[12][6]] = CRGB::Yellow;
   leds[grid[12][7]] = CRGB::Yellow;

   leds[grid[13][3]] = CRGB::Yellow;
   leds[grid[13][4]] = CRGB::Yellow;
   leds[grid[13][5]] = CRGB::Yellow;
   leds[grid[13][6]] = CRGB::Yellow;
   
   leds[grid[14][3]] = CRGB::Yellow;
   leds[grid[14][4]] = CRGB::Yellow;
   leds[grid[14][5]] = CRGB::Yellow;
   leds[grid[14][6]] = CRGB::Yellow;

   leds[grid[15][4]] = CRGB::Yellow;
   leds[grid[15][5]] = CRGB::Yellow;
  
    FastLED.show();
}

void loop(){

  

  valN= digitalRead(buttonPinN);
  valS= digitalRead(buttonPinS);
  valE= digitalRead(buttonPinE);
  valW= digitalRead(buttonPinW);
  
  if ((valN == HIGH) && (old_valN == LOW) && flagS==0){
        stateN=1;
        stateS=0;
        stateE=0;
        stateW=0;
        delay(10);
  }
  if ((valS == HIGH) && (old_valS == LOW) && flagN==0){
        stateN=0;
        stateS=1;
        stateE=0;
        stateW=0;
        delay(10);
  }
  if ((valE == HIGH) && (old_valE == LOW) && flagW==0){
        stateN=0;
        stateS=0;
        stateE=1;
        stateW=0;
        delay(10);
  }
  if ((valW == HIGH) && (old_valW == LOW) && flagE==0){
        stateN=0;
        stateS=0;
        stateE=0;
        stateW=1;
        delay(10);
  }

  
  //Serial.print("The current val value is ="); Serial.print(val); Serial.println();
  old_valN = valN; 
  old_valS = valS; 
  old_valE = valE; 
  old_valW = valW; 

  
  if (stateN == 1) {
    check_Collision();
      updateNorth(snake);
      //printSnake(snake);
      showSnake(snake);
  }

  if (stateS==1){
   check_Collision();
     updateSouth(snake);
     //printSnake(snake);
      showSnake(snake);
  }
  
  
  if (stateW==1){
    //check_Collision();
      updateWest(snake);
      //printSnake(snake);
       showSnake(snake);
  }
 
  
  if (stateE==1){
   check_Collision();
      updateEast(snake);
      //printSnake(snake);
      showSnake(snake);
  }
 

}


void printSnake(int snake_local[]){
  for(int i=0; i<slength; i++){
    Serial.print("Element position:");
    Serial.print(i);
    Serial.print(" value is ");
    Serial.print(snake_local[i]);
    Serial.print(" value of headc ");
    Serial.print(headc);
    Serial.print(" value of headr ");
    Serial.print(headr);
    Serial.println("");
  }
  Serial.println("");

  
}

void updateNorth(int snake_local[]){
  
    for(int i=slength-2;i>=0;i--){
        snake_local[i+1]=snake_local[i];
    }
    headr--;
    if(headr<0){
      headr=M-1;
    }
    snake_local[0]=grid[headr][headc];
    
    flagN=1;
    flagS=0;
    flagE=0;
    flagW=0;
    
}
void updateSouth(int snake_local[]){
    
    for(int i=slength-2;i>=0;i--){
        snake_local[i+1]=snake_local[i];
    }
    headr++;
    if(headr>M-1){
      headr=0;
    }
    snake_local[0]=grid[headr][headc];
 
   flagN=0;
   flagS=1;
   flagE=0;
   flagW=0;
}

void updateEast(int snake_local[]){

    for(int i=slength-2;i>=0;i--){
        snake_local[i+1]=snake_local[i];
    }
    headc++;
    if(headc>N-1){
      headc=0;
    }
    snake_local[0]=grid[headr][headc];

   flagN=0;
   flagS=0;
   flagE=1;
   flagW=0;
}
void updateWest(int snake_local[]){

 
    for(int i=slength-2;i>=0;i--){
        snake_local[i+1]=snake_local[i];
    }
    headc--;
    if(headc<0){
      headc=N-1;
    }
    snake_local[0]=grid[headr][headc];

   flagN=0;
   flagS=0;
   flagE=0;
   flagW=1;
    
}



void showSnake(int snake_local[]){
   
   
   if(snake[0]==food){
    growSnake();
    generateFood();
   // showSnake(snake);
   }
   
   for(int i=0;i<slength;i++){
    
       if(i%7==0){
          leds[snake_local[i]] = CRGB(50,0,0); //[Green, Red, Blue ]  
       }
       if(i%7==1){
          leds[snake_local[i]] = CRGB(0,50,0); //[Green, Red, Blue ]  
       }
       if(i%7==2){
         leds[snake_local[i]] = CRGB(0,0,50); //[Green, Red, Blue ]  
       }
       if(i%7==3){
         leds[snake_local[i]] = CRGB(50,50,0); //[Green, Red, Blue ]  
       }
       if(i%7==4){
         leds[snake_local[i]] = CRGB::Brown; //[Green, Red, Blue ]  
       }
       if(i%7==5){
         leds[snake_local[i]] = CRGB(50,0,50); //[Green, Red, Blue ]  
       }
       if(i%7==6){
         leds[snake_local[i]] = CRGB(50,50,50); //[Green, Red, Blue ]  
       }
       
     //  leds[snake_local[i]] = CRGB(random(255),random(255),random(255)); //[Green, Red, Blue ]  
       
    }
    
    FastLED.show(); 
    
    delay(350); //control the speed of the snake from here!
    
   // leds[snake[slength-1]]=CRGB(0,0,0); //actually novely- best line of the code!22.2 |18.15

     for(int i=0;i<slength;i++){
         leds[snake_local[i]] = CRGB(0,0,0); //[Green, Red, Blue ]  
    }
}

void generateFood(){

  food= random(0,49);
  int flag =0;
  for(int i=0;i<slength;i++){
        if(snake[i]==food){
          flag =1;
        }
  }
  if(flag==1){
    generateFood();
    
  }
  else{
  leds[food]=CRGB(0,50,50);
  }
}


void growSnake(){

  slength++;
 // initializeSnake(headr,headc,slength);
  
  
}


void check_Collision(){
  /* if any of the coordinates of the snake_array match, 
   *  its a collision,then make the snake Red
   */

   int flag=0;
   
   for(int i=0;i<slength-1;i++){
      for(int j=i+1;j<slength;j++)
      { 
         if(snake[i]==snake[j]){
             flag=1;
             Serial.println(flag);
             break;
         }
      }
   }
   
    if(flag==1){
       show_Snake_Red();
    }
   
   
}

void show_Snake_Red(){
    
    for(int i=0;i<slength;i++){   
       leds[snake[i]] = CRGB(0,50,0); //[Green, Red, Blue ]        
    }
    FastLED.show();
    delay(2500);
     FastLED.clear();
    showScore();
   
    delay(2500);
    slength=3;
    initializeSnake(0,2,3);

}
