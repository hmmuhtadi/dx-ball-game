# include "iGraphics.h"

#define on 0
#define off 1  
#define brickSet 7                     
#define brickNo 11   
#define brickWidth  36                  
#define brickHigh   16  

int start=off,flagBurst=off,burst=0,initializeFlag=on,pause=off,stageCounter=0,ballrad,hitting_condition=0,pop_border=off; 
int screen=-1,screen_y=530,stageFlag=off,Menu=off,Menu_x=700,board=0,selector=1,selector_y=350,pop_x,pop_y,pop_len,pop_hight;
int About=off,Load=off,Save=off,Keys=off,Hall_Of_Fame=off,Delay_Break=off,Mx,My,Player_Index=-1,name_flag=off,fire=1;
int total_saved_board,pre_save=off,pre_load=off,pre_about=off,pre_keys=off,ball=1,esc_blink=1;
char BOARD[1],save_load_instruction[30];

struct BOARD_PARAMETER
{
	int len,hight;
	int x,y;
}Board={496,429,25,45};

struct PADDLE
{
	int flag,len,hight,dLen;			
	int px,life;						
}Paddle={on,96,14,48,227,3};

struct BALL
{
	int flag;
	int dx,dy;	
	int x,y,speed;	
}Ball={on,4,4,on,on};

struct GUN
{
	int bulletFlag[4];			// these flags for counting enabled bullet set 
	int bulletFlag12[4][2];
	int flag,bullets;			// flag for enabling gun
	int i,j;
	int bulletX[4];				// 4 sets of bullets can be shown on the screen
	int bulletY[4];	
}Gun={{off,off,off,off},{{off,off},{off,off},{off,off},{off,off}},off,20};

struct GUN_ICON							
{
	int flag,up,down;
	int dy,dx,i,j;
	int X,Y,initialY;
}Gun_Icon={off,off,off,-6,7};

struct EXPAND_PADDLE							
{
	int flag,up,down;
	int dy,dx,i,j;
	int X,Y,initialY;
}Expand_Paddle={off,off,off,6,-7};

struct SHRINK_PADDLE							
{
	int flag,up,down;
	int dy,dx,i,j;
	int X,Y,initialY;
}Shrink_Paddle={off,on,off,6,7};

struct EXPAND_BALL							
{
	int flag,up,down;
	int dy,dx,i,j;
	int X,Y,initialY;
}Expand_Ball={off,on,off,-6,7};

struct SHRINK_BALL							
{
	int flag,up,down;
	int dy,dx,i,j;
	int X,Y,initialY;
}Shrink_Ball={off,off,on,-6,-7};

struct SLOW_BALL							
{
	int flag,up,down;
	int dy,dx,i,j;
	int X,Y,initialY;
}Slow_Ball={off,off,off,-6,7};

struct FAST_BALL							
{
	int flag,up,down;
	int dy,dx,i,j;
	int X,Y,initialY;
}Fast_Ball={off,off,off,6,-7};

struct BALL_THROUGH_BRICK							
{
	int flag,up,down,through;
	int dy,dx,i,j;
	int X,Y,initialY;
}Ball_Through_Brick={off,off,on,off,-7,6};

struct KILL_PADDLE							
{
	int flag,up,down;
	int dy,dx,i,j;
	int X,Y,initialY;
}Kill_Paddle={off,off,off,8,-7};


struct SCORE						
{
	char scoreStr[7];
	int score;
	int hits;
}Score;

struct BRICK
{
	int x,brickLeft;					// x co ordinates
	int y[brickSet];					// y co ordinates
	
	struct BRICK_PATTERN
	{
		int state[brickSet][brickNo];	// on-off state of bricks
		int type[brickSet][brickNo];
		int totalBrick;
	}Description;

}Brick={76,(brickSet*brickNo),{Board.y+180}};

struct HALL_OF_FAME
{
	char name[20];
	char score[7];
}Fame_Name[10],Player,temp;

struct CURSOR
{
	int flag;
	int x,y,blinker;
	char name[20];
	char temp[20];
	char game_name[20];
	char temp_game[20];
}Cursor={off};

struct SAVE_GAME
{
	int board,screen;
	char name[20];

	struct PADDLE Paddle;
	struct BALL Ball;
	struct GUN Gun;
	struct GUN_ICON	Gun_Icon;						
	struct EXPAND_PADDLE Expand_Paddle;							
	struct SHRINK_PADDLE Shrink_Paddle;							
	struct EXPAND_BALL Expand_Ball;							
	struct SHRINK_BALL Shrink_Ball;							
	struct SLOW_BALL Slow_Ball;						
	struct FAST_BALL Fast_Ball;							
	struct BALL_THROUGH_BRICK Ball_Through_Brick;							
	struct KILL_PADDLE Kill_Paddle;						
	struct SCORE Score;						
	struct BRICK Brick;
}Save_Game[10],Current,Temp;


void show_stage(void);
void show_game_screen(void);
void show_record_screen(void);
void show_starting_screen(void);
void show_pop_up_border(void);
void show_paddle_burst(void);
void show_score(void);
void show_gun(void);
void show_paddle(void);
void show_ball(void);
void show_icons(void);
void show_life(void);
void show_board_selector(void);
void show_record(void);
void show_cursor(void);
void move_pop_up_border(void);
void move_ball(void);
void move_bullet(void);
void move_icons(void);
void move_screen(void);
void move_selector(void);
void move_others(void);
void load_stage(void);
void initialize(void);
void initialize_icons_position(void);
void ball_brick_collision(void);
void bullet_brick_collision(void);
void burst_paddle(void);
void shoot(void);
void off_flags(void);
void check_record(void);
void check_menu(void);
void check_board(void);
void check_hitting_condition(int j,int i);
void select_board(void);
void load_hall_of_fame(void);
void insert_palyers_record(void);
void restart_game(void);
void blink_cursor(void);
void write(char key);
void save_record(void);
void score(void);
void glow_brick(void);
void save_game(void);
void delete_game(int serial);
void load_game(int serial);
void show_saved_name(void);
void check_availability(void);

void iDraw()
{	
	iClear(); 		
	
	if(screen==-1)
		show_starting_screen();
		
	else if(screen==0)	
		show_board_selector();	
	
	else if(screen==1||screen==4)
		iShowBMP(0,screen_y,"wm skin2.bmp");	
	
	else if(screen==2)
		show_game_screen();
		
	else if(screen==3)
		show_record_screen();		
} 

void iMouseMove(int mx, int my)
{
	
	if(pause==off&&Paddle.flag==on&&screen==2)
	{	
		Paddle.px=mx;	
		
		if(mx<=Board.x+ballrad*2)
			Paddle.px=Board.x+ballrad*2;
		else if(mx>=Board.x+Board.len-Paddle.len-ballrad*2)
			Paddle.px=Board.x+Board.len-Paddle.len-ballrad*2;
	}
}

void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{        
		Mx=mx;
		My=my;	
		check_menu();		
	}

	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if(screen==2&&Paddle.life!=0)		
			shoot(); 		
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		if(screen==2&&Paddle.life!=0)		
			start=on;
		
	}
}

void iKeyboard(unsigned char key)
{
    if(Cursor.flag==on)
		write(key);

	if(key=='p'&&Paddle.life>0&&About==off&&Save==off&&Load==off&&Keys==off&&screen==2)    
	{
		if(pause==off)
			pause=on;
		else 
			pause=off;
	}

	if(pause==off&&Paddle.flag==on&&screen==2)
	{
	/******************************Game start***********************************/
	if(key==32)    
	{
		if(Paddle.life!=0)
			start=on;		
	}		
	/********************************Jump****************************************/
		if(key=='a')    
			Paddle.px=31+ballrad*2;
				
		if(key=='s')    
			Paddle.px=227;		
		
		if(key=='d')    
			Paddle.px=517-Paddle.len-ballrad;
	}

	if(key==27)    
    {  
		if(screen==-1)
			screen=0;
		
		else if(screen==3)
		{
			if(Paddle.life>0&&board<6)
				screen=2;			
			else
			{				
				screen=0;
				board=0;
				Score.score=0;
				
				if(Cursor.flag==on)
				{
					Cursor.flag=off;
					name_flag=off;
					strcpy(Cursor.name,"");
				}
			}			
		}
		
		else
		{
			if(Paddle.life==0||board>5)
			{
				screen=4;
				check_record();
			}

			else 
			{
				screen=0;
				board=0;
				Score.score=0;
			}
		}
    }
	
	if(key==13)    
    {        
		if(screen==0)
		{
			off_flags();
			select_board();
			screen_y=530;
			screen=1;
		}

		if(name_flag==on&&(strlen(Cursor.name)!=0))
		{			
			strcpy(Player.name,Cursor.name);
			insert_palyers_record();
			name_flag=off;
			Cursor.flag=off;
			save_record();
			strcpy(Cursor.name,"");
		}
    }
}

