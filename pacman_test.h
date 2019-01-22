
#include<iostream>
#include<conio.h>				// for getch() & kbhit()
#include<windows.h>				// for Sleep(),Beep() & rand()

//	macro substitution

//#define w 20
//#define h 10
#define max 5
const int w=28,h=14;

using namespace std ;

class packman
{
	// data members by default private
	
	char map[h+1][w+1];
	bool go,flag;
	static int level,score;					// static data member
	int x,y,g,gx[max],gy[max],st,bs,colour_no;
	int px,py,gpx[max],gpy[max],ch,gch[max];

	// member fuctions
	
	public:
		
		void setup();
		void draw();
		void level_1();
		void level_2();
		void logic();
		void input();
		void win();
		void ghost();
		void colour(int no);
		void show_score_list();
		void modify_score_list();
		
		friend void run(packman p);
};
	
	int packman::score=-1;
	int packman::level=1;			//static member initialization

	void packman::setup()
	{
		go=false; ch=st=colour_no=0;
		x=w/2; y=h/2;
		
		if(level==1 || level==3)
		g=2;
		else
		{
			if(level==2)
			g=3; else g=4;
		}
		
		ghost();
		
		for(int i=1;i<h;i++)
		for(int j=1;j<w;j++)
		map[i][j]='.';
		
		if(level<=2 || level==4)
		{
			map[1][w-1]='o';	map[h-1][1]='o';
			if(level==2)		map[1][1]='o';
		}
	}
	
	void packman::ghost()
	{
		for(int i=0; i<g; i++)
		{
			gch[i]=0;
			switch(i)
			{
				case 0: 	gx[i]=1;	gy[i]=1;	break;
				case 1: 	gx[i]=w-1;	gy[i]=h-1;	break;
				case 2: 	gx[i]=w-1;	gy[i]=1;	break;
				case 3: 	gx[i]=1;	gy[i]=h-1;	break;
			}
		}
	}

	void packman::draw()
	{
		Sleep(20);
		system("cls");
		colour(6);
		
		cout<<"\n\t*****	PACKMAN GAME ( MINI PROJECT 3RD SEM )	*****"<<endl;
		cout<<"\t*****	Created by ~ AMAN KATHAIT	*****"<<endl;	colour(2);
		cout<<"\n\tLEVEL=="<<level<<"\tHIGH SCORE=="<<bs<<"\n\tSCORE=="<<score<<"\tSAFETY TIME REMAINING=="<<st<<endl;	colour(5);
		cout<<"\n\tPRESS x FOR EXIT   PRESS p FOR PAUSE   PRESS L FOR HIGH SCORES LIST"<<endl;
		
		switch(level)
		{
			case 1: 	level_1(); break;
			case 2: 	level_2(); break;
			case 3: 	level_1(); break;
			case 4: 	level_2(); break;
		}
		
	for(int i=0;i<=h;i++)
	{
		cout<<"\n\t";
			
		for(int j=0;j<=w;j++)
		{
			bool f=false;
			for(int k=0; k<g; k++)
			if((i==gy[k] && j==gx[k]))
			{
				if(colour_no==0)
				colour(4);
				else colour(colour_no);
				cout<<"G";	f=true; break;	
			}
			if(f!=true)
			{
				switch(map[i][j])
				{
					case '#': 	colour(15);	cout<<map[i][j]; break;
					case '.': 	colour(5);	cout<<map[i][j]; break;
					case 'P': 	colour(11);	cout<<map[i][j]; break;
					case 'o': 	colour(10);	cout<<map[i][j]; break;
					case ' ':   colour(100);  cout<<map[i][j]; break;
				}	
			}
		}
	}
		
	}
	
	void packman::colour(int no)
	{
		HANDLE text= GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute(text,no | FOREGROUND_INTENSITY);
	}

	void packman::input()
	{
		map[y][x]=' ';	//to eat
		px=x; py=y; 		// prevoius position
		for(int i=0; i<g; i++)
		{
			gpx[i]=gx[i]; gpy[i]=gy[i];
		}
		
		if(kbhit())		//kbhit is a boolen fuction which tell key is press or not from keyboard
		{
			switch((getch()))
			{
				case 75: 	x--; ch=1; break;
				case 77: 	x++; ch=2; break;
				case 72: 	y--; ch=3; break;
				case 80: 	y++; ch=4; break;
				
				case 'l':	show_score_list(); break;
				
				case 'x':	cout<<"\n\n\tARE YOU SURE TO EXIT :(Y/N)\t";
							if(tolower(getch())=='y')
							exit(0); break;
				
				case 'p': 	cout<<"\n\n\tPRESS ANY KEY TO RESUME......";
							//system("pause>nul");
							getch(); break;
			}
		}
		else
		{
			switch(ch)
			{
				case 1: 	x--; break;
				case 2: 	x++; break;
				case 3: 	y--; break;
				case 4: 	y++; break;
			}
		}
		for(int i=0; i<g; i++)
		switch(gch[i])
		{
			case 0: 	gy[i]--; break;
			case 1: 	gy[i]++; break;
			case 2: 	gx[i]++; break;
			case 3: 	gx[i]--; break;
		}
	}

	void packman::logic()
	{
		static int pgch[max];
		if(map[y][x]=='#')
		{
			x=px; y=py;
		}
		
		for(int i=0; i<g; i++)
		if(map[gy[i]][gx[i]]=='#')
		{
			gch[i]=rand() % 3;
			pgch[i]=gch[i];
			gx[i]=gpx[i]; gy[i]=gpy[i];
		}
		else
		{
			gch[i]=rand() % h;
			if(gch[i]%2==0) gch[i]++;
			if(gy[i]==gch[i] && gx[i]==w-1)
			gch[i]=pgch[i]=3;
			else gch[i]=pgch[i];
		}
		
		if(map[y][x]=='.')
		{ 
			if(score%3==0)
			Beep(1000,50);
			score++;
		}
		if(st!=0)
		st--;
		else colour_no=0;
		if(map[y][x]=='o')
		{
			score+=10; st=60;	colour_no=16;Beep(2000,100);
		}
		
		for(int i=0; i<g; i++)
		if(((x==gx[i] && y==gy[i]) || ((x==gpx[i] && y==gpy[i] && px==gx[i] && py==gy[i]))) && st==0)
		{
			//go=true; Beep(2000,150);						// gameover
		}
		else
		win();							// level complete
		
		FILE *ptr;
		ptr=fopen("list.txt","r");
		if(bs=getw(ptr));
		fclose(ptr);
	}

	void packman::win()
	{
		flag=false; // reinitialization
		
		for(int i=1;i<h;i++)
		{
			for(int j=1;j<w;j++)
			if(map[i][j]=='.')
			flag=true;
		}
		
		if(flag==false)
		{
			level++;	// next level
			go=true;
		}
	}

	// friend function defination
	
	void run(packman p)
	{
		prev:
		while(p.go!=true)
		{
			p.logic();
			p.draw();
			p.input();
			//p.logic();
			Sleep(20);
		}
		
		p.modify_score_list();
		p.level=p.level-p.g+1;
		
		if(p.level==5)
		{
			cout<<"\n\n\t*****CONGRATUALTION YOU COMPLETE ALL LEVEL*****"<<endl;
			return;
		}
		if(p.flag==false)
		{
			p.colour(6); Beep(4000,500);
			cout<<"\n\n\t*****CONGRATUALTION YOU COMPLETE LEVEL "<<p.level-1<<"*****"<<endl;	p.colour(15);
			cout<<"\n\n\tDO YOU WANT TO PLAY NEXT LEVEL :(Y/N)\t";
			if('y'==tolower(getch()))
			{
				//packman p;
				p.setup();
				goto prev;
				//run(p);
			}
		}
		else
		{
			p.colour(4);	cout<<"\n\n\t.....GAMEOVER....."<<endl;
		}
	
	}
	
	void packman::show_score_list()
	{
		FILE *ptr;	int num,f=0,i=1;
		ptr=fopen("list.txt","r");
		system("cls");
		
		while((num=getw(ptr))!=-1)
		{
			colour(i);
			cout<<i<<".\t"<<num<<endl;
			f=1; i++;
		}
		
		if(f==0)
		{
			colour(4);	cout<<"\nSORRY NO RECORD FOUND !!!!!!!!\n";
		}
		system("pause");
		fclose(ptr);
	}
	
	void sort(int a[], int n)
	{
		int tmp;
		for(int i=0;i<n-1;i++)
  		{	 
			for(int j=0;j<n-i-1;j++)
    		{ 
				if(a[j]<a[j+1])
      			{
					tmp=a[j];
        			a[j]=a[j+1];
        			a[j+1]=tmp;
      			}
			}
  		}
	}
	
	void packman::modify_score_list()
	{
		int n=0,num,bs[20]={0};
		FILE *ptr ;
		ptr=fopen("list.txt","r");
		
		while((num=getw(ptr))!=-1)
		{
		bs[n]=num; n++;
		}
		fclose(ptr);
	
		ptr=fopen("list.txt","w");
		bs[n]=score;
		sort(bs,n+1);
		
		for(int i=0;i<=n;i++)
		putw(bs[i],ptr);
		
		fclose(ptr);
	}
	
	/* FUNCTIONS TO DESIGN MAP OF DIFEERENTS LEVEL */

	void packman::level_1()
	{
		for(int i=0;i<=h;i++)
		{
			for(int j=0;j<=w;j++)
			{	
				if(i==0 || i==h)
				map[i][j]='#';
				else
				{
					if(j==0 || j==w)
					map[i][j]='#';
					else
					{
						if(i%2==0 && j>=2 && j<=w-2)
						map[i][j]='#';
						else
						{
							if(i==y && j==x)
							map[i][j]='P';
						}
					}
				}
			}
		}
	}
	
	void packman::level_2()
	{
		for(int i=0;i<=h;i++)
		{
			for(int j=0;j<=w;j++)
			{
				if(i==0 || i==h)
				map[i][j]='#';
				else
				{
					if(j==0 || j==w)
					map[i][j]='#';
					else
					{
						if(i%2==0 && j%4!=0 && j>=2 && j<=w-2)
						map[i][j]='#';
						else
						{
							if(i==y && j==x)
							map[i][j]='P';
						}
					}
				}
			}
		}
	}
