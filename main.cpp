/*Danny Lamarca
Final Project
4/27/15
I certify this work is my own.
*/


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

const int SIZE = 22;
const int alienMaxammo = 20;
const int MAXammo = 20;
const int ammoRefill = 5;
const int MAXhealth = 100;
const int alienMAXhealth = 100;
char PLAYER = 193;
char ALIEN = 29;
const char MEDPACK=4;
const char BULLETS=247;
const char SHOTGUN=169;
const char SHIELD=234;
const char GRENADE=235;
int score = 0;

void tutorial();
void menu();
void gameOverWIN(int&,int&, int&, int&);
void gameOverLOST(int&,int&, int&, int&);
void easterEgg();
void createArena(char [][SIZE], int);
void displayArena(char [][SIZE]);
void displayHUD (int, const int, int, const int, char, char, int, char);
void spawnItem(char [][SIZE],bool&, int&, int&, int&);
void alienmovement(char[][SIZE], int&, int&, int&, int&, char&, int&, int&, int&, int&, int&);
void firestrike(char[][SIZE], int, int, char);
void rotatePlayer (char[][SIZE], char&, char&, int&, char&, const int);
void basicFire(char[][SIZE],int&,int&, char&,int&,int& , int&, int& );
void hitDetectionP (char[][SIZE],int& ,int& , int&);
void hitDetectionA (char[][SIZE],int& ,int& , int&);
void alienbeam(char [][SIZE], int , int, char);
void playerPickup(char [][SIZE],int&,int&, int&, int&, int&, bool&, int&, bool&, int&, int&);
void alienPickup(char [][SIZE],int&,int&, int&, int&, int&, bool&, int&, int&, bool&, bool&);
void AlienbasicFire(char [][SIZE], char& ,int&,int&);
void Shotgun(char [][SIZE], int, int, char, int&);
void alienShotgun(char [][SIZE], int, int, char, int&);
void grenadeAttack(char[][SIZE], int, int, char,int&);
void PshieldReset(bool&);
void AshieldReset(bool&);
void detectGameover(int& , bool& , int&,int&, int&, int&);
void AMMOsteal(bool&, int&, int&);

