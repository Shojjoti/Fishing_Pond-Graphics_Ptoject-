#include<iostream>
#include<GL/glut.h>
#include<math.h>
using namespace std;

int isNight = 0;
int isRaining = 0;
int isWinter = 0;
int isFoggy = 0;
float cloudPos1 = 0.0f, cloudPos2 = 0.0f;
float cloudSpeed = 1.0f;

float fishX = -50.0f;
float fishY = -40.0f;
float fishSpeed = 0.05f;

float human2PosY = -150.0f;
float human2Speed = 0.4f;

const int numRaindrops = 2000;
float raindropX[numRaindrops];
float raindropY[numRaindrops];
float raindropSpeed[numRaindrops];
float snowOffset[numRaindrops];
const float groundHeight = -200.0;
float riverStartX = 0.0f;
float riverEndX = 800.0f;



void initRaindrops()
{
    for (int i = 0; i < numRaindrops; i++)
    {
        raindropX[i] = -500 + rand() % 1000;
        raindropY[i] = -200 + rand() % 600;

        raindropSpeed[i] = 1.0f + (float)rand() / (RAND_MAX / 2.0f);

        snowOffset[i] = rand() % 360;
    }
}


void drawRaindrops()
{
    if (!isRaining) return;

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_LINES);

    float angle = 75.0 * M_PI / 180.0;
    float length = 8.0f;

    float dx = length * cos(angle);
    float dy = length * sin(angle);

    for (int i = 0; i < numRaindrops; i++)
    {
        glVertex2f(raindropX[i], raindropY[i]);
        glVertex2f(raindropX[i] + dx, raindropY[i] - dy);
    }

    glEnd();
}

// Function to update raindrop positions
void updateRaindrops()
{
    if (!isRaining) return;

    float angle = 75.0 * M_PI / 180.0;

    for (int i = 0; i < numRaindrops; i++)
    {
        // angle move
        raindropX[i] += cos(angle) * raindropSpeed[i];
        raindropY[i] -= sin(angle) * raindropSpeed[i];

        //  top + left side spawn
        if (raindropY[i] <= -200)
        {
            raindropX[i] = -600 + rand() % 1200;
            raindropY[i] = 284 + rand() % 100;
        }
    }
}

void drawSnow()
{
    if (!isWinter) return;

    glColor3f(1.0, 1.0, 1.0);
    glPointSize(5.0f);

    glBegin(GL_POINTS);
    for (int i = 0; i < numRaindrops; i++)
    {
        glVertex2f(raindropX[i], raindropY[i]);
    }
    glEnd();
}

void updateSnow()
{
    if (!isWinter) return;

    for (int i = 0; i < numRaindrops; i++)
    {
        raindropY[i] -= 0.2f;

// for each snowflake
        raindropX[i] += sin((raindropY[i] + snowOffset[i]) * 0.01f) * 0.5f;

        if (raindropY[i] < -200)
        {
            raindropY[i] = 284;
            raindropX[i] = -500 + rand() % 1000;

            snowOffset[i] = rand() % 360; // reset offset
        }
    }
}

void drawFog()
{
    if (!isWinter) return;

    glEnable(GL_BLEND);
    glColor4f(0.9, 0.9, 0.9, 0.3);

    glBegin(GL_QUADS);
    glVertex2f(-450, -200);
    glVertex2f(464, -200);
    glVertex2f(464, 284);
    glVertex2f(-450, 284);
    glEnd();

    glDisable(GL_BLEND);
}

void drawCircle(double cx, double cy, double radius, int segments)
{
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= segments; i++)
    {
        double angle = 2.0 * M_PI * i / segments;
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        glVertex2d(cx + x, cy + y);
    }
    glEnd();
}

//Sky Background
void drawskyBG()
{
    glBegin(GL_POLYGON);
    glVertex2f(-450.3682541657872, 149.68529349150);
    glVertex2f(463.9221307697697, 151.8346712374031);
    glVertex2f(464.7681989931592, 284.3201129533518);
    glVertex2f(-450.3682541657872, 284.3201129533518);

    glEnd();

}


//mountain color

void drawMountain1()
{


    if (isNight)
    {
        glColor3f(0.2f, 0.1f, 0.05f);  // Darker for night
    }
    else
    {
        glColor3f(0.55f, 0.35f, 0.15f);// Brown for day
    }
    glBegin(GL_TRIANGLES);
    glVertex2f(-450, 150);
    glVertex2f(-276.9886005311207, 249.7724127510133);
    glVertex2f(-101.0225, 150.700);

    glEnd();

    glColor3f(0.6f, 0.4f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-276.9886005311207, 249.7724127510133);
    glVertex2f(-222.81, 150.45);
    glVertex2f(-101.0225, 150.700);

    glEnd();

    if (isWinter)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    else
    {
        glColor3f(0.55f, 0.35f, 0.15f);  // Light brown for day
    }
    glBegin(GL_TRIANGLES);
    glVertex2f(-276.99,249.77);
    glVertex2f(-303.933,234.233);
    glVertex2f(-267.26,231.94);

    glEnd();

    if (isWinter)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    else
    {
        glColor3f(0.6f, 0.4f, 0.2f);
    }
    glBegin(GL_TRIANGLES);
    glVertex2f(-276.99,249.77);
    glVertex2f(-267.26,231.94);
    glVertex2f(-254.85,237.31);
    glEnd();


    //center mountain

    if (isNight)
    {
        glColor3f(0.2f, 0.1f, 0.05f); // Darker for night
    }
    else
    {
        glColor3f(0.5f, 0.26f, 0.13f);  // Light brown for day
    }
    glBegin(GL_TRIANGLES);
    glVertex2f(-222.81, 150.45);
    glVertex2f(-31.4440038606137, 250.6462369385878);
    glVertex2f(203.9794, 151.313);

    glEnd();

    glColor3f(0.6f, 0.4f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-31.4440038606137, 250.6462369385878);
    glVertex2f(100,150);
    glVertex2f(203.9794, 151.313);

    glEnd();

    if (isWinter)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    else
    {
        glColor3f(0.5f, 0.26f, 0.13f);  // Light brown for day
    }
    glBegin(GL_TRIANGLES);
    glVertex2f(-31.444,250.65);
    glVertex2f(-51.55,240.119);
    glVertex2f(-14.96,238.0222);

    glEnd();
    if (isWinter)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    else
    {
       glColor3f(0.6f, 0.4f, 0.2f);
    }
    glBegin(GL_TRIANGLES);
    glVertex2f(-31.444,250.65);
    glVertex2f(-14.96,238.0222);
    glVertex2f(-7.044,240.35);

    glEnd();

    //3rd mountain
   if (isNight)
    {
        glColor3f(0.2f, 0.1f, 0.05f);  // Darker for night
    }
    else
    {
        glColor3f(0.45f, 0.22f, 0.11f); // Light brown for day
    }
    glBegin(GL_TRIANGLES);
    glVertex2f(100,150);
    glVertex2f(300,250);
    glVertex2f(463.9721307697697, 151.8346712374031);

    glEnd();

    glColor3f(0.6f, 0.4f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(300,250);
    glVertex2f(406.8488,151.72000);
    glVertex2f(463.9721307697697, 151.8346712374031);
    glEnd();

    if (isWinter)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    else
    {
        glColor3f(0.5f, 0.26f, 0.13f);  // Light brown for day
    }
    glBegin(GL_TRIANGLES);
    glVertex2f(300.000,250);
    glVertex2f(280,240);
    glVertex2f(314.5084,236.655);

    glEnd();

    if (isWinter)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    else
    {
        glColor3f(0.6f, 0.4f, 0.2f);
    }
    glBegin(GL_TRIANGLES);
    glVertex2f(300.000,250);
    glVertex2f(314.5084,236.655);
    glVertex2f(319.130,238.55);

    glEnd();

}


void drawSun()
{

    if (isWinter || isNight)
    {
    glColor3f(1.0f, 0.9f, 0.9f); // soft winter
    }
    else
    {
        glColor3f(1.0f, 1.0f, 0.0f); //  for day
    }


    drawCircle(390.349, 237.877, 30.0, 100);
}


void drawCloud1(double cx, double cy, double radius)
{

    if (isNight || isRaining)
    {
        glColor3f(0.6, 0.6, 0.6); // Darker for night
    }
    else
    {
        glColor3f(1.0, 1.0, 1.0); // White for day
    }
    // Draw clouds
    drawCircle(cx, cy, radius * 0.7, 50);         // Center cloud
    drawCircle(cx + 30.0, cy, radius * 0.6, 50);  // Right cloud
    drawCircle(cx - 30.0, cy, radius * 0.6, 50);  // Left cloud
}


//GROUND BG
void drawGrounBG()
{
    glBegin(GL_QUADS);
    glVertex2f(-450, -200);
    glVertex2f(462.210381260016, -201.6652564378993);
    glVertex2f(463.9721307697697, 151.83467123740311);
    glVertex2f(-450.3682541657872, 149.6852934915035);

    glEnd();
}

//POND
void drawPond()
{
    if (isWinter)
    {
    glColor3f(0.8f, 0.9f, 1.0f); // frozen look
    }
    else if (isNight)
    {
        glColor3f(20.0/255, 60.0/255, 120.0/255); // night water
    }
    else
    {
        glColor3f(64.0/255, 164.0/255, 223.0/255); //for day
    }
    glBegin(GL_QUADS);
    glVertex2f(-50, -100);
    glVertex2f(380, -100);
    glVertex2f(319.696019506978, 26.0038256825806);
    glVertex2f(-20, 26);

    glEnd();

    //par
    if (isNight)
    {
        glColor3f(70.0/255, 50.0/255, 35.0/255);//for night water
    }
    else
    {
        glColor3f(139.0/255, 94.0/255, 60.0/255); //for day water
    }

    glBegin(GL_QUADS);
    glVertex2f(-50, -110);
    glVertex2f(380, -110);
    glVertex2f(380, -100);
    glVertex2f(-50, -100);

    glEnd();

}

void drawFish()
{
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_QUADS);
    glVertex2f(fishX+ 117.5577587811762, -33.1712359556068 +fishY);
    glVertex2f(fishX+ 124.7645901202613, -35.3332853576662 +fishY);
    glVertex2f(fishX+ 130.9048104211618, -32.6523440991125 +fishY);
    glVertex2f(fishX+ 124.5339715174106, -30.5479493477747 +fishY);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(fishX+ 130.9048104211618, -32.6523440991125 +fishY);
    glVertex2f(fishX+ 134, -34 +fishY);
    glVertex2f(fishX+ 134.0181615596465, -31.326287132516 +fishY);
    glEnd();


}

