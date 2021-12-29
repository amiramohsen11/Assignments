#include <stdio.h>
#include <stdlib.h>

int menu(){
    int choice;
 
    system("clear");
    printf("\n\n                               scheduling CPU");
    printf("\n-------------------------------------------------------------------------------");
    printf("\n    Choose the algorithm you want to use to simulate the scheduler. \n");
    printf("\n                  < 1 > Firts-Come, First-Serve (FCFS)");
    printf("\n                  < 2 > Shortest-Job-First- (SRTF) ");
    printf("\n                  < 3 > non-preemptive priority ");
    printf("\n                  < 4 > Round Robin (RR) ");
    printf("\n                  < 5 > Exit \n");
    printf("\n     Your choice: ");
    scanf("%i", &choice);

    return choice;
}

int sch_cpu(){
    int choice;
    system("clear");
    printf("\n\n                                scheduling CPU");
    printf("\n-------------------------------------------------------------------------------\n\n");
    printf("                           Definition of processes.\n\n");
    printf("\n                  < 1 > Use processes established by the program.");
    printf("\n                  < 2 > Introduce new processes.");
    printf("\n\n     Your choice: ");
    scanf("%i", &choice);
    if (choice>2)
       sch_cpu();
    else
        return choice;
}

void top(){
    system("clear");
    printf("\n\n                               scheduling CPU");
    printf("\n-------------------------------------------------------------------------------\n\n");
}

struct process{
    int id;
    int dur;
    int prio;
    int execu;
    int esp;
    struct process *p;
    /*
        id - process identification
        dur - process duration time
        exe - process execution time
        esp -process timeout
    */
};

struct process *enter_process(int id, int dur, int prio){
    struct process *loc;
    loc = (struct process*)malloc(sizeof(struct process));
    if(loc == NULL){
        printf("Allocation error.\nEnd of execution\n");
        exit(1);
    };
    loc->id = id;
    loc->dur = dur;
    loc->prio = prio;
    loc->execu = 0;
    loc->esp = 0;
    loc->p = NULL;
}

void list_process(struct process *loc){
    struct process *tmp = loc;
    printf("\n\n\t\t\tList of processes\n\n");
    while(tmp != NULL){
        printf("\tProcess: %d\tPriority: %d\tBurst Time: %d\n", tmp->id, tmp->prio, tmp->dur);
        tmp = tmp->p;
    }
    printf("\n");
}

void fcfs(struct process *loc, int n_proc) {
    int tempo = 0, start ,end,tmp_esp=0, turnaround_time=0;
    int p1[n_proc], i=0;
    struct process *tmp = loc;
    printf("\n\t\t   Firts-Come, First-Serve (FCFS)\n\n");
    while (tmp != NULL){
       start = tempo;
        tempo += tmp->dur;
        p1[i] = tempo;
        end = tempo;
        printf("\tProcess: %d\t Burst Time %d\tStart: %d\tEnd: %d\n", tmp->id, tmp->dur, start, end);
        tmp_esp += start;
        tmp = tmp->p;
        i++;
    }
    i=0;
    printf("\n\t\tAverage Waiting Time= %f\n\n\n",tmp_esp*1.0/n_proc);
    printf("\t   Gantt chart");
    printf("\n\n\t\t    ");
    for (i=0; i<n_proc; i++){
            printf("| P1%d ", i+1);
    }
    printf("|");
    printf("\n\t\t    0  ");
    for (i=0; i<n_proc; i++)
        printf("  %d ", p1[i]);
}

