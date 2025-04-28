#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

typedef struct {
    int time_per_item;
    int id;
    long long next_free_time;
} Cashier;

Cashier heap[MAX];
int heap_size = 0;

int compare(Cashier a, Cashier b) {
    if (a.next_free_time != b.next_free_time)
        return a.next_free_time < b.next_free_time;
    return a.id < b.id;
}

void swap(int i, int j) {
    Cashier tmp = heap[i];
    heap[i] = heap[j];
    heap[j] = tmp;
}

void heap_push(Cashier c) {
    int i = heap_size++;
    heap[i] = c;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (compare(heap[p], heap[i]))
            break;
        swap(p, i);
        i = p;
    }
}

Cashier heap_pop() {
    Cashier ret = heap[0];
    heap[0] = heap[--heap_size];
    int i = 0;
    while (2 * i + 1 < heap_size) {
        int child = 2 * i + 1;
        if (child + 1 < heap_size && compare(heap[child + 1], heap[child]))
            child++;
        if (compare(heap[i], heap[child]))
            break;
        swap(i, child);
        i = child;
    }
    return ret;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int vi[N], cj[M];
    for (int i = 0; i < N; i++)
        scanf("%d", &vi[i]);
    for (int i = 0; i < M; i++)
        scanf("%d", &cj[i]);

    for (int i = 0; i < N; i++) {
        Cashier c = {vi[i], i, 0};
        heap_push(c);
    }

    long long max_time = 0;
    for (int i = 0; i < M; i++) {
        Cashier c = heap_pop();
        long long time_needed = (long long)c.time_per_item * cj[i];
        c.next_free_time += time_needed;
        if (c.next_free_time > max_time)
            max_time = c.next_free_time;
        heap_push(c);
    }

    printf("%lld\n", max_time);
    return 0;
}
