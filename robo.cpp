#include<graphics.h>
#include<fstream>
#include<stdio.h>
using namespace std;
/*
  color 0 = black
  color 1 = blue
  color 2 = green
  color 3 = light blue
  color 4 = red
  color 5 = purple
  color 6 = yellow
  color 7 = white
  color 8 = grey
  color 9 = indigo
  color 10 = light green
  */

void saver()
{
      ofstream ofile("scores",ios::binary);
      ofile<<4500<<endl;
      ofile<<3800<<endl;
      ofile<<3500<<endl;
      ofile<<3200<<endl;
      ofile<<3000<<endl;
      ofile.close();
}  
void credits()
{
     cleardevice();
     setcolor(10);
     outtextxy(410,200,"THANKS FOR PLAYING");
     setcolor(7);
   /*  outtextxy(440,225,"A GAME BY");
     setcolor(9);
     outtextxy(370,250,"CB.EN.U4CSE11209   D Braghadeesh");
     outtextxy(370,270,"CB.EN.U4CSE11218   M Jayagar");
     outtextxy(370,290,"CB.EN.U4CSE11205   Ashwanth");*/
     getch();
}
     
void save(int n)
{
     int val[6];
     ifstream ifile("scores",ios::binary);
     for(int i=0; i<5; ++i)
     {
             ifile>>val[i];
     }
     val[5]=n;
     for(int j=0; j<6; ++j)
     {
             for(int k=0; k<5; ++k)
             {
                     if(val[k]<val[k+1])
                     {
                           int temp;
                           temp=val[k];
                           val[k]=val[k+1];
                           val[k+1]=temp;
                     }
             }
     }
     ifile.close();
     ofstream ofile("scores",ios::binary);
     for(int i=0; i<5; ++i)
     {
             ofile<<val[i]<<endl;
     }
     ofile.close();
}    
void high_scores()
{
     char scorestring[100];
     cleardevice();
     setcolor(10);
     outtextxy(410,200,"H I G H - S C O R E S");
     setcolor(7);
     outtextxy(410,230,"Top Five High Scores");
     ifstream ifile("scores",ios::binary);
     int val[5];
     for(int i=0; i<5; ++i)
     {
             ifile>>val[i];
             sprintf(scorestring,"%d",val[i]);
             outtextxy(460,250+20*i,scorestring);
     }
     ifile.close();
     getch();
}            
class game
{
      int head_x,head_y;
      int bot_x[6],bot_y[6];
      int score,tele,alive;
      int color[5];
      
      public:

