#ifndef DUMPER_OBJ_H
#define DUMPER_OBJ_H

struct DumperObj {
    DumperObj * prev;
    DumperObj * next;

    DumperObj(DumperObj * prev_token = 0) : prev(0), next(0) {
        if ((prev = prev_token)) {
            if ((next = prev -> next))
                next -> prev = this;

            prev -> next = this;
        }
    }

    ~DumperObj() {
        delete next;
    }
};


#endif // DUMPER_OBJ_H
