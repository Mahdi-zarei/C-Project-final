#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#define ll long long
int mark[21][21];
int mapp1[21][21];
int mapp2[21][21];
int s1[21][21];
int s2[21][21];
int num1,num2;
int b;
int toti;
int num;
int score1;
int score2;
int savex,savey;
bool upd;
bool lose;
bool turn;
bool dec;
bool how;
bool att;
bool noc;
bool finished;
bool tosave;
int x1;
int yy;
FILE *scb;
FILE *sav;
FILE *tmp;
int th1,th2;
struct nova {
	char name[50];
	int scr;
};
struct node {
	int len;
	int id;
	int hit;
	int cor1;
	int cor2;
	bool side;
	struct node* next;
};
struct node* ships[20][2];
void hide() {
	int i;
	for (i=0;i<30;i++) printf("\n");
}
void zerofier(int x) {
	int i,j;
	if (x==-1) {
		for (i=0;i<20;i++) {
			for (j=0;j<20;j++) {
				mapp1[i][j]=0;
				mapp2[i][j]=0;
				s1[i][j]=0;
				s2[i][j]=0;
			}
		}
	}
	if (x==0) {
		for (i=0;i<20;i++) {
			for (j=0;j<20;j++){
				mark[i][j]=0;
			}
		}
	}
	if (x==2) {
		for (i=0;i<20;i++) {
			for (j=0;j<20;j++) {
				mapp1[i][j]=0;
				mapp2[i][j]=0;
			}
		}
	}
}
void prifier(int x,bool mode) {
	int i,j;
	char cc=177;
	printf("  ");
	for (i=0;i<b;i++) {
		if (i<9) printf(" %d ",i+1);
		else printf (" %d",i+1);
	}
	printf("\n\n");
	if (mode==0) {
		if (x==1) {
		for (i=0;i<b;i++) {
			if (i<9) printf("%d  ",i+1);
			else printf("%d ",i+1);
			for (j=0;j<b;j++) {
				if (s1[i][j]!=0) printf("S  ");
				else printf("%c  ",cc);
			}
			printf("\n\n");
		}
	} else {
		for (i=0;i<b;i++) {
			if (i<9) printf("%d  ",i+1);
			else printf("%d ",i+1);
			for (j=0;j<b;j++) {
				if (s2[i][j]!=0) printf("S  ");
				else printf("%c  ",cc);
			}
			printf("\n\n");
		}
	}
	} else {
		if (x==0) {
			for (i=0;i<b;i++) {
				if (i<9) printf("%d  ",i+1);
				else printf("%d ",i+1);
				for (j=0;j<b;j++) {
					if (mapp1[i][j]==0) printf("%c  ",cc);
					if (mapp1[i][j]==1) printf("H  ");
					if (mapp1[i][j]==2) printf("E  ");
					if (mapp1[i][j]==-1) printf("D  ");
				}
				printf("\n\n");
			}	
		} else {
			for (i=0;i<b;i++) {
				if (i<9) printf("%d  ",i+1);
				else printf("%d ",i+1);
				for (j=0;j<b;j++) {
					if (mapp2[i][j]==0) printf("%c  ",cc);
					if (mapp2[i][j]==1) printf("H  ");
					if (mapp2[i][j]==2) printf("E  ");
					if (mapp2[i][j]==-1) printf("D  ");
				}
				printf("\n\n");
			}
		}
	}
	printf("\n");
}
void setter(int x) {
	if (x==1) {
		b=20;
		toti=127;
				num=18;
				ships[0][0]->len=18;
				ships[1][0]->len=15;
				ships[2][0]->len=14;
				ships[3][0]->len=10;
				ships[4][0]->len=10;
				ships[5][0]->len=8;
				ships[6][0]->len=8;
				ships[7][0]->len=8;
				ships[8][0]->len=6;
				ships[9][0]->len=6;
				ships[10][0]->len=5;
				ships[11][0]->len=4;
				ships[12][0]->len=4;
				ships[13][0]->len=4;
				ships[14][0]->len=3;
				ships[15][0]->len=2;
				ships[16][0]->len=1;
				ships[17][0]->len=1;
	}
	if (x==2) {
		b=15;
		toti=59;
				num=12;
				ships[0][0]->len=12;
				ships[1][0]->len=10;
				ships[2][0]->len=7;
				ships[3][0]->len=7;
				ships[4][0]->len=5;
				ships[5][0]->len=4;
				ships[6][0]->len=4;
				ships[7][0]->len=3;
				ships[8][0]->len=3;
				ships[9][0]->len=2;
				ships[10][0]->len=1;
				ships[11][0]->len=1;
	}
	if (x==3) {
		b=10;
		toti=30;
				num=8;
				ships[0][0]->len=6;
				ships[1][0]->len=6;
				ships[2][0]->len=5;
				ships[3][0]->len=4;
				ships[4][0]->len=4;
				ships[5][0]->len=3;
				ships[6][0]->len=1;
				ships[7][0]->len=1;
	}
	int i;
	for (i=0;i<20;i++) {
		ships[i][1]->len=ships[i][0]->len;
	}
}
void hitzero() {
	int i;
	for (i=0;i<b;i++) {
		ships[i][0]->hit=0;
		ships[i][1]->hit=0;
		ships[i][0]->id=i+1;
		ships[i][1]->id=i+1;
	}
}
void hitter (int x) {
	int i;
	if (turn==0) th1++;
	if (turn==1) th2++;
	ships[x-1][!turn]->hit++;
	if (turn==0) score1++;
	if (turn==1) score2++;
	if (ships[x-1][!turn]->hit==ships[x-1][!turn]->len) {
		if (turn==1) {
			dec=0;
			how=0;
		}
		ships[x-1][!turn]->id=-1;
		if (turn==0) score1+=2*(ships[0][0]->len-ships[x-1][turn]->len+2);
		if (turn==1) score2+=2*(ships[0][0]->len-ships[x-1][turn]->len+2);
		for (i=0;i<ships[x-1][turn]->len;i++) {
			if (turn==1) {
				if (ships[x-1][!turn]->side==0) {
					mapp2[ships[x-1][!turn]->cor1][ships[x-1][!turn]->cor2 +i]=-1;
					if (ships[x-1][!turn]->cor1>0) {
						mapp2[ships[x-1][!turn]->cor1-1][ships[x-1][!turn]->cor2 +i]=2;
						if (ships[x-1][!turn]->cor2>0) {
							mapp2[ships[x-1][!turn]->cor1-1][ships[x-1][!turn]->cor2-1]=2;
							mapp2[ships[x-1][!turn]->cor1][ships[x-1][!turn]->cor2-1]=2;
						}
						if (ships[x-1][!turn]->cor2<b-1) {
							mapp2[ships[x-1][!turn]->cor1-1][ships[x-1][!turn]->cor2+1]=2;
							mapp2[ships[x-1][!turn]->cor1][ships[x-1][!turn]->cor2+1]=2;
						}
					} 
					if (ships[x-1][!turn]->cor1<b-1) {
						mapp2[ships[x-1][!turn]->cor1+1][ships[x-1][!turn]->cor2+i]=2;
						if (ships[x-1][!turn]->cor2>0) mapp2[ships[x-1][!turn]->cor1+1][ships[x-1][!turn]->cor2-1]=2;
						if (ships[x-1][!turn]->cor2<b-1) mapp2[ships[x-1][!turn]->cor1+1][ships[x-1][!turn]->cor2+1]=2;
					}
				}
				else {
					mapp2[ships[x-1][!turn]->cor1 +i][ships[x-1][!turn]->cor2]=2;
					if (ships[x-1][!turn]->cor2>0) {
						mapp2[ships[x-1][!turn]->cor1+i][ships[x-1][!turn]->cor2 -1]=2;
						if (ships[x-1][!turn]->cor1>0) {
							mapp2[ships[x-1][!turn]->cor1-1][ships[x-1][!turn]->cor2-1]=2;
							mapp2[ships[x-1][!turn]->cor1-1][ships[x-1][!turn]->cor2]=2;
						}
						if (ships[x-1][!turn]->cor1<b-1) {
							mapp2[ships[x-1][!turn]->cor1+1][ships[x-1][!turn]->cor2-1]=2;
							mapp2[ships[x-1][!turn]->cor1+1][ships[x-1][!turn]->cor2]=2;
						}
					}
					if (ships[x-1][!turn]->cor2<b-1) {
						mapp2[ships[x-1][!turn]->cor1+i][ships[x-1][!turn]->cor2+1]=2;
						if (ships[x-1][!turn]->cor1>0) mapp2[ships[x-1][!turn]->cor1-1][ships[x-1][!turn]->cor2+1]=2;
						if (ships[x-1][!turn]->cor1<b-1) mapp2[ships[x-1][!turn]->cor1+1][ships[x-1][!turn]->cor2+1]=2;
					}
				}
			}
			else {
				if (ships[x-1][!turn]->side==0) {
					mapp1[ships[x-1][!turn]->cor1][ships[x-1][!turn]->cor2 +i]=-1;
					if (ships[x-1][!turn]->cor1>0) {
						mapp1[ships[x-1][!turn]->cor1-1][ships[x-1][!turn]->cor2 +i]=2;
						if (ships[x-1][!turn]->cor2>0) {
							mapp1[ships[x-1][!turn]->cor1-1][ships[x-1][!turn]->cor2-1]=2;
							mapp1[ships[x-1][!turn]->cor1][ships[x-1][!turn]->cor2-1]=2;
						}
						if (ships[x-1][!turn]->cor2<b-1) {
							mapp1[ships[x-1][!turn]->cor1-1][ships[x-1][!turn]->cor2+1]=2;
							mapp1[ships[x-1][!turn]->cor1][ships[x-1][!turn]->cor2+1]=2;
						}
					} 
					if (ships[x-1][!turn]->cor1<b-1) {
						mapp1[ships[x-1][!turn]->cor1+1][ships[x-1][!turn]->cor2+i]=2;
						if (ships[x-1][!turn]->cor2>0) mapp1[ships[x-1][!turn]->cor1+1][ships[x-1][!turn]->cor2-1]=2;
						if (ships[x-1][!turn]->cor2<b-1) mapp1[ships[x-1][!turn]->cor1+1][ships[x-1][!turn]->cor2+1]=2;
					}
				}
				else {
					mapp1[ships[x-1][!turn]->cor1 +i][ships[x-1][!turn]->cor2]=2;
					if (ships[x-1][!turn]->cor2>0) {
						mapp1[ships[x-1][!turn]->cor1+i][ships[x-1][!turn]->cor2 -1]=2;
						if (ships[x-1][!turn]->cor1>0) {
							mapp1[ships[x-1][!turn]->cor1-1][ships[x-1][!turn]->cor2-1]=2;
							mapp1[ships[x-1][!turn]->cor1-1][ships[x-1][!turn]->cor2]=2;
						}
						if (ships[x-1][!turn]->cor1<b-1) {
							mapp1[ships[x-1][!turn]->cor1+1][ships[x-1][!turn]->cor2-1]=2;
							mapp1[ships[x-1][!turn]->cor1+1][ships[x-1][!turn]->cor2]=2;
						}
					}
					if (ships[x-1][!turn]->cor2<b-1) {
						mapp1[ships[x-1][!turn]->cor1+i][ships[x-1][!turn]->cor2+1]=2;
						if (ships[x-1][!turn]->cor1>0) mapp1[ships[x-1][!turn]->cor1-1][ships[x-1][!turn]->cor2+1]=2;
						if (ships[x-1][!turn]->cor1<b-1) mapp1[ships[x-1][!turn]->cor1+1][ships[x-1][!turn]->cor2+1]=2;
					}
				}
			}
		}
	}
}
//bot decision making section
int maxi() {
	int i,j;
	int tmp=0;
	int ans=0;
	for (i=0;i<b;i++) {
		for (j=0;j<b;j++) {
			if (tmp>ans) ans=tmp;
			if (mapp2[i][j]!=0) {
				tmp=0;
			}
			else tmp++;
		}
		tmp=0;
	}
	for (i=0;i<b;i++) {
		for (j=0;j<b;j++) {
			if (tmp>ans) ans=tmp;
			if (mapp2[j][i]!=0) {
				tmp=0;
			}
			else tmp++;
		}
		tmp=0;
	}
	return ans;
}
bool isf(int x) {
	int n=0;
	int ans=0;
	if (x<b) {
		int i;
		for (i=0;i<b;i++) {
			if (ans<n) ans=n;
			if (mapp2[x][i]!=0) {
				n=0;
			}
			else n++;
		}
	}
	else {
		n=0;
		int i;
		for (i=0;i<b;i++) {
			if (ans<n) ans=n;
			if (mapp2[i][x-b]!=0) {
				n=0;
			}
			else n++;
		}
	}
	if (ans==maxi()) return 1;
	return 0;
}
int botti(int x) {
	int n=0;
	int ans=0;
	if (x<b) {
		int i;
		for (i=0;i<b;i++) {
			if (mapp2[x][i]!=0) {
				n=0;
			}
			else n++;
			if (n==maxi()) return i-maxi()/2;
		}
	}
	else {
		n=0;
		int i;
		for (i=0;i<b;i++) {
			if (mapp2[i][x-b]!=0) {
				n=0;
			}
			else n++;
			if (n==maxi()) return i-maxi()/2;
		}
	}
}
void findi() {
	int i,j;
	for (i=0;i<b;i++) {
		for (j=0;j<b;j++) {
			if (mapp2[i][j]==1) {
				x1=i;
				yy=j;
				return;
			}
		}
	}
}
void hower() {
	findi();
	if (x1>0 && mapp2[x1-1][yy]==0) {
		savex=x1-1;
		savey=yy;
		if (s1[x1-1][yy]!=0) {
			mapp2[x1-1][yy]=1;
			how=1;
			hitter(s1[x1-1][yy]);
			att=1;
			printf("The enemy attacked your ship on: %d %d\n",x1,yy+1);
			Sleep(500);
			printf("The enemy Map:\n");
			prifier(1,1);
		} else {
			mapp2[x1-1][yy]=2;
			printf("The enemy hit the water!\n");
			Sleep(500);
			printf("the enemy map:\n");
			prifier(1,1);
		}
	} else if (yy>0 && mapp2[x1][yy-1]==0) {
		savex=x1;
		savey=yy-1;
		if (s1[x1][yy-1]!=0) {
			mapp2[x1][yy-1]=1;
			how=1;
			hitter(s1[x1][yy-1]);
			att=0;
			printf("The enemy attacked your ship on: %d %d\n",x1+1,yy);
			Sleep(500);
			printf("The enemy Map:\n");
			prifier(1,1);
		} else {
			mapp2[x1][yy-1]=2;
			printf("The enemy hit the water!\n");
			Sleep(500);
			printf("the enemy map:\n");
			prifier(1,1);
		}
	} else if (x1<b-1 && mapp2[x1+1][yy]==0) {
		savex=x1+1;
		savey=yy;
		if (s1[x1+1][yy]!=0) {
			mapp2[x1+1][yy]=1;
			how=1;
			hitter(s1[x1+1][yy]);
			att=1;
			printf("The enemy attacked your ship on: %d %d\n",x1+2,yy+1);
			Sleep(500);
			printf("The enemy Map:\n");
			prifier(1,1);
		} else {
			mapp2[x1+1][yy]=2;
			printf("The enemy hit the water!\n");
			Sleep(500);
			printf("the enemy map:\n");
			prifier(1,1);
		}
	} else if (yy<b-1 && mapp2[x1][yy+1]==0) {
		savex=x1;
		savey=yy+1;
		if (s1[x1][yy+1]!=0) {
			mapp2[x1][yy+1]=1;
			how=1;
			hitter(s1[x1][yy+1]);
			att=0;
			printf("The enemy attacked your ship on: %d %d\n",x1+1,yy+2);
			Sleep(500);
			printf("The enemy Map:\n");
			prifier(1,1);
		} else {
			mapp2[x1][yy+1]=2;
			printf("The enemy hit the water!\n");
			Sleep(500);
			printf("the enemy map:\n");
			prifier(1,1);
		}
	}
}
void attacker() {
	findi();
	if (how==0) {
		hower();
	}
	else {
		if (att==0) {
			if (yy>0 && mapp2[x1][yy-1]==0) {
				savex=x1;
				savey=yy-1;
				if (s1[x1][yy-1]!=0) {
					mapp2[x1][yy-1]=1;
					hitter(s1[x1][yy-1]);
					printf("The enemy attacked your ship on: %d %d\n",x1+1,yy);
					Sleep(500);
					printf("The enemy Map:\n");
					prifier(1,1);
				} else {
					mapp2[x1][yy-1]=2;
					printf("The enemy hit the water!\n");
					Sleep(500);
					printf("the enemy map:\n");
					prifier(1,1);
				}
			} else {
				int n=0;
				while(mapp2[x1][yy+n]==1) {
					n++;
				}
				mapp2[x1][yy+n]=1;
				hitter(s1[x1][yy+n]);
				savex=x1,
				savey=yy+n;
				printf("The enemy attacked your ship on: %d %d\n",x1+1,yy+n+1);
				Sleep(500);
				printf("The enemy Map:\n");
				prifier(1,1);
			}
		} else {
			if (x1>0 && mapp2[x1-1][yy]==0) {
				savex=x1-1;
				savey=yy;
				if (s1[x1-1][yy]!=0) {
					mapp2[x1-1][yy]=1;
					hitter(s1[x1-1][yy]);
					printf("The enemy attacked your ship on: %d %d\n",x1,yy+1);
					Sleep(500);
					printf("The enemy Map:\n");
					prifier(1,1);
				} else {
					mapp2[x1-1][yy]=2;
					printf("The enemy hit the water!\n");
					Sleep(500);
					printf("the enemy map:\n");
					prifier(1,1);
				}
			} else {
				int n=0;
				while(mapp2[x1+n][yy]==1) {
					n++;
				}
				mapp2[x1+n][yy]=1;
				hitter(s1[x1+n][yy]);
				savex=x1+n;
				savey=yy;
				printf("The enemy attacked your ship on: %d %d\n",x1+n+1,yy+1);
				Sleep(500);
				printf("The enemy Map:\n");
				prifier(1,1);
			}
		}
	}
}
void mover() {
	if (dec==0) {
		int n;
		while (true) {
			n=rand();
			n%=(2*b);
			if (isf(n)==1) break;
		}
		int y=botti(n);
		if (n<b) {
			savex=n;
			savey=y;
			if (s1[n][y]!=0) {
				dec=1;
				mapp2[n][y]=1;
				hitter(s1[n][y]);
				printf("The enemy attacked your ship on: %d %d\n",n+1,y+1);
				Sleep(500);
				printf("The enemy Map:\n");
				prifier(1,1);
			} else {
				mapp2[n][y]=2;
				printf("The enemy hit the water!\n");
				Sleep(500);
				printf("the enemy map:\n");
				prifier(1,1);
			}
		} else {
			savex=y;
			savey=n-b;
			if (s1[y][n-b]!=0) {
				dec=1;
				mapp2[y][n-b]=1;
				hitter(s1[y][n-b]);
				printf("The enemy attacked your ship on: %d %d\n",y+1,n-b+1);
				Sleep(500);
				printf("The enemy Map:\n");
				prifier(1,1);
			} else {
				mapp2[y][n-b]=2;
				printf("The enemy hit the water!\n");
				Sleep(500);
				printf("the enemy map:\n");
				prifier(1,1);
			}
		}
	} else {
		attacker();
	}
}
//end of bot decision making section

