
#include <iostream>
#include <conio.h>										//Konsole input / output benötigt um Spiel darzustellen
#include <windows.h>									//Library nötig um die Spielgechwindigkeit langsamer zu machen
using namespace std;
bool gameOver;
const int width = 20;									//Spielfeld Breite
const int height = 20;									//Spielfeld Höhe
int x, y, fruitX, fruitY, score;						//Variablen für die Position des Spielers, der Frucht und der Punktzahl
int tailX[100], tailY[100];								//Maximallänge des Schlangenschwanzes 100 Einheiten in beide Richtungen
int nTail;												//nTail gibt Anzahl der Längeneinheiten des Schlangenschwanzes an
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};		//Bewegungsrichtungen der Schlange
eDirection dir;											//stellt die gewählte Bewegungsrichtung fest, um die Taste nur ein einziges Mal drücken zu müssen
void Setup()
{
	gameOver = false;
	dir = STOP;											//Schlange bewegt sich erst, wenn wir eine Richtung auswählen
	x = width / 2;										//Zentrale Ausrichtung der Startpostition der Schlange auf dem Spielfeld
	y = height / 2;										//Zentrale Ausrichtung der Startpostition der Schlange auf dem Spielfeld
	fruitX = rand() % width;							//Frucht wird zufällig auf dem Spielfeld platziert
	fruitY = rand() % height;							//Frucht wird zufällig auf dem Spielfeld platziert
	score = 0;											//Anfangspunktzahl = 0
}
void Draw()
{
	system("cls"); //sytem("clear");					//Konsolenfenster wird freigemacht
	for (int i = 0; i < width + 2; i++)					//Oberer Rand des Spielfeldes
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)					//Unterer Rand des Spielfeldes
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)									//Ausfüllen des rechten und linken Spielfeldrandes bzw. erstellen der freien Mittelfläche
				cout << "#";
			if (i == y && j == x)						//Schlangenkopf in O-Form wird erstellt, wenn die Höhe der Y Koordinate und die Breite der X Koordinate entspricht
				cout << "0";
			else if (i == fruitY && j == fruitX)		//Frucht in Form eines F wird erstellt, wenn die Höhe der Y Koordinate der Frucht entspricht und die Breite der X Koordinate der Frucht entspricht
				cout << "F";
			else
			{
				bool print = false;						//Kontrolle ob neue Einheit des Schlangenschwanzes erstellt wurde oder nicht
				for (int k = 0; k < nTail; k++)			//Erstellung der jeweiligen Anzahl an Einheiten des Schlangenschwanzes
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)			//Erstellung der Punktzahlanzeige
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;
}
void Input()
{
	if (_kbhit())					//Kontrolle ob Taste betätigt wurde
	{
		switch (_getch())			//legt für das Betätigen der Taste a die Bewegungsrichtung links fest
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':					//legt für das Betätigen der Taste d die Bewegungsrichtung rechts fest
			dir = RIGHT;
			break;
		case 'w':					//legt für das Betätigen der Taste w die Bewegungsrichtung oben fest
			dir = UP;
			break;
		case 's':					//legt für das Betätigen der Taste s die Bewegungsrichtung unten fest
			dir = DOWN;
			break;
		case 'x':					//legt für das Betätigen der Taste x die Beendigung des Spiels fest
			gameOver = true;
			break;
		}
	}
}
void Logic()
{
	int prevX = tailX[0];			//Merken der vorherigen Koordinaten des Schlangenschwanzes für die gleichmäßige Bewegung der einzelnen Teile des Schlangenschwanzes
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;					//Festlegung, dass der Schlangenschwanz hinter die Position des Kopfes addiert wird und ihm "folgt"
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)		//Logik für Steuerung der Schlange
	{
	case LEFT:			//X Koordinate nimmt bei Bewegung nach links ab
		x--;
		break;
	case RIGHT:			//X Koordinate nimmt bei Bewegung nach rechts zu
		x++;
		break;
	case UP:			//Y Koordinate nimmt bei Bewegung nach oben ab
		y--;
		break;
	case DOWN:			//Y Koordinate nimmt bei Bewegung nach unten zu
		y++;
		break;
	default:
		break;
	}
	//if (x > width || x < 0 || y > height || y < 0)			//Wenn dies aktiviert wäre, würde man im Spiel bei Berührung der Ränder verlieren
	//gameOver = true;
	if (x >= width) x = 0; else if (x < 0) x = width - 1;		//Wenn man den Rand an einer Seite berührt kommt die Schlange aus der gegenüberliegenden Seite wieder raus
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)								//Wenn Der Schlangenkopf die selbe Koordinate aufweißt wie ein Teil des Schwanzes, dann ist das Spiel verloren
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)		//Wenn der Kopf der Schlange die selben Koordinaten wie die Frucht aufweist, wird die Schlange länger und die Frucht erscheint an einem zufälligen neuen Punkt
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
int main()								//Spielroutine während Spiel ausgeführt wird
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(50);						//Verlangsamt die Spielgeschwindigkeit
	}
	return 0;
}