int main()
{
    bool gameRun = true;
    char ARENA[SIZE][SIZE];//arena
    char movement;
    int health=100;
    int ammo = 10;
    int shotgunAmmo = 0;
    int playerGrenades = 0;
    char direction = 'N';
    char directArrow = ' ';
    int playerPts = 3;
    char recharge = 255;
    bool shieldON = false;
    int r=0;
    int X = 5;
    int Y = 5;
    int alienPts = 3;
    int alienAmmo = 10;
    int alienshotAmmo = 5;
    int noAmmo = 0;
    int pointDec = 1;
    int AnoAmmo = 0;
    bool AshieldON = false;
    bool alienAmmoSteal = true;
    int alienX = 10;
    int alienY = 15;
    bool spawn = false;
    int alienHealth= 100;
    char alienDirection = 'N';
    int ITEM = 0;
    int h=0;
    int c=0;
    string secret = " ";
    string phrase = "i hope i pass this class";

    menu();
    tutorial();
    while(gameRun == true)
    {
        while (playerPts>0)//PLAYER MOVES
        {
            createArena(ARENA, SIZE);
            ARENA[X][Y] = PLAYER;
            ARENA[alienX][alienY] = ALIEN;
            spawnItem(ARENA,spawn,h,c, ITEM);
            displayArena(ARENA);
            if (movement == 'w' && ARENA[X]>ARENA[1])
            {
                X--;
                direction = 'N';
                directArrow = 24;
                playerPts -= pointDec;
                PLAYER = 193;
            }
            else if (movement == 'a' && ARENA[Y]>ARENA[1])
            {
                Y--;
                direction = 'W';
                directArrow = 27;
                playerPts -= pointDec;
                PLAYER = 180;
            }
            else if (movement == 's'&& ARENA[X]<ARENA[20])
            {
                X++;
                direction = 'S';
                directArrow = 25;
                playerPts -= pointDec;
                PLAYER = 194;
            }
            else if (movement == 'd'&& ARENA[Y]<ARENA[20])
            {
                Y++;
                direction = 'E';
                directArrow = 26;
                playerPts -= pointDec;
                PLAYER = 195;
            }
            else if (movement == 't')
            {
                tutorial();
            }
            else if (movement == 'c')//EXTRA CREDIT EASTER EGG INPUT
            {
                cout << "Enter password: ";
                cin.ignore();
                getline(cin,secret);
                if (secret == phrase)
                {
                    gameRun=false;
                    easterEgg();
                    break;
                }
            }
            else if (movement == 'q' && shotgunAmmo>0)
            {
                Shotgun(ARENA,X, Y, direction, shotgunAmmo);
                if(AshieldON == false)
                {
                    hitDetectionP (ARENA, alienX, alienY, alienHealth);
                }
                playerPts -= pointDec;
                cout << "\n"<<shotgunAmmo<<" SHOTGUN ROUNDS LEFT!";
                for(int i = 0; i < 999999994; i++);
            }
            else if (movement == 'f' && ammo>0)
            {
                basicFire(ARENA, X, Y, direction, alienX, alienY, alienHealth, ammo);
                if(AshieldON == false)
                {
                    hitDetectionP (ARENA, alienX, alienY, alienHealth);
                }
                playerPts -= pointDec;
            }
            else if (movement == 'g' && playerGrenades>0)
            {
                grenadeAttack(ARENA, X, Y, direction, playerGrenades);
                if(AshieldON == false)
                {
                    hitDetectionP (ARENA, alienX, alienY, alienHealth);
                }
                cout << playerGrenades<<" GRENADES REMAINING!";
                for(int i = 0; i < 999999994; i++);
                playerPts -= pointDec;
            }
            else if (movement == 'r')
            {
                r++;
                if(r == 1)
                {
                    recharge = 95;
                }
                else if(r ==2)
                {
                    recharge = 61;
                }
                else if(r ==3)
                {
                    recharge = 240;
                    cout << "MISSILE STRIKE READY! \n";
                    for(int i = 0; i < 799999994; i++);

                }
                else if(r ==4)
                {
                    firestrike(ARENA, X, Y,direction);
                    if(AshieldON == false)
                    {
                        hitDetectionP (ARENA, alienX, alienY, alienHealth);
                    }
                    recharge = 255;
                    r = 0;
                }
                playerPts -= pointDec;
            }
            rotatePlayer (ARENA, direction, directArrow, playerPts, movement, pointDec);
            playerPickup(ARENA, X, Y, health, h, c, spawn, ammo, shieldON, shotgunAmmo, playerGrenades);
            displayHUD(health, MAXhealth, ammo, MAXammo, direction, directArrow, playerPts, recharge);
            cout << "Input Action: ";
            cin.get(movement);
            alienPts = 3;
        }
        AshieldReset(AshieldON);
        spawnItem(ARENA,spawn,h,c, ITEM);
        detectGameover(health, gameRun, alienHealth, ammo, shotgunAmmo, playerGrenades);
        if(ammo==0 && shotgunAmmo == 0 && playerGrenades == 0)
        {
            noAmmo++;
            score -= 50;
        }
        if(noAmmo==3)
        {
            cout<< "NO AMMO FOUND! PROBED!!!\n";
            for(int i = 0; i < 799999994; i++);
            gameOverLOST( health, ammo, shotgunAmmo, playerGrenades);
            gameRun=false;
            break;
        }
        while(alienPts>0)//ALIEN MOVES
        {
            alienPickup(ARENA, alienX, alienY, alienHealth, h, c, spawn, alienAmmo, alienshotAmmo, AshieldON, alienAmmoSteal);
            createArena(ARENA, SIZE);
            ARENA[X][Y] = PLAYER;
            displayArena(ARENA);
            alienPickup(ARENA, alienX, alienY, alienHealth, h, c, spawn, alienAmmo, alienshotAmmo, AshieldON, alienAmmoSteal);
            if (alienAmmoSteal == true)
            {
                AMMOsteal(alienAmmoSteal,ammo,alienAmmo);
                alienPts-=1;
            }
            alienmovement(ARENA, alienX, alienY, alienPts, alienAmmo, alienDirection, alienshotAmmo, h, c, X, Y);
            alienPickup(ARENA, alienX, alienY, alienHealth, h, c, spawn, alienAmmo, alienshotAmmo, AshieldON, alienAmmoSteal);
            displayArena(ARENA);

            if (shieldON == false)
            {
                hitDetectionA (ARENA,X,Y,health);
            }
            playerPts = 3;
        }
        PshieldReset(shieldON);
        spawnItem(ARENA,spawn,h,c, ITEM);
        detectGameover(health, gameRun, alienHealth, ammo, shotgunAmmo, playerGrenades);
        alienPickup(ARENA, alienX, alienY, alienHealth, h, c, spawn, alienAmmo, alienshotAmmo, AshieldON, alienAmmoSteal);
        if(alienAmmo==0 && alienshotAmmo== 0)
        {
            AnoAmmo++;
        }
        if(AnoAmmo==5)
        {
            gameOverWIN(health, ammo, shotgunAmmo, playerGrenades);
            gameRun=false;
            break;
        }
    }

    return 0;
}

void tutorial()//EXTRA CREDIT TUTORIAL ABLE TO BE CALLED AT ANY TIME DURING GAMEPLAY
{
    system("cls");
    cout << "-Use w,a,s,d to move one block NORTH, WEST, SOUTH, EAST.\n";
    cout << "-Use i,j,k,l to rotate NORTH, WEST, SOUTH, EAST.(ENTER) \n";
    system("pause>nul");
    cout << "-Enter 'f' to fire main weapon. 'Q' fires your shotgun.(ENTER)\n";
    system("pause>nul");
    cout << "-Moving over items will pick them up and use them."<<endl;
    cout << "-Items  available for pickup: Medpack = " << MEDPACK << "\tAmmo = " << BULLETS << endl;
    cout <<"Shotgun Ammo = " << SHOTGUN << "\tShield = "<< SHIELD<< "\tGrenades = "<<GRENADE <<endl;
    cout << "-These items will spawn randomly in the map. Be careful though, "<<endl;
    cout << "the enemy can also pick these up!(ENTER)\n";
    system("pause>nul");
    cout<< "-Actions use action points, only 3 allowed per turn. USE THEM CAREFULLY.(ENTER)\n";
    system("pause>nul");
    cout<< "-When you run out of ALL ammo and can't find more within 3 rounds the alien\nautomatically probe's you to death.\n";
    system("pause>nul");
    cout << "-A missile strike can be charged up by entering 'r', using up an action point.\n";
    cout<< "Once the strike has been charged up three times it will be ready to fire,\nby entering 'r'. This will unleash an attack that affects a straight line\nin the direction you are facing.\n";
    system("pause>nul");
    cout << "Careful not to let life drop to 0. Once all life is lost, you will be defeated.\n";
    cout << "-This tutorial can be brought up at any time by entering 't'.\n";
    system("pause>nul");
    cout << "-GOOD LUCK.";
    for(int i = 0; i < 799999994; i++);

}