//map handler section
bool can(int x,int y,int size,bool s) {
	int i;
	for (i=0;i<size;i++) {
		if (s==1) {
			if (mark[x+i][y]!=0 || x+i>b-1) return 0;
		}
		else  {
			if (mark[x][y+i]!=0 || y+i>b-1) return 0;
		}
	}
	return 1;
}
void addi(int x,int y,int size,bool s,int m) {
	int i;
	for (i=0;i<size;i++) {
		if (s==1) {
			mark[x+i][y]+=7;
			if (turn==0) s1[x+i][y]=m;
			else s2[x+i][y]=m;
			if (y>0) mark[x+i][y-1]++;
			if (y<b-1) mark[x+i][y+1]++;
		}
		else {
			mark[x][y+i]+=7;
			if (turn==0) s1[x][y+i]=m;
			else s2[x][y+i]=m;
			if (x>0) mark[x-1][y+i]++;
			if (x<b-1) mark[x+1][y+i]++;
		}
	}
	if (x>0 && s==1) {
		mark[x-1][y]++;
		if (y>0) mark[x-1][y-1]++;
		if (y<b-1) mark[x-1][y+1]++;
	}
	if (x+size-1<b-1 && s==1) {
		mark[x+size][y]++;
		if (y>0) mark[x+size][y-1]++;
		if (y<b-1) mark[x+size][y+1]++;
	}
	if (y>0 && s==0) {
		mark[x][y-1]++;
		if (x>0) mark[x-1][y-1]++;
		if (x<b-1) mark[x+1][y-1]++;
	}
	if (y+size-1<b-1 && s==0) {
		mark[x][y+size]++;
		if (x>0) mark[x-1][y+size]++;
		if (x<b-1) mark[x+1][y+size]++;
	} 
}
void placer() {
	zerofier(0);
	int counter=0;
	int i;
	for (i=0;i<num;i++) {
		int size=ships[i][0]->len;
		while (true) {
			int n=rand()%(b*b-1);
			int x=n/b;
			int y=n%b;
			n=rand();
			n%=2;
			if (can(x,y,size,n)==1) {
				addi(x,y,size,n,i+1);
				ships[i][turn]->cor1=x;
				ships[i][turn]->cor2=y;
				ships[i][turn]->side=n;
				break;
			}
		}
	}
}
int main() {
	srand(time(NULL));
	struct nova* haji[100];
	int l;
	for (l=0;l<100;l++) {
		haji[l]=malloc(sizeof(struct nova));
	}
	scb=fopen("data.txt","a");
	fclose(scb);
	sav=fopen("saved.bin","ab");
	fclose(sav);
	scb=fopen("data.txt","r");
	int scbl=0;
	while (true) {
		fscanf(scb,"%s %d",haji[scbl]->name,&haji[scbl]->scr);
		if (feof(scb)) break;
		scbl++;
	}
	fclose(scb);
	while(true) {
		bool bot=0;
		bool play=0;
		int i;
		for (i=0;i<20;i++) {
			ships[i][0]=malloc(sizeof(struct node));
			ships[i][1]=malloc(sizeof(struct node));
			ships[i][0]->id=i+1;
			ships[i][1]->id=i+1;
			ships[i][0]->hit=0;
			ships[i][1]->hit=0;
		}
		tosave=0;
		finished=0;
		printf("*** MENU ***\n");
		printf (" 1)New Game\n 2)Load Saved Games\n 3)Scoreboard\n 4)Info\n 5)Exit Game\n");
		int x; scanf("%d",&x);
		if (x==4) {
			printf("The Map Uses Following Format:\n");
			printf ("D For Completely Destroyed Ships\n");
			printf ("H For Hit Ships Which Are Not Fully Destroyed\n");
			printf ("E For Hit Spots Which Are Empty\n");
			printf("At The Play Time You Can Enter -1 -1 To Save The Game!\n");
			printf("While Navigating The Menu, You Can Enter An Out Of Range Number To Restart The Menu!\n");
			printf("BE CAREFUL WHILE ENTERING COORDIANTES, AS ENTERING NON-NUMBER INPUTS WILL RESULT IN A CRASH!\n");
			printf("I strongly suggest you run the game in full screen\n as the size of map can be too big to show\n\n");
		}
		if (x==1) {
			noc=0;
			upd=0;
			lose=0;
			th1=th2=0;
			zerofier(-1);
			hitzero();
			printf("Select Play Mode:\n 1)PvP\n 2)Against Bot\n");
			int y; scanf("%d",&y);
			if (y<1 || y>2) {
				printf("Invalid Input!\n");
				continue;
			}
			if (y==2) bot=1;
			char s[50];
			printf("Enter Your Desired Name (less than 50 characters, no space is allowed):\n");
			scanf("%s",s);
			bool pre1=0;
			bool pre2=0;
			int t;
			for (t=0;t<scbl;t++) {
				if (strcmp(s,haji[t]->name)==0) {
					pre1=1;
					num1=t;
					break;
				}
			}
			if (pre1==1) {
				printf("Welcome Back!\n\n");
				Sleep(1000);
			} else {
				printf("Player Account Created!\n\n");
				strcpy(haji[scbl]->name,s);
				num1=scbl;
				haji[scbl]->scr=0;
				scbl++;
				Sleep(1000);
			}
			if (bot==0) {
				printf("Enter Player 2's Name:\n");
			char sss[50];
			scanf("%s",sss);
			for (t=0;t<scbl;t++) {
				if (strcmp(sss,haji[t]->name)==0) {
					pre2=1;
					num2=t;
					break;
				}
			}
			if (pre2==1) {
				printf("Welcome Back!\n\n");
				Sleep(1000);
			}
			else {
				printf("Player Account Created!\n\n");
				strcpy(haji[scbl]->name,sss);
				num2=scbl;
				haji[scbl]->scr=0;
				scbl++;
				Sleep(1000);
				}
			}
			printf("Select Game Mode:\n 1)As Big As U Got!\n ( 20*20 map, 18 ships )\n");
			printf("2)The Goodi!\n ( 15*15 map, 12 ships )\n");
			printf("3)No Place Like Home!\n ( 10*10 map, 8 ships )\n");
			scanf("%d",&y);
			if (y<1 || y>3) {
				printf("Invalid Input!\n");
				continue;
			}
			setter(y);
			printf ("Choose The Filling Mode: \n 1)Manual\n 2)Auto\n");
			scanf("%d",&y);
			if (y<1 || y>2) {
				printf("Invalid Input!\n");
				continue;
			}
			if (y==1) {
				printf("* %s's Map *\n",haji[num1]->name);
				turn=0;
				zerofier(0);
				printf("For Each Ship Given, Give The Coordinates as follows: row column side\n");
				printf("if side=1 the ship will be parrallel to x axis\n if side=0 it will be parallel to y axis.\n");
				for (i=0;i<num;i++) {
					int c1,c2,c3;
					bool si;
					printf("Size Of Ship: %d\n",ships[i][0]->len);
					scanf("%d %d %d",&c1,&c2,&c3);;
					si=c3;
					c1--;
					c2--;
					if (can(c1,c2,ships[i][0]->len,si)==0) {
						printf("Coordiantes Contradict the Rules! Try again\n");
						i--;
					} else {
						ships[i][turn]->cor1=c1;
						ships[i][turn]->cor2=c2;
						ships[i][turn]->side=si;
						addi(c1,c2,ships[i][0]->len,si,i+1);
						printf("Ship Has Been Placed!\n");
						Sleep(500);
						prifier(1,0);
					}
					Sleep(800);
				}
				hide();
				if (bot==0) {
					printf("* %s's Map *\n",haji[num2]->name);
					turn=1;
					zerofier(0);
					printf("For Each Ship Given, Give The Coordinates as follows: row column side\n");
					printf("if side=1 the ship will be parrallel to x axis\n if side=0 it will be parallel to y axis.\n");
					for (i=0;i<num;i++) {
						int c1,c2,c3;
						bool si;
						printf("Size Of Ship: %d\n",ships[i][0]->len);
						scanf("%d %d %d",&c1,&c2,&c3);;
						si=c3;
						c1--;
						c2--;
						if (can(c1,c2,ships[i][0]->len,si)==0) {
							printf("Coordiantes Contradict the Rules! Try again\n");
							i--;
						} else {
							ships[i][turn]->cor1=c1;
							ships[i][turn]->cor2=c2;
							ships[i][turn]->side=si;
							addi(c1,c2,ships[i][0]->len,si,i+1);
							printf("Ship Has Been Placed!\n");
							sleep(500);
							prifier(2,0);
						}
						Sleep(800);
					} hide();
				} else {
					turn=1;
					placer();
					printf("The Enemy Has Set Up His Plans!\n");
				}
			} else {
				turn =0;
				placer();
				printf ("Map Of Player 1:\n");
				prifier(1,0);
				turn =1;
				placer();
				Sleep(5000);
				hide();
				if (bot==0) {
					printf("Enter Any Character To See Map Of Player 2\n");
					char qqqq[200];
					scanf("%s",qqqq);
					prifier(2,0);
					Sleep(5000);
					hide();
				} else {
					printf("The Enemy Has Set Up His Plans!\n");
				}
			}
			play=1;
		} else if (x==2) {
			hitzero();
			zerofier(-1);
			sav=fopen("saved.bin","rb");
			printf("Select The Game You Wish To Continue : \n");
			int cnt=0;
			while (true) {
				int t1,t2,bottmp;
				char stmp[50];
				fread(&t1,sizeof(int),1,sav);
				if (feof(sav)) break;
				bottmp=t1;
				fread(&t1,sizeof(int),1,sav);
				fread(&t1,sizeof(int),1,sav);
				if (bottmp==0) fread(&t2,sizeof(int),1,sav);
				printf("%d )",cnt+1);
				fread(stmp,sizeof(char),t1,sav);
				stmp[t1]='\0';
				printf("%s Against ",stmp);
				if (bottmp==0) {
					char ss[50];
					fread(ss,sizeof(char),t2,sav);
					ss[t2]='\0';
					printf("%s \n",ss);
				} else printf("Bot\n");
				while (true) {
					fread(&t1,sizeof(int),1,sav);
					if (t1==-1) {
						fread(&t2,sizeof(int),1,sav);
						break;
					}
				} cnt++;
			}
			fseek(sav,0,SEEK_SET);
			if (cnt!=0) {
				int tob;
			scanf("%d",&tob);
			if (tob>cnt) {
				printf("Invalid Input!\n");
				continue;
			}
			cnt=tob;
			int skip;
			for (skip=1;skip<cnt;skip++) {
				int t1,t2,bottmp;
				char stmp[50];
				fread(&t1,sizeof(int),1,sav);
				bottmp=t1;
				fread(&t1,sizeof(int),1,sav);
				fread(&t1,sizeof(int),1,sav);
				if (bottmp==0) fread(&t2,sizeof(int),1,sav);
				fread(stmp,sizeof(char),t1,sav);
				stmp[t1]='\0';
				if (bottmp==0) {
					char ss[50];
					fread(ss,sizeof(char),t2,sav);
					ss[t2]='\0';
				}
				while (true) {
					fread(&t1,sizeof(int),1,sav);
					if (t1==-1) {
						fread(&t2,sizeof(int),1,sav);
						break;
					}
				}
			}
			int bti;
			zerofier(-1);
			fread(&bti,sizeof(int),1,sav);
			bot=bti;
			fread(&bti,sizeof(int),1,sav);
			setter(bti);
				int l1,l2;
				fread(&l1,sizeof(int),1,sav);
				if(bot==0) fread(&l2,sizeof(int),1,sav);
				char s[50];
				fread(s,sizeof(char),l1,sav);
				int q;
				for (q=0;q<scbl;q++) {
					if (strcmp(haji[q]->name,s)==0) {
						num1=q;
						break;
					}
				}
				if (bot==0) fread(s,sizeof(char),l2,sav);
				if (bot==0) for (q=0;q<scbl;q++) {
					if (strcmp(s,haji[q]->name)==0) {
						num2=q;
						break;
					}
				}
				turn =0;
				for (q=0;q<num;q++) {
					int tmp1,tmp2,tmp3;
					fread(&tmp1,sizeof(int),1,sav);
					fread(&tmp2,sizeof(int),1,sav);
					fread(&tmp3,sizeof(int),1,sav);
					addi(tmp1,tmp2,ships[q][turn]->len,tmp3,q+1);
				}
				turn =1;
				for (q=0;q<num;q++) {
					int tmp1,tmp2,tmp3;
					fread(&tmp1,sizeof(int),1,sav);
					fread(&tmp2,sizeof(int),1,sav);
					fread(&tmp3,sizeof(int),1,sav);
					addi(tmp1,tmp2,ships[q][turn]->len,tmp3,q+1);
				}
				int t;
				turn =0;
				while (true) {
					fread(&q,sizeof(int),1,sav);
					fread(&t,sizeof(int),1,sav);
					if (q==-1 && t==-1) break;
					if (turn==0) {
						if (s2[q][t]!=0) {
							mapp1[q][t]=1;
							hitter(s2[q][t]);
						}
						else mapp1[q][t]=2;
					} else {
						if (s1[q][t]!=0) {
							mapp2[q][t]=1;
							hitter(s1[q][t]);
						}
						else mapp2[q][t]=2;
					}
					turn=!turn;
					noc=1;
				}
				play=1;
				printf("Game Has Been Loaded!\n\n");
				Sleep(1000);
			} else printf("Such Emptiness! No Game Is Saved!\n");
			fclose(sav);
		} else if (x==3) {
			scb=fopen("data.txt","w+");
			int q,z;
			for (q=0;q<scbl;q++) {
				for (z=q;z<scbl;z++) {
					if (haji[q]->scr<haji[z]->scr) {
						char p[50];
						int tm;
						strcpy(p,haji[q]->name);
						strcpy(haji[q]->name,haji[z]->name);
						strcpy(haji[z]->name,p);
						tm=haji[q]->scr;
						haji[q]->scr=haji[z]->scr;
						haji[z]->scr=tm;
					}
				}
			}
			for (q=0;q<scbl;q++) {
				fprintf(scb,"%s %d\n",haji[q]->name,haji[q]->scr);
			}
			fclose(scb);
			scb=fopen("data.txt","r");
			if (scbl!=0) printf("The Leaderboard Is As Follows: \n");
			else printf("No Record Is Available!\n");
			Sleep(500);
			while (true) {
				char rq[50];
				int eq;
				fscanf(scb,"%s %d",rq,&eq);
				if (feof(scb)) break;
				printf("%s %d\n",rq,eq);
			}
			fclose(scb);
		} else if (x==5) {
			printf("Good Bye!\n");
			break;
		}
		if (play==1) {
			tmp=fopen("last.bin","w+b");
			if (bot==0) {
				printf("Enter The Coordinates As Follows: row column\n\n");
				Sleep(500);
				if (noc==0) turn=0;
				while (true) {
					if (turn==0) printf ("* %s's Turn *\n\n",haji[num1]->name);
					else printf("* %s's Turn *\n\n",haji[num2]->name);
					printf ("Enter Coordiantes:\n");
					int c1,c2;
					scanf("%d %d",&c1,&c2);
					if (c1==-1 && c2==-1) {
						fwrite(&c1,sizeof(int),1,tmp);
						fwrite(&c2,sizeof(int),1,tmp);
						upd=1;
						tosave=1;
						break;
					}
					if (turn==0) {
						c1--;
						c2--;
						if (mapp1[c1][c2]==0 && c1<b && c2<b && c1>=0 && c2>=0) {
							fwrite(&c1,sizeof(int),1,tmp);
							fwrite(&c2,sizeof(int),1,tmp);
							if (s2[c1][c2]!=0) {
								mapp1[c1][c2]=1;
								hitter(s2[c1][c2]);
								printf("Congratz! You Hit An Enemy Ship!\n");
								Sleep(1000);
								prifier(turn,1);
								Sleep(700);
							} else {
								printf("Bleep! You Hit Water!\n");
								mapp1[c1][c2]=2;
								Sleep(1000);
								prifier(turn,1);
								Sleep(700);
							}
						} else {
							printf("Invalid Choice!\n");
							continue;
						}
					} else {
						c1--;
						c2--;
						if (mapp2[c1][c2]==0 && c1>=0 && c2>=0 && c1<b && c2<b) {
							fwrite(&c1,sizeof(int),1,tmp);
							fwrite(&c2,sizeof(int),1,tmp);
							if (s1[c1][c2]!=0) {
								mapp2[c1][c2]=1;
								hitter(s1[c1][c2]);
								printf("Congratz! You Hit An Enemy Ship!\n");
								Sleep(1000);
								prifier(turn,1);
								Sleep(700);
							} else {
								printf("Bleep! You Hit Water!\n");
								mapp2[c1][c2]=2;
								Sleep(1000);
								prifier(turn,1);
								Sleep(700);
							}
						} else {
							printf("Invalid Choice!\n");
							continue;
						}
					}
					if (th1==toti || th2==toti) {
						char p[50];
						if (turn==0) strcpy(p,haji[num1]->name);
						if (turn==1) strcpy(p,haji[num2]->name);
						if (lose==0) printf("*****CONGRATULATIONS %s ! YOU WON!!*****\n",p);
						Sleep(2000);
						upd=1;
						int jtw=-2;
						fwrite(&jtw,sizeof(int),1,tmp);
						fwrite(&jtw,sizeof(int),1,tmp);
						finished=1;
						break;
					}
					turn=!turn;
				}
			} else {
				printf("Enter The Coordinates As Follows: row column\n\n");
				Sleep(500);
				if (noc==0) turn=0;
				while (true) {
					if (turn==0) {
						printf("* %s's Turn *\n",haji[num1]->name);
						printf ("Enter Coordiantes:\n");
						int c1,c2;
						scanf("%d %d",&c1,&c2);
						if (c1==-1 && c2==-1) {
							fwrite(&c1,sizeof(int),1,tmp);
							fwrite(&c2,sizeof(int),1,tmp);
							upd=1;
							tosave=1;
							break;
						}
						c1--;
						c2--;
						if (mapp1[c1][c2]==0 && c1>=0 && c2>=0 && c1<b && c2<b) {
							fwrite(&c1,sizeof(int),1,tmp);
							fwrite(&c2,sizeof(int),1,tmp);
							if (s2[c1][c2]!=0) {
								mapp1[c1][c2]=1;
								hitter(s2[c1][c2]);
								printf("Congratz! You Hit An Enemy Ship!\n");
								Sleep(1000);
								prifier(turn,1);
								Sleep(700);
							} else {
								printf("Bloop! You Hit The Water!\n");
								mapp1[c1][c2]=2;
								Sleep(1000);
								prifier(turn,1);
								Sleep(700);
							}
						} else {
							printf("Invalid Choice!\n");
							continue;
						}
					} else {
						mover();
						fwrite(&savex,sizeof(int),1,tmp);
						fwrite(&savey,sizeof(int),1,tmp);
						Sleep(1000);
					}
					if (th1==toti || th2==toti) {
						if (turn==0) printf("*****CONGRATUILATIONS %s ! YOU WON!!*****\n",haji[num1]->name);
						else printf("*_* Dear %s You Have Been Defeated! *_*\n",haji[num1]->name);
						upd=1;
						int jtw=-2;
						fwrite(&jtw,sizeof(int),1,tmp);
						fwrite(&jtw,sizeof(int),1,tmp);
						finished=1;
						break;
					}
					turn=!turn;
				}
			}
			fclose(tmp);
		}
		if (tosave==1) {
			score1=0;
			score2=0;
			tmp=fopen("last.bin","rb");
			sav=fopen("saved.bin","a+b");
			int jtw=bot;
			fwrite(&jtw,sizeof(int),1,sav);
			jtw=5 - b/5;
			fwrite(&jtw,sizeof(int),1,sav);
			jtw=strlen(haji[num1]->name);
			fwrite(&jtw,sizeof(int),1,sav);
			if (bot==0) {
				jtw=strlen(haji[num2]->name);
				fwrite(&jtw,sizeof(int),1,sav);
			}
			fwrite(haji[num1]->name,sizeof(char),strlen(haji[num1]->name),sav);
			if (bot==0) fwrite(haji[num2]->name,sizeof(char),strlen(haji[num2]->name),sav);
			for (jtw=0;jtw<num;jtw++) {
				fwrite(&ships[jtw][0]->cor1,sizeof(int),1,sav);
				fwrite(&ships[jtw][0]->cor2,sizeof(int),1,sav);
				int bti=ships[jtw][0]->side;
				fwrite(&bti,sizeof(int),1,sav);
			}
			for (jtw=0;jtw<num;jtw++) {
				fwrite(&ships[jtw][1]->cor1,sizeof(int),1,sav);
				fwrite(&ships[jtw][1]->cor2,sizeof(int),1,sav);
				int bti=ships[jtw][1]->side;
				fwrite(&bti,sizeof(int),1,sav);
			}
			while (true) {
				int tmp1,tmp2;
				fread(&tmp1,sizeof(int),1,tmp);
				fread(&tmp2,sizeof(int),1,tmp);
				fwrite(&tmp1,sizeof(int),1,sav);
				fwrite(&tmp2,sizeof(int),1,sav);
				if (tmp1==-1 && tmp2==-1) break;
			}
			fclose(tmp);
			fclose(sav);
			printf("Game Has Been Saved!\n");
			Sleep(1000);
		}
		if (upd==1) {
			if (turn==0) {
				haji[num1]->scr+=score1;
				if (bot!=1) haji[num2]->scr+=(score2 / 2);
			} else {
				haji[num1]->scr+=(score1 /2);
				if (bot!=1) haji[num2]->scr+=score2;
			}
			scb=fopen("data.txt","w+");
			int q;
			for (q=0;q<scbl;q++) {
				fprintf(scb,"%s %d\n",haji[q]->name,haji[q]->scr);
			}
			fclose(scb);
		}
		if (finished==1) {
			hitzero();
			printf("Do You Want To Playback The Game?\n 1)Yes   2)No\n");
			int ask;
			scanf("%d",&ask);
			if (ask==1) {
			zerofier(2);
			turn =0;
			tmp=fopen("last.bin","rb");
			while (true) {
				int e1,e2;
				fread(&e1,sizeof(int),1,tmp);
				fread(&e2,sizeof(int),1,tmp);
				if (e1==-2 && e2==-2) break;
				if (turn==0) {
					printf("%s's move:\n",haji[num1]->name);
					if (s2[e1][e2]!=0) {
						mapp1[e1][e2]=1;
						hitter(s2[e1][e2]);
					} else mapp1[e1][e2]=2;
					Sleep(500);
					prifier(0,1);
					Sleep(1000);
				} else {
					printf("%s's move:\n",haji[num2]->name);
					if (s1[e1][e2]!=0) {
						mapp2[e1][e2]=1;
						hitter(s1[e1][e2]);
					} else mapp2[e1][e2]=2;
					Sleep(500);
					prifier(1,1);
					Sleep(1000);
				}
				turn=!turn;
			}
			fclose(tmp);
			}
			printf("Playback Complete!\n");
			Sleep(1000);
		}
 	}
	system("PAUSE");
}
