#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#define SCR_WIDTH 100
#define SCR_HEIGHT 40
#define MAX_BULLETS 100

typedef struct
{
	int state_;
	int width_;
	int height_;
	int pos_x_;
	int pos_y_;
	int live; //생명 설정
	int p_position;
	char *image_;
}Object, *pObject, *eObject;
Object player;
Object enemy[300];

//Object *p_bullet = NULL;
pObject p_bullet_array[MAX_BULLETS];
eObject e_bullet_array[MAX_BULLETS];

int hp = 5;
int score;
char front_buffer[SCR_HEIGHT][SCR_WIDTH]; 
char back_buffer[SCR_HEIGHT][SCR_WIDTH];
void moveCursorTo(const short x, const short y);
int enemy_num = 1; //record enemy number
int time = 0;
int i, j;

void GameStart()
{

}

void GameExit()
{
	system("cls");
	for (int i = 0; i < 20; i++)
		printf("\n");
	printf("                                                    GMAE OVER\n");
}

void AddEnemy()
{
	if (score >= 20)
	{

		enemy[enemy_num].image_ = "*X_X*";
		enemy[enemy_num].width_ = 5;
		enemy[enemy_num].height_ = 1;
		enemy[enemy_num].pos_x_ = rand() % 99; //start random position
		enemy[enemy_num++].pos_y_ = SCR_HEIGHT - 3;
		enemy[enemy_num].live = 1;
	}

	else if (score >= 10)
	{
		enemy[enemy_num].image_ = "*-_-*";
		enemy[enemy_num].width_ = 5;
		enemy[enemy_num].height_ = 1;
		enemy[enemy_num].pos_x_ = rand() % 99; //start random position
		enemy[enemy_num++].pos_y_ = SCR_HEIGHT - 3;
		enemy[enemy_num].live = 1;
	}
	else
	{
		enemy[enemy_num].image_ = "*^A^*";
		enemy[enemy_num].width_ = 5; 
		enemy[enemy_num].height_ = 1;
		enemy[enemy_num].pos_x_ = rand() % 99; //start random position
		enemy[enemy_num++].pos_y_ = SCR_HEIGHT - 3;
		enemy[enemy_num].live = 1;
	}
} // change enemy image with score



void drawToBackBuffer(const int i, const int j, char* image)
{


	int ix = 0;
	while (1)
	{
		if (image[ix] == '\0') break;

		back_buffer[j][i + ix] = image[ix];
		ix++;
	}


}
void render()
{
	// re-draw chaged parts
	for (j = 0; j < SCR_HEIGHT; j++)
		for (i = 0; i < SCR_WIDTH; i++)
		{
			if (back_buffer[j][i] != front_buffer[j][i])
			{
				moveCursorTo(i, j);
				if (back_buffer[j][i] == '\0')
					printf("%c", ' ');
				else
					printf("%c", back_buffer[j][i]);
			}
		}
	//update frame buffer
	for (j = 0; j < SCR_HEIGHT; j++)
		for (i = 0; i < SCR_WIDTH; i++)
		{
			front_buffer[j][i] = back_buffer[j][i];
			back_buffer[j][i] = '\0';
		}
}

