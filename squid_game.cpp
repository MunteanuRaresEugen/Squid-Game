#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<time.h>

using namespace std;

int n = 108,cn = 99 ,sn = 9,Fr[108] = {0},Frnb[100] = {0},active_players = 99;
class Squid_Game{
    public:
    virtual void Hello() = 0;
};

class User : public Squid_Game{
    public:
        string f_name, l_name,city;
        int debt,weight,active;
    void Hello()
    {
        cout<<"Welcome to Squid Game.The game is about to start"<<endl;
    }
    void Hello(User u[108])
    {
        cout<<"Hello to all users"<<endl;
    }
    User();
    void read(User w[108]);
};

User::User()
{   
    for(int i = 0;i < n ;i++){
       f_name = "default";
       l_name = "default";
       city = "default";
       debt = 0;
       weight = 0;
       active = 1;
    }   
}

void User::read(User w[108])
{
    srand(time(0));
    ifstream myfile ("data.txt");
    int i = 0;
    string name,lname,cty;

    if (myfile.is_open())
    {
        while ( myfile>>name>>lname>>cty)
        {
        w[i].f_name = lname;
        w[i].l_name = name;
        w[i].city = cty;
        w[i].debt = (rand() % 90001) + 10000; // +1 on % to have 100000 included on debt,same as with weight with 100  
        w[i].weight = (rand() % 51) + 50;
        i++;
        }
        myfile.close();
    }
    else 
        cout << "Unable to open file"; 
}


class Competitor : public User {
    public:
        int cont_numb;
    void choose_competitors(Competitor comp[99],User w[108]);
    void printc(Competitor cp[99]);
    void sort(Competitor comp[99]); // the players eliminated are the beginning of the list after sort
    void showactive(Competitor comp[99]); 
    void sort_descending(Competitor comp[99]); // preparation for the last game(Genken).
    void RedLightGreenLight(Competitor comp[99]);
    void Tug_of_War(Competitor comp[99]);
    void Marbles(Competitor comp[99]);
    void Genken(Competitor comp[99]);
};

void Competitor::choose_competitors(Competitor comp[99],User w[108]){
    int x,i,count = 0,y;

    srand(time(0));

    do
    {
        x = rand() % 108;
        while(Fr[x] == 1)
            x = rand() % 108 ; // in w positions are from 0 to 107 
        Fr[x] = 1;  

        do
        {
          y = rand() % 99 + 1;
        } while (Frnb[y] == 1);

        Frnb[y] = 1;

        comp[count].f_name = w[x].f_name;
        comp[count].l_name = w[x].l_name;
        comp[count].city = w[x].city;
        comp[count].debt = w[x].debt;
        comp[count].weight = w[x].weight; 
        comp[count].cont_numb = y;

        count++;
        
    } while (count != 99);
}

void Competitor::printc(Competitor cp[99])
{
    for(int i = 0; i < cn ;i++)
        cout<<i<<" "<<cp[i].f_name<<" "<<cp[i].l_name<<" "<<cp[i].city<<" "<<cp[i].debt<<" "<<cp[i].weight<<" "<<cp[i].cont_numb<<" "<<cp[i].active<<endl;
}

void Competitor::sort(Competitor comp[99])
{
    int i,j;
    Competitor aux;

    for(i = 0;i < cn; i++)
        if(comp[i].active == 0)
        {
            aux = comp[i];
            for(int k = i; k >=1;k--)
                comp[k] = comp[k-1];
            comp[0] = aux;    
        }
}

void Competitor::showactive(Competitor comp[99])
{    
    for(int i = 0;i < cn; i++)
        if(comp[i].active == 1)
            cout<<comp[i].cont_numb<<" "<<comp[i].f_name<<" "<<comp[i].l_name<<endl;
}

void Competitor::sort_descending(Competitor comp[99]) 
{
    int i,j,poz = 0;
    Competitor aux;

    while(comp[poz].active == 0)
        poz++;
    
    for(i = poz;i < cn - 1; i++)
        for(j = i + 1; j < cn; j++)
            if(comp[i].cont_numb < comp[j].cont_numb)
                {
                    aux = comp[i];
                    comp[i] = comp[j];
                    comp[j] = aux;
                }
}

void Competitor::RedLightGreenLight(Competitor comp[99]){
    int i;

    for(i = 0;i < cn; i++)
        if(comp[i].cont_numb % 2 == 0)
            {
                comp[i].active = 0;
                active_players--;
            }
    cout<<endl<<"First game has ended.Here are the players remaining:"<<endl;
    comp->sort(comp);
    comp->showactive(comp);
}