void createArena(char ARENA[][SIZE], int s)
{
    for(int i = 0; i < s; i++)
    {
        ARENA[0][i] = 194;//top row
        ARENA[s-1][i] =193;//bottom row
        ARENA[i][0] = 198;//left row
        ARENA[i][s-1] = 181;//right row
    }
    ARENA[0][0] = 197;
    ARENA[0][s-1] = 197;
    ARENA[s-1][0] = 197;
    ARENA[s-1][s-1] = 197;

    for(int i = 1; i < s-1; i++)
    {
        for(int j = 1; j < s-1; j++)
        {
            ARENA[i][j] = 255;
        }
    }
}
void displayArena(char ARENA[][SIZE])
{
    system("cls");
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            cout << ARENA[i][j];
        }
        cout << endl;
    }
}

void displayHUD(int health, const int MAXhealth, int ammo, const int MAXammo, char direction, char directArrow, int playerPts, char recharge)
{
    const char ammoSign =126;
    const char pointsSign = 158;
    cout << "HEALTH: " << health << "/" << MAXhealth << "+";
    cout << setw(8)<<"AMMO: " <<  ammo << "/" << MAXammo<<ammoSign;
    cout << setw(15) <<"Direction: " << direction<< setw(2)<<directArrow;
    cout << setw(2) << pointsSign<<": " <<playerPts;
    cout << setw(20) << "Strike Recharge: " << recharge<<endl;
}

//------------------------------------------
//SPAWN ITEMS, *EXTRA ITEMS SPAWNED
//-------------------------------------------------
void spawnItem(char ARENA[][SIZE],bool& spawn, int& h, int& c, int& ITEM)
{
    static int r = 0;
    r++;
    if (r==50)
    {
        spawn = false;
        r = 0;
    }
    srand(time(0));
    if(spawn == false)
    {
        h=1+(rand()%18);
        c=1+(rand()%18);
        ITEM = 1+(rand()%9);
    }

    if(ITEM == 9 || ITEM == 10 || ITEM == 8)//spawn health
    {
        ARENA[h][c]=MEDPACK;
        spawn = true;
    }
    else if(ITEM == 6 || ITEM == 3 || ITEM == 7)//spawn ammo
    {
        ARENA[h][c]=BULLETS;
        spawn = true;
    }
    else if(ITEM == 2)//spawn SHOTGUN
    {
        ARENA[h][c]=SHOTGUN;
        spawn = true;
    }
    else if(ITEM == 4)//spawn shield
    {
        ARENA[h][c]=SHIELD;
        spawn = true;
    }
    else if(ITEM == 1 || ITEM == 5)//spawn grenade
    {
        ARENA[h][c]=GRENADE;
        spawn = true;
    }

}