void moveCursorTo(const short x, const short y)
{

	const COORD pos = { x, SCR_HEIGHT - y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void drawBoundary()
{
	int i = 0;
	for (j = 0; j < SCR_HEIGHT; j++)
	{
		drawToBackBuffer(i, j, ":");
	}
	i = SCR_WIDTH - 1;
	for (j = 0; j < SCR_HEIGHT; j++)
	{
		drawToBackBuffer(i, j, ":");
	}
}
void drawAll()
{
	int b;
	drawBoundary();
	//draw boundary

	for (i = 0; i < enemy_num; i++) 
		drawToBackBuffer(enemy[i].pos_x_, enemy[i].pos_y_, enemy[i].image_);

	//draw enemy
	drawToBackBuffer(player.pos_x_, player.pos_y_, player.image_);
	
	//draw player

	for (b = 0; b < MAX_BULLETS; b++)
	{
		if (p_bullet_array[b] != NULL)
		{
			drawToBackBuffer(p_bullet_array[b]->pos_x_, p_bullet_array[b]->pos_y_, p_bullet_array[b]->image_);

		} //draw p_bullet
	}

	for (b = 0; b < MAX_BULLETS; b++)
	{
		if (e_bullet_array[b] != NULL)
		{
			drawToBackBuffer(e_bullet_array[b]->pos_x_, e_bullet_array[b]->pos_y_, e_bullet_array[b]->image_);

		} //draw e_bullet
	}

	char scoretext[15];
	sprintf(scoretext, "score : %d", score);
	drawToBackBuffer(1, 1, scoretext);//draw score

	char hptext[15];
	sprintf(hptext, "HP : %d", hp);
	drawToBackBuffer(13, 1, hptext);//draw hp
}
void P_shootBullet()
{
	int b, b_ix = -1;
	for (b = 0; b < MAX_BULLETS; b++)
	{
		if (p_bullet_array[b] == NULL)
		{
			b_ix = b;
			break;
		}
	}

	if (b_ix == -1) return;
	p_bullet_array[b_ix] = (Object*)malloc(sizeof(Object));
	            
	if        (score >= 12)
	{  
            		p_bullet_array[b_ix     ]->image_ = "+ + +";
		p_bullet_array[b_ix]->height_ = 1;
		p_bullet_array[b_ix]->width_ = 5;
		p_bullet_array[b_ix]->pos_x_ = player.pos_x_;
		p_bullet_array[b_ix]->pos_y_ = player.pos_y_;

	}

	else if (score >= 30)
	{
		p_bullet_array[b_ix]->image_ = "^_^_^";
		p_bullet_array[b_ix]->height_ = 1;
		p_bullet_array[b_ix]->width_ = 5;
		p_bullet_array[b_ix]->pos_x_ = player.pos_x_;
		p_bullet_array[b_ix]->pos_y_ = player.pos_y_;

	}
	else if (score >= 20)
	{
		p_bullet_array[b_ix]->image_ = "^ _ ^";
		p_bullet_array[b_ix]->height_ = 1;
		p_bullet_array[b_ix]->width_ = 5;
		p_bullet_array[b_ix]->pos_x_ = player.pos_x_;
		p_bullet_array[b_ix]->pos_y_ = player.pos_y_;

	}
	else if (score >=10)
	{
		p_bullet_array[b_ix]->image_ = "^_^";
		p_bullet_array[b_ix]->height_ = 1;
		p_bullet_array[b_ix]->width_ = 3;
		p_bullet_array[b_ix]->pos_x_ = player.pos_x_;
		p_bullet_array[b_ix]->pos_y_ = player.pos_y_;

	}
	else if (score >= 5)
	{
		p_bullet_array[b_ix]->image_ = "^^";
		p_bullet_array[b_ix]->height_ = 1;
		p_bullet_array[b_ix]->width_ = 2;
		p_bullet_array[b_ix]->pos_x_ = player.pos_x_;
		p_bullet_array[b_ix]->pos_y_ = player.pos_y_;

	}
	else
	{
		p_bullet_array[b_ix]->image_ = "^";
		p_bullet_array[b_ix]->height_ = 1;
		p_bullet_array[b_ix]->width_ = 1;
		p_bullet_array[b_ix]->pos_x_ = player.pos_x_ + 2;
		p_bullet_array[b_ix]->pos_y_ = player.pos_y_;
	}
	//chage bullet image with score
}

void E_shootBullet()
{
	int b, b_ix = -1, t_enemy = rand() % enemy_num, x_position;

	if (enemy[t_enemy].live == 0) //0을 만나면 리턴
		return;
	for (b = 0; b < MAX_BULLETS; b++)
	{
		if (e_bullet_array[b] == NULL)
		{
			b_ix = b;
			break;
		}
	}

	if (b_ix == -1) return;
	e_bullet_array[b_ix] = (Object*)malloc(sizeof(Object));

	e_bullet_array[b_ix]->image_ = "*";
	e_bullet_array[b_ix]->height_ = 1;
	e_bullet_array[b_ix]->width_ = 1;
	e_bullet_array[b_ix]->pos_x_ = enemy[t_enemy].pos_x_ + 2;
	e_bullet_array[b_ix]->pos_y_ = enemy[t_enemy].pos_y_;
	if (player.pos_x_ - enemy[t_enemy].pos_x_ == 0)
		x_position = 1;
	else
		x_position = player.pos_x_ - enemy[t_enemy].pos_x_;
	e_bullet_array[b_ix]->p_position = (int)((enemy[t_enemy].pos_y_-player.pos_y_) / (x_position)); // p_position y좌표 차이/x좌표 차이 저장(x차이가 0이되면 오류 발생)
	 
}


void main()
{
	int b;
	system("mode con:lines=40 cols=120");

	for (j = 0; j < SCR_HEIGHT; j++)
		for (i = 0; i < SCR_WIDTH; i++)
		{
			front_buffer[j][i] = '\0';
			back_buffer[j][i] = '\0';
		}

	player.image_ = "==^==";
	player.width_ = 5;
	player.height_ = 1;
	player.pos_x_ = 30;
	player.pos_y_ = 3;

	enemy[0].image_ = "*^A^*";
	enemy[0].width_ = 5;
	enemy[0].height_ = 1;
	enemy[0].pos_x_ = rand() % 99;
	enemy[0].pos_y_ = SCR_HEIGHT - 3;


	for (b = 0; b < MAX_BULLETS; b++)
	{
		p_bullet_array[b] = NULL;
	} //initialize bullet

	for (b = 0; b < MAX_BULLETS; b++)
	{
		e_bullet_array[b] = NULL;
	} //initialize bullet

	CONSOLE_CURSOR_INFO cur_info;
	cur_info.dwSize = 1;
	cur_info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info); // hide cursor

	while (1) //main game loop
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			player.pos_x_--;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			if (player.pos_x_ < SCR_WIDTH - player.width_ - 1)
				player.pos_x_++;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			player.pos_y_++;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (player.pos_y_ <= SCR_HEIGHT - player.height_ - 1)
				player.pos_y_--;
		}
		static bool roaded = true;

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (roaded == true)
			{
				P_shootBullet();
				roaded = false;
			}
		}
		else
		{
			roaded = true;
		}


		for (b = 0; b < MAX_BULLETS; b++)
		{
			if (p_bullet_array[b] != NULL)
			{

				if (p_bullet_array[b]->pos_y_ >= SCR_HEIGHT - 1)
				{
					free(p_bullet_array[b]);
					p_bullet_array[b] = NULL;
				}
				else
					p_bullet_array[b]->pos_y_++;
			}
		}

		for (b = 0; b < MAX_BULLETS; b++)
		{
			if (e_bullet_array[b] != NULL)
			{

				if (e_bullet_array[b]->pos_y_ <= 1)
				{
					free(e_bullet_array[b]);
					e_bullet_array[b] = NULL;
				}
				else
				{
					static int stack = 0;
					e_bullet_array[b]->pos_y_--;
					stack++;
					if (e_bullet_array[b]->p_position>0 && e_bullet_array[b]->p_position <= stack)
					{
						stack = 0;
						e_bullet_array[b]->pos_x_++;
					}
					else if (e_bullet_array[b]->p_position<0 && -e_bullet_array[b]->p_position <= stack)
					{
						stack = 0;
						e_bullet_array[b]->pos_x_--;
					}
				}
			}
		}


		//check collision between enemy and bullet
		for (b = 0; b < MAX_BULLETS; b++)
		{
			if (p_bullet_array[b] != NULL)
			{
				for (i = 0; i < enemy_num; i++)
				{
					if (p_bullet_array[b]->pos_y_ == enemy[i].pos_y_ &&
						p_bullet_array[b]->pos_x_ >= enemy[i].pos_x_ &&
						p_bullet_array[b]->pos_x_ < enemy[i].pos_x_ + enemy[i].width_)
					{
						score++;
						free(p_bullet_array[b]);
						p_bullet_array[b] = NULL;

						enemy[i].image_ = ""; 
						enemy[i].width_ = 0;
						enemy[i].height_ = 0;
						enemy[i].live = 0;  // image가 없어져도 총알이 계속 날아오는 문제 수정
						enemy[i].pos_x_ = 0;
						enemy[i].pos_y_ = 0;
						break;
					}
				}
			}
		}

		for (b = 0; b < MAX_BULLETS; b++)
		{
			if (e_bullet_array[b] != NULL)
			{
				for (i = 0; i < enemy_num; i++)
				{
					if (e_bullet_array[b]->pos_y_ == player.pos_y_ &&
						e_bullet_array[b]->pos_x_ >= player.pos_x_ &&
						e_bullet_array[b]->pos_x_ < player.pos_x_ + player.width_)
					{
						hp--;
						free(e_bullet_array[b]);
						e_bullet_array[b] = NULL;
						break;
					}
				}
			}
		}


		int dice = rand() % 3;
		if (time % 10 == 0)
			for (i = 0; i < enemy_num; i++)
			{
				dice = (dice + rand() % 8) % 3;
				switch (dice)
				{
				case 0:
					if (rand() % 4 == 1)
						E_shootBullet();
					break;
				case 1:
					if (enemy[i].pos_x_ > 1)
						enemy[i].pos_x_--;
					break;
				case 2:
					if (enemy[i].pos_x_ < SCR_WIDTH - enemy[i].width_ - 1)
						enemy[i].pos_x_++;
					break;
				} //move enemy randomly
			}

		time += 2;
		if (time % 100 == 0)
		{
			for (i = 0; i < enemy_num; i++)
				enemy[i].pos_y_--;
		} // 1초에 한 번씩  enemy 하향
		if (time % 20 == 0)
		{
			AddEnemy();
		} // 0.2초에 한 번씩 enemy 생성
		drawAll();

		render();

		Sleep(20);

		if (hp == 0)
			break;
	}
	GameExit();
}