      game()
      {
            head_x=460;
            head_y=200;
            score=100;
            tele=5;
            alive=6;
            color[0]=10;
            color[1]=color[2]=color[3]=8;
      }
      // drawing functions
      void grid()
      {
               int i;
               char scorestring [100];
               //Draw Boundary
                setcolor (7);
                line (10,20,10,620);
                line (910,20,910,620);
                line (10,620,910,620);
                line (10,20,910,20);
                //Write Score on screen
                sprintf (scorestring, "Score: %d", score);
                outtextxy (820,2, scorestring);
                sprintf (scorestring, "Bots Alive: %d",alive);
                outtextxy (460,2,scorestring);
                sprintf(scorestring, "Teleports left: %d", tele);
                outtextxy (10,2,scorestring);
                // vertical lines
                for(int i=30; i<=900; i=i+20)
                {
                        line(i,20,i,620);
                }
                // horizontal lines
                for(int j=20; j<=620; j=j+20)
                {
                        line(10,j,910,j);
                }
      }
      // draw head of robot in help menu
      void one_bot()
      {
           int k,l;
           // outline of face
           for( k=head_y;k<=head_y+20;k++)
           {
              for( l=head_x;l<=head_x+20;l++)
              {
                 putpixel(l,k,5);     
              }
           }
           // for eyes
           for( k=head_y+4; k<=head_y+6; k++)
           {
                for( l=head_x+4; l<=head_x+6; l++)
                {
                     putpixel(l,k,0);
                     putpixel(l+10,k,0);
                }
           }     
           //for mouth
           setcolor(0);
           line(head_x+4, head_y+14, head_x+16, head_y+14);
      }
      void draw_head()
      {
           int k,l;
           // outline of face
           for( k=head_y;k<=head_y+20;k++)
           {
              for( l=head_x;l<=head_x+20;l++)
              {
                 putpixel(l,k,7);     
              }
           }
           // for eyes
           for( k=head_y+4; k<=head_y+6; k++)
           {
                for( l=head_x+4; l<=head_x+6; l++)
                {
                     putpixel(l,k,0);
                     putpixel(l+10,k,0);
                }
           }     
           //for mouth
           setcolor(0);
           line(head_x+4, head_y+14, head_x+16, head_y+14);
      }
      // draw the (no)th bot
      void draw_bots(int no)
      {
           int k,l;
           // outline of face
           for( k=bot_y[no];k<=bot_y[no]+20;k++)
           {
                for( l=bot_x[no];l<=bot_x[no]+20;l++)
                {
                     putpixel(l,k,5);     
                }
           }
           // for eyes
           for( k=bot_y[no]+4; k<=bot_y[no]+6; k++)
           {
                for( l=bot_x[no]+4; l<=bot_x[no]+6; l++)
                {
                     putpixel(l,k,7);
                     putpixel(l+10,k,7);
                }
           }     
           //for mouth
           setcolor(7);
           line(bot_x[no]+4, bot_y[no]+14, bot_x[no]+16, bot_y[no]+14);
      }
      // clear the screen and drwa the grid again
      void killall()
      {
           cleardevice();
           grid();
      }
      // motion functions
      // make the robots move towards the player
      void bots()
      {
           for(int i=0; i<6; ++i)
           {
                   if(bot_x[i]<head_x)
                   {
                          bot_x[i]+=20;
                   }
                   if(bot_x[i]>head_x)
                   {
                          bot_x[i]-=20;
                   }
                   if(bot_y[i]<head_y)
                   {
                          bot_y[i]+=20;
                   }
                   if(bot_y[i]>head_y)
                   {
                          bot_y[i]-=20;
                   }
           }
      }
      // make the human teleport to a random place
      void teleport()
      {
           bool flag;
           time_t t;
           do
           {
                flag=0;
                srand((unsigned)time(&t));
                // generate new coordinates
                head_x=rand()%43;
                head_y=rand()%28;
                head_x=head_x*20+10;
                head_y=head_y*20+20;
                // check if the new location is not occupied
                for(int i=0; i<6; ++i)
                {
                        if(head_x==bot_x[i] && head_y==bot_y[i])
                        {
                                            flag=1;
                                            break;
                        }
                }
           }
           while(flag);// repeat process if the generated new location is not free
           draw_head();// place the human in the new location
           killall();// clear the screen and draw the grid
           tele--;// decrement the remaining number of teleports left
           for(int i=0; i<6; ++i)
           {
                   draw_bots(i);     
           }
      }      
      // game physics    
      void www(bool &flag)
      {
           if(head_y>=40)
           {
                        head_y-=20;
                        flag=1;
           }
      }          
      void xxx(bool &flag)
      {
           if(head_y<600)
           {
                        head_y+=20;
                        flag=1;
           }
      }
      void aaa(bool &flag)
      {
           if(head_x>=30)
           {
                        head_x-=20;
                        flag=1;
           }
      }                
      void ddd(bool &flag)
      {
           if(head_x<890)
           {
                        head_x+=20;
                        flag=1;
           }
      }
      void qqq(bool &flag)
      {
           if(head_x>=30 && head_y>=40)
           {
                         head_x-=20;
                         head_y-=20;
                         flag=1;
           }
      }
      void eee(bool &flag)
      {
           if(head_x<890 && head_y>=40)
           {
                          head_x+=20;
                          head_y-=20;
                          flag=1;
           }
      }
      void zzz(bool &flag)
      {
           if(head_x>=30 && head_y<600)
           {
                         head_x-=20; 
                         head_y+=20; 
                         flag=1;
           }
      }
      void ccc(bool &flag)
      {
           if(head_x<=890 && head_y<600)
           {
                          head_x+=20; 
                          head_y+=20; 
                          flag=1;
           }
      }                          
      // move the human as per input
      void move()
      {
           bool flag=0;
           char c;
           c=getch();
           switch(c)
           {
                    case 'w': www(flag); break; // up
                    case 'x': xxx(flag); break; // down
                    case 'a': aaa(flag); break; // left
                    case 'd': ddd(flag); break; // right
                    case 's': flag=1; break; // stay put
                    case 'q': qqq(flag); break;
                    case 'e': eee(flag); break;
                    case 'z': zzz(flag); break;
                    case 'c': ccc(flag); break;
                    case ' ': if(tele>0){teleport(); score-=300; flag=1; break;} else { flag=0; break; }
                    default: flag=0;
           }
           if(flag)// if player moves
           {
                   score+=100;
                   killall();
                   bots();// make the bots move
                   for(int i=0; i<6; ++i)
                   {
                           draw_bots(i);// place the bots
                   }
                   draw_head();// place the human
           }
      }
      // to check if the bot can be placed successfully without coinciding with the human and the previously placed bots
      int place_bot(int x)
      {
          int flag=1;
          if(bot_x[x]==head_x && bot_y[x]==head_y)
          {
                     flag=0;
          }
          for(int i=0; i<x; ++i)
          {
             if(bot_x[i]==bot_x[x] && bot_y[i]==bot_y[x] && flag==1)
             {
                                   flag=0;
                                   break;
             }
          }
          return flag;
      }
      // game engine
      void collision()
      {
           for(int i=0; i<6; ++i)
           {
                   for(int j=0; j<i; ++j)
                   {
                           if(bot_x[i]<1000 && bot_y[i]<1000)
                           {
                                      int k,l;
                                      if(bot_x[i]==bot_x[j] && bot_y[i]==bot_y[j] )
                                      {
                                                 for( k=bot_x[i]; k<=bot_x[i]+20; ++k)
                                                 {
                                                         for( l=bot_y[i]; l<=bot_y[i]+20; ++l)
                                                         {
                                                                 putpixel(k,l,4);     
                                                         }
                                                 }
                                                 // for eyes
                                                 for( k=bot_y[i]+4; k<=bot_y[i]+6; k++)
                                                 {
                                                         for( l=bot_x[i]+4; l<=bot_x[i]+6; l++)
                                                         {
                                                              putpixel(l,k,0);
                                                              putpixel(l+10,k,0);
                                                         }
                                                 }     
                                                 //for mouth
                                                 setcolor(0);
                                                 line(bot_x[i]+4, bot_y[i]+14, bot_x[i]+16, bot_y[i]+14);                
                                                 alive-=2;
                                                 bot_x[i]=bot_y[i]=bot_x[j]=bot_y[j]=10000;
                                      }
                           }
                   }
           }
      }
      int game_over()
      {
          //default
          int flag=0;
          if(alive==0)
          {
                      // you win
                      return 1;
          }
          else
          {
              // you lose
              for(int i=0; i<6; ++i)
              {
                      if(head_x==bot_x[i] && head_y==bot_y[i])
                      {
                                          flag=2;
                                          break;
                      }
              }
              return flag;// returns 0 if normal 1 if you win 2 if you lose
          }
      }           
      void lose()
      {
           grid();
           for(int i=0; i<6; ++i)
           {
                   draw_bots(i);
           }
           int k,l;
           // outline of face
           for( k=head_y;k<=head_y+20;k++)
           {
              for( l=head_x;l<=head_x+20;l++)
              {
                 putpixel(l,k,10);     
              }
           }
           // for eyes
           for( k=head_y+4; k<=head_y+6; k++)
           {
                for( l=head_x+4; l<=head_x+6; l++)
                {
                     putpixel(l,k,0);
                     putpixel(l+10,k,0);
                }
           }     
           //for mouth
           setcolor(0);
           line(head_x+4, head_y+14, head_x+16, head_y+14);
           setcolor(7);
           outtextxy (455,622, "Game Over");
      }
           