void alienmovement(char ARENA[][SIZE],int& alienX,int& alienY, int& alienPts, int& alienAmmo, char& alienDirection, int& alienshotAmmo, int& h, int& c, int& X, int& Y)
{
    int m=0;
    srand(time(0));
    m=1+(rand()%7);
    if (alienAmmo<3 && alienX != h)//EXTRA CREDIT SMART AI THAT SEEKS OUT AMMO WHEN IT DROPS BELOW 3
    {
        if (alienX<h)
        {
            alienX++;
            alienDirection='S';
        }
        else if(alienX>h)
        {
            alienX--;
            alienDirection = 'N';
        }

        ARENA[alienX][alienY]=ALIEN;
        displayArena(ARENA);
        alienPts -=1;
    }
    else if (alienAmmo<3 && alienY != c)
    {
        if (alienY<c)
        {
            alienY++;
            alienDirection='W';
        }
        else if(alienY>c)
        {
            alienY--;
            alienDirection = 'E';
        }

        ARENA[alienX][alienY]=ALIEN;
        displayArena(ARENA);
        alienPts -=1;
    }
    else if(alienAmmo>3)
    {
        for(int i = 0; i<alienX; i++)//EXTRA CREDIT SMART AI THAT DETECTS WHEN TO SHOOT BEAM
        {
            if(ARENA[i]== ARENA[X] && ARENA[alienY]==ARENA[Y])
            {
                m=6;
                alienDirection= 'N';
            }
        }
        for(int i = 0; i<alienY; i++)
        {
            if(ARENA[alienX]== ARENA[X] && ARENA[i]==ARENA[Y])
            {
                alienDirection= 'W';
                m=6;
            }
        }
        for(int i = SIZE; i>alienX; i--)
        {
            if(ARENA[i]== ARENA[X] && ARENA[alienY]==ARENA[Y])
                alienDirection= 'S';
            m=6;
        }
        for(int i = SIZE; i>alienY; i--)
        {
            if(ARENA[i]== ARENA[X] && ARENA[i]==ARENA[Y])
            {
                alienDirection= 'E';
                m=6;
            }
        }
    }
    if(alienX+1 == X && alienshotAmmo>0)
    {
        m=8;
        alienDirection = 'S';
    }
    else if(alienX-1 == X&& alienshotAmmo>0)
    {
        m=8;
        alienDirection = 'N';
    }
    switch (m)
    {
    case 1://alien moves up
        if(ARENA[alienX]<ARENA[2])
        {
            ARENA[alienX][alienY]=ALIEN;
            break;
        }
        ARENA[alienX][alienY]=ALIEN;
        alienX--;
        alienPts -= 1;
        alienDirection = 'N';
        break;
    case 2://alien moves left
        if(ARENA[alienY]<ARENA[2])
        {
            ARENA[alienX][alienY] = ALIEN;
            break;
        }
        ARENA[alienX][alienY] = ALIEN;
        alienY--;
        alienPts -= 1;
        alienDirection = 'W';
        break;
    case 3://alien moves down
        if(ARENA[alienX]>ARENA[19])
        {
            ARENA[alienX][alienY]=ALIEN;
            break;
        }
        ARENA[alienX][alienY]=ALIEN;
        alienX++;
        alienPts -= 1;
        alienDirection = 'S';
        break;
    case 4://alien moves right
        if(ARENA[alienY]>ARENA[19])
        {
            ARENA[alienX][alienY] = ALIEN;
            break;
        }
        ARENA[alienX][alienY] = ALIEN;
        alienY++;
        alienPts -= 1;
        alienDirection = 'E';
        break;
    case 5://EXREA CREDIT alien area of effect attack
        if (alienAmmo <= 0)
        {
            ARENA[alienX][alienY] = ALIEN;
            break;
        }
        alienAmmo -=1;
        alienPts -= 1;
        ARENA[alienX][alienY] = ALIEN;
        ARENA[alienX+1][alienY] = 'X';
        ARENA[alienX][alienY+1] = 'X';
        ARENA[alienX-1][alienY] = 'X';
        ARENA[alienX][alienY-1] = 'X';
        ARENA[alienX+1][alienY+1] = 'X';
        ARENA[alienX-1][alienY-1] = 'X';
        ARENA[alienX+1][alienY-1] = 'X';
        ARENA[alienX-1][alienY+1] = 'X';
        ARENA[alienX+2][alienY] = 'X';
        ARENA[alienX][alienY+2] = 'X';
        ARENA[alienX-2][alienY] = 'X';
        ARENA[alienX][alienY-2] = 'X';
        ARENA[alienX+3][alienY+2] = 'X';
        ARENA[alienX-3][alienY-2] = 'X';
        ARENA[alienX+3][alienY-2] = 'X';
        ARENA[alienX-3][alienY+2] = 'X';
        break;
    case 6://alien fires beam
        if (alienAmmo <= 0)
        {
            ARENA[alienX][alienY] = ALIEN;
            break;
        }
        alienbeam(ARENA, alienX, alienY, alienDirection);
        ARENA[alienX][alienY] = ALIEN;
        alienPts -= 1;
        alienAmmo -=1;
        break;
    case 7://alien basic fire
        if (alienAmmo <= 0)
        {
            ARENA[alienX][alienY] = ALIEN;
            break;
        }
        AlienbasicFire(ARENA, alienDirection,alienX, alienY);
        ARENA[alienX][alienY] = ALIEN;
        alienPts -= 1;
        break;
    case 8: //alien shotgun
        if(alienshotAmmo>0)
        {
            alienShotgun(ARENA, alienX, alienY, alienDirection, alienshotAmmo);
            ARENA[alienX][alienY] = ALIEN;
            alienPts -= 1;
            break;
        }
        else
        {
            ARENA[alienX][alienY] = ALIEN;
            break;
        }
    }
}


void firestrike(char ARENA[][SIZE], int X, int Y, char direction)//EXTRA CREDIT secondary weapon function player
{
    switch(direction)
    {
    case 'N':
        for (int i =X-1; i>0; i--)
        {
            ARENA[i][Y]='X';
            displayArena(ARENA);
        }
        break;
    case 'S':
        for (int i = X+1; i<19; i++)
        {
            ARENA[i][Y]='X';
            displayArena(ARENA);
        }

        break;
    case 'E':
        for (int i =Y+1; i<19; i++)
        {
            ARENA[X][i]='X';
            displayArena(ARENA);
        }
        break;
    case 'W':
        for (int i =Y-1; i>0 ; i--)
        {
            ARENA[X][i]='X';
            displayArena(ARENA);
        }
        displayArena(ARENA);
        break;
    }
}

void rotatePlayer (char ARENA[][SIZE], char& direction, char& directArrow, int& playerPts, char& movement, const int pointDec)//ROTATES PLAYER
{
    switch(movement)
    {
    case 'i':
        direction = 'N';
        directArrow = 24;
        playerPts -= pointDec;
        PLAYER = 193;
        break;
    case 'j':
        direction = 'W';
        directArrow = 27;
        playerPts -= pointDec;
        PLAYER = 180;
        break;
    case 'k':
        direction = 'S';
        directArrow = 25;
        playerPts -= pointDec;
        PLAYER = 194;
        break;
    case 'l':
        direction = 'E';
        directArrow = 26;
        playerPts -= pointDec;
        PLAYER = 195;
        break;
    }
}