void iSpecialKeyboard(unsigned char key)
{	
    if(key == GLUT_KEY_END)
	{
		exit(0);
	}
   
    if(key==GLUT_KEY_RIGHT)    
    {
		if(pause==off&&Paddle.flag==on)
		{	
			if(Paddle.px<517-Paddle.len-ballrad*2)
				Paddle.px+=10;
			else
				Paddle.px=517-Paddle.len-ballrad*2;
		}
    }
    
    if(key==GLUT_KEY_LEFT)    
    {        
		if(pause==off&&Paddle.flag==on)
		{	
			if(Paddle.px>31+ballrad*2)
				Paddle.px-=10;
			else
				Paddle.px=31+ballrad*2;
		}
    }
	
    if(key==GLUT_KEY_UP)    
    {
		if(screen==2)
			shoot(); 
		else if(screen==0)
		{
			selector_y+=50;
			if(selector_y>350)
				selector_y=350;
		}
	}

	if(key==GLUT_KEY_DOWN)    
    {
		if(screen==2)
			shoot(); 
		else if(screen==0)
		{
			selector_y-=50;

			if(selector_y<100)
				selector_y=100;
		}
	}
}

int main()
{
	load_hall_of_fame();
	
	iSettimer(1,move_ball);    
	iSettimer(1,move_icons);
	iSettimer(1,move_bullet);
	iSettimer(150,burst_paddle);	
	iSettimer(1,move_others);
	iSettimer(60,move_selector);
	iSettimer(700,blink_cursor);
	iSettimer(100,glow_brick);
	iSettimer(1,move_pop_up_border);

	iInitialize(699, 512, "DX-BALL");

	return 0;
}

void show_stage(void)
{
	register int i,j=0,brickx,bricky; 

	if(screen_y==0)
	{
		for(i=0;i<brickSet;i++)
		{    
			brickx=Brick.x,bricky=Brick.y[i];

			for(j=0;j<brickNo;j++)
			{
				if(Brick.Description.state[i][j]==on)
				{
					if(Brick.Description.type[i][j]==1)
						iShowBMP(brickx,bricky,"brickgreen.bmp"); 
					else if(Brick.Description.type[i][j]==2)
						iShowBMP(brickx,bricky,"brickblue.bmp"); 
					else if(Brick.Description.type[i][j]==3)
						iShowBMP(brickx,bricky,"brickred.bmp"); 
					else if(Brick.Description.type[i][j]==4)
					{
						if(fire==1)
							iShowBMP(brickx,bricky,"brickfiry.bmp"); 
						else if(fire==2)
							iShowBMP(brickx,bricky,"brickfiry2.bmp"); 
						else if(fire==3)
							iShowBMP(brickx,bricky,"brickfiry3.bmp"); 
						else if(fire==4)
							iShowBMP(brickx,bricky,"brickfiry4.bmp"); 
					} 
					else if(Brick.Description.type[i][j]==5)
						iShowBMP(brickx,bricky,"brickmetal.bmp"); 
					else if(Brick.Description.type[i][j]==6)
						iShowBMP(brickx,bricky,"brickviolet.bmp"); 
					else if(Brick.Description.type[i][j]==7)
						iShowBMP(brickx,bricky,"brickyellow.bmp");
					else if(Brick.Description.type[i][j]==8)
						iShowBMP(brickx,bricky,"brickorange.bmp");
					else if(Brick.Description.type[i][j]==9)
						iShowBMP(brickx,bricky,"brickmulti.bmp");
				}
						
				brickx+=brickWidth;
			} 
		}
	}
}

void initialize(void)
{
	static int i=0;
	
	if(i==0)
	{
		i++;

		for(i=1;i<brickSet;i++)		
			Brick.y[i]=Brick.y[0]+brickHigh*i;			
	}
	  
	Paddle.flag=on;
	Paddle.px=227;
	Paddle.len=96;	
	
	start=off;	
	hitting_condition=0;

	Ball.flag=on;
	Ball.dx=2;
	Ball.dy=5;
	ballrad=5;
	Ball.x=Paddle.px+(Paddle.len/2);	
	Ball.y=Board.y+Paddle.hight+ballrad;
	Ball.speed=0;

	Gun.bullets=20;
	strcpy(Cursor.name,"");
}

void load_stage(void)
{
	if(board<=5)
	{
		FILE *fp;
		fp=fopen("brick pattern.dat","rb");

		if(fp==NULL)
		{
			printf("Error");
			exit(1);
		}

		fseek(fp,(board)*sizeof(Brick.Description),0);
		fread(&Brick.Description,sizeof(Brick.Description),1,fp);
		fclose(fp);

		Brick.brickLeft=Brick.Description.totalBrick;
	}
}
	
void show_paddle_burst(void)
{
	if(flagBurst==on)
	{
		if(burst==1)
			iShowBMP(Paddle.px-6,Board.y,"burst1.bmp");
		if(burst==2)
			iShowBMP(Paddle.px-6,Board.y,"burst2.bmp");
		if(burst==3)
			iShowBMP(Paddle.px-6,Board.y,"burst3.bmp");
		if(burst==4)
			iShowBMP(Paddle.px-6,Board.y,"burst4.bmp");
		if(burst==5)
			iShowBMP(Paddle.px-6,Board.y,"burst5.bmp");
		if(burst==6)
			iShowBMP(Paddle.px-6,Board.y,"burst6.bmp");			
	}

	iShowBMP(524,0,"left part.bmp");
}

void show_icons(void)
{
	if(Expand_Paddle.flag==on)
        iShowBMP(Expand_Paddle.X,Expand_Paddle.Y,"expand.bmp");	

	if(Shrink_Paddle.flag==on)
        iShowBMP(Shrink_Paddle.X,Shrink_Paddle.Y,"Shrink_Paddle.bmp");

	if(Expand_Ball.flag==on)
        iShowBMP(Expand_Ball.X,Expand_Ball.Y,"Expand_Ball.bmp");

	if(Shrink_Ball.flag==on)
        iShowBMP(Shrink_Ball.X,Shrink_Ball.Y,"Shrink_Ball.bmp");

	if(Gun_Icon.flag==on)
        iShowBMP(Gun_Icon.X,Gun_Icon.Y,"Gun_Icon.bmp");

	if(Slow_Ball.flag==on)
        iShowBMP(Slow_Ball.X,Slow_Ball.Y,"Slow_Ball.bmp");

	if(Fast_Ball.flag==on)
        iShowBMP(Fast_Ball.X,Fast_Ball.Y,"Fast_Ball.bmp");

	if(Ball_Through_Brick.flag==on)
        iShowBMP(Ball_Through_Brick.X,Ball_Through_Brick.Y,"Ball_Through_Brick.bmp");
	if(Kill_Paddle.flag==on)
        iShowBMP(Kill_Paddle.X,Kill_Paddle.Y,"Kill_Paddle.bmp");
}

void show_score(void)
{
	iShowBMP(540,425,"score.bmp"); 

	Score.score+=Score.hits*50;
    Score.hits=0;
	sprintf(BOARD,"%d",board+1);

    if(Score.score==0)
		sprintf(Score.scoreStr,"000000");
	else if(Score.score<10)
		sprintf(Score.scoreStr,"00000%d",Score.score);
	else if(Score.score<100)
		sprintf(Score.scoreStr,"0000%d",Score.score);
	else if(Score.score<1000)
		sprintf(Score.scoreStr,"000%d",Score.score);
	else if(Score.score<10000)
		sprintf(Score.scoreStr,"00%d",Score.score);
	else if(Score.score<100000)
		sprintf(Score.scoreStr,"0%d",Score.score);
	else 
		sprintf(Score.scoreStr,"%d",Score.score);

	iSetcolor(1,0,0);
    iText(570,396,Score.scoreStr,GLUT_BITMAP_TIMES_ROMAN_24);

	iSetcolor(1,1,1);	
	iText(570,78,"Board -",GLUT_BITMAP_9_BY_15);
	iText(639,78,BOARD,GLUT_BITMAP_9_BY_15);
}

