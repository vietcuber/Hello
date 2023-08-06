#include <conio.h>
#include <stdio.h> 
#include <iostream>
#include <fstream> 
#include <stdlib.h>
#include <time.h>
#include <windows.h> 
#include <string>

#define NORTH 0 // tren
#define EAST 1 // phai
#define SOUTH 2 // duoi
#define WEST 3 // trai
#define Toado pair <int, int>
#define H first // H = hang
#define C second // C = cot
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define cps 1000 //CLOCKS_PER_SEC  1000

using namespace std;

int way[1000][2]; // mảng 2 chiều chứa các bước giải mê cung
int way_user[1000][2]; // ... of user;
int demWay = 0; // số bước chân để giải mê cung tối ưu
int user_step = 0; // số bước chân của người chơi
int GRID_WIDTH; // chieu rong me cung
int GRID_HEIGHT; // chieu cao me cung

bool maze[35 * 77]; // 35 x 77 la maxsize
bool maze2D[35][77];
int step; // the same with demWay num
int ways = 0;

clock_t start;

double temp_time, final_time;

int capdo = 0; // bien level nhung la bien toan cuc

class Mecung
{
	int n, m;
	int A[100][100];
public:

	void Path()
	{
		step = INT_MAX;
		ways = 0;
		Toado s, f;
		s.H = s.C = 2;
		f.C = GRID_WIDTH - 1;
		f.H = GRID_HEIGHT - 1;
		Toado* x = new Toado[n * m + 5];
		x[1] = s;
		A[s.H][s.C] = 1;
		TRY(x, 1, f);
		delete[] x;
		x = 0;
	}

	void TRY(Toado* x, int k, Toado f)
	{
		int hh[4] = { 0, -1,  0,  1 };
		int hc[4] = { 1,  0, -1,  0 };
		if (x[k] == f) Print(x, k);
		else
		{
			FOR(t, 0, 3)
			{
				x[k + 1].H = x[k].H + hh[t];
				x[k + 1].C = x[k].C + hc[t];
				if (A[x[k + 1].H][x[k + 1].C] == 0)
				{
					A[x[k + 1].H][x[k + 1].C] = 1; //tien
					TRY(x, k + 1, f);
					A[x[k + 1].H][x[k + 1].C] = 0; //lui
				}
			}
		}
	}

	void Print(Toado* x, int k)
	{
		ways++; // số cách giải
		if (step > k) // +inf > bước đi
		{
			demWay = 0;
			FOR(i, 1, k)
			{
				way[i][0] = x[i].H;
				way[i][1] = x[i].C;
				demWay++;
			}
			step = k;
		}
	}

	void LoadFile(char* fn)
	{
		ifstream f(fn);
		f >> n >> m;
		FOR(i, 1, n)
			FOR(j, 1, m)
			f >> A[i][j];
		f.close();
		FOR(i, 1, n) A[i][0] = A[i][m + 1] = 1;
		FOR(j, 1, m) A[0][j] = A[n + 1][j] = 1;
	}

};

void bye();
void menu();
void veMenu();
void veKhung();
void moveMenu(int& x, int& y, char lenh, bool sub);
void gioi_thieu();
char doi_nhap(char lenh);
void gotoxy(short x, short y);
void fixConsoleWindow();
void TextColor(int x);
void SetWindow(int Width, int Height);
void play(int level);
void genmaze();
void move();
void moveCharacter();
void Visit(int x, int y);
int XYToIndex(int x, int y);
int IsInBounds(int x, int y);
void autoMove();
void showInfo(int level);
void showStep();
void showTime();
void winner(double time, int user_step);
void loser();
void huong_dan();
void saveGame();
void xep_hang(int c);
void ducMaze(int level);

int main()
{
	fixConsoleWindow();	// co dinh console
	SetWindow(105, 50); // kich co console
	menu();
}

