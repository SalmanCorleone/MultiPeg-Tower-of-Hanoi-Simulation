#include "iGraphics.h"
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <cstring>
#include <cstdlib>


using namespace std;


int p, sub=0;
int n=2,m,x[100],y[100];
int a[20][3],k=0,l=0, kk=1;
stack<int> last;

int ax[100000],ay[100000];
int ind=0;
stack<int> q[20];

int peg[20]={0};
int dp[201][21];
int in[201][21];


char str[100], str2[100];
int lent1=0, lent2=0;
int mode=0;
int flg=0;
int start=0;

void drawTextBox()
{
	iSetColor(255, 255, 255);
	iRectangle(770, 470, 80, 50);

	iRectangle(770, 370, 80, 50);
}

int rec(int n, int p)
{
    if(n==0) return 0;
    if(n==1) return 1;
    if(dp[n][p]!=-1) return dp[n][p];
    if(p==3)
    {
        in[n][p]=n-1;
        if(n<31)
        {
            dp[n][p]=(1<<n)-1;
        }
        else dp[n][p]=INT_MAX;
    }
    else
    {
        if(n<p)
        {
            dp[n][p]=2*n-1;
        }
        else
        {
            int mn=INT_MAX;
            for(int i=1; i<n; i++)
            {
                int val=2*rec(i,p) + rec(n-i, p-1);
                if(val>=0)
                {
                    if(val<mn)
                    {
                        in[n][p]=i;
                    }
                    mn=min(mn,val);
                }
            }
            dp[n][p]=mn;
        }
    }
    return dp[n][p];
}


void TOH(int n,int x,int y,int z);

void plate(int c, int d, int r)
{
	iFilledRectangle(c,d, r,10);
	iFilledRectangle(c-r,d,r,10);
	iSetColor(255,0,100);
	iLine(c-r, d, c+r, d);
}

void iDraw()
{
	//y[0]=60-10;
	iClear();
	if(mode==0 || mode==1 || mode==2)
	{
		iShowBMP(0,0, "bck3.bmp");
		iShowBMP(0, 512, "bck4.bmp");
		iShowBMP(838,0, "bck5.bmp");
		iShowBMP(838, 512, "bck6.bmp");
		drawTextBox();
		iSetColor(0, 0, 0);
		iText(775, 485, str);
		iText(775, 385, str2);

	}
	if(mode==3)
	{
		iSetColor(100,200,30);
		iFilledRectangle(10,20, 1330, 40);
		iSetColor(10,20,30);
		for(int i=0; i<p; i++)
		{
			iFilledRectangle(a[i][0]-5,60,10,150);
		}
		for(int i=0; i<n; i++)
		{

			iSetColor(255,255,255);
			plate(x[i],y[i], 70- (i*5));
		}
	}
}

void iMouseMove(int mx, int my)
{
}

void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(mx >= 770 && mx <= 850 && my >= 470 && my <= 520 && (mode == 0 || mode==2))
		{
			if(mode==2) flg=1;
			mode = 1;
		}
		if(mx >= 770 && mx <= 850 && my >= 370 && my <= 420 && (mode == 0 || mode==1))
		{
			if(mode==1) flg=1;
			mode = 2;
		}
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	}
}

void iKeyboard(unsigned char key)
{
	if(key== '\r')
	{
		if(flg==1 && (mode==1 || mode ==2))
		{
			mode=3;
		}

	}
	else
	{
		if(mode==1 )
		{
			str[lent1]= key;
			lent1++;
		}

		if(mode==2)
		{
			str2[lent2]= key;
			lent2++;
		}
	}
	if(key == ' ')
	{
		kk++;
		if(kk%2==0) iPauseTimer(0);
		else iResumeTimer(0);
	}

	if(key == 'q')
	{
		exit(0);
	}
	//place your codes for other keys here
}

void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	//place your codes for other keys here
}

void outofpillar(int e)
{
	if(y[e] < 230) y[e]+=10;
	//else if(a[e-1][0]) a[e-1][0]-=10;
}

void insidepillar(int e)
{
	y[e]-=10;
	//else a[e-1][0]+=10;
}

void moveplate(int e, int f)
{
	if(k==0)
	{
		outofpillar(e);
		//y[e]= y[e]+1;
		//printf(" %d s%d\n",e,y[e]);
		if( y[e] >= 230)
		{
			//a[e-1][1]-=10;
			if( x[e] < a[f][0]) k=1;
			else k=10;
		}
	}
	else if(k==1)
	{

		//printf(" %d d%d\n",e,y[e]);
		if( x[e] < a[f][0])
		{
			x[e]+=10;
			//printf("s   %d %d\n",x[e],a[f][0]);
		}
		else
		{
			x[e] = a[f][0];
			k=3;
		}
	}

	else if(k==10)
	{

		//printf(" %d d%d\n",e,y[e]);
		if( x[e] > a[f][0])
		{
			x[e]-=10;
			//printf("s   %d %d %d\n",x[e],a[f][0],f);
		}
		else
		{
			x[e] = a[f][0];
			k=3;
		}
	}
	else if(k==3)
	{
		insidepillar(e);

		//printf(" %d a%d\n",e,y[e]);
		if( y[e]-10 < a[f][1])
		{
			k=4;
			a[f][1]+=10;
			q[f].push(e);
		}
	}
}