void show_gun(void)
{
	if(Gun.flag==on)
	{
		iSetcolor(.5,.5,.5);
		iFilledRectangle(Paddle.px-4,Board.y+Paddle.hight,5,10);
		iFilledRectangle(Paddle.px+Paddle.len-1,Board.y+Paddle.hight,5,10);

		iSetcolor(0,1,1);
		iText(578,150,"Bullet",GLUT_BITMAP_9_BY_15);
	
		int x=548,y=130;
		
		for(int i=1;i<=Gun.bullets;i++)
		{
			iSetcolor(1,0,0);
			iFilledRectangle(x,y,2,10);

			x+=6;
		}
	}

	if(Gun.bulletFlag[0]==on)				// first set of bullets
    {    
		double x00[3],y00[3],x01[3],y01[3];

		x00[0]=Gun.bulletX[0];
		x00[1]=Gun.bulletX[0]-3;
		x00[2]=Gun.bulletX[0]+3;
		y00[0]=Gun.bulletY[0];
		y00[1]=Gun.bulletY[0]-10;
		y00[2]=Gun.bulletY[0]-10;

		x01[0]=Gun.bulletX[0]+Paddle.len+3;
		x01[1]=Gun.bulletX[0]-3+Paddle.len+3;
		x01[2]=Gun.bulletX[0]+3+Paddle.len+3;
		y01[0]=Gun.bulletY[0];
		y01[1]=Gun.bulletY[0]-10;
		y01[2]=Gun.bulletY[0]-10;

        iSetcolor(1,0,0); 
		if(Gun.bulletFlag12[0][0]==on)
			iFilledPolygon(x00,y00,3);	// left bullet of the first set
		if(Gun.bulletFlag12[0][1]==on)
			iFilledPolygon(x01,y01,3);  // right bullet of the first set      
    }    

    if(Gun.bulletFlag[1]==on)			// second set of bullets
    { 
        double x10[3],y10[3],x11[3],y11[3];

		x10[0]=Gun.bulletX[1];
		x10[1]=Gun.bulletX[1]-3;
		x10[2]=Gun.bulletX[1]+3;
		y10[0]=Gun.bulletY[1];
		y10[1]=Gun.bulletY[1]-10;
		y10[2]=Gun.bulletY[1]-10;

		x11[0]=Gun.bulletX[1]+Paddle.len+3;
		x11[1]=Gun.bulletX[1]-3+Paddle.len+3;
		x11[2]=Gun.bulletX[1]+3+Paddle.len+3;
		y11[0]=Gun.bulletY[1];
		y11[1]=Gun.bulletY[1]-10;
		y11[2]=Gun.bulletY[1]-10;
		
		iSetcolor(1,0,0);	
		if(Gun.bulletFlag12[1][0]==on)
			iFilledPolygon(x10,y10,3);
		if(Gun.bulletFlag12[1][1]==on)
			iFilledPolygon(x11,y11,3);
    } 
    if(Gun.bulletFlag[2]==on)			// third set of bullets
    {  
        double x20[3],y20[3],x21[3],y21[3];

		x20[0]=Gun.bulletX[2];
		x20[1]=Gun.bulletX[2]-3;
		x20[2]=Gun.bulletX[2]+3;
		y20[0]=Gun.bulletY[2];
		y20[1]=Gun.bulletY[2]-10;
		y20[2]=Gun.bulletY[2]-10;

		x21[0]=Gun.bulletX[2]+Paddle.len+3;
		x21[1]=Gun.bulletX[2]-3+Paddle.len+3;
		x21[2]=Gun.bulletX[2]+3+Paddle.len+3;
		y21[0]=Gun.bulletY[2];
		y21[1]=Gun.bulletY[2]-10;
		y21[2]=Gun.bulletY[2]-10;

		iSetcolor(1,0,0);
		if(Gun.bulletFlag12[2][0]==on)
			iFilledPolygon(x20,y20,3);
		if(Gun.bulletFlag12[2][1]==on)
			iFilledPolygon(x21,y21,3);
    } 
    if(Gun.bulletFlag[3]==on)			// fourth set of bullets
    { 
        double x30[3],y30[3],x31[3],y31[3];

		x30[0]=Gun.bulletX[3];
		x30[1]=Gun.bulletX[3]-3;
		x30[2]=Gun.bulletX[3]+3;
		y30[0]=Gun.bulletY[3];
		y30[1]=Gun.bulletY[3]-10;
		y30[2]=Gun.bulletY[3]-10;

		x31[0]=Gun.bulletX[3]+Paddle.len+3;
		x31[1]=Gun.bulletX[3]-3+Paddle.len+3;
		x31[2]=Gun.bulletX[3]+3+Paddle.len+3;
		y31[0]=Gun.bulletY[3];
		y31[1]=Gun.bulletY[3]-10;
		y31[2]=Gun.bulletY[3]-10;
		
		iSetcolor(1,0,0);	
		if(Gun.bulletFlag12[3][0]==on)
			iFilledPolygon(x30,y30,3);
		if(Gun.bulletFlag12[3][1]==on)
			iFilledPolygon(x31,y31,3);
    } 
}

void show_paddle(void)
{
	if(Paddle.flag==on)
	{
		
		if(Paddle.px>517-Paddle.len)
			Paddle.px=517-Paddle.len;
		
		if(Gun.flag==off)
			iSetcolor(.4,1,1);  
		else
			iSetcolor(1,.3,.2); 
		iFilledCircle(Paddle.px,(Board.y+(Paddle.hight/2)),5);
		iFilledCircle(Paddle.px+Paddle.len,(Board.y+(Paddle.hight/2)),5);
        iSetcolor(.5,.5,.5);
		iFilledRectangle(Paddle.px,Board.y,Paddle.len,Paddle.hight);
        
		if(fire%4==0||fire%4==1)
		{
			iSetcolor(.8,.8,.8);			// stripes on the paddle
			iFilledRectangle(Paddle.px,Board.y+1,Paddle.len,2);
			iSetcolor(1,1,1);
			iFilledRectangle(Paddle.px,Board.y+6,Paddle.len,2);
			iSetcolor(.8,.8,.8);
			iFilledRectangle(Paddle.px,Board.y+11,Paddle.len,2);
		}
		else if(fire%4==2||fire%4==3)
		{
			iSetcolor(1,1,1);				// stripes on the paddle
			iFilledRectangle(Paddle.px,Board.y+1,Paddle.len,2);
			iSetcolor(.8,.8,.8);
			iFilledRectangle(Paddle.px,Board.y+6,Paddle.len,2);
			iSetcolor(1,1,1);
			iFilledRectangle(Paddle.px,Board.y+11,Paddle.len,2);
		}
	}
}

void show_ball(void)
{	 
	if(Ball.flag==on)
	{
		if(Ball_Through_Brick.through==on)
			iSetcolor(0,1,1); 
		else
			iSetcolor(.8,.8,.8);
		
		iFilledCircle(Ball.x,Ball.y,ballrad,200);
	}
}

void ball_brick_collision(void)
{
	int i,j;	

	for(j=0;j<brickSet;j++)
	{
		for(i=0;i<brickNo;i++)
		{	
			hitting_condition=0;
			if(Brick.Description.state[j][i]==on)
				check_hitting_condition(j,i);

			if(hitting_condition)
			{
				if((j==Gun_Icon.i)&&(i==Gun_Icon.j))
				{					
					Gun_Icon.flag=on;
					Gun_Icon.up=on;
					Gun_Icon.X=Ball.x;
					Gun_Icon.Y=Ball.y;
					Gun_Icon.initialY=Ball.y;						
				}   
				if((j==Expand_Paddle.i)&&(i==Expand_Paddle.j))
				{
					Expand_Paddle.flag=on; 						
					Expand_Paddle.up=on;
					Expand_Paddle.X=Ball.x;
					Expand_Paddle.Y=Ball.y;
					Expand_Paddle.initialY=Ball.y;						
				}     
				if((j==Shrink_Paddle.i)&&(i==Shrink_Paddle.j))
				{
					Shrink_Paddle.flag=on; 						
					Shrink_Paddle.up=on;
					Shrink_Paddle.X=Ball.x;
					Shrink_Paddle.Y=Ball.y;
					Shrink_Paddle.initialY=Ball.y;						
				}     
				if((j==Expand_Ball.i)&&(i==Expand_Ball.j))
				{
					Expand_Ball.flag=on; 						
					Expand_Ball.up=on;
					Expand_Ball.X=Ball.x;
					Expand_Ball.Y=Ball.y;
					Expand_Ball.initialY=Ball.y;						
				}   
				if((j==Shrink_Ball.i)&&(i==Shrink_Ball.j))
				{
					Shrink_Ball.flag=on; 						
					Shrink_Ball.up=on;
					Shrink_Ball.X=Ball.x;
					Shrink_Ball.Y=Ball.y;
					Shrink_Ball.initialY=Ball.y;						
				}   
				if((j==Slow_Ball.i)&&(i==Slow_Ball.j))
				{
					Slow_Ball.flag=on; 						
					Slow_Ball.up=on;
					Slow_Ball.X=Ball.x;
					Slow_Ball.Y=Ball.y;
					Slow_Ball.initialY=Ball.y;						
				} 
				if((j==Fast_Ball.i)&&(i==Fast_Ball.j))
				{
					Fast_Ball.flag=on; 						
					Fast_Ball.up=on;
					Fast_Ball.X=Ball.x;
					Fast_Ball.Y=Ball.y;
					Fast_Ball.initialY=Ball.y;						
				} 
				if((j==Ball_Through_Brick.i)&&(i==Ball_Through_Brick.j))
				{
					Ball_Through_Brick.flag=on; 						
					Ball_Through_Brick.up=on;
					Ball_Through_Brick.X=Ball.x;
					Ball_Through_Brick.Y=Ball.y;
					Ball_Through_Brick.initialY=Ball.y;						
				} 
				if((j==Kill_Paddle.i)&&(i==Kill_Paddle.j))
				{
					Kill_Paddle.flag=on; 						
					Kill_Paddle.up=on;
					Kill_Paddle.X=Ball.x;
					Kill_Paddle.Y=Ball.y;
					Kill_Paddle.initialY=Ball.y;						
				} 
				if(Ball_Through_Brick.through==off)
				{
					if(hitting_condition==1)
						Ball.dy=-Ball.dy;
					else if(hitting_condition==2)
						Ball.dx=-Ball.dx;
				}

				Brick.Description.state[j][i]=off;
				Brick.brickLeft--;				
				Score.hits++;
				check_board();
			}   		
		}
	}
}