void hitDetectionP (char ARENA[][SIZE],int& alienX,int& alienY, int& alienHealth)//detects if player hits alien
{
    if ('x'== ARENA[alienX][alienY])
    {
        alienHealth -= 10;
        displayArena(ARENA);
        score += 100;
        for(int i = 0; i < 99999994; i++);
        cout << "NICE HIT! ALIEN HAS TAKEN 10 DAMAGE POINTS!";
        for(int i = 0; i < 99999994; i++);
    }
    else if ('O'== ARENA[alienX][alienY])
    {
        alienHealth -= 80;
        displayArena(ARENA);
        score += 800;
        for(int i = 0; i < 99999994; i++);
        cout << "BOOM! DIRECT SHOTGUN BLAST! CRITICAL DAMAGE TO ALIEN (-80 ALIEN HEALTH POINTS)";
        for(int i = 0; i < 99999994; i++);
    }
    else if ('o'== ARENA[alienX][alienY])
    {
        alienHealth -= 20;
        displayArena(ARENA);
        score += 200;
        for(int i = 0; i < 99999994; i++);
        cout << "BOOM! YOU GRAZED THE ALIEN WITH YOUR SHOTGUN! (-20 ALIEN HEALTH POINTS)\n";
        for(int i = 0; i < 99999994; i++);
    }
    else if ('X'== ARENA[alienX][alienY])
    {
        alienHealth -= 40;
        displayArena(ARENA);
        score += 400;
        for(int i = 0; i < 99999994; i++);
        cout << "MISSILE STRIKE EFFECTIVE! -40 HEALTH DEMOLISHED FROM ALIEN.";
        for(int i = 0; i < 99999994; i++);
    }
    else if ('*'== ARENA[alienX][alienY])
    {
        alienHealth -= 40;
        displayArena(ARENA);
        score += 500;
        for(int i = 0; i < 99999994; i++);
        cout << "GRENADE TOSS ON TARGET! -40 HEALTH BLOWN AWAY FROM ALIEN.";
        for(int i = 0; i < 99999994; i++);
    }

    else
    {
        for(int i = 0; i < 999994; i++);
        cout << "TARGET MISSED! ";
        score -= 100;
        for(int i = 0; i < 999999994; i++);
    }

}
void hitDetectionA (char ARENA[][SIZE],int& X,int& Y, int& health)//detects if alien hits player
{
    if ('X'== ARENA[X][Y])
    {
        health -= 10;
        displayArena(ARENA);
        for(int i = 0; i < 99999994; i++);
        cout << "ONLY LOSERS GET HIT BY SHOCKWAVE, GUESS YOU ARE ONE. (-10 HEALTH)";
        for(int i = 0; i < 999999994; i++);
    }
    else if ('Y'== ARENA[X][Y] || '-'== ARENA[X][Y])
    {
        health -= 30;
        displayArena(ARENA);
        for(int i = 0; i < 99999994; i++);
        cout << "YOU GOT #REKT BY THE ALIEN BEAM. (-30 HEALTH)";
        for(int i = 0; i < 999999994; i++);
    }
    else if ('x'== ARENA[X][Y])
    {
        health -= 50;
        displayArena(ARENA);
        for(int i = 0; i < 99999994; i++);
        cout << "ALIEN GOT A DIRECT HIT ON YOU. (-50 HEALTH)";
        for(int i = 0; i < 999999994; i++);
    }
    else if ('O'== ARENA[X][Y])
    {
        health -= 80;
        displayArena(ARENA);
        for(int i = 0; i < 99999994; i++);
        cout << "YOU'VE BEEN BLASTED BY A SHOTGUN- DAMAGE IS SEVERE! (-80 HEALTH)";
        for(int i = 0; i < 99999994; i++);
    }
    else if ('o'== ARENA[X][Y])
    {
        health -= 20;
        displayArena(ARENA);
        for(int i = 0; i < 99999994; i++);
        cout << "YOU'VE BEEN GRAZED BY THE ALIEN SHOTGUN BLAST! (-20 HEALTH)";
        for(int i = 0; i < 99999994; i++);
    }
    else if ('*'== ARENA[X][Y])
    {
        health -= 40;
        displayArena(ARENA);
        for(int i = 0; i < 99999994; i++);
        cout << "YOU'VE BEEN BLOWN UP BY ENEMY GRENADE! (-40 HEALTH)";
        for(int i = 0; i < 99999994; i++);
    }

}

void basicFire(char ARENA[][SIZE], int& X, int& Y, char& direction,int& alienX,int& alienY, int& alienHealth, int& ammo)//main weapon function
{
    switch(direction)
    {
    case 'N':

        ARENA[X-2][Y]='x';
        displayArena(ARENA);
        ammo-=1;
        break;
    case 'S':
        ARENA[X+2][Y]='x';
        displayArena(ARENA);
        ammo-=1;
        break;
    case 'E':
        ARENA[X][Y+2]='x';
        displayArena(ARENA);
        ammo-=1;
        break;
    case 'W':
        ARENA[X][Y-2]='x';
        displayArena(ARENA);
        ammo-=1;
        break;
    }
}

void alienbeam(char ARENA[][SIZE], int alienX, int alienY, char alienDirection)//EXTRA CREDIT alien beam function
{
    switch(alienDirection)
    {
    case 'N':
        for (int i =alienX-1; i>0; i--)
        {
            ARENA[alienX][alienY]=29;
            ARENA[i][alienY]='Y';
            displayArena(ARENA);
        }
        break;
    case 'S':
        for (int i = alienX+1; i<19; i++)
        {
            ARENA[alienX][alienY]=29;
            ARENA[i][alienY]='Y';
            displayArena(ARENA);
        }
        break;
    case 'E':
        for (int i =alienY+1; i<19; i++)
        {
            ARENA[alienX][alienY]=18;
            ARENA[alienX][i]='-';
            displayArena(ARENA);
        }
        break;
    case 'W':
        for (int i =alienY-1; i>0 ; i--)
        {
            ARENA[alienX][alienY]=18;
            ARENA[alienX][i]='-';
            displayArena(ARENA);
        }
        displayArena(ARENA);
        break;
    }
}