void Competitor::Tug_of_War(Competitor comp[99])
{
    int numb_players = active_players/4,poz = 0,ok1 = 1,ok2 = 1,ok3 = 1,ok4 = 1,x;
    int t1[12],t2[12],t3[12],t4[12]; //i ll put the postition in my vector , to make the sum and eliminate them easily
    int Act[100]={0}, w1 = 0,w2 = 0,w3 = 0,w4 = 0;
    srand(time(0));

    while(comp[poz].active == 0)
        poz++;
    
    for(int i = 0; i < numb_players;i++)
    {   
        do
        {
            x = rand()%(99-poz) + poz; // +1 or not Idk yet
        } while (Act[x] == 1);
        Act[x] = 1;
        t1[i] = x;   
    }
    
    for(int i = 0; i < numb_players;i++)
    {   
        do
        {
            x = rand()%(99-poz) + poz;
        } while (Act[x] == 1);
        Act[x] = 1;
        t2[i] = x;
    }
    
    for(int i = 0; i < numb_players;i++)
    {   
        do
        {
            x = rand()%(99-poz) + poz;
        } while (Act[x] == 1);
        Act[x] = 1;
        t3[i] = x;
    }
    
    for(int i = 0; i < numb_players;i++)
    {   
        do
        {
            x = rand()%(99-poz) + poz;
        } while (Act[x] == 1);
        Act[x] = 1;
        t4[i] = x;
        
    }
    // If there are players which have no team,they automatically go in the next round because the param active will remain 1
    //So i ll take t1 vs t2 and t3 vs t4 in the "semifinals" and the winner of those will play in the final(we don't have third place play-off like in the world cup:)))) )
    for(int i = 0; i < 12;i++)
        w1+=comp[t1[i]].weight;
    
    for(int i = 0; i < 12;i++)
        w2+=comp[t2[i]].weight;
    
    for(int i = 0; i < 12;i++)
        w3+=comp[t3[i]].weight;
    
    for(int i = 0; i < 12;i++)
        w4+=comp[t4[i]].weight;
    
    if(w1 > w2){
        ok2 = 0;
        if(w3 > w4)
            {
                ok4 = 0;
                if(w1 > w3)
                    ok3 = 0;
                else
                    ok1 = 0;
            }
            else
            {
                ok3 = 0;
                if(w1 > w4)
                    ok4 = 0;
                else
                    ok1 = 0;
            }
    }
        else{
        ok1 = 0;
        if(w3 > w4)
            {
                ok4 = 0;
                if(w2 > w3)
                    ok3 = 0;
                else
                    ok2 = 0;
            }
            else
            {
                ok3 = 0;
                if(w2 > w4)
                    ok4 = 0;
                else
                    ok2 = 0;
            }
        }
    cout<<endl;
    cout<<w1<<" "<<w2<<" "<<w3<<" "<<w4<<endl;
    cout<<ok1<<" "<<ok2<<" "<<ok3<<" "<<ok4<<endl;
    active_players = active_players - 3*numb_players;
    cout<<numb_players<<" on every team "<<endl; //these are to check if it's ok
    cout<<"There are "<<active_players<<" players remaining"<<endl;
    if(ok1 == 1)
        for(int i = 0; i < numb_players ;i++)
        {
            comp[t2[i]].active = 0;
            comp[t3[i]].active = 0;
            comp[t4[i]].active = 0;
        }
        else
        if(ok2 == 1)
            for(int i = 0; i < numb_players ;i++)
            {
                comp[t1[i]].active = 0;
                comp[t3[i]].active = 0;
                comp[t4[i]].active = 0;
            }
        else
        if(ok3 == 1)
            for(int i = 0; i < numb_players ;i++)
            {
                comp[t1[i]].active = 0;
                comp[t2[i]].active = 0;
                comp[t4[i]].active = 0;
            }
        else
            for(int i = 0; i < numb_players ;i++)
            {
                comp[t1[i]].active = 0;
                comp[t2[i]].active = 0;
                comp[t3[i]].active = 0;
            }
    cout<<endl<<"The second game has ended.Here are the players remaining:"<<endl;
    comp->sort(comp);
    comp->showactive(comp);
    // Normally it must be 14 players left,but i get 15.Idk why.I saw where the mistake is:))))
}

void Competitor::Marbles(Competitor comp[99])
{
    int i,poz = 0,x,n1,n2;

    while(comp[poz].active == 0)
        poz++;
    
    if(active_players % 2 == 1)
        cout<<"The last one automatically goes to final"<<endl;
    
    i = poz;

    srand(time(0));

    // n1 is for comp[i] and n2 is for comp[i+1].Numbers generated are between 1 and 10.
    while(i < cn)
    {   
        do
        {
            n1 = rand() % 10 + 1;
            n2 = rand() % 10 + 1;
            
        } while (n1 == n2);

        if(n1 < n2)
            comp[i+1].active = 0;
            else
            comp[i].active = 0;
            
        i = i + 2;
    }
    cout<<endl<<"The third game has ended.Here are the players remaining:"<<endl;
    comp->sort(comp);
    comp->showactive(comp);

}