void bullet_brick_collision(void)
{
	int i,j,k;

	for(j=0;j<brickSet;j++)				// loop for rows of bricks
	{
		for(i=0;i<brickNo;i++)			// loop for columns of bricks
        {
			for(k=0;k<4;k++)			// There are 4 sets of bullets
            {
				if((Gun.bulletX[k]>=(Brick.x + brickWidth*i ))&&(Gun.bulletX[k]<(Brick.x+ brickWidth*(i+1) ))&&(Gun.bulletFlag12[k][0]==on)&&(Brick.Description.state[j][i]==on)&&(Gun.bulletY[k]>=(Brick.y[j]))&&(Gun.bulletY[k]<(Brick.y[j]+brickHigh)))
				{
					Brick.Description.state[j][i]=off;
					Gun.bulletFlag12[k][0]=off;
					Brick.brickLeft--;
					Gun.bullets--;
					Score.hits++;
					check_board();
					if(Gun.bullets<1)
						Gun.flag=off;
				}
				if((Gun.bulletX[k]+Paddle.len>=(Brick.x + brickWidth*i ))&&(Gun.bulletX[k]+Paddle.len<(Brick.x+ brickWidth*(i+1)  ))&&(Gun.bulletFlag12[k][1]==on)&&(Brick.Description.state[j][i]==on)&&(Gun.bulletY[k]>=(Brick.y[j]))&&(Gun.bulletY[k]<(Brick.y[j]+brickHigh)))
				{
					Brick.Description.state[j][i]=off;
					Gun.bulletFlag12[k][1]=off;
					Brick.brickLeft--;	
					Gun.bullets--;
					Score.hits++;
					check_board();

					if(Gun.bullets<1)
						Gun.flag=off;
				}
			}				      
		} 
	}
}

void move_bullet(void)
{   
	if(pause==off)
	{
		if(Gun.bulletY[0]>=Board.hight+Board.y-10)
		{
			Gun.bulletFlag[0]=off;   
			Gun.bulletFlag12[0][0]=off;
			Gun.bulletFlag12[0][1]=off;
		}
		
		else if(Gun.bulletFlag[0]==on)
			Gun.bulletY[0]+=15;        
		
		if(Gun.bulletY[1]>=Board.hight-10+Board.y)
		{
			Gun.bulletFlag[1]=off;   
			Gun.bulletFlag12[1][0]=off;
			Gun.bulletFlag12[1][1]=off;
		}
		
		else if(Gun.bulletFlag[1]==on)
			Gun.bulletY[1]+=15; 
		
		if(Gun.bulletY[2]>=Board.hight-10+Board.y)
		{
			Gun.bulletFlag[2]=off;    
			Gun.bulletFlag12[2][0]=off;
			Gun.bulletFlag12[2][1]=off;
		}
		
		else if(Gun.bulletFlag[2]==on)
			Gun.bulletY[2]+=15; 
		
		if(Gun.bulletY[3]>=Board.hight-10+Board.y)
		{
			Gun.bulletFlag[3]=off;    
			Gun.bulletFlag12[3][0]=off;
			Gun.bulletFlag12[3][1]=off;
		}
	
		else if(Gun.bulletFlag[3]==on)
			Gun.bulletY[3]+=15; 		
	}	   
	
	bullet_brick_collision();	
}