void ducMaze(int level)
{
	short GRID_HEIGHT, GRID_WIDTH;
	short x = 0, y = 0;

	if (level == 1)
	{
		GRID_WIDTH = 25;
		GRID_HEIGHT = 13;
	}
	if (level == 2)
	{
		GRID_WIDTH = 51;
		GRID_HEIGHT = 23;
	}
	if (level == 3)
	{
		GRID_WIDTH = 77;
		GRID_HEIGHT = 35;
	}

	switch (level)
	{
	case 1:
	{
		FOR(i, 0, 10)
		{
			while (1)
			{
				x = rand() % (GRID_WIDTH - 1);
				y = rand() % (GRID_HEIGHT - 1);
				if (maze[XYToIndex(x, y)] && x != 0 && y != 0 && x != GRID_WIDTH - 1 && y != GRID_HEIGHT - 1)
				{
					maze[XYToIndex(x, y)] = 0;
					break;
				}
			}
		}
		break;
	}
	case 2:
	{
		FOR(i, 0, 15)
		{
			while (1)
			{
				x = rand() % (GRID_WIDTH - 1);
				y = rand() % (GRID_HEIGHT - 1);
				if (maze[XYToIndex(x, y)] && x != 0 && y != 0 && x != GRID_WIDTH - 1 && y != GRID_HEIGHT - 1)
				{
					maze[XYToIndex(x, y)] = 0;
					break;
				}
			}
		}
		break;
	}
	case 3:
	{
		FOR(i, 0, 17)
		{
			while (1)
			{
				x = rand() % (GRID_WIDTH - 1);
				y = rand() % (GRID_HEIGHT - 1);
				if (maze[XYToIndex(x, y)] && x != 0 && y != 0 && x != GRID_WIDTH - 1 && y != GRID_HEIGHT - 1)
				{
					maze[XYToIndex(x, y)] = 0;
					break;
				}
			}
		}
		break;
	}

	}
}
void loser()
{
	TextColor(14);
	FOR(i, 0, 10)
	{
		gotoxy(29, GRID_HEIGHT + 1 + i);
		if (i == 0)	//dong dau
		{
			cout << char(201);
			FOR(j, 1, 21) cout << char(205) << char(205);
			cout << char(205) << char(205) << char(187) << endl;
		}
		else if (i == 10)	//dong cuoi
		{
			cout << char(200);
			FOR(j, 1, 21) cout << char(205) << char(205);
			cout << char(205) << char(205) << char(188) << endl;
		}
		else //dong thuong
		{
			cout << char(186);
			gotoxy(74, GRID_HEIGHT + 1 + i);
			cout << char(186) << endl;
		}
	}
	gotoxy(31, GRID_HEIGHT + 3);
	cout << "Ban chua giai me cung thanh cong nhung da";
	gotoxy(31, GRID_HEIGHT + 4);
	cout << "su dung quyen tro giup.";
	gotoxy(31, GRID_HEIGHT + 6);
	cout << "Hay co gang hon cho lan sau ban nhe!";
	gotoxy(31, GRID_HEIGHT + 8);
	cout << "\t\t>> Nhan phim bat ki de tiep tuc";
	_getch();
	menu();

}
void xep_hang(int c)
{
	system("cls");

	string lv;
	switch (c)
	{
	case 1: lv = "mazelv1.txt"; break;
	case 2: lv = "mazelv2.txt"; break;
	case 3: lv = "mazelv3.txt"; break;
	}

	ifstream isf(lv);
	if (isf.good()) // nếu em vẫn còn bên anh
	{
		ifstream fi;
		fi.open(lv, ios::in);

		int dem = 0;
		string* s;
		double* stime;
		s = new string[100];	// Player
		stime = new double[100]; // mảng time

		string line;
		while (!fi.eof())
		{
			getline(fi, line);
			s[dem] = line;
			if (s[dem].length() > 0)
				stime[dem] = stod(s[dem].substr(s[dem].find(':') + 1, s[dem].length())); // tách time từ string s
			dem++;
		}
		dem--;
		fi.close();

		// sort time
		FOR(i, 0, dem - 2)
		{
			FOR(j, i + 1, dem - 1)
				if (stime[i] > stime[j])
				{
					swap(stime[i], stime[j]);
					swap(s[i], s[j]);
				}
		}

		veKhung();
		if (dem > 10)
			dem = 10;
		gotoxy(51, 17);
		TextColor(14);
		cout << "BANG XEP HANG";
		FOR(i, 0, dem - 1)
		{
			gotoxy(46, 19 + i);
			cout << i + 1 << "/ " << s[i].substr(0, s[i].find(':')) << "   Time: " << stime[i] << endl;
		}

		delete[] s, stime;
		stime = 0;
		s = 0;
	}
	else
	{
		veKhung();
		gotoxy(51, 17);
		TextColor(14);
		cout << "Khong co du lieu!";
	}

	_getch();
	menu();
}
void veKhung()
{
	TextColor(14);
	FOR(i, 0, 14)
	{
		gotoxy(35, 15 + i);
		if (i == 0)	//dong dau
		{
			cout << char(201);
			FOR(j, 1, 21) cout << char(205) << char(205);
			cout << char(205) << char(205) << char(187) << endl;
		}
		else if (i == 14)	//dong cuoi
		{
			cout << char(200);
			FOR(j, 1, 21) cout << char(205) << char(205);
			cout << char(205) << char(205) << char(188) << endl;
		}
		else //dong thuong
		{
			cout << char(186);
			gotoxy(80, 15 + i);
			cout << char(186) << endl;
		}
	}
}