void Shotgun(char ARENA[][SIZE], int X, int Y, char direction,int& ammo)//EXTRA CREDIT SHOTGUN WEAPON function
{
    switch(direction)
    {
    case 'N':

        ARENA[X-1][Y]='O';
        ARENA[X-2][Y+1]='o';
        ARENA[X-2][Y-1]='o';
        displayArena(ARENA);
        ammo-=1;
        break;
    case 'S':
        ARENA[X+1][Y]='O';
        ARENA[X+2][Y+1]='o';
        ARENA[X+2][Y-1]='o';
        displayArena(ARENA);
        ammo-=1;
        break;
    case 'E':
        ARENA[X][Y+1]='O';
        ARENA[X-1][Y+2]='o';
        ARENA[X+1][Y+2]='o';
        displayArena(ARENA);
        ammo-=1;
        break;
    case 'W':
        ARENA[X][Y-1]='O';
        ARENA[X-1][Y-2]='o';
        ARENA[X+1][Y-2]='o';
        displayArena(ARENA);
        ammo-=1;
        break;
    }
}

void alienShotgun(char ARENA[][SIZE], int alienX, int alienY, char alienDirection,int& alienshotAmmo)//EXTRA CREDIT alien SHOTGUN WEAPON function
{
    switch(alienDirection)
    {
    case 'N':
        ARENA[alienX][alienY]=29;
        ARENA[alienX-1][alienY]='O';
        ARENA[alienX-2][alienY+1]='o';
        ARENA[alienX-2][alienY-1]='o';
        displayArena(ARENA);
        alienshotAmmo-=1;
        break;
    case 'S':
        ARENA[alienX][alienY]=29;
        ARENA[alienX+1][alienY]='O';
        ARENA[alienX+2][alienY+1]='o';
        ARENA[alienX+2][alienY-1]='o';
        displayArena(ARENA);
        alienshotAmmo-=1;
        break;
    case 'E':
        ARENA[alienX][alienY]=29;
        ARENA[alienX][alienY+1]='O';
        ARENA[alienX-1][alienY+2]='o';
        ARENA[alienX+1][alienY+2]='o';
        displayArena(ARENA);
        alienshotAmmo-=1;
        break;
    case 'W':
        ARENA[alienX][alienY]=29;
        ARENA[alienX][alienY-1]='O';
        ARENA[alienX-1][alienY-2]='o';
        ARENA[alienX+1][alienY-2]='o';
        displayArena(ARENA);
        alienshotAmmo-=1;
        break;
    }
}

void AlienbasicFire(char ARENA[][SIZE], char& alienDirection,int& alienX,int& alienY)//ALIEN main weapon function
{
    switch(alienDirection)
    {
    case 'N':

        ARENA[alienX-2][alienY]='x';
        displayArena(ARENA);
        for(int i = 0; i < 99999994; i++);
        break;
    case 'S':
        ARENA[alienX+2][alienY]='x';
        displayArena(ARENA);
        for(int i = 0; i < 99999994; i++);
        break;
    case 'E':
        ARENA[alienX][alienY+2]='x';
        displayArena(ARENA);
        for(int i = 0; i < 99999994; i++);
        break;
    case 'W':
        ARENA[alienX][alienY-2]='x';
        displayArena(ARENA);
        for(int i = 0; i < 99999994; i++);
        break;
    }
}


void alienPickup(char ARENA[][SIZE],int& alienX,int& alienY, int& alienHealth, int& h, int& c, bool& spawn, int& alienAmmo, int& alienshotAmmo, bool& AshieldON, bool& alienAmmoSteal)
{
    if(ARENA[alienX]== ARENA[h] && alienHealth < alienMAXhealth && ARENA[alienY] == ARENA[c]&& ARENA[h][c]==MEDPACK)//health pickup
    {
        alienHealth += 10;
        cout << "\nALIEN HAS GAINED HEALTH!\n";
        for(int i = 0; i < 999999994; i++);
        spawn=false;
    }
    else if(ARENA[alienX]== ARENA[h] && alienAmmo < alienMaxammo && ARENA[alienY] == ARENA[c] && ARENA[h][c]==BULLETS)//ammo pickup
    {
        alienAmmo += ammoRefill;
        cout << "ALIEN HAS GAINED AMMO!\n";
        for(int i = 0; i < 999999994; i++);
        spawn = false;
    }
    else if(ARENA[alienX]== ARENA[h] && ARENA[alienY] == ARENA[c] && ARENA[h][c]==SHOTGUN)//EXTRA CREDITSHOTGUN pickup
    {
        cout << "WATCH OUT ALIEN HAS PICKED UP A SHOTGUN!\n";
        for(int i = 0; i < 999999994; i++);
        alienshotAmmo = 5;
        spawn = false;
        alienshotAmmo +=ammoRefill;
    }
    else if(ARENA[alienX]== ARENA[h] && ARENA[alienY] == ARENA[c] && ARENA[h][c]==SHIELD)//EXTRA CREDIT shield pickup
    {
        cout << "ALIEN HAS TURNED ON SHIELD! (ALIEN IS INVULNERABLE FOR 1 ROUND)\n";
        for(int i = 0; i < 999999994; i++);
        spawn = false;
        AshieldON = true;
    }
    else if(ARENA[alienX]== ARENA[h] && ARENA[alienY] == ARENA[c] && ARENA[h][c]==GRENADE)//EXTRA CREDIT ALIEN ammo steal ability pickup
    {
        cout << "ALIEN HAS ACQUIRED SHIP CODES! IT CAN STEAL YOUR AMMO!\n";
        for(int i = 0; i < 999999994; i++);
        alienAmmoSteal = true;
        spawn = false;
    }
}