void Competitor::Genken(Competitor comp[99])
{
    int n1,n2,i,nb_avb = 0,count = 0 ;
    Competitor Final[17],x; //17 just to be sure 

    //comp->sort(comp);
    comp->sort_descending(comp); //starting in descending order according to the competition numbers
    cout<<endl<<"The players in the final are :"<<endl;
    comp->showactive(comp);

    i = 0;

    while(comp[i].active == 0)
        i++;
    
    nb_avb = 99 - i;

    while(i < cn)
    {
        Final[count] = comp[i];
        i++;
        count++;
    }

    /*for(i = 0;i < count;i++)
        cout<<Final[i].active<<" "<<Final[i].cont_numb<<" "<<Final[i].f_name<<" "<<Final[i].l_name<<endl;*/ //Just to check if everything is ok. 
    
    srand(time(0));
    
    while(count != 1)
    {
        do
        {
            n1 = rand() % 3 + 1;
            n2 = rand() % 3 + 1;
        }while(n1 == n2);
        // n1 is for Final[0] and n2 is for Final[1] 1-rock 2-paper 3-scissors.    
        if(n1 == 1 && n2 == 2) // rock vs paper,paper(2) wins
            {   
                x = Final[0];
                Final[0] = Final[1];
                Final[1] = x;
                for(i = 1;i < count;i++)
                    Final[i-1] = Final[i];
            }
        else
            if(n1 == 1 && n2 == 3) // rock vs scissors,rock(1) wins
                for(i = 1;i < count;i++)
                    Final[i-1] = Final[i];
        else
            if(n1 == 2 && n2 == 1) // paper vs rock,paper(2) wins
                for(i = 1;i < count;i++)
                    Final[i-1] = Final[i];
        else
            if(n1 == 2 && n2 == 3)  // paper vs scissors,scissors(3) wins
            {   
                x = Final[0];
                Final[0] = Final[1];
                Final[1] = x;
                for(i = 1;i < count;i++)
                    Final[i-1] = Final[i];
            }
        else
            if(n1 == 3 && n2 == 1) // scissors vs rock,rock(1) wins
            {   
                x = Final[0];
                Final[0] = Final[1];
                Final[1] = x;
                for(i = 1;i < count;i++)
                    Final[i-1] = Final[i];
            }
        else
            if(n1 == 3 && n2 == 2) // scissors vs paper,scissors(3) wins
                for(i = 1;i < count;i++)
                    Final[i-1] = Final[i];
            count--;

        // I considered only to compare Final[0] with Final[1] and eliminate on of them until there is 1 player left.If Final[0] wins I directly eliminate Final[1]
        // If Final[1] wins i swap Final[0] with Final[1] and I eliminate Final[1].I know this isn't the best way
        // When I took the screenshots I probably made a permutaion on the numbers of rock,paper and scissors and the final result might not be the corect one,but the logic is the same
        // I hope i didn't something wrong on this logic:))))

    }
    
    for(i = nb_avb;i < cn ;i++) // to mark the ones who are eliminated 
        if(comp[i].cont_numb !=Final[0].cont_numb)
            comp[i].active = 0;
    cout<<endl<<"The last game has ended.Here is the winner"<<endl;
    comp->sort(comp);
    comp->showactive(comp); //check here
}

class Supervisor : public User{
    private:
        string mask_form;
    public:
        int sup[11],win; // here every supervisor has 11 competitors on observation 
    void choose_supervisors(Supervisor s[9],User w[108]);
    void prints(Supervisor s[9]);
    void choose_sup_of_comp(Supervisor s[9]); // to find out supervisors' players on observation 
    void Final(Supervisor s[9],Competitor comp[99]);
    void set_maskform(string mask_f)
    {
        this->mask_form = mask_f;
    }
    string get_maskform()
    {
        return this->mask_form;
    }
};

