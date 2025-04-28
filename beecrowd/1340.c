#include <stdio.h>

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        int stack[1000], stack_top = -1;
        int queue[1000], q_front = 0, q_rear = 0;
        int pq[1000], pq_size = 0;

        int is_stack = 1, is_queue = 1, is_pq = 1;

        for (int i = 0; i < n; i++) {
            int op, x;
            scanf("%d", &op);
            if (op == 1) {
                scanf("%d", &x);
                stack[++stack_top] = x;
                queue[q_rear++] = x;

                int pos = pq_size++;
                while (pos > 0 && pq[(pos - 1) / 2] < x) {
                    pq[pos] = pq[(pos - 1) / 2];
                    pos = (pos - 1) / 2;
                }
                pq[pos] = x;
            } else {
                scanf("%d", &x);
                if (is_stack) {
                    if (stack_top < 0 || stack[stack_top--] != x)
                        is_stack = 0;
                }
                if (is_queue) {
                    if (q_front == q_rear || queue[q_front++] != x)
                        is_queue = 0;
                }
                if (is_pq) {
                    if (pq_size == 0) {
                        is_pq = 0;
                    } else {
                        int max = pq[0];
                        int last = pq[--pq_size];
                        int i = 0;
                        while (i * 2 + 1 < pq_size) {
                            int child = i * 2 + 1;
                            if (child + 1 < pq_size && pq[child] < pq[child + 1])
                                child++;
                            if (last >= pq[child])
                                break;
                            pq[i] = pq[child];
                            i = child;
                        }
                        pq[i] = last;
                        if (max != x)
                            is_pq = 0;
                    }
                }
            }
        }

        int possible = is_stack + is_queue + is_pq;
        if (possible == 0)
            printf("impossible\n");
        else if (possible > 1)
            printf("not sure\n");
        else if (is_stack)
            printf("stack\n");
        else if (is_queue)
            printf("queue\n");
        else
            printf("priority queue\n");
    }

    return 0;
}