void updateFish()
{
    fishX -= fishSpeed;

    if(fishX < -120)
        fishX = 240;

    fishY = -45 + sin(fishX * 0.05f) * 15;
}

//Road
void drawRoad()
{
    //1

    glBegin(GL_POLYGON);
    glVertex2f(-201.2162733875239, -26.0903387104429);
    glVertex2f(-75.7213162292419, -28.0665935441005);
    glVertex2f(-97.9844401417428, 14.3788683890542);
    glVertex2f(-200, 13.1386237535039);

    glEnd();

    //2
    glBegin(GL_POLYGON);
    glVertex2f(-75.7213162292419, -28.0665935441005);
    glVertex2f(-30.2606064160686, 100.1939754495036);
    glVertex2f(-51.5984147860171, 125.4700535906349);
    glVertex2f(-97.9844401417428, 14.3788683890542);

    glEnd();

    //3

    glBegin(GL_POLYGON);
    glVertex2f(-30.2606064160686, 100.1939754495036);
    glVertex2f(350, 100);
    glVertex2f(376.6796005008279, 124.535201149219);
    glVertex2f(-51.5984147860171, 125.4700535906349);

    glEnd();

    //4
    glBegin(GL_POLYGON);
    glVertex2f(350, 100);
    glVertex2f(477.6878145512603, -131.8734800753629);
    glVertex2f(547.3407153649591, -175.4822527654572);
    glVertex2f(376.6796005008279, 124.535201149219);

    glEnd();

    //5
    glBegin(GL_POLYGON);
    glVertex2f(-108.6079070805696, -179.7219945547719);
    glVertex2f(547.3407153649591, -175.4822527654572);
    glVertex2f(477.6878145512603, -131.8734800753629);
    glVertex2f(-76.8596108536896, -131.6161977997722);

    glEnd();

    //6
    glBegin(GL_POLYGON);
    glVertex2f(-266.5844637748193, -108.46602765361);
    glVertex2f(-108.6079070805696, -179.7219945547719);
    glVertex2f(-76.8596108536896, -131.6161977997722);
    glVertex2f(-266.5931692675187, -39.6936545818417);

    glEnd();

}

//counter side tree
//big one
void drawBTree()
{
    if (isNight)
    {
        glColor3f(0.25f, 0.18f, 0.10f); //for night
    }
    else
    {
        glColor3f(0.55f, 0.35f, 0.20f); //for day
    }

    glBegin(GL_QUADS);
    glVertex2f(-450.1684960799848, -40.0031075846766);
    glVertex2f(-429.879668478891, -40.0031075846766);
    glVertex2f(-430, 70);
    glVertex2f(-450.1684960799848, 69.99997005640889);

    glEnd();

    //lower triangle part
    if (isNight)
    {
        glColor3f(0.10f, 0.35f, 0.18f);//for night
    }
    else
    {
        glColor3f(0.20f, 0.65f, 0.30f);//for day
    }

    glBegin(GL_TRIANGLES);
    glVertex2f(-450.1684960799848, 69.99997005640889);
    glVertex2f(-390, 70);
    glVertex2f(-450.1684960799848, 124.9604872685955);

    glEnd();

    //upper triangle part
    if (isNight)
    {
        glColor3f(0.10f, 0.35f, 0.18f);//for night
    }
    else
    {
        glColor3f(0.20f, 0.65f, 0.30f);//for day
    }

    glBegin(GL_TRIANGLES);
    glVertex2f(-450.1684960799848, 107.5076306038345);
    glVertex2f(-376.271176071052, 107.5076306038345);
    glVertex2f(-450.442199966587, 219.9024463643643951);

    glEnd();
}

//small one
void drawSTree()
{
    if (isNight)
    {
        glColor3f(0.25f, 0.18f, 0.10f); //for night
    }
    else
    {
        glColor3f(0.55f, 0.35f, 0.20f); //for day
    }

    glBegin(GL_QUADS);
    glVertex2f(-420, -40);
    glVertex2f(-410, -40);
    glVertex2f(-410, 10);
    glVertex2f(-420, 3.8770493356906);

    glEnd();

    //lower triangle part
    if (isNight)
    {
        glColor3f(0.10f, 0.35f, 0.18f);//for night
    }
    else
    {
        glColor3f(0.20f, 0.65f, 0.30f);//for day
    }

    glBegin(GL_TRIANGLES);
    glVertex2f(-445.8337854417734, 4.4632499069124805);
    glVertex2f(-380.4890388546914, 4.4632499069124805);
    glVertex2f(-416.9057721568507, 33.4442820594857);

    glEnd();

    //upper triangle part
    if (isNight)
    {
        glColor3f(0.10f, 0.35f, 0.18f);//for night
    }
    else
    {
        glColor3f(0.20f, 0.65f, 0.30f);//for day
    }

    glBegin(GL_TRIANGLES);
    glVertex2f(-442.7014150873259, 24.8872437013167);
    glVertex2f(-385.340514049237, 24.8872437013167);
    glVertex2f(-416.16014299271, 58.1646150941963);

    glEnd();
}