void playerPickup(char ARENA[][SIZE],int& X,int& Y, int& health, int& h, int& c, bool& spawn, int& ammo, bool& shieldON, int& shotgunAmmo, int& playerGrenades)
{
    if(ARENA[X]== ARENA[h]  && health < MAXhealth && ARENA[Y] == ARENA[c]&& ARENA[h][c]==MEDPACK)//health pickup
    {
        health += 10;
        cout << "\nYOU GOT A HEALTH MEDPACK! (+10 HEALTH)\n";
        for(int i = 0; i < 999999994; i++);
        spawn=false;
    }
    else if(ARENA[X]== ARENA[h]  && ammo < MAXammo && ARENA[Y] == ARENA[c] && ARENA[h][c]==BULLETS)//ammo pickup
    {
        ammo += 5;
        cout << "YOU GOT SOME SHITTY BULLETS PUSSY!!!! (+5 AMMO)\n";
        for(int i = 0; i < 99999994; i++);
        spawn = false;
    }
    else if(ARENA[X]== ARENA[h] && ARENA[Y] == ARENA[c] && ARENA[h][c]==SHOTGUN)//SHOTGUN pickup
    {
        cout << "YOU PICKED UP A SHOTGUN. WRECK THAT ALIEN! (PRESS 'q' TO USE)\n";
        for(int i = 0; i < 999999994; i++);
        spawn = false;
        shotgunAmmo += 5;
    }
    else if(ARENA[X]== ARENA[h] && ARENA[Y] == ARENA[c] && ARENA[h][c]==SHIELD)//shield pickup
    {
        cout << "PROTECTIVE SHIELD IS ON. (INVULNERABILITY FOR 1 ROUND)\n";
        for(int i = 0; i < 999999994; i++);
        spawn = false;
        shieldON=true;
    }
    else if(ARENA[X]== ARENA[h] && ARENA[Y] == ARENA[c] && ARENA[h][c]==GRENADE)//GRENADE pickup
    {
        cout << "GRENADES HAVE BEEN ADDED TO YOUR AVAILABLE WEAPONS \n";
        for(int i = 0; i < 999999994; i++);
        playerGrenades += 2;
        spawn = false;
    }
}

void grenadeAttack(char ARENA[][SIZE], int X, int Y, char direction,int& playerGrenades)//EXTRA CREDIT PLAYER GRENADE TOSS function
{
    switch(direction)
    {
    case 'N':

        ARENA[X-5][Y]='*';
        ARENA[X-5][Y+1]='*';
        ARENA[X-6][Y]='*';
        ARENA[X-6][Y+1]= '*';
        displayArena(ARENA);
        playerGrenades-=1;
        break;
    case 'S':
        ARENA[X+5][Y]='*';
        ARENA[X+5][Y+1]='*';
        ARENA[X+6][Y]='*';
        ARENA[X+6][Y+1]= '*';
        displayArena(ARENA);
        playerGrenades-=1;
        break;
    case 'E':
        ARENA[X][Y+5]='*';
        ARENA[X+1][Y+5]='*';
        ARENA[X][Y+6]='*';
        ARENA[X+1][Y+6]= '*';
        displayArena(ARENA);
        playerGrenades-=1;
        break;
    case 'W':
        ARENA[X][Y+5]='*';
        ARENA[X+1][Y-5]='*';
        ARENA[X][Y-6]='*';
        ARENA[X+1][Y-6]= '*';
        displayArena(ARENA);
        playerGrenades-=1;
        break;
    }
}

void gameOverWIN(int& health,int& ammo, int& shotgunAmmo, int& playerGrenades)//EXTRA CREDIT HIGH SCORES STATS AND SELECTION SORTING OF THE SCORES, READ FROM A FILE
{
    fstream scoreFile;
    scoreFile.open("scores.txt", ios::in | ios::out | ios::app);
    int sizes = 0;
    int highscores[sizes];
    int startscan, minIndex, minvalue;
    score += 1000;
    score += (ammo*50) + (health*10)+ (shotgunAmmo*100) + (playerGrenades*200);
    scoreFile <<endl<<score;
    scoreFile.close();
    scoreFile.open("scores.txt", ios::in | ios::out | ios::app);
    system("cls");
    cout <<  "\n\n\n\n\n\n\n"<< setw(45) << "VICTORY! \n";
    for(int i = 0; i < 9999994; i++);
    cout << setw(57) <<"YOU HAVE DEAFEATED THE ENEMY ALIEN!" ;
    for(int i = 0; i < 9999994; i++);
    cout <<setw(65)<< "SCORE: "<<score<< "\n\n";
    cout <<setw(45)<< "HIGH SCORES\n";
    while(scoreFile>>highscores[sizes])
    {
        sizes++;
    }
    for(int i = 0; i<sizes; i++)
    {
        scoreFile >> highscores[i];
    }
    for (startscan = 0; startscan<(sizes-1); startscan++)
    {
        minIndex = startscan;
        minvalue = highscores[startscan];
        for(int index = startscan + 1; index<sizes; index++)
        {
            if (highscores[index]>minvalue)
            {
                minvalue = highscores[index];
                minIndex = index;
            }
        }
        highscores[minIndex] = highscores[startscan];
        highscores[startscan] = minvalue;
    }


    if(score>=highscores[0])
    {
        cout<< setw(37)<< "1. "<<highscores[0];
        cout<< setw(15)<< " NEW HIGH SCORE!"<<endl;
    }
    else
    {
        cout<< setw(37)<< "1. "<<highscores[0]<<endl;
    }

    for(int i = 1; i<5; i++)
    {
        scoreFile << highscores[i];
        cout << setw(35) <<i+1<<". "<< highscores[i]<<endl;
    }

    scoreFile.close();
    system("pause>nul");
    exit(0);
}