void saveGame()
{
	system("cls");
	string lv;
	switch (capdo)
	{
	case 1: lv = "mazelv1.txt"; break;
	case 2: lv = "mazelv2.txt"; break;
	case 3: lv = "mazelv3.txt"; break;
	}
	char username[10];

	veKhung();

	TextColor(13);
	gotoxy(53, 17);
	cout << "Save Game";
	TextColor(15);
	gotoxy(40, 20);
	cout << "Nhap ten nguoi choi";
	gotoxy(40, 22);
	cout << ">> ";
	//getline(cin, username);
	FOR(i, 0, 9) cin >> username[i];
	ofstream f(lv, ios::app);
	FOR(i, 0, 9) f << username[i];
	f << ":" << final_time << endl;
	f.close();
}

void huong_dan()
{
	system("cls");
	GRID_WIDTH = 35;
	GRID_HEIGHT = 17;

	FOR(i, 0, GRID_WIDTH * GRID_HEIGHT - 1) maze[i] = true;
	Visit(1, 1);
	TextColor(2);
	FOR(i, 0, GRID_HEIGHT - 1)
	{
		FOR(j, 0, GRID_WIDTH - 1)
		{
			if (maze[XYToIndex(j, i)])
			{
				maze2D[i][j] = 1;
				cout << char(219);
			}
			else
			{
				maze2D[i][j] = 0;
				cout << " ";
			}
		}
		cout << endl;
	}
	gotoxy(1, 1);
	printf("X");
	gotoxy(GRID_WIDTH - 2, GRID_HEIGHT - 2);
	printf("$");
	veKhung();

	TextColor(13);
	gotoxy(48, 17);
	cout << "HUONG DAN CHOI ME CUNG";
	TextColor(15);
	gotoxy(38, 19);
	cout << "1. Su dung cac mui ten tren ban phim";
	gotoxy(41, 20);
	cout << "de di chuyen nhan vat";
	gotoxy(38, 22);
	cout << "2. Di chuyen nhan vat X -> $";
	gotoxy(41, 23);
	cout << "de chien thang";
	gotoxy(38, 25);
	cout << "3. Hoan thanh me cung voi thoi gian";
	gotoxy(41, 26);
	cout << "ngan nhat de co hang cao";
	_getch();

	menu();
}

void winner(double time, int user_step)
{
	final_time = time; // time này thì truyền temp vào

	TextColor(14);
	FOR(i, 0, 10)
	{
		gotoxy(29, GRID_HEIGHT + 1 + i);
		if (i == 0)	//dong dau
		{
			cout << char(201);
			FOR(j, 1, 21) cout << char(205) << char(205);
			cout << char(205) << char(205) << char(187) << endl;
		}
		else if (i == 10)	//dong cuoi
		{
			cout << char(200);
			FOR(j, 1, 21) cout << char(205) << char(205);
			cout << char(205) << char(205) << char(188) << endl;
		}
		else //dong thuong
		{
			cout << char(186);
			gotoxy(74, GRID_HEIGHT + 1 + i);
			cout << char(186) << endl;
		}
	}
	TextColor(15);
	gotoxy(31, GRID_HEIGHT + 3);
	cout << "CHUC MUNG BAN DA GIAI THANH CONG ME CUNG";
	gotoxy(31, GRID_HEIGHT + 5);
	cout << ">> NHAN L DE LUU DIEM SO";
	gotoxy(31, GRID_HEIGHT + 7);
	cout << ">> NHAN ENTER DE XEM DUONG DI TOI UU";
	gotoxy(31, GRID_HEIGHT + 9);
	cout << ">> NHAN PHIM BAT KI DE TRO VE MENU";

	bool lap = 1;
	while (lap)
	{
		char lenh = ' ';
		lenh = doi_nhap(lenh);
		switch (lenh)
		{
		case 13: //enter
			autoMove();
			break;
		case 'L': case 'l':
			saveGame();
			lap = !lap;
			break;
		default: menu();
		}
	}

	menu();
}

