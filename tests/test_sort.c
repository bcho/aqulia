#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "test.h"
#include "../src/core/consume_record.h"
#include "../src/core/sort.h"

#define PRT(record) printf("consumed: %s received: %s\n"\
                           "sum: %.2lf balance: %.2lf\n"\
                           "type: %d\ntranscation: %d pos: %s\n\n",\
                           record->consumed, record->received, record->sum,\
                           record->balance, record->consume_type, record->pos->transcation,\
                           record->pos->name)

void *next(void *cur)
{
    return ((struct consume_record *) cur)->next;
}

void set_next(void *cur, void *value)
{
    ((struct consume_record *) cur)->next = value;
}

int cmp(void *a, void *b)
{
    struct consume_record *c, *d;
    int ret;

    return -1 * strcmp(((struct consume_record *) a)->consumed,
    ((struct consume_record *) b)->consumed);
    ret = strcmp(c->consumed, d->consumed);
    if (ret == 0)
        if (c->balance > d->balance)
            ret = 1;
        else if (c->balance < d->balance)
            ret = -1;
    return ret * -1;
}

int main()
{
    struct consume_record *record, *p;
    char *data = TESTCASES_DIR"/fee.dat";

    record = consume_record_read(data);
    /*
    for (p = record;p != NULL;p = p->next)
        PRT(p);
    */
    sort((void **) &record, next, set_next, cmp, 0);
    for (p = record;p != NULL;p = p->next)
        PRT(p);
    printf("--------\n");
    sort((void **) &record, next, set_next, cmp, 1);
    for (p = record;p != NULL;p = p->next)
        PRT(p);
    consume_record_destory(record);

    return 0;
}