void gameOverLOST(int& health,int& ammo, int& shotgunAmmo, int& playerGrenades)
{
    fstream scoreFile;
    scoreFile.open("scores.txt", ios::in | ios::out | ios::app);
    int sizes = 0;
    int highscores[sizes];
    int startscan, minIndex, minvalue;
    score -=500;
    score += (ammo*50) + (health*10)+ (shotgunAmmo*100) + (playerGrenades*200);
    scoreFile <<endl<<score;
    scoreFile.close();
    scoreFile.open("scores.txt", ios::in | ios::out | ios::app);
    system("cls");
    cout <<  "\n\n\n\n\n\n\n"<< setw(45) << "DEFEAT! \n";
    for(int i = 0; i < 9999994; i++);
    cout << setw(60) <<"ALIEN HAS ANNIHILATED YOU AND THE EARTH!\n" ;
    for(int i = 0; i < 9999994; i++);
    cout <<setw(40)<< "SCORE: "<<score<< "\n\n";
    cout <<setw(45)<< "HIGH SCORES\n";
    while(scoreFile>>highscores[sizes])
    {
        sizes++;
    }
    for(int i = 0; i<sizes; i++)
    {
        scoreFile >> highscores[i];
    }
    for (startscan = 0; startscan<(sizes-1); startscan++)
    {
        minIndex = startscan;
        minvalue = highscores[startscan];
        for(int index = startscan + 1; index<sizes; index++)
        {
            if (highscores[index]>minvalue)
            {
                minvalue = highscores[index];
                minIndex = index;
            }
        }
        highscores[minIndex] = highscores[startscan];
        highscores[startscan] = minvalue;
    }


    if(score>=highscores[0])
    {
        cout<< setw(37)<< "1. "<<highscores[0];
        cout<< setw(15)<< " NEW HIGH SCORE!"<<endl;
    }
    else
    {
        cout<< setw(37)<< "1. "<<highscores[0]<<endl;
    }

    for(int i = 1; i<5; i++)
    {
        scoreFile << highscores[i];
        cout << setw(35) <<i+1<<". "<< highscores[i]<<endl;
    }

    scoreFile.close();
    system("pause>nul");
    exit(0);

}

void easterEgg()//EXTRA CREDIT EASTER EGG
{
    system("cls");
    score += 3000;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\tCongratulations on figuring out the secret message! Have a cookie.\n";
    for(int i = 0; i < 999999994; i++);
    cout << setw(45)<< "  *** \n";
    cout << setw(45)<< " *****\n";
    cout << setw(45)<< "  *** \n";
    system("pause>nul");
    exit(0);
}

void detectGameover(int& health, bool& gameRun, int& alienHealth, int& ammo, int& shotgunAmmo, int& playerGrenades)
{
    if (health <= 0)
    {
        gameRun=false;
        gameOverLOST(health, ammo, shotgunAmmo, playerGrenades);
        exit(0);
    }
    else if (alienHealth <= 0)
    {
        gameRun=false;
        gameOverWIN(health,ammo,shotgunAmmo, playerGrenades);
        exit(0);
    }

}

void menu()//MATRIX STYLE EXTRA CREDIT MENU
{
    system("cls");
    fstream inFile;
    inFile.open("MENU.txt");
    char ch;

    while(inFile)
    {
        inFile.get(ch);
        cout << ch;
        for(int i = 0; i < 7999994; i++);
    }
    cout << "\tPress Enter to begin...";
    system("pause>nul");
}



void PshieldReset(bool& shieldON)
{
    if (shieldON == true)
    {
        static int b = 0;
        b++;
        if (b==3)
        {
            shieldON = false;
            b = 0;
        }
    }
}
void AshieldReset(bool& AshieldON)
{
    if (AshieldON == true)
    {
        static int q = 0;
        q++;
        if (q==3)
        {
            AshieldON = false;
            q = 0;
        }
    }
}

void AMMOsteal(bool& alienAmmoSteal, int& ammo, int& alienAmmo)//EXTRA CREDIT ALIEN STEALS PLAYER AMMO
{

    for(int i = 0; i<5; i++)
    {
        ammo -=1;
        alienAmmo +=1;
        if(ammo<0 || alienAmmo>alienMaxammo)
        {
            alienAmmoSteal = false;
            break;
        }
    }
    alienAmmoSteal = false;
}

