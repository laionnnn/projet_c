#ifndef STAT_H
#define STAT_H

int dif_date(int date_start[3], int date_end[3]);
int calcul_persent_compleate(int creation_date[3],int actual_date[3], int end_date[3]);
int calcul_persent_respect(int creation_date[3],int actual_date[3], int end_date[3], int iteration_compleate);
int convert_h_to_s(int hour[3]);
int convert_s_to_h(int second, int return_date[3]);


#endif