//counter Backgraound wall
void drawCounterBG()
{
    glColor3f(0.95f, 0.94f, 0.85f);
    glBegin(GL_POLYGON);
    glVertex2f(-368, 0);
    glVertex2f(-200, 0);
    glVertex2f(-200, 94);
    glVertex2f(-366.856499185106, 114.0545612285132);

    glEnd();
}

//Counter
void drawCounter()
{
    //left glass
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.45f, 0.65f, 0.85f, 0.40f);
    glBegin(GL_POLYGON);
    glVertex2f(-368, 0);
    glVertex2f(-342.6970877678052, -0.0054768784587);
    glVertex2f(-342.2329249033665, 93.6413749598924);
    glVertex2f(-366.856499185106, 114.0545612285132);

    glEnd();
    glDisable(GL_BLEND);

    //front glass
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.68f, 0.86f, 1.00f, 0.35f);

    glBegin(GL_POLYGON);
    glVertex2f(-342.6970877678052, -0.0054768784587);
    glVertex2f(-200, 0);
    glVertex2f(-200, 94);
    glVertex2f(-342.2329249033665, 93.6413749598924);

    glEnd();
    glDisable(GL_BLEND);

    //siling top left cap
    glColor3f(0.62f, 0.64f, 0.66f);
    glBegin(GL_POLYGON);
    glVertex2f(-351.6033038016722, 116.4689655145231);
    glVertex2f(-346.808366144744, 116.4541329854885);
    glVertex2f(-360.158865374604, 137.549790456419);
    glVertex2f(-369.8816219318672, 137.234178400308);

    glEnd();

    //siling left
    glColor3f(180.0/255, 180.0/255, 180.0/255);
    glBegin(GL_POLYGON);
    glVertex2f(-370.2651320375603, 118.0423266029338);
    glVertex2f(-349.3924351738878, 93.6233230238891);
    glVertex2f(-351.6033038016722, 116.4689655145231);
    glVertex2f(-369.8816219318672, 137.234178400308);

    glEnd();

    //front siling
    glColor3f(0.78f, 0.80f, 0.82f);
    glBegin(GL_POLYGON);
    glVertex2f(-349.3924351738878, 93.6233230238891);
    glVertex2f(-200, 94);
    glVertex2f(-200, 116);
    glVertex2f(-351.6033038016722, 116.4689655145231);

    glEnd();

    //siling top right
    glColor3f(0.62f, 0.64f, 0.66f);
    glBegin(GL_POLYGON);
    glVertex2f(-208.2825157121603, 115.9581320103581);
    glVertex2f(-200, 116);
    glVertex2f(-199.632101888375, 137.4298533316633);
    glVertex2f(-207.831450860561, 136.1999509856454);

    glEnd();


    //left middle
    glColor3f(180.0/255, 180.0/255, 180.0/255);

    glBegin(GL_POLYGON);
    glVertex2f(-373.5595153726596, -10.3851993442435);
    glVertex2f(-343.5309999090373, -10.0592658288248);
    glVertex2f(-342.6970877678052, -0.0054768784587);
    glVertex2f(-368, 0);

    glEnd();

    //front middle
     glColor3f(0.78f, 0.80f, 0.82f);

    glBegin(GL_POLYGON);
    glVertex2f(-343.5309999090373, -10.0592658288248);
    glVertex2f(-200, -10.0592658288248);
    glVertex2f(-200, 0);
    glVertex2f(-342.6970877678052, -0.0054768784587);

    glEnd();

    //left down
    glColor3f(180.0/255, 100.0/255, 40.0/255);

    glBegin(GL_POLYGON);
    glVertex2f(-369.3125070074132, -37.3176288666067);
    glVertex2f(-342.5377660428576, -39.2910260126577);
    glVertex2f(-343.5309999090373, -10.0592658288248);
    glVertex2f(-369.996238792399, -10.3465230645713);

    glEnd();

    //front down
   glColor3f(0.72f, 0.45f, 0.25f);

    glBegin(GL_POLYGON);
    glVertex2f(-342.5377660428576, -39.2910260126577);
    glVertex2f(-202.2044615823676, -39.8052244937269);
    glVertex2f(-199.9462466888555, -8.4638671488066);
    glVertex2f(-343.5309999090373, -10.0592658288248);

    glEnd();


}


