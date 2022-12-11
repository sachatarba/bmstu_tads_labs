#include "../inc/queue_array_t.h"
#include "../inc/queue_list_t.h"
#include "../inc/request_t.h"
#include "../inc/sleep_time.h"
#include <math.h>
#include <stdio.h>

#define EPS 1e-7

float min_of_three(float a, float b, float c)
{
    float min = a;

    if (min > b)
    {
        min = b;
    }

    if (min > c)
    {
        min = c;
    }

    return min;
}


float rand_time(int min, int max)
{
    //srand(time(NULL));

    return (max - min) * (float)(rand()) / (float)RAND_MAX + min;
}

void process(bool is_list, request_t *req1, request_t *req2)
{
    if (!is_list)
    {
        // queue_array_t *arr1 = create_array(20000);
        // queue_array_t *arr2 = create_array(20000);
        // request_t *temp1 = NULL;
        // request_t *temp2 = NULL;
        
        // size_t counter = 0;
        // while (1)
        // {
        //     double t1 = rand_double(req1->min_in, req1->max_in, 6);
        //     double t2 = rand_double(req2->min_in, req2->max_in, 6);
            
        //     // if (t2 > t1)
        //     // {
            
            
        //     temp1 = create_req(req1->min_in, req1->max_in, req1->min_proc, req1->max_proc);
        //     temp2 = create_req(req2->min_in, req2->max_in, req2->min_proc, req2->max_proc);
        //     sleep_usecs(t1);
        //     timespec_get(&temp1->in_time, TIME_UTC);
        //     push_array(arr1, temp1);
        //     sleep_usecs(t2 - t1);
        //     timespec_get(&temp2->in_time, TIME_UTC);
        //     push_array(arr2, temp2);
        //     // }
        //     // else
        //     // {
        //     //     temp1 = create_req(req1->min_in, req1->max_in, req1->min_proc, req1->max_proc);
        //     //     temp2 = create_req(req2->min_in, req2->max_in, req2->min_proc, req2->max_proc);
        //     //     sleep_usecs(t2);
        //     //     timespec_get(&temp2->in_time, TIME_UTC);
        //     //     push_array(arr2, temp2);
        //     //     sleep_usecs(t1 - t2);
        //     //     timespec_get(&temp1->in_time, TIME_UTC);
        //     //     push_array(arr1, temp1);
        //     // // }
        //     // rand_sleep(req1->min_in, req1->max_in, 6);
        //     // push_array(arr1, p);
        // }
    // }

        request_t *temp1 = NULL;
        request_t *temp2 = NULL;

        queue_array_t *queue1 = create_array(10000);

        int q1_req_in = 0;  // заявок вошло
        int q1_req_out = 0; // заявок вышло
        int q1_req_all = 0; // количество раз работы с очередью
        int q1_len_all = 0; // вся длина очереди (для среднего значения)
        float q1_time_in_queue = 0;
        float q1_time_all = 0; // общее время для всей первой очереди
        int q1_len_cur = 0; // текущая длина очереди

        queue_array_t *queue2 = create_array(10000);

        int q2_req_in = 0; 
        int q2_req_out = 0;
        int q2_req_all = 0;
        int q2_len_all = 0;
        float q2_time_in_queue = 0;
        float q2_time_all = 0; // общее время для всей второй очереди
        int q2_len_cur = 0;

        // дополнительные переменные подсчета

        float q1_cur_time_in = 0;
        //float q1_cur_time_work = 0;
        float q2_cur_time_in = 0;
        //float q2_cur_time_work = 0;

        //int q1_req_out_all = 0;

        int queue_type = 0;
        float oa_time = 0;


        float time_all = 0; // общее время

        int to_show = 0;

        int in_push = 0, in_pop = 0;

        while (q1_req_out < 1000)
        {
            if (fabs(q1_cur_time_in) < EPS)
            {
                q1_cur_time_in = rand_time(req1->min_in, req1->max_in);
            }

            if (fabs(q2_cur_time_in) < EPS)
            {
                q2_cur_time_in = rand_time(req2->min_in, req2->max_in);
            }

            if (fabs(oa_time) < EPS)
            {
                // если время работы аппарата = 0, то загрузить его работой с первой очередью, иначе - со второй
                if (!is_empty_array(queue1))
                {
                    //puts("YESSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS!!!!!!!");
                    oa_time = rand_time(req1->min_proc, req1->max_proc);
                    queue_type = 1;
                    request_t *temp = create_req(0, 0, 0, 0); 
                    pop_array(queue1, (void **) &temp);
                    q1_time_in_queue += time_all - temp->in_time;
                    free_req(&temp);

                    in_pop++;

                    q1_len_cur--;
                    q1_req_all++;
                    q1_len_all += q1_len_cur;

                    q1_time_all += oa_time;
                }
                else if (!is_empty_array(queue2))
                {
                    // puts("!!!!!!!YESSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS");
                    oa_time = rand_time(req2->min_proc, req2->max_proc);
                    queue_type = 2;
                    request_t *temp = create_req(0, 0, 0, 0); 
                    pop_array(queue2, (void **) &temp);
                    q2_time_in_queue += time_all - temp->in_time;
                    free_req(&temp);

                    q2_len_cur--;
                    q2_req_all++;
                    q2_len_all += q2_len_cur;

                    q2_time_all += oa_time;
                }            
            }
        

            float min_time = 0;

            //printf("\n\n oa = %f\nq1_cur_time_in = %f\nq2_cur_time_in = %f\n\n", oa_time, q1_cur_time_in, q2_cur_time_in);

            // если обработки нет, то ищем тот элемент, что будет добавлен быстрее (в 1 или во 2 очередь)
            if (oa_time == 0)
            {
                min_time = min_of_three(q1_cur_time_in, q2_cur_time_in, q1_cur_time_in);
            }
            // если есть обработки, то решаем, какой процесс быстрее - произвести обработку или добавить элемент из какой-то из очередей
            else
            {
                min_time = min_of_three(q1_cur_time_in, q2_cur_time_in, oa_time);
            }

            //printf("\nmin time = %f\n\n", min_time);

            // если обработка быстрее
            if (fabs(oa_time - min_time) < EPS)
            {
                //printf("\n\ntype = %d\n\n", queue_type);
                oa_time = 0;

                if (queue_type == 1)
                {
                    //puts("yessssssssssssssssssssssssssssssssssssssssss");
                    q1_req_out++;
                }
                else if (queue_type == 2)
                {
                    q2_req_out++;
                }
            }

            //printf("\n\n oa = %f\nq1_cur_time_in = %f\nq2_cur_time_in = %f\n\n", oa_time, q1_cur_time_in, q2_cur_time_in);

            // если добавлене элемента в 1ую очередь быстрее
            if (fabs(q1_cur_time_in - min_time) < EPS)
            {
                //puts("YESSSSSSSSSSSSSSSSSSSSSSSSSSS");
                temp1 = create_req(0,0,0,0);
                temp1->in_time = time_all;
                push_array(queue1, temp1);

                in_push++;

                q1_req_in++;
                q1_len_cur++;
                q1_req_all++;
                q1_len_all += q1_len_cur;
            }
            // если добавлене элемента в 2ую очередь быстрее
            if (fabs(q2_cur_time_in - min_time) < EPS)
            {
                temp2 = create_req(0,0,0,0);
                temp2->in_time = time_all;
                push_array(queue2, temp2);

                q2_req_in++;
                q2_len_cur++;
                q2_req_all++;
                q2_len_all += q2_len_cur;
            }


            // Оставшееся время для добавления заявки
            q1_cur_time_in -= min_time;
            q2_cur_time_in -= min_time;

            if (oa_time >= min_time)
            {
                oa_time -= min_time;
            }

            time_all += min_time;


            // info every 100
            if ((q1_req_out % 100 == 0) && (q1_req_out != to_show))
            {
                to_show = q1_req_out;
                // printf("Заявок 1го типа обработано = %d\n\n", q1_req_out);
                printf("---------------------------------------------------------------------------------\n");
                printf("Текущая длина очереди 1го типа = %d\n", q1_len_cur);
                printf("Средняя длина очереди 1го типа = %f\n\n", (float)((float)q1_len_all / q1_req_all));

                printf("Текущая длина очереди 2го типа = %d\n", q2_len_cur);
                printf("Средняя длина очереди 2го типа = %f\n\n\n", (float)((float)q2_len_all / q2_req_all));

                printf("Количество вошедших заявок 1го типа = %d\n", q1_req_in);
                printf("Количество вышедших заявок 1го типа = %d\n\n", q1_req_out);

                printf("Количество вошедших заявок 2го типа = %d\n", q2_req_in);
                printf("Количество вышедших заявок 2го типа = %d\n\n", q2_req_out);

                printf("Среднее время пребывания в очереди заявок 1го типа = %lf\n", (q1_time_in_queue) / q1_req_out);
                printf("Среднее время пребывания в очереди заявок 2го типа = %lf\n\n", (q2_time_in_queue) / q2_req_out);
                printf("---------------------------------------------------------------------------------\n");

            }

        }

        float avg_q1_in = (req1->min_in + req1->max_in) / 2;
        float all_avg_q1_in = avg_q1_in * 1000;

        float avg_q1_out = (req1->min_proc + req1->max_proc) / 2;
        float all_avg_q1_out = avg_q1_out * 1000;

        float avg_q2_in = (float)(req2->min_in + req2->max_in) / (float)2;

        
        float estimate_model_time;

        if (all_avg_q1_in > all_avg_q1_out)
        {
            estimate_model_time = all_avg_q1_in;
        }
        else
        {
            estimate_model_time = all_avg_q1_out;
        }

        float percent_oa = fabs((time_all - estimate_model_time) * 100 / estimate_model_time);

        printf("\n\nОбщее время моделировния = %f \
        \nПогрешность моделирования = %f процентов\n\n", time_all, percent_oa);

        printf("\nЗаявок вошло в 1ую очередь = %d \
        \nЗаявок 1ой очереди вышло = %d \
        \nСреднее время обработки заявки в 1ой очереди (ожидаемое) = %f\n\n", q1_req_in, q1_req_out, avg_q1_in);

        printf("\nЗаявок вошло во 2ую очередь = %d \
        \nЗаявок 2ой очереди вышло = %d \
        \nСреднее время обработки заявки в 2ой очереди (ожидаемое) = %f\n\n", q2_req_in, q2_req_out, avg_q2_in);

        float time_in1 = time_all / avg_q1_in;
        float percent_time_in1 = fabs((q1_req_in - time_in1) * 100 / time_in1);

        float time_in2 = time_all / avg_q2_in;
        float percent_time_in2 = fabs((q2_req_in - time_in2) * 100 / time_in2);

        printf("Погрешность ввода заявок в 1ую очередь %f процентов \
        \nПогрешность ввода заявок во 2ую очередь %f процентов\n\n", percent_time_in1, percent_time_in2);


        float all_estimate_work = q1_time_all + q2_time_all;
        float time_wait = time_all - all_estimate_work;

        printf("\nВремя простоя = %f\n\n", fabs(time_wait));
    }
    else
    {
        request_t *temp1 = NULL;
        request_t *temp2 = NULL;

        queue_list_t *queue1 = create_list(10000);

        int q1_req_in = 0;  // заявок вошло
        int q1_req_out = 0; // заявок вышло
        int q1_req_all = 0; // количество раз работы с очередью
        int q1_len_all = 0; // вся длина очереди (для среднего значения)
        float q1_time_in_queue = 0;
        float q1_time_all = 0; // общее время для всей первой очереди
        int q1_len_cur = 0; // текущая длина очереди

        queue_list_t *queue2 = create_list(10000);

        int q2_req_in = 0; 
        int q2_req_out = 0;
        int q2_req_all = 0;
        int q2_len_all = 0;
        float q2_time_in_queue = 0;
        float q2_time_all = 0; // общее время для всей второй очереди
        int q2_len_cur = 0;

        // дополнительные переменные подсчета

        float q1_cur_time_in = 0;
        //float q1_cur_time_work = 0;
        float q2_cur_time_in = 0;
        //float q2_cur_time_work = 0;

        //int q1_req_out_all = 0;

        int queue_type = 0;
        float oa_time = 0;


        float time_all = 0; // общее время

        int to_show = 0;

        int in_push = 0, in_pop = 0;

        while (q1_req_out < 1000)
        {
            if (fabs(q1_cur_time_in) < EPS)
            {
                q1_cur_time_in = rand_time(req1->min_in, req1->max_in);
            }

            if (fabs(q2_cur_time_in) < EPS)
            {
                q2_cur_time_in = rand_time(req2->min_in, req2->max_in);
            }

            if (fabs(oa_time) < EPS)
            {
                // если время работы аппарата = 0, то загрузить его работой с первой очередью, иначе - со второй
                if (!is_empty_list(queue1))
                {
                    //puts("YESSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS!!!!!!!");
                    oa_time = rand_time(req1->min_proc, req1->max_proc);
                    queue_type = 1;
                    request_t *temp = create_req(0, 0, 0, 0); 
                    pop_list(queue1, (void **) &temp);
                    q1_time_in_queue += time_all - temp->in_time;
                    free_req(&temp);

                    in_pop++;

                    q1_len_cur--;
                    q1_req_all++;
                    q1_len_all += q1_len_cur;

                    q1_time_all += oa_time;
                }
                else if (!is_empty_list(queue2))
                {
                    // puts("!!!!!!!YESSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS");
                    oa_time = rand_time(req2->min_proc, req2->max_proc);
                    queue_type = 2;
                    request_t *temp = create_req(0, 0, 0, 0); 
                    pop_list(queue2, (void **) &temp);
                    q2_time_in_queue += time_all - temp->in_time;
                    free_req(&temp);

                    q2_len_cur--;
                    q2_req_all++;
                    q2_len_all += q2_len_cur;

                    q2_time_all += oa_time;
                }            
            }
        

            float min_time = 0;

            //printf("\n\n oa = %f\nq1_cur_time_in = %f\nq2_cur_time_in = %f\n\n", oa_time, q1_cur_time_in, q2_cur_time_in);

            // если обработки нет, то ищем тот элемент, что будет добавлен быстрее (в 1 или во 2 очередь)
            if (oa_time == 0)
            {
                min_time = min_of_three(q1_cur_time_in, q2_cur_time_in, q1_cur_time_in);
            }
            // если есть обработки, то решаем, какой процесс быстрее - произвести обработку или добавить элемент из какой-то из очередей
            else
            {
                min_time = min_of_three(q1_cur_time_in, q2_cur_time_in, oa_time);
            }

            //printf("\nmin time = %f\n\n", min_time);

            // если обработка быстрее
            if (fabs(oa_time - min_time) < EPS)
            {
                //printf("\n\ntype = %d\n\n", queue_type);
                oa_time = 0;

                if (queue_type == 1)
                {
                    //puts("yessssssssssssssssssssssssssssssssssssssssss");
                    q1_req_out++;
                }
                else if (queue_type == 2)
                {
                    q2_req_out++;
                }
            }

            //printf("\n\n oa = %f\nq1_cur_time_in = %f\nq2_cur_time_in = %f\n\n", oa_time, q1_cur_time_in, q2_cur_time_in);

            // если добавлене элемента в 1ую очередь быстрее
            if (fabs(q1_cur_time_in - min_time) < EPS)
            {
                //puts("YESSSSSSSSSSSSSSSSSSSSSSSSSSS");
                temp1 = create_req(0,0,0,0);
                temp1->in_time = time_all;
                push_list(queue1, temp1);

                in_push++;

                q1_req_in++;
                q1_len_cur++;
                q1_req_all++;
                q1_len_all += q1_len_cur;
            }
            // если добавлене элемента в 2ую очередь быстрее
            if (fabs(q2_cur_time_in - min_time) < EPS)
            {
                temp2 = create_req(0,0,0,0);
                temp2->in_time = time_all;
                push_list(queue2, temp2);

                q2_req_in++;
                q2_len_cur++;
                q2_req_all++;
                q2_len_all += q2_len_cur;
            }


            // Оставшееся время для добавления заявки
            q1_cur_time_in -= min_time;
            q2_cur_time_in -= min_time;

            if (oa_time >= min_time)
            {
                oa_time -= min_time;
            }

            time_all += min_time;


            // info every 100
            if ((q1_req_out % 100 == 0) && (q1_req_out != to_show))
            {
                to_show = q1_req_out;
                // printf("Заявок 1го типа обработано = %d\n\n", q1_req_out);
                printf("---------------------------------------------------------------------------------\n");
                printf("Текущая длина очереди 1го типа = %d\n", q1_len_cur);
                printf("Средняя длина очереди 1го типа = %f\n\n", (float)((float)q1_len_all / q1_req_all));

                printf("Текущая длина очереди 2го типа = %d\n", q2_len_cur);
                printf("Средняя длина очереди 2го типа = %f\n\n\n", (float)((float)q2_len_all / q2_req_all));

                printf("Количество вошедших заявок 1го типа = %d\n", q1_req_in);
                printf("Количество вышедших заявок 1го типа = %d\n\n", q1_req_out);

                printf("Количество вошедших заявок 2го типа = %d\n", q2_req_in);
                printf("Количество вышедших заявок 2го типа = %d\n\n", q2_req_out);

                printf("Среднее время пребывания в очереди заявок 1го типа = %lf\n", (q1_time_in_queue) / q1_req_out);
                printf("Среднее время пребывания в очереди заявок 2го типа = %lf\n\n", (q2_time_in_queue) / q2_req_out);
                printf("---------------------------------------------------------------------------------\n");

            }

        }

        float avg_q1_in = (req1->min_in + req1->max_in) / 2;
        float all_avg_q1_in = avg_q1_in * 1000;

        float avg_q1_out = (req1->min_proc + req1->max_proc) / 2;
        float all_avg_q1_out = avg_q1_out * 1000;

        float avg_q2_in = (float)(req2->min_in + req2->max_in) / (float)2;

        
        float estimate_model_time;

        if (all_avg_q1_in > all_avg_q1_out)
        {
            estimate_model_time = all_avg_q1_in;
        }
        else
        {
            estimate_model_time = all_avg_q1_out;
        }

        float percent_oa = fabs((time_all - estimate_model_time) * 100 / estimate_model_time);

        printf("\n\nОбщее время моделировния = %f \
        \nПогрешность моделирования = %f процентов\n\n", time_all, percent_oa);

        printf("\nЗаявок вошло в 1ую очередь = %d \
        \nЗаявок 1ой очереди вышло = %d \
        \nСреднее время обработки заявки в 1ой очереди (ожидаемое) = %f\n\n", q1_req_in, q1_req_out, avg_q1_in);

        printf("\nЗаявок вошло во 2ую очередь = %d \
        \nЗаявок 2ой очереди вышло = %d \
        \nСреднее время обработки заявки в 2ой очереди (ожидаемое) = %f\n\n", q2_req_in, q2_req_out, avg_q2_in);

        float time_in1 = time_all / avg_q1_in;
        float percent_time_in1 = fabs((q1_req_in - time_in1) * 100 / time_in1);

        float time_in2 = time_all / avg_q2_in;
        float percent_time_in2 = fabs((q2_req_in - time_in2) * 100 / time_in2);

        printf("Погрешность ввода заявок в 1ую очередь %f процентов \
        \nПогрешность ввода заявок во 2ую очередь %f процентов\n\n", percent_time_in1, percent_time_in2);


        float all_estimate_work = q1_time_all + q2_time_all;
        float time_wait = time_all - all_estimate_work;

        printf("\nВремя простоя = %f\n\n", fabs(time_wait));
    }
}