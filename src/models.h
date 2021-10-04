static Janet cfun_DrawBillboard(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);

    Camera *c = jaylib_getcamera3d(argv, 0);
    Texture2D *t = jaylib_gettexture2d(argv, 1);
    Vector3 center = jaylib_getvec3(argv, 2);
    float size = janet_getnumber(argv, 3);
    Color col = jaylib_getcolor(argv, 4);

    DrawBillboard(*c, *t, center, size, col);

    return janet_wrap_nil();
}

static JanetReg models_cfuns[] = {
    {"draw-billboard", cfun_DrawBillboard, NULL},
    {NULL, NULL, NULL}
};