void sjf(struct process *loc, int n_proc){
    int tempo_exe, shortest, start, end, tmp_esp, durc;
    struct process *copy, *src_tmp, *tmp, *before_shortest;
    printf("\n\t\tShortest-Job-First- (SRTF)\n\n ");
    src_tmp = loc;
    copy = tmp = NULL;
    while (src_tmp != NULL){/*making a copy of the processes*/
        if(copy == NULL){
            copy =enter_process(src_tmp->id, src_tmp->dur, src_tmp->prio);
            tmp = copy;
        }
        else{
            tmp->p = enter_process(src_tmp->id, src_tmp->dur, src_tmp->prio);
            tmp = tmp->p;
        }
        src_tmp = src_tmp->p;
    }
    tempo_exe = 0;
    while(copy != NULL){/*search for the new process*/
       before_shortest= NULL;
        shortest = copy->dur;
        tmp = copy->p;
        src_tmp = copy;
        while(tmp != NULL){
            if(tmp->dur < shortest){
                shortest = tmp->dur;
               before_shortest = src_tmp;
            }
            src_tmp = tmp;
            tmp = tmp->p;
        }
        if(before_shortest == NULL){
         start = tempo_exe;
            tempo_exe += copy->dur;
            durc = copy->dur;
            end = tempo_exe;
            printf("\tProcess: %d\t Burst Time: %d\tStart: %d\tEnd: %d\n", copy->id, durc, start, end);
            tmp_esp += end;
            src_tmp = copy;
            copy = copy->p;
            free(src_tmp);
        }
        else{ 
            tmp =  before_shortest->p;
           start= tempo_exe;
            tempo_exe += tmp->dur;
            durc = tmp->dur;
            end = tempo_exe;
            printf("\tProcess: %d\t Burst Time: %d\tStart: %d\tEnd:%d\n", tmp->id, durc, start, end);
           before_shortest->p = tmp->p;
            free(tmp);
        }
    }
    printf("\n\t\tAverage Waiting Time= %f\n",tmp_esp*1.0/n_proc);
} 

void sjf_simulator(struct process *loc, int n_proc){
    int tempo_exe, shortest, start, end, durc, i=0, p1[n_proc];
    struct process *copy, *src_tmp, *tmp, *before_shortest;
    printf("\n\t   Gantt chart\n\n ");
    src_tmp = loc;
    copy = tmp = NULL;
    while (src_tmp != NULL){
        if(copy == NULL){
            copy= enter_process(src_tmp->id, src_tmp->dur, src_tmp->prio);
            tmp = copy;
        }
        else{
            tmp->p = enter_process(src_tmp->id, src_tmp->dur, src_tmp->prio);
            tmp = tmp->p;
        }
        src_tmp = src_tmp->p;
    }
    tempo_exe = 0;
    printf("\t\t  ");
    while(copy != NULL){/*search for the new process*/
        before_shortest = NULL;
        shortest = copy->dur;
        tmp = copy->p;
        src_tmp = copy;
        while(tmp != NULL){
            if(tmp->dur < shortest){
                shortest = tmp->dur;
                before_shortest = src_tmp;
            }
            src_tmp = tmp;
            tmp = tmp->p;
        }
        if(before_shortest == NULL){
            start = tempo_exe;
            tempo_exe += copy->dur;
            durc = copy->dur;
            end = tempo_exe;
            p1[i]=tempo_exe;
            printf("| P1%d ", copy->id);
            src_tmp = copy;
            copy = copy->p;
            free(src_tmp);
        }
        else{ 
            tmp = before_shortest->p;
            start= tempo_exe;
            tempo_exe += tmp->dur;
            durc = tmp->dur;
            p1[i]=tempo_exe;
            end = tempo_exe;
            printf("| P1%d ", tmp->id);
            before_shortest->p = tmp->p;
            free(tmp);
        }
        i++;
    }
    printf("|");
    printf("\n\t\t  0  ");
    for (i=0; i<n_proc; i++)
        printf("  %d ", p1[i]);
}