void Supervisor::choose_supervisors(Supervisor s[9],User w[108])
{   
    int i,x,Fr9[10] = {0},count = 0;
    
    srand(time(0));
    
    for(i = 0; i < 108; i++)
        if(Fr[i] == 0)
        {
            Fr[i] = 1;
            do
            {
              x = rand() % 9 + 1;
            } while (Fr9[x] == 1);
        Fr9[x] = 1;    
        s[count].f_name = w[i].f_name;
        s[count].l_name = w[i].l_name;
        s[count].city = w[i].city;
        s[count].debt = w[i].debt;
        s[count].weight = w[i].weight; 
        if(x % 3 == 0)
            s[count].set_maskform("Rectangle");
            else
            if(x % 3 == 1)
                s[count].set_maskform("Triangle");
                else
                s[count].set_maskform("Circle");
        // from the 9 supervisors,we have to make group equals of 3 for each masks so i considered the rest of divison with 3 like:0- rectangle, 1 -triangle ,2-circle 
        count++;
        }    
}

void Supervisor::prints(Supervisor s[9])
{
    for(int i = 0; i < sn ;i++)
        cout<<i<<" "<<s[i].f_name<<" "<<s[i].l_name<<" "<<s[i].city<<" "<<s[i].debt<<" "<<s[i].weight<<" "<<s[i].get_maskform()<<endl;
}

void Supervisor::choose_sup_of_comp(Supervisor s[9])
{
    // I will do the parting in depending on the content number
    // i considered the group of supervisors depending on mask form already.
    int i,F[99] ={0},j,x; 
    
    srand(time(0));

    for(i = 0; i < 9 ; i++){
        int count = 0;
        for(j = 0; j < 11;j++)
        {  
            do
            {
                x = rand() % 99 + 1;
            } while (F[x] == 1);
            F[x] = 1;
            s[i].sup[count] = x;
            count++;
        }
    }
}

void Supervisor::Final(Supervisor s[9],Competitor comp[99])
{   
    long long total_win = 0,rect_win = 0,circ_win = 0,triang_win = 0;
    int i,j,found,k;
    Supervisor aux;
   
    for(i = 0;i< cn - 1; i++)
        total_win +=comp[i].debt;
    cout<<endl<<"The winner has won "<<total_win<<"$"<<endl;

    for(i = 0;i < sn; i++)
        {   
            s[i].win = 0;
            for(j = 0;j < 11;j++)
                {
                    found = 0;
                    while(found < cn && comp[found].cont_numb != s[i].sup[j] )
                        found++;
                    if(found == cn)
                        s[i].win = comp[found].debt *10; 
                        else
                        s[i].win+=comp[found].debt;
                }
            s[i].win = s[i].win - s[i].debt;
        }
    for(i = 0; i < sn - 1; i++)
        for(j = i+1 ; j < sn; j++)
            if(s[i].win < s[j].win)
            {
                aux = s[i];
                s[i] = s[j];
                s[j] = aux;
            }
    cout<<endl<<"The ranking of the supervisors:"<<endl; 
    for(i = 0; i < sn ; i++)
    {
        cout<<s[i].f_name<<" "<<s[i].l_name<<" "<<s[i].get_maskform()<<" "<<s[i].win<<"$"<<endl;
        if(s[i].get_maskform() == "Rectangle")
            rect_win += s[i].win;
            else
            if(s[i].get_maskform() == "Triangle")
                triang_win += s[i].win;
                else
                if(s[i].get_maskform() == "Circle")
                circ_win += s[i].win;
    }
    cout<<triang_win<<" "<<rect_win<<" "<<circ_win<<endl;
    try
    {   
        if(triang_win > circ_win && triang_win > rect_win)
            throw "Triangle";
            else
            if(circ_win > triang_win && circ_win > rect_win )
                throw "Circle";
                else
                    throw "Rectangle";
    }
    catch(const char *team)
    {
        cout<<endl<<team<<" team has earned the most money "<<endl;
    }
    // I don't know why triang_win,rect_win,circ_win are all 0.When i checked first time, everything was good.I'm an idiot.I didn't wrote them with capital letters when calculation every sum.
}

template <class T>
void print(T a[],int length)
{   
    for(int i = 0; i < length;i++)
        cout<<i+1<<" "<<a[i].f_name<<" "<<a[i].l_name<<" "<<a[i].city<<" "<<a[i].debt<<" "<<a[i].weight<<endl;
}

int main()
{   
    
    User v[108];
    Competitor comp1[99];
    Supervisor s1[9];

    v->Hello();
    v->Hello(v);
    v->read(v);
    //print<User>(v,108);
    comp1->choose_competitors(comp1,v);
    //comp1->printc(comp1);
    s1->choose_supervisors(s1,v);
    //s1->prints(s1); I don't show these because there are to many lines in the output
    s1->choose_sup_of_comp(s1);

    comp1->RedLightGreenLight(comp1);
    comp1->Tug_of_War(comp1);
    comp1->Marbles(comp1);
    comp1->Genken(comp1);
    s1->Final(s1,comp1);
    
    return 0;
}