void move_icons(void)
{
	if(pause==off&&screen==2)		
	{
		if(Expand_Paddle.flag==on)								// if expand icon is displayed then
		{
			if(Expand_Paddle.Y<Board.y)							// if the icon is out of screen then stop displaying
				Expand_Paddle.flag=off;	
			
			if(Expand_Paddle.Y>Board.y+Board.hight-36)			// if the icon is out of screen then stop displaying
			{
				Expand_Paddle.up=off;
				Expand_Paddle.down=on;
			}

			if(Expand_Paddle.up==on)							// first go Expand_Paddle.up
			{
				Expand_Paddle.Y+=Expand_Paddle.dy;				// Expand_Paddle.Y is the y cordinate of the icon

				if(Expand_Paddle.Y>=Expand_Paddle.initialY+200)	// Expand_Paddle.initialY is the position from where the icon starts displaying
				{
					Expand_Paddle.up=off;
					Expand_Paddle.down=on;
				}
			}

			else if(Expand_Paddle.down==on)						// if it's not possible to go up, then go down		
			{
				Expand_Paddle.Y-=Expand_Paddle.dy+2;
			}

			Expand_Paddle.X-=Expand_Paddle.dx;
			
			if((Expand_Paddle.X<=Board.x)||(Expand_Paddle.X>=Board.len+Board.x-36))Expand_Paddle.dx=-Expand_Paddle.dx;// 36 is expand icon length
			
			if((Expand_Paddle.X>=Paddle.px-30)&&(Expand_Paddle.X<=Paddle.px+Paddle.len-1)&&(Expand_Paddle.Y>Board.y-10)&&(Expand_Paddle.Y<=Board.y+Paddle.hight))
			{
				Expand_Paddle.flag=off;
				Paddle.len+=Paddle.dLen;
				Score.score+=200;				
			}			
		}
		


		if(Shrink_Paddle.flag==on)							
		{
			if(Shrink_Paddle.Y<Board.y)						
				Shrink_Paddle.flag=off;	
			
			if(Shrink_Paddle.Y>Board.y+Board.hight-32)		
			{
				Shrink_Paddle.up=off;
				Shrink_Paddle.down=on;
			}
		
			if(Shrink_Paddle.up==on)						
			{
				Shrink_Paddle.Y+=Shrink_Paddle.dy;				

				if(Shrink_Paddle.Y>=Shrink_Paddle.initialY+200)	
				{
					Shrink_Paddle.up=off;
					Shrink_Paddle.down=on;
				}
			}
			else if(Shrink_Paddle.down==on)			
			{
				Shrink_Paddle.Y-=Shrink_Paddle.dy+2;
			}

			Shrink_Paddle.X-=Shrink_Paddle.dx;
			
			if((Shrink_Paddle.X<=Board.x)||(Shrink_Paddle.X>=Board.len+Board.x-36))Shrink_Paddle.dx=-Shrink_Paddle.dx;// 36 is expand icon length
			
			if((Shrink_Paddle.X>=Paddle.px-30)&&(Shrink_Paddle.X<Paddle.px+Paddle.len-1)&&(Shrink_Paddle.Y>Board.y-10)&&(Shrink_Paddle.Y<=Board.y+Paddle.hight))
			{
				Shrink_Paddle.flag=off;
				Paddle.len-=Paddle.dLen;
				Score.score+=200;				
			}			
		}
		


		if(Gun_Icon.flag==on)							
		{
			if(Gun_Icon.Y<Board.y)							
				Gun_Icon.flag=off;	
			
			if(Gun_Icon.Y>Board.y+Board.hight-32)			
			{
				Gun_Icon.up=off;
				Gun_Icon.down=on;
			}

			if(Gun_Icon.up==on)							
			{		
				Gun_Icon.Y+=Gun_Icon.dy;					

				if(Gun_Icon.Y>=Gun_Icon.initialY+200)		
				{
					Gun_Icon.up=off;
					Gun_Icon.down=on;
				}
			}

			else if(Gun_Icon.down==on)						
			{
				Gun_Icon.Y-=Gun_Icon.dy+2;
			}

			Gun_Icon.X-=Gun_Icon.dx;
			
			if((Gun_Icon.X<=Board.x)||(Gun_Icon.X>=Board.len+Board.x-36))Gun_Icon.dx=-Gun_Icon.dx;// 36 is expand icon length
			
			if((Gun_Icon.X>=Paddle.px-30)&&(Gun_Icon.X<=Paddle.px+Paddle.len-1)&&(Gun_Icon.Y>Board.y-10)&&(Gun_Icon.Y<=Board.y+Paddle.hight))
			{
				Gun_Icon.flag=off;
				Gun.flag=on;
				Score.score+=200;
			}
		}

	


		if(Expand_Ball.flag==on)						
		{
			if(Expand_Ball.Y<Board.y)						
				Expand_Ball.flag=off;	
			
			if(Expand_Ball.Y>Board.y+Board.hight-32)		
			{
				Expand_Ball.up=off;
				Expand_Ball.down=on;
			}

			if(Expand_Ball.up==on)							
			{
				Expand_Ball.Y+=Expand_Ball.dy;				

				if(Expand_Ball.Y>=Expand_Ball.initialY+200)	
				{
					Expand_Ball.up=off;
					Expand_Ball.down=on;
				}
			}
			else if(Expand_Ball.down==on)					
			{
				Expand_Ball.Y-=Expand_Ball.dy+2;
			}

			Expand_Ball.X-=Expand_Ball.dx;
			
			if((Expand_Ball.X<=Board.x)||(Expand_Ball.X>=Board.len+Board.x-36))Expand_Ball.dx=-Expand_Ball.dx;// 36 is expand icon length
			//checking for paddle
			if((Expand_Ball.X>=Paddle.px-30)&&(Expand_Ball.X<=Paddle.px+Paddle.len-1)&&(Expand_Ball.Y>Board.y-10)&&(Expand_Ball.Y<=Board.y+Paddle.hight))
			{
				Expand_Ball.flag=off;
				ballrad=6;
				Score.score+=200;
			}
		}
		


		if(Shrink_Ball.flag==on)							
		{
			if(Shrink_Ball.Y<Board.y)							
				Shrink_Ball.flag=off;		
			
			if(Shrink_Ball.Y>Board.y+Board.hight-32)		
			{
				Shrink_Ball.up=off;
				Shrink_Ball.down=on;
			}

			if(Shrink_Ball.up==on)							
			{
				Shrink_Ball.Y+=Shrink_Ball.dy;				

				if(Shrink_Ball.Y>=Shrink_Ball.initialY+200)	
				{
					Shrink_Ball.up=off;
					Shrink_Ball.down=on;
				}
			}
			else if(Shrink_Ball.down==on)						
			{
				Shrink_Ball.Y-=Shrink_Ball.dy+2;
			}

			Shrink_Ball.X-=Shrink_Ball.dx;
			
			if((Shrink_Ball.X<=Board.x)||(Shrink_Ball.X>=Board.len+Board.x-36))Shrink_Ball.dx=-Shrink_Ball.dx;// 36 is expand icon length
			//checking for paddle
			if((Shrink_Ball.X>=Paddle.px-30)&&(Shrink_Ball.X<=Paddle.px+Paddle.len-1)&&(Shrink_Ball.Y>Board.y-10)&&(Shrink_Ball.Y<=Board.y+Paddle.hight))
			{
				Shrink_Ball.flag=off;
				ballrad=3;
				Score.score+=200;
			}
		}
		


		if(Slow_Ball.flag==on)							
		{
			if(Slow_Ball.Y<Board.y)					
				Slow_Ball.flag=off;	
			
			if(Slow_Ball.Y>Board.y+Board.hight-32)					
			{
				Slow_Ball.up=off;
				Slow_Ball.down=on;
			}

			if(Slow_Ball.up==on)						
			{
				Slow_Ball.Y+=Slow_Ball.dy;				

				if(Slow_Ball.Y>=Slow_Ball.initialY+200)	
				{
					Slow_Ball.up=off;
					Slow_Ball.down=on;
				}
			}
			else if(Slow_Ball.down==on)				
			{
				Slow_Ball.Y-=Slow_Ball.dy+2;
			}

			Slow_Ball.X-=Slow_Ball.dx;
			
			if((Slow_Ball.X<=Board.x)||(Slow_Ball.X>=Board.len+Board.x-36))Slow_Ball.dx=-Slow_Ball.dx;// 36 is expand icon length
			//checking for paddle
			if((Slow_Ball.X>=Paddle.px-30)&&(Slow_Ball.X<=Paddle.px+Paddle.len-1)&&(Slow_Ball.Y>Board.y-10)&&(Slow_Ball.Y<=Board.y+Paddle.hight))
			{				
				Slow_Ball.flag=off;
				Ball.speed=-2;
			
				if(Ball.dy>0)
					Ball.dy+=Ball.speed;
				else
					Ball.dy-=Ball.speed;
				if(Ball.dx>0)
					Ball.dx+=Ball.speed;
				else
					Ball.dx-=Ball.speed;
				Score.score+=200;
			}
		}
		


		if(Fast_Ball.flag==on)							
		{
			if(Fast_Ball.Y<Board.y)						
				Fast_Ball.flag=off;	
			
			if(Fast_Ball.Y>Board.y+Board.hight-32)			
			{
				Fast_Ball.up=off;
				Fast_Ball.down=on;
			}

			if(Fast_Ball.up==on)						
			{
				Fast_Ball.Y+=Fast_Ball.dy;				

				if(Fast_Ball.Y>=Fast_Ball.initialY+200)	
				{
					Fast_Ball.up=off;
					Fast_Ball.down=on;
				}
			}
			else if(Fast_Ball.down==on)				
			{
				Fast_Ball.Y-=Fast_Ball.dy+2;
			}

			Fast_Ball.X-=Fast_Ball.dx;
			
			if((Fast_Ball.X<=Board.x)||(Fast_Ball.X>=Board.len+Board.x-36))Fast_Ball.dx=-Fast_Ball.dx;// 36 is expand icon length
			//checking for paddle
			if((Fast_Ball.X>=Paddle.px-30)&&(Fast_Ball.X<=Paddle.px+Paddle.len-1)&&(Fast_Ball.Y>Board.y-10)&&(Fast_Ball.Y<=Board.y+Paddle.hight))
			{			
				Fast_Ball.flag=off;
				Ball.speed=2;
				if(Ball.dy>0)
					Ball.dy+=Ball.speed;
				else
					Ball.dy-=Ball.speed;
				if(Ball.dx>0)
					Ball.dx+=Ball.speed;
				else
					Ball.dx-=Ball.speed;
				Score.score+=200;
			}
		}
	


		if(Ball_Through_Brick.flag==on)							
		{
			if(Ball_Through_Brick.Y<Board.y)					
				Ball_Through_Brick.flag=off;	
			
			if(Ball_Through_Brick.Y>Board.y+Board.hight-32)		
			{
				Ball_Through_Brick.up=off;
				Ball_Through_Brick.down=on;
			}

			if(Ball_Through_Brick.up==on)						
			{
				Ball_Through_Brick.Y+=Ball_Through_Brick.dy;			

				if(Ball_Through_Brick.Y>=Ball_Through_Brick.initialY+200)	
				{
					Ball_Through_Brick.up=off;
					Ball_Through_Brick.down=on;
				}
			}
			else if(Ball_Through_Brick.down==on)				
			{
				Ball_Through_Brick.Y-=Ball_Through_Brick.dy+2;
			}

			Ball_Through_Brick.X-=Ball_Through_Brick.dx;
			
			if((Ball_Through_Brick.X<=Board.x)||(Ball_Through_Brick.X>=Board.len+Board.x-36))Ball_Through_Brick.dx=-Ball_Through_Brick.dx;// 36 is expand icon length
			//checking for paddle
			if((Ball_Through_Brick.X>=Paddle.px-30)&&(Ball_Through_Brick.X<=Paddle.px+Paddle.len-1)&&(Ball_Through_Brick.Y>Board.y-10)&&(Ball_Through_Brick.Y<=Board.y+Paddle.hight))
			{
				Ball_Through_Brick.flag=off;
				Ball_Through_Brick.through=on;
			}
		}


	
		if(Kill_Paddle.flag==on)							
		{
			if(Kill_Paddle.Y<Board.y)						
				Kill_Paddle.flag=off;	
			
			if(Kill_Paddle.Y>Board.y+Board.hight-32)		
			{
				Kill_Paddle.up=off;
				Kill_Paddle.down=on;
			}

			if(Kill_Paddle.up==on)						
			{
				Kill_Paddle.Y+=Kill_Paddle.dy;				

				if(Kill_Paddle.Y>=Kill_Paddle.initialY+200)	
				{
					Kill_Paddle.up=off;
					Kill_Paddle.down=on;
				}
			}
			else if(Kill_Paddle.down==on)				
			{
				Kill_Paddle.Y-=Kill_Paddle.dy+2;
			}

			Kill_Paddle.X-=Kill_Paddle.dx;
			
			if((Kill_Paddle.X<=Board.x)||(Kill_Paddle.X>=Board.len+Board.x-36))Kill_Paddle.dx=-Kill_Paddle.dx;// 36 is expand icon length
			//checking for paddle
			if((Kill_Paddle.X>=Paddle.px-30)&&(Kill_Paddle.X<=Paddle.px+Paddle.len-1)&&(Kill_Paddle.Y>Board.y-10)&&(Kill_Paddle.Y<=Board.y+Paddle.hight))
			{
				Kill_Paddle.flag=off;
				flagBurst=on;
				off_flags();
			}
		}
	}
}

