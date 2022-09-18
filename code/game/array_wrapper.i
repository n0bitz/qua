%{
typedef struct {
    void *array;
    size_t dim;
    swig_type_info *type;
} array_wrapper;

int array_wrapper_index(lua_State *L) {
    array_wrapper *wrapper;
    size_t index;

    wrapper = luaL_checkudata(L, 1, "array_wrapper");
    luaL_argcheck(L, wrapper != NULL, 1, "`array_wrapper` expected");

    index = luaL_checkinteger(L, 2);
    luaL_argcheck(L, index < wrapper->dim, 2, "index out of range");

    if(wrapper->type == SWIGTYPE_p_float) {
        lua_pushnumber(L, ((float*)wrapper->array)[index]);
    } else {
        SWIG_NewPointerObj(L, wrapper->array, wrapper->type, 0);
    }
    return 1;
}

int array_wrapper_newindex(lua_State *L) {
    array_wrapper *wrapper;
    size_t index;

    wrapper = luaL_checkudata(L, 1, "array_wrapper");
    luaL_argcheck(L, wrapper != NULL, 1, "`array_wrapper` expected");

    index = luaL_checkinteger(L, 2);
    luaL_argcheck(L, index < wrapper->dim, 2, "index out of range");

    if(wrapper->type == SWIGTYPE_p_float) {
        float value = luaL_checknumber(L, 3);
        ((float*)wrapper->array)[index] = value;
    } else {
        luaL_argerror(L, 1, "assignment not supported for this type");
    }

    return 0;
}
%}

%init {
    luaL_newmetatable(L, "array_wrapper");
    lua_pushstring(L, "__index");
    lua_pushcfunction(L, array_wrapper_index);
    lua_rawset(L, -3);
    lua_pushstring(L, "__newindex");
    lua_pushcfunction(L, array_wrapper_newindex);
    lua_rawset(L, -3);
    lua_pop(L, 1);
}

%typemap(out) SWIGTYPE[ANY] {
    array_wrapper *wrapper = (array_wrapper*)lua_newuserdata(L, sizeof(array_wrapper));
    luaL_getmetatable(L, "array_wrapper");
    lua_setmetatable(L, -2);
    wrapper->array = $1;
    wrapper->dim = $1_dim0;
    wrapper->type = $1_descriptor;
    SWIG_arg++;
}