      // main function of game
      void run ( ) //places characters randomly
      {
           score=100;
           alive=6;
           tele=5;
           cleardevice();
           grid();
           int temp=0;
           time_t t;
           srand((unsigned)time(&t));
           // place human
           head_x=rand()%43;
           head_y=rand()%28;
           head_x=head_x*20+10;
           head_y=head_y*20+20;
           draw_head();
           getch (); // Holds the window for a while
           // place bots
           for(int i=0; i<6; ++i)
           {
                   bot_x[i]=rand()%43;
                   bot_y[i]=rand()%28;
                   if(place_bot(i))// place successfully
                   {
                            bot_x[i]=bot_x[i]*20+10;
                            bot_y[i]=bot_y[i]*20+20;
                            draw_bots(i);
                   }
                   else
                   {
                            i--;
                   }
           }
           while(temp==0)
           {
                   move();
                   collision();
                   temp=game_over();
           }
           setcolor(7);
           if(temp==2)
           {
                      lose();
                      getch();
           }
           else if(temp==1)
           {
                      outtextxy (455,622, "YOU WIN");
                      getch();
                      save(score);
           }
      }
      char menu(int x[])
      {
           char ch;
           cleardevice();
           setcolor(7);
           outtextxy(410,200,"ANGRY BOTS v1.0");
           setcolor(x[0]);
           outtextxy(450,230,"PLAY");
           setcolor(x[1]);
           outtextxy(450,250,"HELP");
           setcolor(x[2]);
           outtextxy(426,270,"HIGH-SCORES");
           setcolor(x[3]);
           outtextxy(450,290,"EXIT");
           setcolor(7);
           outtextxy(260,330,"Use W to move up and S to move down. Then Press Enter to Select");
           ch=getch();
           return ch;
      }
      void help()
      {
           cleardevice();
           setcolor(10);
           outtextxy(435,180,"H E L P");
           setcolor(7);
           outtextxy(420,220,"You are ");
           head_x=480; head_y=220;
           // draw human head
           draw_head();
           head_x=410; head_y=240;
           // draw bot head
           one_bot();
           setcolor(7);
           outtextxy(440,240," are Robots");
           outtextxy(360,260,"Use Q,W,E,A,S,D,Z,X,C to Move");
           outtextxy(390,280,"Use SPACE to Teleport");
           outtextxy(375,300,"Avoid Contact with Robots");
           outtextxy(365,320,"Robots Will Move Towards You");
           outtextxy(340,340,"Make the Robots collide with each other");
           outtextxy(370,380,"May The SOURCE Be With You!");
           getch();
      }
      void choose()
      {
           cleardevice();
           int x;
           char ch;
           ch=menu(color);
           if(ch==13)
           {
                 for(int i=0; i<4; i++)
                 {
                             if(color[i]==10)
                             {
                                     x=i;
                                     break;
                             }
                 }
                 switch(x)
                 {
                          case 0: cleardevice(); run(); choose(); break;
                          case 1: help(); choose(); break;
                          case 2: high_scores(); choose(); break;
                          case 3: credits(); exit(0);
                          default:;
                 }
           }
           else if(ch=='w')
           {
                for(int i=1; i<4; ++i)
                {
                        if(color[i]==10)
                        {
                                   color[i]=8;
                                   color[i-1]=10;
                                   break;
                        }
                }
                choose();
           }
           else if(ch=='s')
           {
                for(int i=0; i<3; ++i)
                {
                        if(color[i]==10)
                        {
                                   color[i]=8;
                                   color[i+1]=10;
                                   break;
                        }
                }
                choose();
           }
           else
           {
               choose();
           }
      }                              
};
int main ()
{
    game play;
    initwindow(920,650,"Angry Robots v1.0"); // Create the Game Window, paramter value is optimize for mode 1024 * 740 
    play.choose();

    closegraph (); // This close down the graphics 
    return 0;
}