void move_ball(void)
{	
	if(pause==off&&screen==2)
	{	
		if(start==off)								
		{
			Ball.x=Paddle.px+(Paddle.len/2);
			Ball.y=Board.y+Paddle.hight+ballrad;
		}

		else if(start==on&&Ball.flag==on)			
		{
			Ball.x=Ball.dx + Ball.x;
			Ball.y=Ball.y + Ball.dy;    
        
			// checking left/ right boundary
			if((Ball.x<=ballrad+Board.x+2)||(Ball.x>=Board.len+Board.x-ballrad-2))Ball.dx=-Ball.dx;   

			 // checking top boundary
			if(Ball.y>=Board.hight+Board.y-ballrad)Ball.dy=-Ball.dy;   

			if(Ball.y<=Paddle.hight+Board.y+ballrad+2)
			{
				if((Ball.x>=Paddle.px)&&(Ball.x<Paddle.px+(Paddle.len/8)*1))
				{
					Ball.dy=4+Ball.speed;		//21.8 degree
					Ball.dx=-7-Ball.speed;
				}
				else if((Ball.x>=Paddle.px+(Paddle.len/8)*7)&&(Ball.x<=Paddle.px+Paddle.len))
				{
					Ball.dy=4+Ball.speed;		//21.8
					Ball.dx=7+Ball.speed;
				}
				
				else if((Ball.x>Paddle.px+(Paddle.len/8)*1)&&(Ball.x<Paddle.px+(Paddle.len/8)*2))
				{
					Ball.dy=6+Ball.speed;		//36.66
					Ball.dx=-7-Ball.speed;
				}
				else if((Ball.x>Paddle.px+(Paddle.len/8)*6)&&(Ball.x<Paddle.px+(Paddle.len/8)*7))
				{
					Ball.dy=6+Ball.speed;		//36.66
					Ball.dx=7+Ball.speed;
				}
				
				else if((Ball.x>=Paddle.px+(Paddle.len/8)*2)&&(Ball.x<Paddle.px+(Paddle.len/8)*3))
				{
					Ball.dy=5+Ball.speed;		//51.34
					Ball.dx=-4-Ball.speed;
				}
				else if((Ball.x>=Paddle.px+(Paddle.len/8)*5)&&(Ball.x<=Paddle.px+(Paddle.len/8)*6))
				{
					Ball.dy=7+Ball.speed;		//51.34
					Ball.dx=4+Ball.speed;
				}
				
				else if((Ball.x>Paddle.px+(Paddle.len/8)*3)&&(Ball.x<Paddle.px+(Paddle.len/8)*5))
				{
					Ball.dy=7+Ball.speed;		//68.19
					if(Ball.dx<0)
						Ball.dx=-4-Ball.speed;
					else
						Ball.dx=4+Ball.speed;
				}
			}				
			
			else if((Ball.y<=Paddle.hight+Board.y+ballrad-2)&&(Ball.y>=Board.y+Paddle.hight/2/*+3 */)&&(((Ball.x>=Paddle.px-5-ballrad)&&(Ball.x<Paddle.px))))
			{
				Ball.dy=1;
				if(Ball.dx>0)
					Ball.dx=-7-Ball.speed;
				else
					Ball.dx=-7-Ball.speed;

			}
			else if((Ball.y<=Paddle.hight+Board.y+ballrad-2)&&(Ball.y>=Board.y+Paddle.hight/2/*+3 */)&&(((Ball.x<=Paddle.px+Paddle.len+5+ballrad)&&(Ball.x>Paddle.px+Paddle.len))))
			{
				Ball.dy=1;
				if(Ball.dx>0)
					Ball.dx=7+Ball.speed;
				else
					Ball.dx=7+Ball.speed;
			}
			
			if(Ball.y<Board.y+ballrad)
			{
				flagBurst=on;
				off_flags();				
			}

			ball_brick_collision();	
		}
	}   
}

void burst_paddle(void)
{
	if(flagBurst==on)
		burst++;

	if(burst>15)
	{
		burst=0;
		flagBurst=off;
	
		initialize();
		Paddle.life--;

		if(Paddle.life==0)esc_blink=0;
			
		if(Paddle.life==0||board>5)
			check_record();		
	}
}

void shoot(void)
{
	if((pause==off)&&(Gun.flag==on))
    {    
		if(Gun.bulletFlag[0]==off)
        {    
			Gun.bulletFlag[0]=on;  
			Gun.bulletFlag12[0][0]=on;
			Gun.bulletFlag12[0][1]=on;
            Gun.bulletX[0]=Paddle.px-2;
            Gun.bulletY[0]=Board.y+Paddle.hight+8;
        }
        else if(Gun.bulletFlag[1]==off)
        {
            Gun.bulletFlag[1]=on; 
			Gun.bulletFlag12[1][0]=on;
			Gun.bulletFlag12[1][1]=on;
            Gun.bulletX[1]=Paddle.px-2;
            Gun.bulletY[1]=Board.y+Paddle.hight+8;
        }
        else if(Gun.bulletFlag[2]==off)
        {
            Gun.bulletFlag[2]=on; 
			Gun.bulletFlag12[2][0]=on;
			Gun.bulletFlag12[2][1]=on;
            Gun.bulletX[2]=Paddle.px-2;
            Gun.bulletY[2]=Board.y+Paddle.hight+8;
        }
        else if(Gun.bulletFlag[3]==off)
        {
            Gun.bulletFlag[3]=on;  
			Gun.bulletFlag12[3][0]=on;
			Gun.bulletFlag12[3][1]=on;
            Gun.bulletX[3]=Paddle.px-2;
            Gun.bulletY[3]=Board.y+Paddle.hight+8;
        }       
    }
}

void initialize_icons_position(void)
{
	srand(time(NULL)) ;

	Gun_Icon.i=rand()%brickSet;
	Gun_Icon.j=rand()%brickNo;

	Expand_Paddle.i=rand()%brickSet;
	Expand_Paddle.j=rand()%brickNo;

	Shrink_Paddle.i=rand()%brickSet;
	Shrink_Paddle.j=rand()%brickNo;

	Expand_Ball.i=rand()%brickSet;
	Expand_Ball.j=rand()%brickNo;

	Shrink_Ball.i=rand()%brickSet;
	Shrink_Ball.j=rand()%brickNo;

	Slow_Ball.i=rand()%brickSet;
	Slow_Ball.j=rand()%brickNo;

	Fast_Ball.i=rand()%brickSet;
	Fast_Ball.j=rand()%brickNo;

	Ball_Through_Brick.i=rand()%brickSet;
	Ball_Through_Brick.j=rand()%brickNo;

	Kill_Paddle.i=rand()%brickSet;
	Kill_Paddle.j=rand()%brickNo;
}

void off_flags(void)
{
	Ball.flag=off;	
	Paddle.flag=off;	
	Gun.flag=off;
	Gun_Icon.flag=off;
	Expand_Paddle.flag=off;
	Shrink_Paddle.flag=off;
	Expand_Ball.flag=off;
	Shrink_Ball.flag=off;
	Slow_Ball.flag=off;
	Ball_Through_Brick.flag=off;
	Ball_Through_Brick.through=off;
	Kill_Paddle.flag=off;
	start=off;
	About=off;
	Save=off;
	Keys=off;
	About=off;
	pause=off;
}

void show_life(void)
{
	int x=560,y=324,i;

	if(Paddle.life)
	{
		for(i=1;i<=Paddle.life;i++)
			if(Paddle.life>=1)
			{
				iShowBMP(x,y,"Life.bmp");
				y-=25;
			}
	}
}
void move_others(void)
{
	int i,x=0;

	if(screen==1||screen==4)
	{
		if(screen_y>0)
			screen_y-=5;
		if(screen_y<=0)
		{
			screen_y=0;

			for(i=0;i<90000000;i++)
			{
				x++;
			}

			if(screen==1)
				screen=2;
			else if(screen==4)
			{
				screen=3;
				Cursor.flag=on;
			}		
		}
	}
	
	if(Menu==on)
	{
		Menu_x-=10;

		if(Menu_x<516)
			Menu_x=516;		
	}
	else
	{
		if(Menu_x<700)
			Menu_x+=10;
		else if(Menu_x>700)
			Menu_x=700;	
	}
}

void check_board(void)
{
	int i,x=0;

	if(Brick.brickLeft==0&&board<=5)
	{
		
		for(i=0;i<100000000;i++)
			x++;
				
		screen_y=530;
		screen=1;
		board++;

		if(board>5||Paddle.life==0)
		{
			screen=4;
			check_record();
		}
		else
		{
			off_flags();
			initialize_icons_position();
			initialize();
			load_stage();
		}
	}
}

void show_board_selector(void)
{
	iShowBMP(0,0,"wm skin2.bmp");	
	iShowBMP(80,432,"Select_Board_Set.bmp");

	
	iSetcolor(1,1,1);
	iText(150,417,"Use arrows to select board and then press Enter",GLUT_BITMAP_8_BY_13);
	
	if(selector==1)
		iShowBMP(50,selector_y,"selector1.bmp");
	else if(selector==2)
		iShowBMP(50,selector_y,"selector2.bmp");
	else if(selector==3)
		iShowBMP(50,selector_y,"selector3.bmp");
	else if(selector==4)
		iShowBMP(50,selector_y,"selector4.bmp");
	else if(selector==5)
		iShowBMP(50,selector_y,"selector5.bmp");
	
	iSetcolor(.5,1,.5);
	iText(100,364,"Board-1",GLUT_BITMAP_HELVETICA_18);
	iSetcolor(.5,1,1);
	iText(100,364,"                                          Searching for Bucephalas",GLUT_BITMAP_TIMES_ROMAN_24);
	
	iSetcolor(.5,1,.5);
	iText(100,314,"Board-2",GLUT_BITMAP_HELVETICA_18);
	iSetcolor(.5,1,1);
	iText(100,314,"                                          Crab's Nest",GLUT_BITMAP_TIMES_ROMAN_24);
	
	iSetcolor(.5,1,.5);
	iText(100,264,"Board-3",GLUT_BITMAP_HELVETICA_18);
	iSetcolor(.5,1,1);
	iText(100,264,"                                          Metal Maze",GLUT_BITMAP_TIMES_ROMAN_24);
	
	iSetcolor(.5,1,.5);
	iText(100,214,"Board-4",GLUT_BITMAP_HELVETICA_18);
	iSetcolor(.5,1,1);
	iText(100,214,"                                          Journey to the Sun",GLUT_BITMAP_TIMES_ROMAN_24);
	
	iSetcolor(.5,1,.5);
	iText(100,164,"Board-5",GLUT_BITMAP_HELVETICA_18);
	iSetcolor(.5,1,1);
	iText(100,164,"                                          Expedition: Cornfed",GLUT_BITMAP_TIMES_ROMAN_24);
	
	
	iSetcolor(.5,1,.5);
	iText(100,114,"Board-6",GLUT_BITMAP_HELVETICA_18);
	iSetcolor(.5,1,1);
	iText(100,114,"                                          Hide and Glow Seek",GLUT_BITMAP_TIMES_ROMAN_24);
	
}
void move_selector(void)
{
	selector++;
	if(selector>5)
		selector=1;
}