void showInfo(int level)
{
	// hiện thông tin người chơi
	TextColor(14);
	for (int i = 0; i <= 40; i++)	// huong dan
	{
		gotoxy(85, 0 + i);
		if (i == 0)	//dong dau
		{
			cout << char(201);
			for (int j = 1; j <= 8; j++)
			{
				cout << char(205) << char(205);
			}
			cout << char(205) << char(205) << char(187) << endl;
		}
		else if (i == 40)	//dong cuoi
		{
			cout << char(200);
			for (int j = 1; j <= 8; j++)
			{
				cout << char(205) << char(205);
			}
			cout << char(205) << char(205) << char(188) << endl;
		}
		else //dong thuong
		{
			cout << char(186);
			gotoxy(104, 0 + i);
			cout << char(186) << endl;
		}
	}

	gotoxy(91, 3);
	cout << "MUC CHOI";
	gotoxy(90, 6);
	TextColor(12);
	switch (level)
	{
	case 1: cout << "<< Easy >>"; break;
	case 2: gotoxy(89, 6);
		cout << "<< Normal >>"; break;
	case 3: cout << "<< Hard >>"; break;
	}
	TextColor(15);
	gotoxy(87, 10);

	cout << "THOI GIAN DA QUA";

	gotoxy(89, 14);
	cout << "SO BUOC DA DI";
	gotoxy(87, 18);
	cout << "BUOC GIAI TOI UU";
	gotoxy(93, 19);
	cout << demWay - 1;
	gotoxy(89, 21);
	cout << "SO CACH GIAI";
	TextColor(14);
	gotoxy(88, 24);
	cout << "CACH DI CHUYEN";
	gotoxy(91, 26);
	cout << "^: LEN";
	gotoxy(91, 28);
	cout << "v: XUONG";
	gotoxy(91, 30);
	cout << "<: TRAI";
	gotoxy(91, 32);
	cout << ">: PHAI";
	gotoxy(89, 34);
	cout << "ENTER: GIAI";
	gotoxy(89, 36);
	cout << "TAB: VE MENU";
	gotoxy(89, 38);
	cout << "ESC: THOAT GAME";
}

void showStep()
{
	// hiện số bước của người chơi 
	gotoxy(93, 15);
	TextColor(15);
	cout << user_step;
}

void showTime()
{
	TextColor(15);
	gotoxy(93, 22);
	cout << ways;

	// hiện thời gian 
	clock_t end = clock();
	temp_time = double(end - start) / cps;
	gotoxy(92, 11);
	TextColor(15);
	cout << temp_time << " s";

	// lưu ý: temp_time là 1 biến toàn cục
}

void bye()
{
	system("cls");
	TextColor(14);
	gotoxy(45, 20);
	cout << "TRO CHOI KET THUC\n";
	gotoxy(45, 21);
	Sleep(2000);
	exit(0);
}

// Duong di toi uu
void autoMove()
{
	TextColor(12);
	FOR(i, 1, user_step)
	{
		gotoxy(way_user[i][1], way_user[i][0]);
		cout << char(219);
		Sleep(10);
	}
	TextColor(14);
	gotoxy(1, 1);
	FOR(i, 0, demWay)
	{
		gotoxy(way[i][1] - 1, way[i][0] - 1);
		cout << char(219);
		Sleep(10);
	}

}

int XYToIndex(int x, int y)
{
	//Converts the two-dimensional index pair(x,y) into a single-dimensional index.  The result is y * ROW_WIDTH + x.
	return y * GRID_WIDTH + x;
}

int IsInBounds(int x, int y)
{
	// ret 1 if x and y both in-bounds
	if (x < 0 || x >= GRID_WIDTH) return false;
	if (y < 0 || y >= GRID_HEIGHT) return false;
	return true;
}

