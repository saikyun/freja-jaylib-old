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

//    Mesh GenMeshCubicmap(Image cubicmap, Vector3 cubeSize);
static Janet cfun_GenMeshCubicmap(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);

    Image *i = jaylib_getimage(argv, 0);
    Vector3 cubeSize = jaylib_getvec3(argv, 1);
    Mesh *mesh = janet_abstract(&AT_Mesh, sizeof(Mesh));
    *mesh = GenMeshCubicmap(*i, cubeSize);
    return janet_wrap_abstract(mesh);
}

//    Model LoadModelFromMesh(Mesh mesh);    // Load model from generated mesh (default material)
static Janet cfun_LoadModelFromMesh(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);

    Mesh *m = jaylib_getmesh(argv, 0);
    Model *model = janet_abstract(&AT_Model, sizeof(Model));
    *model = LoadModelFromMesh(*m);
    return janet_wrap_abstract(model);
}

static Janet cfun_GetModelMaterial(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);

    Model *model = jaylib_getmodel(argv, 0);
    int i = janet_getinteger(argv, 1);

    Material *mat = janet_abstract(&AT_Material, sizeof(Material));
    *mat = model->materials[i];

    return janet_wrap_abstract(mat);
}

static const KeyDef map_material_defs[] = {
    {"diffuse", MATERIAL_MAP_DIFFUSE},
};

static Janet cfun_SetMaterialTexture(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);

    Material *mat = jaylib_getmaterial(argv, 0);
    Texture2D *tex = jaylib_gettexture2d(argv, 1);
    const uint8_t *map_material = janet_getkeyword(argv, 2);

    int map_int = -1;
    for (unsigned j = 0; j < (sizeof(map_material_defs) / sizeof(KeyDef)); j++) {

                printf("%s - %s", map_material, map_material_defs[j].name);
        if (!janet_cstrcmp(map_material, map_material_defs[j].name))
            {
                map_int = map_material_defs[j].key;
               	break;
            }
    }

    if (-1 == map_int) {
        JanetArray *available = janet_array(0);
        for (unsigned j = 0; j < (sizeof(map_material_defs) / sizeof(KeyDef)); j++) {
            janet_array_push(available, janet_ckeywordv(map_material_defs[j].name));
        }
        janet_panicf("unknown material map %v - available material map are %p", argv[2],	janet_wrap_array(available));
    }

    mat->maps[map_int].texture = *tex;

    return janet_wrap_nil();
}


static Janet cfun_DrawModel(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);

    Model *model = jaylib_getmodel(argv, 0);
    Vector3 pos = jaylib_getvec3(argv, 1);
    float scale = janet_getnumber(argv, 2);
    Color tint = jaylib_getcolor(argv, 3);

    DrawModel(*model, pos, scale, tint);

    return janet_wrap_nil();
}

static JanetReg models_cfuns[] = {
    {"draw-billboard", cfun_DrawBillboard, NULL},
    {"gen-mesh-cubicmap", cfun_GenMeshCubicmap, NULL},
    {"load-model-from-mesh", cfun_LoadModelFromMesh, NULL},
    {"get-model-material", cfun_GetModelMaterial, NULL},
    {"set-material-texture", cfun_SetMaterialTexture, NULL},
    {"draw-model", cfun_DrawModel, NULL},
    {NULL, NULL, NULL}
};
