#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



//fonctions


int dif_date(int date_start[3], int date_end[3]){

    //storage

    int day[2] = {date_start[0],date_end[0]};
    int month[2] = {date_start[1],date_end[1]};
    int year[2] = {date_start[2],date_end[2]};

    //lenth of monthe : jan, fev ... dec
    int month_lenth[2][12] = {{31,28,31,30,31,30,31,31,30,31,30,31}, {31,28,31,30,31,30,31,31,30,31,30,31}};
    int year_lenth[2] = {365, 365};

    int number_of_day = 0;

    //leap year

    for(int i=0; i<2; i++){

        if (year[i] % 4 == 0){

            month_lenth[i][1] = 29;
        }

    }

    //year

    int number_of_year = year[1] - year[0] + 1;


    for(int i = 0; i != number_of_year; i++){

        if((year[0] + i) % 4 == 0){

            number_of_day += 366;
        }

        else{

            number_of_day += 365;
        }

    }

    //month

    for(int i = 0; i != (month[0]-1); i++){

        number_of_day -= month_lenth[0][i];
    }
   
    for(int i = 0; i != (12-month[1]); i++){

        number_of_day -= month_lenth[1][11-i];
        
    }

    //day

    number_of_day -= day[0];
    number_of_day -= month_lenth[1][month[1]-1] - day[1];

    return(number_of_day);

};


int calcul_persent_compleate(int creation_date[3],int actual_date[3], int end_date[3]){

    int day_gone = dif_date(creation_date,actual_date);
    int day_total = dif_date(creation_date,end_date);
    float persent_compleate = (float)day_gone / (float)day_total * 100;
    
    return(persent_compleate);


};

int calcul_persent_respect(int creation_date[3],int actual_date[3], int end_date[3], int iteration_compleate){
    int day_gone = dif_date(creation_date,actual_date);
    float persent_respect = (float)iteration_compleate / (float)day_gone * 100;
    return(persent_respect);
};

int convert_h_to_s(int hour[3]){

    int second = hour[2];
    second += hour[1] * 60;
    second += hour[0] * 3600;
    return(second);

};

int convert_s_to_h(int second, int return_date[3]){

    return_date[0] = second / 3600;
    second -= return_date[0] * 3600;
    return_date[1] = second / 60;
    return_date[2] = second % 60;
    return(0);

};