// Tao me cung
void genmaze()
{
	demWay = 0;
	srand(time(NULL));
	FOR(i, 0, GRID_WIDTH * GRID_HEIGHT - 1) maze[i] = true;

	Visit(1, 1);

	ducMaze(capdo);

	TextColor(2);
	FOR(i, 0, GRID_HEIGHT - 1)
	{
		FOR(j, 0, GRID_WIDTH - 1)
		{
			if (maze[XYToIndex(j, i)])
			{
				maze2D[i][j] = 1;
				cout << char(219);
			}
			else
			{
				maze2D[i][j] = 0;
				cout << " ";
			}
		}
		cout << endl;
	}

	TextColor(12);
	gotoxy(1, 1);
	cout << 'X';

	TextColor(14);
	gotoxy(GRID_WIDTH - 2, GRID_HEIGHT - 2);
	cout << '$';
	// ghi me cung ra file

	ofstream f("mecung.txt", ios::out);
	f << GRID_HEIGHT << " " << GRID_WIDTH << endl;
	FOR(i, 0, GRID_HEIGHT - 1)
	{
		FOR(j, 0, GRID_WIDTH - 1) f << maze2D[i][j] << " ";
		f << endl;
	}
	f.close();

	// giai me cung


	//Mecung M;
	//M.LoadFile("mecung.txt");
	//M.Path();

	Mecung M;
	char filename[] = "mecung.txt";
	M.LoadFile(filename);
	M.Path();
}

void Visit(int x, int y)
{
	// Starting at the given index, recursively visits every direction in a randomized order.

	// Set my current location to be an empty passage.
	maze[XYToIndex(x, y)] = 0;

	// Create an local array containing the 4 directions and shuffle their order.
	int dirs[4];
	dirs[0] = NORTH;
	dirs[1] = EAST;
	dirs[2] = SOUTH;
	dirs[3] = WEST;
	FOR(i, 0, 3)
	{
		int r = rand() & 3;
		int temp = dirs[r];
		dirs[r] = dirs[i];
		dirs[i] = temp;
	}

	// Loop through every direction and attempt to Visit that direction.
	FOR(i, 0, 3)
	{
		// dx,dy are offsets from current location.  Set them based on the next direction I wish to try.
		int dx = 0, dy = 0;
		switch (dirs[i])
		{
		case NORTH: dy = -1; break;
		case SOUTH: dy = 1; break;
		case EAST:  dx = 1; break;
		case WEST:  dx = -1; break;
		}

		// Find the (x,y) coordinates of the grid cell 2 spots away in the given direction.
		int x2 = x + (dx << 1);
		int y2 = y + (dy << 1);

		if (IsInBounds(x2, y2))
		{
			if (maze[XYToIndex(x2, y2)] == 1)
			{
				// (x2,y2) has not been visited yet...knock down the wall between my current position and that position
				maze[XYToIndex(x2 - dx, y2 - dy)] = 0;
				// Recursively Visit (x2,y2)
				Visit(x2, y2);
			}
		}
	}
}

void play(int level)
{
	if (level == 1)
	{
		GRID_WIDTH = 25;
		GRID_HEIGHT = 13;
	}
	if (level == 2)
	{
		GRID_WIDTH = 51;
		GRID_HEIGHT = 23;
	}
	if (level == 3)
	{
		GRID_WIDTH = 77;
		GRID_HEIGHT = 35;
	}

	capdo = level; // luu lai level de su dung cho ham savegame

	gotoxy(0, 0);
	system("cls");
	user_step = 0;
	genmaze();
	start = clock(); // tính điểm mốc thời gian bắt đầu chơi
	showInfo(level);
	moveCharacter();
}

void SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size
}