void initial()
{
	memset(dp,-1,sizeof(dp));
		p= atoi(str);
		n= atoi(str2);
		int cd=1350-(p*10);
		cd=cd/(2*p);
		int inn=-10-cd;

		for(int i=0; i<n; i++)
		{
			q[0].push(i);

			x[i]=inn+(2*cd)+10;
			y[i]= 60+(i*10);
		}

		for(int i=0; i<p; i++)
		{
			a[i][0]=inn+(2*cd)+10;
			inn=a[i][0];
		}
		a[0][1]= 60+(n*10);
		for(int i=1; i<p; i++)
			a[i][1]= 60;

		sub=0;
		int xtra=rec(20,20);

		TOH(n,p,0,p-1);

		for(int i=0; i<n; i++)
		{
			q[0].push(i);
			q[p-1].pop();
		}
		printf("%d\n",ind);
}

void imove()
{

	if(mode==3)
	{
		if(start==0)
		{
			initial();
			start=1;
		}

		if(l==ind) iPauseTimer(0);
		else
		{
			//printf("%d %d %d\n",ax[l],ay[l],a[ay[l]][1]);
			//printf("%d\n",k);
			//printf("e  %d %d %d\n", q[ax[l]].size(), ax[l],l);
			moveplate(q[ax[l]].top(), ay[l]);
			if(k==4)
			{
				if(a[ax[l]][1]>60)
				{
					a[ax[l]][1]-=10;
					//printf("d   %d %d\n",ax[l], a[ax[l]][1]);
				}
				//printf("%d %d %d\n",ax[l],ay[l],a[ay[l]][1]);
				//printf("%d %d\n",q[ax[l]].size(),q[ax[l]].top());
				q[ax[l]].pop();
				l++;
				k=0;
				//printf("%d %d %d\n",ax[l],ay[l],a[ay[l]][1]);
			}
		}
	}
}


void main()
{

	iSetTimer(5, imove);
	iInitialize(1350,700, "tower of rc");

}
void TOH(int n,int t,int x,int y)
{
	if(n==1)
	{
	ax[ind]=x;
	ay[ind]=y;
	q[y].push(q[x].top());
	q[x].pop();
	printf("%d->%d\n",x,y);
	ind++;
	}
	else
	{
		int kkk=x;
		int xtra= rec(n,t);

		//

		if(in[n][t]>0)
		{
			while(kkk==x || kkk==y || (q[kkk].size() && q[x].top()<=q[kkk].top()))
			{
				kkk++;
				if(kkk==p) kkk=0;
				//if(!q[kkk].empty()) printf(" %d %d %d %d\n",q[kkk].top(),kkk,q[x].top(),x);
			}
			printf("%d kkk %d %d %d %d\n",q[kkk].size(), kkk,in[n][t],n,t);
			sub=kkk;
			TOH(in[n][t], t, x, kkk);
			printf("c\n");
			TOH(n-in[n][t], t-1, x, y);
			TOH(in[n][t], t, kkk, y);
			sub=y;
		}
		else
		{
			for(int i=0; i<n;i++)
			{
				printf("%d ",i);
				if(i==n-1)
				{

					ax[ind]=x;
					ay[ind]=y;
					q[y].push(q[x].top());
					q[x].pop();
					printf("%d->%d\n",x,y);
					ind++;
					//printf("   %d %d %d\n",i);
					continue;
				}
				while(kkk==x || kkk==y || (q[kkk].size() && q[x].top()<=q[kkk].top()))
				{
					kkk++;
					if(kkk==p) kkk=0;
				}
				last.push(kkk);
				ax[ind]=x;
		   		ay[ind]=kkk;
				q[kkk].push(q[x].top());
				q[x].pop();
				printf("%d->%d\n",x,kkk);
				ind++;
				kkk++;
				if(kkk==p) kkk=0;


			}
			for(int i=0; i<n-1; i++)
			{
				ax[ind]=last.top();
				ay[ind]=y;
				q[y].push(q[last.top()].top());
				q[last.top()].pop();
				printf("%d->%d\n",ax[ind],y);
				ind++;
				last.pop();
			}

		}
	}
}

