#ifndef __HITABLELIST_H__
#define __HITABLELIST_H__

#include "hitable.h"

class HitableList : public Hitable
{
public:
    HitableList() {}
    HitableList(Hitable **list, int n) : list(list), length(n) {}
    ~HitableList() {}

    virtual bool hit(const Ray& r, real t_min, real t_max, HitRecord& rec) const;

private:
    Hitable **list;
    int length;
};

bool HitableList::hit(const Ray& r, real t_min, real t_max, HitRecord& rec) const
{
    HitRecord tempRec;
    bool bHitAny = false;
    real closest = t_max;
    for (int i = 0; i < length; i++)
    {
        if (list[i]->hit(r, t_min, closest, tempRec))
        {
            bHitAny = true;
            closest = tempRec.t;
            rec = tempRec;
        }
    }
    return bHitAny;
}

#endif // !__HITABLELIST_H__