void TextColor(int x) //Xac dinh mau cua chu
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void gotoxy(short x, short y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

// Co dinh console
void fixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

char doi_nhap(char lenh)
{
	lenh = _getch();
	return lenh;
}

void moveMenu(int& x, int& y, char lenh, bool sub)
{
	gotoxy(x, y);       // xoa (ghi de)
	cout << " ";

	if (sub)
	{
		if (y >= 18 && lenh == 72)
		{
			if (y <= 18) y = 26;
			gotoxy(x, y - 2);
			TextColor(13);
			cout << "<";
			TextColor(15);
			y -= 2;
		}

		if (y <= 24 && lenh == 80)
		{
			if (y >= 24) y = 16;
			gotoxy(x, y + 2);
			TextColor(13);
			cout << "<";
			TextColor(15);
			y += 2;
		}
	}
	else
	{
		if (y >= 18 && lenh == 72)
		{
			if (y <= 18) y = 28;
			gotoxy(x, y - 2);
			TextColor(13);
			cout << "<";
			TextColor(15);
			y -= 2;
		}

		if (y <= 26 && lenh == 80)
		{
			if (y >= 26) y = 16;
			gotoxy(x, y + 2);
			TextColor(13);
			cout << "<";
			TextColor(15);
			y += 2;
		}
	}
}

void veMenu()
{
	system("cls");

	gotoxy(35, 6); TextColor(12); cout << "888b     d888";
	gotoxy(35, 7); TextColor(12); cout << "8888b   d8888";
	gotoxy(35, 8); TextColor(12); cout << "88888b.d88888";
	gotoxy(35, 9); TextColor(12); cout << "888Y88888P888"; TextColor(14); cout << " 8888b. "; TextColor(2); cout << "88888888"; TextColor(11); cout << " .d88b. ";
	gotoxy(35, 10); TextColor(12); cout << "888 Y888P 888"; TextColor(14); cout << "    '88b"; TextColor(2); cout << "   d88P "; TextColor(11); cout << "d8P  Y8b";
	gotoxy(35, 11); TextColor(12); cout << "888  Y8P  888"; TextColor(14); cout << ".d888888"; TextColor(2); cout << "  d88P  "; TextColor(11); cout << "88888888";
	gotoxy(35, 12); TextColor(12); cout << "888   '   888"; TextColor(14); cout << "888  888"; TextColor(2); cout << " d88P   "; TextColor(11); cout << "Y8b.    ";
	gotoxy(35, 13); TextColor(12); cout << "888       888"; TextColor(14); cout << "'Y888888"; TextColor(2); cout << "88888888"; TextColor(11); cout << " 'Y8888 ";
	TextColor(14);

	FOR(i, 0, 14)
	{
		gotoxy(39, 15 + i);
		if (i == 0) //dong dau
		{
			cout << char(201);
			FOR(j, 1, 12)
				cout << char(205) << char(205);
			cout << char(205) << char(205) << char(187) << endl;
		}
		else if (i == 14)   //dong cuoi
		{
			cout << char(200);
			FOR(j, 1, 12)
				cout << char(205) << char(205);
			cout << char(205) << char(205) << char(188) << endl;
		}
		else //dong thuong
		{
			cout << char(186);
			gotoxy(66, 15 + i);
			cout << char(186) << endl;
		}
	}

	int x = 44, y = 18;

	gotoxy(x, y);
	cout << "CHOI" << endl;
	gotoxy(x, y + 2);
	cout << "HUONG DAN" << endl;
	gotoxy(x, y + 4);
	cout << "GIOI THIEU" << endl;
	gotoxy(x, y + 6);
	cout << "XEP HANG" << endl;
	gotoxy(x, y + 8);
	cout << "THOAT" << endl;

	x = 75;
	gotoxy(x, y - 1);
	cout << "DI CHUYEN" << endl;
	gotoxy(x, y + 2);
	cout << "^: LEN" << endl;
	gotoxy(x, y + 4);
	cout << "v: XUONG" << endl;
	gotoxy(x, y + 6);
	cout << "ENTER: CHON" << endl;

	x = 62;
	gotoxy(x, y);
	TextColor(13);
	cout << "<";
	TextColor(15);
}

void gioi_thieu()
{
	system("cls");

	veKhung();

	TextColor(13);
	gotoxy(53, 17);
	cout << "MazeGame";
	TextColor(15);
	gotoxy(40, 20);
	cout << "Pham Hoang Nhat Thanh x Andy Nguyen";
	gotoxy(40, 22);
	cout << "DH20CS01 2021";
	gotoxy(40, 24);
	cout << "GV: Vo Thi Hong Tuyet";
	_getch();
}

void menu()
{
	veMenu();

	int x = 62, y = 18;
	bool lap = true, sub;

	while (lap)
	{
		sub = 0;
		char lenh = ' ';
		lenh = doi_nhap(lenh);          //doi nhap tu ban phim

		switch (lenh)
		{
		case 72:    // len
			moveMenu(x, y, lenh, sub);
			break;

		case 80:    // xuong
			moveMenu(x, y, lenh, sub);
			break;
		case 13: //chon
			switch (y)
			{
			case 18: //choi
				lap = false;
				x = 44; sub = 1;
				TextColor(14);
				gotoxy(x, y); cout << "MUC DO DE" << endl;
				gotoxy(x, y + 2); cout << "BINH THUONG" << endl;
				gotoxy(x, y + 4); cout << "MUC DO KHO" << endl;
				gotoxy(x, y + 6); cout << "QUAY LAI MENU" << endl;
				gotoxy(x, y + 8); cout << "     " << endl;
				x = 62; y = 18;
				while (1)
				{
					lenh = doi_nhap(lenh);
					switch (lenh)
					{
					case 72:    // len
						moveMenu(x, y, lenh, sub);
						break;

					case 80:    // xuong
						moveMenu(x, y, lenh, sub);
						break;
					case 13: //enter
						switch (y)
						{
						case 18: //de
							play(1);
							break;
						case 20: //vua
							play(2);
							break;
						case 22: //kho
							play(3);
							break;
						default:
							menu();
						}
					}
				}
				break;
			case 20: // huong dan
				huong_dan();
				break;
			case 22:
				gioi_thieu();
				menu();
			case 24:
				lap = false;
				gotoxy(x, y);
				cout << " ";
				gotoxy(x, 18);
				TextColor(13);
				cout << '<';
				x = 44; sub = 1;
				TextColor(14);
				gotoxy(x, y - 6); cout << "MUC DO DE" << endl;
				gotoxy(x, y - 4); cout << "BINH THUONG" << endl;
				gotoxy(x, y - 2); cout << "MUC DO KHO" << endl;
				gotoxy(x, y); cout << "QUAY LAI MENU" << endl;
				gotoxy(x, y + 2); cout << "     " << endl;
				x = 62; y = 18;
				while (1)
				{
					lenh = doi_nhap(lenh);
					switch (lenh)
					{
					case 72:    // len
						moveMenu(x, y, lenh, sub);
						break;

					case 80:    // xuong
						moveMenu(x, y, lenh, sub);
						break;
					case 13: //enter
						switch (y)
						{
						case 18: //de
							xep_hang(1); //xuat top 10
							break;
						case 20: //vua
							xep_hang(2); //xuat top 10
							break;
						case 22: //kho
							xep_hang(3); //xuat top 10
							break;
						default:
							menu();
						}
					}
				}
				break;
			case 26:
				bye();
				lap = false;
				break;
			}
			break;
		}

	}
}

void moveCharacter()
{
	int x = 1, y = 1;
	bool lap = true;
	while (x != GRID_WIDTH - 2 && y != GRID_HEIGHT - 2)
	{
		while (lap)
		{
			showTime();
			TextColor(12);
			if (x == GRID_WIDTH - 2 && y == GRID_HEIGHT - 2)
				winner(temp_time, user_step);

			char lenh = ' ';
			lenh = doi_nhap(lenh);

			switch (lenh)
			{
			case 72:    // len
				if (!maze2D[y - 1][x])
				{
					gotoxy(x, y);
					cout << ' ';
					y -= 1;
					gotoxy(x, y);
					cout << 'X';
					gotoxy(x, y);
					user_step++;
					showStep();
					way_user[user_step][1] = x;
					way_user[user_step][0] = y;
				}
				break;

			case 80:    // xuong
				if (!maze2D[y + 1][x])
				{
					gotoxy(x, y);
					cout << ' ';
					y += 1;
					gotoxy(x, y);
					cout << 'X';
					gotoxy(x, y);
					user_step++;
					showStep();
					way_user[user_step][1] = x;
					way_user[user_step][0] = y;
				}
				break;

			case 77:    // phai
				if (!maze2D[y][x + 1])
				{
					gotoxy(x, y);
					cout << ' ';
					x += 1;
					gotoxy(x, y);
					cout << 'X';
					gotoxy(x, y);
					user_step++;
					showStep();
					way_user[user_step][1] = x;
					way_user[user_step][0] = y;
				}
				break;

			case 75:    // trai
				if (!maze2D[y][x - 1])
				{
					gotoxy(x, y);
					cout << ' ';
					x -= 1;
					gotoxy(x, y);
					cout << 'X';
					gotoxy(x, y);
					user_step++;
					showStep();
					way_user[user_step][1] = x;
					way_user[user_step][0] = y;
				}
				break;
			case 13: // auto move giữa chừng
				autoMove();
				loser();
				//không thể cho nó làm winner vì nó là loser
				//winner(temp_time, user_step);
				break;
			case 27:	// thoat
				bye();
				break;

			case 9:	// quay lai
				menu();
				break;
			default: break;
			}
		}
	}
	_getch();
}