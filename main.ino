
// Hardware interface
const int LEDPIN=9;
const int BTNPIN=10;

// The player info
struct playerInfo {
    uint8_t numTries;
    uint32_t totalTime;
    uint32_t fastest;
    uint32_t slowest;
    uint32_t lastTime;    
};

// Global state stuff
const int maxPlayers = 3;
struct playerInfo pinfo[maxPlayers];
int8_t curPlayer;
char buf[64];

void waitForBtn() {
       while( digitalRead(BTNPIN) ) {}
}


void printStats(int playerNum) {
    sprintf(buf, "Stats for player %i\r\n", playerNum+1); Serial.print(buf);
    sprintf(buf, "  Newest time: %i\r\n", pinfo[playerNum].lastTime); Serial.print(buf);
    sprintf(buf, "  Fastest time: %i\r\n", pinfo[playerNum].fastest); Serial.print(buf);
    sprintf(buf, "  Slowest time: %i\r\n", pinfo[playerNum].slowest); Serial.print(buf);
    sprintf(buf, "  Number of tries: %i\r\n", pinfo[playerNum].numTries); Serial.print(buf);
    sprintf(buf, "  Avg time: %i\r\n\r\n", (pinfo[playerNum].totalTime/pinfo[playerNum].numTries) ); Serial.print(buf);
}

bool playerTurn(uint8_t curPlayer) {
        // Blink the player number
    for(int i=0; i < curPlayer+1; i++) {
        digitalWrite(LEDPIN, 0);
        delay(500);
        digitalWrite(LEDPIN, 1);
        delay(500);
    }

    // Write helpful letters
    sprintf(buf, "\r\nPlayer %i, it's your turn!\r\n", curPlayer+1);
    Serial.print(buf);
    Serial.print("Press btn when ready, or longpress to yield turn!\r\n");
    int downTime=0;
    while(!downTime) {
            while(!digitalRead(BTNPIN)) {
                delay(1);
                downTime++;
            }
    }

    if(downTime > 500) {
        Serial.print("Player does not want any more turns.\r\n");
        return false;
    }

    digitalWrite(LEDPIN, 0);

    
    // Start the turn, by waiting a random amount of "time"
    delay(random(2000, 6001));

    // Turn off the LED
    digitalWrite(LEDPIN, 1);

    // Record start time
    unsigned long timeStart = millis();

    // Wait for meatbag to mash button with soft fleshy protrusion (such as a finger)
    waitForBtn();

    // Record stop time
    unsigned long timeStop = millis();

    // Turn on the led
    digitalWrite(LEDPIN, 0);

    unsigned long  curTime = timeStop - timeStart;

    pinfo[curPlayer].lastTime = curTime;

    //Find out if this was the slowest time
    if( curTime > pinfo[curPlayer].slowest ) {
        pinfo[curPlayer].slowest = curTime;
    }
    
    // Find out if this was the fastest time
    if( curTime < pinfo[curPlayer].fastest  ) {
        pinfo[curPlayer].fastest = curTime;
        Serial.print("         ,\r\n");
        Serial.print("        /|      __\r\n");
        Serial.print("       / |   ,-~ /\r\n");
        Serial.print("      Y :|  //  /\r\n");
        Serial.print("      | jj /( .^\r\n");
        Serial.print("      >-\"~\"-v\"\r\n");
        Serial.print("     /       Y\r\n");
        Serial.print("    jo  o    |\r\n");
        Serial.print("   ( ~T~     j\r\n");
        Serial.print("    >._-' _./\r\n");
        Serial.print("   /   \"~\"  |\r\n");
        Serial.print("  Y     _,  |\r\n");
        Serial.print(" /| ;-\"~ _  l\r\n");
        Serial.print("/ l/ ,-\"~    \\\r\n");
        Serial.print("\\//\\/      .- \\\r\n");
        Serial.print(" Y        /    Y    -Row\r\n");
        Serial.print(" l       I     !\r\n");
        Serial.print(" ]\\      _\\    /\"\\\r\n");
        Serial.print("(\" ~----( ~   Y.  )\r\n");
        Serial.print("\r\n");
        Serial.print("A winner is you!\r\n");
    }

    // Add to accumulator
    pinfo[curPlayer].totalTime += curTime;

    // Increase number fo times we did it
    pinfo[curPlayer].numTries++;

    // Print out the stats for this turn
    printStats(curPlayer);
    delay(1000);

    return true;
}

// Sets up variables for a new game.
void game() {
    

    for(int i=0; i < maxPlayers; i++) {
        memset( &pinfo[i], 0, sizeof(playerInfo));
        pinfo[i].fastest = 0xFFFFFFFF;
    }

    curPlayer=0;

    bool again = true;


    while( curPlayer < maxPlayers) {
        while( again ) {
            again = playerTurn(curPlayer);
        }
        curPlayer++;
        again=true;
    }

    Serial.print("\r\n\r\n\r\nGame over!\r\n");;
    for(int i=0; i < maxPlayers; i++) {
        printStats(i);
    }
    Serial.print("\r\nThank you for playing! Game resets all data now!\r\n");
}

void setup()  {
    // Set the LED pin to output..
    pinMode(LEDPIN, OUTPUT);
    // Turn the LED fof
    digitalWrite(LEDPIN, 1);
    // Button pin set to input
    pinMode(BTNPIN, INPUT);
    // Activate internal pullup resistor (methinks)
    digitalWrite(BTNPIN, 1);

    // Act as a serial device
    Serial.begin(9600);
    // Block until the serial port has been connected
    while(! Serial.available() ) {}
    Serial.print("Hello, this is reaction time game, you are happy now.\r\n");



}

void loop()  {
    // Initialize fresh game state
    game();
}