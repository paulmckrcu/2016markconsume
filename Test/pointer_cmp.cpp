namespace std {

bool pointer_cmp_eq_dep(void* p, void* q) noexcept
{
    return p == q;
}

bool pointer_cmp_ne_dep(void* p, void* q) noexcept
{
    return p != q;
}

bool pointer_cmp_gt_dep(void* p, void* q) noexcept
{
    return p > q;
}

bool pointer_cmp_ge_dep(void* p, void* q) noexcept
{
    return p >= q;
}

bool pointer_cmp_lt_dep(void* p, void* q) noexcept
{
    return p < q;
}

bool pointer_cmp_le_dep(void* p, void* q) noexcept
{
    return p <= q;
}
}