void priority_scheduler(struct process *loc, int n_proc){
    int tempo_exe, start, major, end, tmp_esp, durc;
    struct process *copy, * src_tmp, *tmp, *major_prio;
    printf("\n\t\tScheduler with priority\n\n");
    src_tmp = loc;
    copy = tmp = NULL;
    while (src_tmp != NULL){
        if(copy== NULL){
            copy =  enter_process(src_tmp->id, src_tmp->dur, src_tmp->prio);
            tmp = copy;
        }
        else{
            tmp->p =  enter_process(src_tmp->id, src_tmp->dur, src_tmp->prio);
            tmp = tmp->p;
        }
        src_tmp = src_tmp->p;
    }
    tempo_exe = 0;
    while(copy != NULL){
        major_prio= NULL;
        major = copy->prio;
        tmp = copy->p;
        src_tmp = copy;
        while(tmp != NULL){
            if(tmp->prio < major){
                major = tmp->prio;
               major_prio= src_tmp;
            }
            src_tmp = tmp;
            tmp = tmp->p;
        }
        if(major_prio == NULL){
            start= tempo_exe;
            tempo_exe += copy->dur;
            durc = copy->dur;
            end = tempo_exe;
            printf("\tProcess: %d\tBurst Time: %d\tStart: %d\tEnd: %d\n", copy->id, durc, start, end);
            tmp_esp += end;
            src_tmp = copy->p;
            free(copy);
            copy = src_tmp;
        }
        else {
            tmp = major_prio ->p;
           start = tempo_exe;
            tempo_exe += tmp->dur;
            durc = tmp->dur;
            end = tempo_exe;
            printf("\tProcess: %d\t Burst Time: %d\tStart: %d\tEnd: %d\n", tmp->id, durc, start, end);
           major_prio->p = tmp->p;
            free(tmp);
        }
    }
    printf("\n\t\tAverage Waiting Time= %f\n",tmp_esp*1.0/n_proc);
}

void simulator_priority(struct process *loc, int n_proc){
    int tempo_exe, start, major, end, durc, i=0, p1[n_proc];
    struct process *copy, * src_tmp, *tmp, *major_prio;
    printf("\n\t   Gantt chart\n\n ");
    src_tmp = loc;
    copy = tmp = NULL;
    while (src_tmp != NULL){
        if(copy == NULL){
            copy = enter_process(src_tmp->id, src_tmp->dur, src_tmp->prio);
            tmp = copy;
        }
        else{
            tmp->p = enter_process(src_tmp->id, src_tmp->dur, src_tmp->prio);
            tmp = tmp->p;
        }
        src_tmp = src_tmp->p;
    }
    tempo_exe = 0;
    printf("\t\t  ");
    while(copy != NULL){
        major_prio = NULL;
        major = copy->prio;
        tmp = copy->p;
        src_tmp = copy;
        while(tmp != NULL){
            if(tmp->prio < major){
                major = tmp->prio;
                major_prio = src_tmp;
            }
            src_tmp = tmp;
            tmp = tmp->p;
        }
        if(major_prio == NULL){
           start= tempo_exe;
            tempo_exe += copy->dur;
            p1[i]=tempo_exe;
            durc = copy->dur;
            end = tempo_exe;
            printf("| P%d ", copy->id);
            src_tmp = copy->p;
            free(copy);
            copy = src_tmp;
        }
        else {
            tmp = major_prio->p;
            start = tempo_exe;
            tempo_exe += tmp->dur;
            p1[i]=tempo_exe;
            durc = tmp->dur;
            end = tempo_exe;
            printf("| P1%d ", tmp->id);
            major_prio->p = tmp->p;
            free(tmp);
        }
        i++;
    }
    printf("|");
    printf("\n\t\t  0  ");
    for (i=0; i<n_proc; i++)
        printf("  %d ", p1[i]);
}