void select_board(void)
{
	Paddle.life=3;
	Score.score=0;

	if(selector_y==350)
		board=0;
	else if(selector_y==300)
		board=1;
	else if(selector_y==250)
		board=2;
	else if(selector_y==200)
		board=3;
	else if(selector_y==150)
		board=4;
	else if(selector_y==100)
		board=5;

	if(Paddle.life==0)
	{					
		Paddle.life=3;	
		Score.score=0;
	}

	initialize_icons_position();
	initialize();
	load_stage();	

	screen++;
	selector_y=350;
}

void check_menu(void)
{
	if(name_flag==on)
	{
		if((Mx>=398&&Mx<=448)&&(My>=246&&My<=270&&(strlen(Cursor.name)!=0)))
		{			
			strcpy(Player.name,Cursor.name);
			insert_palyers_record();
			name_flag=off;
			Cursor.flag=off;
			save_record();
			strcpy(Cursor.name,"");
		}
	}

	if(Menu==off&&About==off&&Keys==off&&Save==off&&Load==off&&screen==2&&Paddle.life>0)
	{
	
		if(Mx<0||Mx>520||My<0||My>512)		
			pause=on;		
		
		else		
			pause=off;		
	}

	if(screen==2&&(Mx>=688&&Mx<=698)&&(My>=250&&My<=302))
	{
		if(Menu==on)
			Menu=off;
		else
			Menu=on;
	}
	
	if(Menu==on)
	{
		if((Mx>=538&&Mx<=654)&&(My>=122&&My<=150)&&Keys==off&&Save==off&&Load==off)
		{
			Menu=off;
			pre_about=on;
			show_pop_up_border();
			
		}

		else if((Mx>=538&&Mx<=654)&&(My>=197&&My<=225)&&About==off&&Save==off&&Load==off)
		{
			Menu=off;
			pre_keys=on;
			show_pop_up_border();			
		}

		else if((Mx>=538&&Mx<=654)&&(My>=352&&My<=380)&&About==off&&Keys==off&&Load==off)
		{
			Menu=off;
			pre_save=on;
			show_pop_up_border();	
			
			check_availability();

			if(total_saved_board<10)
			{
				strcpy(save_load_instruction,"Enter a name and click save");
			}
			else
			{
				strcpy(save_load_instruction,"Slot full.First delete a game");
			}
		}
		else if((Mx>=538&&Mx<=654)&&(My>=314&&My<=342)&&About==off&&Save==off&&Keys==off)
		{
			Menu=off;
			pre_load=on;
			show_pop_up_border();
			
			check_availability();

			if(total_saved_board>0)
			{
				strcpy(save_load_instruction,"Enter a serial to delete/load");
			}
			else
			{
				strcpy(save_load_instruction,"No game is available");
			}
		}

		else if((Mx>=538&&Mx<=654)&&(My>=160&&My<=188)&&About==off&&Keys==off&&Save==off&&Load==off)
		{
			Menu=off;			
			screen=3;			

			if(Paddle.life==0||board>5)
			{				
				check_record();
			}
			
		}

		else if((Mx>=538&&Mx<=654)&&(My>=277&&My<=305)&&About==off&&Save==off&&Load==off&&Keys==off)
		{
			Menu=off;
			restart_game();
		}
	}

	else if(About==on||Keys==on)
	{
		if((Mx>=357&&Mx<=406)&&(My>=172&&My<=182))
		{
			About=off;
			Keys=off;
		}
	}	
	else if(Save==on)
	{	

		if((Mx>=296&&Mx<=346)&&(My>=120&&My<=130))
		{
			Save=off;
			strcpy(Cursor.name,"");
		}
		else if((Mx>=210&&Mx<=260)&&(My>=120&&My<=130))
		{
			if(total_saved_board<10)
			{
				if(strlen(Cursor.name)==0)
					strcpy(save_load_instruction,"You must enter a name");
				else
				{
					strcpy(Cursor.game_name,Cursor.name);
					save_game();
					Save=off;
					strcpy(Cursor.name,"");
				}
			}
		}

	}	
	else if(Load==on)
	{
		if((Mx>=326&&Mx<=376)&&(My>=120&&My<=130))
		{
			Load=off;//cancel
			strcpy(Cursor.name,"");
		}
		else if((Mx>=253&&Mx<=303)&&(My>=120&&My<=130))//laod =253,120//303,130
		{
			if(total_saved_board>0)
			{
				int serial=atoi(Cursor.name);

				if(serial>=1&&serial<=total_saved_board)
				{
					load_game(serial);
					Load=off;
					strcpy(Cursor.name,"");
				}

				else
					strcpy(save_load_instruction,"Enter a valid seriel(1,2..)");
				}

		}		
		
		else if((Mx>=180&&Mx<=230)&&(My>=120&&My<=130))//delete = 180,120//230,130
		{
			if(total_saved_board>0)
			{
				int serial=atoi(Cursor.name);

				if(serial>=1&&serial<=total_saved_board)
				{
					delete_game(serial);
					Load=off;
					strcpy(Cursor.name,"");
				}

				else
					strcpy(save_load_instruction,"Enter a valid seriel(1-10)");
			}
		}
	}
}

void load_hall_of_fame(void)
{
	FILE* fp;

	fp=fopen("hall of fame.dat","rb");

	if(fp==NULL)
	{
		printf("Error");
		exit(1);
	}
	
	fread(&Fame_Name,sizeof(Fame_Name),1,fp);
	fclose(fp);
}

void insert_palyers_record(void)
{
	int i,x=0;
	int player_score,record_score;

	player_score=Score.score;
	sprintf(Player.score,"%d",Score.score);

	for(i=0;i<10;i++)
	{	
		record_score=atoi(Fame_Name[i].score);
					
		if(player_score>=record_score)
		{
			x++;

			if(x==1)
				Player_Index=i;

			temp=Fame_Name[i];
			Fame_Name[i]=Player;
			Player=temp;				
		}
	}
}

void restart_game(void)
{
	off_flags();
	Paddle.life=3;	
	Score.score=0;
	board=0;
	initialize_icons_position();
	initialize();
	load_stage();
}

void show_record(void)
{
	int i,x=292,y=429;
	for(i=0;i<10;i++)
	{
		if(i==Player_Index)
			iSetcolor(1,0,0);

		else
			iSetcolor(1,1,1);

		iText(x,y,Fame_Name[i].name,GLUT_BITMAP_HELVETICA_18);
		iText(x+250,y,Fame_Name[i].score,GLUT_BITMAP_HELVETICA_18);
		iShowBMP(x-40,y-10,"dxball.bmp");

		y-=40;
	}
}

void check_record(void)
{
	int player_score;

	player_score=atoi(Fame_Name[9].score);

	if(Score.score>=player_score)
	{
		name_flag=on;
		Cursor.flag=on;
		Cursor.x=267;
		Cursor.y=292;
	}
}

void blink_cursor(void)
{
	Cursor.blinker++;
	esc_blink++;	
}

void glow_brick(void)
{
	if(screen==2&&pause==off)
	{
		fire++;

		if(fire>4)
		{
			fire=1;
		}
	}
	else if(screen==-1)
	{		
		ball++;

		if(ball>4)
			ball=1;
	}
}

void show_cursor(void)
{
	int i;
	
	strcpy(Cursor.temp,Cursor.name);
	i=strlen(Cursor.name);
	Cursor.temp[i++]='|';
	Cursor.temp[i++]='\0';

	if(Cursor.blinker%2)	
	{
		if(screen==3)
			iSetcolor(1,1,1);
		else if(screen==2)
			iSetcolor(0,0,0);
		iText(Cursor.x,Cursor.y,Cursor.temp,GLUT_BITMAP_9_BY_15);
	}	
	
	if(screen==2)
		iSetcolor(0,0,0);
	else if(screen==3)
		iSetcolor(1,0,0);
	iText(Cursor.x,Cursor.y,Cursor.name,GLUT_BITMAP_9_BY_15);

}

void write(char key)
{
	if(Cursor.flag==on)
	{
		int k;
		k=strlen(Cursor.name);


		if(key==13)
			Cursor.name[k]='\0';
		
		else if(key==8)
			Cursor.name[k-1]='\0';
		
		else if(k<19&&key!=27)
		{		
			Cursor.name[k]=key;
			Cursor.name[k+1]='\0';						
		}
	}
}

void save_record(void)
{
	FILE* fp;

	fp=fopen("hall of fame.dat","wb");

	if(fp==NULL)
	{
		printf("Error");
		exit(1);
	}
	
	fwrite(&Fame_Name,sizeof(Fame_Name),1,fp);
	fclose(fp);
}