//trush bin
void drawBin()
{
    glColor3f(0.10f, 0.30f, 0.55f);

    glBegin(GL_QUADS);
    glVertex2f(-185.7646891075231, 13.3992846874672);
    glVertex2f(-159.9385122061665, 13.6234828110275);
    glVertex2f(-159.9385122061665, 40.2128837110468);
    glVertex2f(-185.7646891075231, 40.2128837110468);

    glEnd();

    //top
    glColor3f(0.20f, 0.45f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(-188.9657955925715, 40.1202967523111);
    glVertex2f(-156.4761968582463, 40.2246106565286);
    glVertex2f(-156.4761968582463, 46.7817916676309);
    glVertex2f(-188.9657955925715, 46.7817916676309);

    glEnd();
}

//bin side lamp
void drawLamp()
{
    //khuti
    glColor3f(0.30f, 0.32f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(-140.0396545936459, 13.822664636735);
    glVertex2f(-134.9323643962649, 13.822664636735);
    glVertex2f(-134.9323643962649, 130);
    glVertex2f(-140.0396545936459, 130);

    glEnd();

    //upper
    glColor3f(0.60f, 0.62f, 0.65f);
    glBegin(GL_QUADS);
    glVertex2f(-140.0040027803395, 118.2729260061069);
    glVertex2f(-80.0141319126148, 118.9037499119727);
    glVertex2f(-80, 120);
    glVertex2f(-140.0040027803395, 120.00000011650488);

    glEnd();


    // up of light
    glColor3f(0.60f, 0.62f, 0.65f);
    glBegin(GL_QUADS);
    glVertex2f(-104.4678725182487, 110.0965653344021);
    glVertex2f(-80, 110);
    glVertex2f(-80.0141319126148, 118.9037499119727);
    glVertex2f(-104.4678725182487, 118.3782883736264);

    glEnd();

    //main light
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(0.90f, 0.95f, 1.00f);

    if (isNight)
    {
        glColor3f(1.0f, 1.0f, 0.0f); //  for day  Yellow sun
    }
    else
    {

        glColor3f(1.0f, 1.0f, 0.85f);  // Soft white moon
    }

    glBegin(GL_QUADS);
    glVertex2f(-102.8051206682303, 105.2548769506401);
    glVertex2f(-81.9951001553641, 105.2548769506401);
    glVertex2f(-81.9999686002108, 110.0907082212129);
    glVertex2f(-102.8925869790839, 110.0907082212129);

    glEnd();
    glDisable(GL_BLEND);
}

//road side lamp
void drawRLamp()
{

    //khuti
    glColor3f(0.30f, 0.32f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(412.145450028029, 60.4292603278633);
    glVertex2f(415.7248940939145, 55.894669997908);
    glVertex2f(416.5001662813021, 139.640179294295);
    glVertex2f(414.4407893207097, 139.6741833373146);

    glEnd();

    //upper
    glColor3f(0.60f, 0.62f, 0.65f);
    glBegin(GL_QUADS);
    glVertex2f(372.4312325966991, 133.6713161568834);
    glVertex2f(414.312921538154, 131.8516217890153);
    glVertex2f(414.312921538154, 136.0219949250622);
    glVertex2f(372.9094929869626, 137.4330652417699);

    glEnd();

    //top of light
    glColor3f(0.70f, 0.72f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(373.0171082222162, 127.1604579255518);
    glVertex2f(402.5194011254922, 123.910205317062);
    glVertex2f(403.6477840963544, 131.8516217890153);
    glVertex2f(372.4312325966991, 133.6713161568834);

    glEnd();

    //main light
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(0.90f, 0.95f, 1.00f);

    if (isNight)
    {
        glColor3f(1.0f, 1.0f, 0.0f); //  for day  Yellow sun
    }
    else
    {

        glColor3f(1.0f, 1.0f, 0.85f);  // Soft white moon
    }

    glBegin(GL_QUADS);
    glVertex2f(376.1999563435438, 121.6544627563615);
    glVertex2f(398.3555585370506, 118.6101815384631);
    glVertex2f(399.0950567453756, 124.2874635962856);
    glVertex2f(376.6286908772214, 126.7625717007864);

    glEnd();
}

void drawLampLight()
{
    if (!isNight) return;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_POLYGON);

    // center (bright)
    glColor4f(1.0f, 1.0f, 0.6f, 0.6f);
    glVertex2f(-102.8051206682303, 105.2548769506401);
    glVertex2f(-130.24753, 13.99);
    glVertex2f(-45.6922667054881, 13.9338706534045);
    glVertex2f(-81.9951001553641, 105.108327510386);

    glEnd();

    glBegin(GL_POLYGON);

    // center (bright)
    glColor4f(1.0f, 1.0f, 0.6f, 0.6f);
    glVertex2f(376.076604573024, 115.3003958652407);
    glVertex2f(343.5989441752837, 26.5011111368559);
    glVertex2f(435.1839411668615, 26.1347711488331);
    glVertex2f(400, 112);

    glEnd();

    glDisable(GL_BLEND);
}

//fishing bowl
void drawBowl()
{
    glColor4f(0.60f, 0.20f, 0.20f, 0.50f);
    glBegin(GL_QUADS);
    glVertex2f(50, 26.0007883453595);
    glVertex2f(72.1247329001451, 26.0007883453595);
    glVertex2f(74.5527953750396, 37.7929317853151);
    glVertex2f(47.1644405122199, 37.7929317853151);

    glEnd();

    //top
    glColor4f(1.00f, 0.80f, 0.80f, 0.60f);
    glLineWidth(2.0);
    glBegin(GL_QUADS);
    glVertex2f(45.9788697214894, 37.7667637024292);
    glVertex2f(76.0081370502205, 37.7667637024292);
    glVertex2f(75.9744810223978, 40);
    glVertex2f(46, 40);

    glEnd();
}


void drawBowl1()
{
    glColor4f(0.60f, 0.20f, 0.20f, 0.50f);
    glBegin(GL_QUADS);
    glVertex2f(50+150, 26.0007883453595);
    glVertex2f(150+72.1247329001451, 26.0007883453595);
    glVertex2f(150+74.5527953750396, 37.7929317853151);
    glVertex2f(150+47.1644405122199, 37.7929317853151);

    glEnd();

    //top
    glColor4f(1.00f, 0.80f, 0.80f, 0.60f);
    glLineWidth(2.0);
    glBegin(GL_QUADS);
    glVertex2f(150+45.9788697214894, 37.7667637024292);
    glVertex2f(150+76.0081370502205, 37.7667637024292);
    glVertex2f(150+75.9744810223978, 40);
    glVertex2f(150+46, 40);

    glEnd();
}

//fishing pole
void drawFishingPole()
{
    glBegin(GL_QUADS);
    glVertex2f(12.3686441311661, 35.5049867445017);
    glVertex2f(14.3641171094575, 36.8974793521441);
    glVertex2f(14.0109618791751, 37.4506740508105);
    glVertex2f(12, 36);

    glEnd();

    //hand middle
    glBegin(GL_QUADS);
    glVertex2f(18.1276158949878, 39.5914549353777);
    glVertex2f(22.5269712812556, 42.76979798494669);
    glVertex2f(22.6329876121409, 44.7953750698765);
    glVertex2f(17.6762375324694, 41.1422720953229);

    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(25.9747886184496, 44.9603492252361);
    glVertex2f(63.702494058721, 71.593579136901);
    glVertex2f(63.2816081815703, 73.2147396838915);
    glVertex2f(25.2275586642834, 46.2645063397297);

    glEnd();

    //pole cap
    glBegin(GL_POLYGON);
    glVertex2f(63.702494058721, 71.593579136901);
    glVertex2f(63.9084565112178, 71.9231772761773);
    glVertex2f(63.6845238562219, 72.2160122866018);
    glVertex2f(63.2816081815703, 72.2147396838915);

    glEnd();


}

void drawFishingPole1()
{
    glBegin(GL_QUADS);
    glVertex2f(150+12.3686441311661, 35.5049867445017);
    glVertex2f(150+14.3641171094575, 36.8974793521441);
    glVertex2f(150+14.0109618791751, 37.4506740508105);
    glVertex2f(150+12, 36);

    glEnd();

    //hand middle
    glBegin(GL_QUADS);
    glVertex2f(150+18.1276158949878, 39.5914549353777);
    glVertex2f(150+22.5269712812556, 42.76979798494669);
    glVertex2f(150+22.6329876121409, 44.7953750698765);
    glVertex2f(150+17.6762375324694, 41.1422720953229);

    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(150+25.9747886184496, 44.9603492252361);
    glVertex2f(150+63.702494058721, 71.593579136901);
    glVertex2f(150+63.2816081815703, 73.2147396838915);
    glVertex2f(150+25.2275586642834, 46.2645063397297);

    glEnd();

    //pole cap
    glBegin(GL_POLYGON);
    glVertex2f(150+63.702494058721, 71.593579136901);
    glVertex2f(150+63.9084565112178, 71.9231772761773);
    glVertex2f(150+63.6845238562219, 72.2160122866018);
    glVertex2f(150+63.2816081815703, 72.2147396838915);

    glEnd();


}

 //DDA Line

   /* x1 = 62.95, y1 = 71.06
   x2 = 62.95, y2 = 41.35
   dx = x2 - x1 = 0
   dy = y2 - y1 = -29.71
   m = max(|dx|, |dy|) = 29.71 ≈ 30
   */

void drawfishingRope(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float m = dy / dx;

    float x = x1;
    float y = y1;

    glPointSize(1);
    glBegin(GL_POINTS);

   if (fabs(m) < 1)
    {
        while (x <= x2 && y <= y2)
        {
            glVertex2i(x, y);

            x = x + 1;
            y = y + m;
        }
    }
    else
    {
        while (y <= y2)
        {
            glVertex2i(x, y);

            y = y + 1;
            x = x + (1/m);
        }
    }

    glEnd();
}



void drawGateRoad()
{
    if (isNight)
    {
       glColor3f(70.0/255, 40.0/255, 30.0/255); //for night
    }
    else
    {
        glColor3f(140.0/255, 75.0/255, 50.0/255);//for day
    }

    glBegin(GL_POLYGON);
    glVertex2f(-349.982697604776, -200.182571384608);
    glVertex2f(-264.8845356930136, -200.3552792399336);
    glVertex2f(-266.5931692675187, -39.6936545818417);
    glVertex2f(-338.5251758740029, -39.295196746656124);

    glEnd();


}

void drawGate()
{
    glBegin(GL_POLYGON);
    glVertex2f(-349.982697604776, -200.182571384608);
    glVertex2f(-330, -180);
    glVertex2f(-330, -160);
    glVertex2f(-345.6469090130005, -138.312673966703);

    glEnd();

    //right
    glBegin(GL_POLYGON);
    glVertex2f(-286.8044110892114, -177.0383397976886);
    glVertex2f(-264.8845356930136, -200.3552792399336);
    glVertex2f(-266.0730364154203, -137.2150013434717);
    glVertex2f(-288.4348855899107, -152.5812222834221);

    glEnd();

}


void drawHuman()
{
    //body
    glColor3f(0.8f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(10.0829809501763, 33.1326359277462);
    glVertex2f(30.096485696343, 33.1580242592085);
    glVertex2f(30, 50);
    glVertex2f(10, 50);

    glEnd();

    //neck
    glColor3f(0.8f, 0.6f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(15, 50);
    glVertex2f(25, 50);
    glVertex2f(25, 55.6369998767938);
    glVertex2f(15, 55.0686858245353);

    glEnd();

    //right sleeves
    glColor3f(0.8f, 0.3f, 0.3f);
    glBegin(GL_TRIANGLES);
    glVertex2f(6.6937934023573, 47.8357406702272);
    glVertex2f(10, 45.0001210101675);
    glVertex2f(10, 50);

    glEnd();

    //left sleeves
    glColor3f(0.8f, 0.3f, 0.3f);
    glBegin(GL_TRIANGLES);
    glVertex2f(30.0286434713072, 45.0001640950751);
    glVertex2f(34.0307827480343, 46.6847095397051);
    glVertex2f(30, 50);

    glEnd();

    //right arm
    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(7.4670358963019, 47.1774546935044);
    glVertex2f(5.0721262525478, 42.7323323013116);
    glVertex2f(8.4477891338854, 43.3963971305298);
    glVertex2f(9.3773622775688, 45.551132967009);

    glEnd();

    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(5.0721262525478, 42.7323323013116);
    glVertex2f(14.0923401813679, 37.8625235537117);
    glVertex2f(15, 40);
    glVertex2f(8.4477891338854, 43.3963971305298);

    glEnd();

    //left arm
    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(34, 38);
    glVertex2f(37.0267286865709, 39.123584111971);
    glVertex2f(33.2152493067376, 46.3414423397182);
    glVertex2f(30.0286434713072, 45.0001640950751);

    glEnd();

    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(25.4254684209703, 41.007549454539);
    glVertex2f(34,38);
    glVertex2f(31.7384049187757, 41.2389136194158);
    glVertex2f(27.0119655513088, 42.9576188442147);

    glEnd();

    //right hand
    drawCircle(24.7644279499959, 43.0567749148761, 2.255785474, 500);
    //head
    drawCircle(19.4896724155492, 65.2562230187891, 11.1208809, 300);
    //left hand
    drawCircle(16.1261701721976, 38.4116835786408, 2.32328331, 500);

    //right shoe
    glColor3f(28/255, 28/255, 31/255);
    glBegin(GL_POLYGON);
    glVertex2f(12.8600776094165, 26.3763111839903);
    glVertex2f(17.1163372502743, 26.9372136173683);
    glVertex2f(17.3615554301925, 27.4751848668295);
    glVertex2f(14.9852964510929, 28.4905910607104);
    glVertex2f(12.6291177839436, 28.3559668312068);

    glEnd();

    //left shoe
    glColor3f(28/255, 28/255, 31/255);
    glBegin(GL_POLYGON);
    glVertex2f(22.6255394522634, 26.4849892581208);
    glVertex2f(22.6255394522634, 26.0004801727);
    glVertex2f(27.0695860402455, 26.1586021617636);
    glVertex2f(27.1658520467707, 27.7229247680405);
    glVertex2f(24.5503209941446, 27.670216442222);
    glVertex2f(23.233845342973, 27.3242507268372);

    glEnd();

    //right leg
    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(19.4032079423204, 27.3174034493224);
    glVertex2f(22.2626219156812, 25.9842827724091);
    glVertex2f(23.233845342973, 27.3242507268372);
    glVertex2f(20.2390327255815, 29.0159104915657);

    glEnd();

    //right pant
    glColor3f(0.1f, 0.1f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(19.1126371588891, 26.7269249999966);
    glVertex2f(20.5815636950689, 29.7119789445624);
    glVertex2f(7.1172487061047, 37.239263469706);
    glVertex2f(5.6125575119151, 37.2878018953325);
    glVertex2f(4.1060408410472, 36.5758227062552);
    glVertex2f(3.4256181905815, 35.3322916552121);
    glVertex2f(3.9829852404772, 33.8522717056164);
    glVertex2f(4.9057105855657, 32.7977284539238);

    glEnd();

    //left pant
    glColor3f(0.1f, 0.1f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(20.5815636950689, 29.7119789445624);
    glVertex2f(22, 27);
    glVertex2f(38.3966101898888, 31.3089782702647);
    glVertex2f(38.6171036473787, 32.5216922866468);
    glVertex2f(38.1761167323988, 33.6241595742669);
    glVertex2f(36.8543151615978, 35.2375387968683);
    glVertex2f(34.7399813416332, 35.7661222519411);

    glEnd();

    //hair
    glColor3f(28/255, 28/255, 31/255);
    glBegin(GL_POLYGON);
    glVertex2f(4.7849864806396, 67.5128105961969);
    glVertex2f(6.6565414300017, 68.5712138127066);
    glVertex2f(14.8033217643065, 71.3043506817469);
    glVertex2f(16.85484282853, 71.3043506817469);
    glVertex2f(16.85484282853, 74.4304780181892);
    glVertex2f(20.860193477728, 72.8674143499681);
    glVertex2f(23.9863208136875, 74.2350950596616);
    glVertex2f(30.4180257341926, 67.3165835905539);
    glVertex2f(33.2778334774662, 71.1603729539829);
    glVertex2f(33.7060508982795, 75.0143297418978);
    glVertex2f(32.4213986358396, 77.1554168462949);
    glVertex2f(32.7782464865174, 79.3678735208386);
    glVertex2f(30.9224158403476, 82.7342537556141);
    glVertex2f(29.0662777346217, 83.6134770689885);
    glVertex2f(26.9170651911495, 84.5903918616267);
    glVertex2f(24.9632356061749, 87.9119021565967);
    glVertex2f(23.4978634174439, 85.567306654265);
    glVertex2f(20.9578849569768, 86.0557640505841);
    glVertex2f(18.2225235380122, 86.5442214469032);
    glVertex2f(15.4383163794233, 87.2769075413819);
    glVertex2f(13.611485717472, 85.9873800150994);
    glVertex2f(10.9249700381318, 83.9456280984855);
    glVertex2f(8.4533756131389, 80.9367305371598);
    glVertex2f(3.9400292718474, 81.581494300301);
    glVertex2f(7.2713087142292, 78.0352936030243);
    glVertex2f(6.7340055783611, 75.6711598048398);
    glVertex2f(5.9817811881459, 73.5219472610357);
    glVertex2f(5.4444780522779, 71.8025772259924);
    glVertex2f(4.5413890955794, 70.1906678181394);

    glEnd();

    //ear
  /*  glColor3f();
    glBegin(GL_POLYGON);
    glVertex2f();
    glVertex2f();
    glVertex2f();
    glVertex2f();
    glVertex2f();
    glVertex2f();
    glVertex2f();
    glVertex2f();

    glEnd();
    */
}


//Beizer Curve
//counter human smile
struct Point {
    float x, y;
};

//b(t)= nCi * t^i(1-t)^n-i
Point bezier(Point p0, Point p1, Point p2, Point p3, float t)
{
    Point p;
    float u = 1 - t;

    float b0 = u * u * u;        // (1 - t)^3
    float b1 = 3 * t * u * u;    // 3t(1 - t)^2
    float b2 = 3 * t * t * u;    // 3t^2(1 - t)
    float b3 = t * t * t;        // t^3

    p.x = b0 * p0.x + b1 * p1.x + b2 * p2.x + b3 * p3.x;
    p.y = b0 * p0.y + b1 * p1.y + b2 * p2.y + b3 * p3.y;

    return p;
}



void drawBezierCurve(Point p0, Point p1, Point p2, Point p3)
{
    glBegin(GL_LINE_STRIP);

    for (float t = 0; t <= 1; t += 0.001)
    {
        Point p = bezier(p0, p1, p2, p3, t);
        glVertex2f(p.x, p.y);
    }

    glEnd();
}



void drawCounterHuman()
{
    //body
    glColor3f(0.65f, 0.5f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-310,0);
    glVertex2f(-273.3799781756772, 0);
    glVertex2f(-273.5229146095074, 40.0048485417322);
    glVertex2f(-310, 40);

    glEnd();

    //neck
    glColor3f(0.8f, 0.6f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(-300, 40);
    glVertex2f(-286.544291205579, 40.0031177376627);
    glVertex2f(-288.12316117403, 46.3200231726795);
    //glVertex2f(-291.6159398841482, 44.9188297726934);
   // glVertex2f(-295.7474566589726, 44.7847720149645);
    glVertex2f(-299.0471264751023, 45.81634350643);

    glEnd();

    //left sleeves
    glColor3f(0.65f, 0.5f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-325.5517765237087, 29.427552436662);
    glVertex2f(-317.2614633615557, 25.8541415903545);
    glVertex2f(-310, 31.2857260767419);
    glVertex2f(-310, 40);

    glEnd();

    //right sleeves
    glColor3f(0.65f, 0.5f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-273.5124772533728, 29.520950362007);
    glVertex2f(-259.801016961806, 21.280175707081);
    glVertex2f(-257.0852247190317, 30.5710439074804);
    glVertex2f(-273.5229146095074, 40.0048485417322);

    glEnd();

    //left hand
    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(-325.5517765237087, 29.427552436662);
    glVertex2f(-289.7651374486935, -26.353909461594178);
    glVertex2f(-287.41150390058885, -17.901185560328436);
    glVertex2f(-317.2614633615557, 25.8541415903545);

    glEnd();

    //rignt hand
    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(-259.3863073844072, 22.6989189984014);
    glVertex2f(-250, 15);
    glVertex2f(-244.4383998458175, 17.8507280835376);
    glVertex2f(-257.4929639999034, 29.1761463674409);

    glEnd();

    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(-250, 15);
    glVertex2f(-256.3459786273864, 0);
    glVertex2f(-250, 0);
    glVertex2f(-244.4383998458175, 17.8507280835376);

    glEnd();

    //hair
    glColor3f(0.0, 0.0 ,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-305.4132559300641, 55.9361257980948);
    glVertex2f(-313.1044859923751, 61.3901570557295);
    glVertex2f(-308.640475288488, 73.0461850065684);
    glVertex2f(-295.7444443661475, 77.0141945217476);
    glVertex2f(-286.3204217690525, 76.7661939270489);
    glVertex2f(-279.6396387477102, 72.6832358128873);
    glVertex2f(-277.6404009559388, 64.6141647868126);
    glVertex2f(-280, 60);
    glVertex2f(-283.017799174297, 58.7969009998901);

    glEnd();

    //head
    glColor3f(1.0f, 0.8f, 0.6f);
    drawCircle(-294.0442681298111, 56.0258163091665, 11.36934158, 300 );
    //eyes
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-298.5113372450116, 58.9786518786618, 3.40171402, 300);
    drawCircle(-290, 60, 3.678578553, 300);

    //mouth
    /*
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-296.9610873182411, 49.8432505230676);
    glVertex2f(-290, 50);

    glEnd();
    */

    //smile
    Point p0 = {-297.9165865874643, 49.730045677442};
    Point p1 = {-296.2231963640764, 48.7800950641752};
    Point p2 = {-294.0341797338432, 48.9040016659057};
    Point p3 = {-292.5059983127371, 49.3170236716738};

    glColor3f(0, 0, 0);
    drawBezierCurve(p0, p1, p2, p3);


}

//Birds
void drawBird()
{
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_QUADS);
    glVertex2f(60.002639011723, 271.9102654513228);
    glVertex2f(73.5681100826984, 264.261648782464);
    glVertex2f(79.9179050520911, 277.8271198555343);
    glVertex2f(72.1249748623818, 269.1683085322979);

    glEnd();

    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_QUADS);
    glVertex2f(50, 250);
    glVertex2f(68.2285097675272, 232.6569874526513);
    glVertex2f(71.1147802081603, 257.4789132459289);
    glVertex2f(65.0536122828308, 242.3259934302652);

    glEnd();

    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_QUADS);
    glVertex2f(71.1147802081603, 257.4789132459289);
    glVertex2f(92.4731814688448, 251.1291182755555);
    glVertex2f(94.3492572552563, 279.2702550760737);
    glVertex2f(88.7210298960219, 258.7777349444143);

    glEnd();

}

//Brasalham Midpoint Line
void BresalhamMidLine(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float x = x1;
    float y = y1;

    glPointSize(2);
    glBegin(GL_POINTS);

    float d = 2*dy - dx;

    while (x <= x2)
    {
        glVertex2i(x, y);

        //d<0 , East direction
        if (d < 0)
        {
            x = x + 1;
            d = 2*dy +d ;
        }
        //NE direction
        else
        {
            x = x + 1;
            y = y + 1;
            d = d + 2*(dy - dx);
        }
    }

    glEnd();
}

//Ticket price list
void drawList()
{
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex2f(-240, 50);
    glVertex2f(-220, 50);
    glVertex2f(-220, 80);
    glVertex2f(-240, 80);

    glEnd();

    //1
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    BresalhamMidLine(-237.6407955146785, 75.969235672092,-222.8512080597141, 76.0500530898911);
   // glVertex2f(-237.6407955146785, 75.969235672092);
   // glVertex2f(-222.8512080597141, 76.0500530898911);

    glEnd();

    //2
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-237.8024303502519, 72.4940867067276);
    glVertex2f(-223.2552951486476, 72.3324518711292);

    glEnd();

    //3
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-237.5599780968918, 68.6148506523673);
    glVertex2f(-223.0128428952875, 68.6148506523673);

    glEnd();

    //4
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-237.7216129324652, 63.9274404200153);
    glVertex2f(-230.0439582427296, 63.9274404200153);

    glEnd();
}


//xc = circle center x
//yc = circle center y

void drawCirclePoints(float xc, float yc, int x, int y)
{
    glVertex2f(xc + x, yc + y);
    glVertex2f(xc - x, yc + y);
    glVertex2f(xc + x, yc - y);
    glVertex2f(xc - x, yc - y);
    glVertex2f(xc + y, yc + x);
    glVertex2f(xc - y, yc + x);
    glVertex2f(xc + y, yc - x);
    glVertex2f(xc - y, yc - x);
}

void BresalhamMidCircle(float xc, float yc, float r)
{
    int x = 0;
    int y = r;

    //d start  1 - r
    int d = 1 - r;

    glPointSize(4);
    glBegin(GL_POINTS);

    while (x <= y)
    {
        drawCirclePoints(xc, yc, x, y);

        // East move
        if (d < 0)
        {
            d = d + (2*x) + 3;
        }
        else
        {
            // South-East move
            d = d + (2 * (x - y)) + 5;
            y = y - 1;
        }

        x = x + 1;
    }

    glEnd();
}

//another human
void drawHuman1()
{
    //body
    glColor3f(0.5f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(150+10.0829809501763, 33.1326359277462);
    glVertex2f(150+30.096485696343, 33.1580242592085);
    glVertex2f(150+30, 50);
    glVertex2f(150+10, 50);

    glEnd();

    //neck
    glColor3f(0.8f, 0.6f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(150+15, 50);
    glVertex2f(150+25, 50);
    glVertex2f(150+25, 55.6369998767938);
    glVertex2f(150+15, 55.0686858245353);

    glEnd();

    //right sleeves
    glColor3f(0.5f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(150+6.6937934023573, 47.8357406702272);
    glVertex2f(150+10, 45.0001210101675);
    glVertex2f(150+10, 50);

    glEnd();

    //left sleeves
    glColor3f(0.5f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(150+30.0286434713072, 45.0001640950751);
    glVertex2f(150+34.0307827480343, 46.6847095397051);
    glVertex2f(150+30, 50);

    glEnd();

    //right arm
    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(150+7.4670358963019, 47.1774546935044);
    glVertex2f(150+5.0721262525478, 42.7323323013116);
    glVertex2f(150+8.4477891338854, 43.3963971305298);
    glVertex2f(150+9.3773622775688, 45.551132967009);

    glEnd();

    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(150+5.0721262525478, 42.7323323013116);
    glVertex2f(150+14.0923401813679, 37.8625235537117);
    glVertex2f(150+15, 40);
    glVertex2f(150+8.4477891338854, 43.3963971305298);

    glEnd();

    //left arm
    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(150+34, 38);
    glVertex2f(150+37.0267286865709, 39.123584111971);
    glVertex2f(150+33.2152493067376, 46.3414423397182);
    glVertex2f(150+30.0286434713072, 45.0001640950751);

    glEnd();

    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(150+25.4254684209703, 41.007549454539);
    glVertex2f(150+34,38);
    glVertex2f(150+31.7384049187757, 41.2389136194158);
    glVertex2f(150+27.0119655513088, 42.9576188442147);

    glEnd();

    //right hand
    drawCircle(150+24.7644279499959, 43.0567749148761, 2.255785474, 500);
    //head
    drawCircle(150+19.4896724155492, 65.2562230187891, 11.1208809, 300);
    //left hand
    drawCircle(150+16.1261701721976, 38.4116835786408, 2.32328331, 500);

    //right shoe
    glColor3f(28/255, 28/255, 31/255);
    glBegin(GL_POLYGON);
    glVertex2f(150+12.8600776094165, 26.3763111839903);
    glVertex2f(150+17.1163372502743, 26.9372136173683);
    glVertex2f(150+17.3615554301925, 27.4751848668295);
    glVertex2f(150+14.9852964510929, 28.4905910607104);
    glVertex2f(150+12.6291177839436, 28.3559668312068);

    glEnd();

    //left shoe
    glColor3f(28/255, 28/255, 31/255);
    glBegin(GL_POLYGON);
    glVertex2f(150+22.6255394522634, 26.4849892581208);
    glVertex2f(150+22.6255394522634, 26.0004801727);
    glVertex2f(150+27.0695860402455, 26.1586021617636);
    glVertex2f(150+27.1658520467707, 27.7229247680405);
    glVertex2f(150+24.5503209941446, 27.670216442222);
    glVertex2f(150+23.233845342973, 27.3242507268372);

    glEnd();

    //right leg
    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(150+19.4032079423204, 27.3174034493224);
    glVertex2f(150+22.2626219156812, 25.9842827724091);
    glVertex2f(150+23.233845342973, 27.3242507268372);
    glVertex2f(150+20.2390327255815, 29.0159104915657);

    glEnd();

    //right pant
    glColor3f(0.1f, 0.1f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(150+19.1126371588891, 26.7269249999966);
    glVertex2f(150+20.5815636950689, 29.7119789445624);
    glVertex2f(150+7.1172487061047, 37.239263469706);
    glVertex2f(150+5.6125575119151, 37.2878018953325);
    glVertex2f(150+4.1060408410472, 36.5758227062552);
    glVertex2f(150+3.4256181905815, 35.3322916552121);
    glVertex2f(150+3.9829852404772, 33.8522717056164);
    glVertex2f(150+4.9057105855657, 32.7977284539238);

    glEnd();

    //left pant
    glColor3f(0.1f, 0.1f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(150+20.5815636950689, 29.7119789445624);
    glVertex2f(150+22, 27);
    glVertex2f(150+38.3966101898888, 31.3089782702647);
    glVertex2f(150+38.6171036473787, 32.5216922866468);
    glVertex2f(150+38.1761167323988, 33.6241595742669);
    glVertex2f(150+36.8543151615978, 35.2375387968683);
    glVertex2f(150+34.7399813416332, 35.7661222519411);

    glEnd();

    //hair
    glColor3f(28/255, 28/255, 31/255);
    glBegin(GL_POLYGON);
    glVertex2f(150+4.7849864806396, 67.5128105961969);
    glVertex2f(150+6.6565414300017, 68.5712138127066);
    glVertex2f(150+14.8033217643065, 71.3043506817469);
    glVertex2f(150+16.85484282853, 71.3043506817469);
    glVertex2f(150+16.85484282853, 74.4304780181892);
    glVertex2f(150+20.860193477728, 72.8674143499681);
    glVertex2f(150+23.9863208136875, 74.2350950596616);
    glVertex2f(150+30.4180257341926, 67.3165835905539);
    glVertex2f(150+33.2778334774662, 71.1603729539829);
    glVertex2f(150+33.7060508982795, 75.0143297418978);
    glVertex2f(150+32.4213986358396, 77.1554168462949);
    glVertex2f(150+32.7782464865174, 79.3678735208386);
    glVertex2f(150+30.9224158403476, 82.7342537556141);
    glVertex2f(150+29.0662777346217, 83.6134770689885);
    glVertex2f(150+26.9170651911495, 84.5903918616267);
    glVertex2f(150+24.9632356061749, 87.9119021565967);
    glVertex2f(150+23.4978634174439, 85.567306654265);
    glVertex2f(150+20.9578849569768, 86.0557640505841);
    glVertex2f(150+18.2225235380122, 86.5442214469032);
    glVertex2f(150+15.4383163794233, 87.2769075413819);
    glVertex2f(150+13.611485717472, 85.9873800150994);
    glVertex2f(150+10.9249700381318, 83.9456280984855);
    glVertex2f(150+8.4533756131389, 80.9367305371598);
    glVertex2f(150+3.9400292718474, 81.581494300301);
    glVertex2f(150+7.2713087142292, 78.0352936030243);
    glVertex2f(150+6.7340055783611, 75.6711598048398);
    glVertex2f(150+5.9817811881459, 73.5219472610357);
    glVertex2f(150+5.4444780522779, 71.8025772259924);
    glVertex2f(150+4.5413890955794, 70.1906678181394);

    glEnd();


}

void drawHuman2()
{
    //head
    glColor3f(1.0f, 0.8f, 0.6f);
    drawCircle(-354.4956687868789, -64.5764911887998, 11.22, 300 );
    //body
    glColor3f(0.8f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-357.1401195524953, -82.18543373557327);
    glVertex2f(-334.7902480195905, -97.9746445813787);
    glVertex2f(-318.4378680449833, -78.3898173994641);
    glVertex2f(-340.0035,-59.999);

    glEnd();

    //left hand
    glColor3f(0.8f, 0.6f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(-357.1401195524953, -82.18543373557327);
    glVertex2f(-356.662053038194, -95.4474667748068);
    glVertex2f(-340, -100);
    glVertex2f(-339.5476174528052, -97.9388086642038);
    glVertex2f(-352.662053038194, -95.4474667748068);
    glVertex2f(-351.216,-83.37);


    glEnd();

    //right hand
    glColor3f(0.8f, 0.6f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(-340.0035,-59.999);
    glVertex2f(-328.1741001334012, -59.9187650477531);
    glVertex2f(-326.53,-59.918);
    glVertex2f(-329.274,-69.149);
    glVertex2f(-330.2321651721505, -64.2515335510523);
    glVertex2f(-334.165,-64.98);

    glEnd();

    //legs
    glColor3f(0.8f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-334.7902480195905, -97.9746445813787);
    glVertex2f(-313.8925192220647, -110.2017430297793);
    glVertex2f(-313.8925192220647, -110.2017430297793);
    glVertex2f(-326.50,-88.05);
    glVertex2f(-302.8725043538822, -96.9198648507577);
    glVertex2f(-302.8725043538822, -96.9198648507577);
    glVertex2f(-320.823,-81.25);

    glEnd();


}

void updateHuman2()
{
    human2PosY += human2Speed;

    if(human2PosY > 50)
        human2PosY = -80;
}


void drawText(float x, float y, char *string) {
    glRasterPos2f(x, y);

    while (*string) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string);
        string++;
    }
}


//bresalham midpoint circle function use for winter pool water
void drawWinterPoolCircle()
{
    if(isWinter)
    {
        glColor3f(64.0/255, 164.0/255, 223.0/255);
        BresalhamMidCircle(20.7832780781832, -6.9705560047497, 18.9091309 );

        drawCircle(19.7832780781832, -5.9705560047497, 18, 500 );
    }

}



void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //sky
    if (isNight)
    {
    glColor3f(0.0f, 0.0f, 0.0f);
    }
    else if (isWinter || isRaining)
    {
    glColor3f(0.75f, 0.80f, 0.85f);
    }
    else
    {
    glColor3f(0.082, 0.396, 0.753);
    }
    drawskyBG();

    drawSun();

    drawCloud1(-100 + cloudPos1, 250, 30);
    drawCloud1(350 + cloudPos2, 250, 30);

    drawMountain1();

    drawCloud1(-300 + cloudPos1, 250, 30);
    drawCloud1(200 + cloudPos2, 250, 30);


    drawBird();

    //Ground BG
    if (isWinter)
    {
    glColor3f(1.0f, 1.0f, 1.0f); // snow
    }
    else if (isNight)
    {
    glColor3f(50.0/255, 100.0/255, 70.0/255);
    }
    else
    {
    glColor3f(102.0/255, 187.0/255, 106.0/255);
    }
    drawGrounBG();

    //road
    if (isNight)
    {
        glColor3f(0.35f, 0.18f, 0.12f); //for night
    }
    else
    {
        glColor3f(176.0/255, 96.0/255, 66.0/255);//for day
    }
    drawRoad();

    drawGateRoad();

    //Counter side trees
    if (isWinter)
    {
    glColor3f(0.9f, 0.9f, 0.9f); // snow leaves
    }
    else if (isNight)
    {
    glColor3f(0.10f, 0.35f, 0.18f);
    }
    else
    {
    glColor3f(0.20f, 0.65f, 0.30f);
    }
    drawBTree();

    if (isWinter)
    {
    glColor3f(0.9f, 0.9f, 0.9f); // snow leaves
    }
    else if (isNight)
    {
    glColor3f(0.10f, 0.35f, 0.18f);
    }
    else
    {
    glColor3f(0.20f, 0.65f, 0.30f);
    }
    drawSTree();

    drawCounterBG();

    drawCounterHuman();

    drawList();

    //COUNTER
    drawCounter();



    //pond
    if (isNight)
    {
        glColor3f(0.0, 0.2, 0.6); //for night water
    }
    else
    {
        glColor3f(0.0, 0.4, 0.9); //for day water
    }
    drawPond();

    drawFish();
    updateFish();

    //winter pond water
    if (isWinter)
    {
    glColor3f(1.0f, 1.0f, 1.0f); // snow
    }
    else if (isNight)
    {
    glColor3f(50.0/255, 100.0/255, 70.0/255);
    }
    else
    {
    glColor3f(102.0/255, 187.0/255, 106.0/255);
    }
    drawWinterPoolCircle();

    drawBin();
    drawLamp();
    drawRLamp();

    drawLampLight();
    drawBowl();
    drawBowl1();

    drawHuman();

    drawHuman1();

    glColor3f(0.93f, 0.51f, 0.93f);
    drawFishingPole();

    glColor3f(0.93f, 0.51f, 0.93f);
    drawFishingPole1();

    if (isNight)
    {
        glColor3f(0.35f, 0.25f, 0.05f); //for night
    }
    else
    {
        glColor3f(0.7f, 0.5f, 0.1f); //for day
    }
    drawGate();

    //DDA Rope
    glColor3f(0.85f, 0.75f, 0.50f);
    drawfishingRope( 62.9539, 41.3527, 62.9539, 71.0651);

    glColor3f(0.85f, 0.75f, 0.50f);
    drawfishingRope( 150+62.9539, 41.3527, 150+62.9539, 71.0651);


    // Draw rain effect
    drawRaindrops();
    updateRaindrops();

    drawSnow();
    updateSnow();

    drawFog();

    glColor3f(0.5f, 0.0f, 0.0f);
    drawText(-308.2617543124225, 105.6085316375694, "Ticket Counter");

    glTranslatef(0.0f, human2PosY, 0.0f);
    drawHuman2();

    glFlush();


}

//Keyboard function
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
        isWinter = !isWinter;
        if(isWinter)
            {
                isRaining = 0;
                isFoggy = 0;
            }

        glutPostRedisplay();
        break;

        case 'W':
        isWinter = !isWinter;
        if(isWinter)
            {
                isRaining = 0;
                isFoggy = 0;
            }

        glutPostRedisplay();
        break;

        case 'R':
        isWinter = !isWinter;
        if(isWinter)
            {
                isRaining = 0;
                isFoggy = 0;
            }

        glutPostRedisplay();
        break;

        case 'r':
        isRaining = !isRaining;
        if(isRaining)
            {
                isWinter = 0;
            }

        isFoggy = !isFoggy;
        glutPostRedisplay();
        break;

    }
}


//mouse function
void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON) isNight = false;
        if (button == GLUT_RIGHT_BUTTON) isNight = true;
        glutPostRedisplay();
    }
}

void timer(int value)
{
    cloudPos1 += cloudSpeed;
    cloudPos2 += cloudSpeed;

    if (cloudPos1 > 715) cloudPos1 = -800.0f;
    if (cloudPos2 > 715) cloudPos2 = -800.0f;

    updateRaindrops();
    updateHuman2();

    glutPostRedisplay();
    glutTimerFunc(25, timer, 0);
}


void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-450, 464, -200, 284);
}

int main(int argc, char** argv) {

    cout << "Press 'r' for Rainy season\n";
    cout << "Press 'w' for Winter season\n";
    cout << "Click Mouse Right for night\n";
    cout << "Click Mouse Left for day\n";

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1900, 1200);
    glutCreateWindow("Fishing pond ");

    initRaindrops();
    init();

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutTimerFunc(25, timer, 0);

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}