void robbin_round(struct process *loc, int quantum, int n_proc){
    int count, j, time, remain, flag=0;
    int tmp_esp=0, turnaround_time=0, at[10], bt[10], rt[10];
    remain=n_proc;
    struct process *copy, *src_tmp, *tmp, *slot;
    printf("\n\t\tRound Robin (RR) - Quantum: %d\n", quantum);
    src_tmp = loc;
    for(count=0; count < n_proc; count++){
            bt[count] = src_tmp->dur;
            rt[count] = bt[count];
            src_tmp = src_tmp->p;
    }
    for(time = 0, count = 0; remain !=0;){
        at[count]=time;
        if(rt[count] <= quantum && rt[count] > 0){
            time+=rt[count];
            rt[count]=0;
            flag=1;
        }
        else if(rt[count]>0){
            rt[count]-=quantum;
            time+=quantum;
        }
        if(rt[count]==0 && flag==1){
            remain--;
            printf("\tProcess: %d\tStart: %d\tEnd: %d\n", count+1, time-bt[count], time);
            tmp_esp+=time-bt[count];
            turnaround_time+=time;
            flag=0;
        }
        if(count == n_proc-1)
            count=0;
        else if(at[count]<=time)
            count++;
        else
            count=0;
    }
    printf("\n\t      Average Waiting Time= %f\n",tmp_esp*1.0/n_proc); 
    printf("\t   Avgerage Turnaround Time = %f",turnaround_time*1.0/n_proc);
    free(src_tmp);
}

int main(){
    int esc, es_proc, n_proc, i, id, dur, prio, pos=0;
    do{
    if (pos==0){
        es_proc=sch_cpu();
    }
    else
        esc = menu();
    struct process *list_proc, *tmp_proc;
    if(es_proc == 1){
        n_proc = 4;
        list_proc = enter_process(1, 60, 3);
        list_proc->p = enter_process(2, 30, 2); tmp_proc = list_proc->p;
        tmp_proc->p  = enter_process(3,  40, 1); tmp_proc = tmp_proc->p;
        tmp_proc->p  = enter_process(4,  10, 4);
        esc = menu();
    }
    else if(es_proc==2){
        top();
        printf("\n\n  NOTE: Choose preferably for more than 3 processes");
        printf("\n\n   Enter the number of processes: ");
        scanf("%d", &n_proc);
        for(i=0; i<n_proc;i++){
            system("clear");
            top();
            printf("\n             Process %d: ", i+1);
            printf("\n\nEnter Burst time P1[%d]: ", i+1);
            scanf("%d", &dur);
            printf("Enter execution priority P1[%d]: ", i+1);
            scanf("%d", &prio);
            if(i==0)
                list_proc = enter_process(i+1, dur, prio);
            else if(i==1){
                list_proc->p =enter_process(i+1, dur, prio); tmp_proc = list_proc->p;
            }
            else if(i==n_proc-1){
                tmp_proc->p  = enter_process(i+1,  dur, prio);
            }
            else{
                tmp_proc->p  = enter_process(i+1,  dur, prio); tmp_proc = tmp_proc->p;
            }
        }
        pos=1;
        esc = menu();
    }

    if(esc == 1){
        system("clear");
       list_process(list_proc);
        fcfs(list_proc, n_proc);
        printf("\n\n\t< 1 > To come back\nChoice:");
        int i;
        scanf("%d", &i);
    }
    else if ( esc == 2){
        system("clear");
         list_process(list_proc);
        sjf(list_proc, n_proc);
        sjf_simulator(list_proc, n_proc);
        printf("\n\n\t< 1 >To come back\nChoice: ");
        int i;
        scanf("%d", &i);
    }
    else if (esc == 3){
        system("clear");
         list_process(list_proc);
         priority_scheduler(list_proc, n_proc);
      simulator_priority(list_proc, n_proc);
        printf("\n\n\t< 1 > To come back\nChoice: ");
        int i;
        scanf("%d", &i);
    }
    else if( esc == 4){
        system("clear");
        int quantum;
        list_process(list_proc);
        printf("\nEnter the desired time quantum: ");
        scanf("%d", &quantum);
        robbin_round(list_proc, quantum, n_proc);
        printf("\n\n\t< 1 > To come back\nChoice: ");
        int i;
        scanf("%d", &i);
    }
    else if( esc == 5){
        printf("\n\n End of program.\n\n");
        exit(2);
    }
    }while(esc <= 6);
    return 0;
}