void check_hitting_condition(int j,int i)
{
	if((Ball.x>Brick.x+brickWidth*i)&&(Ball.x<=Brick.x+brickWidth*(i+1))&&((Ball.y>=(Brick.y[j]-ballrad))&&(Ball.y<=(Brick.y[j]+brickHigh+ballrad))))
		hitting_condition=1;
	
	else if(((((Ball.x>=Brick.x+brickWidth*i-ballrad)&&(Ball.x<=Brick.x+brickWidth*(i+1)))||((Ball.x<=Brick.x+brickWidth*(i+1)+ballrad)&&(Ball.x>Brick.x+brickWidth*(i+1))))&&(Ball.y>Brick.y[j]-ballrad+2)&&(Ball.y<Brick.y[j]+brickHigh+ballrad-2)))
	hitting_condition=2;
}

void show_starting_screen(void)
{
	iShowBMP(0,0,"Starting_Skin.bmp");
	
	iSetcolor(1,1,0);
	if(esc_blink>5)
	{
		if(esc_blink%3==0)
			iText(250,250,"Press Esc to continue",GLUT_BITMAP_9_BY_15);
	}

	if(ball==1)
		iShowBMP(450,60,"ball1.bmp");
	else if(ball==2)
		iShowBMP(450,60,"ball2.bmp");
	else if(ball==3)
		iShowBMP(450,60,"ball3.bmp");
	else 
		iShowBMP(450,60,"ball4.bmp");
}

void show_pop_up_border(void)
{
	pop_border=on;

	if(pre_about==on||pre_keys==on)
	{
		pop_x=128;
		pop_y=160;
	}
	else if(pre_save==on||pre_load==on)
	{
		pop_x=128;
		pop_y=101;
	}
	pop_len=0;
	pop_hight=0;
}
void move_pop_up_border(void)
{
	if(pop_border==on)
	{
		if(pre_about==on||pre_keys==on)
		{
			pop_len+=21;
			pop_hight+=14;
			if(pop_len>292)
				pop_len=292;
			if(pop_hight>202)
				pop_hight=202;
			if(pop_hight==202&&pop_len==292)
			{
				pop_border=off;
				if(pre_about==on)
				{
					pre_about=off;
					About=on;
				}
				else if(pre_keys==on)
				{
					pre_keys=off;
					Keys=on;
				}				
			}
		}

		else if(pre_save==on||pre_load==on)
		{
			pop_len+=21;
			pop_hight+=27;
			if(pop_len>292)
				pop_len=292;
			if(pop_hight>370)
				pop_hight=370;

			if(pop_hight==370&&pop_len==292)
			{
				pop_border=off;
				if(pre_save==on)
				{
					pre_save=off;
					Save=on;
				}
				else if(pre_load==on)
				{
					pre_load=off;
					Load=on;
				}

				Cursor.x=152;
				Cursor.y=147;
				Cursor.flag=on;
			}
		}
	}		
}

void show_game_screen(void)
{
	iShowBMP(0,0,"wm skin2.bmp");	// background screen		
	show_paddle_burst();	
	show_score();	
	show_stage();    
	show_icons();    
	show_gun();  		
	
	if(Paddle.life==0)
	{
		iShowBMP(115,370,"Game_Over.bmp");			
		if(esc_blink>5)
		{
			if(esc_blink%3==0)
			{
				iSetcolor(1,1,0);
				iText(180,350,"Press Esc to continue",GLUT_BITMAP_9_BY_15);
			}
		}
	}
	
	else
	{
		show_paddle();    
		show_ball();
		show_life();			
	}
	
	if(pause==on)
	{
		iSetcolor(0,1,1);	
		iText(560,108,"Game Paused",GLUT_BITMAP_9_BY_15);
	}
	
	if(About==on)
		iShowBMP(128,160,"About.bmp");

	else if(Keys==on)
		iShowBMP(128,160,"Keys.bmp");

	else if(Save==on)
		iShowBMP(128,101,"Save.bmp");
	
	else if(Load==on)
		iShowBMP(128,101,"Load.bmp");

	if(Save==on||Load==on)
	{
		iSetcolor(0,1,1);
		iText(145,172,save_load_instruction,GLUT_BITMAP_9_BY_15);
		show_saved_name();
	}
	
	iShowBMP(Menu_x,100,"Menu.bmp");
	iShowBMP(675,47,"Left_Line.bmp");
	
	if(pop_border==on)
	{
		iSetcolor(.5,1,1);
		iRectangle(pop_x,pop_y,pop_len,pop_hight);
	}

	if(Save==on||Load==on)
		show_cursor();
}

void show_record_screen(void)
{
	iShowBMP(0,0,"hall of fame.bmp");		
	show_record();

	if(name_flag==on)
	{
		iShowBMP(230,240,"enter name.bmp");
		show_cursor();
	}
}

void check_availability(void)
{
	FILE *fp;

	fp=fopen("saved game.dat","rb");
	if(fp==NULL)
	{
		printf("\nCan not open saved game.dat");
		exit(0);
	}

	fread(&total_saved_board,sizeof(total_saved_board),1,fp);
	printf("\ntotalboard=%d",total_saved_board);
	for(int i=0;i<total_saved_board;i++)
	{
		fread(&Save_Game[i],sizeof(Save_Game[i]),1,fp);
	}
	
	fclose(fp);	
}

void show_saved_name(void)
{
	int i=0,x=160,y=420;
	char serial[3],temp[3];	

	for(i=1;i<=total_saved_board;i++)
	{
		if(i<10)
		{
			sprintf(serial,"0");
			sprintf(temp,"%d",i);
			strcat(serial,temp);			
		}
		else
		{
			sprintf(serial,"%d",i);				
		}

		iSetcolor(0,1,1);
		iText(x,y,serial);
		iSetcolor(1,0,0);
		iText(x+40,y,Save_Game[i-1].name,GLUT_BITMAP_9_BY_15);
		y-=24;
	}	
}

void save_game(void)
{
	Save_Game[total_saved_board].board=board;
	Save_Game[total_saved_board].screen=screen;
	strcpy(Save_Game[total_saved_board].name,Cursor.game_name);
	Save_Game[total_saved_board].Paddle=Paddle;
	Save_Game[total_saved_board].Ball=Ball;
	Save_Game[total_saved_board].Gun=Gun;
	Save_Game[total_saved_board].Gun_Icon=Gun_Icon;
	Save_Game[total_saved_board].Expand_Paddle=Expand_Paddle;
	Save_Game[total_saved_board].Shrink_Paddle=Shrink_Paddle;
	Save_Game[total_saved_board].Expand_Ball=Expand_Ball;
	Save_Game[total_saved_board].Shrink_Ball=Shrink_Ball;
	Save_Game[total_saved_board].Slow_Ball=Slow_Ball;
	Save_Game[total_saved_board].Fast_Ball=Fast_Ball;
	Save_Game[total_saved_board].Ball_Through_Brick=Ball_Through_Brick;
	Save_Game[total_saved_board].Kill_Paddle=Kill_Paddle;
	Save_Game[total_saved_board].Score=Score;
	Save_Game[total_saved_board].Brick=Brick;

	total_saved_board++;

	FILE *fp;

	fp=fopen("saved game.dat","wb");

	if(fp==NULL)
	{
		printf("\nCan not open saved game.dat to save");
		exit(0);
	}

	fwrite(&total_saved_board,sizeof(total_saved_board),1,fp);

	for(int i=0;i<total_saved_board;i++)
	{
		fwrite(&Save_Game[i],sizeof(Save_Game[i]),1,fp);
	}
	
	fclose(fp);	
}

void load_game(int serial)
{
	off_flags();

	board=Save_Game[serial-1].board;
	screen=Save_Game[serial-1].screen;	
	Paddle=Save_Game[serial-1].Paddle;
	Ball=Save_Game[serial-1].Ball;
	Gun=Save_Game[serial-1].Gun;
	Gun_Icon=Save_Game[serial-1].Gun_Icon;
	Expand_Paddle=Save_Game[serial-1].Expand_Paddle;
	Shrink_Paddle=Save_Game[serial-1].Shrink_Paddle;
	Expand_Ball=Save_Game[serial-1].Expand_Ball;
	Shrink_Ball=Save_Game[serial-1].Shrink_Ball;
	Slow_Ball=Save_Game[serial-1].Slow_Ball;
	Fast_Ball=Save_Game[serial-1].Fast_Ball;
	Ball_Through_Brick=Save_Game[serial-1].Ball_Through_Brick;
	Kill_Paddle=Save_Game[serial-1].Kill_Paddle;
	Score=Save_Game[serial-1].Score;
	Brick=Save_Game[serial-1].Brick;
	pause=on;
	start=on;
}

void delete_game(int serial)
{
	total_saved_board--;

	for (int i=serial;i<=total_saved_board;i++)
	{
		Save_Game[i-1]=Save_Game[i];
	}
	
	FILE *fp;

	fp=fopen("saved game.dat","wb");

	if(fp==NULL)
	{
		printf("\nCan not open saved game.dat to save");
		exit(0);
	}

	fwrite(&total_saved_board,sizeof(total_saved_board),1,fp);

	for(i=0;i<total_saved_board;i++)
	{
		fwrite(&Save_Game[i],sizeof(Save_Game[i]),1,fp);
	}
	
	fclose(fp);	
}